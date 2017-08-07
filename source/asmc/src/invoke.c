/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	Processing of INVOKE directive.
*
****************************************************************************/

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
#include <atofloat.h>

int QueueTestLines( char * );
int ExpandHllProc( char *, int, struct asm_tok[] );

extern uint_32 list_pos;  /* current LST file position */
extern int_64 maxintvalues[];
extern int_64 minintvalues[];
extern enum special_token stackreg[];

#define NUMQUAL

enum reg_used_flags {
    R0_USED	  = 0x01, /* register contents of AX/EAX/RAX is destroyed */
    R0_H_CLEARED  = 0x02, /* 16bit: high byte of R0 (=AH) has been set to 0 */
    R0_X_CLEARED  = 0x04, /* 16bit: register R0 (=AX) has been set to 0 */
    R2_USED	  = 0x08, /* contents of DX is destroyed ( via CWD ); cpu < 80386 only */
};

int size_vararg; /* size of :VARARG arguments */

struct fastcall_conv {
    int	 (* invokestart)( struct dsym const *, int, int, struct asm_tok[], int * );
    void (* invokeend)	( struct dsym const *, int, int );
    int	 (* handleparam)( struct dsym const *, int, struct dsym *, bool, struct expr *, char *, uint_8 * );
};

static const enum special_token regax[] = { T_AX, T_EAX, T_RAX };

extern struct fastcall_conv fastcall_tab[];
extern short GetSegmentPart(struct expr *, char *, const char *);
extern void fastcall_init(void);

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

	if ( proc->sym.langtype == LANG_FASTCALL
#ifdef FCT_ELF64
	|| ( proc->sym.langtype == LANG_SYSCALL && ModuleInfo.Ofssize == USE64 )
#endif
	    ) {
	    if ( fastcall_tab[ModuleInfo.fctype].handleparam( proc, reqParam, curr, addr, &opnd, fullparam, r0flags ) )
		return( NOT_ERROR );
	}

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

	if ( proc->sym.langtype == LANG_FASTCALL
#ifdef FCT_ELF64
	|| ( proc->sym.langtype == LANG_SYSCALL && ModuleInfo.Ofssize == USE64 )
#endif
	)
	    if (fastcall_tab[ModuleInfo.fctype].handleparam(
		 proc, reqParam, curr, addr, &opnd, fullparam, r0flags))
		return(NOT_ERROR);

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
			/* v2.23 if stack base is ESP */
			if ( CurrProc && ModuleInfo.basereg[ModuleInfo.Ofssize] == T_ESP )
			    AddLineQueueX( " push %r ptr %s+%u", dw, fullparam,
				NUMQUAL pushsize );
			else
			    AddLineQueueX( " push %r ptr %s+%u", dw, fullparam,
				NUMQUAL asize-pushsize );

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
			    /* v2.25: added support for REAL10 and REAL16 */
			case 10:
			    if ( Ofssize == USE16 || Options.strict_masm_compat == TRUE || opnd.kind != EXPR_FLOAT )
				break;
			    atofloat( &opnd.fvalue, fullparam, 10, opnd.negative, opnd.float_tok->floattype );
			    sprintf(fullparam, "0x%04X", (int_32)opnd.hlvalue & 0xFFFF);
			    AddLineQueueX( " push %s", fullparam );
			    sprintf(fullparam, "0x%016" I64_SPEC "X", opnd.llvalue);
			    if (( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_64 ) {
				if ( opnd.llvalue > 0xFFFFFFFF ) {
				    *r0flags |= R0_USED;
				    AddLineQueueX( " mov %r, %s", T_RAX, fullparam );
				    strcpy( fullparam, "rax" );
				}
				break;
			    }
			    AddLineQueueX( " pushd %r (%s)", T_HIGH32, fullparam );
			    qual = T_LOW32;
			    instr = "d";
			    break;
#if defined(_ASMLIB_)
			case 16:
			    if ( Ofssize == USE16 || Options.strict_masm_compat == TRUE )
				break;
			    if ( opnd.kind == EXPR_FLOAT )
				atofloat( &opnd.fvalue, fullparam, 16, opnd.negative, opnd.float_tok->floattype );
			    sprintf(fullparam, "0x%016" I64_SPEC "X", opnd.hlvalue);
			    if ( Ofssize == USE32 ) {
				AddLineQueueX( " pushd %r (%s)", T_HIGH32, fullparam );
				AddLineQueueX( " pushd %r (%s)", T_LOW32, fullparam );
			    } else {
				if ( opnd.hlvalue <=  0xFFFFFFFF ) {
				    AddLineQueueX( " push %s", fullparam );
				} else {
				    *r0flags |= R0_USED;
				    AddLineQueueX( " mov %r, %s", T_RAX, fullparam );
				    AddLineQueueX( " push %r", T_RAX );
				}
			    }
			    sprintf(fullparam, "0x%016" I64_SPEC "X", opnd.llvalue);
			    if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_64 &&
				opnd.llvalue >	 0xFFFFFFFF ) {
				*r0flags |= R0_USED;
				AddLineQueueX( " mov %r, %s", T_RAX, fullparam );
				AddLineQueueX( " push %r", T_RAX );
				goto skip_push;
			    }
			    /* no break */
#endif
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
skip_push:
	    if ( curr->sym.is_vararg ) {
		size_vararg += psize;
	    }
	}
    }
    return( NOT_ERROR );
}

/* generate a call for a prototyped procedure */

int InvokeDirective( int i, struct asm_tok tokenarray[] )
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
	    if (Token_Count == 2 &&
		tokenarray[0].tokval == T_INVOKE &&
		tokenarray[1].token == T_REG)
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

    for (curr = info->paralist, numParam = 0 ; curr ; curr = curr->nextparam, numParam++);

    if ( proc->sym.langtype == LANG_FASTCALL
#ifdef FCT_ELF64
	|| ( proc->sym.langtype == LANG_SYSCALL && ModuleInfo.Ofssize == USE64 )
#endif
    ) {
	fastcall_init();
	porder = fastcall_tab[ModuleInfo.fctype].invokestart(
		   proc, numParam, i, tokenarray, &value);
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
	(sym->langtype == LANG_FASTCALL && porder) ||
	sym->langtype == LANG_SYSCALL ) {

	/* v2.23 if stack base is ESP */

	int	total = 0;
	int	offset;
	struct	dsym *p;

	for ( ; curr ; curr = curr->nextparam ) {
	    numParam--;
	    if ( PushInvokeParam( i, tokenarray, proc, curr, numParam, &r0flags ) == ERROR ) {
		asmerr( 2033, numParam);
	    }

	    if ( CurrProc && ModuleInfo.basereg[ModuleInfo.Ofssize] == T_ESP ) {

		/* The symbol offset is reset after the loop.
		 * To have any effect the push-lines needs to
		 * be processed here for each argument.
		 */
		RunLineQueue();

		/* set push size to DWORD/QWORD */

		offset = curr->sym.total_size;
		if (offset < 4)
		    offset = 4;
		if (offset > 4)
		    offset = 8;
		total += offset;

		/* Update arguments in the current proc if any */

		for ( p = CurrProc->e.procinfo->paralist; p; p = p->nextparam )
		    if ( p->sym.state != SYM_TMACRO )
			p->sym.offset += offset;
	    }
	}
	if ( total ) {
	    for ( p = CurrProc->e.procinfo->paralist; p; p = p->nextparam ) {
		if ( p->sym.state != SYM_TMACRO )
		    p->sym.offset -= total;
	    }
	}

    } else {
	for ( numParam = 0 ; curr && curr->sym.is_vararg == FALSE; curr = curr->nextparam, numParam++ ) {
	    if ( PushInvokeParam( i, tokenarray, proc, curr, numParam, &r0flags ) == ERROR ) {
		asmerr( 2033, numParam);
	    }
	}
    }
#ifdef FCT_ELF64
    if ( info->has_vararg && proc->sym.langtype == LANG_SYSCALL && ModuleInfo.Ofssize == USE64 )
	 AddLineQueueX( " xor %r, %r", T_EAX, T_EAX );
#endif

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

    if (( sym->langtype == LANG_C ||
	( sym->langtype == LANG_SYSCALL
#ifdef FCT_ELF64
	&& ModuleInfo.fctype != FCT_ELF64
#endif
	)) &&
	( info->parasize || ( info->has_vararg && size_vararg ) )) {
	if ( info->has_vararg ) {
	    if ( ModuleInfo.epilogueflags )
		AddLineQueueX( " lea %r, [%r+%u]",
		stackreg[ModuleInfo.Ofssize], stackreg[ModuleInfo.Ofssize], NUMQUAL info->parasize + size_vararg );
	    else
		AddLineQueueX( " add %r, %u", stackreg[ModuleInfo.Ofssize], NUMQUAL info->parasize + size_vararg );
	} else {
	    if ( ModuleInfo.epilogueflags )
		AddLineQueueX( " lea %r, [%r+%u]",
		stackreg[ModuleInfo.Ofssize], stackreg[ModuleInfo.Ofssize], NUMQUAL info->parasize );
	    else
		AddLineQueueX( " add %r, %u", stackreg[ModuleInfo.Ofssize], NUMQUAL info->parasize );
	}
    } else if ( sym->langtype == LANG_FASTCALL
#ifdef FCT_ELF64
	|| ( proc->sym.langtype == LANG_SYSCALL && ModuleInfo.fctype == FCT_ELF64 )
#endif
    ) {
	fastcall_tab[ModuleInfo.fctype].invokeend( proc, numParam, value );
    }
    LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), NULL );
    RunLineQueue();

    return( NOT_ERROR );
}
