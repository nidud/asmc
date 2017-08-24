/*
 * UNDEF directive.
 * syntax: UNDEF symbol [, symbol, ... ]
 */

#include <globals.h>
#include <parser.h>

int UndefDirective( int i, struct asm_tok tokenarray[] )
{
    struct asym *sym;

    i++; /* skip directive */
    do {
	if ( tokenarray[i].token != T_ID ) {
	    return( asmerr(2008, tokenarray[i].string_ptr ) );
	}
	sym = SymSearch( tokenarray[i].string_ptr );
	if ( sym == NULL ) {
	    return( asmerr( 2006, tokenarray[i].string_ptr ) );
	}
	sym->state = SYM_UNDEFINED;
	i++;
	if ( i < Token_Count ) {
	    if ( tokenarray[i].token != T_COMMA || tokenarray[i+1].token == T_FINAL ) {
		return( asmerr(2008, tokenarray[i].tokpos ) );
	    }
	    i++;
	}
    } while ( i < Token_Count );

    return( NOT_ERROR );
}

