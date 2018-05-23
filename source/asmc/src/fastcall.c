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

extern enum special_token stackreg[];
extern int size_vararg; /* size of :VARARG arguments */

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

static int fcscratch;  /* exclusively to be used by FASTCALL helper functions */

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
static	int elf64_fcstart( struct dsym const *, int, int, struct asm_tok[], int * );
static void elf64_fcend ( struct dsym const *, int, int );
static	int elf64_param ( struct dsym const *, int, struct dsym *, bool, struct expr *, char *, uint_8 * );
#define REGPAR_ELF64 0x03C6 /* regs 1, 2, 6, 7, 8 and 9 */
#define ELF64_START 1 /* elf64: RDI first param start at bit 6 */

struct fastcall_conv {
    int	 (* invokestart)( struct dsym const *, int, int, struct asm_tok[], int * );
    void (* invokeend)	( struct dsym const *, int, int );
    int	 (* handleparam)( struct dsym const *, int, struct dsym *, bool, struct expr *, char *, uint_8 * );
};

const struct fastcall_conv fastcall_tab[] = {
 { ms32_fcstart, ms32_fcend , ms32_param }, /* FCT_MSC */
 { watc_fcstart, watc_fcend , watc_param }, /* FCT_WATCOMC */
 { ms64_fcstart, ms64_fcend , ms64_param }, /* FCT_WIN64 */
 { elf64_fcstart, elf64_fcend, elf64_param }, /* FCT_ELF64 */
 { ms32_fcstart, ms32_fcend , ms32_param }, /* FCT_VEC32 */
 { ms64_fcstart, ms64_fcend , ms64_param }, /* FCT_VEC64 */
};

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

unsigned char elf64_regs[] = {
 T_DIL, T_SIL, T_DL,  T_CL,  T_R8B, T_R9B,
 T_DI,	T_SI,  T_DX,  T_CX,  T_R8W, T_R9W,
 T_EDI, T_ESI, T_EDX, T_ECX, T_R8D, T_R9D,
 T_RDI, T_RSI, T_RDX, T_RCX, T_R8,  T_R9
};

/* segment register names, order must match ASSUME_ enum */

static int ms32_fcstart( struct dsym const *proc, int numparams, int start,
	struct asm_tok tokenarray[], int *value )
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
{
    /* nothing to do */
    return;
}

static int ms32_param( struct dsym const *proc, int index, struct dsym *param, bool addr, struct expr *opnd, char *paramvalue, uint_8 *r0used )
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
{
    int size = 8;
    int args = 4;

    if ( proc->sym.langtype == LANG_VECTORCALL ) {
	size = 16;
	args = 6;
    }
    /* v2.04: VARARG didn't work */
    if ( proc->e.procinfo->has_vararg ) {
	for ( numparams = 0; tokenarray[start].token != T_FINAL; start++ )
	    if ( tokenarray[start].token == T_COMMA )
		numparams++;
    }
    if ( numparams < args )
	numparams = args;
    else if ( numparams & 1 )
	numparams++;
    size = args * size + ((numparams - args) ? (numparams - args) * 8: 0);
    *value = size;

    if ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) {
	if ( size > sym_ReservedStack->value )
	    sym_ReservedStack->value = size;
    } else
	AddLineQueueX( " sub %r, %d", T_RSP, size );
    /* since Win64 fastcall doesn't push, it's a better/faster strategy to
     * handle the arguments from left to right.
     */
    return( 0 );
}

static void ms64_fcend( struct dsym const *proc, int numparams, int value )
{
    /* use <value>, which has been set by ms64_fcstart() */
    if ( !( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) ) {
	if ( ModuleInfo.epilogueflags )
	    AddLineQueueX( " lea %r, [%r+%d]", T_RSP, T_RSP, value );
	else
	    AddLineQueueX( " add %r, %d", T_RSP, value );
    }
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

static int ms64_param( struct dsym const *proc, int index, struct dsym *param,
	bool addr, struct expr *opnd, char *paramvalue, uint_8 *regs_used )
{
    uint_32 size;
    uint_32 psize;
    int reg;
    int reg2;
    int i;
    int base;
    int offset;
    bool destroyed = FALSE;

    /* v2.11: default size is 32-bit, not 64-bit */
    /* v2.24: 64-bit if [reg].. */
    if ( param->sym.is_vararg ) {
	psize = 0;
	if ( addr || opnd->instr == T_OFFSET )
	    psize = 8;
	else if ( opnd->kind == EXPR_REG ) {
	    if ( opnd->indirect == FALSE )
		psize = SizeFromRegister( opnd->base_reg->tokval );
	    else
		psize = 8;
	} else if ( opnd->mem_type != MT_EMPTY )
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

    offset = index*8;
    if ( proc->sym.langtype == LANG_VECTORCALL && index < 6 )
	offset += offset;

    if ( index >= 4 && !( proc->sym.langtype == LANG_VECTORCALL &&
	 index < 6 && param->sym.mem_type == MT_REAL16 ) ) {

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
	    AddLineQueueX( " mov [%r+%u], %r", T_RSP, NUMQUAL offset, i );
	    return( 1 );
	}

	if ( opnd->kind == EXPR_CONST ||
	   ( opnd->kind == EXPR_ADDR && opnd->indirect == FALSE &&
	     opnd->mem_type == MT_EMPTY && opnd->instr != T_OFFSET ) ) {

	    /* v2.06: support 64-bit constants for params > 4 */
	    if ( psize == 8 &&
		( opnd->value64 > LONG_MAX || opnd->value64 < LONG_MIN ) ) {
		AddLineQueueX( " mov %r ptr [%r+%u], %r ( %s )", T_DWORD, T_RSP, NUMQUAL offset, T_LOW32, paramvalue );
		AddLineQueueX( " mov %r ptr [%r+%u+4], %r ( %s )", T_DWORD, T_RSP, NUMQUAL offset, T_HIGH32, paramvalue );

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
		AddLineQueueX( " mov %r ptr [%r+%u], %s", i, T_RSP, NUMQUAL offset, paramvalue );
	    }

	} else if ( opnd->kind == EXPR_FLOAT  ) {

	    if ( param->sym.mem_type == MT_REAL8 ) {
		AddLineQueueX( " mov %r ptr [%r+%u+0], %r (%s)", T_DWORD, T_RSP, NUMQUAL offset, T_LOW32, paramvalue );
		AddLineQueueX( " mov %r ptr [%r+%u+4], %r (%s)", T_DWORD, T_RSP, NUMQUAL offset, T_HIGH32, paramvalue );
	    } else
		AddLineQueueX( " mov %r ptr [%r+%u], %s", T_DWORD, T_RSP, NUMQUAL offset, paramvalue );

	} else { /* it's a register or variable */

	    if ( opnd->kind == EXPR_REG && opnd->indirect == FALSE ) {

		if ( proc->sym.langtype == LANG_VECTORCALL && index < 6 &&
		     param->sym.mem_type & MT_FLOAT )
			goto vector_0_5;

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
	    } else if ( opnd->kind != EXPR_REG || opnd->indirect == TRUE ) {
		if ( ( paramvalue[0] == '0' && paramvalue[1] == 0 ) ||
		     ( opnd->kind == EXPR_CONST && opnd->value == 0 ) )
		    AddLineQueueX(" xor %r, %r", i, i );
		else
		    AddLineQueueX( " mov %r, %s", i, paramvalue );
	    }
	    AddLineQueueX( " mov [%r+%u], %r", T_RSP, NUMQUAL offset, i );
	}

    } else if ( param->sym.mem_type == MT_REAL4 || param->sym.mem_type == MT_REAL8 ||
	       param->sym.mem_type == MT_REAL16 ) {

	vector_0_5:

	/* v2.04: check if argument is the correct XMM register already */
	if ( opnd->kind == EXPR_REG && opnd->indirect == FALSE ) {

	    if ( GetValueSp( reg ) & OP_XMM ) {
		if ( reg != T_XMM0 + index ) {

		    if ( reg >= T_XMM0 ) {
			if ( param->sym.mem_type == MT_REAL4 )
			    AddLineQueueX( " movss %r, %r", T_XMM0 + index, reg );
			else if ( param->sym.mem_type == MT_REAL8 )
			    AddLineQueueX( " movsd %r, %r", T_XMM0 + index, reg );
			else
			    AddLineQueueX( " movaps %r, %r", T_XMM0 + index, reg );
		    } else {
			if ( param->sym.mem_type == MT_REAL4 )
			    AddLineQueueX( " movd %r, %s", T_XMM0 + index, paramvalue );
			else
			    AddLineQueueX( " movq %r, %s", T_XMM0 + index, paramvalue );
		    }
		}
		return( 1 );
	    }
	}
	if ( opnd->kind == EXPR_FLOAT ) {

	    *regs_used |= R0_USED;
	    if ( param->sym.mem_type != MT_REAL8 ) {
		AddLineQueueX( " mov %r, %s", T_EAX, paramvalue );
		AddLineQueueX( " movd %r, %r", T_XMM0 + index, T_EAX );
	    } else {
		AddLineQueueX( " mov %r, %r ptr %s", T_RAX, T_REAL8, paramvalue );
		AddLineQueueX( " movq %r, %r", T_XMM0 + index, T_RAX );
	    }
	} else {
	    if ( param->sym.mem_type == MT_REAL4 )
		AddLineQueueX( " movd %r, %s", T_XMM0 + index, paramvalue );
	    else if ( param->sym.mem_type == MT_REAL8 )
		AddLineQueueX( " movq %r, %s", T_XMM0 + index, paramvalue );
	    else
		AddLineQueueX(" movaps %r, %s", T_XMM0 + index, paramvalue );
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

	if ( opnd->kind == EXPR_REG ) {
	    if ( opnd->indirect == FALSE ) {
		reg = opnd->base_reg->tokval;
		size = SizeFromRegister( reg );
	    } else {
		size = 8;
	    }
	} else if ( opnd->kind == EXPR_CONST || opnd->kind == EXPR_FLOAT ) {
	    if ( opnd->kind == EXPR_CONST && opnd->hvalue )
		psize = 8;
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
	else {
	    if ( ( paramvalue[0] == '0' && paramvalue[1] == 0 ) ||
		 ( opnd->kind == EXPR_CONST && opnd->value == 0 ) )
		AddLineQueueX( " xor %r, %r", ms64_regs[index+base], ms64_regs[index+base] );
	    else
		AddLineQueueX( " mov %r, %s", ms64_regs[index+base], paramvalue );
	}
	*regs_used |= ( 1 << ( index + RPAR_START ) );
    }
    return( 1 );
}

/* convert register number to param number: */

int GetParmIndexS( int x )
{
    switch ( x ) {
      case 1: return( 3 ); /* CX */
      case 2: return( 2 ); /* DX */
      case 8: return( 4 ); /* R8 */
      case 9: return( 5 ); /* R9 */
      case 6: return( 1 ); /* SI */
    }
    return( 0 ); /* DI */
}

static int elf64_fcstart( struct dsym const *proc, int numparams, int start,
	struct asm_tok tokenarray[], int *value )
{
    *value = 0;
    return( 0 );
}

static int elf64_param( struct dsym const *proc, int index, struct dsym *param,
	bool addr, struct expr *opnd, char *paramvalue, uint_8 *regs_used )
{
    uint_32 size;
    uint_32 psize;
    int reg;
    int i;
    int base;
    int destroyed = FALSE;

    if ( *paramvalue == 0 )
	return 1;

    /* v2.11: default size is 32-bit, not 64-bit */
    if ( param->sym.is_vararg ) {
	psize = 0;
	if ( addr || opnd->instr == T_OFFSET )
	    psize = 8;
	else if ( opnd->kind == EXPR_REG ) {
	    if ( opnd->indirect == FALSE )
		psize = SizeFromRegister( opnd->base_reg->tokval );
	    else
		psize = 8;
	} else if ( opnd->mem_type != MT_EMPTY )
	    psize = SizeFromMemtype( opnd->mem_type, USE64, opnd->type );
	if ( psize < 4 )
	    psize = 4;
    } else
	psize = SizeFromMemtype( param->sym.mem_type, USE64, param->sym.type );

    if ( param->sym.mem_type == MT_REAL4 || param->sym.mem_type == MT_REAL8 ||
	 param->sym.mem_type == MT_REAL16 ) {

	reg = opnd->base_reg->tokval;

	/* v2.04: check if argument is the correct XMM register already */

	if ( opnd->kind == EXPR_REG && opnd->indirect == FALSE ) {

	    if ( GetValueSp( reg ) & OP_XMM ) {
		if ( reg != T_XMM0 + index ) {

		    if ( reg >= T_XMM0 ) {
			if ( param->sym.mem_type == MT_REAL4 )
			    AddLineQueueX( " movss %r, %r", T_XMM0 + index, reg );
			else if ( param->sym.mem_type == MT_REAL8 )
			    AddLineQueueX( " movsd %r, %r", T_XMM0 + index, reg );
			else
			    AddLineQueueX( " movaps %r, %r", T_XMM0 + index, reg );
		    } else {
			if ( param->sym.mem_type == MT_REAL4 )
			    AddLineQueueX( " movd %r, %s", T_XMM0 + index, paramvalue );
			else
			    AddLineQueueX( " movq %r, %s", T_XMM0 + index, paramvalue );
		    }
		}
		return( 1 );
	    }
	}
	if ( opnd->kind == EXPR_FLOAT ) {

	    if ( param->sym.mem_type == MT_REAL4 ) {
		*regs_used |= R0_USED;
		AddLineQueueX( " mov %r, %s", T_EAX, paramvalue );
		AddLineQueueX( " movd %r, %r", T_XMM0 + index, T_EAX );
	    } else if ( param->sym.mem_type == MT_REAL8 ) {
		*regs_used |= R0_USED;
		AddLineQueueX( " mov %r, %r ptr %s", T_RAX, T_REAL8, paramvalue );
		AddLineQueueX( " movd %r, %r", T_XMM0 + index, T_RAX );
	    } else
		AddLineQueueX(" movaps %r, %r ptr %s", index + T_XMM0, T_REAL16, paramvalue );
	} else {
	    if ( param->sym.mem_type == MT_REAL4 )
		AddLineQueueX( " movd %r, %s", T_XMM0 + index, paramvalue );
	    else if ( param->sym.mem_type == MT_REAL8 )
		AddLineQueueX( " movq %r, %s", T_XMM0 + index, paramvalue );
	    else
		AddLineQueueX(" movaps %r, %s", T_XMM0 + index, paramvalue );
	}

    } else {

	base = 3*6;
	switch ( psize ) {
	case 1: base = 0;   break;
	case 2: base = 1*6; break;
	case 4: base = 2*6; break;
	}

	if ( addr ) {
	    if ( psize >= 4 )
		AddLineQueueX( " lea %r, %s", elf64_regs[index + base], paramvalue );
	    else
		asmerr( 2114, index+1 );
	    *regs_used |= ( 1 << ( index + RPAR_START ) );
	    return( 1 );
	}

	if ( opnd->kind == EXPR_REG ) {
	    if ( opnd->indirect == FALSE ) {
		reg = opnd->base_reg->tokval;
		size = SizeFromRegister( reg );
	    } else {
		size = 8;
	    }
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
	/* optimization if the register holds the value already */
	if ( opnd->kind == EXPR_REG && opnd->indirect == FALSE ) {
	    if ( GetValueSp( reg ) & OP_R ) {
		if ( elf64_regs[index+base] == reg ) {
		    return( 1 );
		}
		i = GetRegNo( reg );
		if ( REGPAR_ELF64 & ( 1 << i ) ) {
		    i = GetParmIndexS( i );
		    if ( *regs_used & ( 1 << ( i + ELF64_START ) ) )
			asmerr( 2133 );
		}
	    }
	}
	/* v2.11: allow argument extension */
	if ( size < psize )
	    if ( size == 4 ) {
		if ( IS_SIGNED( opnd->mem_type ) )
		    AddLineQueueX( " movsxd %r, %s", elf64_regs[index+base], paramvalue );
		else
		    AddLineQueueX( " mov %r, %s", elf64_regs[index+2*6], paramvalue );
	    } else
		AddLineQueueX( " mov%sx %r, %s", IS_SIGNED( opnd->mem_type ) ? "s" : "z", elf64_regs[index+base], paramvalue );
	else {
	    if ( ( paramvalue[0] == '0' && paramvalue[1] == 0 ) ||
		 ( opnd->kind == EXPR_CONST && opnd->value == 0 ) )
		AddLineQueueX( " xor %r, %r", elf64_regs[index+base], elf64_regs[index+base] );
	    else
		AddLineQueueX( " mov %r, %s", elf64_regs[index+base], paramvalue );
	}
	*regs_used |= ( 1 << ( index + ELF64_START ) );
    }
    return( 1 );
}

static void elf64_fcend( struct dsym const *proc, int numparams, int value )
{
    return;
}

/* get segment part of an argument
 * v2.05: extracted from PushInvokeParam(),
 * so it could be used by watc_param() as well.
 */

short GetSegmentPart( struct expr *opnd, char *buffer, const char *fullparam )
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
{
    return( 1 );
}

static void watc_fcend( struct dsym const *proc, int numparams, int value )
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
static int watc_param( struct dsym const *proc, int index, struct dsym *param,
	bool addr, struct expr *opnd, char *paramvalue, uint_8 *r0used )
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

void fastcall_init(void)
{
    fcscratch = 0;
}
