/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	Implements FOR/IRP, FORC/IRPC, REPEAT/REPT, WHILE
*
****************************************************************************/

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <input.h>
#include <equate.h>
#include <expreval.h>
#include <tokenize.h>
#include <macro.h>
#include <listing.h>
#include <reswords.h>

ret_code LoopDirective( int i, struct asm_tok tokenarray[] )
/**********************************************************/
{
    int directive = tokenarray[i].tokval;
    int arg_loc;
    int len;
    char *parmstring;
    char *ptr;
    struct dsym *m;//acro;
    bool is_exitm;
    struct expr opnd;
    struct macro_info macinfo;
    struct dsym tmpmacro;
    char buffer[4];

    i++; /* skip directive */
    if ( ModuleInfo.list == TRUE ) LstWriteSrcLine();

    switch ( directive ) {
    case T_WHILE:
	arg_loc = i;
	/* no break */
    case T_REPT:
    case T_REPEAT:
	/* the expression is "critical", that is, no forward
	 * referenced symbols may be used here!
	 */
	if ( EvalOperand( &i, tokenarray, Token_Count, &opnd, EXPF_NOUNDEF ) == ERROR ) {
	    opnd.value = 0;
	    i = Token_Count;
	} else if ( opnd.kind != EXPR_CONST ) { /* syntax <REPEAT|WHILE 'A'> is valid! */
	    asmerr( 2026 );
	    opnd.value = 0;
	} else if( tokenarray[i].token != T_FINAL ) {
	    asmerr(2008, tokenarray[i].tokpos );
	    opnd.value = 0;
	}
	break;
    default: /* FOR, FORC, IRP, IRPC */
	/* get the formal parameter and the argument list */
	/* the format parameter will become a macro parameter, so it can
	 * be a simple T_ID, but also an instruction or something else.
	 * v2.02: And it can begin with a '.'!
	 */
	if( tokenarray[i].token == T_FINAL ) {
	    return( asmerr(2008, tokenarray[i-1].tokpos ) );
	}
	/* v2.02: allow parameter name to begin with a '.' */
	if( is_valid_id_first_char( *tokenarray[i].string_ptr ) == FALSE ) {
	    return( asmerr(2008, tokenarray[i].tokpos ) );
	}
	arg_loc = i;
	i++;

	if( directive == T_FORC || directive == T_IRPC ) {
	    if( tokenarray[i].token != T_COMMA ) {
		return( asmerr( 2008, tokenarray[i].tokpos ) );
	    }
	    i++;
	    /* FORC/IRPC accepts anything as "argument list", even nothing! */
	    if( tokenarray[i].token == T_STRING && tokenarray[i].string_delim == '<' ) {
		len = tokenarray[i+1].tokpos - (tokenarray[i].tokpos+1);
		parmstring = myalloca( len );
		memcpy( parmstring, tokenarray[i].tokpos+1, len );
		while( *(parmstring+len-1) != '>' ) len--;
		*(parmstring+len-1) = NULLC;
		/* v2.02: if there's additional stuff behind the <> literal,
		 * it's an error!
		 */
		if ( tokenarray[i+1].token != T_FINAL )
		    asmerr(2008, tokenarray[i+1].tokpos );
	    } else {
		char *ptr2;
		ptr = tokenarray[i].tokpos;
		ptr2 = ptr;
		/* this is what Masm does: use the string until a space
		 * is detected. Anything beyond the space is ignored.
		 */
		while ( *ptr2 && ( islspace( *ptr2 ) == FALSE ) )
		    ptr2++;
		len = ptr2 - ptr;
		parmstring = myalloca( len + 1 );
		memcpy( parmstring, ptr, len );
		*(parmstring+len) = NULLC;
	    }
	} else {
	    /* for FOR/IRP, skip everything between the name and the comma!
	     * these items will be stored as (first) macro parameter.
	     * for example, valid syntax is:
	     * FOR xxx,<a, ...>
	     * FOR xxx:REQ,<a, ...>
	     */
	    while ( tokenarray[i].token != T_FINAL && tokenarray[i].token != T_COMMA )
		i++;
	    if( tokenarray[i].token != T_COMMA ) {
		return( asmerr( 2008, tokenarray[i].tokpos ) );
	    }
	    i++;
	    /* FOR/IRP accepts a literal enclosed in <> only */
	    if( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' ) {
		return( asmerr(2008, tokenarray[i].tokpos ) );
	    }
	    /* v2.03: also ensure that the literal is the last item */
	    if( tokenarray[i+1].token != T_FINAL ) {
		return( asmerr(2008, tokenarray[i+1].tokpos ) );
	    }
	    /* v2.08: use myalloca() instead of a fixed-length buffer.
	     * the loop directives are often nested, they call RunMacro()
	     * and hence should be careful with stack usage because of JWASMR!
	     */
	    //parmstring = myalloca( tokenarray[i].stringlen + 1 );
	    /* v2.0: use GetLiteralValue() instead of memcpy!!! */
	    //memcpy( line, tokenarray[i].string_ptr, tokenarray[i].stringlen + 1 );
	    //GetLiteralValue( parmstring, tokenarray[i].string_ptr );
	    parmstring = tokenarray[i].string_ptr;
	}
	/* to run StoreMacro(), tokenarray must be setup correctly. */
	/* clear contents beginning with the comma! */
	i--;
	tokenarray[i].token = T_FINAL;
	Token_Count = i;
	i = arg_loc;
    }

    /* now make a temporary macro */
    m = &tmpmacro;
    memset( &tmpmacro, 0, sizeof(tmpmacro) );
    tmpmacro.sym.name = "";
    tmpmacro.e.macroinfo = &macinfo;
    memset( &macinfo, 0, sizeof(macinfo) );
    macinfo.srcfile = get_curr_srcfile();

    if( StoreMacro( m, i, tokenarray, TRUE ) == ERROR ) {
	ReleaseMacroData( m );
	return( ERROR );
    }
    /* EXITM <> is allowed inside a macro loop.
     * This doesn't make the loop a macro function, reset the bit!
     */
    m->sym.isfunc = FALSE;

    /* now run the just created macro in a loop */

    /* don't run the macro if there are no lines (macroinfo->data == NULL)!
     * this isn't exactly what Masm does; an empty 'WHILE 1'
     * will loop "forever" in Masm,
     */
    if ( macinfo.data ) /* added in v2.01 */
    switch ( directive ) {
    case T_REPEAT:
    case T_REPT:
	/* negative repeat counts are accepted and are treated like 0 */
	for ( ; m->sym.value < opnd.value; m->sym.value++ ) {
	    /* v2.10: Token_Count becomes volatile if MF_NOSAVE is set */
	    tokenarray[0].token = T_FINAL;
	    Token_Count = 0;
	    RunMacro( m, 0, tokenarray, NULL, MF_NOSAVE, &is_exitm );
	    if ( is_exitm )
		break;
	}
	break;
    case T_WHILE:
	while ( opnd.kind == EXPR_CONST && opnd.value != 0 ) {
	    RunMacro( m, Token_Count, tokenarray, NULL, 0, &is_exitm );
	    if ( is_exitm )
		break;
	    i = arg_loc;
	    if ( EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) == ERROR )
		break;
	    m->sym.value++;
	}
	break;
    case T_FORC:
    case T_IRPC:
	for( ptr = parmstring; *ptr; ptr++, m->sym.value++ ) {
	    tokenarray[0].token = T_STRING;
	    tokenarray[0].string_delim = NULLC;
	    tokenarray[0].string_ptr = buffer;
	    tokenarray[0].tokpos = buffer;
	    tokenarray[1].token = T_FINAL;
	    buffer[2] = NULLC;
	    Token_Count = 1;
	    if ( *ptr == '!' ) {
		buffer[0] = *ptr++;
		buffer[1] = *ptr;
		if ( *ptr == NULLC ) /* ensure the macro won't go beyond the 00 */
		    ptr--;
		tokenarray[0].stringlen = 2;
		tokenarray[1].tokpos = buffer+2;
	    } else if ( islspace( *ptr ) ) {
		buffer[0] = '!';
		buffer[1] = *ptr;
		tokenarray[0].stringlen = 2;
		tokenarray[1].tokpos = buffer+2;
	    } else {
		buffer[0] = *ptr;
		tokenarray[0].stringlen = 1;
		tokenarray[1].tokpos = buffer+1;
		buffer[1] = NULLC;
	    }
	    RunMacro( m, 0, tokenarray, NULL, MF_NOSAVE, &is_exitm );
	    if ( is_exitm )
		break;
	}
	break;
    default: /* T_FOR, T_IRP */
	i = Token_Count + 1;
	Token_Count = Tokenize( parmstring, i, tokenarray, TOK_RESCAN | TOK_NOCURLBRACES );

	/* v2.09: if a trailing comma is followed by white space(s), add a blank token */
	if ( i != Token_Count && tokenarray[Token_Count-1].token == T_COMMA &&
	    *(tokenarray[Token_Count-1].tokpos+1) ) {
	    tokenarray[Token_Count].token = T_STRING;
	    tokenarray[Token_Count].string_delim = NULLC;
	    tokenarray[Token_Count].stringlen = strlen( tokenarray[Token_Count].tokpos );
	    tokenarray[Token_Count+1].tokpos = tokenarray[Token_Count].tokpos + tokenarray[Token_Count].stringlen;
	    Token_Count++;
	    tokenarray[Token_Count].token = T_FINAL;
	}

	/* a FOR/IRP parameter can be a macro function call */
	/* that's why the macro calls must be run synchronously */
	/* v2.05: reset an optional VARARG attribute for the macro
	 * parameter.
	 * take care of a trailing comma, this is to make another
	 * RunMacro() call with a "blank" argument.
	 */
	m->sym.mac_vararg = FALSE;
	/* v2.09: flag MF_IGNARGS introduced. This allows RunMacro() to
	 * parse the full argument and trigger macro expansion if necessary.
	 * No need anymore to count commas here. */
	for( ; i < Token_Count; i++, m->sym.value++ ) {
	    i = RunMacro( m, i, tokenarray, NULL, MF_IGNARGS, &is_exitm );
	    if ( i < 0 || is_exitm )
		break;
	}
    }
    ReleaseMacroData( m );
    return( NOT_ERROR );
}
