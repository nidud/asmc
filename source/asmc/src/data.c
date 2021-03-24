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
* Description:	data definition. handles
*		- directives DB,DW,DD,...
*		- predefined types (BYTE, WORD, DWORD, ...)
*		- arbitrary types
*
****************************************************************************/

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <expreval.h>
#include <input.h>
#include <fixup.h>
#include <listing.h>
#include <segment.h>
#include <types.h>
#include <fastpass.h>
#include <tokenize.h>
#include <macro.h>
#include <omf.h>
#include <atofloat.h>
#include <float.h>

int segm_override( const struct expr *, struct code_info * );
extern struct asym *SegOverride;
extern const char szNull[];

static int data_item( int *, struct asm_tok[], struct asym *, uint_32, const struct asym *, uint_32, bool inside_struct, bool, bool, int );

#define OutputDataBytes( x, y ) OutputBytes( x, y, NULL )

/* initialize an array inside a structure
 * if there are no brackets, the next comma, '>' or '}' will terminate
 *
 * valid initialization are:
 * - an expression, might contain DUP or a string enclosed in quotes.
 * - a literal enclosed in <> or {} which then is supposed to contain
 *   single items.
 */
static int InitializeArray( const struct sfield *f, int *pi, struct asm_tok tokenarray[] )
/*********************************************************************************************/
{
    uint_32 oldofs;
    uint_32 no_of_bytes;
    int	 i = *pi;
    int	 j;
    int	 lvl;
    int old_tokencount;
    char bArray;
    ret_code rc;

    oldofs = GetCurrOffset();
    no_of_bytes = SizeFromMemtype( f->sym.mem_type, USE_EMPTY, f->sym.type );

    /* If current item is a literal enclosed in <> or {}, just use this
     * item. Else, use all items until a comma or EOL is found.
     */

    if ( tokenarray[i].token != T_STRING ||
	 ( tokenarray[i].string_delim != '<' &&
	   tokenarray[i].string_delim != '{' )) {

	/* scan for comma or final. Ignore commas inside DUP argument */
	for( j = i, lvl = 0, bArray = FALSE; tokenarray[j].token != T_FINAL; j++ ) {
	    if ( tokenarray[j].token == T_OP_BRACKET )
		lvl++;
	    else if ( tokenarray[j].token == T_CL_BRACKET )
		lvl--;
	    else if ( lvl == 0 && tokenarray[j].token == T_COMMA )
		break;
	    else if ( tokenarray[j].token == T_RES_ID && tokenarray[j].tokval == T_DUP )
		bArray = TRUE;
	    else if ( no_of_bytes == 1 && tokenarray[j].token == T_STRING &&
		     ( tokenarray[j].string_delim == '"' || tokenarray[j].string_delim == '\'' ))
		bArray = TRUE;
	}
	*pi = j;

	if ( bArray == FALSE ) {
	    return( asmerr( 2181, tokenarray[i].tokpos ) );
	}

	lvl = tokenarray[j].tokpos - tokenarray[i].tokpos;

	/* v2.07: accept an "empty" quoted string as array initializer for byte arrays */
	if ( lvl == 2 &&
	    f->sym.total_size == f->sym.total_length &&
	    ( tokenarray[i].string_delim == '"' || tokenarray[i].string_delim == '\'' ) )
	    rc = NOT_ERROR;
	else {
	    lvl = i; /* i must remain the start index */
	    rc = data_item( &lvl, tokenarray, NULL, no_of_bytes, f->sym.type, 1, FALSE, f->sym.mem_type & MT_FLOAT, FALSE, j );
	}

    } else {

	/* initializer is a literal */
	(*pi)++;
	old_tokencount = Token_Count;
	j = Token_Count + 1;
	/* if the string is empty, use the default initializer */
	if ( tokenarray[i].stringlen == 0 ) {
	    Token_Count = Tokenize( (char *)f->ivalue, j, tokenarray, TOK_RESCAN );
	} else {
	    Token_Count = Tokenize( tokenarray[i].string_ptr, j, tokenarray, TOK_RESCAN );
	}
	rc = data_item( &j, tokenarray, NULL, no_of_bytes, f->sym.type, 1, FALSE, f->sym.mem_type & MT_FLOAT, FALSE, Token_Count );
	Token_Count = old_tokencount;
    }

    /* get size of array items */
    no_of_bytes = GetCurrOffset() - oldofs ;

    if ( no_of_bytes > f->sym.total_size ) {
	asmerr( 2036, tokenarray[i].tokpos );
	rc = ERROR;
    } else if ( no_of_bytes < f->sym.total_size ) {
	char filler = NULLC;
	if ( CurrSeg && CurrSeg->e.seginfo->segtype == SEGTYPE_BSS )
	    SetCurrOffset( CurrSeg, f->sym.total_size - no_of_bytes, TRUE, TRUE );
	else {
	    /* v2.07: if element size is 1 and a string is used as initial value,
	     * pad array with spaces!
	     */
	    if ( f->sym.total_size == f->sym.total_length &&
		( f->ivalue[0] == '"' || f->ivalue[0] == '\'' ) )
		filler = ' ';
	    FillDataBytes( filler, f->sym.total_size - no_of_bytes );
	}
    }

    return( rc );
}

/* initialize a STRUCT/UNION/RECORD data item
 * index:    index of initializer literal
 * symtype:  type of data item
 * embedded: is != NULL if proc is called recursively

 * up to v2.08, this proc did emit ASM lines with simple types
 * to actually "fill" the structure.
 * since v2.09, it calls data_item() directly.

 * Since this function may be reentered, it's necessary to save/restore
 * global variable Token_Count.
 */
static int InitStructuredVar( int index, struct asm_tok tokenarray[], const struct dsym *symtype, struct asym *embedded )
{
    struct sfield   *f;
    int_32	    nextofs;
    int		    i;
    int		    old_tokencount = Token_Count;
    char	    *old_stringbufferend = StringBufferEnd;
    int		    lvl;
    uint_64	    dwRecInit;
    bool	    is_record_set;
    struct expr	    opndx;


    if ( tokenarray[index].token == T_STRING ) {
	/* v2.08: no special handling of {}-literals anymore */
	if ( tokenarray[index].string_delim != '<' &&
	    tokenarray[index].string_delim != '{' ) {
	    return( asmerr( 2045 ) );
	}
	i = Token_Count + 1;
	//strcpy( line, tokenarray[index].string_ptr );
	Token_Count = Tokenize( tokenarray[index].string_ptr, i, tokenarray, TOK_RESCAN );
	/* once Token_Count has been modified, don't exit without
	 * restoring this value!
	 */
	index++;

    } else if ( embedded &&
		( tokenarray[index].token == T_COMMA ||
		 tokenarray[index].token == T_FINAL)) {
	i = Token_Count;
    } else {
	return( asmerr( 2181, embedded ? embedded->name : "" ) );
    }
    if ( symtype->sym.typekind == TYPE_RECORD ) {
	dwRecInit = 0;
	is_record_set = FALSE;
    }

    /* scan the STRUCT/UNION/RECORD's members */
    for( f = symtype->e.structinfo->head; f != NULL; f = f->next ) {

	/* is it a RECORD field? */
	if ( f->sym.mem_type == MT_BITS ) {
	    if ( tokenarray[i].token == T_COMMA || tokenarray[i].token == T_FINAL ) {
		if ( f->ivalue[0] ) {
		    int j = Token_Count + 1;
		    int max_item = Tokenize( f->ivalue, j, tokenarray, TOK_RESCAN );
		    EvalOperand( &j, tokenarray, max_item, &opndx, 0 );
		    is_record_set = TRUE;
		} else {
		    opndx.value = 0;
		    opndx.kind = EXPR_CONST;
		    opndx.quoted_string = NULL;
		}
	    } else {
		EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 );
		is_record_set = TRUE;
	    }
	    if ( opndx.kind != EXPR_CONST || opndx.quoted_string != NULL )
		asmerr( 2026 );

	    /* fixme: max bits in 64-bit is 64 - see MAXRECBITS! */
	    if ( f->sym.total_size < 32 ) {
		uint_32 dwMax = (1 << f->sym.total_size);
		if ( opndx.value >= dwMax )
		    asmerr( 2071, f->sym.name );
	    }
	    dwRecInit |= opndx.llvalue << f->sym.offset;
	} else if ( f->ivalue[0] == NULLC ) {  /* embedded struct? */

	    InitStructuredVar( i, tokenarray, (struct dsym *)f->sym.type, &f->sym );
	    if ( tokenarray[i].token == T_STRING )
		i++;

	} else if ( f->sym.isarray &&
		    tokenarray[i].token != T_FINAL &&
		    tokenarray[i].token != T_COMMA ) {
	    if ( ERROR == InitializeArray( f, &i, tokenarray ) )
		break;

	} else if ( f->sym.total_size == f->sym.total_length &&
		   tokenarray[i].token == T_STRING &&
		   tokenarray[i].stringlen > 1 &&
		   ( tokenarray[i].string_delim == '"' ||
		    tokenarray[i].string_delim == '\'' ) ) {
	    /* v2.07: it's a byte type, but no array, string initializer must have true length 1 */
	    asmerr( 2041 );
	    i++;
	} else {
	    uint_32 no_of_bytes = SizeFromMemtype( f->sym.mem_type, USE_EMPTY, f->sym.type );

	    if ( tokenarray[i].token == T_FINAL || tokenarray[i].token == T_COMMA ) {
		int tc = Token_Count;
		int j = Token_Count+1;
		Token_Count = Tokenize( f->ivalue, j, tokenarray, TOK_RESCAN );
		data_item( &j, tokenarray, NULL, no_of_bytes, f->sym.type, 1, FALSE, f->sym.mem_type & MT_FLOAT, FALSE, Token_Count );
		Token_Count = tc;
	    } else {
		char c;
		int j = i;
		/* ignore commas enclosed in () ( might occur inside DUP argument! ).
		 */
		for ( lvl = 0, c = 0; tokenarray[i].token != T_FINAL; i++ ) {
		    if ( tokenarray[i].token == T_OP_BRACKET )
			lvl++;
		    else if ( tokenarray[i].token == T_CL_BRACKET )
			lvl--;
		    else if ( lvl == 0 && tokenarray[i].token == T_COMMA )
			break;
		    else if ( tokenarray[i].token == T_RES_ID && tokenarray[i].tokval == T_DUP )
			c++; /* v2.08: check added */
		}
		if ( c ) {
		    asmerr( 2181, tokenarray[j].tokpos );
		} else
		    if ( ERROR == data_item( &j, tokenarray, NULL, no_of_bytes, f->sym.type, 1, FALSE, f->sym.mem_type & MT_FLOAT, FALSE, i ) ) {
			asmerr( 2104, f->sym.name );
		    }
	    }
	}
	/* Add padding bytes if necessary (never inside RECORDS!).
	 * f->next == NULL : it's the last field of the struct/union/record
	 */
	if ( symtype->sym.typekind != TYPE_RECORD ) {
	    if ( f->next == NULL || symtype->sym.typekind == TYPE_UNION )
		nextofs = symtype->sym.total_size;
	    else
		nextofs = f->next->sym.offset;

	    if ( f->sym.offset + f->sym.total_size < nextofs ) {
		SetCurrOffset( CurrSeg, nextofs - (f->sym.offset + f->sym.total_size), TRUE, TRUE );
	    }
	}
	/* for a union, just the first field is initialized */
	if ( symtype->sym.typekind == TYPE_UNION )
	    break;

	if ( f->next != NULL ) {

	    if ( tokenarray[i].token != T_FINAL )
		if ( tokenarray[i].token == T_COMMA )
		    i++;
		else {
		    asmerr(2008, tokenarray[i].tokpos );
		    while ( tokenarray[i].token != T_FINAL && tokenarray[i].token != T_COMMA )
			i++;
		}
	}
    }  /* end for */

    if ( symtype->sym.typekind == TYPE_RECORD ) {
	int no_of_bytes;
	switch ( symtype->sym.mem_type ) {
	case MT_BYTE: no_of_bytes = 1; break;
	case MT_WORD: no_of_bytes = 2; break;
	case MT_QWORD: no_of_bytes = 8; break;
	default: no_of_bytes = 4;
	}
	if ( is_record_set )
	    OutputDataBytes( (uint_8 *)&dwRecInit, no_of_bytes );
	else
	    SetCurrOffset( CurrSeg, no_of_bytes, TRUE, TRUE );
    }

    if ( tokenarray[i].token != T_FINAL ) {
	asmerr( 2036, tokenarray[i].tokpos );
    }

    /* restore token status */
    Token_Count = old_tokencount;
    StringBufferEnd = old_stringbufferend;
    return( NOT_ERROR );
}

/*
 * convert a string into little endian format - ( LSB 1st, LSW 1st ... etc ).
 * <len> is the TYPE, may be 2,4,6,8,10?,16
 */
static char *little_endian( const char *src, unsigned len )
{
    /* v2.06: input and output buffer must be different! */
    char *dst = StringBufferEnd;

    for( ; len > 1; dst++, src++, len-- ) {
	len--;
	*dst = *(src + len);
	*(dst + len) = *src;
    }
    if ( len )
	*dst = *src;

    return( StringBufferEnd );
}

static void output_float( struct expr *opnd, unsigned size )
{
    /* v2.07: buffer extended to max size of a data item (=32).
     * test case: XMMWORD REAL10 ptr 1.0
     */
    int i;
    char buffer[32];

    if ( opnd->mem_type != MT_REAL16 ) {

	memset( buffer, 0, sizeof( buffer ) );
	i = SizeFromMemtype( opnd->mem_type, USE_EMPTY, NULL );
	if ( i > size )
	    asmerr( 2156 );
	else
	    quad_resize( opnd, i );
	OutputDataBytes( opnd->chararray, size );

    } else {

	 if ( size != 16 )
	    quad_resize( opnd, size );
	OutputDataBytes( opnd->chararray, size );
    }
    return;
}

/*
 * initialize a data item or struct member;
 * - start_pos: contains tokenarray[] index [in/out]
 * - tokenarray[]: token array
 *
 * - sym:
 *   for data item:	label (may be NULL)
 *   for struct member: field/member (is never NULL)
 *
 * - no_of_bytes: size of item in bytes
 * - type_sym:
 *   for data item:	if != NULL, item is a STRUCT/UNION/RECORD.
 *   for struct member: if != NULL, item is a STRUCT/UNION/RECORD/TYPEDEF.
 *
 * - dup: array size if called by DUP operator, otherwise 1
 * - inside_struct: TRUE=inside a STRUCT declaration
 * - is_float: TRUE=item is float
 * - first: TRUE=first item in a line
 *
 * the symbol will have its 'isarray' flag set if any of the following is true:
 * 1. at least 2 items separated by a comma are used for initialization
 * 2. the DUP operator occures
 * 3. item size is 1 and a quoted string with len > 1 is used as initializer
 */

#if !defined(__UNIX__)
int WINAPI MultiByteToWideChar(int, int, char *, int, unsigned short *, int);
#endif

static int data_item( int *start_pos, struct asm_tok tokenarray[], struct asym *sym, uint_32 no_of_bytes, const struct asym *type_sym, uint_32 dup, bool inside_struct, bool is_float, bool first, int end )

{
    int			i;
    int			string_len;
    uint_32		total = 0;
    bool		initwarn = FALSE;
    uint_8		*pchar;
    char		tmp;
    enum fixup_types	fixup_type;
    struct fixup	*fixup;
    struct expr		opndx;

    for ( ; dup; dup-- ) {
    i = *start_pos;
next_item:  /* <--- continue scan if a comma has been detected */
    /* since v1.94, the expression evaluator won't handle strings
     * enclosed in <> or {}. That is, in previous versions syntax
     * "mov eax,<1>" was accepted, now it's rejected.
     */
    if ( tokenarray[i].token == T_STRING && ( tokenarray[i].string_delim == '<'	 || tokenarray[i].string_delim == '{' ) ) {
	if( type_sym ) {

	    /* it's either a real data item - then inside_struct is FALSE -
	     * or a structure FIELD of arbitrary type.
	     *
	     * v2.10: regression in v2.09: alias types weren't skipped for InitStructuredVar()
	     */
	    while ( type_sym->type ) type_sym = type_sym->type;
	    if( inside_struct == FALSE ) {
		if ( InitStructuredVar( i, tokenarray, (struct dsym *)type_sym, NULL ) == ERROR )
		    return( ERROR );
	    } else {
		/* v2.09: emit a warning if a TYPEDEF member is a simple type,
		 * but is initialized with a literal.
		 * Note: Masm complains about such literals only if the struct is instanced OR -Fl is set.
		 * fixme: the best solution is to always set type_sym to NULL if
		 * the type is a TYPEDEF. if the item is a struct member, then
		 * sym is ALWAYS != NULL and the symbol's type can be gained from there.
		 * v2.10: aliases are now already skipped here ( see above ).
		 */
		if( type_sym->typekind == TYPE_TYPEDEF && Parse_Pass == PASS_1 )
		    asmerr( 8001, tokenarray[i].tokpos );
	    }

	    total++;
	    i++;
	    goto item_done;
	}
    }

    if ( tokenarray[i].token == T_QUESTION_MARK )
	opndx.kind = EXPR_EMPTY;
    else
	if ( EvalOperand( &i, tokenarray, end, &opndx, 0 ) == ERROR )
	    return( ERROR );

    /* handle DUP operator */

    if ( tokenarray[i].token == T_RES_ID && tokenarray[i].tokval == T_DUP ) {
	if ( opndx.kind != EXPR_CONST ) {
	    if ( opndx.sym && opndx.sym->state == SYM_UNDEFINED )
		asmerr( 2006, opndx.sym->name );
	    else
		asmerr( 2026 );
	    return( ERROR );
	}
	/* max dup is 0x7fffffff */
	if ( opndx.value < 0 ) {
	    return( asmerr( 2092 ) );
	}
	i++;
	if( tokenarray[i].token != T_OP_BRACKET ) {
	    return( asmerr( 2065, "(" ) );
	}
	i++;

	if ( sym )
	    sym->isarray = TRUE;

	if ( opndx.value == 0 ) {
	    int level = 1;
	    for ( ; tokenarray[i].token != T_FINAL; i++ ) {
		if ( tokenarray[i].token == T_OP_BRACKET )
		    level++;
		else if ( tokenarray[i].token == T_CL_BRACKET )
		    level--;
		if ( level == 0 )
		    break;
	    }
	} else {
	    if ( data_item( &i, tokenarray, sym, no_of_bytes, type_sym, opndx.uvalue, inside_struct, is_float, first, end ) == ERROR ) {
		return( ERROR );
	    }
	}
	if( tokenarray[i].token != T_CL_BRACKET ) {
	    return( asmerr( 2065, ")" ) );
	}
	/* v2.09: SIZE and LENGTH actually don't return values for "first initializer, but
	 * the "first dimension" values
	 * v2.11: fixme: if the first dimension is 0 ( opndx.value == 0),
	 * Masm ignores the expression - may be a Masm bug!
	 */
	if ( sym && first && Parse_Pass == PASS_1 ) {
	    sym->first_size = opndx.value * no_of_bytes;
	    sym->first_length = opndx.value;
	    first = FALSE;
	}

	i++;
	goto item_done;
    }
    /* a STRUCT/UNION/RECORD data item needs a literal as initializer */
    if( type_sym ) {
	const struct asym *tmp = type_sym;
	while ( tmp->type ) tmp = tmp->type;
	if ( tmp->typekind != TYPE_TYPEDEF ) {
	    return( asmerr( 2179, type_sym->name ) );
	}
    }

    /* handle '?' */
    if ( opndx.kind == EXPR_EMPTY && tokenarray[i].token == T_QUESTION_MARK ) {
	opndx.uvalue = no_of_bytes;
	/* tiny optimization for uninitialized arrays */
	if ( tokenarray[i+1].token != T_COMMA && i == *start_pos ) {
	    opndx.uvalue *= dup;
	    total += dup;
	    dup = 1; /* force loop exit */
	} else {
	    total++;
	}
	if( !inside_struct ) {
	    SetCurrOffset( CurrSeg, opndx.uvalue, TRUE, TRUE );
	}
	i++;
	goto item_done;
    }

    /* warn about initialized data in BSS/AT segments */
    if ( Parse_Pass == PASS_2 &&
	inside_struct == FALSE	&&
	(CurrSeg->e.seginfo->segtype == SEGTYPE_BSS ||
	 CurrSeg->e.seginfo->segtype == SEGTYPE_ABS) &&
	initwarn == FALSE ) {
	asmerr( 8006, (CurrSeg->e.seginfo->segtype == SEGTYPE_BSS) ? "BSS" : "AT" );
	initwarn = TRUE;
    };

    switch( opndx.kind ) {
    case EXPR_EMPTY:
	if ( tokenarray[i].token != T_FINAL )
	    asmerr(2008, tokenarray[i].tokpos );
	else
	    asmerr( 2008, "" );
	return( ERROR );
    case EXPR_FLOAT:
	if (!inside_struct)
	    output_float( &opndx, no_of_bytes );
	total++;
	break;
    case EXPR_CONST:
	if ( is_float ) {
	    return( asmerr( 2187 ) );
	}

	/* a string returned by the evaluator (enclosed in quotes!)? */

	if ( opndx.quoted_string ) {
	    pchar = (uint_8 *)opndx.quoted_string->string_ptr + 1;
	    string_len = opndx.quoted_string->stringlen; /* this is the length without quotes */

	    /* v2.07: check for empty string for ALL types */
	    if ( string_len == 0 ) {
		if ( inside_struct ) {
		    /* when the struct is declared, it's no error -
		     * but won't be accepted when the struct is instanced.
		     * v2.07: don't modify string_len! Instead
		     * mark field as array!
		     */
		    sym->isarray = TRUE;
		} else {
		    return( asmerr( 2047 ) ); /* MASM doesn't like "" */
		}
	    }
	    /* a string is only regarded as an array if item size is 1 */
	    /* else it is regarded as ONE item */
	    if( no_of_bytes != 1 ) {
		if( string_len > no_of_bytes ) {
		    /* v2.22 - unicode */
		    /* v2.23 - use L"Unicode" */
		    if ( inside_struct ||
		      !( ( ModuleInfo.strict_masm_compat == 0 ) &&
			 ( ModuleInfo.xflag & ( OPT_WSTRING | OPT_LSTRING ) ) &&
			 no_of_bytes == 2) )
			return( asmerr( 2071 ) );
		}
	    }

	    if( sym && Parse_Pass == PASS_1 && string_len > 0 ) {
		total++;
		if ( no_of_bytes == 1 && string_len > 1 ) {
		    total += ( string_len - 1 );
		    sym->isarray = TRUE; /* v2.07: added */
		    if ( first ) {
			sym->first_length = 1;
			sym->first_size = 1;
			first = FALSE; /* avoid to touch first_xxx fields below */
		    }
		}
		else if ( ( ModuleInfo.strict_masm_compat == 0 )
			&& (ModuleInfo.xflag & ( OPT_WSTRING | OPT_LSTRING ))
			&& no_of_bytes == 2 && string_len > 1 ) {
		    total += ( string_len - 1 );
		    sym->isarray = TRUE; /* v2.07: added */
		    if ( first ) {
			sym->first_length = 1;
			sym->first_size = 2;
			first = FALSE; /* avoid to touch first_xxx fields below */
		    }
		}
	    }

	    if( !inside_struct ) {
		/* anything bigger than a byte must be stored in little-endian
		 * format -- LSB first */
		/* v2.22 - unicode */
		/* v2.23 - use L"Unicode" */
		if ( ( ModuleInfo.strict_masm_compat == 0 ) &&
		     ( ModuleInfo.xflag & ( OPT_WSTRING | OPT_LSTRING ) ) &&
		     string_len > 1 &&
		     no_of_bytes == 2 ) {

			unsigned short *w;
			uint_8 *p = NULL;
			int q = string_len;
#if !defined(__UNIX__)
			if ((w = malloc(string_len*2)) != NULL) {

			    /* v2.24 - Unicode CodePage */
			    if ( (q = MultiByteToWideChar(ModuleInfo.codepage, 0,
				  pchar, string_len, w, string_len)) != 0 ) {

				p = (uint_8 *)w;
				while ( q-- ) {
				    OutputBytes( p++, 1, NULL );
				    OutputBytes( p++, 1, NULL );
				}
			    }
			    free(w);
			}
#endif
			if (p == NULL) {
			    p = pchar;
			    while ( q-- ) {

				OutputBytes( p++, 1, NULL );
				FillDataBytes( 0, 1 );
			    }
			}
		} else {
		    if ( string_len > 1 && no_of_bytes > 1 )
			pchar = (uint_8 *)little_endian( (const char *)pchar, string_len );
		    OutputDataBytes( pchar, string_len );
		}
		if ( no_of_bytes > string_len )
		    FillDataBytes( 0, no_of_bytes - string_len );
	    }
	} else {
	    /* it's NOT a string */
	    if( !inside_struct ) {
		/* the evaluator cannot handle types with size > 16.
		 * so if a (simple) type is larger ( YMMWORD? ),
		 * clear anything which is above.
		 */
		if ( no_of_bytes > 16 ) {
		    OutputDataBytes( opndx.chararray, 16 );
		    tmp = ( opndx.chararray[15] < 0x80 ? 0 : 0xFF );
		    FillDataBytes( tmp, no_of_bytes - 16 );
		} else {
		    if ( no_of_bytes > sizeof( int_64 ) ) {
			if ( opndx.negative && opndx.value64 < 0 && opndx.hlvalue == 0 )
			    opndx.hlvalue = -1;
		    }
		    OutputDataBytes( opndx.chararray, no_of_bytes );
		    /* check that there's no significant data left
		     * which hasn't been emitted.
		     */
		    if ( no_of_bytes <= sizeof( int_64 ) ) {
			tmp = ( opndx.chararray[7] < 0x80 ? 0 : 0xFF );
			memset( opndx.chararray, tmp, no_of_bytes );
			if ( opndx.llvalue != 0 && opndx.llvalue != -1 ) {
			    return( asmerr( 2071, opndx.sym ? opndx.sym->name : "" ) );
			}
		    } else if ( no_of_bytes == 10 ) {
			if ( opndx.hlvalue > 0xffff && opndx.hlvalue < -0xffff ) {
			    return( asmerr( 2071, opndx.sym ? opndx.sym->name : "" ) );
			}
		    }
		}
	    }
	    total++;
	}
	break;
    case EXPR_ADDR:
	/* since a fixup will be created, 8 bytes is max.
	 * there's no way to define an initialized tbyte "far64" address,
	 * because there's no fixup available for the selector part.
	 */
	if ( no_of_bytes > sizeof(uint_64) ) {
	    asmerr( 2104, sym ? sym->name : "" );
	    break;
	}
	/* indirect addressing (incl. stack variables) is invalid */
	if ( opndx.indirect == TRUE ) {
	    asmerr( 2032 );
	    break;
	}
	if ( ModuleInfo.Ofssize != USE64 )
	    if ( opndx.hvalue && ( opndx.hvalue != -1 || opndx.value >= 0 ) ) {
		return( EmitConstError( &opndx ) );
	    }

	if ( is_float ) {
	    asmerr( 2187 );
	    break;
	}

	total++;
	/* for STRUCT fields, don't emit anything! */
	if ( inside_struct ) {
	    break;
	}

	/* determine what type of fixup is to be created */

	switch ( opndx.inst ) {
	case T_SEG:
	    if ( no_of_bytes < 2 ) {
		asmerr( 2071 );
	    }
	    fixup_type = FIX_SEG;
	    break;
	case T_OFFSET:
	    switch ( no_of_bytes ) {
	    case 1:
		/* forward reference? */
		if ( Parse_Pass == PASS_1 && opndx.sym && opndx.sym->state == SYM_UNDEFINED ) {
		    fixup_type = FIX_VOID; /* v2.10: was regression in v2.09 */
		} else {
		    asmerr( 2071 );
		    fixup_type = FIX_OFF8;
		}
		break;
	    case 2:
		fixup_type = FIX_OFF16;
		break;
	    case 8:
		if ( ModuleInfo.Ofssize == USE64 ) {
		    fixup_type = FIX_OFF64;
		    break;
		}
	    default:
		if ( opndx.sym && ( GetSymOfssize(opndx.sym) == USE16 ) )
		    fixup_type = FIX_OFF16;
		else
		    fixup_type = FIX_OFF32;
		break;
	    }
	    break;
	case T_IMAGEREL:
	    if ( no_of_bytes < sizeof(uint_32) ) {
		asmerr( 2071 );
	    }
	    fixup_type = FIX_OFF32_IMGREL;
	    break;
	case T_SECTIONREL:
	    if ( no_of_bytes < sizeof(uint_32) ) {
		asmerr( 2071 );
	    }
	    fixup_type = FIX_OFF32_SECREL;
	    break;
	case T_DOT_LOW:
	    fixup_type = FIX_OFF8; /* OMF, BIN + GNU-ELF only */
	    break;
	case T_DOT_HIGH:
	    fixup_type = FIX_HIBYTE; /* OMF only */
	    break;
	case T_LOWWORD:
	    fixup_type = FIX_OFF16;
	    if ( no_of_bytes < 2 ) {
		asmerr( 2071 );
		break;
	    }
	    break;
	case T_HIGH32:
	    /* no break */
	case T_HIGHWORD:
	    fixup_type = FIX_VOID;
	    asmerr( 2026 );
	    break;
	case T_LOW32:
	    fixup_type = FIX_OFF32;
	    if ( no_of_bytes < 4 ) {
		asmerr( 2071 );
		break;
	    }
	    break;
	default:
	    /* size < 2 can work with T_LOW|T_HIGH operator only */
	    if ( no_of_bytes < 2 ) {
		/* forward reference? */
		if ( Parse_Pass == PASS_1 && opndx.sym && opndx.sym->state == SYM_UNDEFINED )
		    ;
		else {
		    if ( opndx.sym && opndx.sym->state == SYM_EXTERNAL && opndx.is_abs == TRUE ) {
		    } else {
			asmerr( 2071 );
		    }
		    fixup_type = FIX_OFF8;
		    break;
		}
	    }
	    /* if the symbol references a segment or group,
	     then generate a segment fixup.
	     */
	    if ( opndx.sym && (opndx.sym->state == SYM_SEG || opndx.sym->state == SYM_GRP ) ) {
		fixup_type = FIX_SEG;
		break;
	    }

	    switch ( no_of_bytes ) {
	    case 2:
		/* accept "near16" override, else complain
		 * if symbol's offset is 32bit */
		if ( opndx.explicit == TRUE ) {
		    if ( SizeFromMemtype( opndx.mem_type, opndx.Ofssize, opndx.type ) > no_of_bytes ) {
			asmerr( 2071, opndx.sym ? opndx.sym->name : "" );
		    };
		} else if ( opndx.sym && opndx.sym->state == SYM_EXTERNAL && opndx.is_abs == TRUE ) {
		} else if ( opndx.sym &&
			   opndx.sym->state != SYM_UNDEFINED &&
			   ( GetSymOfssize(opndx.sym) > USE16 ) ) {
		    asmerr( 2071, opndx.sym ? opndx.sym->name : "" );
		}
		fixup_type = FIX_OFF16;
		break;
	    case 4:
		/* masm generates:
		 * off32 if curr segment is 32bit,
		 * ptr16 if curr segment is 16bit,
		 * and ignores type overrides.
		 * if it's a NEAR external, size is 16, and
		 * format isn't OMF, error 'symbol type conflict'
		 * is displayed
		 */
		if ( opndx.explicit == TRUE ) {
		    if ( opndx.mem_type == MT_FAR ) {
			if ( opndx.Ofssize != USE_EMPTY && opndx.Ofssize != USE16 ) {
			    asmerr( 2071, opndx.sym ? opndx.sym->name : "" );
			}
			fixup_type = FIX_PTR16;
		    } else if ( opndx.mem_type == MT_NEAR ) {
			if ( opndx.Ofssize == USE16 )
			    fixup_type = FIX_OFF16;
			else if ( opndx.sym && ( GetSymOfssize( opndx.sym ) == USE16 ) )
			    fixup_type = FIX_OFF16;
			else
			    fixup_type = FIX_OFF32;
		    }
		} else {
		    /* what's done if code size is 16 is Masm-compatible.
		     * It's not very smart, however.
		     * A better strategy is to choose fixup type depending
		     * on the symbol's offset size.
		     */
		    if ( ModuleInfo.Ofssize == USE16 )
			if ( opndx.mem_type == MT_NEAR &&
			    ( Options.output_format == OFORMAT_COFF
			     || Options.output_format == OFORMAT_ELF
			    )) {
			    fixup_type = FIX_OFF16;
			    asmerr( 2004, sym->name );
			} else
			    fixup_type = FIX_PTR16;
		    else
			fixup_type = FIX_OFF32;
		}
		break;
	    case 6:
		/* Masm generates a PTR32 fixup in OMF!
		 * and a DIR32 fixup in COFF.
		 */
		/* COFF/ELF has no far fixups */
		if ( Options.output_format == OFORMAT_COFF
		    || Options.output_format == OFORMAT_ELF
		   ) {
		    fixup_type = FIX_OFF32;
		} else
		    fixup_type = FIX_PTR32;
		break;
	    default:
		/* Masm generates
		 * off32 if curr segment is 32bit
		 * ptr16 if curr segment is 16bit
		 * JWasm additionally accepts a FAR32 PTR override
		 * and generates a ptr32 fixup then */
		if ( opndx.explicit == TRUE && opndx.mem_type == MT_FAR && opndx.Ofssize == USE32 )
		    fixup_type = FIX_PTR32;
		else if( ModuleInfo.Ofssize == USE32 )
		    fixup_type = FIX_OFF32;
		else if( ModuleInfo.Ofssize == USE64 )
		    fixup_type = FIX_OFF64;
		else
		    fixup_type = FIX_PTR16;
	    }
	    break;
	} /* end switch ( opndx.instr ) */

	/* v2.07: fixup type check moved here */
	if ( ( 1 << fixup_type ) & ModuleInfo.fmtopt->invalid_fixup_type ) {
	    return( asmerr( 3001,
		    ModuleInfo.fmtopt->formatname,
		    opndx.sym ? opndx.sym->name : szNull ) );
	}
	fixup = NULL;
	if ( write_to_file ) {
	    /* there might be a segment override:
	     * a segment, a group or a segment register.
	     * Init var SegOverride, it's used inside set_frame()
	     */
	    SegOverride = NULL;
	    segm_override( &opndx, NULL );

	    /* set global vars Frame and Frame_Datum */
	    /* opndx.sym may be NULL, then SegOverride is set. */
	    if ( ModuleInfo.offsettype == OT_SEGMENT &&
		( opndx.inst == T_OFFSET || opndx.inst == T_SEG ))
		set_frame2( opndx.sym );
	    else
		set_frame( opndx.sym );
	    /* uses Frame and Frame_Datum  */
	    fixup = CreateFixup( opndx.sym, fixup_type, OPTJ_NONE );
	}
	OutputBytes( (unsigned char *)&opndx.value, no_of_bytes, fixup );
	break;
    case EXPR_REG:
	asmerr( 2032 );
	break;
    default: /* unknown opndx.kind, shouldn't happen */
	return( asmerr( 2008, "" ) );
    } /* end switch (opndx.kind) */
item_done:
    if( sym && first && Parse_Pass == PASS_1 ) {
	sym->first_length = total;
	sym->first_size = total * no_of_bytes;
    }
    if( i < end && tokenarray[i].token == T_COMMA ) {
	i++;
	if ( tokenarray[i].token != T_FINAL &&
	    tokenarray[i].token != T_CL_BRACKET ) {
	    first = FALSE;
	    if ( sym )
		sym->isarray = TRUE;
	    goto next_item;
	}
    }

    } /* end for */

    if( sym && Parse_Pass == PASS_1 ) {
	sym->total_length += total;
	sym->total_size += total * no_of_bytes;
    }

    *start_pos = i;
    return( NOT_ERROR );
}

static int checktypes( const struct asym *sym, unsigned char mem_type, const struct asym *type_sym )
/******************************************************************************************************/
{
    /* for EXTERNDEF, check type changes */
    if ( sym->mem_type != MT_EMPTY ) {
	unsigned char mem_type2 = sym->mem_type;
	const struct asym *tmp;
	/* skip alias types */
	tmp = type_sym;
	while ( mem_type == MT_TYPE ) {
	    mem_type = tmp->mem_type;
	    tmp = tmp->type;
	}
	tmp = sym;
	while ( mem_type2 == MT_TYPE ) {
	    mem_type2 = tmp->mem_type;
	    tmp = tmp->type;
	}
	if ( mem_type2 != mem_type ) {
	    return( asmerr( 2004, sym->name ) );
	}
    }
    return( NOT_ERROR );
}
/*
 * parse data definition line. Syntax:
 * [label] directive|simple type|arbitrary type initializer [,...]
 * - directive: DB, DW, ...
 * - simple type: BYTE, WORD, ...
 * - arbitrary type: struct, union, typedef or record name
 * arguments:
 * i: index of directive or type
 * type_sym: userdef type or NULL
 */

int data_dir( int i, struct asm_tok tokenarray[], struct asym *type_sym )
{
    uint_32		no_of_bytes;
    struct asym		*sym = NULL;
    uint_32		old_offset;
    uint_32		currofs; /* for LST output */
    unsigned char	mem_type;
    bool		is_float = FALSE;
    int			o,idx;
    char		*name;

    /* v2.05: the previous test in parser.c wasn't fool-proved */
    if ( i > 1 && ModuleInfo.m510 == FALSE ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    if( tokenarray[i+1].token == T_FINAL ) {
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }

    o = 1;
    if ( tokenarray[i].token == T_BINARY_OPERATOR ) {

	char type[128];

	idx = i;
	strcpy( type, "ptr?" );

	if ( tokenarray[i+1].token != T_QUESTION_MARK &&
	     tokenarray[i+1].token != T_NUM ) {

	    o++;
	    i++;
	    if ( tokenarray[i].token == T_BINARY_OPERATOR ) {
		strcat( type, "ptr?" );
		if ( tokenarray[i+1].token != T_QUESTION_MARK &&
		     tokenarray[i+1].token != T_NUM ) {
		    i++;
		    o++;
		}
	    }
	    if ( tokenarray[i].token != T_QUESTION_MARK &&
		 tokenarray[i].token != T_NUM ) {
		strcat( type, tokenarray[i].string_ptr );
	    }
	}
	if ( CreateType( idx, tokenarray, type, &type_sym ) == ERROR )
	    return ERROR;
    }

    /* set values for mem_type and no_of_bytes */
    if ( type_sym ) {
	/* if the parser found a TYPE id, type_sym is != NULL */
	mem_type = MT_TYPE;
	if ( type_sym->typekind != TYPE_TYPEDEF &&
	     ( type_sym->total_size == 0 || ((struct dsym *)type_sym)->e.structinfo->OrgInside == TRUE ) ) {
	    return( asmerr( 2159 ) );
	}

	/* v2.09: expand literals inside <> or {}.
	 * Previously this was done inside InitStructuredVar()
	 */
	if ( Parse_Pass == PASS_1 || UseSavedState == FALSE )
	    ExpandLiterals( i+1, tokenarray );

	no_of_bytes = type_sym->total_size;
	if ( no_of_bytes == 0 ) {
	    /* a void type is not valid */
	    if ( type_sym->typekind == TYPE_TYPEDEF ) {
		return( asmerr( 2004, type_sym->name ) );
	    }
	}
    } else {
	/* it's either a predefined type or a data directive. For types, the index
	 into the simpletype table is in <bytval>, for data directives
	 the index is found in <sflags>.
	 * v2.06: SimpleType is obsolete. Use token index directly!
	 */

	if ( tokenarray[i].token == T_STYPE ) {
	    idx = tokenarray[i].tokval;
	} else if ( tokenarray[i].token == T_DIRECTIVE &&
	       ( tokenarray[i].dirtype == DRT_DATADIR )) {
	    idx = GetSflagsSp( tokenarray[i].tokval );
	} else {
	    return( asmerr( 2004, tokenarray[i].string_ptr ) );
	}
	mem_type = GetMemtypeSp( idx );
	/* types NEAR[16|32], FAR[16|32] and PROC are invalid here */
	if ( ( mem_type & MT_SPECIAL_MASK ) == MT_ADDRESS ) {
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}
	no_of_bytes = (mem_type & MT_SIZE_MASK) + 1;
	if ( mem_type & MT_FLOAT )
	    is_float = TRUE;
    }

    /* if i == 1, there's a (data) label at pos 0.
     * (note: if -Zm is set, a code label may be at pos 0, and
     * i is 2 then.)
     */
    name = ( ( i == o ) ? tokenarray[0].string_ptr : NULL );

    /* in a struct declaration? */
    if( CurrStruct ) {

	/* structure parsing is done in the first pass only */
	if( Parse_Pass == PASS_1 ) {
	    if (!(sym = CreateStructField( i, tokenarray, name, mem_type, type_sym, no_of_bytes ))) {
		return ( ERROR );
	    }
	    if ( StoreState ) FStoreLine(0);
	    currofs = sym->offset;
	    sym->isdata = TRUE; /* 'first_size' is valid */
	} else { /* v2.04: else branch added */
	    sym = &CurrStruct->e.structinfo->tail->sym;
	    currofs = sym->offset;
	    CurrStruct->e.structinfo->tail = CurrStruct->e.structinfo->tail->next;
	}

    } else {

	if( CurrSeg == NULL ) {
	    return( asmerr( 2034 ) );
	}

	FStoreLine(0);

	if ( ModuleInfo.CommentDataInCode )
	    omf_OutSelect( TRUE );

	if ( ModuleInfo.list ) {
	    currofs = GetCurrOffset();
	}

	/* is a label accociated with the data definition? */
	if( name ) {
	    /* get/create the label. */
	    sym = SymLookup( name );
	    if( Parse_Pass == PASS_1 ) {

		if ( sym->state == SYM_EXTERNAL && sym->weak == TRUE && sym->isproc == FALSE ) { /* EXTERNDEF? */
		    checktypes( sym, mem_type, type_sym );
		    sym_ext2int( sym );
		    sym->total_size = 0;
		    sym->total_length = 0;
		    sym->first_length = 0;

		} else if( sym->state == SYM_UNDEFINED ) {

		    sym_remove_table( &SymTables[TAB_UNDEF], (struct dsym *)sym );
		    sym->state = SYM_INTERNAL;
		    /* v2.11: Set the symbol's langtype. It may have been set
		     * by a PUBLIC directive, so take care not to overwrite it.
		     * Problem: Masm doesn't do this - might be a bug.
		     */
		    if ( sym->langtype == LANG_NONE )
			sym->langtype = ModuleInfo.langtype;
		} else if ( sym->state == SYM_INTERNAL) {

		    /* accept a symbol "redefinition" if addresses and types
		     * do match.
		     */
		    if ( sym->segment != (struct asym *)CurrSeg ||
			sym->offset != GetCurrOffset() ) {
			return( asmerr(2005, name ) );
		    }
		    /* check for symbol type conflict */
		    if ( checktypes( sym, mem_type, type_sym ) == ERROR )
			return( ERROR );
		    /* v2.09: reset size and length ( might have been set by LABEL directive ) */
		    sym->total_size = 0;
		    sym->total_length = 0;
		    goto label_defined; /* don't relink the label */

		} else {
		    return( asmerr( 2005, sym->name ) );
		}
		/* add the label to the linked list attached to curr segment */
		/* this allows to reduce the number of passes (see Fixup.c) */
		((struct dsym *)sym)->next = (struct dsym *)CurrSeg->e.seginfo->label_list;
		CurrSeg->e.seginfo->label_list = sym;

	    } else {
		old_offset = sym->offset;
	    }
	label_defined:
	    SetSymSegOfs( sym );
	    if( Parse_Pass != PASS_1 && sym->offset != old_offset ) {
		ModuleInfo.PhaseError = TRUE;
	    }
	    sym->isdefined = TRUE;
	    sym->isdata = TRUE; /* 'first_size' is valid */
	    sym->mem_type = mem_type;
	    sym->type = type_sym;

	    /* backpatch for data items? Yes, if the item is defined
	     * in a code segment then its offset may change!
	     */
	    BackPatch( sym );
	}

	if ( type_sym ) {
	    while ( type_sym->mem_type == MT_TYPE )
		type_sym = type_sym->type;
	    /* if it is just a type alias, skip the arbitrary type */
	    if ( type_sym->typekind == TYPE_TYPEDEF )
		type_sym = NULL;
	}

    }
    i++;
    if ( data_item( &i, tokenarray, sym, no_of_bytes, type_sym, 1, CurrStruct != NULL, is_float, TRUE, Token_Count ) == ERROR ) {
	return( ERROR );
    }

    if ( tokenarray[i].token != T_FINAL ) {
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }

    /* v2.06: update struct size after ALL items have been processed */
    if ( CurrStruct )
	UpdateStructSize( sym );

    if ( ModuleInfo.list )
	LstWrite( CurrStruct ? LSTTYPE_STRUCT : LSTTYPE_DATA, currofs, sym );

    return( NOT_ERROR );
}

