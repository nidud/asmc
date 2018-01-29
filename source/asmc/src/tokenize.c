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
* Description:	tokenizer.
*
****************************************************************************/

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "condasm.h"
#include "reswords.h"
#include "input.h"
#include "segment.h"
#include "listing.h"
#include "tokenize.h"
#include "fastpass.h"

#define CONCATID 0 /* 0=most compatible (see backsl.asm) */
#define MASMNUMBER 1 /* 1=Masm-compatible number scanning */
#ifdef __I86__
#define TOKSTRALIGN 0 /* 0=don't align token strings */
#else
#define TOKSTRALIGN 1 /* 1=align token strings to sizeof(uint_32) */
#endif

#ifndef DOTNAMEX /* v2.08: added */
/* set DOTNAMEX to 1 if support for Intel C++ generated assembly code
 * is to be enabled.
 */
#define DOTNAMEX 0
#endif

extern struct ReservedWord  ResWordTable[];

extern char *token_stringbuf;  /* start token string buffer */
extern char *commentbuffer;

#if !defined(__GNUC__) && !defined(__POCC__)
#define tolower(c) ((c >= 'A' && c <= 'Z') ? c | 0x20 : c )
#endif

/* strings for token 0x28 - 0x2F */
static const short stokstr1[] = {
    '(',')','*','+',',','-','.','/'};
/* strings for token 0x5B - 0x5D */
static const short stokstr2[] = {
    '[',0,']'};

static char _cstring  = 0; // allow \" in string
static char _brachets = 0; // proc ( ... )

/* test line concatenation if last token is a comma.
 * dont concat EQU, macro invocations or
 * - ECHO
 * - FORC/IRPC (v2.0)
 * - INCLUDE (v2.8)
 * lines!
 * v2.05: don't concat if line's an instruction.
 */
static int IsMultiLine( struct asm_tok tokenarray[] )
{
    struct asym *sym;
    int i;

    if ( tokenarray[1].token == T_DIRECTIVE && tokenarray[1].tokval == T_EQU )
	return( FALSE );
    i = ( tokenarray[1].token == T_COLON ? 2 : 0 );
    /* don't concat macros */
    if ( tokenarray[i].token == T_ID ) {
	sym = SymSearch( tokenarray[i].string_ptr );
	if ( sym && ( sym->state == SYM_MACRO )
	    && sym->mac_multiline == FALSE  /* v2.11: added */
	   )
	    return( FALSE );
    } else if ( tokenarray[i].token == T_INSTRUCTION ||
	       ( tokenarray[i].token == T_DIRECTIVE &&
	       ( tokenarray[i].tokval == T_ECHO ||
		tokenarray[i].tokval == T_INCLUDE ||
		tokenarray[i].tokval == T_FORC ||
		tokenarray[i].tokval == T_IRPC ) ) ) {
	return( FALSE );
    }
    return( TRUE );
}

static int get_float( struct asm_tok *buf, struct line_status *p )
{
    /* valid floats look like:	(int)[.(int)][e(int)]
     * Masm also allows hex format, terminated by 'r' (3F800000r)
     */

    char    got_decimal = FALSE;
    char    got_e = FALSE;
    char    *ptr = p->input;

    for( ; *ptr != NULLC; ptr++ ) {
	char c = *ptr;
	if( isldigit( c ) ) {
	    ;
	} else if ( c == '.' && got_decimal == FALSE ) {
	    got_decimal = TRUE;
	} else if ( tolower( c ) == 'e' && got_e == FALSE ) {
	    got_e = TRUE;
	    /* accept e+2 / e-4 /etc. */
	    if ( *(ptr+1) == '+' || *(ptr+1) == '-' )
		ptr++;
	    /* it's accepted if there's no digit behind 'e' */
	    //if ( !isdigit( *(ptr+1) ) )
	    //	  break;
	} else
	    break;
    }

    buf->token = T_FLOAT;
    buf->floattype = NULLC;
    memcpy( p->output, p->input, ptr - p->input );
    p->output += ( ptr - p->input );
    *p->output++ = NULLC;
    p->input = ptr;

    return( NOT_ERROR );
}

static int ConcatLine( char *src, int cnt, char *out, struct line_status *ls )
/*********************************************************************************/
{
    char *p = src+1;
    int max;

    while ( islspace(*p) ) p++;
    if ( *p == NULLC || *p == ';' ) {
	char *buffer = out;
	if( GetTextLine( buffer ) ) {
	    p = buffer;
	    /* skip leading spaces */
	    while ( islspace( *p ) ) p++;
	    max = strlen( p );
	    if ( cnt == 0 )
		*src++ = ' ';
	    if ( ( src - ls->start ) + max >= MAX_LINE_LEN ) {
		asmerr( 2039 );
		max = MAX_LINE_LEN - ( src - ls->start + 1 );
		*(p+max) = NULLC;
	    }
	    memcpy( src, p, max+1 );
	    return( NOT_ERROR );
	}
    }
    return( EMPTY );
}

static int get_string( struct asm_tok *buf, struct line_status *p )
/**********************************************************************/
{
    char    symbol_o;
    char    symbol_c;
    char    c;
    char    *cp;
    char    *src = p->input;
    char    *dst = p->output;
    int	    count = 0;
    int	    level;

    symbol_o = *src;

    switch( symbol_o ) {
    case '"':
    case '\'':
	buf->string_delim = symbol_o;
	*dst++ = symbol_o;
	src++;
	for ( ; count < MAX_STRING_LEN; src++, count++ ) {
	    c = *src;

	    if( c == NULLC ) {
		/* missing terminating quote, change to undelimited string */
		buf->string_delim = NULLC;
		count++; /* count the first quote */
		break;
	    }

	    if ( symbol_o == '"' && c == _cstring ) {	// case \" ?
		if ( *(src-1) == '\\' && *(src-2) != '\\' ) {
		    *dst++ = c;
		    continue;
		}

		for( cp = src + 1; *cp == ' ' || *cp == 9; cp++ );
		if ( *cp == '"' ) {

		    /* "string1" "string2" */
		    src = cp;
		    continue;
		}
	    }

	    if ( c == symbol_o ) { /* another quote? */
		*dst++ = c; /* store it */
		src++;
		if( *src != c )
		    break; /* exit loop */
		/* a pair of quotes inside the string is
		 * handled as a single quote */
	    } else if( c == NULLC ) {
		/* missing terminating quote, change to undelimited string */
		buf->string_delim = NULLC;
		count++; /* count the first quote */
		break;
	    } else {
		*dst++ = c;
	    }
	}
	break;	/* end of string marker is the same */
    case '{':
	if ( p->flags & TOK_NOCURLBRACES )
	    goto undelimited_string;
    case '<':
	buf->string_delim = symbol_o;
	symbol_c = ( symbol_o == '<' ? '>' : '}' );
	src++;
	for( level = 0; count < MAX_STRING_LEN; ) {
	    c = *src;
	    if( c == symbol_o ) { /* < or { ? */
		level++;
		*dst++ = c; src++;
		count++;
	    } else if( c == symbol_c ) { /* > or }? */
		if( level ) {
		    level--;
		    *dst++ = c; src++;
		    count++;
		} else {
		    /* store the string delimiter unless it is <> */
		    /* v2.08: don't store delimiters for {}-literals */
		    src++;
		    break; /* exit loop */
		}
	    /*
	     a " or ' inside a <>/{} string? Since it's not a must that
	     [double-]quotes are paired in a literal it must be done
	     directive-dependant!
	     see: IFIDN <">,<">
	     */
	    } else if( ( c == '"' || c == '\'' ) && ( p->flags2 & DF_STRPARM ) == 0 ) {
		char delim = c;
		char *tdst;
		char *tsrc;
		int tcount;
		*dst++ = c; src++;
		count++;
		tdst = dst;
		tsrc = src;
		tcount = count;
		while (*src != delim && *src != NULLC && count < MAX_STRING_LEN-1 ) {
		    if ( symbol_o == '<' && *src == '!' && *(src+1) != NULLC )
			src++;
		    *dst++ = *src++;
		    count++;
		}
		if ( *src == delim ) {
		    *dst++ = *src++;
		    count++;
		    continue;
		} else {
		    /* restore values */
		    src = tsrc;
		    dst = tdst;
		    count = tcount;
		}
	    } else if( c == '!' && symbol_o == '<' && *(src+1) ) {
		/* handle literal-character operator '!'.
		 * it makes the next char to enter the literal uninterpreted.
		 */
		src++;
		*dst++ = *src++;
		count++;
	    } else if( c == '\\' &&  ConcatLine( src, count, dst, p ) != EMPTY ) {
		p->flags3 |= TF3_ISCONCAT;
	    } else if( c == NULLC || ( c == ';' && symbol_o == '{' )) {
		if ( p->flags == TOK_DEFAULT && (( p->flags2 & DF_NOCONCAT ) == 0 ) ) { /* <{ */
		    /* if last nonspace character was a comma
		     * get next line and continue string scan
		     */
		    char *tmp = dst-1;
		    while ( islspace(*tmp) ) tmp--;
		    if ( *tmp == ',' ) {

			tmp = GetAlignedPointer( p->output, strlen( p->output ) );
			if( GetTextLine( tmp ) ) {
			    /* skip leading spaces */
			    while ( islspace( *tmp ) ) tmp++;
			    /* this size check isn't fool-proved yet */
			    if ( strlen( tmp ) + count >= MAX_LINE_LEN ) {
				asmerr( 2039 );
				return( ERROR );
			    }
			    strcpy( src, tmp );
			    continue;
			}
		    }
		}
		src = p->input;
		dst = p->output;
		*dst++ = *src++;
		count = 1;
		goto undelimited_string;
	    } else {
		*dst++ = c; src++;
		count++;
	    }
	}
	break;
    default:
	undelimited_string:
	buf->string_delim = NULLC;
	/* this is an undelimited string,
	 * so just copy it until we hit something that looks like the end.
	 * this format is used by the INCLUDE directive, but may also
	 * occur inside the string macros!
	 */
	/* v2.05: also stop if a ')' is found - see literal2.asm regression test */

	for( ; count < MAX_STRING_LEN && *src && !islspace( *src ) && *src != ','; ) {

	    if ( *src == ')' ) {
		_brachets = 0;
		break;
	    }
	    /* v2.08: stop also at < and % */

	    if ( *src == '%' ) break;
	    if ( *src == ';' && p->flags == TOK_DEFAULT ) break;

	    /* v2.11: handle '\' also for expanded lines */

	    if (  *src == '\\' && ( p->flags == TOK_DEFAULT || ( p->flags & TOK_LINE ) ) ) {

		if ( ConcatLine( src, count, dst, p ) != EMPTY ) {
		    p->flags3 |= TF3_ISCONCAT;
		    if ( count )
			continue;
		    return( EMPTY );
		}
	    }
	    /* v2.08: handle '!' operator */
	    if ( *src == '!' && *(src+1) && count < MAX_STRING_LEN - 1 )
		*dst++ = *src++;
	    *dst++ = *src++;
	    count++;
	}
	break;
    }

    if ( count == MAX_STRING_LEN ) {
	return( asmerr( 2041 ) );
    }
    *dst++ = NULLC;
    buf->token = T_STRING;
    buf->stringlen = count;
    p->input = src;
    p->output = dst;
    return( NOT_ERROR );
}

static int get_special_symbol( struct asm_tok *buf, struct line_status *p )
{
    char symbol;

    symbol = *p->input;
    switch( symbol ) {
    case ':' : /* T_COLON binary operator (0x3A) */
	p->input++;
	if ( *p->input == ':' ) {
	    p->input++;
	    buf->token = T_DBL_COLON;
	    buf->string_ptr = "::";
	} else {
	    buf->token = T_COLON;
	    buf->string_ptr = ":";
	}
	break;
    case '%' : /* T_PERCENT (0x25) */

	/* %OUT directive? */
	if ( ( _memicmp( p->input+1, "OUT", 3 ) == 0 ) && !is_valid_id_char( *(p->input+4) ) ) {
	    buf->token = T_DIRECTIVE;
	    buf->tokval = T_ECHO;
	    buf->dirtype = DRT_ECHO;
	    memcpy( p->output, p->input, 4 );
	    p->input += 4;
	    p->output += 4;
	    *(p->output)++ = NULLC;
	    break;
	}

	p->input++;
	if ( p->flags == TOK_DEFAULT && p->index == 0 ) {
	    p->flags3 |= TF3_EXPANSION;
	    return( EMPTY );
	}
	buf->token = T_PERCENT;
	buf->string_ptr = "%";
	break;
    case '(' : /* 0x28: T_OP_BRACKET operator - needs a matching ')' */
	/* v2.11: reset c-expression flag if a macro function call is detected */
	/* v2.20: set _cstring to allow escape chars (\") in @CStr( string ) */
	/* v2.20: removed auto off switch for asmc_syntax in macros */
	/* v2.20: added more test code for label() calls */

	if ( *(p->input+1) == ')' && (buf-1)->token == T_REG ) {

	    /* REG() expans as CALL REG */

	    (buf-1)->hll_flags |= T_HLL_PROC;

	} else if ( p->index && (buf-1)->token == T_ID ) {

	    char flag = 0;
	    int state = 0;
	    struct asym *sym = SymFind( (buf-1)->string_ptr );
	    struct asm_tok *tok = (buf-1);

	    if ( !sym && p->index >= 3 && (tok-1)->token == T_DOT ) {

		/* p.x(...) | [...][.type].x(...) */

		tok -= 2;
		if ( (tok-1)->token == T_CL_SQ_BRACKET ) {

		    tok += 2;
		    sym++;
		    state = SYM_TYPE;

		} else {

		    sym = SymFind( (tok-1)->string_ptr );
		}
	    }

	    if ( sym ) {

		if ( !state )
		    state = sym->state;

		while ( 1 ) {

		    if ( !( ModuleInfo.aflag & _AF_ON ) ) {

			if ( ( state == SYM_MACRO ) && sym->isfunc )
			    p->flags2 &= ~DF_CEXPR;

		    } else if ( sym->state == SYM_MACRO ) {

			if ( sym->isfunc ) {

			    p->flags2 &= ~DF_CEXPR;

			    if ( sym->predefined ) {

				if ( !strcmp( sym->name, "@CStr" ) ) {
				    _brachets++;
				    _cstring = '"';
				    break;
				}
			    }
			    flag = T_HLL_MACRO;
			    break;
			}

			if ( sym->predefined || !sym->string_ptr )
			    break;

			if ( !( sym = SymFind( sym->string_ptr ) ) )
			    break;

			if ( !sym->isproc )
			    break;

			flag = T_HLL_PROC;
			_brachets++;
			_cstring = '"';

		    } else if ( state == SYM_STACK || state == SYM_INTERNAL || state == SYM_EXTERNAL || sym->isproc ) {

			flag = T_HLL_PROC;
			_brachets++;
			_cstring = '"';

		    } else if ( state == SYM_TYPE ) { /* structure, union, typedef, record */

			/* [...].type.x(...) */
			if ( p->index >= 5 && (tok-1)->token == T_DOT && (tok-2)->token == T_CL_SQ_BRACKET ) {

			    tok -= 4;
			    state = p->index - 4;

			    while ( state && tok->token != T_OP_SQ_BRACKET ) {

				tok--;
				state--;
			    };

			    if ( tok->token == T_OP_SQ_BRACKET ) {

				flag = T_HLL_PROC;
				_brachets++;
				_cstring = '"';
			    }
			}

		    } else if ( state == SYM_UNDEFINED ) {

			if ( *(p->input+1) == ')' )
			    flag = T_HLL_PROC;
		    }
		    break;
		}

		tok->hll_flags |= flag;

	    } else if ( *(p->input+1) == ')' ) {
		//
		// undefined code label..
		//
		// label() or .if label()
		// ...
		// label:
		//
		tok->hll_flags |= T_HLL_PROC;
	    }
	}
	/* no break */
    case ')' : /* 0x29: T_CL_BRACKET */
	if ( symbol == ')' && _brachets ) {
	    _brachets--;
	    _cstring = 0;
	}
    case '*' : /* 0x2A: binary operator */
    case '+' : /* 0x2B: unary|binary operator */
    case ',' : /* 0x2C: T_COMMA */
    case '-' : /* 0x2D: unary|binary operator */
    case '.' : /* 0x2E: T_DOT binary operator */
    case '/' : /* 0x2F: binary operator */
	/* all of these are themselves a token */
	p->input++;
	buf->token = symbol;
	buf->specval = 0; /* initialize, in case the token needs extra data */
	/* v2.06: use constants for the token string */
	buf->string_ptr = (char *)&stokstr1[symbol - '('];
	break;
    case '[' : /* T_OP_SQ_BRACKET operator - needs a matching ']' (0x5B) */
    case ']' : /* T_CL_SQ_BRACKET (0x5D) */
	p->input++;
	buf->token = symbol;
	/* v2.06: use constants for the token string */
	buf->string_ptr = (char *)&stokstr2[symbol - '['];
	break;
    case '=' : /* (0x3D) */
	if ( *(p->input+1) != '=' ) {
	    buf->token = T_DIRECTIVE;
	    buf->tokval = T_EQU;
	    buf->dirtype = DRT_EQUALSGN; /* to make it differ from EQU directive */
	    buf->string_ptr = "=";
	    p->input++;
	    break;
	}
	/* fall through */
    default:
	/* detect C style operators.
	 * DF_CEXPR is set if .IF, .WHILE, .ELSEIF or .UNTIL
	 * has been detected in the current line.
	 * will catch: '!', '<', '>', '&', '==', '!=', '<=', '>=', '&&', '||'
	 * A single '|' will also be caught, although it isn't a valid
	 * operator - it will cause a 'operator expected' error msg later.
	 * the tokens are stored as one- or two-byte sized "strings".
	 */
	if ( ( p->flags2 & DF_CEXPR ) && strchr( "=!<>&|", symbol ) ) {
	    *(p->output)++ = symbol;
	    p->input++;
	    buf->stringlen = 1;
	    if ( symbol == '&' || symbol == '|' ) {
		if ( *p->input == symbol ) {
		    *(p->output)++ = symbol;
		    p->input++;
		    buf->stringlen = 2;
		} else if ( symbol == '&' &&
		    ( (buf-1)->token == T_OP_BRACKET || (buf-1)->token == T_COMMA ) ) {
		    buf->token = '&';
		    buf->string_ptr = "&";
		    break;
		}
	    } else if ( *p->input == '=' ) {
		*(p->output)++ = '=';
		p->input++;
		buf->stringlen = 2;
	    }
	    buf->token = T_STRING;
	    buf->string_delim = NULLC;
	    *(p->output)++ = NULLC;
	    break;
	}
	/* v2.08: ampersand is a special token */
	if ( symbol == '&' ) {
	    p->input++;
	    buf->token = '&';
	    buf->string_ptr = "&";
	    break;
	}
	/* anything we don't recognise we will consider a string,
	 * delimited by space characters, commas, newlines or nulls
	 */
	return( get_string( buf, p ) );
    }
    return( NOT_ERROR );
}

/* read in a number.
 * check the number suffix:
 * b or y: base 2
 * d or t: base 10
 * h: base 16
 * o or q: base 8
 */
static int get_number( struct asm_tok *buf, struct line_status *p )
/**********************************************************************/
{
    char		*ptr = p->input;
    char		*dig_start;
    char		*dig_end;
    unsigned		base = 0;
    unsigned		len;
    uint_32		digits_seen;
    char		last_char;

#define VALID_BINARY	0x0003
#define VALID_OCTAL	0x00ff
#define VALID_DECIMAL	0x03ff
#define OK_NUM( t )	((digits_seen & ~VALID_##t) == 0)

    digits_seen = 0;
    dig_start = ptr;
#if CHEXPREFIX
    if( *ptr == '0' && (tolower( *(ptr+1) ) == 'x' ) ) {
	ptr += 2;
	base = 16;
    }
#endif
    for( ;; ptr++ ) {
	if (*ptr >= '0' && *ptr <= '9')
	    digits_seen |= 1 << (*ptr - '0');
	else {
	    last_char = tolower( *ptr );
	    if ( last_char >= 'a' && last_char <= 'f' )
		digits_seen |= 1 << ( last_char + 10 - 'a' );
	    else
		break;
	}
    }

    /* note that a float MUST contain a dot.
     * 1234e78 is NOT a valid float
     */
    if ( last_char == '.' )
	return( get_float( buf, p ) );

#if CHEXPREFIX
    if ( base != 0 ) {
	dig_end = ptr;
	if ( digits_seen == 0 )
	    base = 0;
    } else
#endif
    switch( last_char ) {
    case 'r': /* a float with the "real number designator" */
	buf->token = T_FLOAT;
	buf->floattype = 'r';
	ptr++;
	goto number_done;
    case 'h':
	base = 16;
	dig_end = ptr;
	ptr++;
	break;
    case 'y':
	if( OK_NUM( BINARY ) ) {
	    base = 2;
	    dig_end = ptr;
	    ptr++;
	}
	break;
    case 't':
	if( OK_NUM( DECIMAL ) ) {
	    base = 10;
	    dig_end = ptr;
	    ptr++;
	}
	break;
    case 'q':
    case 'o':
	if( OK_NUM( OCTAL ) ) {
	    base = 8;
	    dig_end = ptr;
	    ptr++;
	}
	break;
    default:
	last_char = tolower( *(ptr-1) );
	if ( ( last_char == 'b' || last_char == 'd' ) && digits_seen >= ( 1UL << ModuleInfo.radix ) ) {
	    char *tmp = dig_start;
	    char max = ( last_char == 'b' ? '1' : '9' );
	    for ( dig_end = ptr-1; tmp < dig_end && *tmp <= max; tmp++ );
	    if ( tmp == dig_end ) {
		base = ( last_char == 'b' ? 2 : 10 );
		break;
	    }
	}
	dig_end = ptr;
#if COCTALS
	if( Options.allow_c_octals && *dig_start == '0' ) {
	    if( OK_NUM( OCTAL ) ) {
		base = 8;
		break;
	    }
	}
#endif
	/* radix      max. digits_seen
	 -----------------------------------------------------------
	 2	      3	     2^2-1  (0,1)
	 8	      255    2^8-1  (0,1,2,3,4,5,6,7)
	 10	      1023   2^10-1 (0,1,2,3,4,5,6,7,8,9)
	 16	      65535  2^16-1 (0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f)
	 */
	if ( digits_seen < (1UL << ModuleInfo.radix) )
	    base = ModuleInfo.radix;
	break;
    }

#if MASMNUMBER
    /* Masm doesn't swallow alphanum chars which may follow the
     * number!
     */
    if ( base != 0 ) {
#else
    if ( base != 0 && is_valid_id_char( *ptr ) == FALSE ) {
#endif
	buf->token = T_NUM;
	buf->numbase = base;
	buf->itemlen = dig_end - dig_start;
    } else {
	buf->token = T_BAD_NUM;
	/* swallow remainder of token */
	while( is_valid_id_char( *ptr ) ) ++ptr;
    }
number_done:
    len = ptr - p->input;
    memcpy( p->output, p->input, len );

    p->output += len;
    *p->output++ = NULLC;
    p->input = ptr;

    return( NOT_ERROR );
}

#if BACKQUOTES
static int get_id_in_backquotes( struct asm_tok *buf, struct line_status *p )
{
    char *optr = p->output;
    buf->token = T_ID;
    buf->idarg = 0;

    p->input++;		/* strip off the backquotes */
    for( ; *p->input != '`'; ) {
	if( *p->input == NULLC || *p->input == ';' ) {
	    *p->output = NULLC;
	    return( asmerr( 2046 ); );
	}
	*optr++ = *p->input++;
    }
    p->input++;		/* skip the terminating '`' */
    *optr++ = NULLC;
    p->output = optr;
    return( NOT_ERROR );
}
#endif

/* get an ID. will always return NOT_ERROR. */

static int get_id( struct asm_tok *buf, struct line_status *p )
{
    char *src = p->input;
    char *dst = p->output;
    int	 index;
    unsigned size;

    if ( *src == 'L' && *(src+1) == '"' && _brachets ) {
	*dst = 'L';
	p->input++;
	p->output++;
	get_string( buf, p );
	return 0;
    }

#if CONCATID || DOTNAMEX
continue_scan:
#endif
    do {
	*dst++ = *src++;
    } while ( is_valid_id_char( *src ) );
#if CONCATID
    /* v2.05: in case there's a backslash right behind
     * the ID, check if a line concatenation is to occur.
     * If yes, and the first char of the concatenated line
     * is also a valid ID char, continue to scan the name.
     * Problem: it's ok for EQU, but less good for other directives.
     */
    if ( *src == '\\' ) {
	if ( ConcatLine( src, src - p->input, dst, p ) != EMPTY ) {
	    p->concat = TRUE;
	    if ( is_valid_id_char( *src ) )
		goto continue_scan;
	}
    }
#endif
#if DOTNAMEX
    /* if the name starts with a dot or underscore, then accept dots
     * within the name (though not as last char). OPTION DOTNAME
     * must be on.
     */
    if ( *src == '.' && ModuleInfo.dotname &&
	( *(p->output) == '.' || *(p->output) == '_' ) &&
	( is_valid_id_char(*(src+1)) || *(src+1) == '.' ) )
	goto continue_scan;
#endif
    /* v2.04: check added */
    size = dst - p->output;
    if ( size > MAX_ID_LEN ) {
	asmerr( 2043 );
	dst = p->output + MAX_ID_LEN;
    }
    *dst++ = NULLC;

    /* now decide what to do with it */

    if( size == 1 && *p->output == '?' ) {
	p->input = src;
	buf->token = T_QUESTION_MARK;
	buf->string_ptr = "?";
	return( NOT_ERROR );
    }
    index = FindResWord( p->output, size );
    if( index == 0 ) {
	/* if ID begins with a DOT, check for OPTION DOTNAME.
	 * if not set, skip the token and return a T_DOT instead!
	 */
	if ( *p->output == '.' && ModuleInfo.dotname == FALSE ) {
	   buf->token = T_DOT;
	   buf->string_ptr = (char *)&stokstr1['.' - '('];
	   p->input++;
	   return( NOT_ERROR );
	}
	p->input = src;
	p->output = dst;
	buf->token = T_ID;
	buf->idarg = 0;
	return( NOT_ERROR );
    }
    p->input = src;
    p->output = dst;

    /* v2.24 hack for syscall.. */
    if ( index == T_SYSCALL && p->index == 0 )
	 index = T_SYSCALL_;

    buf->tokval = index; /* is a enum instr_token value */
    if ( index == T_DOT_ELSEIF || index == T_DOT_WHILE || index == T_DOT_CASE )
	buf->hll_flags = T_HLL_DELAY;

    /* v2.11: RWF_SPECIAL now obsolete */

    if ( index >= SPECIAL_LAST ) {

	/* if -Zm is set, the following from the Masm docs is relevant:
	 *
	 * Reserved Keywords Dependent on CPU Mode with OPTION M510
	 *
	 * With OPTION M510, keywords and instructions not available in the
	 * current CPU mode (such as ENTER under .8086) are not treated as
	 * keywords. This also means the USE32, FLAT, FAR32, and NEAR32 segment
	 * types and the 80386/486 registers are not keywords with a processor
	 * selection less than .386.
	 * If you remove OPTION M510, any reserved word used as an identifier
	 * generates a syntax error. You can either rename the identifiers or
	 * use OPTION NOKEYWORD. For more information on OPTION NOKEYWORD, see
	 * OPTION NOKEYWORD, later in this appendix.
	 *
	 * The current implementation of this rule below is likely to be improved.
	 */
	if ( ModuleInfo.m510 ) {
	    /* checking the cpu won't give the expected results currently since
	     * some instructions in the table (i.e. MOV) start with a 386 variant!
	     */
	    index = IndexFromToken( buf->tokval );
	    if (( InstrTable[index].cpu & P_CPU_MASK ) > ( ModuleInfo.curr_cpu & P_CPU_MASK ) ||
		( InstrTable[index].cpu & P_EXT_MASK ) > ( ModuleInfo.curr_cpu & P_EXT_MASK )) {
		buf->token = T_ID;
		buf->idarg = 0;
		return( NOT_ERROR );
	    }
	}
	buf->token = T_INSTRUCTION;
	return( NOT_ERROR );
    }
    index = buf->tokval;

    /* for RWT_SPECIAL, field <bytval> contains further infos:
     - RWT_REG:		    register number (regnum)
     - RWT_DIRECTIVE:	    type of directive (dirtype)
     - RWT_UNARY_OPERATOR:  operator precedence
     - RWT_BINARY_OPERATOR: operator precedence
     - RWT_STYPE:	    memtype
     - RWT_RES_ID:	    for languages, LANG_xxx value
			    for the rest, unused.
     */
    buf->bytval = SpecialTable[index].bytval;

    switch ( SpecialTable[index].type ) {
    case RWT_REG:
	buf->token = T_REG;
	break;
    case RWT_DIRECTIVE:
	buf->token = T_DIRECTIVE;
	if ( p->flags2 == 0 )
	    p->flags2 = SpecialTable[index].value;
	break;
    case RWT_UNARY_OP: /* OFFSET, LOW, HIGH, LOWWORD, HIGHWORD, SHORT, ... */
	buf->token  = T_UNARY_OPERATOR;
	break;
    case RWT_BINARY_OP: /* GE, GT, LE, LT, EQ, NE, MOD, PTR */
	buf->token = T_BINARY_OPERATOR;
	break;
    case RWT_STYPE:  /* BYTE, WORD, FAR, NEAR, FAR16, NEAR32 ... */
	buf->token = T_STYPE;
	break;
    case RWT_RES_ID: /* DUP, ADDR, FLAT, VARARG, language types [, FRAME (64-bit)] */
	buf->token = T_RES_ID;
	break;
    default: /* shouldn't happen */
	buf->token = T_ID;
	buf->idarg = 0;
	break;
    }
    return( NOT_ERROR );
}

/* get one token.
 * possible return values: NOT_ERROR, ERROR, EMPTY.
 *
 * names beginning with '.' are difficult to detect,
 * because the dot is a binary operator. The rules to
 * accept a "dotted" name are:
 * 1.- a valid ID char is to follow the dot
 * 2.- if buffer index is > 0, then the previous item
 *     must not be a reg, ), ] or an ID.
 * [bx.abc]    -> . is an operator
 * ([bx]).abc  -> . is an operator
 * [bx].abc    -> . is an operator
 * varname.abc -> . is an operator
 */

int FASTCALL GetToken( struct asm_tok token[], struct line_status *p )
{
    token[0].hll_flags = 0;
    token[0].tokval = 0;
    if( isldigit( *p->input ) ) {
	return( get_number( token, p ) );
    } else if( is_valid_id_start( *p->input ) ) {
	return( get_id( token, p ) );
    } else if( *p->input == '.' &&
#if DOTNAMEX /* allow dots within identifiers */
	      ( is_valid_id_char(*(p->input+1)) || *(p->input+1) == '.' ) &&
#else
	      is_valid_id_char(*(p->input+1)) &&
#endif
	      /* v2.11: member last_token has been removed */
	      ( p->index == 0 || ( token[-1].token != T_REG && token[-1].token != T_CL_BRACKET &&
		token[-1].token != T_CL_SQ_BRACKET && token[-1].token != T_ID ) ) ) {
	return( get_id( token, p ) );
#if BACKQUOTES
    } else if( *p->input == '`' && Options.strict_masm_compat == FALSE ) {
	return( get_id_in_backquotes( token, p ) );
#endif
    }
    return( get_special_symbol( token, p ) );
}

// fixme char *IfSymbol;	/* save symbols in IFDEF's so they don't get expanded */

static void StartComment( const char *p )
/***************************************/
{
    while ( islspace( *p ) ) p++;
    if ( *p == NULLC ) {
	asmerr( 2110 );
	return;
    }
    ModuleInfo.inside_comment = *p++;
    if( strchr( p, ModuleInfo.inside_comment ) )
	ModuleInfo.inside_comment = NULLC;
    return;
}

int Tokenize( char *line, unsigned int start, struct asm_tok tokenarray[],
	unsigned int flags )
/*
 * create tokens from a source line.
 * line:  the line which is to be tokenized
 * start: where to start in the token buffer. If start == 0,
 *	  then some variables are additionally initialized.
 * flags: 1=if the line has been tokenized already.
 */
{
    int rc;
    struct line_status p;

    _cstring = 0;
    _brachets = 0;

    p.input = line;
    p.start = line;
    p.index = start;
    p.flags = flags;
    p.flags2 = 0;
    p.flags3 = 0;
    if ( p.index == 0 ) {
	/* v2.06: these flags are now initialized on a higher level */
	p.output = token_stringbuf;
	if( ModuleInfo.inside_comment ) {

	    if( strchr( line, ModuleInfo.inside_comment ) != NULL ) {

		ModuleInfo.inside_comment = NULLC;
	    }
	    goto skipline;
	}

    } else {

	p.output = StringBufferEnd;
    }


    for( ;; ) {

	while( islspace( *p.input ) ) p.input++;

	if ( *p.input == ';' && flags == TOK_DEFAULT ) {
	    while ( p.input > line && islspace( *(p.input-1) ) ) p.input--; /* skip */
	    strcpy( commentbuffer, p.input );
	    ModuleInfo.CurrComment = commentbuffer;
	    *p.input = NULLC;
	}

	tokenarray[p.index].tokpos = p.input;

	if( *p.input == NULLC ) {
	    /* if a comma is last token, concat lines ... with some exceptions
	     * v2.05: moved from PreprocessLine(). Moved because the
	     * concatenation may be triggered by a comma AFTER expansion.
	     */
	    if ( p.index > 1 &&
		( tokenarray[p.index-1].token == T_COMMA || _brachets )
		&& ( Parse_Pass == PASS_1 || UseSavedState == FALSE ) /* is it an already preprocessed line? */
		&& start == 0 ) {

		if ( IsMultiLine( tokenarray ) || _brachets ) {
		    char *ptr = GetAlignedPointer( p.output, strlen( p.output ) );
		    if ( GetTextLine( ptr ) ) {
			while ( islspace( *ptr ) ) ptr++;
			if ( *ptr ) {
			    strcpy( p.input, ptr );
			    if ( strlen( p.start ) >= MAX_LINE_LEN ) {
				asmerr( 2039 );
				p.index = start;
				break;
			    }
			    continue;
			}
		    }
		}
	    }
	    break;
	}
	tokenarray[p.index].string_ptr = p.output;
	rc = GetToken( &tokenarray[p.index], &p );
	if ( rc == EMPTY )
	    continue;
	if ( rc == ERROR ) {
	    p.index = start; /* skip this line */
	    break;
	}
	/* v2.04: this has been moved here from condasm.c to
	 * avoid problems with (conditional) listings. It also
	 * avoids having to search for the first token twice.
	 * Note: a conditional assembly directive within an
	 *    inactive block and preceded by a label isn't detected!
	 *    This is an exact copy of the Masm behavior, although
	 *    it probably is just a bug!
	 */
	if ( !(flags & TOK_RESCAN) ) {

	    if ( p.index == 0 || ( p.index == 2 &&
		( tokenarray[1].token == T_COLON || tokenarray[1].token == T_DBL_COLON) ) ) {

		rc = tokenarray[p.index].tokval;
		if ( tokenarray[p.index].token == T_DIRECTIVE &&
		    ( tokenarray[p.index].bytval == DRT_CONDDIR || rc == T_DOT_ASSERT ) ) {

		    if ( rc == T_COMMENT ) {
			StartComment( p.input );
			break; /* p.index is 0 or 2 */
		    }
		    if ( rc == T_DOT_ASSERT ) {

			char *cp;
			if ( ModuleInfo.xflag & _XF_ASSERT )
			    goto dot_assert;
			cp = p.input;
			while ( *cp == ' ' || *cp == 9 ) cp++;
			if ( *cp != ':' )
			    goto dot_assert;
			cp++;
			while ( *cp == ' ' || *cp == 9 ) cp++;
			if ( _memicmp( cp, "ends", 4 ) )
			    goto dot_assert;
			rc = T_ENDIF;
		    }
		    conditional_assembly_prepare( rc );
		    if ( CurrIfState != BLOCK_ACTIVE ) {
			p.index++;
			break; /* p.index is 1 or 3 */
		    }
		} else {
		    dot_assert:
		    if( CurrIfState != BLOCK_ACTIVE )
			/* further processing skipped. p.index is 0 */
			break;
		}
	    }
	}
	p.index++;
	if( p.index >= MAX_TOKEN ) {
	    asmerr( 2141 );
	    p.index = start;
	    goto skipline;
	}

#if TOKSTRALIGN
	p.output = GetAlignedPointer( token_stringbuf, p.output - token_stringbuf );
#endif

    }

#if TOKSTRALIGN
    p.output = GetAlignedPointer( token_stringbuf, p.output - token_stringbuf );
#endif
    StringBufferEnd = p.output;
skipline:
    tokenarray[p.index].token  = T_FINAL;
    tokenarray[p.index].bytval = p.flags3;
    tokenarray[p.index].string_ptr = "";
    return( p.index );
}

