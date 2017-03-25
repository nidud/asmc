/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	Processing of INVOKE directive.
*
****************************************************************************/

#include <ctype.h>
#include <limits.h>

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <reswords.h>
#include <expreval.h>
#include <lqueue.h>
#include <equate.h>
#include <assume.h>
#include <segment.h>
#include <listing.h>
#include <mangle.h>
#include <extern.h>
#include <proc.h>
#include <tokenize.h>
#include <fastpass.h>

int QueueTestLines( char * );
int ExpandHllProc( char *, int, struct asm_tok[] );

extern uint_32 list_pos;  /* current LST file position */
extern int_64		maxintvalues[];
extern int_64		minintvalues[];
extern enum special_token stackreg[];

#define NUMQUAL

enum reg_used_flags {
    R0_USED	  = 0x01, /* register contents of AX/EAX/RAX is destroyed */
    R0_H_CLEARED  = 0x02, /* 16bit: high byte of R0 (=AH) has been set to 0 */
    R0_X_CLEARED  = 0x04, /* 16bit: register R0 (=AX) has been set to 0 */
    R2_USED	  = 0x08, /* contents of DX is destroyed ( via CWD ); cpu < 80386 only */
    RCX_USED	  = 0x08, /* win64: register contents of CL/CX/ECX/RCX is destroyed */
    RDX_USED	  = 0x10, /* win64: register contents of DL/DX/EDX/RDX is destroyed */
    R8_USED	  = 0x20, /* win64: register contents of R8B/R8W/R8D/R8 is destroyed */
    R9_USED	  = 0x40, /* win64: register contents of R9B/R9W/R9D/R9 is destroyed */
#define RPAR_START 3 /* Win64: RCX first param start at bit 3 */
    ROW_AX_USED	  = 0x08, /* watc: register contents of AL/AX/EAX is destroyed */
    ROW_DX_USED	  = 0x10, /* watc: register contents of DL/DX/EDX is destroyed */
    ROW_BX_USED	  = 0x20, /* watc: register contents of BL/BX/EBX is destroyed */
    ROW_CX_USED	  = 0x40, /* watc: register contents of CL/CX/ECX is destroyed */
#define ROW_START 3 /* watc: irst param start at bit 3 */
};

static int size_vararg; /* size of :VARARG arguments */
static int fcscratch;  /* exclusively to be used by FASTCALL helper functions */

struct fastcall_conv {
    int	 (* invokestart)( struct dsym const *, int, int, struct asm_tok[], int * );
    void (* invokeend)	( struct dsym const *, int, int );
    int	 (* handleparam)( struct dsym const *, int, struct dsym *, bool, struct expr *, char *, uint_8 * );
};

static	int ms32_fcstart( struct dsym const *, int, int, struct asm_tok[], int * );
static void ms32_fcend	( struct dsym const *, int, int );
static	int ms32_param	( struct dsym const *, int, struct dsym *, bool, struct expr *, char *, uint_8 * );
static	int watc_fcstart( struct dsym const *, int, int, struct asm_tok[], int * );
static void watc_fcend	( struct dsym const *, int, int );
static	int watc_param	( struct dsym const *, int, struct dsym *, bool, struct expr *, char *, uint_8 * );
static	int ms64_fcstart( struct dsym const *, int, int, struct asm_tok[], int * );
static void ms64_fcend	( struct dsym const *, int, int );
static	int ms64_param	( struct dsym const *, int, struct dsym *, bool, struct expr *, char *, uint_8 * );
#define REGPAR_WIN64 0x0306 /* regs 1, 2, 8 and 9 */

static const struct fastcall_conv fastcall_tab[] = {
 { ms32_fcstart, ms32_fcend , ms32_param }, /* FCT_MSC */
 { watc_fcstart, watc_fcend , watc_param }, /* FCT_WATCOMC */
 { ms64_fcstart, ms64_fcend , ms64_param } /* FCT_WIN64 */
};

static const enum special_token regax[] = { T_AX, T_EAX, T_RAX };

/* 16-bit MS fastcall uses up to 3 registers (AX, DX, BX )
 * and additional params are pushed in PASCAL order!
 */
static const enum special_token ms16_regs[] = {
    T_AX, T_DX, T_BX
};
static const enum special_token ms32_regs[] = {
    T_ECX, T_EDX
};

static const enum special_token ms64_regs[] = {
 T_CL,	T_DL,  T_R8B, T_R9B,
 T_CX,	T_DX,  T_R8W, T_R9W,
 T_ECX, T_EDX, T_R8D, T_R9D,
 T_RCX, T_RDX, T_R8,  T_R9
};

/* segment register names, order must match ASSUME_ enum */

static int ms32_fcstart( struct dsym const *proc, int numparams, int start, struct asm_tok tokenarray[], int *value )
/*******************************************************************************************************************/
{
    struct dsym *param;
    if ( GetSymOfssize( &proc->sym ) == USE16 )
	return( 0 );
    /* v2.07: count number of register params */
    for ( param = proc->e.procinfo->paralist ; param ; param = param->nextparam )
	if ( param->sym.state == SYM_TMACRO )
	    fcscratch++;
    return( 1 );
}

static void ms32_fcend( struct dsym const *proc, int numparams, int value )
/*************************************************************************/
{
    /* nothing to do */
    return;
}

static int ms32_param( struct dsym const *proc, int index, struct dsym *param, bool addr, struct expr *opnd, char *paramvalue, uint_8 *r0used )
/*********************************************************************************************************************************************/
{
    enum special_token const *pst;

    if ( param->sym.state != SYM_TMACRO )
	return( 0 );
    if ( GetSymOfssize( &proc->sym ) == USE16 ) {
	pst = ms16_regs + fcscratch;
	fcscratch++;
    } else {
	fcscratch--;
	pst = ms32_regs + fcscratch;
    }
    if ( addr )
	AddLineQueueX( " lea %r, %s", *pst, paramvalue );
    else {
	enum special_token reg = *pst;
	int size;
	/* v2.08: adjust register if size of operand won't require the full register */
	if ( ( opnd->kind != EXPR_CONST ) &&
	    ( size = SizeFromMemtype( param->sym.mem_type, USE_EMPTY, param->sym.type ) ) < SizeFromRegister( *pst ) ) {
	    if (( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_386 ) {
		AddLineQueueX( " %s %r, %s", ( param->sym.mem_type & MT_SIGNED ) ? "movsx" : "movzx", reg, paramvalue );
	    } else {
		/* this is currently always UNSIGNED */
		AddLineQueueX( " mov %r, %s", T_AL + GetRegNo( reg ), paramvalue );
		AddLineQueueX( " mov %r, 0", T_AH + GetRegNo( reg ) );
	    }
	} else {
	    /* v2.08: optimization */
	    if ( opnd->kind == EXPR_REG && opnd->indirect == 0 && opnd->base_reg ) {
		if ( opnd->base_reg->tokval == reg )
		    return( 1 );
	    }
	    AddLineQueueX( " mov %r, %s", reg, paramvalue );
	}
    }
    if ( *pst == T_AX )
	*r0used |= R0_USED;
    return( 1 );
}

static int ms64_fcstart( struct dsym const *proc, int numparams, int start, struct asm_tok tokenarray[], int *value )
/*******************************************************************************************************************/
{
    /* v2.04: VARARG didn't work */
    if ( proc->e.procinfo->has_vararg ) {
	for ( numparams = 0; tokenarray[start].token != T_FINAL; start++ )
	    if ( tokenarray[start].token == T_COMMA )
		numparams++;
    }
    if ( numparams < 4 )
	numparams = 4;
    else if ( numparams & 1 )
	numparams++;
    *value = numparams;
    if ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) {
	if ( ( numparams * sizeof( uint_64 ) ) > sym_ReservedStack->value )
	    sym_ReservedStack->value = numparams * sizeof( uint_64 );
    } else
	AddLineQueueX( " sub %r, %d", T_RSP, numparams * sizeof( uint_64 ) );
    /* since Win64 fastcall doesn't push, it's a better/faster strategy to
     * handle the arguments from left to right.
     */
    return( 0 );
}

static void ms64_fcend( struct dsym const *proc, int numparams, int value )
/*************************************************************************/
{
    /* use <value>, which has been set by ms64_fcstart() */
    if ( !( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )
	AddLineQueueX( " add %r, %d", T_RSP, value * 8 );
    return;
}

/* macro to convert register number to param number:
 * 1 -> 0 (rCX)
 * 2 -> 1 (rDX)
 * 8 -> 2 (r8)
 * 9 -> 3 (r9)
 */
#define GetParmIndex( x)  ( ( (x) >= 8 ) ? (x) - 6 : (x) - 1 )

/*
 * parameter for Win64 FASTCALL.
 * the first 4 parameters are hold in registers: rcx, rdx, r8, r9 for non-float arguments,
 * xmm0, xmm1, xmm2, xmm3 for float arguments. If parameter size is > 8, the address of
 * the argument is used instead of the value.
 */

static int ms64_param( struct dsym const *proc, int index, struct dsym *param, bool addr, struct expr *opnd, char *paramvalue, uint_8 *regs_used )
/************************************************************************************************************************************************/
{
    uint_32 size;
    uint_32 psize;
    int reg;
    int reg2;
    int i;
    int base;
    bool destroyed = FALSE;

    /* v2.11: default size is 32-bit, not 64-bit */
    if ( param->sym.is_vararg ) {
	psize = 0;
	if ( addr || opnd->instr == T_OFFSET )
	    psize = 8;
	else if ( opnd->kind == EXPR_REG && opnd->indirect == FALSE )
	    psize = SizeFromRegister( opnd->base_reg->tokval );
	else if ( opnd->mem_type != MT_EMPTY )
	    psize = SizeFromMemtype( opnd->mem_type, USE64, opnd->type );
	if ( psize < 4 )
	    psize = 4;
    } else
	psize = SizeFromMemtype( param->sym.mem_type, USE64, param->sym.type );

    /* check for register overwrites; v2.11: moved out the if( index >= 4 ) block */
    if ( opnd->base_reg != NULL ) {
	reg = opnd->base_reg->tokval;
	if ( GetValueSp( reg ) & OP_R ) {
	    i = GetRegNo( reg );
	    if ( REGPAR_WIN64 & ( 1 << i ) ) {
		base = GetParmIndex( i );
		if ( *regs_used & ( 1 << ( base + RPAR_START ) ) )
		    destroyed = TRUE;
	    } else if ( (*regs_used & R0_USED ) && ( ( GetValueSp( reg ) & OP_A ) || reg == T_AH ) ) {
		destroyed = TRUE;
	    }
	}
    }
    if ( opnd->idx_reg != NULL ) {
	reg2 = opnd->idx_reg->tokval;
	if ( GetValueSp( reg2 ) & OP_R ) {
	    i = GetRegNo( reg2 );
	    if ( REGPAR_WIN64 & ( 1 << i ) ) {
		base = GetParmIndex( i );
		if ( *regs_used & ( 1 << ( base + RPAR_START ) ) )
		    destroyed = TRUE;
	    } else if ( (*regs_used & R0_USED ) && ( ( GetValueSp( reg2 ) & OP_A ) || reg2 == T_AH ) ) {
		destroyed = TRUE;
	    }
	}
    }
    if ( destroyed ) {
	asmerr( 2133 );
	*regs_used = 0;
    }

    if ( index >= 4 ) {

	if ( addr || psize > 8 ) {
	    if ( psize == 4 )
		i = T_EAX;
	    else {
		i = T_RAX;
		if ( psize < 8 )
		    asmerr( 2114, index+1 );
	    }
	    *regs_used |= R0_USED;
	    AddLineQueueX( " lea %r, %s", i, paramvalue );
	    AddLineQueueX( " mov [%r+%u], %r", T_RSP, NUMQUAL index*8, i );
	    return( 1 );
	}

	if ( opnd->kind == EXPR_CONST ||
	   ( opnd->kind == EXPR_ADDR && opnd->indirect == FALSE && opnd->mem_type == MT_EMPTY && opnd->instr != T_OFFSET ) ) {

	    /* v2.06: support 64-bit constants for params > 4 */
	    if ( psize == 8 &&
		( opnd->value64 > LONG_MAX || opnd->value64 < LONG_MIN ) ) {
		AddLineQueueX( " mov %r ptr [%r+%u], %r ( %s )", T_DWORD, T_RSP, NUMQUAL index*8, T_LOW32, paramvalue );
		AddLineQueueX( " mov %r ptr [%r+%u], %r ( %s )", T_DWORD, T_RSP, NUMQUAL index*8+4, T_HIGH32, paramvalue );

	    } else {
		/* v2.11: no expansion if target type is a pointer and argument is an address part */
		if ( param->sym.mem_type == MT_PTR && opnd->kind == EXPR_ADDR && opnd->sym->state != SYM_UNDEFINED ) {
		    asmerr( 2114, index+1 );
		}
		switch ( psize ) {
		case 1:	  i = T_BYTE; break;
		case 2:	  i = T_WORD; break;
		case 4:	  i = T_DWORD; break;
		default:  i = T_QWORD; break;
		}
		AddLineQueueX( " mov %r ptr [%r+%u], %s", i, T_RSP, NUMQUAL index*8, paramvalue );
	    }

	} else if ( opnd->kind == EXPR_FLOAT  ) {

	    if ( param->sym.mem_type == MT_REAL8 ) {
		AddLineQueueX( " mov %r ptr [%r+%u+0], %r (%s)", T_DWORD, T_RSP, NUMQUAL index*8, T_LOW32, paramvalue );
		AddLineQueueX( " mov %r ptr [%r+%u+4], %r (%s)", T_DWORD, T_RSP, NUMQUAL index*8, T_HIGH32, paramvalue );
	    } else
		AddLineQueueX( " mov %r ptr [%r+%u], %s", T_DWORD, T_RSP, NUMQUAL index*8, paramvalue );

	} else { /* it's a register or variable */

	    if ( opnd->kind == EXPR_REG && opnd->indirect == FALSE ) {
		size = SizeFromRegister( reg );
		if ( size == psize )
		    i = reg;
		else {
		    if ( size > psize || ( size < psize && param->sym.mem_type == MT_PTR ) ) {
			asmerr( 2114, index+1 );
			psize = size;
		    }
		    switch ( psize ) {
		    case 1:  i = T_AL;	break;
		    case 2:  i = T_AX;	break;
		    case 4:  i = T_EAX; break;
		    default: i = T_RAX; break;
		    }
		    *regs_used |= R0_USED;
		}
	    } else {
		if ( opnd->mem_type == MT_EMPTY )
		    size = ( opnd->instr == T_OFFSET ? 8 : 4 );
		else
		    size = SizeFromMemtype( opnd->mem_type, USE64, opnd->type );
		switch ( psize ) {
		case 1:	 i = T_AL;  break;
		case 2:	 i = T_AX;  break;
		case 4:	 i = T_EAX; break;
		default: i = T_RAX; break;
		}
		*regs_used |= R0_USED;
	    }

	    /* v2.11: no expansion if target type is a pointer */
	    if ( size > psize || ( size < psize && param->sym.mem_type == MT_PTR ) ) {
		asmerr( 2114, index+1 );
	    }
	    if ( size != psize ) {
		if ( size == 4 ) {
		    if ( IS_SIGNED( opnd->mem_type ) )
			AddLineQueueX( " movsxd %r, %s", i, paramvalue );
		    else
			AddLineQueueX( " mov %r, %s", i, paramvalue );
		} else
		    AddLineQueueX( " mov%sx %r, %s", IS_SIGNED( opnd->mem_type ) ? "s" : "z", i, paramvalue );
	    } else if ( opnd->kind != EXPR_REG || opnd->indirect == TRUE )
		AddLineQueueX( " mov %r, %s", i, paramvalue );

	    AddLineQueueX( " mov [%r+%u], %r", T_RSP, NUMQUAL index*8, i );
	}

    } else if ( param->sym.mem_type == MT_REAL4 ||
	       param->sym.mem_type == MT_REAL8 ) {

	/* v2.04: check if argument is the correct XMM register already */
	if ( opnd->kind == EXPR_REG && opnd->indirect == FALSE ) {

	    if ( GetValueSp( reg ) & OP_XMM ) {
		if ( reg == T_XMM0 + index )
		;
		else
		    AddLineQueueX( " movq %r, %s", T_XMM0 + index, paramvalue );
		return( 1 );
	    }
	}
	if ( opnd->kind == EXPR_FLOAT ) {
	    *regs_used |= R0_USED;
	    if ( param->sym.mem_type == MT_REAL4 ) {
		AddLineQueueX( " mov %r, %s", T_EAX, paramvalue );
		AddLineQueueX( " movd %r, %r", T_XMM0 + index, T_EAX );
	    } else {
		AddLineQueueX( " mov %r, %r ptr %s", T_RAX, T_REAL8, paramvalue );
		AddLineQueueX( " movd %r, %r", T_XMM0 + index, T_RAX );
	    }
	} else {
	    if ( param->sym.mem_type == MT_REAL4 )
		AddLineQueueX( " movd %r, %s", T_XMM0 + index, paramvalue );
	    else
		AddLineQueueX( " movq %r, %s", T_XMM0 + index, paramvalue );
	}
    } else {

	if ( addr || psize > 8 ) { /* psize > 8 shouldn't happen! */
	    if ( psize >= 4 )
		AddLineQueueX( " lea %r, %s", ms64_regs[index+2*4+(psize > 4 ? 4 : 0)], paramvalue );
	    else
		asmerr( 2114, index+1 );
	    *regs_used |= ( 1 << ( index + RPAR_START ) );
	    return( 1 );
	}
	/* register argument? */
	if ( opnd->kind == EXPR_REG && opnd->indirect == FALSE ) {
	    reg = opnd->base_reg->tokval;
	    size = SizeFromRegister( reg );
	} else if ( opnd->kind == EXPR_CONST || opnd->kind == EXPR_FLOAT ) {
	    size = psize;
	} else if ( opnd->mem_type != MT_EMPTY ) {
	    size = SizeFromMemtype( opnd->mem_type, USE64, opnd->type );
	} else if ( opnd->kind == EXPR_ADDR && opnd->sym->state == SYM_UNDEFINED ) {
	    size = psize;
	} else
	    size = ( opnd->instr == T_OFFSET ? 8 : 4 );

	if ( size > psize || ( size < psize && param->sym.mem_type == MT_PTR ) ) {
	    asmerr( 2114, index+1 );
	}
	switch ( psize ) {
	case 1: base =	0*4; break;
	case 2: base =	1*4; break;
	case 4: base =	2*4; break;
	default:base =	3*4; break;
	}
	/* optimization if the register holds the value already */
	if ( opnd->kind == EXPR_REG && opnd->indirect == FALSE ) {
	    if ( GetValueSp( reg ) & OP_R ) {
		if ( ms64_regs[index+base] == reg ) {
		    return( 1 );
		}
		i = GetRegNo( reg );
		if ( REGPAR_WIN64 & ( 1 << i ) ) {
		    i = GetParmIndex( i );
		    if ( *regs_used & ( 1 << ( i + RPAR_START ) ) )
			asmerr( 2133 );
		}
	    }
	}
	/* v2.11: allow argument extension */
	if ( size < psize )
	    if ( size == 4 ) {
		if ( IS_SIGNED( opnd->mem_type ) )
		    AddLineQueueX( " movsxd %r, %s", ms64_regs[index+base], paramvalue );
		else
		    AddLineQueueX( " mov %r, %s", ms64_regs[index+2*4], paramvalue );
	    } else
		AddLineQueueX( " mov%sx %r, %s", IS_SIGNED( opnd->mem_type ) ? "s" : "z", ms64_regs[index+base], paramvalue );
	else
	    AddLineQueueX( " mov %r, %s", ms64_regs[index+base], paramvalue );
	*regs_used |= ( 1 << ( index + RPAR_START ) );
    }
    return( 1 );
}

/* get segment part of an argument
 * v2.05: extracted from PushInvokeParam(),
 * so it could be used by watc_param() as well.
 */

static short GetSegmentPart( struct expr *opnd, char *buffer, const char *fullparam )
/***********************************************************************************/
{
    short reg = T_NULL;

    if ( opnd->override != NULL ) {
	if ( opnd->override->token == T_REG )
	    reg = opnd->override->tokval;
	else
	    strcpy( buffer, opnd->override->string_ptr );
    } else if ( opnd->sym != NULL && opnd->sym->segment != NULL ) {
	struct dsym *dir = GetSegm( opnd->sym );
	enum assume_segreg as;
	if ( dir->e.seginfo->segtype == SEGTYPE_DATA ||
	    dir->e.seginfo->segtype == SEGTYPE_BSS )
	    as = search_assume( (struct asym *)dir, ASSUME_DS, TRUE );
	else
	    as = search_assume( (struct asym *)dir, ASSUME_CS, TRUE );
	if ( as != ASSUME_NOTHING ) {
	    //GetResWName( segreg_tab[as], buffer );
	    reg = T_ES + as; /* v2.08: T_ES is first seg reg in special.h */
	} else {
	    struct asym *seg;
	    seg = GetGroup( opnd->sym );
	    if ( seg == NULL )
		seg = &dir->sym;
	    if ( seg )
		strcpy( buffer, seg->name );
	    else {
		strcpy( buffer, "seg " );
		strcat( buffer, fullparam );
	    }
	}
    } else if ( opnd->sym && opnd->sym->state == SYM_STACK ) {
	reg = T_SS;
    } else {
	strcpy( buffer,"seg " );
	strcat( buffer, fullparam );
    }
    return( reg );
}

/* the watcomm fastcall variant is somewhat peculiar:
 * 16-bit:
 * - for BYTE/WORD arguments, there are 4 registers: AX,DX,BX,CX
 * - for DWORD arguments, there are 2 register pairs: DX::AX and CX::BX
 * - there is a "usage" flag for each register. Thus the prototype:
 *   sample proto :WORD, :DWORD, :WORD
 *   will assign AX to the first param, CX::BX to the second, and DX to
 *   the third!
 */

static int watc_fcstart( struct dsym const *proc, int numparams, int start, struct asm_tok tokenarray[], int *value )
/*******************************************************************************************************************/
{
    return( 1 );
}

static void watc_fcend( struct dsym const *proc, int numparams, int value )
/*************************************************************************/
{
    if ( proc->e.procinfo->has_vararg ) {
	AddLineQueueX( " add %r, %u", stackreg[ModuleInfo.Ofssize], NUMQUAL proc->e.procinfo->parasize + size_vararg );
    } else if ( fcscratch < proc->e.procinfo->parasize ) {
	AddLineQueueX( " add %r, %u", stackreg[ModuleInfo.Ofssize], NUMQUAL ( proc->e.procinfo->parasize - fcscratch ) );
    }
    return;
}

/* get the register for parms 0 to 3,
 * using the watcom register parm passing conventions ( A D B C )
 */
static int watc_param( struct dsym const *proc, int index, struct dsym *param, bool addr, struct expr *opnd, char *paramvalue, uint_8 *r0used )
/*********************************************************************************************************************************************/
{
    int opc;
    int qual;
    int i;
    char regs[64];
    char *reg[4];
    char *p;
    int psize = SizeFromMemtype( param->sym.mem_type, USE_EMPTY, param->sym.type );

    if ( param->sym.state != SYM_TMACRO )
	return( 0 );

    fcscratch += CurrWordSize;

    /* the "name" might be a register pair */

    reg[0] = param->sym.string_ptr;
    reg[1] = NULL;
    reg[2] = NULL;
    reg[3] = NULL;
    if ( strchr( reg[0], ':' ) ) {
	strcpy( regs, reg[0] );
	fcscratch += CurrWordSize;
	for ( p = regs, i = 0; i < 4; i++ ) {
	    reg[i] = p;
	    p = strchr( p, ':' );
	    if ( p == NULL )
		break;
	    *p++ = NULLC;
	    p++;
	}
    }

    if ( addr ) {
	if ( opnd->kind == T_REG || opnd->sym->state == SYM_STACK ) {
	    opc = T_LEA;
	    qual = T_NULL;
	} else {
	    opc = T_MOV;
	    qual = T_OFFSET;
	}
	/* v2.05: filling of segment part added */
	i = 0;
	if ( reg[1] != NULL ) {
	    char buffer[128];
	    short sreg;
	    if ( sreg = GetSegmentPart( opnd, buffer, paramvalue ) )
		AddLineQueueX( "%r %s, %r", T_MOV, reg[0],  sreg );
	    else
		AddLineQueueX( "%r %s, %s", T_MOV, reg[0],  buffer );
	    i++;
	}
	AddLineQueueX( "%r %s, %r %s", opc, reg[i], qual, paramvalue );
	return( 1 );
    }
    for ( i = 3; i >= 0; i-- ) {
	if ( reg[i] ) {
	    if ( opnd->kind == EXPR_CONST ) {
		if ( i > 0 )
		    qual = T_LOWWORD;
		else if ( i == 0 && reg[1] != NULL )
		    qual = T_HIGHWORD;
		else
		    qual = T_NULL;
		if ( qual != T_NULL )
		    AddLineQueueX( "mov %s, %r (%s)", reg[i], qual, paramvalue );
		else
		    AddLineQueueX( "mov %s, %s", reg[i], paramvalue );
	    } else if ( opnd->kind == EXPR_REG ) {
		AddLineQueueX( "mov %s, %s", reg[i], paramvalue );
	    } else {
		if ( i == 0 && reg[1] == NULL )
		    AddLineQueueX( "mov %s, %s", reg[i], paramvalue );
		else {
		    if ( ModuleInfo.Ofssize )
			qual = T_DWORD;
		    else
			qual = T_WORD;
		    AddLineQueueX( "mov %s, %r %r %s[%u]", reg[i], qual, T_PTR, paramvalue, psize - ( (i+1) * ( 2 << ModuleInfo.Ofssize ) ) );
		}
	    }
	}
    }
    return( 1 );
}

static void SkipTypecast( char *fullparam, int i, struct asm_tok tokenarray[] )
/*****************************************************************************/
{
    int j;
    fullparam[0] = NULLC;
    for ( j = i; ; j++ ) {
	if (( tokenarray[j].token == T_COMMA ) || ( tokenarray[j].token == T_FINAL ) )
	    break;
	if (( tokenarray[j+1].token == T_BINARY_OPERATOR ) && ( tokenarray[j+1].tokval == T_PTR ) )
	    j = j + 1;
	else {
	    if ( fullparam[0] != NULLC )
		strcat( fullparam," " );
	    strcat( fullparam, tokenarray[j].string_ptr );
	}
    }
}

/*
 * push one parameter of a procedure called with INVOKE onto the stack
 * - i	     : index of the start of the parameter list
 * - tokenarray : token array
 * - proc    : the PROC to call
 * - curr    : the current parameter
 * - reqParam: the index of the parameter which is to be pushed
 * - r0flags : flags for register usage across params
 *
 * psize,asize: size of parameter/argument in bytes.
 */

static int PushInvokeParam( int i, struct asm_tok tokenarray[], struct dsym *proc, struct dsym *curr, int reqParam, uint_8 *r0flags)
/**********************************************************************************************************************************/
{
    int currParm;
    int psize;
    int asize;
    int pushsize;
    int j;
    int fptrsize;
    char Ofssize;
    bool addr = FALSE; /* ADDR operator found */
    struct expr opnd;
    char fullparam[MAX_LINE_LEN];
    char buffer[MAX_LINE_LEN];

    for ( currParm = 0; currParm <= reqParam; ) {
	if ( tokenarray[i].token == T_FINAL ) { /* this is no real error! */
	    return( ERROR );
	}
	if ( tokenarray[i].token == T_COMMA ) {
	    currParm++;
	}
	i++;
    }
    /* if curr is NULL this call is just a parameter check */
    if ( !curr ) return( NOT_ERROR );

    psize = curr->sym.total_size;

    /* ADDR: the argument's address is to be pushed? */
    if ( tokenarray[i].token == T_RES_ID && tokenarray[i].tokval == T_ADDR ) {
	addr = TRUE;
	i++;
    }

    /* copy the parameter tokens to fullparam */
    for ( j = i; tokenarray[j].token != T_COMMA && tokenarray[j].token != T_FINAL; j++ );
    memcpy( fullparam, tokenarray[i].tokpos, tokenarray[j].tokpos - tokenarray[i].tokpos );
    fullparam[tokenarray[j].tokpos - tokenarray[i].tokpos] = NULLC;

    j = i;
    /* v2.11: GetSymOfssize() doesn't work for state SYM_TYPE */
    Ofssize = ( proc->sym.state == SYM_TYPE ? proc->sym.seg_ofssize : GetSymOfssize( &proc->sym ) );
    fptrsize = 2 + ( 2 << Ofssize );

    if ( addr ) {
	/* v2.06: don't handle forward refs if -Zne is set */
	if ( EvalOperand( &j, tokenarray, Token_Count, &opnd, ModuleInfo.invoke_exprparm ) == ERROR )
	    return( ERROR );

	/* DWORD (16bit) and FWORD(32bit) are treated like FAR ptrs
	 * v2.11: argument may be a FAR32 pointer ( psize == 6 ), while
	 * fptrsize may be just 4!
	 */
	if ( psize > fptrsize && fptrsize > 4 ) {
	    /* QWORD is NOT accepted as a FAR ptr */
	    asmerr( 2114, reqParam+1 );

	    return( NOT_ERROR );
	}

	if ( proc->sym.langtype == LANG_FASTCALL )
	    if ( fastcall_tab[ModuleInfo.fctype].handleparam( proc, reqParam, curr, addr, &opnd, fullparam, r0flags ) )
		return( NOT_ERROR );

	if ( opnd.kind == EXPR_REG || opnd.indirect ) {
	    if ( curr->sym.isfar || psize == fptrsize ) {
		if ( opnd.sym && opnd.sym->state == SYM_STACK )
		    GetResWName( T_SS, buffer );
		else if ( opnd.override != NULL )
		    strcpy( buffer, opnd.override->string_ptr );
		else
		    GetResWName( T_DS, buffer );
		AddLineQueueX( " push %s", buffer );
	    }
	    AddLineQueueX( " lea %r, %s", regax[ModuleInfo.Ofssize], fullparam );
	    *r0flags |= R0_USED;
	    AddLineQueueX( " push %r", regax[ModuleInfo.Ofssize] );
	} else {
	push_address:

	    /* push segment part of address?
	     * v2.11: do not assume a far pointer if psize == fptrsize
	     * ( parameter might be near32 in a 16-bit environment )
	     */
	    //if ( curr->sym.isfar || psize == fptrsize ) {
	    if ( curr->sym.isfar || psize > ( 2 << curr->sym.Ofssize ) ) {

		short sreg;
		sreg = GetSegmentPart( &opnd, buffer, fullparam );
		if ( sreg ) {
		    /* v2.11: push segment part as WORD or DWORD depending on target's offset size
		     * problem: "pushw ds" is not accepted, so just emit a size prefix.
		     */
		    if ( Ofssize != ModuleInfo.Ofssize || ( curr->sym.Ofssize == USE16 && CurrWordSize > 2 ) )
			AddLineQueue( " db 66h" );
		    AddLineQueueX( " push %r", sreg );
		} else
		    AddLineQueueX( " push %s", buffer );
	    }
	    /* push offset part of address */
	    if ( (ModuleInfo.curr_cpu & P_CPU_MASK ) < P_186 ) {
		AddLineQueueX( " mov %r, offset %s", T_AX, fullparam );
		AddLineQueueX( " push %r", T_AX );
		*r0flags |= R0_USED;
	    } else {
		if ( curr->sym.is_vararg && opnd.Ofssize == USE_EMPTY && opnd.sym )
		    opnd.Ofssize = GetSymOfssize( opnd.sym );
		/* v2.04: expand 16-bit offset to 32
		 * v2.11: also expand if there's an explicit near32 ptr requested in 16-bit
		 */
		//if ( opnd.Ofssize == USE16 && CurrWordSize > 2 ) {
		if ( ( opnd.Ofssize == USE16 && CurrWordSize > 2 ) ||
		    ( curr->sym.Ofssize == USE32 && CurrWordSize == 2 ) ) {
		    AddLineQueueX( " pushd %r %s", T_OFFSET, fullparam );
		} else if ( CurrWordSize > 2 && curr->sym.Ofssize == USE16 &&
			   ( curr->sym.isfar || Ofssize == USE16 ) ) { /* v2.11: added */
		    AddLineQueueX( " pushw %r %s", T_OFFSET, fullparam );
		} else {
		    AddLineQueueX( " push %r %s", T_OFFSET, fullparam );
		    /* v2.04: a 32bit offset pushed in 16-bit code */
		    if ( curr->sym.is_vararg && CurrWordSize == 2 && opnd.Ofssize > USE16 ) {
			size_vararg += CurrWordSize;
		    }
		}
	    }
	}
	if ( curr->sym.is_vararg ) {
	    size_vararg += CurrWordSize + ( curr->sym.isfar ? CurrWordSize : 0 );
	}
    } else { /* ! ADDR branch */

	/* handle the <reg>::<reg> case here, the evaluator wont handle it */
	if ( tokenarray[j].token == T_REG &&
	    tokenarray[j+1].token == T_DBL_COLON &&
	    tokenarray[j+2].token == T_REG ) {
	    int asize2;
	    /* for pointers, segreg size is assumed to be always 2 */
	    if ( GetValueSp( tokenarray[j].tokval ) & OP_SR ) {
		asize2 = 2;
		/* v2.11: if target and current src have different offset sizes,
		 * the push of the segment register must be 66h-prefixed!
		 */
		if ( Ofssize != ModuleInfo.Ofssize || ( curr->sym.Ofssize == USE16 && CurrWordSize > 2 ) )
		    AddLineQueue( " db 66h" );
	    } else
		asize2 = SizeFromRegister( tokenarray[j].tokval );
	    asize = SizeFromRegister( tokenarray[j+2].tokval );
	    AddLineQueueX( " push %r", tokenarray[j].tokval );
	    /* v2.04: changed */
	    if (( curr->sym.is_vararg ) && (asize + asize2) != CurrWordSize )
		size_vararg += asize2;
	    else
		asize += asize2;
	    strcpy( fullparam, tokenarray[j+2].string_ptr );

	    opnd.kind = EXPR_REG;
	    opnd.indirect = FALSE;
	    opnd.sym = NULL;
	    opnd.base_reg = &tokenarray[j+2]; /* for error msg 'eax overwritten...' */
	} else {
	    /* v2.06: don't handle forward refs if -Zne is set */
	    //if ( EvalOperand( &j, Token_Count, &opnd, 0 ) == ERROR ) {
	    if ( EvalOperand( &j, tokenarray, Token_Count, &opnd, ModuleInfo.invoke_exprparm ) == ERROR ) {
		return( ERROR );
	    }

	    /* for a simple register, get its size */
	    if ( opnd.kind == EXPR_REG && opnd.indirect == FALSE ) {
		asize = SizeFromRegister( opnd.base_reg->tokval );
	    } else if ( opnd.kind == EXPR_CONST || opnd.mem_type == MT_EMPTY ) {
		asize = psize;
		/* v2.04: added, to catch 0-size params ( STRUCT without members ) */
		if ( psize == 0 ) {
		    if ( curr->sym.is_vararg == FALSE ) {
			asmerr( 2114, reqParam+1 );
		    }
		    /* v2.07: for VARARG, get the member's size if it is a structured var */
		    if ( opnd.mbr && opnd.mbr->mem_type == MT_TYPE )
			asize = SizeFromMemtype( opnd.mbr->mem_type, opnd.Ofssize, opnd.mbr->type );
		}
	    } else if ( opnd.mem_type != MT_TYPE ) {
		if ( opnd.kind == EXPR_ADDR &&
		     opnd.indirect == FALSE &&
		     opnd.sym &&
		     opnd.instr == EMPTY &&
		     ( opnd.mem_type == MT_NEAR || opnd.mem_type == MT_FAR ) )
		    goto push_address;
		if ( opnd.Ofssize == USE_EMPTY )
		    opnd.Ofssize = ModuleInfo.Ofssize;
		asize = SizeFromMemtype( opnd.mem_type, opnd.Ofssize, opnd.type );
	    } else {
		if ( opnd.sym != NULL )
		    asize = opnd.sym->type->total_size;
		else
		    asize = opnd.mbr->type->total_size;
	    }
	}

	if ( curr->sym.is_vararg == TRUE )
	    psize = asize;

	pushsize = CurrWordSize;

	if ( proc->sym.langtype == LANG_FASTCALL )
	    if ( fastcall_tab[ModuleInfo.fctype].handleparam( proc, reqParam, curr, addr, &opnd, fullparam, r0flags ) )
		return( NOT_ERROR );

	if ( ( asize > psize ) || ( asize < psize && curr->sym.mem_type == MT_PTR ) ) {
	    asmerr( 2114, reqParam+1 );
	    return( NOT_ERROR );
	}

	if ( ( opnd.kind == EXPR_ADDR && opnd.instr != T_OFFSET ) ||
	    ( opnd.kind == EXPR_REG && opnd.indirect == TRUE ) ) {

	    /* catch the case when EAX has been used for ADDR,
	     * and is later used as addressing register!
	     *
	     */
	    if ( *r0flags && (( opnd.base_reg != NULL &&
		  ( opnd.base_reg->tokval == T_EAX || opnd.base_reg->tokval == T_RAX )) ||
		 ( opnd.idx_reg != NULL &&
		  ( opnd.idx_reg->tokval == T_EAX || opnd.idx_reg->tokval == T_RAX )))) {
		asmerr( 2133 );
		*r0flags = 0;
	    }

	    if ( curr->sym.is_vararg ) {
		size_vararg += ( asize > pushsize ? asize : pushsize );
	    }
	    if ( asize > pushsize ) {

		short dw = T_WORD;
		if (( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_386 ) {
		    pushsize = 4;
		    dw = T_DWORD;
		}

		/* in params like "qword ptr [eax]" the typecast
		 * has to be removed */
		if ( opnd.explicit ) {
		    SkipTypecast( fullparam, i, tokenarray );
		    opnd.explicit = FALSE;
		}

		while ( asize > 0 ) {

		    if ( asize & 2 ) {

			/* ensure the stack remains dword-aligned in 32bit */
			if ( ModuleInfo.Ofssize > USE16 ) {
			    /* v2.05: better push a 0 word? */
			    //AddLineQueueX( " pushw 0" );
			    /* ASMC v1.12: ensure the stack remains dword-aligned in 32bit */
			    if (pushsize == 4)
				size_vararg += 2;
			    AddLineQueueX( " sub %r, 2", stackreg[ModuleInfo.Ofssize] );
			}
			AddLineQueueX( " push word ptr %s+%u", fullparam, NUMQUAL asize-2 );
			asize -= 2;
		    } else {
			AddLineQueueX( " push %r ptr %s+%u", dw, fullparam, NUMQUAL asize-pushsize );
			asize -= pushsize;
		    }
		}
	    } else if ( asize < pushsize ) {

		if ( psize > 4 ) {
		    asmerr( 2114, reqParam+1 );
		}
		/* v2.11: added, use MOVSX/MOVZX if cpu >= 80386 */
		if ( asize < 4 && psize > 2 && IS_SIGNED( opnd.mem_type ) && ( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_386 ) {
		    AddLineQueueX( " movsx %r, %s", T_EAX, fullparam );
		    AddLineQueueX( " push %r", T_EAX );
		    *r0flags = R0_USED; /* reset R0_H_CLEARED  */
		} else {
		    switch ( opnd.mem_type ) {
		    case MT_BYTE:
		    case MT_SBYTE:
			if ( psize == 1 && curr->sym.is_vararg == FALSE ) {
			    AddLineQueueX( " mov %r, %s", T_AL, fullparam );
			    AddLineQueueX( " push %r", regax[ModuleInfo.Ofssize] );
			} else if ( pushsize == 2 ) { /* 16-bit code? */
			    if ( opnd.mem_type == MT_BYTE ) {
				if ( psize == 4 )
				    if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) < P_186 )	 {
					if ( !(*r0flags & R0_X_CLEARED ) )
					    AddLineQueueX( " xor %r, %r", T_AX, T_AX );
					*r0flags |= ( R0_X_CLEARED | R0_H_CLEARED );
					AddLineQueueX( " push %r", T_AX );
				    } else
					AddLineQueue( " push 0" );
				AddLineQueueX( " mov %r, %s", T_AL, fullparam );
				if ( !( *r0flags & R0_H_CLEARED )) {
				    AddLineQueueX( " mov %r, 0", T_AH );
				    *r0flags |= R0_H_CLEARED;
				}
			    } else {
				AddLineQueueX( " mov %r, %s", T_AL, fullparam );
				*r0flags = 0; /* reset AH_CLEARED */
				AddLineQueue( " cbw" );
				if ( psize == 4 ) {
				    AddLineQueue( " cwd" );
				    AddLineQueueX( " push %r", T_DX );
				    *r0flags |= R2_USED;
				}
			    }
			    AddLineQueueX( " push %r", T_AX );
			} else {
			    AddLineQueueX( " mov%sx %r, %s", opnd.mem_type == MT_BYTE ? "z" : "s", T_EAX, fullparam );
			    AddLineQueueX( " push %r", T_EAX );
			}
			*r0flags |= R0_USED;
			break;
		    case MT_WORD:
		    case MT_SWORD:
			if ( opnd.mem_type == MT_WORD && ( Options.masm_compat_gencode || psize == 2 )) {
			    if ( curr->sym.is_vararg || psize != 2 )
				AddLineQueueX( " pushw 0" );
			    else {
				AddLineQueueX( " sub %r, 2", stackreg[ModuleInfo.Ofssize] );
			    }
			    AddLineQueueX( " push %s", fullparam );
			} else {
			    AddLineQueueX( " mov%sx %r, %s", opnd.mem_type == MT_WORD ? "z" : "s", T_EAX, fullparam );
			    AddLineQueueX( " push %r", T_EAX );
			    *r0flags = R0_USED; /* reset R0_H_CLEARED  */
			}
			break;
		    default:
			AddLineQueueX( " push %s", fullparam );
		    }
		}
	    } else { /* asize == pushsize */
		if ( IS_SIGNED( opnd.mem_type ) && psize > asize ) {
		    if ( psize > 2 && (( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_386 ) ) {
			AddLineQueueX( " movsx %r, %s", T_EAX, fullparam );
			AddLineQueueX( " push %r", T_EAX );
			*r0flags = R0_USED; /* reset R0_H_CLEARED  */
		    } else if ( pushsize == 2 && psize > 2 ) {
			AddLineQueueX( " mov %r, %s", T_AX, fullparam );
			AddLineQueueX( " cwd" );
			AddLineQueueX( " push %r", T_DX );
			AddLineQueueX( " push %r", T_AX );
			*r0flags = R0_USED | R2_USED;
		    } else
			AddLineQueueX( " push %s", fullparam );
		} else {
		    if ( pushsize == 2 && psize > 2 ) {
			if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) < P_186 )  {
			    if ( !(*r0flags & R0_X_CLEARED ) )
				AddLineQueueX( " xor %r, %r", T_AX, T_AX );
			    AddLineQueueX( " push %r", T_AX );
			    *r0flags |= ( R0_USED | R0_X_CLEARED | R0_H_CLEARED );
			} else
			    AddLineQueueX( " pushw 0" );
		    }
		    AddLineQueueX( " push %s", fullparam );
		}
	    }

	} else { /* the parameter is a register or constant value! */
	    if ( opnd.kind == EXPR_REG ) {
		int reg = opnd.base_reg->tokval;
		unsigned optype = GetValueSp( reg );

		/* v2.11 */
		if ( curr->sym.is_vararg == TRUE && psize < pushsize )
		    psize = pushsize;

		/* v2.06: check if register is valid to be pushed.
		 * ST(n), MMn, XMMn, YMMn and special registers are NOT valid!
		 */
		if ( optype & ( OP_STI | OP_MMX | OP_XMM | OP_YMM | OP_RSPEC ) ) {
		    return( asmerr( 2114, reqParam+1 ) );
		}

		if ( ( *r0flags & R0_USED ) && ( reg == T_AH || ( optype & OP_A ) ) ) {
		    asmerr( 2133 );
		    *r0flags &= ~R0_USED;
		} else if ( ( *r0flags & R2_USED ) && ( reg == T_DH || GetRegNo( reg ) == 2 ) ) {
		    asmerr( 2133 );
		    *r0flags &= ~R2_USED;
		}
		if ( asize != psize || asize < ( 2 << Ofssize ) ) {
		    /* register size doesn't match the needed parameter size.
		     */
		    if ( psize > 4 ) {
			asmerr( 2114, reqParam+1 );
		    }

		    if ( asize <= 2 && ( psize == 4 || pushsize == 4 ) ) {
			if (( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_386 && asize == psize ) {
			    if ( asize == 2 )
				reg = reg - T_AX + T_EAX;
			    else {
				/* v2.11: hibyte registers AH, BH, CH, DH ( no 4-7 ) needs special handling */
				if ( reg < T_AH )
				    reg = reg - T_AL + T_EAX;
				else {
				    AddLineQueueX( " mov %r, %s", T_AL, fullparam );
				    *r0flags |= R0_USED;
				    reg = T_EAX;
				}
				asize = 2; /* done */
			    }
			} else if ( IS_SIGNED( opnd.mem_type ) && pushsize < 4 ) {

			    /* psize is 4 in this branch */
			    if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_386 ) {
				AddLineQueueX( " movsx %r, %s", T_EAX, fullparam );
				*r0flags = R0_USED;
				reg = T_EAX;
			    } else {
				*r0flags = R0_USED | R2_USED;
				if ( asize == 1 ) {
				    if ( reg != T_AL )
					AddLineQueueX( " mov %r, %s", T_AL, fullparam );
				    AddLineQueue( " cbw" );
				} else if ( reg != T_AX )
				    AddLineQueueX( " mov %r, %s", T_AX, fullparam );
				AddLineQueue( " cwd" );
				AddLineQueueX( " push %r", T_DX );
				reg = T_AX;
			    }
			    asize = 2; /* done */

			} else if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_186 ) {

			    if ( pushsize == 4 ) {
				if ( asize == 1 ) {
				    /* handled below */
				} else if ( psize <= 2 ) {
				    AddLineQueueX( " sub %r, 2", stackreg[ModuleInfo.Ofssize] );
				} else if ( IS_SIGNED( opnd.mem_type ) ) {
				    AddLineQueueX( " movsx %r, %s", T_EAX, fullparam );
				    *r0flags = R0_USED;
				    reg = T_EAX;
				} else {
				    AddLineQueue( " pushw 0" );
				}
			    } else
				AddLineQueue( " pushw 0" );

			} else {

			    if ( !(*r0flags & R0_X_CLEARED) ) {
				/* v2.11: extra check needed */
				if ( reg == T_AH || ( optype & OP_A ) )
				    asmerr( 2133 );
				AddLineQueueX( " xor %r, %r", T_AX, T_AX );
			    }
			    AddLineQueueX( " push %r", T_AX );
			    *r0flags = R0_USED | R0_H_CLEARED | R0_X_CLEARED;
			}
		    }

		    if ( asize == 1 ) {
			if ( ( reg >= T_AH && reg <= T_BH ) || psize != 1 ) {
			    if ( psize != 1 && ( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_386 ) {
				/* v2.10: consider signed type coercion! */
				AddLineQueueX( " mov%sx %r, %s", IS_SIGNED( opnd.mem_type ) ? "s" : "z",
					      regax[ModuleInfo.Ofssize], fullparam );
				*r0flags =  ( IS_SIGNED( opnd.mem_type ) ? R0_USED : R0_USED | R0_H_CLEARED );
			    } else {
				if ( reg != T_AL ) {
				    AddLineQueueX( " mov %r, %s", T_AL, fullparam );
				    *r0flags |= R0_USED;
				    *r0flags &= ~R0_X_CLEARED;
				}
				if ( psize != 1 ) /* v2.11: don't modify AH if paramsize is 1 */
				    if ( IS_SIGNED( opnd.mem_type ) ) {
					AddLineQueue( " cbw" );
					*r0flags &= ~( R0_H_CLEARED | R0_X_CLEARED );
				    } else if (!( *r0flags & R0_H_CLEARED )) {
					AddLineQueueX( " mov %r, 0", T_AH );
					*r0flags |= R0_H_CLEARED;
				    }
			    }
			    reg = regax[ModuleInfo.Ofssize];
			} else {
			    /* convert 8-bit to 16/32-bit register name */
			    if ( (( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_386) &&
				( psize == 4 || pushsize == 4 ) ) {
				reg = reg - T_AL + T_EAX;
			    } else
				reg = reg - T_AL + T_AX;
			}
		    }
		}
		AddLineQueueX( " push %r", reg );
		/* v2.05: don't change psize if > pushsize */
		if ( psize < pushsize )
		    /* v2.04: adjust psize ( for siz_vararg update ) */
		    psize = pushsize;

	    } else { /* constant value */

		/* v2.06: size check */
		if ( psize ) {
		    if ( opnd.kind == EXPR_FLOAT )
			asize = 4;
		    else if ( opnd.value64 <= 255 && opnd.value64 >= -255 )
			asize = 1;
		    else if ( opnd.value64 <= 65535 && opnd.value64 >= -65535 )
			asize = 2;
		    else if ( opnd.value64 <= maxintvalues[0] && opnd.value64 >= minintvalues[0] )
			asize = 4;
		    else
			asize = 8;
		    if ( psize < asize )
			asmerr( 2114, reqParam+1 );
		}
		asize = 2 << Ofssize;

		if ( psize < asize )  /* ensure that the default argsize (2,4,8) is met */
		    if ( psize == 0 && curr->sym.is_vararg ) {
			/* v2.04: push a dword constant in 16-bit */
			if ( asize == 2 &&
			    ( opnd.value > 0xFFFFL || opnd.value < -65535L ) )
			    psize = 4;
			else
			    psize = asize;
		    } else
			psize = asize;

		if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) < P_186 ) {
		    *r0flags |= R0_USED;
		    switch ( psize ) {
		    case 2:
			if ( opnd.value != 0 || opnd.kind == EXPR_ADDR ) {
			    AddLineQueueX( " mov %r, %s", T_AX, fullparam );
			} else {
			    if ( !(*r0flags & R0_X_CLEARED ) ) {
				AddLineQueueX( " xor %r, %r", T_AX, T_AX );
			    }
			    *r0flags |= R0_H_CLEARED | R0_X_CLEARED;
			}
			break;
		    case 4:
			if ( opnd.uvalue <= 0xFFFF )
			    AddLineQueueX( " xor %r, %r", T_AX, T_AX );
			else
			    AddLineQueueX( " mov %r, %r (%s)", T_AX, T_HIGHWORD, fullparam );
			AddLineQueueX( " push %r", T_AX );
			if ( opnd.uvalue != 0 || opnd.kind == EXPR_ADDR ) {
			    AddLineQueueX( " mov %r, %r (%s)", T_AX, T_LOWWORD, fullparam );
			} else {
			    *r0flags |= R0_H_CLEARED | R0_X_CLEARED;
			}
			break;
		    default:
			asmerr( 2114, reqParam+1 );
		    }
		    AddLineQueueX( " push %r", T_AX );
		} else { /* cpu >= 80186 */
		    char *instr = "";
		    char *suffix;
		    int qual = EMPTY;
		    if ( psize != pushsize ) {
			switch ( psize ) {
			case 2:
			    instr = "w";
			    break;
			case 6: /* v2.04: added */
			    /* v2.11: use pushw only for 16-bit target */
			    if ( Ofssize == USE16 )
				suffix = "w";
			    else if ( Ofssize == USE32 && CurrWordSize == 2 )
				suffix = "d";
			    else
				suffix = "";
			    AddLineQueueX( " push%s (%s) shr 32t", suffix, fullparam );
			    /* no break */
			case 4:
			    if (( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_386 )
				instr = "d";
			    else {
				AddLineQueueX( " pushw %r (%s)", T_HIGHWORD, fullparam );
				instr = "w";
				qual = T_LOWWORD;
			    }
			    break;
			case 8:
			    if (( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_64 )
				break;
			    /* v2.06: added support for double constants */
			    if ( opnd.kind == EXPR_CONST || opnd.kind == EXPR_FLOAT ) {
				AddLineQueueX( " pushd %r (%s)", T_HIGH32, fullparam );
				qual = T_LOW32;
				instr = "d";
				break;
			    }
			default:
			    asmerr( 2114, reqParam+1 );
			}
		    }
		    if ( qual != EMPTY )
			AddLineQueueX( " push%s %r (%s)", instr, qual, fullparam );
		    else
			AddLineQueueX( " push%s %s", instr, fullparam );
		}
	    }
	    if ( curr->sym.is_vararg ) {
		size_vararg += psize;
	    }
	}
    }
    return( NOT_ERROR );
}

/* generate a call for a prototyped procedure */

int InvokeDirective( int i, struct asm_tok tokenarray[] )
/************************************************************/
{
    struct asym *	sym;
    struct dsym *	proc;
    char *		p;
    int			numParam;
    int			value;
    int			size;
    int			parmpos;
    int			namepos;
    int			porder;
    uint_8		r0flags = 0;
    struct proc_info *	info;
    struct dsym *	curr;
    struct expr		opnd;
    char		buffer[MAX_LINE_LEN];

    i++; /* skip INVOKE directive */
    namepos = i;

    if ( ModuleInfo.aflag & _AF_ON ) {
	if ( ExpandHllProc( buffer, i, tokenarray ) == ERROR )
	    return ERROR;
	if (buffer[0] != 0) {
	    QueueTestLines( buffer );
	    RunLineQueue();
	    if ( Token_Count == 2 &&
		( !strcmp( tokenarray[1].string_ptr, "rax" ) ||
		  !strcmp( tokenarray[1].string_ptr, "eax" ) ||
		  !strcmp( tokenarray[1].string_ptr, "ax" ) ) )
		return NOT_ERROR;
	}
    }


    /* if there is more than just an ID item describing the invoke target,
     use the expression evaluator to get it
     */
    if ( tokenarray[i].token != T_ID || ( tokenarray[i+1].token != T_COMMA && tokenarray[i+1].token != T_FINAL ) ) {
	if ( ERROR == EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) )
	    return( ERROR );
	if ( opnd.type != NULL && opnd.type->state == SYM_TYPE ) {
	    sym = opnd.type;
	    proc = (struct dsym *)sym;
	    if ( sym->mem_type == MT_PROC ) /* added for v1.95 */
		goto isfnproto;
	    if ( sym->mem_type == MT_PTR )  /* v2.09: mem_type must be MT_PTR */
		goto isfnptr;
	}
	if ( opnd.kind == EXPR_REG ) {
	    if ( GetValueSp( opnd.base_reg->tokval ) & OP_RGT8 )
		sym = GetStdAssume( GetRegNo( opnd.base_reg->tokval ) );
	    else
		sym = NULL;
	} else
	    sym = ( opnd.mbr ? opnd.mbr : opnd.sym );

    } else {
	opnd.base_reg = NULL;
	sym = SymSearch( tokenarray[i].string_ptr );
	i++;
    }

    if( sym == NULL ) {
	/* v2.04: msg changed */
	return( asmerr( 2190 ) );
    }
    if( sym->isproc )  /* the most simple case: symbol is a PROC */
	;
    else if ( sym->mem_type == MT_PTR && sym->target_type && sym->target_type->isproc )
	sym = sym->target_type;
    else if ( sym->mem_type == MT_PTR && sym->target_type && sym->target_type->mem_type == MT_PROC ) {
	proc = (struct dsym *)sym->target_type;
	goto isfnproto;
    } else if ( ( sym->mem_type == MT_TYPE ) && ( sym->type->mem_type == MT_PTR || sym->type->mem_type == MT_PROC ) ) {
	/* second case: symbol is a (function?) pointer */
	proc = (struct dsym *)sym->type;
	if ( proc->sym.mem_type != MT_PROC )
	    goto isfnptr;
    isfnproto:
	/* pointer target must be a PROTO typedef */
	if ( proc->sym.mem_type != MT_PROC ) {
	    return( asmerr( 2190 ) );
	}
    isfnptr:
	/* get the pointer target */
	sym = proc->sym.target_type;
	if ( sym == NULL ) {
	    return( asmerr( 2190 ) );
	}
    } else {
	return( asmerr( 2190 ) );
    }
    proc = (struct dsym *)sym;
    info = proc->e.procinfo;

    /* get the number of parameters */

    for ( curr = info->paralist, numParam = 0 ; curr ; curr = curr->nextparam, numParam++ );

    if ( proc->sym.langtype == LANG_FASTCALL ) {
	fcscratch = 0;
	porder = fastcall_tab[ModuleInfo.fctype].invokestart( proc, numParam, i, tokenarray, &value );
    }

    curr = info->paralist;
    parmpos = i;

    if ( !( info->has_vararg ) ) {
	/* check if there is a superfluous parameter in the INVOKE call */
	if ( PushInvokeParam( i, tokenarray, proc, NULL, numParam, &r0flags ) != ERROR ) {
	    return( asmerr( 2136 ) );
	}
    } else {
	int j = (Token_Count - i) / 2;
	/* for VARARG procs, just push the additional params with
	 the VARARG descriptor
	*/
	numParam--;
	size_vararg = 0; /* reset the VARARG parameter size count */
	while ( curr && curr->sym.is_vararg == FALSE ) curr = curr->nextparam;
	for ( ; j >= numParam; j-- )
	    PushInvokeParam( i, tokenarray, proc, curr, j, &r0flags );
	/* move to first non-vararg parameter, if any */
	for ( curr = info->paralist; curr && curr->sym.is_vararg == TRUE; curr = curr->nextparam );
    }

    /* the parameters are usually stored in "push" order.
     * This if() must match the one in proc.c, ParseParams().
     */

    if ( sym->langtype == LANG_STDCALL ||
	sym->langtype == LANG_C ||
	( sym->langtype == LANG_FASTCALL && porder ) ||
	sym->langtype == LANG_SYSCALL ) {
	for ( ; curr ; curr = curr->nextparam ) {
	    numParam--;
	    if ( PushInvokeParam( i, tokenarray, proc, curr, numParam, &r0flags ) == ERROR ) {
		asmerr( 2033, numParam);//sym->name );
	    }
	}
    } else {
	for ( numParam = 0 ; curr && curr->sym.is_vararg == FALSE; curr = curr->nextparam, numParam++ ) {
	    if ( PushInvokeParam( i, tokenarray, proc, curr, numParam, &r0flags ) == ERROR ) {
		asmerr( 2033, numParam);//sym->name );
	    }
	}
    }

    /* v2.05 added. A warning only, because Masm accepts this. */
    if ( opnd.base_reg != NULL && Parse_Pass == PASS_1 &&
	(r0flags & R0_USED ) && opnd.base_reg->bytval == 0 )
	asmerr( 7002 );

    p = StringBufferEnd;
    strcpy( p, " call " );
    p += 6;

	if ( sym->state == SYM_EXTERNAL && sym->dll ) {
	    char *iatname = p;
	    strcpy( p, ModuleInfo.g.imp_prefix );
	    p += strlen( p );
	    p += Mangle( sym, p );
	    namepos++;
	    if ( sym->iat_used == FALSE ) {
		sym->iat_used = TRUE;
		sym->dll->cnt++;
		if ( sym->langtype != LANG_NONE && sym->langtype != ModuleInfo.langtype )
		    AddLineQueueX( " externdef %r %s: %r %r", sym->langtype + T_C - 1, iatname, T_PTR, T_PROC );
		else
		    AddLineQueueX( " externdef %s: %r %r", iatname, T_PTR, T_PROC );
	    }
	}
	size = tokenarray[parmpos].tokpos - tokenarray[namepos].tokpos;
	memcpy( p, tokenarray[namepos].tokpos, size );
	*(p+size) = NULLC;

    AddLineQueue( StringBufferEnd );

    if (( sym->langtype == LANG_C || sym->langtype == LANG_SYSCALL ) &&
	( info->parasize || ( info->has_vararg && size_vararg ) )) {
	if ( info->has_vararg ) {
	    AddLineQueueX( " add %r, %u", stackreg[ModuleInfo.Ofssize], NUMQUAL info->parasize + size_vararg );
	} else
	    AddLineQueueX( " add %r, %u", stackreg[ModuleInfo.Ofssize], NUMQUAL info->parasize );
    } else if ( sym->langtype == LANG_FASTCALL ) {
	fastcall_tab[ModuleInfo.fctype].invokeend( proc, numParam, value );
    }
    LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL );
    RunLineQueue();

    return( NOT_ERROR );
}

