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
#include <quadmath.h>

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

#ifndef __ASMC64__
static	int ms32_fcstart( struct dsym const *, int, int, struct asm_tok[], int * );
static void ms32_fcend	( struct dsym const *, int, int );
static	int ms32_param	( struct dsym const *, int, struct dsym *, bool, struct expr *, char *, uint_8 * );
static	int vc32_fcstart( struct dsym const *, int, int, struct asm_tok[], int * );
static	int vc32_param	( struct dsym const *, int, struct dsym *, bool, struct expr *, char *, uint_8 * );
static	int watc_fcstart( struct dsym const *, int, int, struct asm_tok[], int * );
static void watc_fcend	( struct dsym const *, int, int );
static	int watc_param	( struct dsym const *, int, struct dsym *, bool, struct expr *, char *, uint_8 * );
#endif
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
#ifndef __ASMC64__
 { ms32_fcstart, ms32_fcend , ms32_param }, /* FCT_MSC */
 { watc_fcstart, watc_fcend , watc_param }, /* FCT_WATCOMC */
#else
 { 0, 0, 0 },
 { 0, 0, 0 },
#endif
 { ms64_fcstart, ms64_fcend , ms64_param }, /* FCT_WIN64 */
 { elf64_fcstart, elf64_fcend, elf64_param }, /* FCT_ELF64 */
#ifndef __ASMC64__
 { vc32_fcstart, ms32_fcend , vc32_param }, /* FCT_VEC32 */
#else
 { 0, 0, 0 },
#endif
 { ms64_fcstart, ms64_fcend , ms64_param }, /* FCT_VEC64 */
};

/* 16-bit MS fastcall uses up to 3 registers (AX, DX, BX )
 * and additional params are pushed in PASCAL order!
 */
#ifndef __ASMC64__
static const enum special_token ms16_regs[] = {
    T_AX, T_DX, T_BX
};
static const enum special_token ms32_regs[] = {
    T_ECX, T_EDX
};
#endif
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

unsigned char elf64_param_index[] = {
/* AX CX DX BX SP BP SI DI R8 R9 */
   0, 3, 2, 0, 0, 0, 1, 0, 4, 5, 0, 0, 0, 0, 0, 0
};

/* segment register names, order must match ASSUME_ enum */

#ifndef __ASMC64__
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

/* FCT_VEC32 */

static int vc32_fcstart( struct dsym const *proc, int numparams, int start,
	struct asm_tok tokenarray[], int *value )
{
    struct dsym *param;

    for ( param = proc->e.procinfo->paralist ; param ; param = param->nextparam )
	if ( param->sym.state == SYM_TMACRO ||
	   ( param->sym.state == SYM_STACK && param->sym.total_size <= 16 ) )
	    fcscratch++;
    return( 1 );
}

static int vc32_param( struct dsym const *proc, int index, struct dsym *param,
	bool addr, struct expr *opnd, char *paramvalue, uint_8 *r0used )
{
    int reg;

    if ( !( param->sym.state == SYM_TMACRO || param->sym.state == SYM_STACK ) ||
	( param->sym.state == SYM_STACK && param->sym.total_size > 16 ) )
	return( 0 );

    fcscratch--;
    if ( param->sym.state == SYM_STACK || fcscratch > 1 || param->sym.mem_type & MT_FLOAT ) {
	if ( fcscratch > 5 )
	    return 0;
	reg = fcscratch + T_XMM0;
    } else {
	if ( fcscratch > 1 )
	    return 0;
	reg = ms32_regs[fcscratch];
    }

    if ( addr )
	AddLineQueueX( " lea %r, %s", reg, paramvalue );
    else {

	int size;

	if ( reg < T_XMM0 && ( opnd->kind != EXPR_CONST ) &&
	    ( size = SizeFromMemtype( param->sym.mem_type, USE_EMPTY, param->sym.type ) ) < 4 ) {

	    if ( !size && opnd->kind == EXPR_REG && opnd->indirect == 0 && opnd->base_reg ) {

		if ( opnd->base_reg->tokval == reg )
		    return 0;
		AddLineQueueX( " mov %r, %s", reg, paramvalue );
	    } else
		AddLineQueueX( " %s %r, %s", ( param->sym.mem_type & MT_SIGNED ) ? "movsx" : "movzx", reg, paramvalue );

	} else {

	    if ( opnd->kind == EXPR_REG && opnd->indirect == 0 && opnd->base_reg ) {
		if ( opnd->base_reg->tokval == reg )
		    return( 1 );
	    }
	    if ( opnd->kind == EXPR_CONST ) {
		if ( index > 1 || reg >= T_XMM0 )
		    return 0;
		AddLineQueueX(" mov %r, %s", reg, paramvalue );
	    } else if ( opnd->kind == EXPR_FLOAT ) {
		if ( param->sym.mem_type == MT_REAL4 ) {
		    *r0used |= R0_USED;
		    AddLineQueueX( " mov %r, %s", T_EAX, paramvalue );
		    AddLineQueueX( " movd %r, %r", reg, T_EAX );
		} else if ( param->sym.mem_type == MT_REAL8 ) {
		    AddLineQueueX( " pushd %r (%s)", T_HIGH32, paramvalue );
		    AddLineQueueX( " pushd %r (%s)", T_LOW32, paramvalue );
		    AddLineQueueX( " movq %r, [esp]", reg );
		    AddLineQueue ( " add esp, 8" );
		} else
		    AddLineQueueX( " movaps %r, %s", reg, paramvalue );
	    } else {
		if ( param->sym.mem_type == MT_REAL4 )
		    AddLineQueueX(" movss %r, %s", reg, paramvalue );
		else if ( param->sym.mem_type == MT_REAL8 )
		    AddLineQueueX(" movsd %r, %s", reg, paramvalue );
		else if ( size == 16 )
		    AddLineQueueX(" movaps %r, %s", reg, paramvalue );
		else
		    return 0;
	    }
	}
    }
    if ( reg == T_AX )
	*r0used |= R0_USED;
    return( 1 );
}

#endif

int GetAccumulator(int size, uint_8 *regs)
{
    int i = T_RAX;
    switch ( size ) {
    case 1: i = T_AL;  break;
    case 2: i = T_AX;  break;
    case 4: i = T_EAX; break;
    }
    *regs |= R0_USED;
    return i;
}

int get_x32_regno(int reg)
{
    if ( reg >= T_RAX && reg <= T_RDI )
	return ( reg - ( T_RAX - T_EAX ) );
    if ( reg >= T_R8 && reg <= T_R15 )
	return ( reg - ( T_R8 - T_R8D ) );
    if ( ( reg >= T_AX && reg <= T_DI ) || ( reg >= T_R8W && reg <= T_R15W ) )
	return (reg + ( T_EAX - T_AX ) );
    if ( ( reg >= T_AL && reg <= T_BH ) || ( reg >= T_R8B && reg <= T_R15B ) )
	return (reg + ( T_EAX - T_AL ) );
    if ( reg >= T_SPL && reg <= T_DIL )
	return ( reg - ( T_SPL - T_ESP ) );
    return reg;
}

int get_x64_regno(int reg)
{
    reg = get_x32_regno(reg);
    if ( reg >= T_EAX && reg <= T_EDI )
	return ( reg + ( T_RAX - T_EAX ) );
    return ( reg + ( T_R8 - T_R8D ) );
}

static int GetPSize( int address, struct asym *param, struct expr *opnd )
{
    int psize;

    /* v2.11: default size is 32-bit, not 64-bit */

    if ( param->is_vararg ) {

	psize = 0;

	if ( address || opnd->inst == T_OFFSET )
	    psize = 8;
	else if ( opnd->kind == EXPR_REG ) {
	    if ( opnd->indirect == FALSE )
		psize = SizeFromRegister( opnd->base_reg->tokval );
	    else
		psize = 8;
	} else if ( opnd->kind == EXPR_FLOAT && opnd->mem_type == MT_REAL16 ) {
	} else if ( opnd->mem_type != MT_EMPTY )
	    psize = SizeFromMemtype( opnd->mem_type, USE64, opnd->type );

	if ( psize < 4 )
	    psize = 4;

    } else {
	psize = SizeFromMemtype( param->mem_type, USE64, param->type );
    }
    return psize;
}


static int ms64_fcstart( struct dsym const *proc, int numparams, int start, struct asm_tok tokenarray[], int *value )
{
    int i;
    int size = 8;
    int args = 4;
    struct dsym *sym;

    if ( proc->sym.langtype == LANG_VECTORCALL ) {
	size = 16;
	args = 6;
    }

    /* v2.29: reg::reg id to fcscratch */

    for ( i = start; tokenarray[i].token != T_FINAL; i++ ) {
	if ( tokenarray[i].token == T_REG && tokenarray[i+1].token == T_DBL_COLON ) {

	    i += 2;
	    fcscratch++;
	}
    }
    if ( fcscratch )
	fcscratch--;

    /* v2.04: VARARG didn't work */
    if ( proc->e.procinfo->has_vararg ) {
	for ( numparams = 0; tokenarray[start].token != T_FINAL; start++ )
	    if ( tokenarray[start].token == T_COMMA )
		numparams++;
    } else { /* v2.31.22: extend call stack to 6 * [32|64] */
	for ( sym = proc->e.procinfo->paralist; sym; sym = sym->prev ) {
	    if ( sym->sym.mem_type & MT_FLOAT || sym->sym.mem_type == MT_YWORD ||
		  ( args == 6 && sym->sym.mem_type == MT_OWORD ) ) {
		if ( size < sym->sym.total_size )
		    size = sym->sym.total_size;
	    }
	}
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

int CreateFloat(int, struct expr *, char *);

static int CheckXMM( int reg, int index, struct dsym *param, struct expr *opnd,
	char *paramvalue, uint_8 *regs_used )
{

    char buffer[64];
    uint_8 sign;
    char *p;
    int xmm; /* v2.31.04: xmm0..xmm31 */

    xmm = index + T_XMM0;

    /* v2.04: check if argument is the correct XMM register already */
    if ( opnd->kind == EXPR_REG && opnd->indirect == FALSE ) {
	sign = GetValueSp( reg );
	if ( sign & (OP_XMM | OP_YMM | OP_ZMM) ) {
	    if ( sign & OP_YMM )
		xmm = index + T_YMM0;
	    else if ( sign & OP_ZMM )
		xmm = index + T_ZMM0;
	    if ( reg != xmm ) {
		if ( reg < T_XMM16 && sign & OP_XMM ) {
		    if ( param->sym.mem_type == MT_REAL4 )
			AddLineQueueX( " movss %r, %r", xmm, reg );
		    else if ( param->sym.mem_type == MT_REAL8 )
			AddLineQueueX( " movsd %r, %r", xmm, reg );
		    else
			AddLineQueueX( " movaps %r, %r", xmm, reg );
		} else {
		    if ( param->sym.mem_type == MT_REAL4 )
			AddLineQueueX( " vmovss %r, %r, %r", xmm, xmm, reg );
		    else if ( param->sym.mem_type == MT_REAL8 )
			AddLineQueueX( " vmovsd %r, %r, %r", xmm, xmm, reg );
		    else
			AddLineQueueX( " vmovaps %r, %r", xmm, reg );
		}
	    }
	    return( 1 );
	}
    }

    if ( opnd->kind == EXPR_FLOAT ) {

	if ( opnd->hlvalue == 0 && opnd->llvalue == 0 ) {

	    AddLineQueueX( " xorps %r, %r", xmm, xmm );
	    return 1;
	}

	if ( param->sym.mem_type == MT_REAL10 || param->sym.mem_type == MT_REAL16 ) {

	    reg = 10;
	    if ( param->sym.mem_type == MT_REAL16 )
		reg = 16;
	    CreateFloat( reg, opnd, buffer );
	    if ( reg == 10 )
		AddLineQueueX( " movaps %r, xmmword ptr %s", xmm, buffer );
	    else
		AddLineQueueX( " movaps %r, %s", xmm, buffer );
	    return 1;
	}

	*regs_used |= R0_USED;
	if ( param->sym.mem_type == MT_REAL2 ) {
	    AddLineQueueX( " mov %r, %s", T_AX, paramvalue );
	    AddLineQueueX( " movd %r, %r", xmm, T_EAX );
	} else if ( param->sym.mem_type == MT_REAL4 ) {
	    AddLineQueueX( " mov %r, %s", T_EAX, paramvalue );
	    AddLineQueueX( " movd %r, %r", xmm, T_EAX );
	} else if ( param->sym.mem_type == MT_REAL8 ) {
	    AddLineQueueX( " mov %r, %r ptr %s", T_RAX, T_REAL8, paramvalue );
	    AddLineQueueX( " movq %r, %r", xmm, T_RAX );
	}
    } else {
	if ( param->sym.mem_type == MT_REAL2 ) {
	    *regs_used |= R0_USED;
	    AddLineQueueX( " movzx %r, word ptr %s", T_EAX, paramvalue );
	    AddLineQueueX( " movd %r, %r", xmm, T_EAX );
	} else if ( param->sym.mem_type == MT_REAL4 )
	    AddLineQueueX( " movd %r, %s", xmm, paramvalue );
	else if ( param->sym.mem_type == MT_REAL8 )
	    AddLineQueueX( " movq %r, %s", xmm, paramvalue );
	else
	    AddLineQueueX( " movaps %r, %s", xmm, paramvalue );
    }
    return 1;
}

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
    int reg_64;
    int reg2;
    int m3;
    int i;
    int i32;
    int base;
    int offset;
    struct dsym *d;
    bool destroyed = FALSE;
    bool vector_call = ( proc->sym.langtype == LANG_VECTORCALL );

    /* v2.11: default size is 32-bit, not 64-bit */
    /* v2.24: 64-bit if [reg].. */

    psize = GetPSize( addr, (struct asym *)param, opnd );

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
    if ( opnd->kind == EXPR_ADDR &&  opnd->idx_reg != NULL ) {
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

    index += fcscratch;
    offset = index*8;
    if ( vector_call && index < 6 )
	offset += offset;

    if ( param->sym.mem_type == MT_ABS ) {
	for ( d = proc->e.procinfo->paralist; index; index-- )
	    d = d->nextparam;
	d->sym.string_ptr = LclAlloc( strlen(paramvalue) + 1);
	strcpy(d->sym.string_ptr, paramvalue);
	return 1;
    }

    if ( index >= 4 && ( addr || psize > 8 ) ) {

	if ( psize == 4 ) {
	    i = T_EAX;
	} else {
	    if ( psize < 8 ) {
		asmerr( 2114, index+1 );
	    } else if ( vector_call && index < 6 && ( param->sym.mem_type & MT_FLOAT ||
		    param->sym.mem_type == MT_YWORD || param->sym.mem_type == MT_OWORD ) ) {
		return CheckXMM( reg, index, param, opnd, paramvalue, regs_used );
	    }
	    i = T_RAX;
	}
	*regs_used |= R0_USED;

	/* v2.31.24 xmm to r64 -- vararg */

	if ( psize == 16 && ( GetValueSp(reg) & OP_XMM ) )
	    AddLineQueueX( " movq %r, %r", i, reg );
	else
	    AddLineQueueX( " lea %r, %s", i, paramvalue );

	AddLineQueueX( " mov [%r+%u], %r", T_RSP, NUMQUAL offset, i );
	return( 1 );
    }

    if ( index >= 4 ) {

	if ( opnd->kind == EXPR_CONST ||
	   ( opnd->kind == EXPR_ADDR && opnd->indirect == FALSE &&
	     opnd->mem_type == MT_EMPTY && opnd->inst != T_OFFSET ) ) {

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

	    if ( vector_call && index < 6 && ( param->sym.mem_type & MT_FLOAT ||
		 param->sym.mem_type == MT_YWORD || param->sym.mem_type == MT_OWORD ) )
		return CheckXMM( reg, index, param, opnd, paramvalue, regs_used );

	    if ( param->sym.mem_type != MT_REAL4 ) {
		AddLineQueueX( " mov %r ptr [%r+%u+0], %r (%s)", T_DWORD, T_RSP, NUMQUAL offset, T_LOW32, paramvalue );
		AddLineQueueX( " mov %r ptr [%r+%u+4], %r (%s)", T_DWORD, T_RSP, NUMQUAL offset, T_HIGH32, paramvalue );
	    } else
		AddLineQueueX( " mov %r ptr [%r+%u], %s", T_DWORD, T_RSP, NUMQUAL offset, paramvalue );

	} else { /* it's a register or variable */

	    if ( opnd->kind == EXPR_REG && opnd->indirect == FALSE ) {

		if ( vector_call && index < 6 && ( param->sym.mem_type & MT_FLOAT ||
			param->sym.mem_type == MT_YWORD || param->sym.mem_type == MT_OWORD ) )
		    return CheckXMM( reg, index, param, opnd, paramvalue, regs_used );

		size = SizeFromRegister( reg );
		if ( size == psize )
		    i = reg;
		else {
		    if ( size > psize || ( size < psize && param->sym.mem_type == MT_PTR ) ) {
			/* added in v2.31.25 */
			if ( size > psize && size == 16 && param->sym.mem_type & MT_FLOAT ) {
			    if ( psize == 4 )
				AddLineQueueX( " movss [%r+%u], %r", T_RSP, offset, reg );
			    else
				AddLineQueueX( " movsd [%r+%u], %r", T_RSP, offset, reg );
			    return 1;
			}
			asmerr( 2114, index+1 );
			psize = size;
		    }
		    i = GetAccumulator( psize, regs_used );
		}
	    } else {
		if ( opnd->mem_type == MT_EMPTY ) {
		    /* added v2.31.25 */
		    size = 4;
		    if ( opnd->inst == T_OFFSET || ( psize == 8 && param->sym.mem_type == MT_PTR )  )
			size = 8;
		} else
		    size = SizeFromMemtype( opnd->mem_type, USE64, opnd->type );
		i = GetAccumulator( psize, regs_used );
	    }

	    /* v2.11: no expansion if target type is a pointer */

	    i32 = get_x32_regno(i);

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
		    AddLineQueueX(" xor %r, %r", i32, i32 );
		else if ( opnd->kind == EXPR_CONST && opnd->hvalue == 0 )
		    AddLineQueueX( " mov %r, %s", i32, paramvalue );
		else
		    AddLineQueueX( " mov %r, %s", i, paramvalue );
	    }
	    AddLineQueueX( " mov [%r+%u], %r", T_RSP, NUMQUAL offset, i );
	}

    } else if ( param->sym.mem_type & MT_FLOAT || param->sym.mem_type == MT_YWORD ||
	    ( param->sym.mem_type == MT_OWORD && vector_call ) ) {

	/* register argument? */

	reg = 0;
	if ( opnd->kind == EXPR_REG && opnd->indirect == FALSE )
	    reg = opnd->base_reg->tokval;

	return CheckXMM( reg, index, param, opnd, paramvalue, regs_used );

    } else {

	reg_64 = 0;
	if ( opnd->kind == EXPR_REG && !opnd->indirect ) {

	    if ( opnd->base_reg[1].token == T_DBL_COLON ) {

		/* case <reg>::<reg> */

		reg_64 = opnd->base_reg[2].tokval;
		if ( fcscratch )
		    fcscratch--;
	    }
	}

	if ( addr || ( !reg_64 && psize > 8 ) ) { /* psize > 8 shouldn't happen! */
	    if ( psize >= 4 ) {
		if ( psize == 16 && ( GetValueSp(reg) & OP_XMM ) )
		    /* v2.31.24 xmm to r64 -- vararg */
		    AddLineQueueX( " movq %r, %r", ms64_regs[index+3*4], reg );
		else
		    AddLineQueueX( " lea %r, %s", ms64_regs[index+2*4+(psize > 4 ? 4 : 0)], paramvalue );
	    } else
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
	} else if ( opnd->kind == EXPR_ADDR && ( !opnd->sym || opnd->sym->state == SYM_UNDEFINED ) ) {
	    size = psize;
	} else
	    size = ( opnd->inst == T_OFFSET ? 8 : 4 );

	if ( size > psize || ( size < psize && param->sym.mem_type == MT_PTR ) ) {
	    asmerr( 2114, index+1 );
	}
	m3 = 0; /* added 2.29 */
	switch ( psize ) {
	case 1: base =	0*4; break;
	case 2: base =	1*4; break;
	case 3: m3++;
	case 4: base =	2*4; break;
	case 5:
	case 6:
	case 7: m3++;
	default:
	    base = 3*4; break;
	}
	i = ms64_regs[index+base];
	i32 = get_x32_regno(i);

	/* optimization if the register holds the value already */
	if ( opnd->kind == EXPR_REG && opnd->indirect == FALSE ) {
	    if ( GetValueSp( reg ) & OP_R ) {

		if ( reg_64 ) {
		    if ( i != reg_64 )
			AddLineQueueX( " mov %r, %r", i, reg_64 );
		    i = ms64_regs[index+3*4+1];
		    if ( i != reg )
			AddLineQueueX( " mov %r, %r", i, reg );
		    return( 1 );
		}

		if ( i == reg ) {
		    return( 1 );
		}
		base = GetRegNo( reg );
		if ( REGPAR_WIN64 & ( 1 << base ) ) {
		    base = GetParmIndex( base );
		    if ( *regs_used & ( 1 << ( base + RPAR_START ) ) )
			asmerr( 2133 );
		}
	    }
	}
	/* v2.11: allow argument extension */
	if ( size < psize )
	    if ( size == 4 ) {
		if ( IS_SIGNED( opnd->mem_type ) )
		    AddLineQueueX( " movsxd %r, %s", i, paramvalue );
		else
		    AddLineQueueX( " mov %r, %s", i32, paramvalue );
	    } else
		AddLineQueueX( " mov%sx %r, %s", IS_SIGNED( opnd->mem_type ) ? "s" : "z", i, paramvalue );
	else {

	    if ( ( paramvalue[0] == '0' && paramvalue[1] == 0 ) ||
		 ( opnd->kind == EXPR_CONST && opnd->value == 0 ) )

		AddLineQueueX( " xor %r, %r", i32, i32 );

	    else if ( opnd->kind == EXPR_CONST && opnd->hvalue == 0 ) {

		AddLineQueueX( " mov %r, %s", i32, paramvalue );

	    } else if ( m3 && opnd->kind == EXPR_ADDR ) { /* added v2.29 */

		*regs_used |= R0_USED;
		if ( size == 3 ) {

		    if ( i32 >= T_EAX && i32 <= T_EDI )
			i = i32 - (T_EAX - T_AL);
		    else
			i = i32 - (T_R8D - T_R8B);

		    AddLineQueueX( " mov %r, byte ptr %s[2]", i, paramvalue );
		    AddLineQueueX( " shl %r, 16", i32 );
		    if ( i32 >= T_EAX && i32 <= T_EDI )
			i32 -= (T_EAX - T_AX);
		    else
			i32 -= (T_R8D - T_R8W);
		    AddLineQueueX( " mov %r, word ptr %s", i32, paramvalue );
		} else {
		    AddLineQueueX(" mov %r, dword ptr %s", i32, paramvalue );
		    if ( size == 5 )
			AddLineQueueX( " mov al, byte ptr %s[4]", paramvalue );
		    else if ( size == 6 )
			AddLineQueueX( " mov ax, word ptr %s[4]", paramvalue );
		    else {
			AddLineQueueX( " mov al, byte ptr %s[6]", paramvalue );
			AddLineQueueX( " shl eax,16" );
			AddLineQueueX( " mov ax, word ptr %s[4]", paramvalue );
		    }
		    AddLineQueueX( " shl rax,32" );
		    AddLineQueueX( " or  %r,rax", i32 );
		}
	    } else {
		if ( opnd->kind == EXPR_FLOAT ) /* added v2.31 */
		    i = ms64_regs[index+3*4];
		AddLineQueueX( " mov %r, %s", i, paramvalue );
	    }
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

int elf64_pcheck( struct dsym *proc, struct dsym *paranode, int *used )
{
    char regname[32];
    int reg, x;
    int size = SizeFromMemtype( paranode->sym.mem_type, paranode->sym.Ofssize, paranode->sym.type );

    if ( paranode->sym.is_vararg ) {
	paranode->sym.string_ptr = NULL;
	return(0);
    }

    x = *used & 0xFF;
    if ( paranode->sym.mem_type & MT_FLOAT || paranode->sym.mem_type == MT_YWORD ) {
	 x = (*used) >> 8;
	 *used += 0x100;
	 if ( x > 7 ) {
	    paranode->sym.regist[1] = x;
	    paranode->sym.regist[0] = x + (T_XMM8 - T_XMM7 - 1);
	    paranode->sym.string_ptr = NULL;
	    return(0);
	 }
	 if ( size == 64 )
	    reg = T_ZMM0 + x;
	 else if ( size == 32 )
	    reg = T_YMM0 + x;
	 else
	    reg = T_XMM0 + x;
    } else if ( size > 16 ) {
	paranode->sym.string_ptr = NULL;
	return(0);
    } else if ( size == 16 || paranode->sym.mem_type == MT_OWORD ) {
	 if ( x < 5 ) {
	    reg = elf64_regs[x+18];
	    *used += 2;
	 } else {
	    paranode->sym.regist[0] = T_RAX;
	    paranode->sym.regist[1] = x;
	    (*used)++;
	    paranode->sym.string_ptr = NULL;
	    return(0);
	 }
    } else if ( x > 5 ) {
	paranode->sym.regist[0] = T_RAX;
	paranode->sym.regist[1] = x;
	(*used)++;
	paranode->sym.string_ptr = NULL;
	return(0);
    } else {
	(*used)++;
	switch ( size ) {
	case 1:	 reg = elf64_regs[x];	 break;
	case 2:	 reg = elf64_regs[x+6];	 break;
	case 4:	 reg = elf64_regs[x+12]; break;
	default: reg = elf64_regs[x+18]; break;
	}
    }
    paranode->sym.state = SYM_TMACRO;
    paranode->sym.regist[0] = reg;
    paranode->sym.regist[1] = x;
    GetResWName( reg, regname );
    paranode->sym.string_ptr = (char *)LclAlloc( strlen( regname ) + 1 );
    strcpy( paranode->sym.string_ptr, regname );
    return( 1 );
}

/* added v2.31 */
static int *elf64_valptr = NULL;

static int elf64_fcstart( struct dsym const *proc, int numparams, int start,
	struct asm_tok tokenarray[], int *value )
{
    struct dsym *p;
    struct asym *sym;
    int i;
    int reg_params = 0;
    int xmm_params = 0;

    if ( proc->e.procinfo->has_vararg ) {
	/* v2.28: xmm id to fcscratch */
	for (; tokenarray[start].token != T_FINAL; start++ ) {
	    if ( tokenarray[start].token == T_REG ) {
		if ( GetValueSp( tokenarray[start].tokval ) & OP_XMM )
		    fcscratch++;
	    } else if ( tokenarray[start].token == T_ID ) {
		sym = SymFind( tokenarray[start].string_ptr );
		if ( sym && ( sym->mem_type & MT_FLOAT ) )
		    fcscratch++;
	    } else if ( tokenarray[start].token == T_COMMA )
		reg_params++; /* added v2.31 */
	}
	reg_params -= fcscratch;
	xmm_params = fcscratch;
    } else {
	for ( p = proc->e.procinfo->paralist; p; p = p->prev ) {
	    if ( p->sym.mem_type & MT_FLOAT || p->sym.mem_type == MT_YWORD )
		xmm_params++;
	    else
		reg_params++;
	}
    }
    i = 0;
    if ( reg_params > 6 )
	i = reg_params - 6;
    if ( xmm_params > 8 ) {
	i += (xmm_params - 8);
	xmm_params = 8;
    }
    if ( i & 1 && ModuleInfo.win64_flags & W64F_AUTOSTACKSP )
	elf64_valptr = value;
    *value = i;
    return( xmm_params );
}

static int elf64_32( int reg )
{
    if ( reg >= T_RAX && reg <= T_RDI )
	reg -= ( T_RAX - T_EAX );
    else if ( reg >= T_R8 && reg <= T_R15 )
	reg -= ( T_R8 - T_R8D );
    return reg;
}

static void elf64_const( int reg, int pos, uint_64 val, char *paramvalue, int negative )
{
    int i;

    if ( val <= 0xFFFFFFFF ) {
	i = elf64_32( reg );
	if ( (int)val == 0 ) {
	    if ( negative )
		AddLineQueueX( " mov %r, -1", reg );
	    else
		AddLineQueueX( " xor %r, %r", i, i );
	} else
	    AddLineQueueX( " mov %r, %s", i, paramvalue );
    } else
	AddLineQueueX( " mov %r, %r %s", reg, pos, paramvalue );
}

static int elf64_param( struct dsym const *proc, int index, struct dsym *param,
	bool addr, struct expr *opnd, char *paramvalue, uint_8 *regs_used )
{
    uint_32 size;
    uint_32 psize;
    int reg;
    int i32;
    int i;
    int base;
    int stack = FALSE; /* added v2.31 */
    int destroyed = FALSE;
    int regno;
    struct asym *sym;
    struct dsym *d;

    if ( *paramvalue == 0 )
	return 1;

    /* v2.31 - align 16 if arg count is odd.. */

    if ( elf64_valptr ) {

	(*elf64_valptr)++;
	elf64_valptr = NULL;
	AddLineQueueX( " sub %r, 8", T_RSP );
    }

    psize = GetPSize( addr, (struct asym *)param, opnd );

    /* v2.11: default size is 32-bit, not 64-bit */

    if ( param->sym.is_vararg ) {

	if ( fcscratch && ( psize == 16 || opnd->mem_type & MT_FLOAT ) ) {
	    fcscratch--;
	    index = fcscratch;
	    i = index + T_XMM0;
	} else {
	    index = index - fcscratch;
	    if ( index < 6 ) {
		base = 3*6;
		switch ( psize ) {
		 case 1: base = 0; break;
		 case 2: base = 1*6; break;
		 case 4: base = 2*6; break;
		}
		i = elf64_regs[index+base];
	    } else
		stack = TRUE;
	}
    } else {
	i = param->sym.regist[0];
	index = param->sym.regist[1];
    }

    sym = (struct asym *)param;
    if ( sym->mem_type == MT_ABS ) {
	for ( d = proc->e.procinfo->paralist; index; index-- )
	    d = d->nextparam;
	d->sym.string_ptr = LclAlloc( strlen(paramvalue) + 1);
	strcpy(d->sym.string_ptr, paramvalue);
	return 1;
    }

    if ( sym->mem_type == MT_EMPTY && sym->is_vararg &&
	 opnd->kind == EXPR_ADDR && ( opnd->mem_type & MT_FLOAT ) ) {
	 if ( !( sym = SymFind( paramvalue ) ) )
	    sym = (struct asym *)param;
    }

    if ( !( sym->mem_type & MT_FLOAT || sym->mem_type == MT_YWORD ) && index >= 6 ) {

	if ( stack == FALSE )
	    return 0;

	i = T_RAX;
    }

    if ( sym->mem_type & MT_FLOAT || sym->mem_type == MT_YWORD ) {

	i = 0;
	if ( opnd->base_reg )
	    i = opnd->base_reg->tokval;

	if ( index < 8 )
	    return CheckXMM( i, index, (struct dsym *)sym, opnd, paramvalue, regs_used );
	else
	    stack++;
    }

    i32 = get_x32_regno(i);

    if ( addr ) {
	//if ( psize >= 4 ) {
	if ( SizeFromRegister(i) == 8 ) {

	    AddLineQueueX( " lea %r, %s", i, paramvalue );
	    if ( stack == TRUE ) {
		AddLineQueueX( " push %r", i );
		*regs_used |= R0_USED;
		return( 1 );
	    }
	} else
	    asmerr( 2114, index + 1 );
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
    } else if ( opnd->kind == EXPR_CONST ) {
	if ( opnd->hvalue && opnd->hvalue != -1 )
	    psize = 8;
	size = psize;
    } else if ( opnd->kind == EXPR_FLOAT ) {
	size = psize;
    } else if ( opnd->mem_type != MT_EMPTY ) {
	size = SizeFromMemtype( opnd->mem_type, USE64, opnd->type );
    } else if ( opnd->kind == EXPR_ADDR && opnd->sym->state == SYM_UNDEFINED ) {
	size = psize;
    } else
	size = ( opnd->inst == T_OFFSET ? 8 : 4 );

    if ( size == 16 && stack && opnd->kind == EXPR_REG ) {
	AddLineQueueX( " lea rsp,[rsp-8]" );
	if ( reg < T_XMM16 ) {
	    if ( param->sym.mem_type == MT_REAL8 )
		AddLineQueueX(" movsd [rsp], %s", paramvalue );
	    else
		AddLineQueueX(" movss [rsp], %s", paramvalue );
	} else
	    AddLineQueueX( " vmovq [rsp], %s", paramvalue );
	return( 1 );
    } else if ( size > psize || ( size < psize && param->sym.mem_type == MT_PTR ) ) {
	asmerr( 2114, index+1 );
    }

    /* optimization if the register holds the value already */

    if ( opnd->kind == EXPR_REG && opnd->indirect == FALSE ) {

	if ( GetValueSp( reg ) & OP_XMM ) {

	    CheckXMM( opnd->base_reg->tokval, index, param, opnd, paramvalue, regs_used );
	    return 1;

	} else if ( GetValueSp( reg ) & OP_R ) {

	    regno = GetRegNo(reg);
	    if ( REGPAR_ELF64 & ( 1 << regno ) ) {
		if ( *regs_used & ( 1 << ( elf64_param_index[regno] + ELF64_START ) ) )
		    destroyed = TRUE;
	    } else if ( (*regs_used & R0_USED ) && ( ( GetValueSp( reg ) & OP_A ) || reg == T_AH ) ) {
		destroyed = TRUE;
	    }
	    if ( destroyed ) {
		asmerr( 2133 );
		*regs_used = 0;
	    }

	    /* case <reg>::<reg> */

	    if ( psize == 16 && size == 8 && opnd->base_reg[1].token == T_DBL_COLON ) {

		if ( i != opnd->base_reg[2].tokval )
		    AddLineQueueX( " mov %r, %r", i, opnd->base_reg[2].tokval );
		i = elf64_regs[index+3*6+1];
		if ( i != reg )
		    AddLineQueueX( " mov %r, %r", i, reg );

		return( 1 );
	    }

	    if ( stack == TRUE ) {

		AddLineQueueX( " push %r", get_x64_regno(reg) );
		return( 1 );
	    }

	    if ( i == reg ) {
		return( 1 );
	    }
	    if ( opnd->mem_type == MT_EMPTY ) {

		/* get type info (signed) */
		opnd->mem_type = param->sym.mem_type;
	    }
	    base = GetRegNo( reg );
	    if ( REGPAR_ELF64 & ( 1 << base ) ) {
		base = GetParmIndexS( base );
		if ( *regs_used & ( 1 << ( base + ELF64_START ) ) )
			asmerr( 2133 );
	    }
	}
    }
    /* v2.11: allow argument extension */
    if ( size < psize ) {
	if ( size == 4 ) {
	    if ( IS_SIGNED( opnd->mem_type ) ) {
		AddLineQueueX( " movsxd %r, %s", i, paramvalue );
	    } else {
		AddLineQueueX( " mov %r, %s", i32, paramvalue );
	    }
	} else {
	    AddLineQueueX( " mov%sx %r, %s",
		IS_SIGNED( opnd->mem_type ) ? "s" : "z", i32, paramvalue );
	}

	if ( stack == TRUE ) {
	    AddLineQueueX( " push %r", i );
	    *regs_used |= R0_USED;
	    return 1;
	}

    } else {

	if ( stack == TRUE ) {

	    if ( opnd->kind == EXPR_FLOAT ) {

		*regs_used |= R0_USED;
		reg = T_RAX;
		if ( param->sym.mem_type == MT_REAL2 )
		    reg = T_AX;
		else if ( param->sym.mem_type == MT_REAL4 )
		    reg = T_EAX;
		AddLineQueueX(" mov %r, %s", reg, paramvalue );
		AddLineQueueX(" push %r", T_RAX );
	    } else
		AddLineQueueX( " push %s", paramvalue );
	    return 1;
	}

	if ( ( paramvalue[0] == '0' && paramvalue[1] == 0 ) ||
	     ( opnd->kind == EXPR_CONST && opnd->value == 0 ) ) {

	    AddLineQueueX( " xor %r, %r", i32, i32 );
	    if ( size == 16 ) {
		i = elf64_regs[index + 3 * 6 + 1];
		if ( opnd->hlvalue == 0 ) {
		    i = elf64_regs[index + 2 * 6 + 1];
		    AddLineQueueX( " xor %r, %r", i, i );
		} else
		    elf64_const( i, T_HIGH64, opnd->hlvalue, paramvalue, opnd->negative );
	    }

	} else if ( opnd->kind == EXPR_CONST && opnd->hvalue == 0 ) {

	    AddLineQueueX( " mov %r, %s", i32, paramvalue );
	    if ( size == 16 ) {
		i = elf64_regs[index + 3 * 6 + 1];
		elf64_const( i, T_HIGH64, opnd->hlvalue, paramvalue, opnd->negative );
	    }

	} else if ( size == 16 ) {

	    reg = elf64_regs[index + 3 * 6 + 1];
	    if ( opnd->kind == EXPR_CONST ) {
		elf64_const( i, T_LOW64, opnd->llvalue, paramvalue, 0 );
		elf64_const( reg, T_HIGH64, opnd->hlvalue, paramvalue, opnd->negative );
	    } else {
		AddLineQueueX( " mov %r, qword ptr %s", i, paramvalue );
		AddLineQueueX( " mov %r, qword ptr %s[8]", reg, paramvalue );
	    }
	} else {

	    if ( opnd->kind == EXPR_FLOAT && param->sym.is_vararg ) /* added v2.31 */
		i = elf64_regs[index + 3 * 6];

	    AddLineQueueX( " mov %r, %s", i, paramvalue );
	}
    }
    *regs_used |= ( 1 << ( index + ELF64_START ) );
    return( 1 );
}

static void elf64_fcend( struct dsym const *proc, int numparams, int value )
{
    if ( value )
	AddLineQueueX( " add rsp, %u*8", value );
}

/* get segment part of an argument
 * v2.05: extracted from PushInvokeParam(),
 * so it could be used by watc_param() as well.
 */
#ifndef __ASMC64__
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

#endif

void fastcall_init(void)
{
    fcscratch = 0;
}
