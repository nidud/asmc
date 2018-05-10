/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	Processing of PROC/ENDP/LOCAL directives.
*
****************************************************************************/

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <segment.h>
#include <extern.h>
#include <equate.h>
#include <fixup.h>
#include <label.h>
#include <input.h>
#include <lqueue.h>
#include <tokenize.h>
#include <expreval.h>
#include <types.h>
#include <condasm.h>
#include <macro.h>
#include <proc.h>
#include <fastpass.h>
#include <listing.h>
#include <posndir.h>
#include <reswords.h>
#include <win64seh.h>

#define NUMQUAL

/* STACKPROBE: emit a conditional "call __chkstk" inside the prologue
 * if stack space that is to be allocated exceeds 1000h bytes.
 * this is currently implemented for 64-bit only,
 * if OPTION FRAME:AUTO is set and the procedure has the FRAME attribute.
 * it's not active by default because, in a few cases, the listing might get messed.
 */
#define STACKPROBE 0

extern const char szDgroup[];
extern uint_32 list_pos;  /* current LST file position */

/*
 * Masm allows nested procedures
 * but they must NOT have params or locals
 */

/*
 * calling convention FASTCALL supports:
 * - Watcom C: registers e/ax,e/dx,e/bx,e/cx
 * - MS fastcall 16-bit: registers ax,dx,bx (default for 16bit)
 * - MS fastcall 32-bit: registers ecx,edx (default for 32bit)
 * - Win64: registers rcx, rdx, r8, r9 (default for 64bit)
 */

struct dsym		*CurrProc;	/* current procedure */
int			procidx;	/* procedure index */

static struct proc_info *ProcStack;

/* v2.11: ProcStatus replaced DefineProc */
enum proc_status ProcStatus;

static bool		endprolog_found;
static uint_8		unw_segs_defined;
static UNWIND_INFO	unw_info;
/* v2.11: changed 128 -> 258; actually, 255 is the max # of unwind codes */
static UNWIND_CODE	unw_code[258];

/* @ReservedStack symbol; used when option W64F_AUTOSTACKSP has been set */
struct asym *sym_ReservedStack; /* max stack space required by INVOKE */

/* tables for FASTCALL support */

/* v2.07: 16-bit MS FASTCALL registers are AX, DX, BX.
 * And params on stack are in PASCAL order.
 */
//static const enum special_token ms32_regs16[] = { T_CX, T_DX };
static const enum special_token ms32_regs16[] = { T_AX, T_DX, T_BX };
static const enum special_token ms32_regs32[] = { T_ECX,T_EDX };
/* v2.07: added */
static const int ms32_maxreg[] = {
    sizeof( ms32_regs16) / sizeof(ms32_regs16[0] ),
    sizeof( ms32_regs32) / sizeof(ms32_regs32[0] ),
};
static const enum special_token watc_regs8[] = {T_AL, T_DL, T_BL, T_CL };
static const enum special_token watc_regs16[] = {T_AX, T_DX, T_BX, T_CX };
static const enum special_token watc_regs32[] = {T_EAX, T_EDX, T_EBX, T_ECX };
static const enum special_token watc_regs_qw[] = {T_AX, T_BX, T_CX, T_DX };
static const enum special_token ms64_regs[] = {T_RCX, T_RDX, T_R8, T_R9 };
/* win64 non-volatile GPRs:
 * T_RBX, T_RBP, T_RSI, T_RDI, T_R12, T_R13, T_R14, T_R15
 */
static const uint_16 win64_nvgpr = 0xF0E8;
/* win64 non-volatile XMM regs: XMM6-XMM15 */
static const uint_16 win64_nvxmm = 0xFFC0;

struct fastcall_conv {
    int (* paramcheck)( struct dsym *, struct dsym *, int * );
    void (* handlereturn)( struct dsym *, char *buffer );
};

static	int ms32_pcheck( struct dsym *, struct dsym *, int * );
static void ms32_return( struct dsym *, char * );
static	int watc_pcheck( struct dsym *, struct dsym *, int * );
static void watc_return( struct dsym *, char * );
static	int ms64_pcheck( struct dsym *, struct dsym *, int * );
static void ms64_return( struct dsym *, char * );
static	int elf64_pcheck( struct dsym *, struct dsym *, int * );

/* table of fastcall types.
 * must match order of enum fastcall_type!
 * also see table in mangle.c!
 */

static const struct fastcall_conv fastcall_tab[] = {
    { ms32_pcheck, ms32_return }, /* FCT_MSC */
    { watc_pcheck, watc_return }, /* FCT_WATCOMC */
    { ms64_pcheck, ms64_return }, /* FCT_WIN64 */
    { elf64_pcheck,ms64_return }, /* FCT_ELF64 */
    { ms32_pcheck, ms32_return }, /* FCT_VEC32 */
    { ms64_pcheck, ms64_return }, /* FCT_VEC64 */
};

const enum special_token stackreg[] = { T_SP, T_ESP, T_RSP };

uint_32 StackAdj;  /* value of @StackBase variable */
int_32 StackAdjHigh;

static const char * const fmtstk0[] = {
    "sub %r, %d",
    "%r %d",
#if STACKPROBE
    "mov %r, %d",
#endif
};
static const char * const fmtstk1[] = {
    "sub %r, %d + %s",
    "%r %d + %s",
#if STACKPROBE
    "mov %r, %d + %s",
#endif
};

#define ROUND_UP( i, r ) (((i)+((r)-1)) & ~((r)-1))

/* register usage for OW fastcall (register calling convention).
 * registers are used for parameter size 1,2,4,8.
 * if a parameter doesn't fit in a register, a register pair is used.
 * however, valid register pairs are e/dx:e/ax and e/cx:e/bx only!
 * if a parameter doesn't fit in a register pair, registers
 * are used ax:bx:cx:dx!!!
 * stack cleanup for OW fastcall: if the proc is VARARG, the caller
 * will do the cleanup, else the called proc does it.
 * in VARARG procs, all parameters are pushed onto the stack!
 */

static int watc_pcheck( struct dsym *proc, struct dsym *paranode, int *used )
/***************************************************************************/
{
    static char regname[64];
    static char regist[32];
    int newflg;
    int shift;
    int firstreg;
    uint_8 Ofssize = GetSymOfssize( &proc->sym );
    int size = SizeFromMemtype( paranode->sym.mem_type, paranode->sym.Ofssize, paranode->sym.type );

    /* v2.05: VARARG procs don't have register params */
    if ( proc->e.procinfo->has_vararg )
	return( 0 );

    if ( size != 1 && size != 2 && size != 4 && size != 8 )
	return( 0 );

    /* v2.05: rewritten. The old code didn't allow to "fill holes" */
    if ( size == 8 ) {
	newflg = Ofssize ? 3 : 15;
	shift = Ofssize ? 2 : 4;
    } else if ( size == 4 && Ofssize == USE16 ) {
	newflg = 3;
	shift = 2;
    } else {
	newflg = 1;
	shift = 1;
    }

    /* scan if there's a free register (pair/quadrupel) */
    for ( firstreg = 0; firstreg < 4 && (newflg & *used ); newflg <<= shift, firstreg += shift );
    if ( firstreg >= 4 ) /* exit if nothing is free */
	return( 0 );

    paranode->sym.state = SYM_TMACRO;
    switch ( size ) {
    case 1:
	paranode->sym.regist[0] = watc_regs8[firstreg];
	break;
    case 2:
	paranode->sym.regist[0] = watc_regs16[firstreg];
	break;
    case 4:
	if ( Ofssize ) {
	    paranode->sym.regist[0] = watc_regs32[firstreg];
	} else {
	    paranode->sym.regist[0] = watc_regs16[firstreg];
	    paranode->sym.regist[1] = watc_regs16[firstreg+1];
	}
	break;
    case 8:
	if ( Ofssize ) {
	    paranode->sym.regist[0] = watc_regs32[firstreg];
	    paranode->sym.regist[1] = watc_regs32[firstreg+1];
	} else {
	    /* the AX:BX:CX:DX sequence is for 16-bit only.
	     * fixme: no support for codeview debug info yet;
	     * the S_REGISTER record supports max 2 registers only.
	     */
	    for( firstreg = 0, regname[0] = NULLC; firstreg < 4; firstreg++ ) {
		GetResWName( watc_regs_qw[firstreg], regname + strlen( regname ) );
		if ( firstreg != 3 )
		    strcat( regname, "::");
	    }
	}
    }
    if ( paranode->sym.regist[1] ) {
	sprintf( regname, "%s::%s",
		GetResWName( paranode->sym.regist[1], regist ),
		GetResWName( paranode->sym.regist[0], NULL ) );
    } else if ( paranode->sym.regist[0] ) {
	GetResWName( paranode->sym.regist[0], regname );
    }
    *used |= newflg;
    paranode->sym.string_ptr = (char *)LclAlloc( strlen( regname ) + 1 );
    strcpy( paranode->sym.string_ptr, regname );
    return( 1 );
}

static void watc_return( struct dsym *proc, char *buffer )
/********************************************************/
{
    int value;
    value = 4 * CurrWordSize;
    if( proc->e.procinfo->has_vararg == FALSE && proc->e.procinfo->parasize > value )
	sprintf( buffer + strlen( buffer ), "%d%c", proc->e.procinfo->parasize - value, ModuleInfo.radix != 10 ? 't' : NULLC );
    return;
}

/* the MS Win32 fastcall ABI is simple: register ecx and edx are used,
 * if the parameter's value fits into the register.
 * there is no space reserved on the stack for a register backup.
 * The 16-bit ABI uses registers AX, DX and BX - additional registers
 * are pushed in PASCAL order (i.o.w.: left to right).
 */

static int ms32_pcheck( struct dsym *proc, struct dsym *paranode, int *used )
/***************************************************************************/
{
    char regname[32];
    int size = SizeFromMemtype( paranode->sym.mem_type, paranode->sym.Ofssize, paranode->sym.type );

    /* v2.07: 16-bit has 3 register params (AX,DX,BX) */
    //if ( size > CurrWordSize || *used >= 2 )
    if ( size > CurrWordSize || *used >= ms32_maxreg[ModuleInfo.Ofssize] )
	return( 0 );
    paranode->sym.state = SYM_TMACRO;
    /* v2.10: for codeview debug info, store the register index in the symbol */
    paranode->sym.regist[0] = ModuleInfo.Ofssize ? ms32_regs32[*used] : ms32_regs16[*used];
    GetResWName( ModuleInfo.Ofssize ? ms32_regs32[*used] : ms32_regs16[*used], regname );
    paranode->sym.string_ptr = (char *)LclAlloc( strlen( regname ) + 1 );
    strcpy( paranode->sym.string_ptr, regname );
    (*used)++;
    return( 1 );
}

static void ms32_return( struct dsym *proc, char *buffer )
/********************************************************/
{
    if( proc->e.procinfo->parasize > ( ms32_maxreg[ModuleInfo.Ofssize] * CurrWordSize ) )
	sprintf( buffer + strlen( buffer ), "%d%c", proc->e.procinfo->parasize - ( ms32_maxreg[ModuleInfo.Ofssize] * CurrWordSize), ModuleInfo.radix != 10 ? 't' : NULLC );
    return;
}

/* the MS Win64 fastcall ABI is strict: the first four parameters are
 * passed in registers. If a parameter's value doesn't fit in a register,
 * it's address is used instead. parameter 1 is stored in rcx/xmm0,
 * then comes rdx/xmm1, r8/xmm2, r9/xmm3. The xmm regs are used if the
 * param is a float/double (but not long double!).
 * Additionally, there's space for the registers reserved by the caller on,
 * the stack. On a function's entry it's located at [esp+8] for param 1,
 * [esp+16] for param 2,... The parameter names refer to those stack
 * locations, not to the register names.
 */

static int ms64_pcheck( struct dsym *proc, struct dsym *paranode, int *used )
/***************************************************************************/
{
    /* since the parameter names refer the stack-backup locations,
     * there's nothing to do here!
     * That is, if a parameter's size is > 8, it has to be changed
     * to a pointer. This is to be done yet.
     */
    return( 0 );
}

static void ms64_return( struct dsym *proc, char *buffer )
/********************************************************/
{
    /* nothing to do, the caller cleans the stack */
    return;
}

#ifdef FCT_ELF64

extern unsigned char elf64_regs[];

static int elf64_pcheck( struct dsym *proc, struct dsym *paranode, int *used )
{
    char regname[32];
    int reg;
    int size = SizeFromMemtype( paranode->sym.mem_type, paranode->sym.Ofssize, paranode->sym.type );

    if ( size > CurrWordSize || *used >= 6 || paranode->sym.is_vararg ) {
	paranode->sym.string_ptr = NULL;
	return(0);
    }
    if ( paranode->sym.mem_type == MT_REAL4 ||
	 paranode->sym.mem_type == MT_REAL8 ||
	 paranode->sym.mem_type == MT_OWORD )
	 reg = T_XMM0 + *used;
    else
	switch ( size ) {
	case 1:	 reg = elf64_regs[*used];    break;
	case 2:	 reg = elf64_regs[*used+6];  break;
	case 4:	 reg = elf64_regs[*used+12]; break;
	default: reg = elf64_regs[*used+18]; break;
	}
    paranode->sym.state = SYM_TMACRO;
    paranode->sym.regist[0] = reg;
    GetResWName( reg, regname );
    paranode->sym.string_ptr = (char *)LclAlloc( strlen( regname ) + 1 );
    strcpy( paranode->sym.string_ptr, regname );
    (*used)++;
    return( 1 );
}

#endif

static void pushitem( void *stk, void *elmt )
/*******************************************/
{
    void      **stack = stk;
    struct qnode *node;

    node = (struct qnode *)LclAlloc( sizeof( struct qnode ));
    node->next = *stack;
    node->elmt = elmt;
    *stack = node;
}

static void *popitem( void *stk )
/*******************************/
{
    void	**stack = stk;
    struct qnode *node;
    void	*elmt;

    node = (struct qnode *)(*stack);
    *stack = node->next;
    elmt = (void *)node->elmt;
    return( elmt );
}

#if 0
void *peekitem( void *stk, int level )
/************************************/
{
    struct qnode  *node = (struct qnode *)stk;

    for ( ; node && level; level-- ) {
	node = node->next;
    }

    if ( node )
	return( node->elt );
    else
	return( NULL );
}
#endif

static void push_proc( struct dsym *proc )
/****************************************/
{
    if ( Parse_Pass == PASS_1 ) /* get the locals stored so far */
	SymGetLocal( (struct asym *)proc );
    pushitem( &ProcStack, proc );
    return;
}

static struct dsym *pop_proc( void )
/**********************************/
{
    if( ProcStack == NULL )
	return( NULL );
    return( (struct dsym *)popitem( &ProcStack ) );
}

/*
 * LOCAL directive. Syntax:
 * LOCAL symbol[,symbol]...
 * symbol:name [[count]] [:[type]]
 * count: number of array elements, default is 1
 * type:  qualified type [simple type, structured type, ptr to simple/structured type]
 */

ret_code LocalDir( int i, struct asm_tok tokenarray[] )
/*****************************************************/
{
    char	*name;
    struct dsym *local;
    struct dsym *curr;
    struct proc_info *info;
    struct qualified_type ti;

    if ( Parse_Pass != PASS_1 ) /* everything is done in pass 1 */
	return( NOT_ERROR );

    if( !( ProcStatus & PRST_PROLOGUE_NOT_DONE ) || CurrProc == NULL ) {
	return( asmerr( 2012 ) );
    }

    info = CurrProc->e.procinfo;
    /* ensure the fpo bit is set - it's too late to set it in write_prologue().
     * Note that the fpo bit is set only IF there are locals or arguments.
     * fixme: what if pass > 1?
     */
    if ( GetRegNo( info->basereg ) == 4 ) {
	info->fpo = TRUE;
	ProcStatus |= PRST_FPO;
    }
    i++; /* go past LOCAL */

    do	{
	if( tokenarray[i].token != T_ID ) {
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}
	name = tokenarray[i].string_ptr;

	ti.symtype = NULL;
	ti.is_ptr = 0;
	ti.ptr_memtype = MT_EMPTY;
	if ( SIZE_DATAPTR & ( 1 << ModuleInfo.model ) )
	    ti.is_far = TRUE;
	else
	    ti.is_far = FALSE;
	ti.Ofssize = ModuleInfo.Ofssize;

	local = (struct dsym *)SymLCreate( name );
	if( !local ) { /* if it failed, an error msg has been written already */
	    return( ERROR );
	}

	local->sym.state = SYM_STACK;
	local->sym.isdefined = TRUE;
	local->sym.total_length = 1; /* v2.04: added */
	switch ( ti.Ofssize ) {
	case USE16:
	    local->sym.mem_type = MT_WORD;
	    ti.size = sizeof( uint_16 );
	    break;
	default:
	    local->sym.mem_type = MT_DWORD;
	    ti.size = sizeof( uint_32 );
	    break;
	}

	i++; /* go past name */

	/* get the optional index factor: local name[xx]:... */
	if( tokenarray[i].token == T_OP_SQ_BRACKET ) {
	    int j;
	    struct expr opndx;
	    i++; /* go past '[' */
	    /* scan for comma or colon. this isn't really necessary,
	     * but will prevent the expression evaluator from emitting
	     * confusing error messages.
	     */
	    for ( j = i; j < Token_Count; j++ )
		if ( tokenarray[j].token == T_COMMA ||
		    tokenarray[j].token == T_COLON)
		    break;
	    if ( ERROR == EvalOperand( &i, tokenarray, j, &opndx, 0 ) )
		return( ERROR );
	    if ( opndx.kind != EXPR_CONST ) {
		asmerr( 2026 );
		opndx.value = 1;
	    }
	    /* zero is allowed as value! */
	    local->sym.total_length = opndx.value;
	    local->sym.isarray = TRUE;
	    if( tokenarray[i].token == T_CL_SQ_BRACKET ) {
		i++; /* go past ']' */
	    } else {
		asmerr( 2045 );
	    }
	}

	/* get the optional type: local name[xx]:type  */
	if( tokenarray[i].token == T_COLON ) {
	    i++;

	    if ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
		return( ERROR );

	    local->sym.mem_type = ti.mem_type;
	    if ( ti.mem_type == MT_TYPE ) {
		local->sym.type = ti.symtype;
	    } else {
		local->sym.target_type = ti.symtype;
	    }
	}
	local->sym.is_ptr  = ti.is_ptr;
	local->sym.isfar   = ti.is_far;
	local->sym.Ofssize = ti.Ofssize;
	local->sym.ptr_memtype = ti.ptr_memtype;
	local->sym.total_size = ti.size * local->sym.total_length;

	/* v2.12: address calculation is now done in SetLocalOffsets() */

	if( info->locallist == NULL ) {
	    info->locallist = local;
	} else {
	    for( curr = info->locallist; curr->nextlocal ; curr = curr->nextlocal );
	    curr->nextlocal = local;
	}

	if ( tokenarray[i].token != T_FINAL )
	    if ( tokenarray[i].token == T_COMMA ) {
		if ( (i + 1) < Token_Count )
		    i++;
	    } else {
		return( asmerr( 2065, "," ) );//tokenarray[i].tokpos ) );
	    }

    } while ( i < Token_Count );

    return( NOT_ERROR );
}

/* read/write value of @StackBase variable */

void UpdateStackBase( struct asym *sym, struct expr *opnd )
{
    if ( opnd ) {
	StackAdj = opnd->uvalue;
	StackAdjHigh = opnd->hvalue;
    }
    sym->value = StackAdj;
    sym->value3264 = StackAdjHigh;
}

/* read value of @ProcStatus variable */

void UpdateProcStatus( struct asym *sym, struct expr *opnd )
{
    sym->value = ( CurrProc ? ProcStatus : 0 );
}

/* parse parameters of a PROC/PROTO.
 * Called in pass one only.
 * i=start parameters
 */

static ret_code ParseParams( struct dsym *proc, int i, struct asm_tok tokenarray[], bool IsPROC )
{
    char	    *name;
    struct asym	    *sym;
    int		    cntParam;
    int		    offset;
    int		    fcint = 0;
    struct qualified_type ti;
    bool	    is_vararg;
    bool	    init_done;
    struct dsym	    *paranode;
    struct dsym	    *paracurr;
    int		    curr;

    /*
     * find "first" parameter ( that is, the first to be pushed in INVOKE ).
     */
    if ( proc->sym.langtype == LANG_C || proc->sym.langtype == LANG_SYSCALL ||
	( proc->sym.langtype == LANG_FASTCALL && ModuleInfo.Ofssize != USE64 ) ||
	( proc->sym.langtype == LANG_VECTORCALL && ModuleInfo.Ofssize != USE64 ) ||
	proc->sym.langtype == LANG_STDCALL )
	for ( paracurr = proc->e.procinfo->paralist; paracurr && paracurr->nextparam;
	      paracurr = paracurr->nextparam );
    else
	paracurr = proc->e.procinfo->paralist;

    /* v2.11: proc_info.init_done has been removed, sym.isproc flag is used instead */
    init_done = proc->sym.isproc;

    for( cntParam = 0 ; tokenarray[i].token != T_FINAL ; cntParam++ ) {

	if ( tokenarray[i].token == T_ID ) {
	    name = tokenarray[i++].string_ptr;
	} else if ( IsPROC == FALSE && tokenarray[i].token == T_COLON ) {
	    if ( paracurr )
		name = paracurr->sym.name;
	    else
		name = "";
	} else {
	    /* PROC needs a parameter name, PROTO accepts <void> also */
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}

	ti.symtype = NULL;
	ti.is_ptr = 0;
	ti.ptr_memtype = MT_EMPTY;
	if ( SIZE_DATAPTR & ( 1 << ModuleInfo.model ) )
	    ti.is_far = TRUE;
	else
	    ti.is_far = FALSE;
	ti.Ofssize = ModuleInfo.Ofssize;
	ti.size = CurrWordSize;
	is_vararg = FALSE;

	/* read colon. It's optional for PROC.
	 * Masm also allows a missing colon for PROTO - if there's
	 * just one parameter. Probably a Masm bug.
	 * JWasm always require a colon for PROTO.
	 */
	if( tokenarray[i].token != T_COLON ) {
	    if ( IsPROC == FALSE ) {
		return( asmerr( 2065, ":") );
	    }
	    switch ( ti.Ofssize ) {
	    case USE16:
		ti.mem_type = MT_WORD; break;
	    default:
		ti.mem_type = MT_DWORD; break;
	    }
	} else {
	    i++;
	    if (( tokenarray[i].token == T_RES_ID ) && ( tokenarray[i].tokval == T_VARARG )) {
		switch( proc->sym.langtype ) {
		case LANG_NONE:
		case LANG_BASIC:
		case LANG_FORTRAN:
		case LANG_PASCAL:
		case LANG_STDCALL:
		    return( asmerr( 2131 ) );
		}
		/* v2.05: added check */
		if ( tokenarray[i+1].token != T_FINAL )
		    asmerr( 2129 );
		else
		    is_vararg = TRUE;
		ti.mem_type = MT_EMPTY;
		ti.size = 0;
		i++;
	    } else {
		if ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
		    return( ERROR );
	    }
	}

	/* check if parameter name is defined already */
	if (( IsPROC ) && ( sym = SymSearch( name ) ) && sym->state != SYM_UNDEFINED ) {
	    return( asmerr( 2005, name ) );
	}

	/* redefinition? */
	if ( paracurr ) {
	    struct asym *to;
	    struct asym *tn;
	    char oo;
	    char on;
	    for( tn = ti.symtype; tn && tn->type; tn = tn->type );
	    /* v2.12: don't assume pointer type if mem_type is != MT_TYPE!
	     * regression test proc9.asm.
	     * v2.23: proto fastcall :type - fast32.asm
	     */
	    if ( proc->sym.langtype == LANG_FASTCALL && ModuleInfo.Ofssize == USE32 )
		paracurr->sym.target_type = NULL;
	    if ( paracurr->sym.mem_type == MT_TYPE )
		to = paracurr->sym.type;
	    else
		to = ( paracurr->sym.mem_type == MT_PTR ? paracurr->sym.target_type : NULL );

	    for( ; to && to->type; to = to->type );
	    oo = ( paracurr->sym.Ofssize != USE_EMPTY ) ? paracurr->sym.Ofssize : ModuleInfo.Ofssize;
	    on = ( ti.Ofssize != USE_EMPTY ) ? ti.Ofssize : ModuleInfo.Ofssize;
	    if ( ti.mem_type != paracurr->sym.mem_type ||
		( ti.mem_type == MT_TYPE && tn != to ) ||
		( ti.mem_type == MT_PTR &&
		 ( ti.is_far != paracurr->sym.isfar ||
		  on != oo ||
		  ti.ptr_memtype != paracurr->sym.ptr_memtype ||
		  tn != to ))) {
		asmerr( 2111, name );
	    }
	    if ( IsPROC ) {
		/* it has been checked already that the name isn't found - SymAddLocal() shouldn't fail */
		SymAddLocal( &paracurr->sym, name );
	    }
	    /* set paracurr to next parameter */
	    if ( proc->sym.langtype == LANG_C ||
		proc->sym.langtype == LANG_SYSCALL ||
		( proc->sym.langtype == LANG_FASTCALL && ti.Ofssize != USE64 ) ||
		( proc->sym.langtype == LANG_VECTORCALL && ti.Ofssize != USE64 ) ||
		proc->sym.langtype == LANG_STDCALL) {
		struct dsym *l;
		for (l = proc->e.procinfo->paralist;
		     l && ( l->nextparam != paracurr );
		     l = l->nextparam );
		paracurr = l;
	    } else
		paracurr = paracurr->nextparam;

	} else if ( init_done == TRUE ) {
	    /* second definition has more parameters than first */
	    return( asmerr( 2111, "" ) );
	} else {
	    if ( IsPROC ) {
		paranode = (struct dsym *)SymLCreate( name );
	    } else
		paranode = (struct dsym *)SymAlloc( "" );/* for PROTO, no param name needed */

	    if( paranode == NULL ) { /* error msg has been displayed already */
		return( ERROR );
	    }
	    paranode->sym.isdefined = TRUE;
	    paranode->sym.mem_type = ti.mem_type;
	    if ( ti.mem_type == MT_TYPE ) {
		paranode->sym.type = ti.symtype;
	    } else {
		paranode->sym.target_type = ti.symtype;
	    }

	    /* v2.05: moved BEFORE fastcall_tab() */
	    paranode->sym.isfar	  = ti.is_far;
	    paranode->sym.Ofssize = ti.Ofssize;
	    paranode->sym.is_ptr  = ti.is_ptr;
	    paranode->sym.ptr_memtype = ti.ptr_memtype;
	    paranode->sym.is_vararg = is_vararg;

	    if ( ( proc->sym.langtype == LANG_FASTCALL || proc->sym.langtype == LANG_VECTORCALL ||
		( proc->sym.langtype == LANG_SYSCALL && ModuleInfo.fctype == FCT_ELF64 ) ) &&
		fastcall_tab[ModuleInfo.fctype].paramcheck( proc, paranode, &fcint ) ) {
	    } else {
		paranode->sym.state = SYM_STACK;
	    }

	    paranode->sym.total_length = 1; /* v2.04: added */
	    paranode->sym.total_size = ti.size;

	    if( paranode->sym.is_vararg == FALSE )
		/* v2.11: CurrWordSize does reflect the default parameter size only for PROCs.
		 * For PROTOs and TYPEs use member seg_ofssize.
		 */
		proc->e.procinfo->parasize += ROUND_UP( ti.size, IsPROC ? CurrWordSize : ( 2 << proc->sym.seg_ofssize ) );

	    /* Parameters usually are stored in "push" order.
	     * However, for Win64, it's better to store them
	     * the "natural" way from left to right, since the
	     * arguments aren't "pushed".
	     */

	    switch( proc->sym.langtype ) {
	    case LANG_BASIC:
	    case LANG_FORTRAN:
	    case LANG_PASCAL:
	    left_to_right:
		paranode->nextparam = NULL;
		if( proc->e.procinfo->paralist == NULL ) {
		    proc->e.procinfo->paralist = paranode;
		} else {
		    for( paracurr = proc->e.procinfo->paralist;; paracurr = paracurr->nextparam ) {
			if( paracurr->nextparam == NULL ) {
			    break;
			}
		    }
		    paracurr->nextparam = paranode;
		    paracurr = NULL;
		}
		break;
	    case LANG_SYSCALL:
	    case LANG_FASTCALL:
	    case LANG_VECTORCALL:
		if ( ti.Ofssize == USE64 )
		    goto left_to_right;
		/* v2.07: MS fastcall 16-bit is PASCAL! */
		if ( ti.Ofssize == USE16 && ModuleInfo.fctype == FCT_MSC )
		    goto left_to_right;
	    default:
		paranode->nextparam = proc->e.procinfo->paralist;
		proc->e.procinfo->paralist = paranode;
		break;
	    }
	}
	if ( tokenarray[i].token != T_FINAL ) {
	    if( tokenarray[i].token != T_COMMA ) {
		return( asmerr( 2065, ",") );// tokenarray[i].tokpos ) );
	    }
	    i++;    /* go past comma */
	}
    } /* end for */

    if ( init_done == TRUE ) {
	if ( paracurr ) {
	    /* first definition has more parameters than second */
	    return( asmerr( 2111, "" ) );
	}
    }

    if ( IsPROC ) {
	/* calc starting offset for parameters,
	 * offset from [E|R]BP : return addr + old [E|R]BP
	 * NEAR: 2 * wordsize, FAR: 3 * wordsize
	 *	   NEAR	 FAR
	 *-------------------------
	 * USE16   +4	 +6
	 * USE32   +8	 +12
	 * USE64   +16	 +24
	 * without frame pointer:
	 * USE16   +2	 +4
	 * USE32   +4	 +8
	 * USE64   +8	 +16
	 */
	offset = ( ( 2 + ( proc->sym.mem_type == MT_FAR ? 1 : 0 ) ) * CurrWordSize );

	/* now calculate the [E|R]BP offsets */

	if ( ModuleInfo.Ofssize == USE64 && ( proc->sym.langtype == LANG_FASTCALL ||
	    proc->sym.langtype == LANG_SYSCALL || proc->sym.langtype == LANG_VECTORCALL ) ) {
	    for ( paranode = proc->e.procinfo->paralist; paranode ;paranode = paranode->nextparam )
		if ( paranode->sym.state == SYM_TMACRO ) /* register param */
		    ;
		else {
		    paranode->sym.offset = offset;
		    proc->e.procinfo->stackparam = TRUE;
		    offset += ROUND_UP( paranode->sym.total_size, CurrWordSize );
		}
	} else
	for ( ; cntParam; cntParam-- ) {
	    for ( curr = 1, paranode = proc->e.procinfo->paralist; curr < cntParam;paranode = paranode->nextparam, curr++ );
	    if ( paranode->sym.state == SYM_TMACRO ) /* register param? */
		;
	    else {
		paranode->sym.offset = offset;
		proc->e.procinfo->stackparam = TRUE;
		offset += ROUND_UP( paranode->sym.total_size, CurrWordSize );
	    }
	}
    }
    return ( NOT_ERROR );
}

/*
 * parse a function prototype - called in pass 1 only.
 * the syntax is used by:
 * - PROC directive:	  <name> PROC ...
 * - PROTO directive:	  <name> PROTO ...
 * - EXTERN[DEF] directive: EXTERN[DEF] <name>: PROTO ...
 * - TYPEDEF directive:	  <name> TYPEDEF PROTO ...
 *
 * i = start index of attributes
 * IsPROC: TRUE for PROCs, FALSE for everything else
 *
 * strategy to set default value for "offset size" (16/32):
 * 1. if current model is FLAT, use 32, else
 * 2. use the current segment's attribute
 * 3. if no segment is set, use cpu setting
 */
int ParseProc( struct dsym *proc, int i, struct asm_tok tokenarray[], bool IsPROC,
	unsigned char langtype )
{
    char	    *token;
    uint_16	    *regist;
    unsigned char    newmemtype;
    uint_8	    newofssize;
    uint_8	    oldofssize;
    bool	    oldpublic = proc->sym.ispublic;

    /* set some default values */

    if ( IsPROC ) {
	proc->e.procinfo->isexport = ModuleInfo.procs_export;
	/* don't overwrite a PUBLIC directive for this symbol! */
	if ( ModuleInfo.procs_private == FALSE )
	    proc->sym.ispublic = TRUE;

	/* set type of epilog code */
	/* v2.11: if base register isn't [E|R]BP, don't use LEAVE! */
	if ( GetRegNo( proc->e.procinfo->basereg ) != 5 ) {
	    proc->e.procinfo->pe_type = 0;
	} else
	if ( Options.masm_compat_gencode ) {
	    /* v2.07: Masm uses LEAVE if
	     * - current code is 32-bit/64-bit or
	     * - cpu is .286 or .586+ */
	    proc->e.procinfo->pe_type = ( ModuleInfo.Ofssize > USE16 ||
					 ( ModuleInfo.curr_cpu & P_CPU_MASK ) == P_286 ||
					 ( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_586 ) ? 1 : 0;
	} else {
	    /* use LEAVE for 286, 386 (and x64) */
	    proc->e.procinfo->pe_type = ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) == P_286 ||
					 ( ModuleInfo.curr_cpu & P_CPU_MASK ) == P_64 ||
					 ( ModuleInfo.curr_cpu & P_CPU_MASK ) == P_386 ) ? 1 : 0;
	}
    }

    /* 1. attribute is <distance> */
    if ( tokenarray[i].token == T_STYPE &&
	tokenarray[i].tokval >= T_NEAR && tokenarray[i].tokval <= T_FAR32 ) {
	uint_8 Ofssize = GetSflagsSp( tokenarray[i].tokval );
	if ( IsPROC ) {
	    if ( ( ModuleInfo.Ofssize >= USE32 && Ofssize == USE16 ) ||
		( ModuleInfo.Ofssize == USE16 && Ofssize == USE32 ) ) {
		asmerr( 2011 );
	    }
	}
	newmemtype = GetMemtypeSp( tokenarray[i].tokval );
	newofssize = (( Ofssize != USE_EMPTY ) ? Ofssize : ModuleInfo.Ofssize );
	i++;
    } else {
	newmemtype = ( ( SIZE_CODEPTR & ( 1 << ModuleInfo.model ) ) ? MT_FAR : MT_NEAR );
	newofssize = ModuleInfo.Ofssize;
    }

    /* v2.11: GetSymOfssize() cannot handle SYM_TYPE correctly */
    if ( proc->sym.state == SYM_TYPE )
	oldofssize = proc->sym.seg_ofssize;
    else
	oldofssize = GetSymOfssize( &proc->sym );

    /* did the distance attribute change? */
    if ( proc->sym.mem_type != MT_EMPTY &&
	( proc->sym.mem_type != newmemtype ||
	 oldofssize != newofssize ) ) {
	if ( proc->sym.mem_type == MT_NEAR || proc->sym.mem_type == MT_FAR )
	    asmerr( 2112 );
	else {
	    return( asmerr( 2005, proc->sym.name ) );
	}
    } else {
	proc->sym.mem_type = newmemtype;
	if ( IsPROC == FALSE )
	    proc->sym.seg_ofssize = newofssize;
    }

    /* 2. attribute is <langtype> */
    /* v2.09: the default language value is now a function argument. This is because
     * EXTERN[DEF] allows to set the language attribute by:
     * EXTERN[DEF] <langtype> <name> PROTO ...
     * ( see CreateProto() in extern.c )
     */
    //langtype = ModuleInfo.langtype; /* set the default value */
    GetLangType( &i, tokenarray, &langtype ); /* optionally overwrite the value */
    /* has language changed? */
    if ( proc->sym.langtype != LANG_NONE && proc->sym.langtype != langtype ) {
	asmerr( 2112 );
    } else
	proc->sym.langtype = langtype;

    /* 3. attribute is <visibility> */
    /* note that reserved word PUBLIC is a directive! */
    /* PROTO does NOT accept PUBLIC! However,
     * PROTO accepts PRIVATE and EXPORT, but these attributes are just ignored!
     */

    if ( tokenarray[i].token == T_ID || tokenarray[i].token == T_DIRECTIVE ) {
	token = tokenarray[i].string_ptr;
	if ( _stricmp( token, "PRIVATE") == 0 ) {
	    if ( IsPROC ) { /* v2.11: ignore PRIVATE for PROTO */
		proc->sym.ispublic = FALSE;
		/* error if there was a PUBLIC directive! */
		proc->sym.scoped = TRUE;
		if ( oldpublic ) {
		    SkipSavedState(); /* do a full pass-2 scan */
		}
		proc->e.procinfo->isexport = FALSE;
	    }
	    i++;
	} else if ( IsPROC && (_stricmp(token, "PUBLIC") == 0 ) ) {
	    proc->sym.ispublic = TRUE;
	    proc->e.procinfo->isexport = FALSE;
	    i++;
	} else if ( _stricmp(token, "EXPORT") == 0 ) {
	    if ( IsPROC ) { /* v2.11: ignore EXPORT for PROTO */
		proc->sym.ispublic = TRUE;
		proc->e.procinfo->isexport = TRUE;
		/* v2.11: no export for 16-bit near */
		if ( ModuleInfo.Ofssize == USE16 && proc->sym.mem_type == MT_NEAR )
		    asmerr( 2145, proc->sym.name );
	    }
	    i++;
	}
    }

    /* 4. attribute is <prologuearg>, for PROC only.
     * it must be enclosed in <>
     */
    if ( IsPROC && tokenarray[i].token == T_STRING && tokenarray[i].string_delim == '<' ) {
	int idx = Token_Count + 1;
	int max;
	if ( ModuleInfo.prologuemode == PEM_NONE )
	    ; /* no prologue at all */
	else if ( ModuleInfo.prologuemode == PEM_MACRO ) {
	    proc->e.procinfo->prologuearg = (char *)LclAlloc( tokenarray[i].stringlen + 1 );
	    strcpy( proc->e.procinfo->prologuearg, tokenarray[i].string_ptr );
	} else {
	    /* check the argument. The default prologue
	     understands FORCEFRAME and LOADDS only
	     */
	    max = Tokenize( tokenarray[i].string_ptr, idx, tokenarray, TOK_RESCAN );
	    for ( ; idx < max; idx++ ) {
		if ( tokenarray[idx].token == T_ID ) {
		    if ( _stricmp( tokenarray[idx].string_ptr, "FORCEFRAME") == 0 ) {
			proc->e.procinfo->forceframe = TRUE;
		    } else if ( ModuleInfo.Ofssize != USE64 && (_stricmp( tokenarray[idx].string_ptr, "LOADDS") == 0 ) ) {
			if ( ModuleInfo.model == MODEL_FLAT ) {
			    asmerr( 8014 );
			} else
			    proc->e.procinfo->loadds = TRUE;
		    } else {
			return( asmerr( 4005, tokenarray[idx].string_ptr ) );
		    }
		    if ( tokenarray[idx+1].token == T_COMMA && tokenarray[idx+2].token != T_FINAL)
			idx++;
		} else {
		    return( asmerr(2008, tokenarray[idx].string_ptr ) );
		}
	    }
	}
	i++;
    }

    /* check for optional FRAME[:exc_proc] */
    if ( ModuleInfo.Ofssize == USE64 &&
	IsPROC &&
	tokenarray[i].token == T_RES_ID &&
	tokenarray[i].tokval == T_FRAME ) {
	/* v2.05: don't accept FRAME for ELF */
	if ( Options.output_format != OFORMAT_COFF
	    && ModuleInfo.sub_format != SFORMAT_PE
	   ) {
	    return( asmerr( 3006, GetResWName( T_FRAME, NULL ) ) );
	}
	i++;
	if( tokenarray[i].token == T_COLON ) {
	    struct asym *sym;
	    i++;
	    if ( tokenarray[i].token != T_ID ) {
		return( asmerr(2008, tokenarray[i].string_ptr ) );
	    }
	    sym = SymSearch( tokenarray[i].string_ptr );
	    if ( sym == NULL ) {
		sym = SymCreate( tokenarray[i].string_ptr );
		sym->state = SYM_UNDEFINED;
		sym->used = TRUE;
		sym_add_table( &SymTables[TAB_UNDEF], (struct dsym *)sym ); /* add UNDEFINED */
	    } else if ( sym->state != SYM_UNDEFINED &&
		       sym->state != SYM_INTERNAL &&
		       sym->state != SYM_EXTERNAL ) {
		return( asmerr( 2005, sym->name ) );
	    }
	    proc->e.procinfo->exc_handler = sym;
	    i++;
	} else
	    proc->e.procinfo->exc_handler = NULL;
	proc->e.procinfo->isframe = TRUE;
    }
    /* check for USES */
    if ( tokenarray[i].token == T_ID && _stricmp( tokenarray[i].string_ptr, "USES" ) == 0 ) {
	int cnt;
	int j;
	if ( !IsPROC ) {/* not for PROTO! */
	    asmerr(2008, tokenarray[i].string_ptr );
	}
	i++;
	/* count register names which follow */
	for ( cnt = 0, j = i; tokenarray[j].token == T_REG; j++, cnt++ );

	if ( cnt == 0 ) {
	    asmerr(2008, tokenarray[i-1].tokpos );
	} else {
	    regist = (unsigned short *)LclAlloc( (cnt + 1) * sizeof( uint_16 ) );
	    proc->e.procinfo->regslist = regist;
	    *regist++ = cnt;
	    /* read in registers */
	    for( ; tokenarray[i].token == T_REG; i++ ) {
		if ( SizeFromRegister( tokenarray[i].tokval ) == 1 ) {
		    asmerr( 2032 );
		}
		*regist++ = tokenarray[i].tokval;
	    }
	}
    }

    /* the parameters must follow */
    if ( tokenarray[i].token == T_STYPE || tokenarray[i].token == T_RES_ID || tokenarray[i].token == T_DIRECTIVE ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }

    /* skip optional comma */
    if ( tokenarray[i].token == T_COMMA )
	i++;

    if( i >= Token_Count ) {
	/* procedure has no parameters at all */
	if ( proc->e.procinfo->paralist != NULL )
	    asmerr( 2111, "" );
    } else if( proc->sym.langtype == LANG_NONE ) {
	if( ModuleInfo.model == MODEL_NONE ) {
	    /* v2.26 - default to /win64 */
	    RewindToWin64();
	}
	asmerr( 2119 );
    } else {
	/* v2.05: set PROC's vararg flag BEFORE params are scanned! */
	if ( tokenarray[Token_Count - 1].token == T_RES_ID &&
	    tokenarray[Token_Count - 1].tokval == T_VARARG )
	    proc->e.procinfo->has_vararg = TRUE;
	if ( ERROR == ParseParams( proc, i, tokenarray, IsPROC ) )
	    /* do proceed if the parameter scan returns an error */
	    ;//return( ERROR );
    }

    /* v2.11: isdefined and isproc now set here */
    proc->sym.isdefined = TRUE;
    proc->sym.isproc = TRUE;

    return( NOT_ERROR );
}

/* create a proc ( internal[=PROC] or external[=PROTO] ) item.
 * sym is either NULL, or has type SYM_UNDEFINED or SYM_EXTERNAL.
 * called by:
 * - ProcDir ( state == SYM_INTERNAL )
 * - CreateLabel ( state == SYM_INTERNAL )
 * - AddLinnumDataRef ( state == SYM_INTERNAL, sym==NULL )
 * - CreateProto ( state == SYM_EXTERNAL )
 * - ExterndefDirective ( state == SYM_EXTERNAL )
 * - ExternDirective ( state == SYM_EXTERNAL )
 * - TypedefDirective ( state == SYM_TYPE, sym==NULL )
 */

struct asym *CreateProc( struct asym *sym, const char *name, enum sym_state state )
/*********************************************************************************/
{
    if ( sym == NULL )
	sym = ( *name ? SymCreate( name ) : SymAlloc( name ) );
    else
	sym_remove_table( ( sym->state == SYM_UNDEFINED ) ? &SymTables[TAB_UNDEF] : &SymTables[TAB_EXT], (struct dsym *)sym );

    if ( sym ) {
	struct proc_info *info;
	sym->state = state;
	if ( state != SYM_INTERNAL ) {
	    sym->seg_ofssize = ModuleInfo.Ofssize;
	}
	info = (struct proc_info *)LclAlloc( sizeof( struct proc_info ) );
	((struct dsym *)sym)->e.procinfo = info;
	info->regslist = NULL;
	info->paralist = NULL;
	info->locallist = NULL;
	info->labellist = NULL;
	info->parasize = 0;
	info->localsize = 0;
	info->prologuearg = NULL;
	info->flags = 0;
	switch ( sym->state ) {
	case SYM_INTERNAL:
	    /* v2.04: don't use sym_add_table() and thus
	     * free the <next> member field!
	     */
	    if ( SymTables[TAB_PROC].head == NULL )
		SymTables[TAB_PROC].head = (struct dsym *)sym;
	    else {
		SymTables[TAB_PROC].tail->nextproc = (struct dsym *)sym;
	    }
	    SymTables[TAB_PROC].tail = (struct dsym *)sym;
	    procidx++;
	    if ( Options.line_numbers ) {
		sym->debuginfo = (struct debug_info *)LclAlloc( sizeof( struct debug_info ) );
		sym->debuginfo->file = get_curr_srcfile();
	    }
	    break;
	case SYM_EXTERNAL:
	    sym->weak = TRUE;
	    sym_add_table( &SymTables[TAB_EXT], (struct dsym *)sym );
	    break;
	}
    }
    return( sym );
}

/* delete a PROC item */

void DeleteProc( struct dsym *proc )
/**********************************/
{
    struct dsym *curr;
    struct dsym *next;

    if ( proc->sym.state == SYM_INTERNAL ) {

	/* delete all local symbols ( params, locals, labels ) */
	for( curr = proc->e.procinfo->labellist; curr; ) {
	    next = curr->e.nextll;
	    SymFree( &curr->sym );
	    curr = next;
	}
    }
    return;
}

/* PROC directive. */

ret_code ProcDir( int i, struct asm_tok tokenarray[] )
/****************************************************/
{
    struct asym		*sym;
    unsigned int	ofs;
    char		*name;
    bool		oldpubstate;
    bool		is_global;

    if( i != 1 ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    /* v2.04b: check was missing */
    if( CurrSeg == NULL ) {
	return( asmerr( 2034 ) );
    }

    name = tokenarray[0].string_ptr;

    if( CurrProc != NULL ) {

	/* this is not needed for JWasm, but Masm will reject nested
	 * procs if there are params, locals or used registers.
	 */
	if ( CurrProc->e.procinfo->paralist ||
	    CurrProc->e.procinfo->isframe ||
	    CurrProc->e.procinfo->locallist ||
	    CurrProc->e.procinfo->regslist ) {
	    return( asmerr( 2144, name ) );
	}
	/* nested procs ... push currproc on a stack */
	push_proc( CurrProc );
    }


    if ( ModuleInfo.procalign ) {
	AlignCurrOffset( ModuleInfo.procalign );
    }

    i++; /* go past PROC */

    sym = SymSearch( name );

    if( Parse_Pass == PASS_1 ) {

	oldpubstate = sym ? sym->ispublic : FALSE;
	if( sym == NULL || sym->state == SYM_UNDEFINED ) {
	    sym = CreateProc( sym, name, SYM_INTERNAL );
	    is_global = FALSE;
	} else if ( sym->state == SYM_EXTERNAL && sym->weak == TRUE ) {
	    /* PROTO or EXTERNDEF item */
	    is_global = TRUE;
	    if ( sym->isproc == TRUE  ) {
		/* don't create the procinfo extension; it exists already */
		procidx++; /* v2.04: added */
		if ( Options.line_numbers ) {
		    sym->debuginfo = (struct debug_info *)LclAlloc( sizeof( struct debug_info ) );
		    sym->debuginfo->file = get_curr_srcfile();
		}
	    } else {
		/* it's a simple EXTERNDEF. Create a PROC item!
		 * this will be SYM_INTERNAL */
		/* v2.03: don't call dir_free(), it'll clear field Ofssize */
		sym = CreateProc( sym, name, SYM_INTERNAL );
	    }
	} else {
	    /* Masm won't reject a redefinition if "certain" parameters
	     * won't change. However, in a lot of cases one gets "internal assembler error".
	     * Hence this "feature" isn't active in jwasm.
	     */
	    return( asmerr( 2005, sym->name ) );
	}
	SetSymSegOfs( sym );

	SymClearLocal();

	/* v2.11: added. Note that fpo flag is only set if there ARE params! */
	((struct dsym *)sym)->e.procinfo->basereg = ModuleInfo.basereg[ModuleInfo.Ofssize];
	/* CurrProc must be set, it's used inside SymFind() and SymLCreate()! */
	CurrProc = (struct dsym *)sym;
	if( ParseProc( (struct dsym *)sym, i, tokenarray, TRUE, ModuleInfo.langtype ) == ERROR ) {
	    CurrProc = NULL;
	    return( ERROR );
	}
	/* v2.04: added */
	if ( is_global && Options.masm8_proc_visibility )
	    sym->ispublic = TRUE;

	/* if there was a PROTO (or EXTERNDEF name:PROTO ...),
	 * change symbol to SYM_INTERNAL!
	 */
	if ( sym->state == SYM_EXTERNAL && sym->isproc == TRUE ) {
	    sym_ext2int( sym );
	    /* v2.11: added ( may be better to call CreateProc() - currently not possible ) */
	    if ( SymTables[TAB_PROC].head == NULL )
		SymTables[TAB_PROC].head = (struct dsym *)sym;
	    else {
		SymTables[TAB_PROC].tail->nextproc = (struct dsym *)sym;
	    }
	    SymTables[TAB_PROC].tail = (struct dsym *)sym;
	}

	/* v2.11: sym->isproc is set inside ParseProc() */
	/* v2.11: Note that fpo flag is only set if there ARE params ( or locals )! */
	if ( CurrProc->e.procinfo->paralist && GetRegNo( CurrProc->e.procinfo->basereg ) == 4 )
	    CurrProc->e.procinfo->fpo = TRUE;
	if( sym->ispublic == TRUE && oldpubstate == FALSE )
	    AddPublicData( sym );

	/* v2.04: add the proc to the list of labels attached to curr segment.
	 * this allows to reduce the number of passes (see fixup.c)
	 */
	((struct dsym *)sym)->next = (struct dsym *)CurrSeg->e.seginfo->label_list;
	CurrSeg->e.seginfo->label_list = sym;

    } else {

	procidx++;
	sym->isdefined = TRUE;

	SymSetLocal( sym );

	/* it's necessary to check for a phase error here
	 as it is done in LabelCreate() and data_dir()!
	 */
	ofs = GetCurrOffset();

	if ( ofs != sym->offset) {
	    sym->offset = ofs;
	    ModuleInfo.PhaseError = TRUE;
	}
	CurrProc = (struct dsym *)sym;
	/* check if the exception handler set by FRAME is defined */
	if ( CurrProc->e.procinfo->isframe &&
	    CurrProc->e.procinfo->exc_handler &&
	    CurrProc->e.procinfo->exc_handler->state == SYM_UNDEFINED ) {
	    asmerr( 2006, CurrProc->e.procinfo->exc_handler->name );
	}
    }

    /* v2.11: init @ProcStatus - prologue not written yet, optionally set FPO flag */
    ProcStatus = PRST_PROLOGUE_NOT_DONE | ( CurrProc->e.procinfo->fpo ? PRST_FPO : 0 );
    StackAdj = 0;  /* init @StackBase to 0 */
    StackAdjHigh = 0;

    if ( CurrProc->e.procinfo->isframe ) {
	endprolog_found = FALSE;
	/* v2.11: clear all fields */
	memset( &unw_info, 0, sizeof( unw_info ) );
	if ( CurrProc->e.procinfo->exc_handler )
	    unw_info.Flags = UNW_FLAG_FHANDLER;
    }

    sym->asmpass = Parse_Pass;
    if ( ModuleInfo.list )
	LstWrite( LSTTYPE_LABEL, 0, NULL );

    if( Options.line_numbers ) {
	AddLinnumDataRef( get_curr_srcfile(), Options.output_format == OFORMAT_COFF ? 0 : GetLineNumber() );
    }

    BackPatch( sym );
    return( NOT_ERROR );
}

ret_code CopyPrototype( struct dsym *proc, struct dsym *src )
/***********************************************************/
{
    struct dsym *curr;
    struct dsym *newl;
    struct dsym *oldl;

    if ( src->sym.isproc == FALSE )
	return( ERROR );
    memcpy(proc->e.procinfo, src->e.procinfo, sizeof( struct proc_info ) );
    proc->sym.mem_type = src->sym.mem_type;
    proc->sym.langtype = src->sym.langtype;
    proc->sym.ispublic	 = src->sym.ispublic;
    /* we use the PROTO part, not the TYPE part */
    proc->sym.seg_ofssize = src->sym.seg_ofssize;
    proc->sym.isproc = TRUE;
    proc->e.procinfo->paralist = NULL;
    for ( curr = src->e.procinfo->paralist; curr; curr = curr->nextparam ) {
	newl = (struct dsym *)LclAlloc( sizeof( struct dsym ) );
	memcpy( newl, curr, sizeof( struct dsym ) );
	newl->nextparam = NULL;
	if ( proc->e.procinfo->paralist == NULL)
	    proc->e.procinfo->paralist = newl;
	else {
	    for ( oldl = proc->e.procinfo->paralist; oldl->nextparam; oldl = oldl->nextparam );
	    oldl->nextparam = newl;
	}
    }
    return( NOT_ERROR );
}

/* for FRAME procs, write .pdata and .xdata SEH unwind information */

static void WriteSEHData( struct dsym *proc )
/*******************************************/
{
    struct dsym *xdata;
    char *segname = ".xdata";
    int i;
    int simplespec;
    uint_8 olddotname;
    uint_32 xdataofs = 0;
    char segnamebuff[12];
    char buffer[128];

    if ( endprolog_found == FALSE ) {
	asmerr( 3007, proc->sym.name );
    }
    if ( unw_segs_defined )
	AddLineQueueX("%s %r", segname, T_SEGMENT );
    else {
	AddLineQueueX("%s %r align(%u) flat read 'DATA'", segname, T_SEGMENT, 8 );
	AddLineQueue("$xdatasym label near");
    }
    xdataofs = 0;
    xdata = (struct dsym *)SymSearch( segname );
    if ( xdata ) {
	/* v2.11: changed offset to max_offset.
	 * However, value structinfo.current_loc might even be better.
	 */
	xdataofs = xdata->sym.max_offset;
    }

    /* write the .xdata stuff (a UNWIND_INFO entry )
     * v2.11: 't'-suffix added to ensure the values are correct if radix is != 10.
     */
    AddLineQueueX( "db %ut + (0%xh shl 3), %ut, %ut, 0%xh + (0%xh shl 4)",
	    UNW_VERSION, unw_info.Flags, unw_info.SizeOfProlog,
	    unw_info.CountOfCodes, unw_info.FrameRegister, unw_info.FrameOffset );
    if ( unw_info.CountOfCodes ) {
	char *pfx = "dw";
	buffer[0] = NULLC;
	/* write the codes from right to left */
	for ( i = unw_info.CountOfCodes; i ; i-- ) {
	    sprintf( buffer + strlen( buffer ), "%s 0%xh", pfx, unw_code[i-1].FrameOffset );
	    pfx = ",";
	    if ( i == 1 || strlen( buffer ) > 72 ) {
		AddLineQueue( buffer );
		buffer[0] = NULLC;
		pfx = "dw";
	    }
	}
    }
    /* make sure the unwind codes array has an even number of entries */
    AddLineQueueX( "%r 4", T_ALIGN );

    if ( proc->e.procinfo->exc_handler ) {
	AddLineQueueX( "dd %r %s", T_IMAGEREL, proc->e.procinfo->exc_handler->name );
	AddLineQueueX( "%r 8", T_ALIGN );
    }
    AddLineQueueX( "%s %r", segname, T_ENDS );

    /* v2.07: ensure that .pdata items are sorted */
    if ( 0 == strcmp( SimGetSegName( SIM_CODE ), proc->sym.segment->name ) ) {
	segname = ".pdata";
	simplespec = ( unw_segs_defined & 1 );
	unw_segs_defined = 3;
    } else {
	segname = segnamebuff;
	sprintf( segname, ".pdata$%04u", GetSegIdx( proc->sym.segment ) );
	simplespec = 0;
	unw_segs_defined |= 2;
    }

    if ( simplespec )
	AddLineQueueX( "%s %r", segname, T_SEGMENT );
    else
	AddLineQueueX( "%s %r align(%u) flat read 'DATA'", segname, T_SEGMENT, 4 );
    /* write the .pdata stuff ( type IMAGE_RUNTIME_FUNCTION_ENTRY )*/
    AddLineQueueX( "dd %r %s, %r %s+0%xh, %r $xdatasym+0%xh",
		  T_IMAGEREL, proc->sym.name,
		  T_IMAGEREL, proc->sym.name, proc->sym.total_size,
		  T_IMAGEREL, xdataofs );
    AddLineQueueX("%s %r", segname, T_ENDS );
    olddotname = ModuleInfo.dotname;
    ModuleInfo.dotname = TRUE; /* set OPTION DOTNAME because .pdata and .xdata */
    RunLineQueue();
    ModuleInfo.dotname = olddotname;
    return;
}

static void SetLocalOffsets( struct proc_info *info );

/* close a PROC
 */

static void ProcFini( struct dsym *proc )
/***************************************/
{
    struct dsym *curr;
    /* v2.06: emit an error if current segment isn't equal to
     * the one of the matching PROC directive. Close the proc anyway!
     */
    if ( proc->sym.segment == &CurrSeg->sym ) {
	proc->sym.total_size = GetCurrOffset() - proc->sym.offset;
    } else {
	asmerr( 1010, proc->sym.name );
	proc->sym.total_size = CurrProc->sym.segment->offset - proc->sym.offset;
    }

    /* v2.03: for W3+, check for unused params and locals */
    if ( Options.warning_level > 2 && Parse_Pass == PASS_1 ) {
	for ( curr = proc->e.procinfo->paralist; curr; curr = curr->nextparam ) {
	    if ( curr->sym.used == FALSE )
		asmerr( 6004, curr->sym.name );
	}
	for ( curr = proc->e.procinfo->locallist; curr; curr = curr->nextlocal ) {
	    if ( curr->sym.used == FALSE )
		asmerr( 6004, curr->sym.name );
	}
    }
    /* save stack space reserved for INVOKE if OPTION WIN64:2 is set */
    if ( Parse_Pass == PASS_1 &&
	( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 ) &&
	( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) ) {
	proc->e.procinfo->ReservedStack = sym_ReservedStack->value;
	if ( proc->e.procinfo->fpo ) {
	    for ( curr = proc->e.procinfo->locallist; curr; curr = curr->nextlocal ) {
		curr->sym.offset += proc->e.procinfo->ReservedStack;
	    }
	    for ( curr = proc->e.procinfo->paralist; curr; curr = curr->nextparam ) {
		curr->sym.offset += proc->e.procinfo->ReservedStack;
	    }
	}
    }

    /* create the .pdata and .xdata stuff */
    if ( proc->e.procinfo->isframe ) {
	LstSetPosition(); /* needed if generated code is done BEFORE the line is listed */
	WriteSEHData( proc );
    }
    if ( ModuleInfo.list )
	LstWrite( LSTTYPE_LABEL, 0, NULL );

    /* create the list of locals */
    if ( Parse_Pass == PASS_1 ) {
	/* in case the procedure is empty, init addresses of local variables ( for proper listing ) */
	if( ProcStatus & PRST_PROLOGUE_NOT_DONE )
	    SetLocalOffsets( CurrProc->e.procinfo );
	SymGetLocal( (struct asym *)CurrProc );
    }

    CurrProc = pop_proc();
    if ( CurrProc )
	SymSetLocal( (struct asym *)CurrProc );	 /* restore local symbol table */

    ProcStatus = 0; /* in case there was an empty PROC/ENDP pair */
}

/* ENDP directive */

ret_code EndpDir( int i, struct asm_tok tokenarray[] )
/****************************************************/
{
    if( i != 1 || tokenarray[2].token != T_FINAL ) {
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }
    /* v2.10: "+ 1" added to CurrProc->sym.name_size */
    if( CurrProc &&
       ( SymCmpFunc(CurrProc->sym.name, tokenarray[0].string_ptr, CurrProc->sym.name_size + 1 ) == 0 ) ) {
	ProcFini( CurrProc );
    } else {
	return( asmerr( 1010, tokenarray[0].string_ptr ) );
    }
    return( NOT_ERROR );
}

/* handles win64 directives
 * .allocstack
 * .endprolog
 * .pushframe
 * .pushreg
 * .savereg
 * .savexmm128
 * .setframe
 */

ret_code ExcFrameDirective( int i, struct asm_tok tokenarray[] )
/**************************************************************/
{
    struct expr opndx;
    int token;
    unsigned int size;
    uint_8 oldcodes = unw_info.CountOfCodes;
    uint_8 reg;
    uint_8 ofs;
    UNWIND_CODE *puc;

    /* v2.05: accept directives for windows only */
    if ( Options.output_format != OFORMAT_COFF
	&& ModuleInfo.sub_format != SFORMAT_PE
       ) {
	return( asmerr( 3006, GetResWName( tokenarray[i].tokval, NULL ) ) );
    }
    if ( CurrProc == NULL || endprolog_found == TRUE ) {
	return( asmerr( 3008 ) );
    }
    if ( CurrProc->e.procinfo->isframe == FALSE ) {
	return( asmerr( 3009 ) );
    }

    puc = &unw_code[unw_info.CountOfCodes];

    ofs = GetCurrOffset() - CurrProc->sym.offset;
    token = tokenarray[i].tokval;
    i++;

    /* note: since the codes will be written from "right to left",
     * the opcode item has to be written last!
     */

    switch ( token ) {
    case T_DOT_ALLOCSTACK: /* syntax: .ALLOCSTACK size */
	if ( ERROR == EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) )
	    return( ERROR );
	if ( opndx.kind == EXPR_ADDR && opndx.sym->state == SYM_UNDEFINED ) /* v2.11: allow forward references */
	     ;
	else if ( opndx.kind != EXPR_CONST ) {
	    return( asmerr( 2026 ) );
	}
	/* v2.11: check added */
	if ( opndx.hvalue ) {
	    return( EmitConstError( &opndx ) );
	}
	if ( opndx.uvalue == 0 ) {
	    return( asmerr( 2090 ) );
	}
	if ( opndx.value & 7 ) {
	    return( asmerr( 2189, opndx.value ) );
	}
	if ( opndx.uvalue > 16*8 ) {
	    if ( opndx.uvalue >= 65536*8 ) {
		/* allocation size 512k - 4G-8 */
		/* v2.11: value is stored UNSCALED in 2 WORDs! */
		puc->FrameOffset = ( opndx.uvalue >> 16 );
		puc++;
		puc->FrameOffset = opndx.uvalue & 0xFFFF;
		puc++;
		unw_info.CountOfCodes += 2;
		puc->OpInfo = 1;
	    } else {
		/* allocation size 128+8 - 512k-8 */
		puc->FrameOffset = ( opndx.uvalue >> 3 );
		puc++;
		unw_info.CountOfCodes++;
		puc->OpInfo = 0;
	    }
	    puc->UnwindOp = UWOP_ALLOC_LARGE;
	} else {
	    /* allocation size 8-128 bytes */
	    puc->UnwindOp = UWOP_ALLOC_SMALL;
	    puc->OpInfo = ( (opndx.uvalue - 8 ) >> 3 );
	}
	puc->CodeOffset = ofs;
	unw_info.CountOfCodes++;
	break;
    case T_DOT_ENDPROLOG: /* syntax: .ENDPROLOG */
	opndx.value = GetCurrOffset() - CurrProc->sym.offset;
	if ( opndx.uvalue > 255 ) {
	    return( asmerr( 3010 ) );
	}
	unw_info.SizeOfProlog = (uint_8)opndx.uvalue;
	endprolog_found = TRUE;
	break;
    case T_DOT_PUSHFRAME: /* syntax: .PUSHFRAME [code] */
	puc->CodeOffset = ofs;
	puc->UnwindOp = UWOP_PUSH_MACHFRAME;
	puc->OpInfo = 0;
	if ( tokenarray[i].token == T_ID && (_stricmp( tokenarray[i].string_ptr, "CODE") == 0 ) ) {
	    puc->OpInfo = 1;
	    i++;
	}
	unw_info.CountOfCodes++;
	break;
    case T_DOT_PUSHREG: /* syntax: .PUSHREG r64 */
	if ( tokenarray[i].token != T_REG || !( GetValueSp( tokenarray[i].tokval ) & OP_R64 ) ) {
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}
	puc->CodeOffset = ofs;
	puc->UnwindOp = UWOP_PUSH_NONVOL;
	puc->OpInfo = GetRegNo( tokenarray[i].tokval );
	unw_info.CountOfCodes++;
	i++;
	break;
    case T_DOT_SAVEREG:	   /* syntax: .SAVEREG r64, offset	 */
    case T_DOT_SAVEXMM128: /* syntax: .SAVEXMM128 xmmreg, offset */
    case T_DOT_SETFRAME:   /* syntax: .SETFRAME r64, offset	 */
	if ( tokenarray[i].token != T_REG ) {
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}
	if ( token == T_DOT_SAVEXMM128 ) {
	    if ( !( GetValueSp( tokenarray[i].tokval ) & OP_XMM ) ) {
		return( asmerr(2008, tokenarray[i].string_ptr ) );
	    }
	} else {
	    if ( !( GetValueSp( tokenarray[i].tokval ) & OP_R64 ) ) {
		return( asmerr(2008, tokenarray[i].string_ptr ) );
	    }
	}
	reg = GetRegNo( tokenarray[i].tokval );

	if ( token == T_DOT_SAVEREG )
	    size = 8;
	else
	    size = 16;

	i++;
	if ( tokenarray[i].token != T_COMMA ) {
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}
	i++;
	if ( ERROR == EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) )
	    return( ERROR );
	if ( opndx.kind == EXPR_ADDR && opndx.sym->state == SYM_UNDEFINED ) /* v2.11: allow forward references */
	     ;
	else if ( opndx.kind != EXPR_CONST ) {
	    return( asmerr( 2026 ) );
	}
	if ( opndx.value & (size - 1) ) {
	    return( asmerr( 2189, size ) );
	}
	switch ( token ) {
	case T_DOT_SAVEREG:
	    puc->OpInfo = reg;
	    if ( opndx.value > 65536 * size ) {
		puc->FrameOffset = ( opndx.value >> 19 );
		puc++;
		puc->FrameOffset = ( opndx.value >> 3 );
		puc++;
		puc->UnwindOp = UWOP_SAVE_NONVOL_FAR;
		unw_info.CountOfCodes += 3;
	    } else {
		puc->FrameOffset = ( opndx.value >> 3 );
		puc++;
		puc->UnwindOp = UWOP_SAVE_NONVOL;
		unw_info.CountOfCodes += 2;
	    }
	    puc->CodeOffset = ofs;
	    puc->OpInfo = reg;
	    break;
	case T_DOT_SAVEXMM128:
	    if ( opndx.value > 65536 * size ) {
		puc->FrameOffset = ( opndx.value >> 20 );
		puc++;
		puc->FrameOffset = ( opndx.value >> 4 );
		puc++;
		puc->UnwindOp = UWOP_SAVE_XMM128_FAR;
		unw_info.CountOfCodes += 3;
	    } else {
		puc->FrameOffset = ( opndx.value >> 4 );
		puc++;
		puc->UnwindOp = UWOP_SAVE_XMM128;
		unw_info.CountOfCodes += 2;
	    }
	    puc->CodeOffset = ofs;
	    puc->OpInfo = reg;
	    break;
	case T_DOT_SETFRAME:
	    if ( opndx.uvalue > 240 ) {
		return( EmitConstError( &opndx ) );
	    }
	    unw_info.FrameRegister = reg;
	    unw_info.FrameOffset = ( opndx.uvalue >> 4 );
	    puc->CodeOffset = ofs;
	    puc->UnwindOp = UWOP_SET_FPREG;
	    puc->OpInfo = reg;
	    unw_info.CountOfCodes++;
	    break;
	}
	break;
    }
    if ( tokenarray[i].token != T_FINAL ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    /* v2.11: check if the table of codes has been exceeded */
    if ( oldcodes > unw_info.CountOfCodes ) {
	return( asmerr( 3011 ) );
    }
    return( NOT_ERROR );
}

/* see if there are open procedures.
 * called when the END directive has been found.
 */
void ProcCheckOpen( void )
/************************/
{
    while( CurrProc != NULL ) {
	asmerr( 1010, CurrProc->sym.name );
	ProcFini( CurrProc );
    }
}

static ret_code write_userdef_prologue( struct asm_tok tokenarray[] )
/*******************************************************************/
{
    int			len;
    int			i;
    struct proc_info	*info;
    char		*p;
    bool		is_exitm;
    struct dsym		*dir;
    int			flags = CurrProc->sym.langtype; /* set bits 0-2 */
    uint_16		*regs;
    char		reglst[128];
    char		buffer[MAX_LINE_LEN];

    if ( Parse_Pass > PASS_1 && UseSavedState )
	return( NOT_ERROR );

    info = CurrProc->e.procinfo;
    /* to be compatible with ML64, translate FASTCALL to 0 (not 7) */
    if ( CurrProc->sym.langtype == LANG_FASTCALL && ModuleInfo.fctype == FCT_WIN64 )
	flags = 0;
    /* set bit 4 if the caller restores (E)SP */
    if (CurrProc->sym.langtype == LANG_C ||
	CurrProc->sym.langtype == LANG_SYSCALL ||
	CurrProc->sym.langtype == LANG_FASTCALL )
	flags |= 0x10;

    /* set bit 5 if proc is far */
    /* set bit 6 if proc is private */
    /* v2.11: set bit 7 if proc is export */
    flags |= ( CurrProc->sym.mem_type == MT_FAR ? 0x20 : 0 );
    flags |= ( CurrProc->sym.ispublic ? 0 : 0x40 );
    flags |= ( info->isexport ? 0x80 : 0 );

    dir = (struct dsym *)SymSearch( ModuleInfo.proc_prologue );
    if ( dir == NULL || dir->sym.state != SYM_MACRO || dir->sym.isfunc != TRUE ) {
	return( asmerr( 2120 ) );
    }

    /* if -EP is on, emit "prologue: none" */
    if ( Options.preprocessor_stdout )
	printf( "option prologue:none\n" );

    p = reglst;
    if ( info->regslist ) {
	regs = info->regslist;
	for ( len = *regs++; len; len--, regs++ ) {
	    GetResWName( *regs, p );
	    p += strlen( p );
	    if ( len > 1 )
		*p++ = ',';
	}
    }
    *p = NULLC;

    /* v2.07: make this work with radix != 10 */
    /* leave a space at pos 0 of buffer, because the buffer is used for
     * both macro arguments and EXITM return value.
     */
    sprintf( buffer," (%s, 0%XH, 0%XH, 0%XH, <<%s>>, <%s>)",
	     CurrProc->sym.name, flags, info->parasize, info->localsize,
	    reglst, info->prologuearg ? info->prologuearg : "" );
    i = Token_Count + 1;
    Token_Count = Tokenize( buffer, i, tokenarray, TOK_RESCAN );

    RunMacro( dir, i, tokenarray, buffer, 0, &is_exitm );
    Token_Count = i - 1;

    if ( Parse_Pass == PASS_1 ) {
	struct dsym *curr;
	len = atoi( buffer ) - info->localsize;
	for ( curr = info->locallist; curr; curr = curr->nextlocal ) {
	    curr->sym.offset -= len;
	}
    }

    return ( NOT_ERROR );
}

/* OPTION WIN64:1 - save up to 4 register parameters for WIN64 fastcall */
/* v2.27 - save up to 6 register parameters for WIN64 vectorcall */

static void win64_SaveRegParams( struct proc_info *info )
{
    int i;
    struct dsym *param;
    int count = 4;
    int size = 8;

    if ( CurrProc->sym.langtype == LANG_VECTORCALL ) {
	count = 6;
	size = 16;
    }

    for ( i = 0, param = info->paralist; param && ( i < count ); i++ ) {
	/* v2.05: save XMMx if type is float/double */
	if ( param->sym.is_vararg == FALSE ) {
	    if ( param->sym.mem_type & MT_FLOAT ) {
		if ( param->sym.mem_type == MT_REAL4 )
		    AddLineQueueX( "movd [%r+%u], %r", T_RSP, 8 + i * size, T_XMM0 + i );
		else if ( param->sym.mem_type == MT_REAL8 )
		    AddLineQueueX( "movq [%r+%u], %r", T_RSP, 8 + i * size, T_XMM0 + i );
		else
		    AddLineQueueX( "movaps [%r+%u], %r", T_RSP, 8 + i * size, T_XMM0 + i );
	    } else
		AddLineQueueX( "mov [%r+%u], %r", T_RSP, 8 + i * size, ms64_regs[i] );
	    param = param->nextparam;
	} else { /* v2.09: else branch added */
	    AddLineQueueX( "mov [%r+%u], %r", T_RSP, 8 + i * size, ms64_regs[i] );
	}
    }
    return;
}

/* win64 default prologue when PROC FRAME and
 * OPTION FRAME:AUTO is set */

static void write_win64_default_prologue( struct proc_info *info )
{
    uint_16 *regist;
    const char * const *ppfmt;
    int cntxmm;
    int resstack = ( ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) ? sym_ReservedStack->value : 0 );

    if ( ModuleInfo.win64_flags & W64F_SAVEREGPARAMS )
	win64_SaveRegParams( info );
    /*
     * PUSH RBP
     * .PUSHREG RBP
     * MOV RBP, RSP
     * .SETFRAME RBP, 0
     */
    /* info->locallist tells whether there are local variables ( info->localsize doesn't! ) */
    if ( info->fpo || ( info->parasize == 0 && info->locallist == NULL ) ) {
    } else {
	AddLineQueueX( "push %r", info->basereg );
	AddLineQueueX( "%r %r", T_DOT_PUSHREG, info->basereg );
	AddLineQueueX( "mov %r, %r", info->basereg, T_RSP );
	AddLineQueueX( "%r %r, 0", T_DOT_SETFRAME, info->basereg );
    }

    /* after the "push rbp", the stack is xmmword aligned */

    /* Push the registers */
    cntxmm = 0;
    if( info->regslist ) {
	int cnt;
	regist = info->regslist;
	for( cnt = *regist++; cnt; cnt--, regist++ ) {
	    if ( GetValueSp( *regist ) & OP_XMM ) {
		cntxmm += 1;
	    } else {
		AddLineQueueX( "push %r", *regist );
		if ( ( 1 << GetRegNo( *regist ) ) & win64_nvgpr ) {
		    AddLineQueueX( "%r %r", T_DOT_PUSHREG, *regist );
		}
	    }
	} /* end for */
    }
    /* alloc space for local variables */
    if( info->localsize + resstack ) {

	/*
	 * SUB	RSP, localsize
	 * .ALLOCSTACK localsize
	 */
	ppfmt = ( resstack ? fmtstk1 : fmtstk0 );
#if STACKPROBE
	if ( info->localsize + resstack > 0x1000 ) {
	    AddLineQueueX( *(ppfmt+2), T_RAX, NUMQUAL info->localsize, sym_ReservedStack->name );
	    AddLineQueue(  "externdef __chkstk:PROC" );
	    AddLineQueue(  "call __chkstk" );
	    AddLineQueueX( "mov %r, %r", T_RSP, T_RAX );
	} else
#endif
	    AddLineQueueX( *(ppfmt+0), T_RSP, NUMQUAL info->localsize, sym_ReservedStack->name );
	AddLineQueueX( *(ppfmt+1), T_DOT_ALLOCSTACK, NUMQUAL info->localsize, sym_ReservedStack->name );

	/* save xmm registers */
	if ( cntxmm ) {
	    int i;
	    int cnt;
	    i = ( info->localsize - cntxmm * 16 ) & ~(16-1);
	    regist = info->regslist;
	    for( cnt = *regist++; cnt; cnt--, regist++ ) {
		if ( GetValueSp( *regist ) & OP_XMM ) {
		    if ( resstack ) {
			AddLineQueueX( "movdqa [%r+%u+%s], %r", T_RSP, NUMQUAL i, sym_ReservedStack->name, *regist );
			if ( ( 1 << GetRegNo( *regist ) ) & win64_nvxmm )  {
			    AddLineQueueX( "%r %r, %u+%s", T_DOT_SAVEXMM128, *regist, NUMQUAL i, sym_ReservedStack->name );
			}
		    } else {
			AddLineQueueX( "movdqa [%r+%u], %r", T_RSP, NUMQUAL i, *regist );
			if ( ( 1 << GetRegNo( *regist ) ) & win64_nvxmm )  {
			    AddLineQueueX( "%r %r, %u", T_DOT_SAVEXMM128, *regist, NUMQUAL i );
			}
		    }
		    i += 16;
		}
	    }
	}

    }
    AddLineQueueX( "%r", T_DOT_ENDPROLOG );

    /* v2.11: linequeue is now run in write_default_prologue() */
    return;
}

/* write PROC prologue
 * this is to be done after the LOCAL directives
 * and *before* any real instruction
 */
/* prolog code timings

						  best result
	       size  86	 286  386  486	P     86  286  386  486	 P
 push bp       2     11	 3    2	   1	1
 mov bp,sp     2     2	 2    2	   1	1
 sub sp,immed  4     4	 3    2	   1	1
	      -----------------------------
	       8     17	 8    6	   3	3     x	  x    x    x	 x

 push ebp      2     -	 -    2	   1	1
 mov ebp,esp   2     -	 -    2	   1	1
 sub esp,immed 6     -	 -    2	   1	1
	      -----------------------------
	       10    -	 -    6	   3	3	       x    x	 x

 enter imm,0   4     -	 11   10   14	11

 write prolog code
*/

static int write_default_prologue( void )
{
    struct proc_info *info;
    uint_16 *regist;
    uint_8 oldlinenumbers;
    int cnt;
    int offset;
    struct dsym *p;
    int resstack = 0;
    int cstack = ( ( ModuleInfo.aflag & _AF_CSTACK ) &&
	( ( ( CurrProc->sym.langtype == LANG_STDCALL || CurrProc->sym.langtype == LANG_C ) &&
	    ModuleInfo.Ofssize == USE32 ) ||
	  ( ( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 ) &&
	    ModuleInfo.Ofssize == USE64 ) ) );

    info = CurrProc->e.procinfo;

    if ( info->isframe ) {
	if ( ModuleInfo.frame_auto ) {
	    write_win64_default_prologue( info );
	    /* v2.11: line queue is now run here */
	    goto runqueue;
	}
	return( NOT_ERROR );
    }
    if ( ModuleInfo.Ofssize == USE64 && ( ModuleInfo.fctype == FCT_WIN64 ||
	 ModuleInfo.fctype == FCT_VEC64 ) && ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )
	resstack = sym_ReservedStack->value;
    /* default processing. if no params/locals are defined, continue */
    if( info->forceframe == FALSE &&
       info->localsize == 0 &&
       info->stackparam == FALSE &&
       info->has_vararg == FALSE &&
       resstack == 0 &&
       info->regslist == NULL )
	return( NOT_ERROR );

    regist = info->regslist;

    /* initialize shadow space for register params */
    if ( ModuleInfo.Ofssize == USE64 &&
	( ( CurrProc->sym.langtype == LANG_FASTCALL && ModuleInfo.fctype == FCT_WIN64 ) ||
	  ( CurrProc->sym.langtype == LANG_VECTORCALL && ModuleInfo.fctype == FCT_VEC64 ) ) ) {

	if ( ModuleInfo.win64_flags & W64F_SAVEREGPARAMS )
	    win64_SaveRegParams( info );

	if ( ModuleInfo.fctype == FCT_VEC64 ) {

	    /* set param offset to 16 */
	    for ( p = info->paralist; p; p = p->nextparam )
		if ( !p->nextparam ) break;

	    if ( p && Parse_Pass == PASS_1 ) {
		for ( cnt = 0, offset = 16, p = info->paralist; p && cnt < 6;
			p = p->nextparam, offset += 16, cnt++ )
		    p->sym.offset = offset;
	    }
	}
    }

    /* Push the USES registers first if -Cs */

    if ( regist && cstack ) {

	offset = 0;

	for (cnt = *regist++; cnt; cnt--, regist++) {

	    offset += ModuleInfo.Ofssize << 2;
	    AddLineQueueX( "push %r", *regist );
	}
	regist = NULL;

	for ( p = info->paralist; p; p = p->nextparam )
	    if ( !p->nextparam ) break;

	if ( p ) {
	    /* v2.23 - skip adding if stackbase is not EBP */
	    if ( ( p->sym.offset == 8 && ModuleInfo.basereg[ModuleInfo.Ofssize] == T_EBP ) ||
	    ( Parse_Pass == PASS_1 && info->pe_type && ModuleInfo.Ofssize == USE64 ) )

	    for ( p = info->paralist; p; p = p->nextparam )
		if ( p->sym.state != SYM_TMACRO ) /* register param? */
		    p->sym.offset += offset;
	}

    }

    if( info->locallist || info->stackparam || info->has_vararg || info->forceframe ) {

	/* write 80386 prolog code
	 * PUSH [E|R]BP
	 * MOV	[E|R]BP, [E|R]SP
	 * SUB	[E|R]SP, localsize
	 */
	if ( !info->fpo ) {
	    AddLineQueueX( "push %r", info->basereg );
	    AddLineQueueX( "mov %r, %r", info->basereg, stackreg[ModuleInfo.Ofssize] );
	}
    }
    if( resstack ) {
	/* in this case, push the USES registers BEFORE the stack space is reserved */
	if ( regist ) {
	    for( cnt = *regist++; cnt; cnt--, regist++ )
		AddLineQueueX( "push %r", *regist );
	    regist = NULL;
	}
	AddLineQueueX( "sub %r, %d + %s", stackreg[ModuleInfo.Ofssize], NUMQUAL info->localsize, sym_ReservedStack->name );

    } else if( info->localsize ) {
	/* using ADD and the 2-complement has one advantage:
	 * it will generate short instructions up to a size of 128.
	 * with SUB, short instructions work up to 127 only.
	 */
	if ( Options.masm_compat_gencode || info->localsize == 128 )
	    AddLineQueueX( "add %r, %d", stackreg[ModuleInfo.Ofssize], NUMQUAL - info->localsize );
	else
	    AddLineQueueX( "sub %r, %d", stackreg[ModuleInfo.Ofssize], NUMQUAL info->localsize );
    }

    if ( info->loadds ) {
	AddLineQueueX( "push %r", T_DS );
	AddLineQueueX( "mov %r, %s", T_AX, szDgroup );
	AddLineQueueX( "mov %r, %r", T_DS, ModuleInfo.Ofssize ? T_EAX : T_AX );
    }

    /* Push the USES registers first if stdcall-32 */
    /* Push the GPR registers of the USES clause */
    if (regist && cstack == 0) {
	for( cnt = *regist++; cnt; cnt--, regist++ ) {
	    AddLineQueueX( "push %r", *regist );
	}
    }

runqueue:

    /* special case: generated code runs BEFORE the line.*/
    if ( ModuleInfo.list && UseSavedState )
	if ( Parse_Pass == PASS_1 )
	    info->prolog_list_pos = list_pos;
	else
	    list_pos = info->prolog_list_pos;
    /* line number debug info also needs special treatment
     * because current line number is the first true src line
     * IN the proc.
     */
    oldlinenumbers = Options.line_numbers;
    Options.line_numbers = FALSE; /* temporarily disable line numbers */
    RunLineQueue();
    Options.line_numbers = oldlinenumbers;

    if ( ModuleInfo.list && UseSavedState && (Parse_Pass > PASS_1))
	 LineStoreCurr->list_pos = list_pos;

    return( NOT_ERROR );
}

/* v2.12: calculate offsets of local variables; this is now
 * done here after ALL locals have been defined.
 * will set value of member 'localsize'.
 * Notes:
 * 64-bit: 16-byte RSP alignment works for
 * - FRAME procedures ( if OPTION FRAME:AUTO is set )
 * - non-frame procedures if option win64:2 is set
 * this means that option win64:4 ( 16-byte stack variable alignment )
 * will also work only in those cases!
 */

static void SetLocalOffsets( struct proc_info *info )
{
    struct dsym *curr;
    int cntxmm = 0;
    int cntstd = 0;
    int start = 0;
    int regsize = 0; /* v2.25 - option cstack:on */
    int rspalign = FALSE;
    int align = CurrWordSize;
    int wsize = CurrWordSize;

    if ( ModuleInfo.fctype == FCT_VEC64 )
	wsize = 16;

    if ( info->isframe || ( ( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 ) &&
	( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) ) ) {

	rspalign = TRUE;
	if ( ModuleInfo.win64_flags & W64F_STACKALIGN16 || ModuleInfo.fctype == FCT_VEC64 )
	    align = 16;
    }
    /* in 64-bit, if the FRAME attribute is set, the space for the registers
     * saved by the USES clause is located ABOVE the local variables!
     * v2.09: if stack space is to be reserved for INVOKE ( option WIN64:2 ),
     * the registers are also saved ABOVE the local variables.
     */
    if (info->fpo || rspalign) {
	/* count registers to be saved ABOVE local variables.
	 * v2.06: the list may contain xmm registers, which have size 16!
	 */
	if ( info->regslist ) {
	    int		cnt;
	    uint_16	*regs;
	    for( regs = info->regslist, cnt = *regs++; cnt; cnt--, regs++ )
		if ( GetValueSp( *regs ) & OP_XMM )
		    cntxmm++;
		else
		    cntstd++;
	}
	/* in case there's no frame register, adjust start offset. */
	if ( ( info->fpo || ( info->parasize == 0 && info->locallist == NULL ) ) )
	    start = CurrWordSize;
	if ( rspalign ) {
	    info->localsize = start + cntstd * wsize;
	    if ( cntxmm ) {
		info->localsize += 16 * cntxmm;
		info->localsize = ROUND_UP( info->localsize, 16 );
	    }
	}
    }

    if ( ( ModuleInfo.aflag & _AF_CSTACK ) &&
	( ModuleInfo.basereg[ModuleInfo.Ofssize] == T_RBP ||
	  ModuleInfo.basereg[ModuleInfo.Ofssize] == T_EBP ) ) {
	regsize = wsize * cntstd + 16 * cntxmm;
    }

    /* scan the locals list and set member sym.offset */
    for( curr = info->locallist; curr; curr = curr->nextlocal ) {
	uint_32 itemsize = ( curr->sym.total_size == 0 ? 0 : curr->sym.total_size / curr->sym.total_length );
	info->localsize += curr->sym.total_size;
	if ( itemsize > align )
	    info->localsize = ROUND_UP( info->localsize, align );
	else if ( itemsize ) /* v2.04: skip if size == 0 */
	    info->localsize = ROUND_UP( info->localsize, itemsize );
	curr->sym.offset = - info->localsize + regsize;
    }

    /* v2.11: localsize must be rounded before offset adjustment if fpo */
    info->localsize = ROUND_UP( info->localsize, wsize );
    /* RSP 16-byte alignment? */
    if ( rspalign ) {
	info->localsize = ROUND_UP( info->localsize, 16 );
    }

    /* v2.11: recalculate offsets for params and locals if there's no frame pointer.
     * Problem in 64-bit: option win64:2 triggers the "stack space reservation" feature -
     * but the final value of this space is known at the procedure's END only.
     * Hence in this case the values calculated below are "preliminary".
     */
    if ( info->fpo ) {
	unsigned localadj;
	unsigned paramadj;
	if ( rspalign ) {
	    localadj = info->localsize;
	    paramadj = info->localsize - CurrWordSize - start;
	} else {
	    localadj = info->localsize + cntstd * CurrWordSize;
	    paramadj = info->localsize + cntstd * CurrWordSize - CurrWordSize;
	}
	/* subtract CurrWordSize value for params, since no space is required to save the frame pointer value */
	for ( curr = info->locallist; curr; curr = curr->nextlocal ) {
	    curr->sym.offset += localadj;
	}
	for ( curr = info->paralist; curr; curr = curr->nextparam ) {
	    curr->sym.offset += paramadj;
	}
    }

    /* v2.12: if the space used for register saves has been added to localsize,
     * the part that covers "pushed" GPRs has to be subtracted now, before prologue code is generated.
     */
    if ( rspalign ) {
	info->localsize -= cntstd * wsize + start;
    }
}

void write_prologue( struct asm_tok tokenarray[] )
{
    /* reset @ProcStatus flag */
    ProcStatus &= ~PRST_PROLOGUE_NOT_DONE;

    if ( ( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 ) &&
	( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) ) {
	/* in pass one init reserved stack with 4*8 to force stack frame creation */
	if ( Parse_Pass == PASS_1 ) {
	    sym_ReservedStack->value = 4 * sizeof( uint_64 );
	    if ( CurrProc->sym.langtype == LANG_VECTORCALL )
		sym_ReservedStack->value = 6 * 16;
	} else {
	    sym_ReservedStack->value = CurrProc->e.procinfo->ReservedStack;
	}
    }
    if ( Parse_Pass == PASS_1 ) {
	/* v2.12: calculation of offsets of local variables is done delayed now */
	SetLocalOffsets( CurrProc->e.procinfo );
    }
    ProcStatus |= PRST_INSIDE_PROLOGUE;
    /* there are 3 cases:
     * option prologue:NONE	      proc_prologue == NULL
     * option prologue:default	      *proc_prologue == NULLC
     * option prologue:usermacro      *proc_prologue != NULLC
     */
    if ( ModuleInfo.prologuemode == PEM_DEFAULT ) {
	write_default_prologue();
    } else if ( ModuleInfo.prologuemode == PEM_NONE ) {
    } else {
	write_userdef_prologue( tokenarray );
    }
    ProcStatus &= ~PRST_INSIDE_PROLOGUE;
    /* v2.10: for debug info, calculate prologue size */
    CurrProc->e.procinfo->size_prolog = GetCurrOffset() - CurrProc->sym.offset;
    return;
}

static void pop_register( uint_16 *regist )
/* Pop the register when a procedure ends */
{
    int cnt;
    if( regist == NULL )
	return;
    cnt = *regist;
    regist += cnt;
    for ( ; cnt; cnt--, regist-- ) {
	/* don't "pop" xmm registers */
	if ( GetValueSp( *regist ) & OP_XMM )
	    continue;
	AddLineQueueX( "pop %r", *regist );
    }
}

/* Win64 default epilogue if PROC FRAME and OPTION FRAME:AUTO is set
 */

static void write_win64_default_epilogue( struct proc_info *info )
{
    /* restore non-volatile xmm registers */
    if ( info->regslist ) {
	uint_16 *regs;
	int cnt;
	int i;

	/* v2.12: space for xmm saves is now included in localsize
	 * so first thing to do is to count the xmm regs that were saved
	 */
	for( regs = info->regslist, cnt = *regs++, i = 0; cnt; cnt--, regs++ )
	    if ( GetValueSp( *regs ) & OP_XMM )
		i++;

	if ( i ) {
	    i = ( info->localsize - i * 16 ) & ~(16-1);
	    for( regs = info->regslist, cnt = *regs++; cnt; cnt--, regs++ ) {
		if ( GetValueSp( *regs ) & OP_XMM ) {
		    /* v2.11: use @ReservedStack only if option win64:2 is set */
		    if ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP )
			AddLineQueueX( "movdqa %r, [%r + %u + %s]", *regs, stackreg[ModuleInfo.Ofssize], NUMQUAL i, sym_ReservedStack->name );
		    else
			AddLineQueueX( "movdqa %r, [%r + %u]", *regs, stackreg[ModuleInfo.Ofssize], NUMQUAL i );
		    i += 16;
		}
	    }
	}
    }

    if ( ( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 ) &&
	( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) ) {
	if ( ModuleInfo.epilogueflags )
	    AddLineQueueX( "lea %r, [%r + %d + %s]",
		stackreg[ModuleInfo.Ofssize], stackreg[ModuleInfo.Ofssize], NUMQUAL info->localsize, sym_ReservedStack->name );
	else
	    AddLineQueueX( "add %r, %d + %s", stackreg[ModuleInfo.Ofssize], NUMQUAL info->localsize, sym_ReservedStack->name );
    } else {
	if ( ModuleInfo.epilogueflags )
	    AddLineQueueX( "lea %r, [%r+%d]",
		stackreg[ModuleInfo.Ofssize], stackreg[ModuleInfo.Ofssize], NUMQUAL info->localsize );
	else
	    AddLineQueueX( "add %r, %d", stackreg[ModuleInfo.Ofssize], NUMQUAL info->localsize );
    }
    pop_register( CurrProc->e.procinfo->regslist );
    if ( ( GetRegNo( info->basereg ) != 4 && ( info->parasize != 0 || info->locallist != NULL ) ) )
	AddLineQueueX( "pop %r", info->basereg );
    return;
}


/* write default epilogue code
 * if a RET/IRET instruction has been found inside a PROC.

 * epilog code timings
 *
 *						    best result
 *		size  86  286  386  486	 P	86  286	 386  486  P
 * mov sp,bp	2     2	  2    2    1	 1
 * pop bp	2     8	  5    4    4	 1
 *	       -----------------------------
 *		4     10  7    6    5	 2	x	      x	   x
 *
 * mov esp,ebp	2     -	  -    2    1	 1
 * pop ebp	2     -	  -    4    4	 1
 *	       -----------------------------
 *		4     -	  -    6    5	 2		      x	   x
 *
 * leave	1     -	  5    4    5	 3	    x	 x    x
 *
 * !!!! DECISION !!!!
 *
 * leave will be used for .286 and .386
 * .286 code will be best working on 286,386 and 486 processors
 * .386 code will be best working on 386 and 486 processors
 * .486 code will be best working on 486 and above processors
 *
 *   without LEAVE
 *
 *	   86  286  386	 486  P
 *  .8086  0   -2   -2	 0    +1
 *  .286   -   -2   -2	 0    +1
 *  .386   -   -    -2	 0    +1
 *  .486   -   -    -	 0    +1
 *
 *   LEAVE 286 only
 *
 *	   86  286  386	 486  P
 *  .8086  0   -2   -2	 0    +1
 *  .286   -   0    +2	 0    -1
 *  .386   -   -    -2	 0    +1
 *  .486   -   -    -	 0    +1
 *
 *   LEAVE 286 and 386
 *
 *	   86  286  386	 486  P
 *  .8086  0   -2   -2	 0    +1
 *  .286   -   0    +2	 0    -1
 *  .386   -   -    0	 0    -1
 *  .486   -   -    -	 0    +1
 *
 *   LEAVE 286, 386 and 486
 *
 *	   86  286  386	 486  P
 *  .8086  0   -2   -2	 0    +1
 *  .286   -   0    +2	 0    -1
 *  .386   -   -    0	 0    -1
 *  .486   -   -    -	 0    -1
 */

static void write_default_epilogue( void )
{
    struct proc_info   *info;
    int resstack = 0;
    int cstack = ( ( ModuleInfo.aflag & _AF_CSTACK ) &&
	( ( ( CurrProc->sym.langtype == LANG_STDCALL || CurrProc->sym.langtype == LANG_C ) &&
	   ModuleInfo.Ofssize == USE32 ) ||
	  ( ( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 ) &&
	      ModuleInfo.Ofssize == USE64 ) ) );

    info = CurrProc->e.procinfo;

    if ( info->isframe ) {
	if ( ModuleInfo.frame_auto )
	    write_win64_default_epilogue( info );
	return;
    }
    if ( ModuleInfo.Ofssize == USE64 &&
	 ( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 ) &&
       ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) ) {

	resstack  = sym_ReservedStack->value;
	/* if no framepointer was pushed, add 8 to align stack on OWORD
	 * v2.12: obsolete; localsize contains correct value.
	 */
	if ( cstack && (info->locallist	 || info->stackparam ||
			info->has_vararg || info->forceframe ) && info->pe_type )
	    ; /* v2.21: leave will follow.. */
	else if ( !cstack && (info->locallist || info->stackparam ||
		  info->has_vararg || info->forceframe ) && info->pe_type &&
		  !CurrProc->e.procinfo->regslist && info->basereg == T_RBP )
	    ; /* v2.27: leave will follow.. */
	else {
	    if ( ModuleInfo.epilogueflags )
		AddLineQueueX( "lea %r, [%r + %d + %s]",
			stackreg[ModuleInfo.Ofssize], stackreg[ModuleInfo.Ofssize],
			NUMQUAL info->localsize, sym_ReservedStack->name );
	    else
		AddLineQueueX( "add %r, %d + %s",
			stackreg[ModuleInfo.Ofssize], NUMQUAL info->localsize, sym_ReservedStack->name );
	}
    }

    if ( cstack == 0 ) {
	/* Pop the registers */
	pop_register( CurrProc->e.procinfo->regslist );

	if ( info->loadds ) {
	    AddLineQueueX( "pop %r", T_DS );
	}
    }

    if( ( info->locallist == NULL ) &&
       info->stackparam == FALSE &&
       info->has_vararg == FALSE &&
       resstack == 0 &&
       info->forceframe == FALSE ) {

	if ( cstack ) {
	    /* Pop the registers */
	    pop_register( CurrProc->e.procinfo->regslist );
	    if ( info->loadds ) {
		AddLineQueueX( "pop %r", T_DS );
	    }
	}
	return;
    }

    /* restore registers e/sp and e/bp.
     * emit either "leave" or "mov e/sp,e/bp, pop e/bp".
     */
    if ( !(info->locallist || info->stackparam || info->has_vararg || info->forceframe )) {

	;
    } else if( info->pe_type ) {

	AddLineQueue( "leave" );
    } else  {

	if ( info->fpo ) {
	    if ( ModuleInfo.Ofssize == USE64 &&
		( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 ) &&
		( ModuleInfo.win64_flags & W64F_AUTOSTACKSP ) )
		;
	    else if ( info->localsize ) {
		if ( ModuleInfo.epilogueflags )
		    AddLineQueueX( "lea %r, [%r+%d]",
			stackreg[ModuleInfo.Ofssize], stackreg[ModuleInfo.Ofssize], NUMQUAL info->localsize );
		else
		    AddLineQueueX( "add %r, %d", stackreg[ModuleInfo.Ofssize], NUMQUAL info->localsize );
	    }
	} else {
	/*
	 MOV [E|R]SP, [E|R]BP
	 POP [E|R]BP
	 */
	    if( info->localsize != 0 ) {
		AddLineQueueX( "mov %r, %r", stackreg[ModuleInfo.Ofssize], info->basereg );
	    }
	    AddLineQueueX( "pop %r", info->basereg );
	}
    }

    if ( cstack ) {
	/* Pop the registers */
	pop_register( CurrProc->e.procinfo->regslist );

	if ( info->loadds ) {
	    AddLineQueueX( "pop %r", T_DS );
	}
    }
}

/* write userdefined epilogue code
 * if a RET/IRET instruction has been found inside a PROC.
 */
static ret_code write_userdef_epilogue( bool flag_iret, struct asm_tok tokenarray[] )
{
    uint_16 *regs;
    int i;
    char *p;
    bool is_exitm;
    struct proc_info   *info;
    int flags = CurrProc->sym.langtype; /* set bits 0-2 */
    struct dsym *dir;
    char reglst[128];
    char buffer[MAX_LINE_LEN]; /* stores string for RunMacro() */

    dir = (struct dsym *)SymSearch( ModuleInfo.proc_epilogue );
    if (dir == NULL ||
	dir->sym.state != SYM_MACRO ||
	dir->sym.isfunc == TRUE ) {
	return( asmerr( 2121, ModuleInfo.proc_epilogue ) );
    }

    info = CurrProc->e.procinfo;

    /* to be compatible with ML64, translate FASTCALL to 0 (not 7) */
    if ( CurrProc->sym.langtype == LANG_FASTCALL && ModuleInfo.fctype == FCT_WIN64 )
	flags = 0;
    if (CurrProc->sym.langtype == LANG_C ||
	CurrProc->sym.langtype == LANG_SYSCALL ||
	CurrProc->sym.langtype == LANG_FASTCALL)
	flags |= 0x10;

    flags |= ( CurrProc->sym.mem_type == MT_FAR ? 0x20 : 0 );
    flags |= ( CurrProc->sym.ispublic ? 0 : 0x40 );
    /* v2.11: set bit 7, the export flag */
    flags |= ( info->isexport ? 0x80 : 0 );
    flags |= flag_iret ? 0x100 : 0;  /* bit 8: 1 if IRET    */

    p = reglst;
    if ( info->regslist ) {
	int cnt = *info->regslist;
	regs = info->regslist + cnt;
	for ( ; cnt; regs--, cnt-- ) {
	    GetResWName( *regs, p );
	    p += strlen( p );
	    if ( cnt != 1 )
		*p++ = ',';
	}
    }
    *p = NULLC;
    sprintf( buffer,"%s, 0%XH, 0%XH, 0%XH, <<%s>>, <%s>",
	    CurrProc->sym.name, flags, info->parasize, info->localsize,
	    reglst, info->prologuearg ? info->prologuearg : "" );
    i = Token_Count + 1;
    Tokenize( buffer, i, tokenarray, TOK_RESCAN );

    /* if -EP is on, emit "epilogue: none" */
    if ( Options.preprocessor_stdout )
	printf( "option epilogue:none\n" );

    RunMacro( dir, i, tokenarray, NULL, 0, &is_exitm );
    Token_Count = i - 1;
    return( NOT_ERROR );
}

/* a RET <nnnn> or IRET/IRETD has occured inside a PROC.
 * count = number of tokens in buffer (=Token_Count)
 * it's ensured already that ModuleInfo.proc_epilogue isn't NULL.
 */
ret_code RetInstr( int i, struct asm_tok tokenarray[], int count )
{
    struct proc_info   *info;
    bool	is_iret = FALSE;
    char	*p;
    char	buffer[MAX_LINE_LEN]; /* stores modified RETN/RETF/IRET instruction */

    if( tokenarray[i].tokval == T_IRET || tokenarray[i].tokval == T_IRETD || tokenarray[i].tokval == T_IRETQ )
	is_iret = TRUE;

    if ( ModuleInfo.epiloguemode == PEM_MACRO ) {
	/* don't run userdefined epilogue macro if pass > 1 */
	if ( UseSavedState ) {
	    if ( Parse_Pass > PASS_1 ) {
		return( ParseLine( tokenarray ) );
	    }
	    /* handle the current line as if it is REPLACED by the macro content */
	    *(LineStoreCurr->line) = ';';
	}
	return( write_userdef_epilogue( is_iret, tokenarray ) );
    }

    if ( ModuleInfo.list ) {
	LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL );
    }

    strcpy( buffer, tokenarray[i].string_ptr );
    p = buffer + strlen( buffer );

    write_default_epilogue();

    info = CurrProc->e.procinfo;

    /* skip this part for IRET */
    if( is_iret == FALSE ) {
	if ( CurrProc->sym.mem_type == MT_FAR )
	    *p++ = 'f';	  /* ret -> retf */
	else
	    *p++ = 'n';	    /* ret -> retn */
    }
    i++; /* skip directive */
    if ( info->parasize || ( count != i ) )
	*p++ = ' ';
    *p = NULLC;
    /* RET without argument? Then calculate the value */
    if( is_iret == FALSE && count == i ) {
	if ( ModuleInfo.epiloguemode != PEM_NONE ) {
	    switch( CurrProc->sym.langtype ) {
	    case LANG_BASIC:
	    case LANG_FORTRAN:
	    case LANG_PASCAL:
		if( info->parasize != 0 )
		    sprintf( p, "%d%c", info->parasize, ModuleInfo.radix != 10 ? 't' : NULLC );
		break;
	    case LANG_SYSCALL:
	    if ( ModuleInfo.Ofssize != USE64 )
		break;

	    case LANG_FASTCALL:
	    case LANG_VECTORCALL:
		fastcall_tab[ModuleInfo.fctype].handlereturn( CurrProc, buffer );
		break;
	    case LANG_STDCALL:
		if( !info->has_vararg && info->parasize != 0 )
		    sprintf( p, "%d%c", info->parasize, ModuleInfo.radix != 10 ? 't' : NULLC  );
		break;
	    }
	}
    } else {
	/* v2.04: changed. Now works for both RET nn and IRETx */
	/* v2.06: changed. Now works even if RET has ben "renamed" */
	strcpy( p, tokenarray[i].tokpos );
    }
    AddLineQueue( buffer );
    RunLineQueue();

    return( NOT_ERROR );
}

/* init this module. called for every pass. */

void ProcInit( void )
/*******************/
{
    ProcStack = NULL;
    CurrProc  = NULL;
    procidx = 1;
    ProcStatus = 0;
    /* v2.09: reset prolog and epilog mode */
    ModuleInfo.prologuemode = PEM_DEFAULT;
    ModuleInfo.epiloguemode = PEM_DEFAULT;
    /* v2.06: no forward references in INVOKE if -Zne is set */
    ModuleInfo.invoke_exprparm = ( Options.strict_masm_compat ? EXPF_NOUNDEF : 0 );
    ModuleInfo.basereg[USE16] = T_BP;
    ModuleInfo.basereg[USE32] = T_EBP;
    ModuleInfo.basereg[USE64] = T_RBP;
    unw_segs_defined = 0;
}
