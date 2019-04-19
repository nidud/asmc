#include <globals.h>
#include <hllext.h>

int FASTCALL DelayExpand( struct asm_tok tokenarray[] )
{
    int i;
    int bracket;

    if ( ModuleInfo.strict_masm_compat == 1 )
	return 0;
    if ( !( tokenarray[0].hll_flags & T_HLL_DELAY ) )
	return 0;
    if ( Parse_Pass != PASS_1 )
	return 0;
    if ( NoLineStore != 0 )
	return 0;

    for ( i = 0;; ) {
	if ( i >= Token_Count ) {
	    tokenarray[0].hll_flags |= T_HLL_DELAYED;
	    return 1;
	}
	if ( !( tokenarray[++i].hll_flags & T_HLL_MACRO ) )
	    continue;
	if ( tokenarray[i].token == T_OP_BRACKET )
	    break;
    }

    bracket = 1; /* one open bracket found */
    for(;;) {
	if ( ++i >= Token_Count ) {
	    tokenarray[0].hll_flags |= T_HLL_DELAYED;
	    return 1;
	}
	if ( tokenarray[i].token == T_OP_BRACKET ) {
	    bracket++;
	} else if ( tokenarray[i].token == T_CL_BRACKET ) {
	    bracket--;
	} else if ( tokenarray[i].token == T_STRING && bracket ) {

	    if ( tokenarray[i].string_ptr[0] != '<' &&
		 tokenarray[i].tokpos[0] == '<') {
		asmerr( 7008, tokenarray[i].tokpos );
		return 0;
	    }
	}
    }
    return 0;
}
