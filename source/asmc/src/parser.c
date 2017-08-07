/****************************************************************************
*
*			     Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:	Parser
*
****************************************************************************/

#include <limits.h>

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <preproc.h>
#include <reswords.h>
#include <codegen.h>
#include <expreval.h>
#include <fixup.h>
#include <types.h>
#include <label.h>
#include <segment.h>
#include <assume.h>
#include <proc.h>
#include <input.h>
#include <tokenize.h>
#include <listing.h>
#include <data.h>
#include <fastpass.h>
#include <omf.h>
#include <omfspec.h>
#include <condasm.h>
#include <extern.h>
#include <atofloat.h>

#define ADDRSIZE( s, x ) ( ( ( x ) ^ ( s ) ) ? TRUE : FALSE )
#define IS_ADDR32( s )	( s->Ofssize ? ( s->prefix.adrsiz == FALSE ) : ( s->prefix.adrsiz == TRUE ))

#define OPSIZE32( s ) ( ( s->Ofssize ) ? FALSE : TRUE )
#define OPSIZE16( s ) ( ( s->Ofssize ) ? TRUE : FALSE )

#define InWordRange( val ) ( (val > 65535 || val < -65535) ? FALSE : TRUE )

extern ret_code (* const directive_tab[])( int, struct asm_tok[] );

/* parsing of branch instructions with imm operand is found in branch.c */
int process_branch( struct code_info *, unsigned, const struct expr * );
int ExpandLine( char *, struct asm_tok[] );
int ExpandHllProc( char *, int, struct asm_tok[] );

extern enum proc_status ProcStatus;
extern const int_64	maxintvalues[];
extern const int_64	minintvalues[];
extern const struct opnd_class opnd_clstab[];
extern const uint_8	vex_flags[];
extern int_8	       Frame_Type;     /* Frame of current fixup */
extern uint_16	       Frame_Datum;    /* Frame datum of current fixup */

struct asym		*SegOverride;
static enum assume_segreg  LastRegOverride;/* needed for CMPS */

/* linked lists of:	index
 *--------------------------------
 * - undefined symbols	TAB_UNDEF
 * - externals		TAB_EXT
 * - segments		TAB_SEG
 * - groups		TAB_GRP
 * - procedures		TAB_PROC
 * - aliases		TAB_ALIAS
 */
struct symbol_queue SymTables[TAB_LAST];

/* add item to linked list of symbols */

void sym_add_table( struct symbol_queue *queue, struct dsym *item )
/*****************************************************************/
{
    if( queue->head == NULL ) {
	queue->head = queue->tail = item;
	item->next = item->prev = NULL;
    } else {
	item->prev = queue->tail;
	queue->tail->next = item;
	queue->tail = item;
	item->next = NULL;
    }
}

/* remove an item from a symbol queue.
 * this is called only for TAB_UNDEF and TAB_EXT,
 * segments, groups, procs or aliases never change their state.
 */
void sym_remove_table( struct symbol_queue *queue, struct dsym *item )
/********************************************************************/
{
    /* unlink the node */
    if( item->prev )
	item->prev->next = item->next;
    if( item->next )
	item->next->prev = item->prev;
    if ( queue->head == item )
	queue->head = item->next;
    if ( queue->tail == item )
	queue->tail = item->prev;

    item->next = NULL;
    item->prev = NULL;
}

void sym_ext2int( struct asym *sym )
/**********************************/
/* Change symbol state from SYM_EXTERNAL to SYM_INTERNAL.
 * called by:
 * - CreateConstant()		  EXTERNDEF name:ABS	       -> constant
 * - CreateAssemblyTimeVariable() EXTERNDEF name:ABS	       -> assembly-time variable
 * - CreateLabel()		  EXTERNDEF name:NEAR|FAR|PROC -> code label
 * - data_dir()			  EXTERNDEF name:typed memref  -> data label
 * - ProcDir()		 PROTO or EXTERNDEF name:NEAR|FAR|PROC -> PROC
 */
{
    /* v2.07: GlobalQueue has been removed */
    if ( sym->isproc == FALSE && sym->ispublic == FALSE ) {
	sym->ispublic = TRUE;
	AddPublicData( sym );
    }
    sym_remove_table( &SymTables[TAB_EXT], (struct dsym *)sym );
    if ( sym->isproc == FALSE ) /* v2.01: don't clear flags for PROTO */
	sym->first_size = 0;
    sym->state = SYM_INTERNAL;
}

int GetLangType( int *i, struct asm_tok tokenarray[], unsigned char *plang )
/********************************************************************************/
{
    if( tokenarray[*i].token == T_RES_ID ) {
	if ( tokenarray[(*i)].tokval >= T_C &&
	    tokenarray[(*i)].tokval <= T_FASTCALL ) {
	    *plang = tokenarray[(*i)].bytval;
	    (*i)++;
	    return( NOT_ERROR );
	}
    }
    return( ERROR );
}

/* get size of a register
 * v2.06: rewritten, since the sflags field
 * does now contain size for GPR, STx, MMX, XMM regs.
 */

int SizeFromRegister( int registertoken )
/***************************************/
{
    unsigned flags;
    flags = GetSflagsSp( registertoken ) & SFR_SIZMSK;

    if ( flags )
	return( flags );

    flags = GetValueSp( registertoken );
    if ( flags & OP_SR )
	return( CurrWordSize );

    /* CRx, DRx, TRx remaining */
    return( ModuleInfo.Ofssize == USE64 ? 8 : 4 );
}

/* get size from memory type */

/* MT_PROC memtype is set ONLY in typedefs ( state=SYM_TYPE, typekind=TYPE_TYPEDEF)
 * and makes the type a PROTOTYPE. Due to technical (obsolete?) restrictions the
 * prototype data is stored in another symbol and is referenced in the typedef's
 * target_type member.
 */
int SizeFromMemtype( unsigned char mem_type, int Ofssize, struct asym *type )
/**************************************************************************/
{
    if ( ( mem_type & MT_SPECIAL) == 0 )
	return ( (mem_type & MT_SIZE_MASK) + 1 );

    if ( Ofssize == USE_EMPTY )
	Ofssize = ModuleInfo.Ofssize;

    switch ( mem_type ) {
    case MT_NEAR:
	return ( 2 << Ofssize );
    case MT_FAR:
	return ( ( 2 << Ofssize ) + 2 );
    case MT_PROC:
	return( ( 2 << Ofssize ) + ( type->isfar ? 2 : 0 ) );
    case MT_PTR:
	return( ( 2 << Ofssize ) + ( ( SIZE_DATAPTR & ( 1 << ModuleInfo.model ) ) ? 2 : 0 ) );
    case MT_TYPE:
	if ( type )
	    return( type->total_size );
    default:
	return( 0 );
    }
}

/* get memory type from size */
int MemtypeFromSize( int size, unsigned char *ptype )
/*******************************************************/
{
    int i;
    for ( i = T_BYTE; SpecialTable[i].type == RWT_STYPE; i++ ) {
	if( ( SpecialTable[i].bytval & MT_SPECIAL ) == 0 ) {
	    /* the size is encoded 0-based in field mem_type */
	    if( ( ( SpecialTable[i].bytval & MT_SIZE_MASK) + 1 ) == size ) {
		*ptype = SpecialTable[i].bytval;
		return( NOT_ERROR );
	    }
	}
    }
    return( ERROR );
}

int OperandSize( enum operand_type opnd, const struct code_info *CodeInfo )
/*************************************************************************/
{
    /* v2.0: OP_M8_R8 and OP_M16_R16 have the DFT bit set! */
    if( opnd == OP_NONE ) {
	return( 0 );
    } else if( opnd == OP_M ) {
	return( SizeFromMemtype( CodeInfo->mem_type, CodeInfo->Ofssize, NULL ) );
    } else if( opnd & ( OP_R8 | OP_M08 | OP_I8 ) ) {
	return( 1 );
    } else if( opnd & ( OP_R16 | OP_M16 | OP_I16 | OP_SR ) ) {
	return( 2 );
    } else if( opnd & ( OP_R32 | OP_M32 | OP_I32 ) ) {
	return( 4 );
    } else if( opnd & ( OP_R64 | OP_M64 | OP_MMX | OP_I64 ) ) {
	return( 8 );
    } else if( opnd & ( OP_I48 | OP_M48 ) ) {
	return( 6 );
    } else if( opnd & ( OP_STI | OP_M80 ) ) {
	return( 10 );
    } else if( opnd & ( OP_XMM | OP_M128 ) ) {
	return( 16 );
    } else if( opnd & ( OP_YMM | OP_M256 ) ) {
	return( 32 );
    } else if( opnd & OP_RSPEC ) {
	return( ( CodeInfo->Ofssize == USE64 ) ? 8 : 4 );
    }
    return( 0 );
}

static int comp_mem16( int reg1, int reg2 )
/*****************************************/
/*
- compare and return the r/m field encoding of 16-bit address mode;
- call by set_rm_sib() only;
*/
{
    switch( reg1 ) {
    case T_BX:
	switch( reg2 ) {
	case T_SI: return( RM_BX_SI ); /* 00 */
	case T_DI: return( RM_BX_DI ); /* 01 */
	}
	break;
    case T_BP:
	switch( reg2 ) {
	case T_SI: return( RM_BP_SI ); /* 02 */
	case T_DI: return( RM_BP_DI ); /* 03 */
	}
	break;
    default:
	return( asmerr( 2030 ) );
    }
    return( asmerr( 2029 ) );
}

static void check_assume( struct code_info *CodeInfo, const struct asym *sym, enum assume_segreg default_reg )
/************************************************************************************************************/
/* Check if an assumed segment register is found, and
 * set CodeInfo->RegOverride if necessary.
 * called by seg_override().
 * at least either sym or SegOverride is != NULL.
 */
{
    enum assume_segreg	   reg;
    struct asym		   *assume;

    if( sym && sym->state == SYM_UNDEFINED )
	return;

    reg = GetAssume( SegOverride, sym, default_reg, &assume );
    /* set global vars Frame and Frame_Datum */
    SetFixupFrame( assume, FALSE );

    if( reg == ASSUME_NOTHING ) {
	if ( sym ) {
	    if( sym->segment != NULL ) {
		asmerr( 2074, sym->name );
	    } else
		CodeInfo->prefix.RegOverride = default_reg;
	} else {
	    asmerr( 2074, SegOverride->name );
	}
    } else if( default_reg != EMPTY ) {
	CodeInfo->prefix.RegOverride = reg;
    }
}

static void seg_override( struct code_info *CodeInfo, int seg_reg, const struct asym *sym, bool direct )
/******************************************************************************************************/
/*
 * called by set_rm_sib(). determine if segment override is necessary
 * with the current address mode;
 * - seg_reg: register index (T_DS, T_BP, T_EBP, T_BX, ... )
 */
{
    enum assume_segreg	default_seg;
    struct asym		*assume;

    /* don't touch segment overrides for string instructions */
    if ( CodeInfo->pinstr->allowed_prefix == AP_REP ||
	 CodeInfo->pinstr->allowed_prefix == AP_REPxx )
	return;

    if( CodeInfo->token == T_LEA ) {
	CodeInfo->prefix.RegOverride = EMPTY; /* skip segment override */
	SetFixupFrame( sym, FALSE );
	return;
    }

    switch( seg_reg ) {
    case T_BP:
    case T_EBP:
    case T_ESP:
	/* todo: check why cases T_RBP/T_RSP aren't needed! */
	default_seg = ASSUME_SS;
	break;
    default:
	default_seg = ASSUME_DS;
    }

    if( CodeInfo->prefix.RegOverride != EMPTY ) {
	assume = GetOverrideAssume( CodeInfo->prefix.RegOverride );
	/* assume now holds assumed SEG/GRP symbol */
	if ( sym ) {
	    SetFixupFrame( assume ? assume : sym, FALSE );
	} else if ( direct ) {
	    /* no label attached (DS:[0]). No fixup is to be created! */
	    if ( assume ) {
		CodeInfo->prefix.adrsiz = ADDRSIZE( CodeInfo->Ofssize, GetSymOfssize( assume ) );
	    } else {
		/* v2.01: if -Zm, then use current CS offset size.
		 * This isn't how Masm v6 does it, but it matches Masm v5.
		 */
		if ( ModuleInfo.m510 )
		    CodeInfo->prefix.adrsiz = ADDRSIZE( CodeInfo->Ofssize, ModuleInfo.Ofssize );
		else
		    CodeInfo->prefix.adrsiz = ADDRSIZE( CodeInfo->Ofssize, ModuleInfo.defOfssize );
	    }
	}
    } else {
	if ( sym || SegOverride )
	    check_assume( CodeInfo, sym, default_seg );
	if ( sym == NULL && SegOverride ) {
	    CodeInfo->prefix.adrsiz = ADDRSIZE( CodeInfo->Ofssize, GetSymOfssize( SegOverride ) );
	}
    }

    if( CodeInfo->prefix.RegOverride == default_seg ) {
	CodeInfo->prefix.RegOverride = EMPTY;
    }
}

/* prepare fixup creation
 * called by:
 * - idata_fixup()
 * - process_branch() in branch.c
 * - data_item() in data.c
 */

void set_frame( const struct asym *sym )
/**************************************/
{
    SetFixupFrame( SegOverride ? SegOverride : sym, FALSE );
}

/* set fixup frame if OPTION OFFSET:SEGMENT is set and
 * OFFSET or SEG operator was used.
 * called by:
 * - idata_fixup()
 * - data_item()
 */
void set_frame2( const struct asym *sym )
/***************************************/
{
    SetFixupFrame( SegOverride ? SegOverride : sym, TRUE );
}

static int set_rm_sib( struct code_info *CodeInfo, unsigned CurrOpnd, char ss, int index, int base, const struct asym *sym )
/*******************************************************************************************************************************/
/*
 * encode ModRM and SIB byte for memory addressing.
 * called by memory_operand().
 * in:	ss = scale factor (00=1,40=2,80=4,C0=8)
 *   index = index register (T_DI, T_ESI, ...)
 *    base = base register (T_EBP, ... )
 *     sym = symbol (direct addressing, displacement)
 * out: CodeInfo->rm_byte, CodeInfo->sib, CodeInfo->prefix.rex
*/
{
    int			temp;
    unsigned char	mod_field;
    unsigned char	rm_field;
    unsigned char	base_reg;
    unsigned char	idx_reg;
    unsigned char	bit3_base;
    unsigned char	bit3_idx;
    unsigned char	rex;

    /* clear mod */
    rm_field = 0;
    bit3_base = 0;
    bit3_idx = 0;
    rex = 0;
    if( CodeInfo->opnd[CurrOpnd].InsFixup != NULL ) { /* symbolic displacement given? */
	mod_field = MOD_10;
    } else if( CodeInfo->opnd[CurrOpnd].data32l == 0 ) { /* no displacement (or 0) */
	mod_field = MOD_00;
    } else if( ( CodeInfo->opnd[CurrOpnd].data32l > SCHAR_MAX )
       || ( CodeInfo->opnd[CurrOpnd].data32l < SCHAR_MIN ) ) {
	mod_field = MOD_10; /* full size displacement */
    } else {
	mod_field = MOD_01; /* byte size displacement */
    }

    if( ( index == EMPTY ) && ( base == EMPTY ) ) {
	/* direct memory.
	 * clear the rightmost 3 bits
	 */
	CodeInfo->isdirect = TRUE;
	mod_field = MOD_00;

	/* default is DS:[], DS: segment override is not needed */
	seg_override( CodeInfo, T_DS, sym, TRUE );

	if( ( CodeInfo->Ofssize == USE16 && CodeInfo->prefix.adrsiz == 0 ) ||
	    ( CodeInfo->Ofssize == USE32 && CodeInfo->prefix.adrsiz == 1 )) {
	    if( !InWordRange( CodeInfo->opnd[CurrOpnd].data32l ) ) {
		return( asmerr( 2011 ) );
	    }
	    rm_field = RM_D16; /* D16=110b */
	} else {
	    rm_field = RM_D32; /* D32=101b */
	    if ( CodeInfo->Ofssize == USE64 && CodeInfo->opnd[CurrOpnd].InsFixup == NULL ) {
		rm_field = RM_SIB;
		CodeInfo->sib = 0x25; /* IIIBBB, base=101b, index=100b */
	    }
	}
    } else if( ( index == EMPTY ) && ( base != EMPTY ) ) {
	/* for SI, DI and BX: default is DS:[],
	 * DS: segment override is not needed
	 * for BP: default is SS:[], SS: segment override is not needed
	 */
	switch( base ) {
	case T_SI:
	    rm_field = RM_SI; /* 4 */
	    break;
	case T_DI:
	    rm_field = RM_DI; /* 5 */
	    break;
	case T_BP:
	    rm_field = RM_BP; /* 6 */
	    if( mod_field == MOD_00 ) {
		mod_field = MOD_01;
	    }
	    break;
	case T_BX:
	    rm_field = RM_BX; /* 7 */
	    break;
	default: /* for 386 and up */
	    base_reg = GetRegNo( base );
	    bit3_base = base_reg >> 3;
	    base_reg &= BIT_012;
	    rm_field = base_reg;
	    if ( base_reg == 4 ) {
		/* 4 is RSP/ESP or R12/R12D, which must use SIB encoding.
		 * SSIIIBBB, ss = 00, index = 100b ( no index ), base = 100b ( ESP ) */
		CodeInfo->sib = 0x24;
	    } else if ( base_reg == 5 && mod_field == MOD_00 ) {
		/* 5 is [E|R]BP or R13[D]. Needs displacement */
		mod_field = MOD_01;
	    }
	    rex = bit3_base; /* set REX_R */
	}
	seg_override( CodeInfo, base, sym, FALSE );
    } else if( ( index != EMPTY ) && ( base == EMPTY ) ) {
	idx_reg = GetRegNo( index );
	bit3_idx = idx_reg >> 3;
	idx_reg &= BIT_012;
	/* mod field is 00 */
	mod_field = MOD_00;
	/* s-i-b is present ( r/m = 100b ) */
	rm_field = RM_SIB;
	/* scale factor, index, base ( 0x05 => no base reg ) */
	CodeInfo->sib = ( ss | ( idx_reg << 3 ) | 0x05 );
	rex = (bit3_idx << 1); /* set REX_X */
	/* default is DS:[], DS: segment override is not needed */
	seg_override( CodeInfo, T_DS, sym, FALSE );
    } else {
	/* base != EMPTY && index != EMPTY */
	base_reg = GetRegNo( base );
	idx_reg	 = GetRegNo( index );
	bit3_base = base_reg >> 3;
	bit3_idx  = idx_reg  >> 3;
	base_reg &= BIT_012;
	idx_reg	 &= BIT_012;
	if ( ( GetSflagsSp( base ) & GetSflagsSp( index ) & SFR_SIZMSK ) == 0 ) {
	    return( asmerr( 2082 ) );
	}
	switch( index ) {
	case T_BX:
	case T_BP:
	    if( ( temp = comp_mem16( index, base ) ) == ERROR )
		return( ERROR );
	    rm_field = temp;
	    seg_override( CodeInfo, index, sym, FALSE );
	    break;
	case T_SI:
	case T_DI:
	    if( ( temp = comp_mem16( base, index ) ) == ERROR )
		return( ERROR );
	    rm_field = temp;
	    seg_override( CodeInfo, base, sym, FALSE );
	    break;
	case T_RSP:
	case T_ESP:
	    return( asmerr( 2032 ) );
	default:
	    if( base_reg == 5 ) { /* v2.03: EBP/RBP/R13/R13D? */
		if( mod_field == MOD_00 ) {
		    mod_field = MOD_01;
		}
	    }
	    /* s-i-b is present ( r/m = 100b ) */
	    rm_field |= RM_SIB;
	    CodeInfo->sib = ( ss | idx_reg << 3 | base_reg );
	    rex = (bit3_idx << 1) + (bit3_base); /* set REX_X + REX_B */
	    seg_override( CodeInfo, base, sym, FALSE );
	} /* end switch(index) */
    }
    if( CurrOpnd == OPND2 ) {
	/* shift the register field to left by 3 bit */
	CodeInfo->rm_byte = mod_field | ( rm_field << 3 ) | ( CodeInfo->rm_byte & BIT_012 );
	CodeInfo->prefix.rex |= ( ( rex >> 2 ) | ( rex & REX_X ) | (( rex & 1) << 2 ) );
    } else if( CurrOpnd == OPND1 ) {
	CodeInfo->rm_byte = mod_field | rm_field;
	CodeInfo->prefix.rex |= rex;
    }
    return( NOT_ERROR );
}

/* override handling
 * called by
 * - process_branch()
 * - idata_fixup()
 * - memory_operand() (CodeInfo != NULL)
 * - data_item()
 * 1. If it's a segment register, set CodeInfo->prefix.RegOverride.
 * 2. Set global variable SegOverride if it's a SEG/GRP symbol
 *    (or whatever is assumed for the segment register)
 */
int segm_override( const struct expr *opndx, struct code_info *CodeInfo )
/****************************************************************************/
{
    struct asym	     *sym;

    if( opndx->override != NULL ) {
	if( opndx->override->token == T_REG ) {
	    int temp = GetRegNo( opndx->override->tokval );
	    if ( SegAssumeTable[temp].error ) {
		return( asmerr(2108) );
	    }
	    /* ES,CS,SS and DS overrides are invalid in 64-bit */
	    if ( CodeInfo && CodeInfo->Ofssize == USE64 && temp < ASSUME_FS ) {
		return( asmerr( 2202 ) );
	    }
	    sym = GetOverrideAssume( temp );
	    if ( CodeInfo ) {
		/* hack: save the previous reg override value (needed for CMPS) */
		LastRegOverride = CodeInfo->prefix.RegOverride;
		CodeInfo->prefix.RegOverride = temp;
	    }
	} else {
	    sym = SymSearch( opndx->override->string_ptr );
	}
	if ( sym && ( sym->state == SYM_GRP || sym->state == SYM_SEG ))
	    SegOverride = sym;
    }
    return( NOT_ERROR );
}

/* get an immediate operand without a fixup.
 * output:
 * - ERROR: error
 * - NOT_ERROR: ok,
 *   CodeInfo->opnd_type[CurrOpnd] = OP_Ix
 *   CodeInfo->data[CurrOpnd]	   = value
 *   CodeInfo->prefix.opsiz
 *   CodeInfo->iswide
 */
static int idata_nofixup( struct code_info *CodeInfo, unsigned CurrOpnd, const struct expr *opndx )
/******************************************************************************************************/
{
    enum operand_type op_type;
    int_32	value;
    int		size;

    /* jmp/call/jxx/loop/jcxz/jecxz? */
    if( IS_ANY_BRANCH( CodeInfo->token ) ) {
	return( process_branch( CodeInfo, CurrOpnd, opndx ) );
    }
    value = opndx->value;
    CodeInfo->opnd[CurrOpnd].data32l = value;

    /* 64bit immediates are restricted to MOV <reg>,<imm64>
     */
    if ( opndx->hlvalue != 0 ) { /* magnitude > 64 bits? */
	return( EmitConstError( opndx ) );
    }
    /* v2.03: handle QWORD type coercion here as well!
     * This change also reveals an old problem in the expression evaluator:
     * the mem_type field is set whenever a (simple) type token is found.
     * It should be set ONLY when the type is used in conjuction with the
     * PTR operator!
     * current workaround: query the 'explicit' flag.
     */
    /* use long format of MOV for 64-bit if value won't fit in a signed DWORD */
    if ( CodeInfo->Ofssize == USE64 &&
	CodeInfo->token == T_MOV &&
	CurrOpnd == OPND2 &&
	( CodeInfo->opnd[OPND1].type & OP_R64 ) &&
	( opndx->value64 > LONG_MAX || opndx->value64 < LONG_MIN ||
	 (opndx->explicit && ( opndx->mem_type == MT_QWORD || opndx->mem_type == MT_SQWORD ) ) ) ) {
	// CodeInfo->iswide = 1; /* has been set by first operand already */
	CodeInfo->opnd[CurrOpnd].type = OP_I64;
	CodeInfo->opnd[CurrOpnd].data32h = opndx->hvalue;
	return( NOT_ERROR );
    }
    if ( opndx->value64 <= minintvalues[0] || opndx->value64 > maxintvalues[0] ) {
	return( EmitConstError( opndx ) );
    }

    /* v2.06: code simplified.
     * to be fixed: the "wide" bit should not be set here!
     * Problem: the "wide" bit isn't set in memory_operand(),
     * probably because of the instructions which accept both
     * signed and unsigned arguments (ADD, CMP, ... ).
     */

    if ( opndx->explicit ) {
	/* size coercion for immediate value */
	CodeInfo->const_size_fixed = TRUE;
	size = SizeFromMemtype( opndx->mem_type,
			       opndx->Ofssize,
			       opndx->type );
	/* don't check if size and value are compatible. */
	switch ( size ) {
	case 1: op_type = OP_I8;  break;
	case 2: op_type = OP_I16; break;
	case 4: op_type = OP_I32; break;
	default:
	    return( asmerr( 2070 ) );
	}
    } else {
	/* use true signed values for BYTE only! */
	if ( (int_8)value == value )
	    op_type = OP_I8;
	else if( value <= USHRT_MAX && value >= 0L - USHRT_MAX )
	    op_type = OP_I16;
	else {
	    op_type = OP_I32;
	}
    }

    switch ( CodeInfo->token ) {
    case T_PUSH:
	if ( opndx->explicit == FALSE ) {
	    if ( CodeInfo->Ofssize > USE16 && op_type == OP_I16 )
		op_type = OP_I32;
	}
	if ( op_type == OP_I16 )
	    CodeInfo->prefix.opsiz = OPSIZE16( CodeInfo );
	else if ( op_type == OP_I32 )
	    CodeInfo->prefix.opsiz = OPSIZE32( CodeInfo );
	break;
    case T_PUSHW:
	if ( op_type != OP_I32 ) {
	    op_type = OP_I16;
	    if( (int_8)value == (int_16)value ) {
		op_type = OP_I8;
	    }
	}
	break;
    case T_PUSHD:
	if ( op_type == OP_I16 )
	    op_type = OP_I32;
	break;
    }

    /* v2.11: set the wide-bit if a mem_type size of > BYTE is set???
     * actually, it should only be set if immediate is second operand
     * ( and first operand is a memory ref with a size > 1 )
     */
    if ( CurrOpnd == OPND2 )
	if ( !(CodeInfo->mem_type & MT_SPECIAL) && ( CodeInfo->mem_type & MT_SIZE_MASK ) )
	    CodeInfo->iswide = 1;

    CodeInfo->opnd[CurrOpnd].type = op_type;
    return( NOT_ERROR );
}

/* get an immediate operand with a fixup.
 * output:
 * - ERROR: error
 * - NOT_ERROR: ok,
 *   CodeInfo->opnd_type[CurrOpnd] = OP_Ix
 *   CodeInfo->data[CurrOpnd]	   = value
 *   CodeInfo->InsFixup[CurrOpnd]  = fixup
 *   CodeInfo->mem_type
 *   CodeInfo->prefix.opsiz
 * to be fixed: don't modify CodeInfo->mem_type here!
 */
int idata_fixup( struct code_info *CodeInfo, unsigned CurrOpnd, struct expr *opndx )
/***************************************************************************************/
{
    enum fixup_types	fixup_type;
    enum fixup_options	fixup_option = OPTJ_NONE;
    int			size;
    uint_8		Ofssize; /* 1=32bit, 0=16bit offset for fixup */

    /* jmp/call/jcc/loopcc/jxcxz? */
    if( IS_ANY_BRANCH( CodeInfo->token ) ) {
	return( process_branch( CodeInfo, CurrOpnd, opndx ) );
    }
    CodeInfo->opnd[CurrOpnd].data32l = opndx->value;

    if ( opndx->Ofssize != USE_EMPTY ) {
	Ofssize = opndx->Ofssize;
    } else if( ( opndx->sym->state == SYM_SEG )
	|| ( opndx->sym->state == SYM_GRP )
	|| ( opndx->instr == T_SEG ) ) {
	Ofssize = USE16;
    } else if( opndx->is_abs ) {  /* an (external) absolute symbol? */
	Ofssize = USE16;
    } else {
	Ofssize = GetSymOfssize( opndx->sym );
    }

    if( opndx->instr == T_SHORT ) {
	/* short works for branch instructions only */
	return( asmerr( 2070 ) );
    }

    /* the code below should be rewritten.
     * - an address operator ( OFFSET, LROFFSET, IMAGEREL, SECTIONREL,
     *	 LOW, HIGH, LOWWORD, HIGHWORD, LOW32, HIGH32, SEG ) should not
     *	 force a magnitude, but may set a minimal magnitude - and the
     *	 fixup type, of course.
     * - check if Codeinfo->mem_type really has to be set here!
     */

    if ( opndx->explicit && !opndx->is_abs ) {
	CodeInfo->const_size_fixed = TRUE;
	if ( CodeInfo->mem_type == MT_EMPTY )
	    CodeInfo->mem_type = opndx->mem_type;
    }
    if ( CodeInfo->mem_type == MT_EMPTY && CurrOpnd > OPND1 && opndx->Ofssize == USE_EMPTY ) {
	size = OperandSize( CodeInfo->opnd[OPND1].type, CodeInfo );
	/* may be a forward reference, so wait till pass 2 */
	if( Parse_Pass > PASS_1 && opndx->instr != EMPTY ) {
	    switch ( opndx->instr ) {
	    case T_SEG: /* v2.04a: added */
		if( size && (size < 2 ) ) {
		    return( asmerr( 2022, size, 2 ) );
		}
		break;
	    case T_OFFSET:
	    case T_LROFFSET:
	    case T_IMAGEREL:
	    case T_SECTIONREL:
		if( size && (size < 2 || ( Ofssize && size < 4 ))) {
		    return( asmerr( 2022, size, ( 2 << Ofssize ) ) );
		}
	    }
	}
	switch ( size ) {
	case 1:
	    if ( opndx->is_abs || opndx->instr == T_LOW || opndx->instr == T_HIGH )
		CodeInfo->mem_type = MT_BYTE;
	    break;
	case 2:
	    if ( opndx->is_abs ||
		CodeInfo->Ofssize == USE16 ||
		opndx->instr == T_LOWWORD ||
		opndx->instr == T_HIGHWORD )
		CodeInfo->mem_type = MT_WORD;
	    break;
	case 4:
	    CodeInfo->mem_type = MT_DWORD;
	    break;
	case 8:
	    if ( Ofssize == USE64 ) {
		if ( CodeInfo->token == T_MOV &&
		    ( CodeInfo->opnd[OPND1].type & OP_R64 ) )
		    CodeInfo->mem_type = MT_QWORD;
		else if ( opndx->instr == T_LOW32 || opndx->instr == T_HIGH32 )
		    /* v2.10:added; LOW32/HIGH32 in expreval.c won't set mem_type anymore. */
		    CodeInfo->mem_type = MT_DWORD;
	    }
	    break;
	}
    }
    if ( CodeInfo->mem_type == MT_EMPTY ) {
	if( opndx->is_abs ) {
	    if( opndx->mem_type != MT_EMPTY ) {
		CodeInfo->mem_type = opndx->mem_type;
	    } else if ( CodeInfo->token == T_PUSHW ) { /* v2.10: special handling PUSHW */
		CodeInfo->mem_type = MT_WORD;
	    } else {
		CodeInfo->mem_type = ( IS_OPER_32( CodeInfo ) ? MT_DWORD : MT_WORD );
	    }
	} else {
	    switch ( CodeInfo->token ) {
	    case T_PUSHW:
	    case T_PUSHD:
	    case T_PUSH:
		if ( opndx->mem_type == MT_EMPTY  ) {
		    switch( opndx->instr ) {
		    case EMPTY:
		    case T_LOW:
		    case T_HIGH:
			opndx->mem_type = MT_BYTE;
			break;
		    case T_LOW32: /* v2.10: added - low32_op() doesn't set mem_type anymore. */
		    case T_IMAGEREL:
		    case T_SECTIONREL:
			opndx->mem_type = MT_DWORD;
			break;
		    };
		}
		/* default: push offset only */
		/* for PUSH + undefined symbol, assume BYTE */
		if ( opndx->mem_type == MT_FAR && ( opndx->explicit == FALSE ) )
		    opndx->mem_type = MT_NEAR;
		/* v2.04: curly brackets added */
		if ( CodeInfo->token == T_PUSHW ) {
		    if ( SizeFromMemtype( opndx->mem_type, Ofssize, opndx->type ) < 2 )
			opndx->mem_type = MT_WORD;
		} else if ( CodeInfo->token == T_PUSHD ) {
		    if ( SizeFromMemtype( opndx->mem_type, Ofssize, opndx->type ) < 4 )
			opndx->mem_type = MT_DWORD;
		}
		break;
	    }
	    /* if a WORD size is given, don't override it with */
	    /* anything what might look better at first glance */
	    if( opndx->mem_type != MT_EMPTY )
		CodeInfo->mem_type = opndx->mem_type;
	    /* v2.04: assume BYTE size if symbol is undefined */
	    else if ( opndx->sym->state == SYM_UNDEFINED ) {
		CodeInfo->mem_type = MT_BYTE;
		fixup_option = OPTJ_PUSH;
	    } else
		/* v2.06d: changed */
		CodeInfo->mem_type = ( Ofssize == USE64 ? MT_QWORD : Ofssize == USE32 ? MT_DWORD : MT_WORD );
	}
    }
    size = SizeFromMemtype( CodeInfo->mem_type, Ofssize, NULL );
    switch( size ) {
    case 1:
	CodeInfo->opnd[CurrOpnd].type = OP_I8;
	CodeInfo->prefix.opsiz = FALSE; /* v2.10: reset opsize is not really a good idea - might have been set by previous operand */
	break;
    case 2:  CodeInfo->opnd[CurrOpnd].type = OP_I16; CodeInfo->prefix.opsiz = OPSIZE16( CodeInfo );  break;
    case 4:  CodeInfo->opnd[CurrOpnd].type = OP_I32; CodeInfo->prefix.opsiz = OPSIZE32( CodeInfo );  break;
    case 8:
	/* v2.05: do only assume size 8 if the constant won't fit in 4 bytes. */
	if ( opndx->value64 > LONG_MAX || opndx->value64 < LONG_MIN ||
	    (opndx->explicit && ( opndx->mem_type & MT_SIZE_MASK ) == 7 ) ) {
	    CodeInfo->opnd[CurrOpnd].type = OP_I64;
	    CodeInfo->opnd[CurrOpnd].data32h = opndx->hvalue;
	} else if ( Ofssize == USE64 && ( opndx->instr == T_OFFSET || ( CodeInfo->token == T_MOV && ( CodeInfo->opnd[OPND1].type & OP_R64 ) ) ) ) {
	    /* v2.06d: in 64-bit, ALWAYS set OP_I64, so "mov m64, ofs" will fail,
	     * This was accepted in v2.05-v2.06c)
	     */
	    CodeInfo->opnd[CurrOpnd].type = OP_I64;
	    CodeInfo->opnd[CurrOpnd].data32h = opndx->hvalue;
	} else {
	    CodeInfo->opnd[CurrOpnd].type = OP_I32;
	}
	CodeInfo->prefix.opsiz = OPSIZE32( CodeInfo );
	break;
    }

    /* set fixup_type */

    if( opndx->instr == T_SEG ) {
	fixup_type = FIX_SEG;
    } else if( CodeInfo->mem_type == MT_BYTE ) {
	if ( opndx->instr == T_HIGH ) {
	    fixup_type = FIX_HIBYTE;
	} else {
	    fixup_type = FIX_OFF8;
	}
    } else if( IS_OPER_32( CodeInfo ) ) {
	if ( CodeInfo->opnd[CurrOpnd].type == OP_I64 && ( opndx->instr == EMPTY || opndx->instr == T_OFFSET ) )
	    fixup_type = FIX_OFF64;
	else
	    if ( size >= 4 && opndx->instr != T_LOWWORD ) {
		/* v2.06: added branch for PTR16 fixup.
		 * it's only done if type coercion is FAR (Masm-compat)
		 */
		if ( opndx->explicit && Ofssize == USE16 && opndx->mem_type == MT_FAR )
		    fixup_type = FIX_PTR16;
		else
		    fixup_type = FIX_OFF32;
	    } else
		fixup_type = FIX_OFF16;
    } else {
	    fixup_type = FIX_OFF16;
    }
    /* v2.04: 'if' added, don't set W bit if size == 1
     * code example:
     *	 extern x:byte
     *	 or al,x
     * v2.11: set wide bit only if immediate is second operand.
     * and first operand is a memory reference with size > 1
     */
    if ( CurrOpnd == OPND2 && size != 1 )
	CodeInfo->iswide = 1;

    segm_override( opndx, NULL ); /* set SegOverride global var */

    /* set frame type in variables Frame_Type and Frame_Datum for fixup creation */
    if ( ModuleInfo.offsettype == OT_SEGMENT &&
	( opndx->instr == T_OFFSET || opndx->instr == T_SEG ))
	set_frame2( opndx->sym );
    else
	set_frame( opndx->sym );

    CodeInfo->opnd[CurrOpnd].InsFixup = CreateFixup( opndx->sym, fixup_type, fixup_option );

    if ( opndx->instr == T_LROFFSET )
	CodeInfo->opnd[CurrOpnd].InsFixup->loader_resolved = TRUE;

    if ( opndx->instr == T_IMAGEREL && fixup_type == FIX_OFF32 )
	CodeInfo->opnd[CurrOpnd].InsFixup->type = FIX_OFF32_IMGREL;
    if ( opndx->instr == T_SECTIONREL && fixup_type == FIX_OFF32 )
	CodeInfo->opnd[CurrOpnd].InsFixup->type = FIX_OFF32_SECREL;
    return( NOT_ERROR );
}

/* convert MT_PTR to MT_WORD, MT_DWORD, MT_FWORD, MT_QWORD.
 * MT_PTR cannot be set explicitely (by the PTR operator),
 * so this value must come from a label or a structure field.
 * (above comment is most likely plain wrong, see 'PF16 ptr [reg]'!
 * This code needs cleanup!
 */
static void SetPtrMemtype( struct code_info *CodeInfo, struct expr *opndx )
/*************************************************************************/
{
    struct asym *sym = opndx->sym;
    int size = 0;

    if ( opndx->mbr )  /* the mbr field has higher priority */
	sym = opndx->mbr;

    if ( opndx->explicit && opndx->type ) {
	size = opndx->type->total_size;
	CodeInfo->isfar = opndx->type->isfar;
    } else
    if ( sym ) {
	if ( sym->type ) {
	    size = sym->type->total_size;
	    CodeInfo->isfar = sym->type->isfar;

	    /* there's an ambiguity with pointers of size DWORD,
	     since they can be either NEAR32 or FAR16 */
	    if ( size == 4 && sym->type->Ofssize != CodeInfo->Ofssize )
		opndx->Ofssize = sym->type->Ofssize;

	} else if ( sym->mem_type == MT_PTR ) {
	    size = SizeFromMemtype( (unsigned char)(sym->isfar ? MT_FAR : MT_NEAR), sym->Ofssize, NULL );
	    CodeInfo->isfar = sym->isfar;
	} else	{
	    if ( sym->isarray )
		size = sym->total_size / sym->total_length;
	    else
		size = sym->total_size;
	}
    } else {
	if ( SIZE_DATAPTR & ( 1 << ModuleInfo.model ) ) {
	    size = 2;
	}
	size += (2 << ModuleInfo.defOfssize );
    }
    if ( size )
	MemtypeFromSize( size, &opndx->mem_type );
}

/*
 * set fields in CodeInfo:
 * - mem_type
 * - prefix.opsiz
 * - prefix.rex REX_W
 * called by memory_operand()
 */
//static void Set_Memtype( struct code_info *CodeInfo, enum memtype mem_type )
static void Set_Memtype( struct code_info *CodeInfo, unsigned char mem_type )
/**************************************************************************/
{
    if( CodeInfo->token == T_LEA )
	return;

    /* v2.05: changed. Set "data" types only. */
    if( mem_type == MT_EMPTY || mem_type == MT_TYPE ||
       mem_type == MT_NEAR || mem_type == MT_FAR )
	return;

    CodeInfo->mem_type = mem_type;

    if( CodeInfo->Ofssize > USE16 ) {
	/* if we are in use32 mode, we have to add OPSIZ prefix for
	 * most of the 386 instructions when operand has type WORD.
	 * Exceptions ( MOVSX and MOVZX ) are handled in check_size().
	 */
	if ( IS_MEM_TYPE( mem_type, WORD ) )
	    CodeInfo->prefix.opsiz = TRUE;
	/*
	 * set rex Wide bit if a QWORD operand is found (not for FPU/MMX/SSE instr).
	 * This looks pretty hackish now and is to be cleaned!
	 * v2.01: also had issues with SSE2 MOVSD/CMPSD, now fixed!
	 */
	/* v2.06: with AVX, SSE tokens may exist twice, one
	 * for "legacy", the other for VEX encoding!
	 */
	else if ( IS_MEMTYPE_SIZ( mem_type, sizeof( uint_64 ) ) ) {
	    switch( CodeInfo->token ) {
	    case T_PUSH: /* for PUSH/POP, REX_W isn't needed (no 32-bit variants in 64-bit mode) */
	    case T_POP:
	    case T_CMPXCHG8B:
	    case T_VMPTRLD:
	    case T_VMPTRST:
	    case T_VMCLEAR:
	    case T_VMXON:
		break;
	    default:
		/* don't set REX for opcodes that accept memory operands
		 * of any size.
		 */
		if ( opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type[OPND1] == OP_M_ANY ) {
		    //printf( "Set_Memtype: OP_M_ANY detected, file=%s, instr=%s\n", CurrFName[ASM], GetResWName( CodeInfo->token, NULL ) );
		    break;
		}
		/* don't set REX for FPU opcodes */
		if ( CodeInfo->pinstr->cpu & P_FPU_MASK )
		    break;
		/* don't set REX for - most - MMX/SSE opcodes */
		if ( CodeInfo->pinstr->cpu & P_EXT_MASK ) {
		    switch ( CodeInfo->token ) {
			/* [V]CMPSD and [V]MOVSD are also candidates,
			 * but currently they are handled in HandleStringInstructions()
			 */
		    case T_CVTSI2SD: /* v2.06: added */
		    case T_CVTSI2SS: /* v2.06: added */
		    case T_PEXTRQ: /* v2.06: added */
		    case T_PINSRQ: /* v2.06: added */
		    case T_MOVD:
		    case T_VCVTSI2SD:
		    case T_VCVTSI2SS:
		    case T_VPEXTRQ:
		    case T_VPINSRQ:
		    case T_VMOVD:
			CodeInfo->prefix.rex |= REX_W;
			break;
		    default:
			break;
		    }
		}
		else
		    CodeInfo->prefix.rex |= REX_W;
	    }
	}
    } else {
	if( IS_MEMTYPE_SIZ( mem_type, sizeof(uint_32) ) ) {

	    /* in 16bit mode, a DWORD memory access usually requires an OPSIZ
	     * prefix. A few instructions, which access m16:16 operands,
	     * are exceptions.
	     */
	    switch( CodeInfo->token ) {
	    case T_LDS:
	    case T_LES:
	    case T_LFS:
	    case T_LGS:
	    case T_LSS:
	    case T_CALL: /* v2.0: added */
	    case T_JMP:	 /* v2.0: added */
		/* in these cases, opsize does NOT need to be changed  */
		break;
	    default:
		CodeInfo->prefix.opsiz = TRUE;
		break;
	    }
	}
	/* v2.06: added because in v2.05, 64-bit memory operands were
	 * accepted in 16-bit code
	 */
	else if ( IS_MEMTYPE_SIZ( mem_type, sizeof(uint_64) ) ) {
	    if ( opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type[OPND1] == OP_M_ANY ) {
		//printf( "Set_Memtype: OP_M_ANY detected, file=%s, instr=%s\n", CurrFName[ASM], GetResWName( CodeInfo->token, NULL ) );
	    } else if ( CodeInfo->pinstr->cpu & ( P_FPU_MASK | P_EXT_MASK ) ) {
		;
	    } else if ( CodeInfo->token != T_CMPXCHG8B )
		/* setting REX.W will cause an error in codegen */
		CodeInfo->prefix.rex |= REX_W;
	}
    }
    return;
}

/*
 * process direct or indirect memory operand
 * in: opndx=operand to process
 * in: CurrOpnd=no of operand (0=first operand,1=second operand)
 * out: CodeInfo->data[]
 * out: CodeInfo->opnd_type[]
 */

static int memory_operand( struct code_info *CodeInfo, unsigned CurrOpnd, struct expr *opndx, bool with_fixup )
/******************************************************************************************************************/
{
    char		ss = SCALE_FACTOR_1;
    int			index;
    int			base;
    int			j;
    struct asym		*sym;
    uint_8		Ofssize;
    enum fixup_types	fixup_type;

    /* v211: use full 64-bit value */
    CodeInfo->opnd[CurrOpnd].data64 = opndx->value64;
    CodeInfo->opnd[CurrOpnd].type = OP_M;

    sym = opndx->sym;

    segm_override( opndx, CodeInfo );

    if ( opndx->mem_type == MT_PTR )
	SetPtrMemtype( CodeInfo, opndx );
    else if ( ( opndx->mem_type & MT_SPECIAL_MASK ) == MT_ADDRESS ) {
	int size;
	if ( opndx->Ofssize == USE_EMPTY && sym )
	    opndx->Ofssize = GetSymOfssize( sym );
	size = SizeFromMemtype( opndx->mem_type, opndx->Ofssize, opndx->type );
	MemtypeFromSize( size, &opndx->mem_type );
    }

    Set_Memtype( CodeInfo, opndx->mem_type );
    if( opndx->mbr != NULL ) {
	if ( opndx->mbr->mem_type == MT_TYPE && opndx->mem_type == MT_EMPTY ) {
	    //enum memtype mem_type;
	    unsigned char mem_type;
	    if ( MemtypeFromSize( opndx->mbr->total_size, &mem_type ) == NOT_ERROR )
		Set_Memtype( CodeInfo, mem_type );
	}
	if ( opndx->mbr->state == SYM_UNDEFINED )
	    CodeInfo->undef_sym = TRUE;
    }

    /* instruction-specific handling */
    switch ( CodeInfo->token ) {
    case T_JMP:
    case T_CALL:
	/* the 2 branch instructions are peculiar because they
	 * will work with an unsized label.
	 */
	/* v1.95: convert MT_NEAR/MT_FAR and display error if no type.
	 * For memory operands, expressions of type MT_NEAR/MT_FAR are
	 * call [bx+<code_label>]
	 */
	if ( CodeInfo->mem_type == MT_EMPTY ) {
	    /* with -Zm, no size needed for indirect CALL/JMP */
	    if ( ModuleInfo.m510 == FALSE &&
		( Parse_Pass > PASS_1 && opndx->sym == NULL ) ) {
		return( asmerr( 2023 ) );
	    }
	    opndx->mem_type = (CodeInfo->Ofssize == USE64) ? MT_QWORD : (CodeInfo->Ofssize == USE32) ? MT_DWORD : MT_WORD;
	    Set_Memtype( CodeInfo, opndx->mem_type );
	}
	j = SizeFromMemtype( CodeInfo->mem_type, CodeInfo->Ofssize, NULL );
	if ( ( j == 1 || j > 6 ) && ( CodeInfo->Ofssize != USE64 )) {
	    /* CALL/JMP possible for WORD/DWORD/FWORD memory operands only */
	    return( asmerr( 2024 ) );
	}

	if( opndx->mem_type == MT_FAR || CodeInfo->mem_type == MT_FWORD ||
	   ( CodeInfo->mem_type == MT_TBYTE && CodeInfo->Ofssize == USE64 ) ||
	    ( CodeInfo->mem_type == MT_DWORD &&
	      (( CodeInfo->Ofssize == USE16 && opndx->Ofssize != USE32 ) ||
	       ( CodeInfo->Ofssize == USE32 && opndx->Ofssize == USE16 )))) {
	    CodeInfo->isfar = TRUE;
	}
	break;
    }

    if ( ( CodeInfo->mem_type & MT_SPECIAL) == 0 ) {
	switch ( CodeInfo->mem_type & MT_SIZE_MASK ) {
	    /* size is encoded 0-based */
	case  0:  CodeInfo->opnd[CurrOpnd].type = OP_M08;  break;
	case  1:  CodeInfo->opnd[CurrOpnd].type = OP_M16;  break;
	case  3:  CodeInfo->opnd[CurrOpnd].type = OP_M32;  break;
	case  5:  CodeInfo->opnd[CurrOpnd].type = OP_M48;  break;
	case  7:  CodeInfo->opnd[CurrOpnd].type = OP_M64;  break;
	case  9:  CodeInfo->opnd[CurrOpnd].type = OP_M80;  break;
	case 15:  CodeInfo->opnd[CurrOpnd].type = OP_M128; break;
	case 31:  CodeInfo->opnd[CurrOpnd].type = OP_M256; break;
	}
    } else if ( CodeInfo->mem_type == MT_EMPTY ) {
	/* v2.05: added */
	switch ( CodeInfo->token ) {
	case T_INC:
	case T_DEC:
	    /* jwasm v1.94-v2.04 accepted unsized operand for INC/DEC */
	    if ( opndx->sym == NULL ) {
		return( asmerr( 2023 ) );
	    }
	    break;
	case T_PUSH:
	case T_POP:
	    if ( opndx->mem_type == MT_TYPE ) {
		return( asmerr( 2070 ) );
	    }
	    break;
	}
    }

    base = ( opndx->base_reg ? opndx->base_reg->tokval : EMPTY );
    index = ( opndx->idx_reg ? opndx->idx_reg->tokval : EMPTY );

    /* check for base registers */

    if ( base != EMPTY ) {
	if ( ( ( GetValueSp( base ) & OP_R32) && CodeInfo->Ofssize == USE32 ) ||
	    ( ( GetValueSp( base ) & OP_R64) && CodeInfo->Ofssize == USE64 ) ||
	    ( ( GetValueSp( base ) & OP_R16) && CodeInfo->Ofssize == USE16 ) )
	    CodeInfo->prefix.adrsiz = FALSE;
	else {
	    CodeInfo->prefix.adrsiz = TRUE;
	    /* 16bit addressing modes don't exist in long mode */
	    if ( ( GetValueSp( base ) & OP_R16) && CodeInfo->Ofssize == USE64 ) {
		return( asmerr( 2085 ) );
	    }
	}
    }

    /* check for index registers */

    if( index != EMPTY ) {
	if ( ( ( GetValueSp( index ) & OP_R32) && CodeInfo->Ofssize == USE32 ) ||
	    ( ( GetValueSp( index ) & OP_R64) && CodeInfo->Ofssize == USE64 ) ||
	    ( ( GetValueSp( index ) & OP_R16) && CodeInfo->Ofssize == USE16 ) ) {
	    CodeInfo->prefix.adrsiz = FALSE;
	} else {
	    CodeInfo->prefix.adrsiz = TRUE;
	}

	/* v2.10: register swapping has been moved to expreval.c, index_connect().
	 * what has remained here is the check if R/ESP is used as index reg.
	 */
	if ( GetRegNo( index ) == 4 ) { /* [E|R]SP? */
	    if( opndx->scale ) { /* no scale must be set */
		asmerr( 2031, GetResWName( index, NULL ) );
	    } else {
		asmerr( 2029 );
	    }
	    return( ERROR );
	}

	/* 32/64 bit indirect addressing? */
	if( ( CodeInfo->Ofssize == USE16 && CodeInfo->prefix.adrsiz == 1 ) ||
	   CodeInfo->Ofssize == USE64  ||
	   ( CodeInfo->Ofssize == USE32 && CodeInfo->prefix.adrsiz == 0 ) ) {
	    if( ( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_386 ) {
		/* scale, 0 or 1->00, 2->40, 4->80, 8->C0 */
		switch( opndx->scale ) {
		case 0:
		case 1:	 break; /* ss = 00 */
		case 2: ss = SCALE_FACTOR_2; break; /* ss = 01 */
		case 4: ss = SCALE_FACTOR_4; break; /* ss = 10 */
		case 8: ss = SCALE_FACTOR_8; break; /* ss = 11 */
		default: /* must be * 1, 2, 4 or 8 */
		    return( asmerr( 2083 ) );
		}
	    } else {
		/* 286 and down cannot use this memory mode */
		return( asmerr( 2085 ) );
	    }
	} else {
	    /* v2.01: 16-bit addressing mode. No scale possible */
	    if ( opndx->scale ) {
		return( asmerr( 2032 ) );
	    }
	}
    }

    if( with_fixup ) {

	if( opndx->is_abs ) {
	    Ofssize = IS_ADDR32( CodeInfo );
	} else if ( sym ) {
	    Ofssize = GetSymOfssize( sym );
	} else if ( SegOverride ) {
	    Ofssize = GetSymOfssize( SegOverride );
	} else
	    Ofssize = CodeInfo->Ofssize;

	/* now set fixup_type.
	 * for direct addressing, the fixup type can easily be set by
	 * the symbol's offset size.
	 */
	if( base == EMPTY && index == EMPTY ) {
	    CodeInfo->prefix.adrsiz = ADDRSIZE( CodeInfo->Ofssize, Ofssize );
	    if ( Ofssize == USE64 )
		/* v2.03: override with a segment assumed != FLAT? */
		if ( opndx->override != NULL &&
		    SegOverride != &ModuleInfo.flat_grp->sym )
		    fixup_type = FIX_OFF32;
		else
		    fixup_type = FIX_RELOFF32;
	    else
		fixup_type = ( Ofssize ) ? FIX_OFF32 : FIX_OFF16;
	} else {
	    if( Ofssize == USE64 ) {
		fixup_type = FIX_OFF32;
	    } else
	    if( IS_ADDR32( CodeInfo ) ) { /* address prefix needed? */
		/* changed for v1.95. Probably more tests needed!
		 * test case:
		 *   mov eax,[ebx*2-10+offset var] ;code and var are 16bit!
		 * the old code usually works fine because HiWord of the
		 * symbol's offset is zero. However, if there's an additional
		 * displacement which makes the value stored at the location
		 * < 0, then the target's HiWord becomes <> 0.
		 */
		fixup_type = FIX_OFF32;
	    } else {
		fixup_type = FIX_OFF16;
		if( Ofssize && Parse_Pass == PASS_2 ) {
		    /* address size is 16bit but label is 32-bit.
		     * example: use a 16bit register as base in FLAT model:
		     *	 test buff[di],cl */
		    asmerr( 8007, sym->name );
		}
	    }
	}

	if ( fixup_type == FIX_OFF32 )
	    if ( opndx->instr == T_IMAGEREL )
		fixup_type = FIX_OFF32_IMGREL;
	    else if ( opndx->instr == T_SECTIONREL )
		fixup_type = FIX_OFF32_SECREL;
	/* no fixups are needed for memory operands of string instructions and XLAT/XLATB.
	 * However, CMPSD and MOVSD are also SSE2 opcodes, so the fixups must be generated
	 * anyways.
	 */
	if ( CodeInfo->token != T_XLAT && CodeInfo->token != T_XLATB ) {
	    CodeInfo->opnd[CurrOpnd].InsFixup = CreateFixup( sym, fixup_type, OPTJ_NONE );
	}
    }

    if( set_rm_sib( CodeInfo, CurrOpnd, ss, index, base, sym ) == ERROR ) {
	return( ERROR );
    }
    /* set frame type/data in fixup if one was created */
    if ( CodeInfo->opnd[CurrOpnd].InsFixup ) {
	CodeInfo->opnd[CurrOpnd].InsFixup->frame_type = Frame_Type;
	CodeInfo->opnd[CurrOpnd].InsFixup->frame_datum = Frame_Datum;
    }

    return( NOT_ERROR );
}

static int process_address( struct code_info *CodeInfo, unsigned CurrOpnd, struct expr *opndx )
/**************************************************************************************************/
/*
 * parse the memory reference operand
 * CurrOpnd is 0 for first operand, 1 for second, ...
 * valid return values: NOT_ERROR, ERROR
 */
{
    if( opndx->indirect ) {  /* indirect register operand or stack var */

	/* if displacement doesn't fit in 32-bits:
	 * Masm (both ML and ML64) just truncates.
	 * JWasm throws an error in 64bit mode and
	 * warns (level 3) in the other modes.
	 * todo: this check should also be done for direct addressing!
	 */
	if ( opndx->hvalue && ( opndx->hvalue != -1 || opndx->value >= 0 ) ) {
	    if ( ModuleInfo.Ofssize == USE64 ) {
		return( EmitConstError( opndx ) );
	    }
	    asmerr( 8008, opndx->value64 );
	}
	if( opndx->sym == NULL || opndx->sym->state == SYM_STACK ) {
	    return( memory_operand( CodeInfo, CurrOpnd, opndx, FALSE ) );
	}
	/* do default processing */

    } else if( opndx->instr != EMPTY ) {
	/* instr is OFFSET | LROFFSET | SEG | LOW | LOWWORD, ... */
	if( opndx->sym == NULL ) { /* better to check opndx->type? */
	    return( idata_nofixup( CodeInfo, CurrOpnd, opndx ) );
	} else {
	    /* allow "lea <reg>, [offset <sym>]" */
	    if( CodeInfo->token == T_LEA && opndx->instr == T_OFFSET )
		return( memory_operand( CodeInfo, CurrOpnd, opndx, TRUE ) );
	    return( idata_fixup( CodeInfo, CurrOpnd, opndx ) );
	}
    } else if( opndx->sym == NULL ) { /* direct operand without symbol */
	if( opndx->override != NULL ) {
	    /* direct absolute memory without symbol.
	     DS:[0] won't create a fixup, but
	     DGROUP:[0] will create one! */
	    /* for 64bit, always create a fixup, since RIP-relative addressing is used
	     * v2.11: don't create fixup in 64-bit.
	     */
	    if ( opndx->override->token == T_REG || CodeInfo->Ofssize == USE64 )
		return( memory_operand( CodeInfo, CurrOpnd, opndx, FALSE ) );
	    else
		return( memory_operand( CodeInfo, CurrOpnd, opndx, TRUE ) );
	} else {
	    return( idata_nofixup( CodeInfo, CurrOpnd, opndx ) );
	}
    } else if( ( opndx->sym->state == SYM_UNDEFINED ) && !opndx->explicit ) {
	/* undefined symbol, it's not possible to determine
	 * operand type and size currently. However, for backpatching
	 * a fixup should be created.
	 */
	/* assume a code label for branch instructions! */
	if( IS_ANY_BRANCH( CodeInfo->token ) )
	    return( process_branch( CodeInfo, CurrOpnd, opndx ) );

	switch( CodeInfo->token ) {
	case T_PUSH:
	case T_PUSHW:
	case T_PUSHD:
	    /* v2.0: don't assume immediate operand if cpu is 8086 */
	    if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) > P_86 ) {
		return( idata_fixup( CodeInfo, CurrOpnd, opndx ) );
	    }
	    break;
	default:
	    /* v2.04: if operand is the second argument (and the first is NOT
	     * a segment register!), scan the
	     * instruction table if the instruction allows an immediate!
	     * If so, assume the undefined symbol is a constant.
	     */
	    if ( CurrOpnd == OPND2 && (( CodeInfo->opnd[OPND1].type & OP_SR ) == 0 ) ) {
		const struct instr_item	 *p = CodeInfo->pinstr;
		do {
		    if ( opnd_clstab[p->opclsidx].opnd_type[OPND2] & OP_I ) {
			return( idata_fixup( CodeInfo, CurrOpnd, opndx ) );
		    }
		    p++;
		} while ( p->first == FALSE );
	    }
	    /* v2.10: if current operand is the third argument, always assume an immediate */
	    if ( CurrOpnd == OPND3 )
		return( idata_fixup( CodeInfo, CurrOpnd, opndx ) );
	}
	/* do default processing */

    } else if( ( opndx->sym->state == SYM_SEG ) ||
	       ( opndx->sym->state == SYM_GRP ) ) {
	/* SEGMENT and GROUP symbol is converted to SEG symbol
	 * for next processing */
	opndx->instr = T_SEG;
	return( idata_fixup( CodeInfo, CurrOpnd, opndx ) );
    } else {
	/* symbol external, but absolute? */
	if( opndx->is_abs ) {
	    return( idata_fixup( CodeInfo, CurrOpnd, opndx ) );
	}

	/* CODE location is converted to OFFSET symbol */
	if ( opndx->mem_type == MT_NEAR || opndx->mem_type == MT_FAR ) {
	    if( CodeInfo->token == T_LEA ) {
		return( memory_operand( CodeInfo, CurrOpnd, opndx, TRUE ) );
	    } else if( opndx->mbr != NULL ) { /* structure field? */
		return( memory_operand( CodeInfo, CurrOpnd, opndx, TRUE ) );
	    } else {
		return( idata_fixup( CodeInfo, CurrOpnd, opndx ) );
	    }
	}
    }
    /* default processing: memory with fixup */
    return( memory_operand( CodeInfo, CurrOpnd, opndx, TRUE ) );
}

/* Handle constant operands.
 * These never need a fixup. Externals - even "absolute" ones -
 * are always labeled as EXPR_ADDR by the expression evaluator.
 */
static int process_const( struct code_info *CodeInfo, unsigned CurrOpnd, struct expr *opndx )
/************************************************************************************************/
{
    /* v2.11: don't accept an empty string */
    if ( opndx->quoted_string && opndx->quoted_string->stringlen == 0 )
	return( asmerr( 2047 ) );

    /* optimization: skip <value> if it is 0 and instruction
     * is RET[W|D|N|F]. */
    /* v2.06: moved here and checked the opcode directly, so
     * RETD and RETW are also handled. */
    if ( ( ( CodeInfo->pinstr->opcode & 0xf7 ) == 0xc2 ) &&
	CurrOpnd == OPND1 && opndx->value == 0 ) {
	return( NOT_ERROR );
    }
    return( idata_nofixup( CodeInfo, CurrOpnd, opndx ) );
}

static int process_register( struct code_info *CodeInfo, unsigned CurrOpnd, const struct expr opndx[] )
/**********************************************************************************************************/
/*
 * parse and encode direct register operands. Modifies:
 * - CodeInfo->opnd_type
 * - CodeInfo->rm_byte (depending on CurrOpnd)
 * - CodeInfo->iswide
 * - CodeInfo->x86hi_used/x64lo_used
 * - CodeInfo->prefix.rex
 */
{
    enum special_token regtok;
    int	 regno;
    uint_32 flags;

    regtok = opndx[CurrOpnd].base_reg->tokval;
    regno = GetRegNo( regtok );
    /* the register's "OP-flags" are stored in the 'value' field */
    flags = GetValueSp( regtok );
    CodeInfo->opnd[CurrOpnd].type = flags;
    if ( flags & OP_R8 ) {
	/* it's probably better to not reset the wide bit at all */
	if ( flags != OP_CL )	   /* problem: SHL AX|AL, CL */
	    CodeInfo->iswide = 0;

	if ( CodeInfo->Ofssize == USE64 && regno >=4 && regno <=7 )
	    if ( SpecialTable[regtok].cpu == P_86 )
		CodeInfo->x86hi_used = 1; /* it's AH,BH,CH,DH */
	    else
		CodeInfo->x64lo_used = 1; /* it's SPL,BPL,SIL,DIL */
	if ( StdAssumeTable[regno].error & (( regtok >= T_AH && regtok <= T_BH ) ? RH_ERROR : RL_ERROR ) ) {
	    return( asmerr(2108) );
	}
    } else if ( flags & OP_R ) { /* 16-, 32- or 64-bit GPR? */
	CodeInfo->iswide = 1;
	if ( StdAssumeTable[regno].error & flags & OP_R ) {
	    return( asmerr(2108) );
	}
	if ( flags & OP_R16 ) {
	    if ( CodeInfo->Ofssize > USE16 )
		CodeInfo->prefix.opsiz = TRUE;
	} else {
	    if( CodeInfo->Ofssize == USE16 )
		CodeInfo->prefix.opsiz = TRUE;
	}
    } else if ( flags & OP_SR ) {
	if( regno == 1 ) { /* 1 is CS */
	    /* POP CS is not allowed */
	    if( CodeInfo->token == T_POP ) {
		return( asmerr( 2008,"POP CS") );
	    }
	}
    } else if ( flags & OP_ST ) {

	regno = opndx[CurrOpnd].st_idx;
	if ( regno > 7 ) { /* v1.96: index check added */
	    return( asmerr( 2032 ) );
	}
	CodeInfo->rm_byte |= regno;
	if( regno != 0 )
	    CodeInfo->opnd[CurrOpnd].type = OP_ST_REG;
	/* v2.06: exit, rm_byte is already set. */
	return( NOT_ERROR );

    } else if ( flags & OP_RSPEC ) { /* CRx, DRx, TRx */
	if( CodeInfo->token != T_MOV ) {
	    if ( CodeInfo->token == T_PUSH )
		return( asmerr( 2151 ) );
	    return( asmerr( 2070 ) );//2032 ) );
	}
	/* v2.04: previously there were 3 flags, OP_CR, OP_DR and OP_TR.
	 * this was summoned to one flag OP_RSPEC to free 2 flags, which
	 * are needed if AVC ( new YMM registers ) is to be supported.
	 * To distinguish between CR, DR and TR, the register number is
	 * used now: CRx are numbers 0-F, DRx are numbers 0x10-0x1F and
	 * TRx are 0x20-0x2F.
	 */
	if ( regno >= 0x20 ) { /* TRx? */
	    CodeInfo->opc_or |= 0x04;
	    /* TR3-TR5 are available on 486-586
	     * TR6+TR7 are available on 386-586
	     * v2.11: simplified.
	     */
	    if( ( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_686 ) {
		return( asmerr( 3004, regno > 0x25 ? 6 : 3, regno > 0x25 ? 7 : 5 ) );
	    }
	} else if ( regno >= 0x10 ) { /* DRx? */
	    CodeInfo->opc_or |= 0x01;
	}
	regno &= 0x0F;
    }

    /* if it's a x86-64 register (SIL, R8W, R8D, RSI, ... */
    if ( ( SpecialTable[regtok].cpu & P_CPU_MASK ) == P_64 ) {
	CodeInfo->prefix.rex |= 0x40;
	if ( flags & OP_R64 )
	    CodeInfo->prefix.rex |= REX_W;
    }

    if( CurrOpnd == OPND1 ) {
	/* the first operand
	 * r/m is treated as a 'reg' field */
	CodeInfo->rm_byte |= MOD_11;
	CodeInfo->prefix.rex |= (regno & 8 ) >> 3; /* set REX_B */
	regno &= BIT_012;
	/* fill the r/m field */
	CodeInfo->rm_byte |= regno;
    } else {
	/* the second operand
	 * XCHG can use short form if op1 is AX/EAX/RAX */
	if( ( CodeInfo->token == T_XCHG ) && ( CodeInfo->opnd[OPND1].type & OP_A ) &&
	     ( 0 == (CodeInfo->opnd[OPND1].type & OP_R8 ) ) ) {
	    CodeInfo->prefix.rex |= (regno & 8 ) >> 3; /* set REX_B */
	    regno &= BIT_012;
	    CodeInfo->rm_byte = ( CodeInfo->rm_byte & BIT_67 ) | regno;
	} else {
	    /* fill reg field with reg */
	    CodeInfo->prefix.rex |= (regno & 8 ) >> 1; /* set REX_R */
	    regno &= BIT_012;
	    CodeInfo->rm_byte = ( CodeInfo->rm_byte & ~BIT_345 ) | ( regno << 3 );
	}
    }
    return( NOT_ERROR );
}


/* special handling for string instructions
 * CMPS[B|W|D|Q]
 *  INS[B|W|D]
 * LODS[B|W|D|Q]
 * MOVS[B|W|D|Q]
 * OUTS[B|W|D]
 * SCAS[B|W|D|Q]
 * STOS[B|W|D|Q]
 * the peculiarity is that these instructions ( optionally )
 * have memory operands, which aren't used for code generation
 * <opndx> contains the last operand.
 */

static void HandleStringInstructions( struct code_info *CodeInfo, const struct expr opndx[] )
/*******************************************************************************************/
{
    int opndidx = OPND1;
    int op_size;

    switch( CodeInfo->token ) {
    case T_VCMPSD:
    case T_CMPSD:
	/* filter SSE2 opcode CMPSD */
	if ( CodeInfo->opnd[OPND1].type & (OP_XMM | OP_MMX)) {
	    /* v2.01: QWORD operand for CMPSD/MOVSD may have set REX_W! */
	    CodeInfo->prefix.rex &= ~REX_W;
	    return;
	}
	/* fall through */
    case T_CMPS:
    case T_CMPSB:
    case T_CMPSW:
    case T_CMPSQ:
	 /* cmps allows prefix for the first operand (=source) only */
	if ( CodeInfo->prefix.RegOverride != EMPTY ) {
	    if ( opndx[OPND2].override != NULL ) {
		if ( CodeInfo->prefix.RegOverride == ASSUME_ES ) {
		    /* content of LastRegOverride is valid if
		     * CodeInfo->RegOverride is != EMPTY.
		     */
		    if ( LastRegOverride == ASSUME_DS )
			CodeInfo->prefix.RegOverride = EMPTY;
		    else
			CodeInfo->prefix.RegOverride = LastRegOverride;
		} else {
		    asmerr( 2070 );
		}
	    } else if ( CodeInfo->prefix.RegOverride == ASSUME_DS ) {
		/* prefix for first operand? */
		CodeInfo->prefix.RegOverride = EMPTY;
	    }
	}
	break;
    case T_VMOVSD:
    case T_MOVSD:
	/* filter SSE2 opcode MOVSD */
	if ( ( CodeInfo->opnd[OPND1].type & (OP_XMM | OP_MMX) ) ||
	    ( CodeInfo->opnd[OPND2].type & (OP_XMM | OP_MMX) ) ) {
	    /* v2.01: QWORD operand for CMPSD/MOVSD may have set REX_W! */
	    CodeInfo->prefix.rex &= ~REX_W;
	    return;
	}
	/* fall through */
    case T_MOVS:
    case T_MOVSB:
    case T_MOVSW:
    case T_MOVSQ:
	/* movs allows prefix for the second operand (=source) only */
	if ( CodeInfo->prefix.RegOverride != EMPTY )
	    if ( opndx[OPND2].override == NULL )
		asmerr( 2070 );
	    else if ( CodeInfo->prefix.RegOverride == ASSUME_DS )
		CodeInfo->prefix.RegOverride = EMPTY;
	break;
    case T_OUTS:
    case T_OUTSB:
    case T_OUTSW:
    case T_OUTSD:
	/* v2.01: remove default DS prefix */
	if ( CodeInfo->prefix.RegOverride == ASSUME_DS )
	    CodeInfo->prefix.RegOverride = EMPTY;
	opndidx = OPND2;
	break;
    case T_LODS:
    case T_LODSB:
    case T_LODSW:
    case T_LODSD:
    case T_LODSQ:
	/* v2.10: remove unnecessary DS prefix ( Masm-compatible ) */
	if ( CodeInfo->prefix.RegOverride == ASSUME_DS )
	    CodeInfo->prefix.RegOverride = EMPTY;
	break;
    default: /*INS[B|W|D], SCAS[B|W|D|Q], STOS[B|W|D|Q] */
	/* INSx, SCASx and STOSx don't allow any segment prefix != ES
	 for the memory operand.
	 */
	if ( CodeInfo->prefix.RegOverride != EMPTY )
	    if ( CodeInfo->prefix.RegOverride == ASSUME_ES )
		CodeInfo->prefix.RegOverride = EMPTY;
	    else
		asmerr( 2070 );
    }

    if ( opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type[opndidx] == OP_NONE ) {
	CodeInfo->iswide = 0;
	CodeInfo->prefix.opsiz = FALSE;
    }

    /* if the instruction is the variant without suffix (MOVS, LODS, ..),
     * then use the operand's size to get further info.
     */
    if ( opnd_clstab[CodeInfo->pinstr->opclsidx].opnd_type[opndidx] != OP_NONE &&
	CodeInfo->opnd[opndidx].type != OP_NONE ) {
	op_size = OperandSize( CodeInfo->opnd[opndidx].type, CodeInfo );
	/* v2.06: added. if memory operand has no size */
	if ( op_size == 0 ) {
	    if ( CodeInfo->opnd[opndidx].InsFixup == NULL || CodeInfo->opnd[opndidx].InsFixup->sym->state != SYM_UNDEFINED )
		asmerr( 2023 );
	    op_size = 1; /* assume shortest format */
	}
	switch( op_size ) {
	case 1:
	    CodeInfo->iswide = 0;
	    CodeInfo->prefix.opsiz = FALSE;
	    break;
	case 2:
	    CodeInfo->iswide = 1;
	    CodeInfo->prefix.opsiz = CodeInfo->Ofssize ? TRUE : FALSE;
	    break;
	case 4:
	    CodeInfo->iswide = 1;
	    CodeInfo->prefix.opsiz = CodeInfo->Ofssize ? FALSE : TRUE;
	    break;
	case 8:
	    if ( CodeInfo->Ofssize == USE64 ) {
		CodeInfo->iswide = 1;
		CodeInfo->prefix.opsiz = FALSE;
		CodeInfo->prefix.rex = REX_W;
	    }
	    break;
	}
    }
    return;
}

static int check_size( struct code_info *CodeInfo, const struct expr opndx[] )
/*********************************************************************************/
/*
 * - use to make sure the size of first operand match the size of second operand;
 * - optimize MOV instruction;
 * - opndx contains last operand
 * todo: BOUND second operand check ( may be WORD/DWORD or DWORD/QWORD ).
 * tofix: add a flag in instr_table[] if there's NO check to be done.
 */
{
    enum operand_type op1 = CodeInfo->opnd[OPND1].type;
    enum operand_type op2 = CodeInfo->opnd[OPND2].type;
    ret_code	rc = NOT_ERROR;
    int		op1_size;
    int		op2_size;

    switch( CodeInfo->token ) {
    case T_IN:
	if( op2 == OP_DX ) {
	    /* wide and size is NOT determined by DX, but
	     * by the first operand, AL|AX|EAX
	     */
	    switch( op1 ) {
	    case OP_AX:
		break;
	    case OP_AL:
		CodeInfo->iswide = 0;	      /* clear w-bit */
	    case OP_EAX:
		if( CodeInfo->Ofssize ) {
		    CodeInfo->prefix.opsiz = FALSE;
		}
		break;
	    }
	}
	break;
    case T_OUT:
	if( op1 == OP_DX ) {
	    switch( op2 ) {
	    case OP_AX:
		break;
	    case OP_AL:
		CodeInfo->iswide = 0;	      /* clear w-bit */
	    case OP_EAX:
		if( CodeInfo->Ofssize ) {
		    CodeInfo->prefix.opsiz = FALSE;
		}
	    }
	}
	break;
    case T_LEA:
	break;
    case T_RCL:
    case T_RCR:
    case T_ROL:
    case T_ROR:
    case T_SAL:
    case T_SAR:
    case T_SHL:
    case T_SHR:
	/* v2.11: added */
	if ( CodeInfo->opnd[OPND1].type == OP_M && CodeInfo->undef_sym == FALSE &&
	    ( opndx[OPND1].sym == NULL || opndx[OPND1].sym->state != SYM_UNDEFINED ) ) {
	    asmerr( 2023 );
	    rc = ERROR;
	    break;
	}
	/* v2.0: if second argument is a forward reference,
	 * change type to "immediate 1"
	 */
	if ( opndx[OPND2].kind == EXPR_ADDR &&
	    Parse_Pass == PASS_1 &&
	    opndx[OPND2].indirect == FALSE &&
	    opndx[OPND2].sym &&
	    opndx[OPND2].sym->state == SYM_UNDEFINED ) {
	    CodeInfo->opnd[OPND2].type = OP_I8;
	    CodeInfo->opnd[OPND2].data32l = 1;
	}
	/* v2.06: added (because if first operand is memory, wide bit
	 * isn't set!)
	 */
	if ( OperandSize( op1, CodeInfo ) > 1 )
	    CodeInfo->iswide = 1;
	/* v2.06: makes the OP_CL_ONLY case in codegen.c obsolete */
	if ( op2 == OP_CL ) {
	    /* CL is encoded in bit 345 of rm_byte, but we don't need it
	     * so clear it here */
	    CodeInfo->rm_byte &= NOT_BIT_345;
	}
	break;
    case T_LDS:
    case T_LES:
    case T_LFS:
    case T_LGS:
    case T_LSS:
	op1_size = OperandSize( op1, CodeInfo ) + 2; /* add 2 for the impl. segment register */
	op2_size = OperandSize( op2, CodeInfo );
	if ( op2_size != 0 && op1_size != op2_size ) {
	    return( asmerr( 2024 ) );
	}
	break;
    case T_ENTER:
	break;
    case T_MOVSX:
    case T_MOVZX:
	CodeInfo->iswide = 0;
	op1_size = OperandSize( op1, CodeInfo );
	op2_size = OperandSize( op2, CodeInfo );
	if ( op2_size == 0 && Parse_Pass == PASS_2 )
	    if ( op1_size == 2 ) {
		asmerr( 8019, "BYTE" );
	    } else
		asmerr( 2023 );
	switch( op1_size ) {
	case 8:
	case 4:
	    if (op2_size < 2)
		;
	    else if (op2_size == 2)
		CodeInfo->iswide = 1;
	    else {
		asmerr( 2024 );
		rc = ERROR;
	    }
	    CodeInfo->prefix.opsiz = CodeInfo->Ofssize ? FALSE : TRUE;
	    break;
	case 2:
	    if( op2_size >= 2 ) {
		asmerr( 2024 );
		rc = ERROR;
	    }
	    CodeInfo->prefix.opsiz = CodeInfo->Ofssize ? TRUE : FALSE;
	    break;
	default:
	    /* op1 must be r16/r32/r64 */
	    asmerr( 2024 );
	    rc = ERROR;
	}
	break;
    case T_MOVSXD:
	break;
    case T_ARPL: /* v2.06: new, avoids the OP_R16 hack in codegen.c */
	CodeInfo->prefix.opsiz = 0;
	goto def_check;
	break;
    case T_LAR: /* v2.04: added */
    case T_LSL: /* 19-sep-93 */
	if ( ModuleInfo.Ofssize != USE64 || ( ( op2 & OP_M ) == 0 ) )
	    goto def_check;
	/* in 64-bit, if second argument is memory operand,
	 * ensure it has size WORD ( or 0 if a forward ref )
	 */
	op2_size = OperandSize( op2, CodeInfo );
	if ( op2_size != 2 && op2_size != 0 ) {
	    return( asmerr( 2024 ) );
	}
	/* the opsize prefix depends on the FIRST operand only! */
	op1_size = OperandSize( op1, CodeInfo );
	if ( op1_size != 2 )
	    CodeInfo->prefix.opsiz = FALSE;
	break;
    case T_IMUL: /* v2.06: check for 3rd operand must be done here */
	if ( CodeInfo->opnd[OPND3].type != OP_NONE ) {
	    int op3_size;
	    op1_size = OperandSize( op1, CodeInfo );
	    op3_size = OperandSize( CodeInfo->opnd[OPND3].type, CodeInfo );
	    /* the only case which must be checked here
	     * is a WORD register as op1 and a DWORD immediate as op3 */
	    if ( op1_size == 2 && op3_size > 2 ) {
		asmerr( 2022, op1_size, op3_size );
		rc = ERROR;
		break;
	    }
	    if ( CodeInfo->opnd[OPND3].type & ( OP_I16 | OP_I32 ) )
		CodeInfo->opnd[OPND3].type = ( op1_size == 2 ? OP_I16 : OP_I32 );
	}
	goto def_check;
	break;
    case T_CVTSD2SI:
    case T_CVTTSD2SI:
    case T_CVTSS2SI:
    case T_CVTTSS2SI:
    case T_VBROADCASTSD:
    case T_VBROADCASTF128:
    case T_VEXTRACTF128:
    case T_VINSERTF128:
    case T_VCVTSD2SI:
    case T_VCVTTSD2SI:
    case T_VCVTSS2SI:
    case T_VCVTTSS2SI:
    case T_INVEPT:
    case T_INVVPID:
	break;
    case T_VCVTPD2DQ:
    case T_VCVTTPD2DQ:
    case T_VCVTPD2PS:
	if ( op2 == OP_M && opndx[OPND2].indirect ) {
	    return( asmerr( 2023 ) );
	}
	break;
    case T_VMOVDDUP:
	if ( !( op1 & OP_YMM ) )
	    break;
	/* fall through */
    case T_VPERM2F128: /* has just one memory variant, and VX_L isnt set */
	if ( op2 == OP_M )
	    CodeInfo->opnd[OPND2].type |= OP_M256;
	break;
    case T_CRC32:
	/* v2.02: for CRC32, the second operand determines whether an
	 * OPSIZE prefix byte is to be written.
	 */
	op2_size = OperandSize( op2, CodeInfo );
	if ( op2_size < 2)
	    CodeInfo->prefix.opsiz = FALSE;
	else if ( op2_size == 2 )
	    CodeInfo->prefix.opsiz = CodeInfo->Ofssize ? TRUE : FALSE;
	else
	    CodeInfo->prefix.opsiz = CodeInfo->Ofssize ? FALSE : TRUE;
	break;
    case T_MOVD:
	break;
    case T_MOV:
	if( op1 & OP_SR ) { /* segment register as op1? */
	    op2_size = OperandSize( op2, CodeInfo );
	    if( ( op2_size == 2 ) || ( op2_size == 4 )
	       || ( op2_size == 8 && ModuleInfo.Ofssize == USE64 )) {
		return( NOT_ERROR );
	    }
	} else if( op2 & OP_SR ) {
	    op1_size = OperandSize( op1, CodeInfo );
	    if( ( op1_size == 2 ) || ( op1_size == 4 )
	       || ( op1_size == 8 && ModuleInfo.Ofssize == USE64 )) {
		return( NOT_ERROR );
	    }
	} else if( ( op1 & OP_M ) && ( op2 & OP_A ) ) { /* 1. operand memory reference, 2. AL|AX|EAX|RAX? */

	    if ( CodeInfo->isdirect == FALSE ) {
		/* address mode is indirect.
		 * don't use the short format (opcodes A0-A3) - it exists for direct
		 * addressing only. Reset OP_A flag!
		 */
		CodeInfo->opnd[OPND2].type &= ~OP_A;
	    } else if ( CodeInfo->Ofssize == USE64 && ( CodeInfo->opnd[OPND1].data64 < 0x80000000 || CodeInfo->opnd[OPND1].data64 >= 0xffffffff80000000 ) ) {
		/* for 64bit, opcodes A0-A3 ( direct memory addressing with AL/AX/EAX/RAX )
		 * are followed by a full 64-bit moffs. This is only used if the offset won't fit
		 * in a 32-bit signed value.
		 */
		CodeInfo->opnd[OPND2].type &= ~OP_A;
	    }

	} else if( ( op1 & OP_A ) && ( op2 & OP_M ) ) { /* 2. operand memory reference, 1. AL|AX|EAX|RAX? */

	    if ( CodeInfo->isdirect == FALSE ) {
		CodeInfo->opnd[OPND1].type &= ~OP_A;
	    } else if ( CodeInfo->Ofssize == USE64 && ( CodeInfo->opnd[OPND2].data64 < 0x80000000 || CodeInfo->opnd[OPND2].data64 >= 0xffffffff80000000 ) ) {
		CodeInfo->opnd[OPND1].type &= ~OP_A;
	    }
	}
	/* fall through */
    default:
    def_check:
	/* make sure the 2 opnds are of the same type */
	op1_size = OperandSize( op1, CodeInfo );
	op2_size = OperandSize( op2, CodeInfo );
	if( op1_size > op2_size ) {
	    if( ( op2 >= OP_I8 ) && ( op2 <= OP_I32 ) ) {     /* immediate */
		op2_size = op1_size;	/* promote to larger size */
	    }
	}
	/* v2.04: check in idata_nofixup was signed,
	 * so now add -256 - -129 and 128-255 to acceptable byte range.
	 * Since Masm v8, the check is more restrictive, -255 - -129
	 * is no longer accepted.
	 */
	if( ( op1_size == 1 ) && ( op2 == OP_I16 ) &&
	    ( CodeInfo->opnd[OPND2].data32l <= UCHAR_MAX ) &&
	    ( CodeInfo->opnd[OPND2].data32l >= -255 ) ) {
	    return( rc ); /* OK cause no sign extension */
	}
	if( op1_size != op2_size ) {
	    /* if one or more are !defined, set them appropriately */
	    if( ( op1 | op2 ) & ( OP_MMX | OP_XMM | OP_YMM ) ) {
	    } else if( ( op1_size != 0 ) && ( op2_size != 0 ) ) {
		//asmerr( 2022, op1_size, op2_size );
		rc = asmerr( 2022, op1_size, op2_size );//ERROR;
	    }
	    /* size == 0 is assumed to mean "undefined", but there
	     * is also the case of an "empty" struct or union. The
	     * latter case isn't handled correctly.
	     */
	    if( op1_size == 0 ) {
		if( ( op1 & OP_M_ANY ) && ( op2 & OP_I ) ) {
		    char *p = "WORD";
		    if( (uint_32)CodeInfo->opnd[OPND2].data32l > USHRT_MAX || op2_size == 4 ) {
			CodeInfo->iswide = 1;
			if ( ModuleInfo.Ofssize == USE16 && op2_size > 2 && InWordRange( CodeInfo->opnd[OPND2].data32l ) )
			    op2_size = 2;
			if (op2_size <= 2 && CodeInfo->opnd[OPND2].data32l > SHRT_MIN && ModuleInfo.Ofssize == USE16 ) {
			    CodeInfo->mem_type = MT_WORD;
			    CodeInfo->opnd[OPND2].type = OP_I16;
			} else {
			    CodeInfo->mem_type = MT_DWORD;
			    CodeInfo->opnd[OPND2].type = OP_I32;
			    p = "DWORD";
			}
		    } else if( (uint_32)CodeInfo->opnd[OPND2].data32l > UCHAR_MAX || op2_size == 2 ) {
			 CodeInfo->mem_type = MT_WORD;
			 CodeInfo->iswide = 1;
			 CodeInfo->opnd[OPND2].type = OP_I16;
		    } else {
			 CodeInfo->mem_type = MT_BYTE;
			 CodeInfo->opnd[OPND2].type = OP_I8;
			 p = "BYTE";
		    }
		    if( opndx[OPND2].explicit == FALSE ) {
			/* v2.06: emit warning at pass one if mem op isn't a forward ref */
			/* v2.06b: added "undefined" check */
			if ( ( CodeInfo->opnd[OPND1].InsFixup == NULL && Parse_Pass == PASS_1 && CodeInfo->undef_sym == FALSE ) ||
			    ( CodeInfo->opnd[OPND1].InsFixup && Parse_Pass == PASS_2 ) )
				asmerr( 8019, p );
		    }
		} else if( ( op1 & OP_M_ANY ) && ( op2 & ( OP_R | OP_SR ) ) ) {
		} else if( ( op1 & ( OP_MMX | OP_XMM ) ) && ( op2 & OP_I ) ) {
		    if( (uint_32)CodeInfo->opnd[OPND2].data32l > USHRT_MAX ) {
			 CodeInfo->opnd[OPND2].type = OP_I32;
		    } else if( (uint_32)CodeInfo->opnd[OPND2].data32l > UCHAR_MAX ) {
			 CodeInfo->opnd[OPND2].type = OP_I16;
		    } else {
			 CodeInfo->opnd[OPND2].type = OP_I8;
		    }
		} else if( ( op1 | op2 ) & ( OP_MMX | OP_XMM ) ) {
		} else {
		    switch( op2_size ) {
		    case 1:
			CodeInfo->mem_type = MT_BYTE;
			if( ( Parse_Pass == PASS_1 ) && ( op2 & OP_I ) ) {
			    asmerr( 8019, "BYTE" );
			}
			break;
		    case 2:
			CodeInfo->mem_type = MT_WORD;
			CodeInfo->iswide = 1;
			if( ( Parse_Pass == PASS_1 ) && ( op2 & OP_I ) ) {
			    asmerr( 8019, "WORD" );
			}
			if( CodeInfo->Ofssize )
			    CodeInfo->prefix.opsiz = TRUE;
			break;
		    case 4:
			CodeInfo->mem_type = MT_DWORD;
			CodeInfo->iswide = 1;
			if( ( Parse_Pass == PASS_1 ) && ( op2 & OP_I ) ) {
			    asmerr( 8019, "DWORD" );
			}
			break;
		    }
		}
	    }
	}
    }
    return( rc );
}

static struct asym *IsType( const char *name )
/********************************************/
{
    struct asym *sym;

    sym = SymSearch( name );
    if ( sym && (sym->state == SYM_TYPE ) )
	return( sym );
    return( NULL );
}

/*
 * ParseLine() is the main parser function.
 * It scans the tokens in tokenarray[] and does:
 * - for code labels: call CreateLabel()
 * - for data items and data directives: call data_dir()
 * - for other directives: call directive[]()
 * - for instructions: fill CodeInfo and call codegen()
 */

int LabelMacro( struct asm_tok tokenarray[] )
{
    if (Token_Count > 2 && tokenarray[0].token == T_ID &&
       (tokenarray[1].token == T_COLON || tokenarray[1].token == T_DBL_COLON)) {
	if (tokenarray[2].token != T_FINAL) {
	    return 1;
	}
    }
    return 0;
}

int ParseLine( struct asm_tok tokenarray[] )
/**********************************************/
{
    int			i;
    int			j;
    int			q;
    char *		p;
    char *		b;
    unsigned		dirflags;
    unsigned		CurrOpnd;
    ret_code		temp;
    struct asym		*sym;
    uint_32		oldofs;
    struct code_info	CodeInfo;
    struct expr		opndx[MAX_OPND+1];
    char		buffer[MAX_LINE_LEN];
    char		hllbuf[MAX_LINE_LEN];

    i = 0;
    j = 0;

    if (Token_Count > 2 && tokenarray[0].token == T_ID &&
       (tokenarray[1].token == T_COLON || tokenarray[1].token == T_DBL_COLON)) {

	if (tokenarray[2].token != T_FINAL)
	    j++;
    }

    if ( j ) {

	/* break label: macro/hll lines */
	strcpy( buffer, tokenarray[2].tokpos );
	strcpy( CurrSource, tokenarray[0].string_ptr );
	strcat( CurrSource, tokenarray[1].string_ptr );
	Token_Count = Tokenize( CurrSource, 0, tokenarray, TOK_DEFAULT );
	if ( ERROR == ParseLine( tokenarray ) )
	    return ERROR;

	/* parse macro or hll function */
	strcpy(CurrSource, buffer);
	Token_Count = Tokenize(CurrSource, 0, tokenarray, TOK_DEFAULT);
	i = ExpandLine(CurrSource, tokenarray);
	if (i == EMPTY)
	    return EMPTY;
	else if (i == ERROR)
	    return ERROR;
	i = 0;
	/* case label: */
    } else if ( tokenarray[0].token == T_ID && ( tokenarray[1].token == T_COLON || tokenarray[1].token == T_DBL_COLON ) ) {
	i = 2;
	if( ProcStatus & PRST_PROLOGUE_NOT_DONE ) write_prologue( tokenarray );

	/* create a global or local code label */
	if( CreateLabel( tokenarray[0].string_ptr, MT_NEAR, NULL,
			( ModuleInfo.scoped && CurrProc && tokenarray[1].token != T_DBL_COLON ) ) == NULL ) {
	    return( ERROR );
	}
	if ( tokenarray[i].token == T_FINAL ) {
	    /* v2.06: this is a bit too late. Should be done BEFORE
	     * CreateLabel, because of '@@'. There's a flag supposed to
	     * be used for this handling, LOF_STORED in line_flags.
	     * It's only a problem if a '@@:' is the first line
	     * in the code section.
	     * v2.10: is no longer an issue because the label counter has
	     * been moved to module_vars (see global.h).
	     */
	    FStoreLine(0);
	    if ( CurrFile[LST] ) {
		LstWrite( LSTTYPE_LABEL, 0, NULL );
	    }
	    return( NOT_ERROR );
	}
    }

    /* handle directives and (anonymous) data items */

    if ( tokenarray[i].token != T_INSTRUCTION ) {
	/* a code label before a data item is only accepted in Masm5 compat mode */
	Frame_Type = FRAME_NONE;
	SegOverride = NULL;
	if ( i == 0 && tokenarray[0].token == T_ID ) {
	    /* token at pos 0 may be a label.
	     * it IS a label if:
	     * 1. token at pos 1 is a directive (lbl dd ...)
	     * 2. token at pos 0 is NOT a userdef type ( lbl DWORD ...)
	     * 3. inside a struct and token at pos 1 is a userdef type
	     *	  or a predefined type. (usertype DWORD|usertype ... )
	     *	  the separate namespace allows this syntax here.
	     */
	    if( tokenarray[1].token == T_DIRECTIVE )
		i++;
	    else {
		sym = IsType( tokenarray[0].string_ptr );
		if ( sym == NULL )
		    i++;
		else if ( CurrStruct &&
			 ( ( tokenarray[1].token == T_STYPE ) ||
			  ( tokenarray[1].token == T_ID && ( IsType( tokenarray[1].string_ptr ) ) ) ) )
		    i++;
	    }
	}
	switch ( tokenarray[i].token ) {
	case T_DIRECTIVE:
	    if ( tokenarray[i].dirtype == DRT_DATADIR ) {
		return( data_dir( i, tokenarray, NULL ) );
	    }
	    dirflags = GetValueSp( tokenarray[i].tokval );
	    if( CurrStruct && ( dirflags & DF_NOSTRUC ) ) {
		return( asmerr( 2037 ) );
	    }
	    /* label allowed for directive? */
	    if ( dirflags & DF_LABEL ) {
		if ( i && tokenarray[0].token != T_ID ) {
		    return( asmerr(2008, tokenarray[0].string_ptr ) );
		}
	    } else if ( i && tokenarray[i-1].token != T_COLON && tokenarray[i-1].token != T_DBL_COLON ) {
		return( asmerr(2008, tokenarray[i-1].string_ptr ) );
	    }
	    /* must be done BEFORE FStoreLine()! */
	    if( ( ProcStatus & PRST_PROLOGUE_NOT_DONE ) && ( dirflags & DF_PROC ) ) write_prologue( tokenarray );
	    if ( StoreState || ( dirflags & DF_STORE ) ) {
		/* v2.07: the comment must be stored as well
		 * if a listing (with -Sg) is to be written and
		 * the directive will generate lines
		 */
		if ( ( dirflags & DF_CGEN ) && ModuleInfo.CurrComment && ModuleInfo.list_generated_code ) {
		    FStoreLine(1);
		} else
		    FStoreLine(0);
	    }
	    if ( tokenarray[i].dirtype > DRT_DATADIR ) {
		temp = directive_tab[tokenarray[i].dirtype]( i, tokenarray );
	    } else {
		temp = ERROR;
		/* ENDM, EXITM and GOTO directives should never be seen here */
		switch( tokenarray[i].tokval ) {
		case T_ENDM:
		    asmerr( 1008 );
		    break;
		case T_EXITM:
		case T_GOTO:
		    asmerr( 2170 );
		    break;
		default:
		    /* this error may happen if
		     * CATSTR, SUBSTR, MACRO, ...
		     * aren't at pos 1
		     */
		    asmerr(2008, tokenarray[i].string_ptr );
		    break;
		}
	    }
	    /* v2.0: for generated code it's important that list file is
	     * written in ALL passes, to update file position! */
	    /* v2.08: UseSavedState == FALSE added */
	    if ( ModuleInfo.list && ( Parse_Pass == PASS_1 || ModuleInfo.GeneratedCode || UseSavedState == FALSE ) )
		LstWriteSrcLine();
	    return( temp );
	case T_STYPE:
	    return( data_dir( i, tokenarray, NULL ) );
	case T_ID:
	    if( sym = IsType( tokenarray[i].string_ptr ) ) {
		return( data_dir( i, tokenarray, sym ) );
	    }
	    break;
	default:
	    if ( tokenarray[i].token == T_COLON ) {
		return( asmerr( 2065, ":") );
	    }
	    break;
	} /* end switch (tokenarray[i].token) */
	if ( i && tokenarray[i-1].token == T_ID )
	    i--;

	if ( i == 0 && tokenarray[0].hll_flags & T_HLL_PROC && ( ModuleInfo.aflag & _AF_ON ) ) {
	    /*
	     * invoke handle import, call do not..
	     */
	    strcpy( buffer, "invoke " );
	    strcat( buffer, tokenarray[0].tokpos );
	    strcpy( CurrSource, buffer );
	    Token_Count = Tokenize( buffer, 0, tokenarray, TOK_DEFAULT );
	    return ParseLine( tokenarray );

	} else {
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}
    }

    if( CurrStruct ) {
	return( asmerr( 2037 ) );
    }

    if( ProcStatus & PRST_PROLOGUE_NOT_DONE )
	write_prologue( tokenarray );

    if ( CurrFile[LST] ) oldofs = GetCurrOffset();

    /* init CodeInfo */
    CodeInfo.prefix.ins		= EMPTY;
    CodeInfo.prefix.RegOverride = EMPTY;
    CodeInfo.prefix.rex	    = 0;
    CodeInfo.prefix.adrsiz  = FALSE;
    CodeInfo.prefix.opsiz   = FALSE;
    CodeInfo.mem_type	    = MT_EMPTY;
    for( j = 0; j < MAX_OPND; j++ ) {
	CodeInfo.opnd[j].type = OP_NONE;
    }
    CodeInfo.rm_byte	    = 0;
    CodeInfo.sib	    = 0;	    /* assume ss is *1 */
    CodeInfo.Ofssize	    = ModuleInfo.Ofssize;
    CodeInfo.opc_or	    = 0;
    CodeInfo.vexregop	    = 0;
    CodeInfo.flags	    = 0;

    /* instruction prefix?
     * T_LOCK, T_REP, T_REPE, T_REPNE, T_REPNZ, T_REPZ */
    if ( tokenarray[i].tokval >= T_LOCK && tokenarray[i].tokval <= T_REPZ ) {
	CodeInfo.prefix.ins = tokenarray[i].tokval;
	i++;
	/* prefix has to be followed by an instruction */
	if( tokenarray[i].token != T_INSTRUCTION ) {
	    return( asmerr( 2068 ) );
	}
    };

    if( CurrProc ) {
	switch( tokenarray[i].tokval ) {
	case T_RET:
	case T_IRET:  /* IRET is always 16-bit; OTOH, IRETW doesn't exist */
	case T_IRETD:
	case T_IRETQ:
	    if ( !( ProcStatus & PRST_INSIDE_EPILOGUE ) && ModuleInfo.epiloguemode != PEM_NONE ) {
		/* v2.07: special handling for RET/IRET */
		FStoreLine( ( ModuleInfo.CurrComment && ModuleInfo.list_generated_code ) ? 1 : 0 );
		ProcStatus |= PRST_INSIDE_EPILOGUE;
		temp = RetInstr( i, tokenarray, Token_Count );
		ProcStatus &= ~PRST_INSIDE_EPILOGUE;
		return( temp );
	    }
	    /* default translation: just RET to RETF if proc is far */
	    /* v2.08: this code must run even if PRST_INSIDE_EPILOGUE is set */
	    if ( tokenarray[i].tokval == T_RET && CurrProc->sym.mem_type == MT_FAR )
		tokenarray[i].tokval = T_RETF;
	}
    }

#if 1
    if ( ( ModuleInfo.aflag & _AF_ON ) && Parse_Pass == PASS_1 ) {

	for ( q = 1; tokenarray[q].token != T_FINAL; q++ ) {

	    if ( tokenarray[q].hll_flags & T_HLL_PROC ) {

		/* v2.21 - mov reg,proc(...) */

		if ( ExpandHllProc( buffer, q, tokenarray ) == ERROR)
		    return ERROR;

		if ( buffer[0] != 0 ) {

		    b = buffer;
		    strcpy( hllbuf, tokenarray[0].tokpos );
		    while ( b ) {
			p = b;
			if ( ( b = strchr( b, '\n' ) ) != NULL )
			    *b++ = 0;
			if ( *p ) {
			    strcpy( CurrSource, p );
			    Token_Count = Tokenize( CurrSource, 0,
				tokenarray, TOK_DEFAULT );
			    if ( ERROR == ParseLine( tokenarray ) )
				return ERROR;
			}
		    }
		    strcpy( CurrSource, hllbuf );
		    Token_Count = Tokenize( CurrSource, 0, tokenarray, TOK_DEFAULT );
		    return ParseLine( tokenarray );
		}
		break;
	    }
	}
    }
#endif
    FStoreLine(0); /* must be placed AFTER write_prologue() */

    CodeInfo.token = tokenarray[i].tokval;
    /* get the instruction's start position in InstrTable[] */
    CodeInfo.pinstr = &InstrTable[IndexFromToken( CodeInfo.token )];
    i++;

    if( CurrSeg == NULL ) {
	return( asmerr( 2034 ) );
    }
    if( CurrSeg->e.seginfo->segtype == SEGTYPE_UNDEF ) {
	CurrSeg->e.seginfo->segtype = SEGTYPE_CODE;
    }
    if ( ModuleInfo.CommentDataInCode )
	omf_OutSelect( FALSE );

    /* get the instruction's arguments.
     * This loop accepts up to 4 arguments if AVXSUPP is on */

    for ( j = 0; j < sizeof(opndx)/sizeof(opndx[0]) && tokenarray[i].token != T_FINAL; j++ ) {
	if ( j ) {
	    if ( tokenarray[i].token != T_COMMA )
		break;
	    i++;
	}
	if( EvalOperand( &i, tokenarray, Token_Count, &opndx[j], 0 ) == ERROR ) {
	    return( ERROR );
	}
	switch ( opndx[j].kind ) {
	case EXPR_FLOAT:
	    /* v2.06: accept float constants for PUSH */
	    if ( j == OPND2 || CodeInfo.token == T_PUSH || CodeInfo.token == T_PUSHD ) {
		if ( Options.strict_masm_compat == FALSE ) {
		    /* convert to REAL4, REAL8, or REAL16 */
		    int m = 4;
		    if ( opndx[j].mem_type == MT_REAL8 )
			m = 8;
#if defined(_ASMLIB_)
		    else if ( opndx[j].mem_type == MT_REAL16 )
			m = 16;
#endif
		    atofloat( &opndx[j].fvalue, opndx[j].float_tok->string_ptr,
			m, opndx[j].negative, opndx[j].float_tok->floattype );
		    opndx[j].kind = EXPR_CONST;
		    opndx[j].float_tok = NULL;
		    break;
		}
		/* Masm message is: real or BCD number not allowed */
		return( asmerr( 2050 ) );
	    }
	    /* fall through */
	case EXPR_EMPTY:
	    if ( i == Token_Count )
		i--;  /* v2.08: if there was a terminating comma, display it */
	    /* fall through */
	case EXPR_ERROR:
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}
    }
    if ( tokenarray[i].token != T_FINAL ) {
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }

    for ( CurrOpnd = 0; CurrOpnd < j && CurrOpnd < MAX_OPND; CurrOpnd++ ) {

	Frame_Type = FRAME_NONE;
	SegOverride = NULL; /* segreg prefix is stored in RegOverride */
	CodeInfo.opnd[CurrOpnd].data32l = 0;
	CodeInfo.opnd[CurrOpnd].InsFixup = NULL;

	/* if encoding is VEX and destination op is XMM, YMM or memory,
	 * the second argument may be stored in the vexregop field.
	 */
	if ( CodeInfo.token >= VEX_START &&
	    CurrOpnd == OPND2 &&
	    ( CodeInfo.opnd[OPND1].type & ( OP_XMM | OP_YMM | OP_M | OP_M256 ) ) ) {
	    if ( vex_flags[CodeInfo.token - VEX_START] & VX_NND )
		;
	    else if ( ( vex_flags[CodeInfo.token - VEX_START] & VX_IMM ) &&
		     ( opndx[OPND3].kind == EXPR_CONST ) && ( j > 2 ) )
		;
	    else if ( ( vex_flags[CodeInfo.token - VEX_START] & VX_NMEM ) &&
		     ( ( CodeInfo.opnd[OPND1].type & OP_M ) ||
		     /* v2.11: VMOVSD and VMOVSS always have 2 ops if a memory op is involved */
		     ( ( CodeInfo.token == T_VMOVSD || CodeInfo.token == T_VMOVSS ) && ( opndx[OPND2].kind != EXPR_REG || opndx[OPND2].indirect == TRUE ) ) )
		    )
		;
	    else {
		if ( opndx[OPND2].kind != EXPR_REG ||
		    ( ! ( GetValueSp( opndx[CurrOpnd].base_reg->tokval ) & ( OP_XMM | OP_YMM ) ) ) ) {
		    return( asmerr( 2070 ) );
		}
		/* fixme: check if there's an operand behind OPND2 at all!
		 * if no, there's no point to continue with switch (opndx[].kind).
		 * v2.11: additional check for j <= 2 added
		 */
		if ( j <= 2 ) {
		    /* v2.11: next line should be activated - currently the error is emitted below as syntax error */
		} else
		/* flag VX_DST is set if an immediate is expected as operand 3 */
		if ( ( vex_flags[CodeInfo.token - VEX_START] & VX_DST ) &&
		    ( opndx[OPND3].kind == EXPR_CONST ) ) {
		    if ( opndx[OPND1].base_reg ) {
			/* first operand register is moved to vexregop */
			/* handle VEX.NDD */
			CodeInfo.vexregop = opndx[OPND1].base_reg->bytval + 1;
			memcpy( &opndx[OPND1], &opndx[CurrOpnd], sizeof( opndx[0] ) * 3 );
			CodeInfo.rm_byte = 0;
			if ( process_register( &CodeInfo, OPND1, opndx ) == ERROR )
			    return( ERROR );
		    }
		} else {
		    unsigned flags = GetValueSp( opndx[CurrOpnd].base_reg->tokval );
		    /* v2.08: no error here if first op is an untyped memory reference
		     * note that OP_M includes OP_M128, but not OP_M256 (to be fixed?)
		     */
		    if ( CodeInfo.opnd[OPND1].type == OP_M )
			; else
		    if ( ( flags & ( OP_XMM | OP_M128 ) ) &&
			( CodeInfo.opnd[OPND1].type & (OP_YMM | OP_M256 ) ) ||
			( flags & ( OP_YMM | OP_M256 ) ) &&
			( CodeInfo.opnd[OPND1].type & (OP_XMM | OP_M128 ) ) ) {
			return( asmerr( 2070 ) );
		    }
		    /* second operand register is moved to vexregop */
		    /* to be fixed: CurrOpnd is always OPND2, so use this const here */
		    CodeInfo.vexregop = opndx[CurrOpnd].base_reg->bytval + 1;
		    memcpy( &opndx[CurrOpnd], &opndx[CurrOpnd+1], sizeof( opndx[0] ) * 2 );
		}
		j--;
	    }
	}
	switch( opndx[CurrOpnd].kind ) {
	case EXPR_ADDR:
	    if ( process_address( &CodeInfo, CurrOpnd, &opndx[CurrOpnd] ) == ERROR )
		return( ERROR );
	    break;
	case EXPR_CONST:
	    if ( process_const( &CodeInfo, CurrOpnd, &opndx[CurrOpnd] ) == ERROR )
		return( ERROR );
	    break;
	case EXPR_REG:
	    if( opndx[CurrOpnd].indirect ) { /* indirect operand ( "[EBX+...]" )? */
		if ( process_address( &CodeInfo, CurrOpnd, &opndx[CurrOpnd] ) == ERROR )
		    return( ERROR );
	    } else {
		/* process_register() can't handle 3rd operand */
		if ( CurrOpnd == OPND3 ) {
		    CodeInfo.opnd[OPND3].type = GetValueSp( opndx[CurrOpnd].base_reg->tokval );
		    CodeInfo.opnd[OPND3].data32l = opndx[CurrOpnd].base_reg->bytval;
		} else if ( process_register( &CodeInfo, CurrOpnd, opndx ) == ERROR )
		    return( ERROR );
	    }
	    break;
	}
    } /* end for */
    /* 4 arguments are valid vor AVX only */
    if ( CurrOpnd != j ) {
	for ( ; tokenarray[i].token != T_COMMA; i-- );
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }

    /* for FAR calls/jmps some special handling is required:
     * in the instruction tables, the "far" entries are located BEHIND
     * the "near" entries, that's why it's needed to skip all items
     * until the next "first" item is found.
     */
    if ( CodeInfo.isfar ) {
	if ( CodeInfo.token == T_CALL || CodeInfo.token == T_JMP ) {
	    do {
		CodeInfo.pinstr++;
	    } while ( CodeInfo.pinstr->first == FALSE );
	}
    }
    /* special handling for string instructions */

    if ( CodeInfo.pinstr->allowed_prefix == AP_REP ||
	 CodeInfo.pinstr->allowed_prefix == AP_REPxx ) {
	HandleStringInstructions( &CodeInfo, opndx );
    } else {
	if( CurrOpnd > 1 ) {
	    /* v1.96: check if a third argument is ok */
	    if ( CurrOpnd > 2 ) {
		do {
		    if ( opnd_clstab[CodeInfo.pinstr->opclsidx].opnd_type_3rd != OP3_NONE )
			break;
		    CodeInfo.pinstr++;
		    if ( CodeInfo.pinstr->first == TRUE ) {
			for ( ; tokenarray[i].token != T_COMMA; i-- );
			return( asmerr(2008, tokenarray[i].tokpos ) );
		    }
		} while ( 1 );
	    }
	    /* v2.06: moved here from process_const() */
	    if ( CodeInfo.token == T_IMUL ) {
		/* the 2-operand form with an immediate as second op
		 * is actually a 3-operand form. That's why the rm byte
		 * has to be adjusted. */
		if ( CodeInfo.opnd[OPND3].type == OP_NONE && ( CodeInfo.opnd[OPND2].type & OP_I ) ) {
		    CodeInfo.prefix.rex |= ((CodeInfo.prefix.rex & REX_B) ? REX_R : 0 );
		    CodeInfo.rm_byte = ( CodeInfo.rm_byte & ~BIT_345 ) | ( ( CodeInfo.rm_byte & BIT_012 ) << 3 );
		} else if ( ( CodeInfo.opnd[OPND3].type != OP_NONE ) &&
			   ( CodeInfo.opnd[OPND2].type & OP_I ) &&
			   CodeInfo.opnd[OPND2].InsFixup &&
			   CodeInfo.opnd[OPND2].InsFixup->sym->state == SYM_UNDEFINED )
		    CodeInfo.opnd[OPND2].type = OP_M;
	    }
	    if( check_size( &CodeInfo, opndx ) == ERROR ) {
		return( ERROR );
	    }
	}
	if ( CodeInfo.Ofssize == USE64 ) {
	    if ( CodeInfo.x86hi_used && CodeInfo.prefix.rex )
		asmerr( 3012 );

	    /* for some instructions, the "wide" flag has to be removed selectively.
	     * this is to be improved - by a new flag in struct instr_item.
	     */
	    switch ( CodeInfo.token ) {
	    case T_PUSH:
	    case T_POP:
		/* v2.06: REX.W prefix is always 0, because size is either 2 or 8 */
		CodeInfo.prefix.rex &= 0x7;
		break;
	    case T_CALL:
	    case T_JMP:
	    case T_VMREAD:
	    case T_VMWRITE:
		/* v2.02: previously rex-prefix was cleared entirely,
		 * but bits 0-2 are needed to make "call rax" and "call r8"
		 * distinguishable!
		 */
		//CodeInfo.prefix.rex = 0;
		CodeInfo.prefix.rex &= 0x7;
		break;
	    case T_MOV:
		/* don't use the Wide bit for moves to/from special regs */
		if ( CodeInfo.opnd[OPND1].type & OP_RSPEC || CodeInfo.opnd[OPND2].type & OP_RSPEC )
		    CodeInfo.prefix.rex &= 0x7;
		break;
	    }
	}
    }

    /* now call the code generator */

    return( codegen( &CodeInfo, oldofs ) );
}

/* process a file. introduced in v2.11 */

void ProcessFile( struct asm_tok tokenarray[] )
/*********************************************/
{
    if ( ModuleInfo.EndDirFound == FALSE && GetTextLine( CurrSource ) ) {

	/* v2.23 - BOM UFT-8 test */
	if ( CurrSource[0] == 0xEF && CurrSource[1] == 0xBB && CurrSource[2] == 0xBF )
	    strcpy( CurrSource, &CurrSource[3] );
	do {
	    if ( PreprocessLine( CurrSource, tokenarray ) ) {
		ParseLine( tokenarray );
		if ( Options.preprocessor_stdout == TRUE && Parse_Pass == PASS_1 )
		    WritePreprocessedLine( CurrSource );
	    }
	} while ( ModuleInfo.EndDirFound == FALSE && GetTextLine( CurrSource ) );
    }
    return;
}

