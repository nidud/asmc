/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	Processing of directives
*		PUBLIC
*		EXT[E]RN
*		EXTERNDEF
*		PROTO
*		COMM
****************************************************************************/

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <segment.h>
#include <fastpass.h>
#include <listing.h>
#include <equate.h>
#include <fixup.h>
#include <mangle.h>
#include <label.h>
#include <input.h>
#include <expreval.h>
#include <types.h>
#include <condasm.h>
#include <proc.h>
#include <extern.h>

/* Masm accepts EXTERN for internal absolute symbols:
 * X EQU 0
 * EXTERN X:ABS
 *
 * However, the other way:
 * EXTERN X:ABS
 * X EQU 0
 *
 * is rejected! MASM_EXTCOND=1 will copy this behavior for JWasm.
 */
#define MASM_EXTCOND 1	/* 1 is Masm compatible */

static const char szCOMM[] = "COMM";

#define mangle_type NULL

/* create external.
 * sym must be NULL or of state SYM_UNDEFINED!
 */
static struct asym *CreateExternal( struct asym *sym, const char *name, char weak )
/*********************************************************************************/
{
    if ( sym == NULL )
	sym = SymCreate( name );
    else
	sym_remove_table( &SymTables[TAB_UNDEF], (struct dsym *)sym );

    if ( sym ) {
	sym->state = SYM_EXTERNAL;
	sym->seg_ofssize = ModuleInfo.Ofssize;
	sym->iscomm = FALSE;
	sym->weak = weak;
	sym_add_table( &SymTables[TAB_EXT], (struct dsym *)sym ); /* add EXTERNAL */
    }
    return( sym );
}

/* create communal.
 * sym must be NULL or of state SYM_UNDEFINED!
 */
static struct asym * __fastcall CreateComm( struct asym *sym, const char *name )
/******************************************************************/
{
    if ( sym == NULL )
	sym = SymCreate( name );
    else
	sym_remove_table( &SymTables[TAB_UNDEF], (struct dsym *)sym );

    if ( sym ) {
	sym->state = SYM_EXTERNAL;
	sym->seg_ofssize = ModuleInfo.Ofssize;
	sym->iscomm = TRUE;
	sym->weak = FALSE;
	sym->isfar = FALSE;
	sym_add_table( &SymTables[TAB_EXT], (struct dsym *)sym ); /* add EXTERNAL */
    }
    return( sym );
}

/* create a prototype.
 * used by PROTO, EXTERNDEF and EXT[E]RN directives.
 */

static struct asym *CreateProto( int i, struct asm_tok tokenarray[], const char *name, unsigned char langtype )
/**************************************************************************************************************/
{
    struct asym	     *sym;
    struct dsym	     *dir;

    sym = SymSearch( name );

    /* the symbol must be either NULL or state
     * - SYM_UNDEFINED
     * - SYM_EXTERNAL + isproc == FALSE ( previous EXTERNDEF )
     * - SYM_EXTERNAL + isproc == TRUE ( previous PROTO )
     * - SYM_INTERNAL + isproc == TRUE ( previous PROC )
     */
    if( sym == NULL ||
       sym->state == SYM_UNDEFINED ||
       ( sym->state == SYM_EXTERNAL && sym->weak == TRUE && sym->isproc == FALSE )) {
	if ( NULL == ( sym = CreateProc( sym, name, SYM_EXTERNAL ) ) )
	    return( NULL ); /* name was probably invalid */
    } else if ( sym->isproc == FALSE ) {
	asmerr( 2005, sym->name );
	return( NULL );
    }
    dir = (struct dsym *)sym;

    /* a PROTO typedef may be used */
    if ( tokenarray[i].token == T_ID ) {
	struct asym * sym2;
	sym2 = SymSearch( tokenarray[i].string_ptr );
	if ( sym2 && sym2->state == SYM_TYPE && sym2->mem_type == MT_PROC ) {
	    i++;
	    if ( tokenarray[i].token != T_FINAL ) {
		asmerr(2008, tokenarray[i].string_ptr );
		return( NULL );
	    }
	    CopyPrototype( dir, (struct dsym *)sym2->target_type );
	    return( sym );
	}
    }
    /* sym->isproc is set inside ParseProc() */
    //sym->isproc = TRUE;

    if ( Parse_Pass == PASS_1 ) {
	if ( ParseProc( dir, i, tokenarray, FALSE, langtype ) == ERROR )
	    return( NULL );
	sym->dll = ModuleInfo.CurrDll;
    } else {
	sym->isdefined = TRUE;
    }
    return( sym );
}

/* externdef [ attr ] symbol:type [, symbol:type,...] */

ret_code ExterndefDirective( int i, struct asm_tok tokenarray[] )
/***************************************************************/
{
    char		*token;
    struct asym		*sym;
    unsigned char	langtype;
    char isnew;
    struct qualified_type ti;


    i++; /* skip EXTERNDEF token */
    do {

	ti.Ofssize = ModuleInfo.Ofssize;

	/* get the symbol language type if present */
	langtype = ModuleInfo.langtype;
	GetLangType( &i, tokenarray, &langtype );

	/* get the symbol name */
	if( tokenarray[i].token != T_ID ) {
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}
	token = tokenarray[i++].string_ptr;

	/* go past the colon */
	if( tokenarray[i].token != T_COLON ) {
	    return( asmerr( 2065, "colon" ) );
	}
	i++;
	sym = SymSearch( token );

	//typetoken = tokenarray[i].string_ptr;
	ti.mem_type = MT_EMPTY;
	ti.size = 0;
	ti.is_ptr = 0;
	ti.is_far = FALSE;
	ti.ptr_memtype = MT_EMPTY;
	ti.symtype = NULL;
	ti.Ofssize = ModuleInfo.Ofssize;

	if ( tokenarray[i].token == T_ID && ( 0 == _stricmp( tokenarray[i].string_ptr, "ABS" ) ) ) {
	    /* v2.07: MT_ABS is obsolete */
	    //ti.mem_type = MT_ABS;
	    i++;
	} else if ( tokenarray[i].token == T_DIRECTIVE && tokenarray[i].tokval == T_PROTO ) {
	    /* dont scan this line further!
	     * CreateProto() will either define a SYM_EXTERNAL or fail
	     * if there's a syntax error or symbol redefinition.
	     */
	    sym = CreateProto( i + 1, tokenarray, token, langtype );
	    return( sym ? NOT_ERROR : ERROR );
	} else if ( tokenarray[i].token != T_FINAL && tokenarray[i].token != T_COMMA ) {
	    if ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
		return( ERROR );
	}

	isnew = FALSE;
	if ( sym == NULL || sym->state == SYM_UNDEFINED ) {
	    sym = CreateExternal( sym, token, TRUE );
	    isnew = TRUE;
	}

	/* new symbol? */

	if ( isnew ) {

	    /* v2.05: added to accept type prototypes */
	    if ( ti.is_ptr == 0 && ti.symtype && ti.symtype->isproc ) {
		CreateProc( sym, NULL, SYM_EXTERNAL );
		CopyPrototype( (struct dsym *)sym, (struct dsym *)ti.symtype );
		ti.mem_type = ti.symtype->mem_type;
		ti.symtype = NULL;
	    }
	    switch ( ti.mem_type ) {
	    //case MT_ABS:
	    case MT_EMPTY:
		/* v2.04: hack no longer necessary */
		//if ( sym->weak == TRUE )
		//    sym->equate = TRUE; /* allow redefinition by EQU, = */
		break;
	    case MT_FAR:
		/* v2.04: don't inherit current segment for FAR externals
		 * if -Zg is set.
		 */
		if ( Options.masm_compat_gencode )
		    break;
		/* fall through */
	    default:
		//SetSymSegOfs( sym );
		sym->segment = &CurrSeg->sym;
	    }
	    sym->Ofssize = ti.Ofssize;

	    if ( ti.is_ptr == 0 && ti.Ofssize != ModuleInfo.Ofssize ) {
		sym->seg_ofssize = ti.Ofssize;
		if ( sym->segment && ((struct dsym *)sym->segment)->e.seginfo->Ofssize != sym->seg_ofssize )
		    sym->segment = NULL;
	    }

	    sym->mem_type = ti.mem_type;
	    sym->is_ptr = ti.is_ptr;
	    sym->isfar = ti.is_far;
	    sym->ptr_memtype = ti.ptr_memtype;
	    if ( ti.mem_type == MT_TYPE )
		sym->type = ti.symtype;
	    else
		sym->target_type = ti.symtype;

	    /* v2.04: only set language if there was no previous definition */
	    SetMangler( sym, langtype, mangle_type );

	} else if ( Parse_Pass == PASS_1 ) {

	    /* v2.05: added to accept type prototypes */
	    if ( ti.is_ptr == 0 && ti.symtype && ti.symtype->isproc ) {
		ti.mem_type = ti.symtype->mem_type;
		ti.symtype = NULL;
	    }
	    /* ensure that the type of the symbol won't change */

	    if ( sym->mem_type != ti.mem_type ) {
		/* if the symbol is already defined (as SYM_INTERNAL), Masm
		 won't display an error. The other way, first externdef and
		 then the definition, will make Masm complain, however */
		asmerr( 8004, sym->name );
	    } else if ( sym->mem_type == MT_TYPE && sym->type != ti.symtype ) {
		struct asym *sym2 = sym;
		/* skip alias types and compare the base types */
		while ( sym2->type )
		    sym2 = sym2->type;
		while ( ti.symtype->type )
		    ti.symtype = ti.symtype->type;
		if ( sym2 != ti.symtype ) {
		    asmerr( 8004, sym->name );
		}
	    }

	    /* v2.04: emit a - weak - warning if language differs.
	     * Masm doesn't warn.
	     */
	    if ( langtype != LANG_NONE && sym->langtype != langtype )
		asmerr( 7000, sym->name );
	}
	sym->isdefined = TRUE;

	if ( sym->state == SYM_INTERNAL && sym->ispublic == FALSE ) {
	    sym->ispublic = TRUE;
	    AddPublicData( sym );
	}

	if ( tokenarray[i].token != T_FINAL )
	    if ( tokenarray[i].token == T_COMMA ) {
		if ( (i + 1) < Token_Count )
		    i++;
	    } else {
		return( asmerr( 2008, tokenarray[i].tokpos ) );
	    }

    } while ( i < Token_Count );

    return( NOT_ERROR );
}

/* PROTO directive.
 * <name> PROTO <params> is semantically identical to:
 * EXTERNDEF <name>: PROTO <params>
 */

ret_code ProtoDirective( int i, struct asm_tok tokenarray[] )
/***********************************************************/
{
    if( Parse_Pass != PASS_1 ) {
	struct asym *sym;
	/* v2.04: set the "defined" flag */
	if ( ( sym = SymSearch( tokenarray[0].string_ptr ) ) && sym->isproc == TRUE )
	    sym->isdefined = TRUE;
	return( NOT_ERROR );
    }
    if( i != 1 ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }

    return( CreateProto( 2, tokenarray, tokenarray[0].string_ptr, ModuleInfo.langtype ) ? NOT_ERROR : ERROR );
}

/* helper for EXTERN directive.
 * also used to create 16-bit floating-point fixups.
 * sym must be NULL or of state SYM_UNDEFINED!
 */
struct asym *MakeExtern( const char *name, unsigned char mem_type, struct asym *vartype, struct asym *sym, uint_8 Ofssize )
/************************************************************************************************************************/
{
    sym = CreateExternal( sym, name, FALSE );
    if ( sym == NULL )
	return( NULL );

    if ( mem_type == MT_EMPTY )
	;
    else if ( Options.masm_compat_gencode == FALSE || mem_type != MT_FAR )
	sym->segment = &CurrSeg->sym;

    sym->isdefined = TRUE;
    sym->mem_type = mem_type;
    sym->seg_ofssize = Ofssize;
    sym->type = vartype;
    return( sym );
}

/* handle optional alternate names in EXTERN directive
 */

static int __fastcall HandleAltname( char *altname, struct asym *sym )
/**************************************************************/
{
    struct asym *symalt;

    if ( altname && sym->state == SYM_EXTERNAL ) {

	symalt = SymSearch( altname );

	/* altname symbol changed? */
	if ( sym->altname && sym->altname != symalt ) {
	    return( asmerr( 2005, sym->name ) );
	}

	if ( Parse_Pass > PASS_1 ) {
	    if ( symalt->state == SYM_UNDEFINED ) {
		asmerr( 2006, altname );
	    } else if (symalt->state != SYM_INTERNAL && symalt->state != SYM_EXTERNAL ) {
		asmerr( 2004, altname );
	    } else {
		if ( symalt->state == SYM_INTERNAL && symalt->ispublic == FALSE )
		    if ( Options.output_format == OFORMAT_COFF
			|| Options.output_format == OFORMAT_ELF
		       ) {
			asmerr( 2217, altname );
		    }
		if ( sym->mem_type != symalt->mem_type )
		    asmerr( 2004, altname );
	    }
	} else {

	    if ( symalt ) {
		if ( symalt->state != SYM_INTERNAL &&
		    symalt->state != SYM_EXTERNAL &&
		    symalt->state != SYM_UNDEFINED ) {
		    return( asmerr( 2004, altname ) );
		}
	    } else {
		symalt = SymCreate( altname );
		sym_add_table( &SymTables[TAB_UNDEF], (struct dsym *)symalt );
	    }
	    /* make sure the alt symbol becomes strong if it is an external
	     * v2.11: don't do this for OMF ( maybe neither for COFF/ELF? )
	     */
	    if ( Options.output_format != OFORMAT_OMF )
		symalt->used = TRUE;
	    /* symbol inserted in the "weak external" queue?
	     * currently needed for OMF only.
	     */
	    if ( sym->altname == NULL ) {
		sym->altname = symalt;
	    }
	}
    }
    return( NOT_ERROR );
}

/* syntax: EXT[E]RN [lang_type] name (altname) :type [, ...] */

int ExternDirective( int i, struct asm_tok tokenarray[] )
/************************************************************/
{
    char		*token;
    char		*altname;
    struct asym		*sym;
    unsigned char	langtype;
    struct qualified_type ti;

    i++; /* skip EXT[E]RN token */
    do {

	altname = NULL;

	/* get the symbol language type if present */
	langtype = ModuleInfo.langtype;
	GetLangType( &i, tokenarray, &langtype );

	/* get the symbol name */
	if( tokenarray[i].token != T_ID ) {
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}
	token = tokenarray[i++].string_ptr;

	/* go past the optional alternative name (weak ext, default resolution) */
	if( tokenarray[i].token == T_OP_BRACKET ) {
	    i++;
	    if ( tokenarray[i].token != T_ID ) {
		return( asmerr(2008, tokenarray[i].string_ptr ) );
	    }
	    altname = tokenarray[i].string_ptr;
	    i++;
	    if( tokenarray[i].token != T_CL_BRACKET ) {
		return( asmerr( 2065, ")" ) );
	    }
	    i++;
	}

	/* go past the colon */
	if( tokenarray[i].token != T_COLON ) {
	    return( asmerr( 2065, ":" ) );
	}
	i++;
	sym = SymSearch( token );

	ti.mem_type = MT_EMPTY;
	ti.size = 0;
	ti.is_ptr = 0;
	ti.is_far = FALSE;
	ti.ptr_memtype = MT_EMPTY;
	ti.symtype = NULL;
	ti.Ofssize = ModuleInfo.Ofssize;

	if ( tokenarray[i].token == T_ID && ( 0 == _stricmp( tokenarray[i].string_ptr, "ABS" ) ) ) {
	    i++;
	} else if ( tokenarray[i].token == T_DIRECTIVE && tokenarray[i].tokval == T_PROTO ) {
	    /* dont scan this line further */
	    /* CreateProto() will define a SYM_EXTERNAL */
	    sym = CreateProto( i + 1, tokenarray, token, langtype );
	    if ( sym == NULL )
		return( ERROR );
	    if ( sym->state == SYM_EXTERNAL ) {
		sym->weak = FALSE;
		return( HandleAltname( altname, sym ) );
	    } else {
		/* unlike EXTERNDEF, EXTERN doesn't allow a PROC for the same name */
		return( asmerr( 2005, sym->name ) );
	    }
	} else if ( tokenarray[i].token != T_FINAL && tokenarray[i].token != T_COMMA ) {
	    if ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
		return( ERROR );
	}

	if( sym == NULL || sym->state == SYM_UNDEFINED ) {
	    if(( sym = MakeExtern(
			(const char *)token,
			(unsigned char)ti.mem_type,
			(struct asym *)(ti.mem_type == MT_TYPE ? ti.symtype : NULL),
			(struct asym *)sym,
			(unsigned char)(ti.is_ptr ? ModuleInfo.Ofssize : ti.Ofssize)
		       )
	     ) == NULL )
		return( ERROR );

	    /* v2.05: added to accept type prototypes */
	    if ( ti.is_ptr == 0 && ti.symtype && ti.symtype->isproc ) {
		CreateProc( sym, NULL, SYM_EXTERNAL );
		sym->weak = FALSE; /* v2.09: reset the weak bit that has been set inside CreateProc() */
		CopyPrototype( (struct dsym *)sym, (struct dsym *)ti.symtype );
		ti.mem_type = ti.symtype->mem_type;
		ti.symtype = NULL;
	    }

	} else {
#if MASM_EXTCOND
	    /* allow internal AND external definitions for equates */
	    if ( sym->state == SYM_INTERNAL && sym->mem_type == MT_EMPTY )
		;
	    else
#endif
	    if ( sym->state != SYM_EXTERNAL ) {
		return( asmerr( 2005, token ) );
	    }
	    /* v2.05: added to accept type prototypes */
	    if ( ti.is_ptr == 0 && ti.symtype && ti.symtype->isproc ) {
		ti.mem_type = ti.symtype->mem_type;
		ti.symtype = NULL;
	    }

	    if( sym->mem_type != ti.mem_type ||
	       sym->is_ptr != ti.is_ptr ||
	       sym->isfar != ti.is_far ||
	       ( sym->is_ptr && sym->ptr_memtype != ti.ptr_memtype ) ||
	       ((sym->mem_type == MT_TYPE) ? sym->type : sym->target_type) != ti.symtype ||
	       ( langtype != LANG_NONE && sym->langtype != LANG_NONE && sym->langtype != langtype )) {
		return( asmerr( 2004, token ) );
	    }
	}

	sym->isdefined = TRUE;
	sym->Ofssize = ti.Ofssize;

	if ( ti.is_ptr == 0 && ti.Ofssize != ModuleInfo.Ofssize ) {
	    sym->seg_ofssize = ti.Ofssize;
	    if ( sym->segment && ((struct dsym *)sym->segment)->e.seginfo->Ofssize != sym->seg_ofssize )
		sym->segment = NULL;
	}

	sym->mem_type = ti.mem_type;
	sym->is_ptr = ti.is_ptr;
	sym->isfar = ti.is_far;
	sym->ptr_memtype = ti.ptr_memtype;
	if ( ti.mem_type == MT_TYPE )
	    sym->type = ti.symtype;
	else
	    sym->target_type = ti.symtype;

	HandleAltname( altname, sym );

	SetMangler( sym, langtype, mangle_type );

	if ( tokenarray[i].token != T_FINAL )
	    if ( tokenarray[i].token == T_COMMA &&  ( (i + 1) < Token_Count ) ) {
		i++;
	    } else {
		return( asmerr(2008, tokenarray[i].string_ptr ) );
	    }
    }  while ( i < Token_Count );

    return( NOT_ERROR );
}

/* helper for COMM directive */

static struct asym *MakeComm( char *name, struct asym *sym, uint_32 size, uint_32 count, bool isfar )
/***************************************************************************************************/
{
    sym = CreateComm( sym, name );
    if( sym == NULL )
	return( NULL );

    sym->total_length = count;
    sym->isfar = isfar;

    /* v2.04: don't set segment if communal is far and -Zg is set */
    if ( Options.masm_compat_gencode == FALSE || isfar == FALSE )
	sym->segment = &CurrSeg->sym;

    MemtypeFromSize( size, &sym->mem_type );

    /* v2.04: warning added ( Masm emits an error ) */
    /* v2.05: code active for 16-bit only */
    if ( ModuleInfo.Ofssize == USE16 )
	if ( ( count * size ) > 0x10000UL )
	    asmerr( 8003, sym->name );

    sym->total_size = count * size;

    return( sym );
}

/* define "communal" items
 * syntax:
 * COMM [langtype] [NEAR|FAR] label:type[:count] [, ... ]
 * the size & count values must NOT be forward references!
 */

int CommDirective( int i, struct asm_tok tokenarray[] )
/**********************************************************/
{
    char	    *token;
    bool	    isfar;
    int		    tmp;
    uint_32	    size;  /* v2.12: changed from 'int' to 'uint_32' */
    uint_32	    count; /* v2.12: changed from 'int' to 'uint_32' */
    struct asym	    *sym;
    struct expr	    opndx;
    unsigned char   langtype;

    i++; /* skip COMM token */
    for( ; i < Token_Count; i++ ) {
	/* get the symbol language type if present */
	langtype = ModuleInfo.langtype;
	GetLangType( &i, tokenarray, &langtype );

	/* get the -optional- distance ( near or far ) */
	isfar = FALSE;
	if ( tokenarray[i].token == T_STYPE )
	    switch ( tokenarray[i].tokval ) {
	    case T_FAR:
	    case T_FAR16:
	    case T_FAR32:
		if ( ModuleInfo.model == MODEL_FLAT ) {
		    asmerr( 2178 );
		} else
		    isfar = TRUE;
		/* no break */
	    case T_NEAR:
	    case T_NEAR16:
	    case T_NEAR32:
		i++;
	    }

	/* v2.08: ensure token is a valid id */
	if( tokenarray[i].token != T_ID ) {
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}
	/* get the symbol name */
	token = tokenarray[i++].string_ptr;

	/* go past the colon */
	if( tokenarray[i].token != T_COLON ) {
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}
	i++;
	/* the evaluator cannot handle a ':' so scan for one first */
	for ( tmp = i; tmp < Token_Count;tmp++ )
	    if ( tokenarray[tmp].token == T_COLON )
		break;
	/* v2.10: expression evaluator isn't to accept forward references */
	if ( EvalOperand( &i, tokenarray, tmp, &opndx, EXPF_NOUNDEF ) == ERROR )
	    return( ERROR );

	/* v2.03: a string constant is accepted by Masm */
	/* v2.11: don't accept NEAR or FAR */
	/* v2.12: check for too large value added */
	if ( opndx.kind != EXPR_CONST )
	    asmerr( 2026 );
	else if ( ( opndx.mem_type & MT_SPECIAL_MASK) == MT_ADDRESS )
	    asmerr( 2104, token );
	else if ( opndx.hvalue != 0 && opndx.hvalue != -1 )
	    EmitConstError( &opndx );
	else if ( opndx.uvalue == 0 )
	    asmerr( 2090 );

	size = opndx.uvalue;

	count = 1;
	if( tokenarray[i].token == T_COLON ) {
	    i++;
	    /* get optional count argument */
	    /* v2.10: expression evaluator isn't to accept forward references */
	    if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
		return( ERROR );

	    /* v2.03: a string constant is acceptable! */
	    /* v2.12: check for too large value added */
	    if ( opndx.kind != EXPR_CONST )
		asmerr( 2026 );
	    else if ( opndx.hvalue != 0 && opndx.hvalue != -1 )
		EmitConstError( &opndx );
	    else if ( opndx.uvalue == 0 )
		asmerr( 2090 );

	    count = opndx.uvalue;
	}

	sym = SymSearch( token );
	if( sym == NULL || sym->state == SYM_UNDEFINED ) {
	    sym = MakeComm( token, sym, size, count, isfar );
	    if ( sym == NULL )
		return( ERROR );
	} else if ( sym->state != SYM_EXTERNAL || sym->iscomm != TRUE ) {
	    return( asmerr( 2005, sym->name ) );
	} else {
	    tmp = sym->total_size / sym->total_length;
	    if( count != sym->total_length || size != tmp ) {
		return( asmerr( 2007, szCOMM, sym->name ) );
	    }
	}
	sym->isdefined = TRUE;
	SetMangler( sym, langtype, mangle_type );

	if ( tokenarray[i].token != T_FINAL && tokenarray[i].token != T_COMMA ) {
	    return( asmerr( 2008, tokenarray[i].tokpos ) );
	}
    }
    return( NOT_ERROR );
}

/* syntax: PUBLIC [lang_type] name [, ...] */

int PublicDirective( int i, struct asm_tok tokenarray[] )
{
    char		*token;
    struct asym		*sym;
    char		skipitem;
    unsigned char	langtype;

    i++; /* skip PUBLIC directive */
    do {

	/* read the optional language type */
	langtype = ModuleInfo.langtype;
	GetLangType( &i, tokenarray, &langtype );

	if ( tokenarray[i].token != T_ID ) {
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}
	/* get the symbol name */
	token = tokenarray[i++].string_ptr;

	/* Add the public name */
	sym = SymSearch( token );
	if ( Parse_Pass == PASS_1 ) {
	    if ( sym == NULL ) {
		if ( sym = SymCreate( token ) ) {
		    sym_add_table( &SymTables[TAB_UNDEF], (struct dsym *)sym );
		} else
		    return( ERROR ); /* name was too long */
	    }
	    skipitem = FALSE;
	} else {
	    if ( sym == NULL || sym->state == SYM_UNDEFINED ) {
		asmerr( 2006, token );
	    }
	}
	if ( sym ) {
	    switch ( sym->state ) {
	    case SYM_UNDEFINED:
		break;
	    case SYM_INTERNAL:
		if ( sym->scoped == TRUE ) {
		    asmerr( 2014, sym->name );
		    skipitem = TRUE;
		}
		break;
	    case SYM_EXTERNAL:
		if ( sym->iscomm == TRUE ) {
		    asmerr( 2014, sym->name );
		    skipitem = TRUE;
		} else if ( sym->weak == FALSE ) {
		    /* for EXTERNs, emit a different error msg */
		    asmerr( 2005, sym->name );
		    skipitem = TRUE;
		}
		break;
	    default:
		asmerr( 2014, sym->name );
		skipitem = TRUE;
	    }
	    if( Parse_Pass == PASS_1 && skipitem == FALSE ) {
		if ( sym->ispublic == FALSE ) {
		    sym->ispublic = TRUE;
		    AddPublicData( sym ); /* put it into the public table */
		}
		SetMangler( sym, langtype, mangle_type );
	    }
	}

	if ( tokenarray[i].token != T_FINAL )
	    if ( tokenarray[i].token == T_COMMA ) {
		if ( (i + 1) < Token_Count )
		    i++;
	    } else {
		return( asmerr(2008, tokenarray[i].tokpos ) );
	    }

    } while ( i < Token_Count );

    return( NOT_ERROR );
}
