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
* Description:	expression evaluator.
*
****************************************************************************/

#include <stddef.h>

#include <globals.h>
#include <parser.h>
#include <reswords.h>
#include <expreval.h>
#include <segment.h>
#include <proc.h>
#include <assume.h>
#include <tokenize.h>
#include <types.h>
#include <label.h>
#include <atofloat.h>
#include <quadmath.h>

extern uint_32 StackAdj;
static struct asym *thissym;
static struct asym *nullstruct;
static struct asym *nullmbr;

static int (*fnasmerr)( int, ... );
static int noasmerr( int msg, ... );

enum labelsize {
    LS_SHORT  = 0xFF01,
    LS_FAR16  = 0xFF05,
    LS_FAR32  = 0xFF06,
};

static void init_expr( struct expr *opnd )
{
    opnd->value	   = 0;
    opnd->hvalue   = 0;
    opnd->hlvalue  = 0;
    opnd->quoted_string	  = NULL;
    opnd->base_reg = NULL;
    opnd->idx_reg  = NULL;
    opnd->label_tok = NULL;
    opnd->override = NULL;
    opnd->inst	   = EMPTY;
    opnd->kind	   = EXPR_EMPTY;
    opnd->mem_type = MT_EMPTY;
    opnd->scale	   = 0;
    opnd->Ofssize  = USE_EMPTY;
    opnd->flags1   = 0;
    opnd->sym	   = NULL;
    opnd->mbr	   = NULL;
    opnd->type	   = NULL;
}

static void TokenAssign( struct expr *opnd1, const struct expr *opnd2 )
{
#if 1
    /* note that offsetof() is used. This means, don't change position
     of field <type> in expr! */
    memcpy( opnd1, opnd2, offsetof( struct expr, type ) );
#else
    opnd1->llvalue  = opnd2->llvalue;
    opnd1->hlvalue  = opnd2->hlvalue;
    opnd1->quoted_string   = opnd2->quoted_string; /* probably useless */
    opnd1->base_reg = opnd2->base_reg;
    opnd1->idx_reg  = opnd2->idx_reg;
    opnd1->label_tok = opnd2->label_tok;
    opnd1->override = opnd2->override;
    opnd1->instr    = opnd2->instr;
    opnd1->kind	    = opnd2->kind;
    opnd1->mem_type = opnd2->mem_type;
    opnd1->scale    = opnd2->scale;
    opnd1->Ofssize  = opnd2->Ofssize;
    opnd1->flags1   = opnd2->flags1;
    opnd1->sym	    = opnd2->sym;
    opnd1->mbr	    = opnd2->mbr;
//  opnd1->type	    = opnd2->type;
#endif
}

static int is_expr_item( struct asm_tok *item )
/**********************************************/
/* Check if a token is a valid part of an expression.
 * chars + - * / . : [] and () are operators.
 * also done here:
 * T_INSTRUCTION  SHL, SHR, AND, OR, XOR changed to T_BINARY_OPERATOR
 * T_INSTRUCTION  NOT			 changed to T_UNARY_OPERATOR
 * T_DIRECTIVE	  PROC			 changed to T_STYPE
 * for the new operators the precedence is set.
 * DUP, comma or other instructions or directives terminate the expression.
 */
{
    switch( item->token ) {
    case T_INSTRUCTION:
	switch( item->tokval ) {
	case T_SHL:
	case T_SHR:
	    item->token = T_BINARY_OPERATOR;
	    item->precedence = 8;
	    return( TRUE );
	case T_NOT:
	    item->token = T_UNARY_OPERATOR;
	    item->precedence = 11;
	    return( TRUE );
	case T_AND:
	    item->token = T_BINARY_OPERATOR;
	    item->precedence = 12;
	    return( TRUE );
	case T_OR:
	case T_XOR:
	    item->token = T_BINARY_OPERATOR;
	    item->precedence = 13;
	    return( TRUE );
	}
	return( FALSE );
    case T_RES_ID:
	if ( item->tokval == T_DUP ) /* DUP must terminate the expression */
	    return( FALSE );
	break;
    case T_DIRECTIVE:
	/* PROC is converted to a type */
	if ( item->tokval == T_PROC ) {
	    item->token = T_STYPE;
	    /* v2.06: avoid to use ST_PROC */
	    //item->bytval = ST_PROC;
	    item->tokval = ( ( SIZE_CODEPTR & ( 1 << ModuleInfo.model ) ) ? T_FAR : T_NEAR );
	    return( TRUE );
	}
	/* fall through. Other directives will end the expression */
    case T_COMMA:
    //case T_FLOAT: /* v2.05: floats are now handled */
    //case T_QUESTION_MARK: /* v2.08: no need to be handled here */
	return( FALSE );
    }
    return( TRUE );
}

static int get_precedence( const struct asm_tok *item )
{
    switch( item->token ) {
    case T_UNARY_OPERATOR:
    case T_BINARY_OPERATOR:
	return( item->precedence );
    case T_OP_BRACKET:
    case T_OP_SQ_BRACKET:
	return( ModuleInfo.m510 ? 9 : 1 );
    case T_DOT:
	return( 2 );
    case T_COLON:
	return( 3 );
    case '*':
    case '/':
	return( 8 );
    case '+':
    case '-':
	return( item->specval ? 9 : 7 );
    }

    fnasmerr( 2008, item->string_ptr );
    return( ERROR );
}

static unsigned int GetTypeSize( unsigned char mem_type, int Ofssize )
{
    if ( mem_type == MT_ZWORD )
	return( 64 );
    if ( (mem_type & MT_SPECIAL) == 0 )
	return( ( mem_type & MT_SIZE_MASK ) + 1 );
    if ( Ofssize == USE_EMPTY )
	Ofssize = ModuleInfo.Ofssize;
    switch ( mem_type ) {
    case MT_NEAR: return ( 0xFF00 | ( 2 << Ofssize ) ) ;
    case MT_FAR:  return ( ( Ofssize == USE16 ) ? LS_FAR16 : 0xFF00 | ( ( 2 << Ofssize ) + 2 ) );
    }
    return( 0 );
}

static uint_64 GetRecordMask( struct dsym *record )
{
    uint_64 mask = 0;
    int i;
    struct sfield *fl;
    for ( fl = record->e.structinfo->head; fl; fl = fl->next ) {
	struct asym *sym = &fl->sym;
	for ( i = sym->offset ;i < sym->offset + sym->total_size; i++ )
	    mask |= (uint_64)1 << i;
    }
    return( mask );
}

/* added v2.31.32 */

static int SetEvexOpt( struct asm_tok tokenarray[], int i )
{
    int o;

    if ( tokenarray[i-1].token == T_COMMA &&
	 tokenarray[i-2].token == T_REG &&
	 tokenarray[i-3].token == T_INSTRUCTION ) {

	o = GetValueSp( tokenarray[i-2].tokval );
	if ( o & OP_XMM ) {
	    if ( tokenarray[i-3].tokval < VEX_START &&
		 tokenarray[i-3].tokval >= T_ADDPD )
		return 0;
	}
    }
    tokenarray[i].hll_flags |= T_EVEX_OPT;
    return 1;
}


static ret_code get_operand( struct expr *opnd, int *idx, struct asm_tok tokenarray[], const uint_8 flags )
{
    char	*tmp;
    struct asym *sym;
    int		i = *idx;
    int		j;
    char	labelbuff[16];

    if ( tokenarray[i].token == '&' ) { /* v2.30.24 -- mov mem,&mem */
	if ( Options.strict_masm_compat == FALSE && i > 2 &&
	      tokenarray[i-1].token == T_COMMA && tokenarray[i-2].token != T_REG ) {
	    i++;
	    (*idx)++;
	    if ( tokenarray[i].token == T_OP_SQ_BRACKET )
		return NOT_ERROR;
	} else
	    return fnasmerr( 2008, tokenarray[i].tokpos );
    }

    switch( tokenarray[i].token ) {
    case T_NUM:
	opnd->kind = EXPR_CONST;
	_atoow( &opnd->llvalue, tokenarray[i].string_ptr, tokenarray[i].numbase, tokenarray[i].itemlen );
	break;
    case T_STRING:
	if ( tokenarray[i].string_delim != '"' && tokenarray[i].string_delim != '\'') {
	    if ( opnd->is_opattr )
		break;
	    if ( tokenarray[i].string_delim == '\0' &&
		( *tokenarray[i].string_ptr == '"' || *tokenarray[i].string_ptr == '\'' ))
		fnasmerr( 2046 );
	    else if ( tokenarray[i].string_delim == '{' ) {
		opnd->kind = EXPR_EMPTY;
		if ( SetEvexOpt( tokenarray, i ) == 0 ) {
		    opnd->kind = EXPR_CONST;
		    opnd->quoted_string = &tokenarray[i];
		}
		break;
	    } else
		fnasmerr( 2167, tokenarray[i].tokpos );
	    return( ERROR );
	}
	opnd->kind = EXPR_CONST;
	opnd->quoted_string = &tokenarray[i];
	tmp = tokenarray[i].string_ptr + 1;
	j = ( tokenarray[i].stringlen > sizeof( opnd->chararray ) ? sizeof( opnd->chararray ) : tokenarray[i].stringlen );
	for( ; j; j-- )
	    opnd->chararray[j-1] = *tmp++;
	break;
    case T_REG:
	opnd->kind = EXPR_REG;
	opnd->base_reg = &tokenarray[i];
	j = tokenarray[i].tokval;
	if( ( ( SpecialTable[j].cpu & P_EXT_MASK ) &&
	     (( SpecialTable[j].cpu & ModuleInfo.curr_cpu & P_EXT_MASK) == 0) ||
	     ( ModuleInfo.curr_cpu & P_CPU_MASK ) < ( SpecialTable[j].cpu & P_CPU_MASK ) ) ) {
	    if ( flags & EXPF_IN_SQBR ) {
		opnd->kind = EXPR_ERROR;
		fnasmerr( 2085 );
	    } else
		return( fnasmerr( 2085 ) );
	}

	if ( (i > 0 && tokenarray[i - 1].tokval == T_TYPEOF) ||
	     (i > 1 && tokenarray[i - 1].token == T_OP_BRACKET
		    && tokenarray[i - 2].tokval == T_TYPEOF) )

	     ; /* v2.24 [reg + type reg] | [reg + type(reg)] */

	else  if( flags & EXPF_IN_SQBR ) {
	    if ( SpecialTable[j].sflags & SFR_IREG ) {
		opnd->indirect = 1;
		opnd->assumecheck = 1;
	    } else if ( SpecialTable[j].value & OP_SR ) {
		if( tokenarray[i+1].token != T_COLON ||
		   ( ModuleInfo.strict_masm_compat && tokenarray[i+2].token == T_REG ) ) {
		    return( fnasmerr( 2032 ) );
		}
	    } else {
		if ( opnd->is_opattr )
		    opnd->kind = EXPR_ERROR;
		else
		    return( fnasmerr( 2031 ) );
	    }
	}
	break;
    case T_ID:
	tmp = tokenarray[i].string_ptr;
	if ( opnd->is_dot ) {
	    opnd->value = 0;
	    sym = ( opnd->type ? SearchNameInStruct( opnd->type, tmp, &opnd->uvalue, 0 ) : NULL );
	    if ( sym == NULL ) {
		sym = SymFind(tmp);
		if ( sym ) {
		    if ( sym->state == SYM_TYPE ) {
			if ( sym == opnd->type || ( opnd->type && opnd->type->isdefined == 0 ) || ModuleInfo.oldstructs )
			    ;
			else {
			    sym = NULL;
			}
		    } else if ( ModuleInfo.oldstructs &&
			       ( sym->state == SYM_STRUCT_FIELD ||
				sym->state == SYM_EXTERNAL ||
				sym->state == SYM_INTERNAL ) )
			;
		    else {
			sym = NULL;
		    }
		}
	    }
	} else {
	    if ( *tmp == '@' && *(tmp+2 ) == '\0' ) {
		if ( *(tmp+1) == 'b' || *(tmp+1 ) == 'B' )
		    tmp = GetAnonymousLabel( labelbuff, 0 );
		else if (*(tmp+1) == 'f' || *(tmp+1 ) == 'F' )
		    tmp = GetAnonymousLabel( labelbuff, 1 );
	    }
	    sym = SymFind(tmp);
	}
	if ( sym == NULL || sym->state == SYM_UNDEFINED ||
	    ( sym->state == SYM_TYPE && sym->typekind == TYPE_NONE ) ||
	    sym->state == SYM_MACRO ||
	    sym->state == SYM_TMACRO ) {
	    if ( opnd->is_opattr ) {
		opnd->kind = EXPR_ERROR;
		break;
	    }
	    if ( sym && ( sym->state == SYM_MACRO || sym->state == SYM_TMACRO ) ) {
		return fnasmerr( 2148, sym->name );
	    }
	    if( Parse_Pass == PASS_1 && !( flags & EXPF_NOUNDEF ) ) {
		if ( sym == NULL ) {
		    if ( opnd->type == NULL ) {
			sym = SymLookup( tmp );
			sym->state = SYM_UNDEFINED;
			sym_add_table( &SymTables[TAB_UNDEF], (struct dsym *)sym );
		    } else if ( opnd->type->typekind != TYPE_NONE ) {
			return( fnasmerr( 2006, tmp ) );
		    } else {
			if ( !nullmbr ) {
			    nullmbr = SymAlloc( "" );
			}
			opnd->mbr = nullmbr;
			opnd->kind = EXPR_CONST;
			break;
		    }
		}
	    } else {

		if ( Options.strict_masm_compat == FALSE
		     && sym == NULL && _stricmp( tmp, "defined" ) == 0 ) {

		    if ( i && tokenarray[i+1].token == T_OP_BRACKET ) {

			i += 2;
			opnd->kind = EXPR_CONST;
			opnd->llvalue = 0;

			/* added v2.28.17: defined(...) returns -1 */

			if ( tokenarray[i].token == T_CL_BRACKET ) {

			    *idx = i;
			    opnd->llvalue--; /* <> -- defined() */
			    break;
			}

			if ( tokenarray[i].token == T_NUM && tokenarray[i+1].token == T_CL_BRACKET ) {

			    opnd->llvalue--;
			    *idx = i + 1;
			    break;
			}


			if ( tokenarray[i].token == T_ID && tokenarray[i+1].token == T_CL_BRACKET ) {

			    *idx = i + 1;
			    sym = SymFind( tokenarray[i].string_ptr );
			    if ( sym && sym->state != SYM_UNDEFINED ) {

				opnd->llvalue--; /* symbol defined */
				break;
			    }

			    /* -- symbol not defined -- */

			    if ( tokenarray[i+2].token == T_FINAL ||
				 tokenarray[i+2].tokval != T_AND  ||
				 tokenarray[i-3].tokval == T_NOT )

				/* [not defined(symbol)] - return 0 */

				break;

			    /* [defined(symbol) and] - return 0 and skip rest of line... */
			    i += 3;
			    for ( j = 0; i < Token_Count; i++ ) {

				if ( tokenarray[i].token == T_CL_BRACKET ) {

				    if ( j == 0 )
					break;
				    j--;
				} else if ( tokenarray[i].token == T_OP_BRACKET ) {
				    j++;
				}
			    }
			    *idx = i - 1;
			    break;
			}
		    }
		}
		return( fnasmerr( 2006, *(tmp+1) == '&' ? "@@" : tmp ) );
	    }
	} else if ( sym->state == SYM_ALIAS ) {
	    sym = sym->substitute;
	}
	sym->used = 1;

	switch ( sym->state ) {
	case SYM_TYPE:
	    if ( sym->typekind != TYPE_TYPEDEF && ((struct dsym *)sym)->e.structinfo->isOpen ) {
		opnd->kind = EXPR_ERROR;
		break;
	    }
	    for ( ; sym->type; sym = sym->type );
	    opnd->kind = EXPR_CONST;
	    opnd->mem_type = sym->mem_type;
	    opnd->is_type = 1;
	    opnd->type = sym;
	     ;
	    if ( sym->typekind == TYPE_RECORD ) {
		opnd->llvalue = GetRecordMask( (struct dsym *)sym );
	    } else if ( ( sym->mem_type & MT_SPECIAL_MASK ) == MT_ADDRESS ) {
		if ( sym->mem_type == MT_PROC ) {
		    opnd->value = sym->total_size;
		    opnd->Ofssize = sym->Ofssize;
		} else
		    opnd->value = GetTypeSize( sym->mem_type, sym->Ofssize );
	    } else
		opnd->value = sym->total_size;
	    break;
	case SYM_STRUCT_FIELD:
	    opnd->value += sym->offset;
	    opnd->kind = EXPR_CONST;
	    opnd->mbr = sym;
	    for ( ; sym->type; sym = sym->type );
	    opnd->mem_type = sym->mem_type;
	    opnd->type = ( sym->state == SYM_TYPE && sym->typekind != TYPE_TYPEDEF ) ? sym : NULL;
	    break;
	default:
	    opnd->kind = EXPR_ADDR;
	    if ( sym->predefined && sym->sfunc_ptr )
		sym->sfunc_ptr( sym, NULL );
	    if( sym->state == SYM_INTERNAL && sym->segment == NULL ) {
		opnd->kind = EXPR_CONST;
		opnd->uvalue = sym->uvalue;
		opnd->hvalue = sym->value3264;
		opnd->mem_type = sym->mem_type;
	    } else if( sym->state == SYM_EXTERNAL &&
		      sym->mem_type == MT_EMPTY &&
		      sym->iscomm == 0 ) {
		opnd->is_abs = 1;
		opnd->sym = sym;
	    } else {
		opnd->label_tok = &tokenarray[i];
		if( sym->type && sym->type->mem_type != MT_EMPTY ) {
		    opnd->mem_type = sym->type->mem_type;
		} else {
		    opnd->mem_type = sym->mem_type;
		}
		if ( sym->state == SYM_STACK ) {
		    opnd->value64 = (int_64)(sym->offset + (int)StackAdj);
		    opnd->indirect = 1;
		    opnd->base_reg = &tokenarray[i];
		    tokenarray[i].tokval = CurrProc->e.procinfo->basereg;
		    tokenarray[i].bytval = SpecialTable[tokenarray[i].tokval].bytval;
		}
		opnd->sym = sym;
		for ( ; sym->type; sym = sym->type );
		opnd->type = ( sym->state == SYM_TYPE && sym->typekind != TYPE_TYPEDEF ) ? sym : NULL;
	    }
	    break;
	}
	break;
    case T_STYPE:
	opnd->kind = EXPR_CONST;
	opnd->mem_type = SpecialTable[tokenarray[i].tokval].bytval;
	opnd->Ofssize = SpecialTable[tokenarray[i].tokval].sflags;
	opnd->value = GetTypeSize( opnd->mem_type, opnd->Ofssize );
	opnd->is_type = 1;
	opnd->type = NULL;
	break;
    case T_RES_ID:
	if ( tokenarray[i].tokval == T_FLAT ) {
	    if ( ( flags & EXPF_NOUNDEF ) == 0 ) {
		if( ( ModuleInfo.curr_cpu & P_CPU_MASK ) < P_386 ) {
		    fnasmerr( 2085 );
		    return( ERROR );
		}
		DefineFlatGroup();
	    }
	    if ( !( opnd->sym = &ModuleInfo.flat_grp->sym ) )
		return( ERROR );
	    opnd->label_tok = &tokenarray[i];
	    opnd->kind = EXPR_ADDR;

	    /* added v2.31.32: typeof(addr ...) */
	} else if ( tokenarray[i].tokval == T_ADDR && i > 2 &&
	    ( tokenarray[i-1].tokval == T_TYPEOF || tokenarray[i-2].tokval == T_TYPEOF ) &&
	    ( tokenarray[i+1].token == T_ID || tokenarray[i+1].token == T_OP_SQ_BRACKET	 ) ) {
	    (*idx)++;
	    opnd->kind = EXPR_ADDR;
	    opnd->mem_type = MT_PTR;
	    break;
	} else {
	    return( fnasmerr( 2008, tokenarray[i].string_ptr ) );
	}
	break;
    case T_FLOAT:
	opnd->kind = EXPR_FLOAT;
	opnd->float_tok = &tokenarray[i];
	opnd->mem_type = MT_REAL16;
	atofloat( opnd, tokenarray[i].string_ptr, 16, 0, tokenarray[i].floattype );
	break;
    default:
	if ( opnd->is_opattr ) {
	    if ( tokenarray[i].token == T_FINAL ||
		tokenarray[i].token == T_CL_BRACKET ||
		tokenarray[i].token == T_CL_SQ_BRACKET )
		return( NOT_ERROR );
	    break;
	}
	if ( tokenarray[i].token == T_BAD_NUM )
	    fnasmerr( 2048, tokenarray[i].string_ptr );
	else if ( tokenarray[i].token == T_COLON )
	    fnasmerr( 2009 );
	else if ( islalpha( *tokenarray[i].string_ptr ) )
	    fnasmerr( 2016, tokenarray[i].tokpos );
	else
	    fnasmerr( 2008, tokenarray[i].tokpos );
	return( ERROR );
    }
    (*idx)++;
    return( NOT_ERROR );
}

static bool check_both( const struct expr *opnd1, const struct expr *opnd2,
	enum exprtype type1, enum exprtype type2 )
{
    if( opnd1->kind == type1 && opnd2->kind == type2 )
	return( 1 );
    if( opnd1->kind == type2 && opnd2->kind == type1 )
	return( 1 );
    return( 0 );
}

static int index_connect( struct expr *opnd1, const struct expr *opnd2 )
{
    if ( opnd2->base_reg != NULL ) {
	if ( opnd1->base_reg == NULL )
	    opnd1->base_reg = opnd2->base_reg;
	else if ( opnd1->idx_reg == NULL ) {
	    if ( opnd2->base_reg->bytval == 4 ) {
		opnd1->idx_reg = opnd1->base_reg;
		opnd1->base_reg = opnd2->base_reg;
	    } else {
		opnd1->idx_reg = opnd2->base_reg;
	    }
	} else {
	    return( fnasmerr( 2030 ) );
	}
	opnd1->indirect = 1;
    }
    if( opnd2->idx_reg != NULL ) {
	if ( opnd1->idx_reg == NULL ) {
	    opnd1->idx_reg = opnd2->idx_reg;
	    opnd1->scale = opnd2->scale;
	} else {
	    return( fnasmerr( 2030 ) );
	}
	opnd1->indirect = 1;
    }
    return( NOT_ERROR );
}

static void MakeConst( struct expr *opnd )
{
    if( ( opnd->kind != EXPR_ADDR ) || opnd->indirect )
	return;
    if( opnd->sym ) {
	if ( Parse_Pass > PASS_1 )
	    return;
	if ( ( opnd->sym->state == SYM_UNDEFINED && opnd->inst == EMPTY ) ||
	    ( opnd->sym->state == SYM_EXTERNAL && opnd->sym->weak == 1 && opnd->is_abs == 1 ) )
	    ;
	else
	    return;
	opnd->value = 1;
    }
    opnd->label_tok = NULL;
    if( opnd->mbr != NULL ) {
	if( opnd->mbr->state == SYM_STRUCT_FIELD ) {
	} else {
	    return;
	}
    }
    if( opnd->override != NULL )
	return;
    opnd->inst = EMPTY;
    opnd->kind = EXPR_CONST;
    opnd->explicit = 0;
    opnd->mem_type = MT_EMPTY;
}

static int MakeConst2( struct expr *opnd1, struct expr *opnd2 )
{
    if ( opnd1->sym->state == SYM_EXTERNAL ) {
	return( fnasmerr( 2018, opnd1->sym->name ) );
    } else if ( ( opnd1->sym->segment != opnd2->sym->segment &&
		 opnd1->sym->state != SYM_UNDEFINED &&
		 opnd2->sym->state != SYM_UNDEFINED ) ||
	       opnd2->sym->state == SYM_EXTERNAL ) {
	return( fnasmerr( 2025 ) );
    }
    opnd1->kind = EXPR_CONST;
    opnd1->value += opnd1->sym->offset;
    opnd2->kind = EXPR_CONST;
    opnd2->value += opnd2->sym->offset;
    return( NOT_ERROR );
}

static int ConstError( struct expr *opnd1, struct expr *opnd2 )
{
    if ( opnd1->is_opattr )
	return( NOT_ERROR );
    if ( opnd1->kind == EXPR_FLOAT || opnd2->kind == EXPR_FLOAT )
	fnasmerr( 2050 );
    else
	fnasmerr( 2026 );
    return( ERROR );
}

static void fix_struct_value( struct expr *opnd )
{
    if( opnd->mbr && ( opnd->mbr->state == SYM_TYPE ) ) {
	opnd->value += opnd->mbr->total_size;
	opnd->mbr = NULL;
    }
}

static int check_direct_reg( const struct expr *opnd1, const struct expr *opnd2 )
{
    if( ( opnd1->kind == EXPR_REG ) && ( opnd1->indirect == 0 )
	|| ( opnd2->kind == EXPR_REG ) && ( opnd2->indirect == 0 ) ) {
	return( ERROR );
    }
    return( NOT_ERROR );
}

static unsigned GetSizeValue( struct asym *sym )
{
    if ( sym->mem_type == MT_PTR )
	return( SizeFromMemtype( (unsigned char)(sym->isfar ? MT_FAR : MT_NEAR), sym->Ofssize, sym->type ) );
    return( SizeFromMemtype( sym->mem_type, sym->Ofssize, sym->type ) );
}

static unsigned IsOffset( struct expr *opnd )
{
    if ( opnd->mem_type == MT_EMPTY )
	if ( opnd->inst == T_OFFSET ||
	    opnd->inst == T_IMAGEREL ||
	    opnd->inst == T_SECTIONREL ||
	    opnd->inst == T_LROFFSET )
	    return( 1 );
    return( 0 );
}

static int invalid_operand( struct expr *opnd, char *oprtr, char *operand )
{
    if ( !opnd->is_opattr )
	fnasmerr( 3018, _strupr( oprtr), operand );
    return( ERROR );
}

static int sizlen_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    opnd1->kind = EXPR_CONST;

    if ( sym ) {
	if ( sym->state == SYM_STRUCT_FIELD || sym->state == SYM_STACK )
	    ;
	else if ( sym->state == SYM_UNDEFINED ) {
	    opnd1->kind = EXPR_ADDR;
	    opnd1->sym = sym;
	} else if ( ( sym->state == SYM_EXTERNAL ||
		 sym->state == SYM_INTERNAL) &&
		 sym->mem_type != MT_EMPTY &&
		 sym->mem_type != MT_FAR &&
		 sym->mem_type != MT_NEAR )
	    ;
	else if ( sym->state == SYM_GRP || sym->state == SYM_SEG ) {
	    return( fnasmerr( 2143 ) );
	} else if ( oper == T_DOT_SIZE || oper == T_DOT_LENGTH )
	;
	else {
	    return( fnasmerr( 2143 ) );
	}
    }
    switch( oper ) {
    case T_DOT_LENGTH:
	opnd1->value = sym->isdata ? sym->first_length : 1;
	break;
    case T_LENGTHOF:
	if( opnd2->kind == EXPR_CONST ) {
	    opnd1->value = opnd2->mbr->total_length;
	} else if ( sym->state == SYM_EXTERNAL && sym->iscomm == 0 ) {
	    opnd1->value = 1;
	} else {
	    opnd1->value = sym->total_length;
	}
	break;
    case T_DOT_SIZE:
	if( sym == NULL ) {
	    if ( ( opnd2->mem_type & MT_SPECIAL_MASK ) == MT_ADDRESS )
		opnd1->value = 0xFF00 | opnd2->value;
	    else
		opnd1->value = opnd2->value;
	} else if ( sym->isdata ) {
	    opnd1->value = sym->first_size;
	} else if( sym->state == SYM_STACK ) {
	    opnd1->value = GetSizeValue( sym );
	} else if( sym->mem_type == MT_NEAR ) {
	    opnd1->value = 0xFF00 | ( 2 << GetSymOfssize( sym ) );
	} else if( sym->mem_type == MT_FAR ) {
	    opnd1->value = GetSymOfssize( sym ) ? LS_FAR32 : LS_FAR16;
	} else {
	    opnd1->value = GetSizeValue( sym );
	}
	break;
    case T_SIZEOF:
	if ( sym == NULL ) {
	    if ( opnd2->is_type && opnd2->type && opnd2->type->typekind == TYPE_RECORD )
		opnd1->value = opnd2->type->total_size;
	    else
		opnd1->value = opnd2->value;
	} else if ( sym->state == SYM_EXTERNAL && sym->iscomm == 0 ) {
	    opnd1->value = GetSizeValue( sym );
	} else
	    opnd1->value = sym->total_size;
	break;
    }
    return( NOT_ERROR );
}

static int type_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    opnd1->kind = EXPR_CONST;
    if( opnd2->inst != EMPTY && opnd2->mem_type != MT_EMPTY ) {
	opnd2->inst = EMPTY;
	sym = NULL;
    }
    if( opnd2->inst != EMPTY ) {
	if ( opnd2->sym ) {
	    switch ( opnd2->inst ) {
	    case T_DOT_LOW:
	    case T_DOT_HIGH:
		opnd1->value = 1;
		break;
	    case T_LOWWORD:
	    case T_HIGHWORD:
		opnd1->value = 2;
		break;
	    case T_LOW32:
	    case T_HIGH32:
		opnd1->value = 4;
		break;
	    case T_LOW64:
	    case T_HIGH64:
		opnd1->value = 8;
		break;
	    case T_OFFSET:
	    case T_LROFFSET:
	    case T_SECTIONREL:
	    case T_IMAGEREL:
		opnd1->value = 2 << GetSymOfssize( opnd2->sym );
		opnd1->is_type = 1;
		break;
	    }
	}
    } else if ( sym == NULL ) {
	if ( opnd2->is_type == 1 ) {
	    if ( opnd2->type && opnd2->type->typekind == TYPE_RECORD )
		opnd2->value = opnd2->type->total_size;
	    TokenAssign( opnd1, opnd2 );
	    opnd1->type = opnd2->type;
	} else if ( opnd2->kind == EXPR_REG && opnd2->indirect == 0 ) {
	    opnd1->value = SizeFromRegister( opnd2->base_reg->tokval );
	    opnd1->is_type = 1;
	    if ( opnd1->value == ModuleInfo.wordsize &&
		opnd1->mem_type == MT_EMPTY &&
		( SpecialTable[opnd2->base_reg->tokval].value & OP_RGT8 ) &&
		( sym = GetStdAssumeEx( opnd2->base_reg->bytval ) ) ) {

		opnd1->type = sym;
		opnd1->mem_type = sym->mem_type;
		opnd1->value = sym->total_size;
	    } else {
		opnd1->mem_type = opnd2->mem_type;
		opnd1->type = opnd2->type;
		if ( opnd1->mem_type == MT_EMPTY )
		    MemtypeFromSize( opnd1->value, &opnd1->mem_type );
	    }
	} else if ( opnd2->mem_type != MT_EMPTY || opnd2->explicit ) {
	    if ( opnd2->mem_type != MT_EMPTY ) {
		if ( opnd2->kind == EXPR_FLOAT && opnd2->mem_type == MT_REAL16 ) {
		    opnd1->value = 0;
		} else {
		    opnd1->value = SizeFromMemtype( opnd2->mem_type, opnd2->Ofssize, opnd2->type );
		    opnd1->mem_type = opnd2->mem_type;
		}
	    } else {
		if ( opnd2->type ) {
		    opnd1->value = opnd2->type->total_size;
		    opnd1->mem_type = opnd2->type->mem_type;
		}
	    }
	    opnd1->is_type = 1;
	    opnd1->type = opnd2->type;
	} else
	    opnd1->value = 0;
    } else if ( sym->state == SYM_UNDEFINED ) {
	opnd1->kind = EXPR_ADDR;
	opnd1->sym = sym;
	opnd1->is_type = 1;
    } else if( sym->mem_type == MT_TYPE && opnd2->explicit == 0 ) {
	opnd1->value = sym->type->total_size;
	opnd1->is_type = 1;
	opnd1->mem_type = sym->type->mem_type;
	opnd1->type = sym->type;
    } else {
	opnd1->is_type = 1;
	if ( opnd1->mem_type == MT_EMPTY )
	    opnd1->mem_type = opnd2->mem_type;
	if ( opnd2->type && opnd2->mbr == NULL ) {
	    opnd1->type_tok = opnd2->type_tok;
	    opnd1->type = opnd2->type;
	    opnd1->value = opnd1->type->total_size;
	} else if ( sym->mem_type == MT_PTR ) {
	    opnd1->type_tok = opnd2->type_tok;
	    opnd1->value = SizeFromMemtype( (unsigned char)(sym->isfar ? MT_FAR : MT_NEAR), sym->Ofssize, NULL );
	} else if( sym->mem_type == MT_NEAR ) {
	    opnd1->value = 0xFF00 | ( 2 << GetSymOfssize( sym ) );
	} else if( sym->mem_type == MT_FAR ) {
	    opnd1->value = GetSymOfssize( sym ) ? LS_FAR32 : LS_FAR16;
	} else
	    opnd1->value = SizeFromMemtype( opnd2->mem_type, GetSymOfssize( sym ), sym->type );
    }
    return( NOT_ERROR );
}

enum opattr_bits {
    OPATTR_CODELABEL = 0x01,
    OPATTR_DATALABEL = 0x02,
    OPATTR_IMMEDIATE = 0x04,
    OPATTR_DIRECTMEM = 0x08,
    OPATTR_REGISTER  = 0x10,
    OPATTR_DEFINED   = 0x20,
    OPATTR_SSREL     = 0x40,
    OPATTR_EXTRNREF  = 0x80,
    OPATTR_LANG_MASK = 0x700,
};

static int opattr_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    struct asm_tok *p;

    opnd1->kind = EXPR_CONST;
    opnd1->sym = NULL;
    opnd1->value = 0;
    opnd1->mem_type = MT_EMPTY;
    opnd1->is_opattr = 0;
    if ( opnd2->kind == EXPR_EMPTY )
	return( NOT_ERROR );
    if ( opnd2->kind == EXPR_ADDR ) {
	if ( opnd2->sym && opnd2->sym->state != SYM_STACK &&
	    ( opnd2->mem_type & MT_SPECIAL_MASK ) == MT_ADDRESS )
	    opnd1->value |= OPATTR_CODELABEL;
	if ( IsOffset( opnd2 ) &&
	    opnd2->sym &&
	    ( opnd2->sym->mem_type & MT_SPECIAL_MASK ) == MT_ADDRESS )
	    opnd1->value |= OPATTR_CODELABEL;
	if ( opnd2->sym &&
	    (( opnd2->sym->mem_type == MT_TYPE ||
	      ( opnd2->mem_type & MT_SPECIAL ) == 0 ) ||
	     ( opnd2->mem_type == MT_EMPTY &&
	      ( opnd2->sym->mem_type & MT_SPECIAL ) == 0 )))
	    opnd1->value |= OPATTR_DATALABEL;
    }
    if ( opnd2->kind != EXPR_ERROR && opnd2->indirect )
	opnd1->value |= OPATTR_DATALABEL;
    if ( opnd2->kind == EXPR_CONST ||
	( opnd2->kind == EXPR_ADDR &&
	 opnd2->indirect == 0 &&
	 (( opnd2->mem_type == MT_EMPTY && IsOffset(opnd2) ) ||
	  ( opnd2->mem_type == MT_EMPTY ) ||
	  (( opnd2->mem_type & MT_SPECIAL_MASK ) == MT_ADDRESS )) &&
	 ( opnd2->sym->state == SYM_INTERNAL ||
	  opnd2->sym->state == SYM_EXTERNAL ) ) )
	opnd1->value |= OPATTR_IMMEDIATE;
    if ( opnd2->kind == EXPR_ADDR &&
	opnd2->indirect == 0 &&
	(( opnd2->mem_type == MT_EMPTY && opnd2->inst == EMPTY ) ||
	 ( opnd2->mem_type == MT_TYPE ) ||
	 (( opnd2->mem_type & MT_SPECIAL ) == 0 ) ||
	 opnd2->mem_type == MT_PTR ) &&
	(opnd2->sym == NULL ||
	 opnd2->sym->state == SYM_INTERNAL ||
	 opnd2->sym->state == SYM_EXTERNAL ) )
	opnd1->value |= OPATTR_DIRECTMEM;
    if ( opnd2->kind == EXPR_REG && opnd2->indirect == 0 )
	opnd1->value |= OPATTR_REGISTER;
    if ( opnd2->kind != EXPR_ERROR && opnd2->kind != EXPR_FLOAT && ( opnd2->sym == NULL || opnd2->sym->isdefined == 1 ) )
	opnd1->value |= OPATTR_DEFINED;
    p = opnd2->idx_reg;
    if ( p == NULL )
	p = opnd2->base_reg;
    if ( ( opnd2->sym && opnd2->sym->state == SYM_STACK ) ||
	( opnd2->indirect && p && ( SpecialTable[p->tokval].sflags & SFR_SSBASED ) ) )
	opnd1->value |= OPATTR_SSREL;
    if ( opnd2->sym && opnd2->sym->state == SYM_EXTERNAL )
	opnd1->value |= OPATTR_EXTRNREF;
    if ( oper == T_OPATTR )
	if ( opnd2->sym && opnd2->kind != EXPR_ERROR )
	    opnd1->value |= opnd2->sym->langtype << 8;
    return( NOT_ERROR );
}

static int short_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    if ( opnd2->kind != EXPR_ADDR ||
	( opnd2->mem_type != MT_EMPTY &&
	 opnd2->mem_type != MT_NEAR &&
	 opnd2->mem_type != MT_FAR ) ) {
	return( fnasmerr( 2028 ) );
    }
    TokenAssign( opnd1, opnd2 );
    opnd1->inst = oper;
    return( NOT_ERROR );
}

static int seg_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    if ( opnd2->sym == NULL || opnd2->sym->state == SYM_STACK || opnd2->is_abs ) {
	return( fnasmerr( 2094 ) );
    }
    TokenAssign( opnd1, opnd2 );
    opnd1->inst = oper;
    if ( opnd1->mbr )
	opnd1->value = 0;
    opnd1->mem_type = MT_EMPTY;
    return( NOT_ERROR );
}

static int offset_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    if ( oper == T_OFFSET ) {
	if ( opnd2->kind == EXPR_CONST ) {
	    TokenAssign( opnd1, opnd2 );
	    return( NOT_ERROR );
	}
    }
    if ( (sym && sym->state == SYM_GRP) || opnd2->inst == T_SEG ) {
	return( invalid_operand( opnd2, GetResWName( oper, NULL ), name ) );
    }
    if ( opnd2->is_type )
	opnd2->value = 0;
    TokenAssign( opnd1, opnd2 );
    opnd1->inst = oper;
    if ( opnd2->indirect ) {
	return( invalid_operand( opnd2, GetResWName( oper, NULL ), name ) );
    }
    opnd1->mem_type = MT_EMPTY;
    return( NOT_ERROR );
}

static int lowword_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    TokenAssign( opnd1, opnd2 );
    if ( opnd2->kind == EXPR_ADDR && opnd2->inst != T_SEG ) {
	opnd1->inst = T_LOWWORD;
	opnd1->mem_type = MT_EMPTY;
    }
    opnd1->llvalue &= 0xffff;
    return( NOT_ERROR );
}

static int highword_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    TokenAssign( opnd1, opnd2 );
    if ( opnd2->kind == EXPR_ADDR && opnd2->inst != T_SEG ) {
	opnd1->inst = T_HIGHWORD;
	opnd1->mem_type = MT_EMPTY;
    }
    opnd1->llvalue = (opnd1->llvalue >> 16) & 0xFFFF;
    return( NOT_ERROR );
}

static int low_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    TokenAssign( opnd1, opnd2 );
    if ( opnd2->kind == EXPR_ADDR && opnd2->inst != T_SEG ) {
	opnd1->inst = T_DOT_LOW;
	opnd1->mem_type = MT_EMPTY;
    }
    opnd1->llvalue &= 0xff;
    return( NOT_ERROR );
}

static int high_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    TokenAssign( opnd1, opnd2 );
    if ( opnd2->kind == EXPR_ADDR && opnd2->inst != T_SEG ) {
	opnd1->inst = T_DOT_HIGH;
	opnd1->mem_type = MT_EMPTY;
    }
    opnd1->value = opnd1->value >> 8;
    opnd1->llvalue &= 0xff;
    return( NOT_ERROR );
}

static int tofloat( struct expr *opnd2, int size )
{
    if ( ModuleInfo.strict_masm_compat )
	return 1;
    opnd2->kind = EXPR_CONST;
    opnd2->float_tok = NULL;
    if ( size != 16 )
	quad_resize( opnd2, size );
    return( NOT_ERROR );
}

static int low32_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    if ( opnd2->kind == EXPR_FLOAT ) {
	if ( tofloat( opnd2, 8 ) )
	    return( ConstError( opnd1, opnd2 ) );
    }
    TokenAssign( opnd1, opnd2 );
    if ( opnd2->kind == EXPR_ADDR && opnd2->inst != T_SEG ) {
	opnd1->inst = T_LOW32;
	opnd1->mem_type = MT_EMPTY;
    }
    opnd1->llvalue &= 0xffffffff;
    return( NOT_ERROR );
}

static int high32_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    if ( opnd2->kind == EXPR_FLOAT ) {
	if ( tofloat( opnd2, 8 ) )
	    return( ConstError( opnd1, opnd2 ) );
    }
    TokenAssign( opnd1, opnd2 );
    if ( opnd2->kind == EXPR_ADDR && opnd2->inst != T_SEG ) {
	opnd1->inst = T_HIGH32;
	opnd1->mem_type = MT_EMPTY;
    }
    opnd1->llvalue = opnd1->llvalue >> 32;
    return( NOT_ERROR );
}

static int low64_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    if ( opnd2->kind == EXPR_FLOAT ) {
	if ( tofloat( opnd2, 16 ) )
	    return( ConstError( opnd1, opnd2 ) );
    }
    TokenAssign( opnd1, opnd2 );
    opnd1->mem_type = MT_QWORD;
    if ( opnd2->kind == EXPR_ADDR && opnd2->inst != T_SEG ) {
	opnd1->inst = T_LOW64;
	opnd1->mem_type = MT_EMPTY;
    }
    opnd1->hlvalue = 0;
    return( NOT_ERROR );
}

static int high64_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    if ( opnd2->kind == EXPR_FLOAT ) {
	if ( tofloat( opnd2, 16 ) )
	    return( ConstError( opnd1, opnd2 ) );
    } else if ( opnd2->negative && opnd2->hlvalue == 0 )
	opnd2->hlvalue = -1;

    TokenAssign( opnd1, opnd2 );
    opnd1->mem_type = MT_QWORD;
    if ( opnd2->kind == EXPR_ADDR && opnd2->inst != T_SEG ) {
	opnd1->inst = T_HIGH64;
	opnd1->mem_type = MT_EMPTY;
    }
    opnd1->llvalue = opnd1->hlvalue;
    opnd1->hlvalue = 0;
    return( NOT_ERROR );
}

static int this_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    if ( opnd2->is_type == 0 ) {
	return( fnasmerr( 2010 ) );
    }
    if ( CurrStruct ) {
	return( fnasmerr( 2034 ) );
    }
    if ( ModuleInfo.currseg == NULL ) {
	return( asmerr( 2034 ) );
    }
    if ( thissym == NULL ) {
	thissym = SymAlloc( "" );
	thissym->state = SYM_INTERNAL;
	thissym->isdefined = 1;
    }
    opnd1->kind = EXPR_ADDR;
    thissym->type = opnd2->type;
    if ( opnd2->type ) {
	thissym->mem_type = MT_TYPE;
    } else
	thissym->mem_type = opnd2->mem_type;
    opnd1->sym	= thissym;
    SetSymSegOfs( thissym );
    opnd1->mem_type = thissym->mem_type;
    return( NOT_ERROR );
}

static int wimask_op( int oper, struct expr *opnd1, struct expr *opnd2, struct asym *sym, char *name )
{
    if ( opnd2->is_type ) {
	sym = opnd2->type;
	if (sym->typekind != TYPE_RECORD ) {
	    return( fnasmerr( 2019 ) );
	}
    } else if ( opnd2->kind == EXPR_CONST ) {
	sym = opnd2->mbr;
    } else {
	sym = opnd2->sym;
    }
    if ( oper == T_DOT_MASK ) {
	int i;
	opnd1->value = 0;
	if ( opnd2->is_type ) {
	    opnd1->llvalue = GetRecordMask( (struct dsym *)sym );
	} else {
	    for ( i = sym->offset ;i < sym->offset + sym->total_size; i++ )
#if defined(LLONG_MAX) || defined(__GNUC__) || defined(__TINYC__)
		opnd1->llvalue |= 1ULL << i;
#else
		opnd1->llvalue |= 1i64 << i;
#endif
	}
    } else {
	if ( opnd2->is_type ) {
	    struct dsym *dir = (struct dsym *)sym;
	    struct sfield *fl;
	    for ( fl = dir->e.structinfo->head; fl; fl = fl->next )
		opnd1->value += fl->sym.total_size;
	} else
	    opnd1->value = sym->total_size;
    }
    opnd1->kind = EXPR_CONST;
    return( NOT_ERROR );
}

#define	 res(token, function) function ,
static int (* const unaryop[])( int, struct expr *, struct expr *, struct asym *, char * ) = {
#include <unaryop.h>
};
#undef res

static int plus_op( struct expr *opnd1, struct expr *opnd2 )
{
    if( check_direct_reg( opnd1, opnd2 ) == ERROR ) {
	return( fnasmerr( 2032 ) );
    }
    if ( opnd1->kind == EXPR_REG )
	opnd1->kind = EXPR_ADDR;
    if ( opnd2->kind == EXPR_REG )
	opnd2->kind = EXPR_ADDR;
    if ( opnd2->override ) {
	if ( opnd1->override ) {
	    if ( opnd1->override->token == opnd2->override->token ) {
		return( fnasmerr( 3013 ) );
	    }
	}
	opnd1->override = opnd2->override;
    }
    if( ( opnd1->kind == EXPR_CONST && opnd2->kind == EXPR_CONST ) ) {
	opnd1->llvalue += opnd2->llvalue;
    } else if ( opnd1->kind == EXPR_FLOAT && opnd2->kind == EXPR_FLOAT ) {
	if ( opnd2->float_tok )
	    atofloat( opnd2->chararray, opnd2->float_tok->string_ptr, 16, opnd2->negative, 0 );
	__addq( opnd1->chararray, opnd2->chararray );
    } else if( ( opnd1->kind == EXPR_ADDR && opnd2->kind == EXPR_ADDR ) ) {
	fix_struct_value( opnd1 );
	fix_struct_value( opnd2 );
	if ( index_connect( opnd1, opnd2 ) == ERROR )
	    return( ERROR );
	if( opnd2->sym != NULL ) {
	    if ( opnd1->sym != NULL &&
		opnd1->sym->state != SYM_UNDEFINED &&
		opnd2->sym->state != SYM_UNDEFINED ) {
		return( fnasmerr( 2101 ) );
	    }
	    opnd1->label_tok = opnd2->label_tok;
	    opnd1->sym = opnd2->sym;
	    if ( opnd1->mem_type == MT_EMPTY )
		opnd1->mem_type = opnd2->mem_type;
	    if ( opnd2->inst != EMPTY )
		opnd1->inst = opnd2->inst;
	}
	opnd1->llvalue += opnd2->llvalue;
	if ( opnd2->type )
	    opnd1->type = opnd2->type;
    } else if( check_both( opnd1, opnd2, EXPR_CONST, EXPR_ADDR ) ) {
	if( opnd1->kind == EXPR_CONST ) {
	    opnd2->llvalue += opnd1->llvalue;
	    opnd2->indirect |= opnd1->indirect;
	    if( opnd1->explicit == 1 ) {
		opnd2->explicit = 1;
		opnd2->mem_type = opnd1->mem_type;
	    } else if ( opnd2->mem_type == MT_EMPTY )
		opnd2->mem_type = opnd1->mem_type;
	    if ( opnd2->mbr == NULL )
		opnd2->mbr = opnd1->mbr;
	    if ( opnd2->type )
		opnd1->type = opnd2->type;
	    TokenAssign( opnd1, opnd2 );
	} else {

	    opnd1->llvalue += opnd2->llvalue;
	    if ( opnd2->mbr ) {
		opnd1->mbr = opnd2->mbr;
		opnd1->mem_type = opnd2->mem_type;
	    } else
	    if ( opnd1->mem_type == MT_EMPTY && opnd2->is_type == 0 )
		opnd1->mem_type = opnd2->mem_type;
	}
	fix_struct_value( opnd1 );
    } else {
	return( ConstError( opnd1, opnd2 ) );
    }
    return( NOT_ERROR );
}

static int minus_op( struct expr *opnd1, struct expr *opnd2 )
{
    struct asym	     *sym;
     ;
    if( check_direct_reg( opnd1, opnd2 ) == ERROR ) {
	return( fnasmerr( 2032 ) );
    }
    if (opnd1->kind == EXPR_ADDR && opnd2->kind == EXPR_ADDR &&
	opnd2->sym && opnd2->sym->state == SYM_UNDEFINED)
	;
    else
	MakeConst( opnd2 );
    if( ( opnd1->kind == EXPR_CONST && opnd2->kind == EXPR_CONST ) ) {
	opnd1->llvalue -= opnd2->llvalue;
    } else if ( opnd1->kind == EXPR_FLOAT && opnd2->kind == EXPR_FLOAT ) {
	if ( opnd2->float_tok )
	    atofloat( opnd2->chararray, opnd2->float_tok->string_ptr, 16, opnd2->negative, 0 );
	__subq( opnd1->chararray, opnd2->chararray );
    } else if( opnd1->kind == EXPR_ADDR && opnd2->kind == EXPR_CONST ) {
	opnd1->llvalue -= opnd2->llvalue;
	fix_struct_value( opnd1 );
    } else if( ( opnd1->kind == EXPR_ADDR && opnd2->kind == EXPR_ADDR ) ){

	fix_struct_value( opnd1 );
	fix_struct_value( opnd2 );
	if( opnd2->indirect ) {
	     ;
	    return( fnasmerr( 2032 ) );
	}
	if( opnd2->label_tok == NULL ) {
	    opnd1->value64 -= opnd2->value64;
	    opnd1->indirect |= opnd2->indirect;
	} else {
	    if( opnd1->label_tok == NULL || opnd1->sym == NULL || opnd2->sym == NULL ) {
		return( fnasmerr( 2094 ) );
	    }
	    sym = opnd1->sym;
	    opnd1->value += sym->offset;
	    sym = opnd2->sym;
	    if( Parse_Pass > PASS_1 ) {
		if ( ( sym->state == SYM_EXTERNAL ||
		     opnd1->sym->state == SYM_EXTERNAL) &&
		    sym != opnd1->sym ) {
		    return( fnasmerr(2018, opnd1->sym->name ) );
		}
		if ( sym->segment != opnd1->sym->segment ) {
		    return( fnasmerr( 2025 ) );
		}
	    }
	    opnd1->kind = EXPR_CONST;
	    if ( opnd1->sym->state == SYM_UNDEFINED ||
		opnd2->sym->state == SYM_UNDEFINED ) {
		opnd1->value = 1;
		if ( opnd1->sym->state != SYM_UNDEFINED ) {
		    opnd1->sym = opnd2->sym;
		    opnd1->label_tok = opnd2->label_tok;
		}
		opnd1->kind = EXPR_ADDR;
	    } else {
		opnd1->value64 -= sym->offset;
		opnd1->value64 -= opnd2->value64;
		opnd1->label_tok = NULL;
		opnd1->sym = NULL;
	    }
	    if( opnd1->indirect == 0 ) {
		if( opnd1->inst == T_OFFSET && opnd2->inst == T_OFFSET )
		    opnd1->inst = EMPTY;
	    } else {
		opnd1->kind = EXPR_ADDR;
	    }
	    opnd1->explicit = 0;
	    opnd1->mem_type = MT_EMPTY;
	}
    } else if( opnd1->kind == EXPR_REG &&
	      opnd2->kind == EXPR_CONST ) {
	opnd1->llvalue = -1 * opnd2->llvalue;
	opnd1->indirect |= opnd2->indirect;
	opnd1->kind = EXPR_ADDR;
    } else {
	return( ConstError( opnd1, opnd2 ) );
    }
    return( NOT_ERROR );
}

static int struct_field_error( struct expr *opnd )
{
    if ( opnd->is_opattr ) {
	opnd->kind = EXPR_ERROR;
	return( NOT_ERROR );
    }
    return( fnasmerr( 2166 ) );
}

static int dot_op( struct expr *opnd1, struct expr *opnd2 )
{
    if( check_direct_reg( opnd1, opnd2 ) == ERROR ) {
	return( fnasmerr( 2032 ) );
    }
    if ( opnd1->kind == EXPR_REG )
	opnd1->kind = EXPR_ADDR;
    if ( opnd2->kind == EXPR_REG )
	opnd2->kind = EXPR_ADDR;
    if ( opnd2->sym && opnd2->sym->state == SYM_UNDEFINED && Parse_Pass == PASS_1 ) {
	if ( !nullstruct )
	    nullstruct = CreateTypeSymbol( NULL, "", 0 );
	opnd2->type = nullstruct;
	opnd2->is_type = 1;
	opnd2->sym = NULL;
	opnd2->kind = EXPR_CONST;
    }
    if( ( opnd1->kind == EXPR_ADDR && opnd2->kind == EXPR_ADDR ) ) {
	if ( opnd2->mbr == NULL && !ModuleInfo.oldstructs ) {
	    return( struct_field_error( opnd1 ) );
	}
	if ( index_connect( opnd1, opnd2 ) == ERROR )
	    return( ERROR );
	if( opnd2->sym != NULL ) {
	    if( opnd1->sym != NULL &&
		opnd1->sym->state != SYM_UNDEFINED &&
		opnd2->sym->state != SYM_UNDEFINED ) {
		return( fnasmerr( 2101 ) );
	    }
	    opnd1->label_tok = opnd2->label_tok;
	    opnd1->sym = opnd2->sym;
	}
	if( opnd2->mbr != NULL ) {
	    opnd1->mbr = opnd2->mbr;
	}
	opnd1->value += opnd2->value;
	if( opnd1->explicit == 0 ) {
	    opnd1->mem_type = opnd2->mem_type;
	}
	if ( opnd2->type )
	    opnd1->type = opnd2->type;
    } else if( ( opnd1->kind == EXPR_CONST ) && ( opnd2->kind == EXPR_ADDR ) ) {
	if ( opnd1->is_type && opnd1->type ) {
	    opnd2->assumecheck = 0;
	    opnd1->llvalue = 0;
	}
	if ( ( !ModuleInfo.oldstructs ) && ( opnd1->is_type == 0 && opnd1->mbr == NULL ) )
	    return( struct_field_error( opnd1 ) );
	if ( opnd1->mbr && opnd1->mbr->state == SYM_TYPE )
	    opnd1->llvalue = opnd1->mbr->offset;
	opnd2->indirect |= opnd1->indirect;
	opnd2->llvalue += opnd1->llvalue;
	if ( opnd2->mbr )
	    opnd1->type = opnd2->type;
	TokenAssign( opnd1, opnd2 );
    } else if( ( opnd1->kind == EXPR_ADDR ) && ( opnd2->kind == EXPR_CONST ) ) {
	if ( (!ModuleInfo.oldstructs) && ( opnd2->type == NULL || opnd2->is_type == 0 ) && opnd2->mbr == NULL ) {
	    return( struct_field_error( opnd1 ) );
	}
	if ( opnd2->is_type && opnd2->type ) {
	    opnd1->assumecheck = 0;
	    /* v2.37: adjust for type's size only (japheth) */
	    opnd2->llvalue -= opnd2->type->total_size;
	}
	if ( opnd2->mbr && opnd2->mbr->state == SYM_TYPE )
	    opnd2->llvalue = opnd2->mbr->offset;
	opnd1->llvalue += opnd2->llvalue;
	opnd1->mem_type = opnd2->mem_type;
	if( opnd2->mbr != NULL )
	    opnd1->mbr = opnd2->mbr;
	opnd1->type = opnd2->type;
    } else if ( opnd1->kind == EXPR_CONST && opnd2->kind == EXPR_CONST ) {
	if ( opnd2->mbr == NULL && !ModuleInfo.oldstructs ) {
	    return( struct_field_error( opnd1 ) );
	}
	if ( opnd1->type != NULL ) {
	    if ( opnd1->mbr != NULL )
		opnd1->llvalue += opnd2->llvalue;
	    else {
		opnd1->llvalue = opnd2->llvalue;
	    }
	    opnd1->mbr = opnd2->mbr;
	    opnd1->mem_type = opnd2->mem_type;
	    opnd1->is_type = opnd2->is_type;
	    if ( opnd1->type != opnd2->type )
		opnd1->type = opnd2->type;
	    else
		opnd1->type = NULL;
	} else {
	    opnd1->llvalue += opnd2->llvalue;
	    opnd1->mbr = opnd2->mbr;
	    opnd1->mem_type = opnd2->mem_type;
	}
    } else {
	return( struct_field_error( opnd1 ) );
    }
    return( NOT_ERROR );
}

static int colon_op( struct expr *opnd1, struct expr *opnd2 )
{
    int_32	temp;
    struct asym *sym;

    if( opnd2->override != NULL ) {
	if ( ( opnd1->kind == EXPR_REG && opnd2->override->token == T_REG ) ||
	    ( opnd1->kind == EXPR_ADDR && opnd2->override->token == T_ID ) ) {
	    return( fnasmerr( 3013 ) );
	}
    }
    switch ( opnd2->kind ) {
    case EXPR_REG:
	if ( opnd2->indirect == 0 ) {
	    return( fnasmerr( 2032 ) );
	}
	break;
    case EXPR_FLOAT:
	return( fnasmerr( 2050 ) );
    }
    if( opnd1->kind == EXPR_REG ) {
	if( opnd1->idx_reg != NULL ) {
	    return( fnasmerr( 2032 ) );
	}
	temp = opnd1->base_reg->tokval;
	if ( ( SpecialTable[temp].value & OP_SR ) == 0 ) {
	    return( fnasmerr( 2096 ) );
	}
	opnd2->override = opnd1->base_reg;
	opnd2->indirect |= opnd1->indirect;
	if ( opnd2->kind == EXPR_CONST ) {
	    opnd2->kind = EXPR_ADDR;
	}
	if( opnd1->explicit ) {
	    opnd2->explicit = opnd1->explicit;
	    opnd2->mem_type = opnd1->mem_type;
	    opnd2->Ofssize  = opnd1->Ofssize;
	}
	TokenAssign( opnd1, opnd2 );
	if ( opnd2->type )
	    opnd1->type = opnd2->type;
    } else if( opnd1->kind == EXPR_ADDR &&
	      opnd1->override == NULL &&
	      opnd1->inst == EMPTY &&
	      opnd1->value == 0 &&
	      opnd1->sym &&
	      opnd1->base_reg == NULL &&
	      opnd1->idx_reg == NULL ) {
	sym = opnd1->sym;
	if( sym->state == SYM_GRP || sym->state == SYM_SEG ) {
	    opnd2->kind = EXPR_ADDR;
	    opnd2->override = opnd1->label_tok;
	    opnd2->indirect |= opnd1->indirect;
	    if( opnd1->explicit ) {
		opnd2->explicit = opnd1->explicit;
		opnd2->mem_type = opnd1->mem_type;
		opnd2->Ofssize	= opnd1->Ofssize;
	    }
	    TokenAssign( opnd1, opnd2 );
	    opnd1->type = opnd2->type;
	} else if( Parse_Pass > PASS_1 || sym->state != SYM_UNDEFINED ) {
	    return( fnasmerr( 2096 ) );
	}
    } else {
	return( fnasmerr( 2096 ) );
    }
    return( NOT_ERROR );
}

static int positive_op( struct expr *opnd1, struct expr *opnd2 )
{
    MakeConst( opnd2 );
    if( opnd2->kind == EXPR_CONST ) {
	opnd1->kind = EXPR_CONST;
	opnd1->llvalue = opnd2->llvalue;
	opnd1->hlvalue = opnd2->hlvalue;
    } else if( opnd2->kind == EXPR_FLOAT ) {
	opnd1->kind = EXPR_FLOAT;
	opnd1->mem_type = opnd2->mem_type;
	opnd1->llvalue = opnd2->llvalue;
	opnd1->hlvalue = opnd2->hlvalue;
	opnd1->chararray[15] &= ~0x80;
	opnd1->negative = opnd2->negative;
    } else {
	return( fnasmerr( 2026 ) );
    }
    return( NOT_ERROR );
}

static int negative_op( struct expr *opnd1, struct expr *opnd2 )
{
    MakeConst( opnd2 );
    if( opnd2->kind == EXPR_CONST ) {
	opnd1->kind = EXPR_CONST;
	opnd1->llvalue = -opnd2->llvalue;
	if ( opnd2->hlvalue ) {
	    opnd1->hlvalue = -opnd2->hlvalue;
	    if ( opnd1->chararray[7] & 0x80 )
		opnd1->hlvalue--;
	}
	opnd1->negative = 1 - opnd2->negative;
    } else if( opnd2->kind == EXPR_FLOAT ) {
	opnd1->kind = EXPR_FLOAT;
	opnd1->mem_type = opnd2->mem_type;
	opnd1->llvalue = opnd2->llvalue;
	opnd1->hlvalue = opnd2->hlvalue;
	opnd1->chararray[15] ^= 0x80;
	opnd1->negative = 1 - opnd2->negative;
    } else {
	return( fnasmerr( 2026 ) );
    }
    return( NOT_ERROR );
}

static void CheckAssume( struct expr *opnd )
{
    struct asym *sym = NULL;

    if ( opnd->explicit ) {
	if ( opnd->type && opnd->type->mem_type == MT_PTR ) {
	    if ( opnd->type->is_ptr == 1 ) {
		opnd->mem_type = opnd->type->ptr_memtype;
		opnd->type = opnd->type->target_type;
		return;
	    }
	}
    }

    if ( opnd->idx_reg )
	sym = GetStdAssumeEx( opnd->idx_reg->bytval );
    if (!sym && opnd->base_reg )
	sym = GetStdAssumeEx( opnd->base_reg->bytval );

    if ( sym ) {
	if ( sym->mem_type == MT_TYPE )
	    opnd->type = sym->type;
	else if ( sym->is_ptr == 1 ) {
	    opnd->type = sym->target_type;
	    if ( sym->target_type )
		opnd->mem_type = sym->target_type->mem_type;
	    else
		opnd->mem_type = sym->ptr_memtype;
	}
    }
}

static int check_streg( struct expr *opnd1, struct expr *opnd2 )
{
    if ( opnd1->scale > 0 ) {
	return( fnasmerr( 2032 ) );
    }
    opnd1->scale++;
    if ( opnd2->kind != EXPR_CONST ) {
	return( fnasmerr( 2032 ) );
    }
    opnd1->st_idx = opnd2->value;
    return( NOT_ERROR );
}

static void cmp_types( struct expr *opnd1, struct expr *opnd2, int trueval )
{
    struct asym *type1;
    struct asym *type2;
    if ( opnd1->mem_type == MT_PTR && opnd2->mem_type == MT_PTR ) {
	type1 = ( opnd1->type ? opnd1->type : SymFind(opnd1->type_tok->string_ptr) );
	type2 = ( opnd2->type ? opnd2->type : SymFind(opnd2->type_tok->string_ptr) );
	opnd1->value64 = ( ( type1->is_ptr == type2->is_ptr &&
			    type1->ptr_memtype == type2->ptr_memtype &&
			    type1->target_type == type2->target_type ) ? trueval : ~trueval );
    } else {
	if ( opnd1->type && opnd1->type->typekind == TYPE_TYPEDEF && opnd1->type->is_ptr == 0 )
	    opnd1->type = NULL;
	if ( opnd2->type && opnd2->type->typekind == TYPE_TYPEDEF && opnd2->type->is_ptr == 0 )
	    opnd2->type = NULL;
	opnd1->value64 = ( ( opnd1->mem_type == opnd2->mem_type &&
			    opnd1->type == opnd2->type ) ? trueval : ~trueval );
    }
}

static int calculate( struct expr *opnd1, struct expr *opnd2, const struct asm_tok *oper )
{
    int_32	temp;
    struct asym *sym;
    char	*name;

    opnd1->quoted_string = NULL;
    if ( opnd2->hlvalue && opnd2->mem_type != MT_REAL16 ) {
	if ( !( oper->token == T_UNARY_OPERATOR && opnd2->kind == EXPR_CONST &&
		ModuleInfo.Ofssize == USE64 ) ) {
	    if ( !(opnd2->is_opattr || ((oper->token == '+' || oper->token == '-') && oper->specval == 0)) )
		return( fnasmerr( 2084, opnd2->hlvalue, opnd2->value64 ) );
	}
    }
    switch( oper->token ) {
    case T_OP_SQ_BRACKET:
	if ( opnd2->assumecheck == 1 ) {
	    opnd2->assumecheck = 0;
	    if ( opnd1->sym == NULL )
		CheckAssume( opnd2 );
	}
	if ( opnd1->kind == EXPR_EMPTY ) {
	    TokenAssign( opnd1, opnd2 );
	    opnd1->type = opnd2->type;
	    if ( opnd1->is_type && opnd1->kind == EXPR_CONST )
		opnd1->is_type = 0;
	    break;
	}
	if ( opnd1->is_type == 1 && opnd1->type == NULL &&
	    (opnd2->kind == EXPR_ADDR || opnd2->kind == EXPR_REG ) ) {
	    return( fnasmerr( 2009 ) );
	}
	if ( opnd1->base_reg && opnd1->base_reg->tokval == T_ST )
	    return( check_streg( opnd1, opnd2 ) );
	return( plus_op( opnd1, opnd2 ) );
    case T_OP_BRACKET:
	if ( opnd1->kind == EXPR_EMPTY ) {
	    TokenAssign( opnd1, opnd2 );
	    opnd1->type = opnd2->type;
	    break;
	}
	if ( opnd1->is_type == 1 && opnd2->kind == EXPR_ADDR ) {
	    return( fnasmerr( 2009 ) );
	}
	if ( opnd1->base_reg && opnd1->base_reg->tokval == T_ST )
	    return( check_streg( opnd1, opnd2 ) );

	return( plus_op( opnd1, opnd2 ) );
    case '+':
	if ( oper->specval == 0 )
	    return( positive_op( opnd1, opnd2 ) );
	return( plus_op( opnd1, opnd2 ) );
    case '-':
	if ( oper->specval == 0 )
	    return( negative_op( opnd1, opnd2 ) );
	return( minus_op( opnd1, opnd2 ) );
    case T_DOT:
	return( dot_op( opnd1, opnd2 ) );
    case T_COLON:
	return( colon_op( opnd1, opnd2 ) );
    case '*':
	MakeConst( opnd1 );
	MakeConst( opnd2 );
	if( ( opnd1->kind == EXPR_CONST && opnd2->kind == EXPR_CONST ) ) {
	    opnd1->llvalue *= opnd2->llvalue;
	} else if( check_both( opnd1, opnd2, EXPR_REG, EXPR_CONST ) ) {
	    if( check_direct_reg( opnd1, opnd2 ) == ERROR ) {
		return( fnasmerr( 2032 ) );
	    }
	    if( opnd2->kind == EXPR_REG ) {
		opnd1->idx_reg = opnd2->base_reg;
		opnd1->scale = opnd1->value;
		opnd1->value = 0;
	    } else {
		opnd1->idx_reg = opnd1->base_reg;
		opnd1->scale = opnd2->value;
	    }
	    if ( opnd1->scale == 0 ) {
		return( fnasmerr( 2083 ) );
	    }
	    opnd1->base_reg = NULL;
	    opnd1->indirect = 1;
	    opnd1->kind = EXPR_ADDR;
	} else if ( ( opnd1->kind == EXPR_FLOAT && opnd2->kind == EXPR_FLOAT ) ) {
	    if ( opnd2->float_tok )
		atofloat( opnd2->chararray, opnd2->float_tok->string_ptr, 16, opnd2->negative, 0);
	    __mulq(opnd1->chararray, opnd2->chararray);
	} else {
	    return( ConstError( opnd1, opnd2 ) );
	}
	break;
    case '/':
	if ( ( opnd1->kind == EXPR_FLOAT && opnd2->kind == EXPR_FLOAT ) ) {
	    if ( opnd2->float_tok )
		atofloat( opnd2->chararray, opnd2->float_tok->string_ptr, 16, opnd2->negative, 0);
	    __divq(opnd1->chararray, opnd2->chararray);
	    break;
	}
	MakeConst( opnd1 );
	MakeConst( opnd2 );
	if( ( opnd1->kind == EXPR_CONST && opnd2->kind == EXPR_CONST ) == 0 ) {
	    return( ConstError( opnd1, opnd2 ) );
	}
	if ( opnd2->llvalue == 0 ) {
	    return( fnasmerr( 2169 ) );
	}
	opnd1->value64 /= opnd2->value64;
	break;
    case T_BINARY_OPERATOR:
	if ( oper->tokval == T_PTR ) {
	    if ( opnd1->is_type == 0 ) {
		if ( opnd1->sym && opnd1->sym->state == SYM_UNDEFINED ) {
		    CreateTypeSymbol( opnd1->sym, NULL, 1 );
		    opnd1->type = opnd1->sym;
		    opnd1->sym = NULL;
		    opnd1->is_type = 1;
		} else {
		    return( fnasmerr( 2010 ) );
		}
	    }
	    opnd2->explicit = 1;
	    if ( opnd2->kind == EXPR_REG && ( opnd2->indirect == 0 || opnd2->assumecheck == 1 ) ) {
		temp = opnd2->base_reg->tokval;
		if ( SpecialTable[temp].value & OP_SR ) {
		    if ( opnd1->value != 2 && opnd1->value != 4 ) {
			return( fnasmerr( 2032 ) );
		    }
		} else if ( opnd1->value != SizeFromRegister( temp ) ) {
		    return( fnasmerr( 2032 ) );
		}
	    } else if ( opnd2->kind == EXPR_FLOAT ) {
		if ( !( opnd1->mem_type & MT_FLOAT ) ) {
		    return( fnasmerr( 2050 ) );
		}
	    }
	    opnd2->mem_type = opnd1->mem_type;
	    opnd2->Ofssize  = opnd1->Ofssize;
	    if ( opnd2->is_type )
		opnd2->value  = opnd1->value;
	    if ( opnd1->override != NULL ) {
		if ( opnd2->override == NULL )
		    opnd2->override = opnd1->override;
		opnd2->kind = EXPR_ADDR;
	    }
	    TokenAssign( opnd1, opnd2 );
	    break;
	}
	MakeConst( opnd1 );
	MakeConst( opnd2 );
	if ( ( opnd1->kind == EXPR_CONST && opnd2->kind == EXPR_CONST ) )
	    ;
	else if ( oper->precedence == 10 &&
		 opnd1->kind != EXPR_CONST ) {
	    if ( opnd1->kind == EXPR_ADDR && opnd1->indirect == 0 && opnd1->sym )
		if ( opnd2->kind == EXPR_ADDR && opnd2->indirect == 0 && opnd2->sym ) {
		    if ( MakeConst2( opnd1, opnd2 ) == ERROR ) {
			return( ERROR );
		    }
		} else {
		    return( fnasmerr( 2094 ) );
		}
	    else {
		return( fnasmerr( 2095 ) );
	    }
	} else {
	    return( ConstError( opnd1, opnd2 ) );
	}
	switch( oper->tokval ) {
	case T_EQ:
	    if ( opnd1->is_type && opnd2->is_type ) {
		cmp_types( opnd1, opnd2, -1 );
	    } else
	    opnd1->value64 = ( opnd1->value64 == opnd2->value64 ? -1:0 );
	    break;
	case T_NE:
	    if ( opnd1->is_type && opnd2->is_type ) {
		cmp_types( opnd1, opnd2, 0 );
	    } else
	    opnd1->value64 = ( opnd1->value64 != opnd2->value64 ? -1:0 );
	    break;
	case T_LT:
	    opnd1->value64 = ( opnd1->value64 <	 opnd2->value64 ? -1:0 );
	    break;
	case T_LE:
	    opnd1->value64 = ( opnd1->value64 <= opnd2->value64 ? -1:0 );
	    break;
	case T_GT:
	    opnd1->value64 = ( opnd1->value64 >	 opnd2->value64 ? -1:0 );
	    break;
	case T_GE:
	    opnd1->value64 = ( opnd1->value64 >= opnd2->value64 ? -1:0 );
	    break;
	case T_MOD:
	    if ( opnd2->llvalue == 0 ) {
		return( fnasmerr( 2169 ) );
	    } else
		opnd1->llvalue %= opnd2->llvalue;
	    break;
	case T_SHL:
	     ;
	    if ( opnd2->value < 0 )
		fnasmerr( 2092 );
	    else if ( opnd2->value >= ( 8 * sizeof( opnd1->llvalue ) ) )
		opnd1->llvalue = 0;
	    else
		opnd1->llvalue = opnd1->llvalue << opnd2->value;
	    if ( ModuleInfo.m510 ) {
		opnd1->hvalue = 0;
		opnd1->hlvalue = 0;
	    }
	    break;
	case T_SHR:
	    if ( opnd2->value < 0 )
		fnasmerr( 2092 );
	    else if ( opnd2->value >= ( 8 * sizeof( opnd1->llvalue ) ) )
		opnd1->llvalue = 0;
	    else {
		if ( opnd1->value == -1 && ModuleInfo.Ofssize == USE32 )
		    opnd1->llvalue = (unsigned long)opnd1->llvalue >> opnd2->value;
		else
		    opnd1->llvalue = opnd1->llvalue >> opnd2->value;
	    }
	    break;
	case T_AND:
	    opnd1->llvalue &= opnd2->llvalue;
	    break;
	case T_OR:
	    opnd1->llvalue |= opnd2->llvalue;
	    break;
	case T_XOR:
	    opnd1->llvalue ^= opnd2->llvalue;
	    break;
	}
	break;
    case T_UNARY_OPERATOR:
	if( oper->tokval == T_NOT ) {
	    MakeConst( opnd2 );
	    if( opnd2->kind != EXPR_CONST ) {
		return( fnasmerr( 2026 ) );
	    }
	    TokenAssign( opnd1, opnd2 );
	    opnd1->llvalue = ~(opnd2->llvalue);
	    break;
	}
	temp = SpecialTable[oper->tokval].value;
	sym = opnd2->sym;
	if( opnd2->mbr != NULL )
	    sym = opnd2->mbr;
	if ( opnd2->inst != EMPTY )
	    name = oper->tokpos + strlen( oper->string_ptr ) + 1;
	else if ( sym )
	    name = sym->name;
	else if ( opnd2->base_reg != NULL && opnd2->indirect == 0 )
	    name = opnd2->base_reg->string_ptr;
	else
	    name = oper->tokpos + strlen( oper->string_ptr ) + 1;
	switch ( opnd2->kind ) {
	case EXPR_CONST:
	    if ( opnd2->mbr != NULL && opnd2->mbr->state != SYM_TYPE ) {
		if ( opnd2->mbr->mem_type == MT_BITS ) {
		    if ( ( temp & AT_BF ) == 0 ) {
			return( invalid_operand( opnd2, oper->string_ptr, name ) );
		    }
		} else {
		    if ( ( temp & AT_FIELD ) == 0 ) {
			return( invalid_operand( opnd2, oper->string_ptr, name ) );
		    }
		}
	    } else if ( opnd2->is_type ) {
		if ( ( temp & AT_TYPE ) == 0 ) {
		    return( invalid_operand( opnd2, oper->string_ptr, name ) );
		}
	    } else {
		if ( ( temp & AT_NUM ) == 0 ) {
		    if ( opnd2->is_opattr )
			return ERROR;
		    if ( temp == 2 )
			return( fnasmerr( 2094 ));
		    return fnasmerr( 2009 );
		}
	    }
	    break;
	case EXPR_ADDR:
	    if ( opnd2->indirect == 1 && opnd2->sym == NULL ) {
		if ( ( temp & AT_IND ) == 0 ) {
		    return( invalid_operand( opnd2, oper->string_ptr, name ) );
		}
	    } else {
		if ( ( temp & AT_LABEL ) == 0 ) {
		    if ( opnd2->is_opattr )
			return ERROR;
		    if ( oper->tokval == T_HIGHWORD && opnd2->flags1 != 4 )
			return( fnasmerr( 2105 ) );
		    if ( opnd2->flags1 == 4 )
			return( fnasmerr( 2026 ) );
		    else
			return( fnasmerr( 2009 ) );
		}
	    }
	    break;
	case EXPR_REG:
	    if ( ( temp & AT_REG ) == 0 ) {
		if ( !opnd2->is_opattr ) {
		    if ( temp == 2 )
			return( fnasmerr( 2094 ) );
		    if ( temp == 0x33 ) {
			if ( opnd2->indirect == 1 )
			   return( fnasmerr( 2098 ) );
			else
			   return( fnasmerr( 2032 ) );
		    }
		    if ( ( temp & 0x20 ) != 0 )
			return( fnasmerr( 2105 ) );
		    if ( opnd2->indirect == 1 )
			return( fnasmerr( 2081 ) );
		    else
			return( fnasmerr( 2009 ) );
		} else {
		    return ERROR;
		}
	    }
	    break;
	case EXPR_FLOAT:
	    if ( ( temp & AT_FLOAT ) == 0 ) {
		return( fnasmerr( 2050 ) );
	    }
	    break;
	}
	return( unaryop[ SpecialTable[oper->tokval].sflags ]( oper->tokval, opnd1, opnd2, sym, name ) );
    default:
	return( fnasmerr( 2008, oper->string_ptr ) );
    }
    return( NOT_ERROR );
}

static void PrepareOp( struct expr *opnd, const struct expr *old, const struct asm_tok *oper )
{
    opnd->is_opattr = old->is_opattr;
    switch ( oper->token ) {
    case T_DOT:
	if ( old->type ) {
	    opnd->type = old->type;
	    opnd->is_dot = 1;
	} else if ( !ModuleInfo.oldstructs && old->sym && old->sym->state == SYM_UNDEFINED ) {
	    opnd->type = NULL;
	    opnd->is_dot = 1;
	}
	break;
    case T_UNARY_OPERATOR:
	switch ( oper->tokval ) {
	case T_OPATTR:
	case T_DOT_TYPE:
	    opnd->is_opattr = 1;
	    break;
	}
	break;
    }
}

static void OperErr( int i, struct asm_tok tokenarray[] )
{
    if ( tokenarray[i].token <= T_BAD_NUM ) {
	fnasmerr( 2206 );
    } else
	fnasmerr( 2008, tokenarray[i].string_ptr );
    return;
}

static int evaluate( struct expr *opnd1, int *i, struct asm_tok tokenarray[], const int end,
	const uint_8 flags )
{
    int rc = NOT_ERROR;

    if ( opnd1->kind == EXPR_EMPTY &&  !( tokenarray[*i].token == T_OP_BRACKET || tokenarray[*i].token == T_OP_SQ_BRACKET || tokenarray[*i].token == '+' || tokenarray[*i].token == '-' || tokenarray[*i].token == T_UNARY_OPERATOR ) ) {
	rc = get_operand( opnd1, i, tokenarray, flags );
    }
    while ( rc == NOT_ERROR && *i < end && !( tokenarray[*i].token == T_CL_BRACKET ) && !( tokenarray[*i].token == T_CL_SQ_BRACKET ) ) {
	int curr_operator;
	struct expr opnd2;
	curr_operator = *i;

	if ( opnd1->kind != EXPR_EMPTY ) {
	    if ( tokenarray[curr_operator].token == '+' || tokenarray[curr_operator].token == '-' )
		tokenarray[curr_operator].specval = 1;
	    else if( !( tokenarray[curr_operator].token >= T_OP_BRACKET ||
		tokenarray[curr_operator].token == T_UNARY_OPERATOR ||
		tokenarray[curr_operator].token == T_BINARY_OPERATOR ) ||
		tokenarray[curr_operator].token == T_UNARY_OPERATOR ) {

		/* v2.26 - added for {k1}{z}.. */
		if ( tokenarray[curr_operator].token == T_STRING &&
		     tokenarray[curr_operator].string_delim == '{' ) {
		    tokenarray[curr_operator].hll_flags |= T_EVEX_OPT;
		    (*i)++;
		    continue;
		} else {
		    rc = ERROR;
		    if ( !opnd1->is_opattr )
			OperErr( curr_operator, tokenarray );
		    break;
		}
	    }
#if 0
	    if ( opnd1->kind == EXPR_FLOAT && opnd1->mem_type != MT_REAL16 ) {
		if ( tokenarray[curr_operator].token == '*' ||
		     tokenarray[curr_operator].token == '/' ||
		     tokenarray[curr_operator].specval == 1 ) {
		    opnd1->mem_type = MT_REAL16;
		    atofloat( opnd1->chararray, opnd1->float_tok->string_ptr, 16, opnd1->negative, 0);
		}
	    }
#endif
	}
	(*i)++;
	init_expr( &opnd2 );
	PrepareOp( &opnd2, opnd1, &tokenarray[curr_operator] );
	if( tokenarray[curr_operator].token == T_OP_BRACKET ||
	   tokenarray[curr_operator].token == T_OP_SQ_BRACKET ) {
	    int exp_token = T_CL_BRACKET;
	    if( tokenarray[curr_operator].token == T_OP_SQ_BRACKET ) {
		exp_token = T_CL_SQ_BRACKET;
	    } else if ( opnd1->is_dot ) {
		opnd2.type = opnd1->type;
		opnd2.is_dot = 1;
	    }
	    rc = evaluate( &opnd2, i, tokenarray, end,
		(const uint_8)( ( flags | ( exp_token == T_CL_SQ_BRACKET ? EXPF_IN_SQBR : 0 ) ) & ~EXPF_ONEOPND ) );
	    if( !( tokenarray[*i].token == exp_token ) ) {
		if ( rc != ERROR ) {
		    fnasmerr( 2157 );
		    if ( ( tokenarray[*i].token == T_COMMA ) && opnd1->sym && opnd1->sym->state == SYM_UNDEFINED )
			fnasmerr( 2006, opnd1->sym->name );
		}
		rc = ERROR;
	    } else {
		(*i)++;
	    }
	} else if( ( tokenarray[*i].token == T_OP_BRACKET || tokenarray[*i].token == T_OP_SQ_BRACKET || tokenarray[*i].token == '+' || tokenarray[*i].token == '-' || tokenarray[*i].token == T_UNARY_OPERATOR ) ) {
	    rc = evaluate( &opnd2, i, tokenarray, end, (const uint_8)(flags | EXPF_ONEOPND) );
	} else {
	    rc = get_operand( &opnd2, i, tokenarray, flags );
	}
	while( rc != ERROR && *i < end && !( tokenarray[*i].token == T_CL_BRACKET ) && !( tokenarray[*i].token == T_CL_SQ_BRACKET ) ) {
	    if ( tokenarray[*i].token == '+' || tokenarray[*i].token == '-' )
		tokenarray[*i].specval = 1;
	    else if( !( tokenarray[*i].token >= T_OP_BRACKET || tokenarray[*i].token == T_UNARY_OPERATOR || tokenarray[*i].token == T_BINARY_OPERATOR ) || tokenarray[*i].token == T_UNARY_OPERATOR ) {

		/* v2.26 - added for {k1}{z}.. */
		if ( tokenarray[*i].token == T_STRING &&
		     tokenarray[*i].string_delim == '{' ) {
		    tokenarray[*i].hll_flags |= T_EVEX_OPT;
		    (*i)++;
		} else {
		    rc = ERROR;
		    if ( !opnd1->is_opattr )
			OperErr( *i, tokenarray );
		}
		break;
	    }
	    if( get_precedence( &tokenarray[*i] ) >= get_precedence( &tokenarray[curr_operator] ) )
		break;
	    rc = evaluate( &opnd2, i, tokenarray, end, (const uint_8)(flags | EXPF_ONEOPND) );
	}
	if ( rc == ERROR && opnd2.is_opattr ) {
	    while( *i < end && !( tokenarray[*i].token == T_CL_BRACKET ) && !( tokenarray[*i].token == T_CL_SQ_BRACKET ) ) {
		(*i)++;
	    }
	    opnd2.kind = EXPR_EMPTY;
	    rc = NOT_ERROR;
	}
	if( rc != ERROR )
	    rc = calculate( opnd1, &opnd2, &tokenarray[curr_operator] );
	if( flags & EXPF_ONEOPND )
	    break;
    }
    return( rc );
}

static int noasmerr( int msg, ... )
{
    return( ERROR );
}

int EvalOperand( int *start_tok, struct asm_tok tokenarray[], int end_tok, struct expr *result, uint_8 flags )
{
    int i;

    init_expr( result );
    for( i = *start_tok; ( i < end_tok ) && is_expr_item( &tokenarray[i] ); i++ );
    if ( i == *start_tok )
	return( NOT_ERROR );
    fnasmerr = ( ( flags & EXPF_NOERRMSG ) ? noasmerr : asmerr );
    return ( evaluate( result, start_tok, tokenarray, i, flags ) );
}

int EmitConstError( const struct expr *opnd )
{
    /*
    if ( opnd->hlvalue != 0 )
	asmerr( 2071, opnd->hlvalue, opnd->value64 );
    else
	asmerr( 2071, opnd->value64 );
    return( ERROR );
    */
    return asmerr( 2084 );
}

void ExprEvalInit( void )
{
    thissym = NULL;
    nullstruct = NULL;
    nullmbr = NULL;
}
