/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	processes directive .SAFESEH
*
****************************************************************************/

#include <ctype.h>

#include <globals.h>
#include <memalloc.h>
#include <parser.h>

/* .SAFESEH works for coff format only.
 * syntax is: .SAFESEH handler
 * <handler> must be a PROC or PROTO
 */

ret_code SafeSEHDirective( int i, struct asm_tok tokenarray[] )
/*************************************************************/
{
    struct asym	   *sym;
    struct qnode   *node;

    if ( Options.output_format != OFORMAT_COFF ) {
	if ( Parse_Pass == PASS_1)
	    asmerr( 8015, "coff" );
	return( NOT_ERROR );
    }
    if ( Options.safeseh == FALSE ) {
	if ( Parse_Pass == PASS_1)
	    asmerr( 8015, "safeseh" );
	return( NOT_ERROR );
    }
    i++;
    if ( tokenarray[i].token != T_ID ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    sym = SymSearch( tokenarray[i].string_ptr );

    /* make sure the argument is a true PROC */
    if ( sym == NULL || sym->state == SYM_UNDEFINED ) {
	if ( Parse_Pass != PASS_1 ) {
	    return( asmerr( 2006, tokenarray[i].string_ptr ) );
	}
    } else if ( sym->isproc == FALSE ) {
	return( asmerr( 3017, tokenarray[i].string_ptr ) );
    }

    if ( Parse_Pass == PASS_1 ) {
	if ( sym ) {
	    for ( node = ModuleInfo.g.SafeSEHQueue.head; node; node = node->next )
		if ( node->elmt == sym )
		    break;
	} else {
	    sym = SymCreate( tokenarray[i].string_ptr );
	    node = NULL;
	}
	if ( node == NULL ) {
	    sym->used = TRUE; /* make sure an external reference will become strong */
	    QAddItem( &ModuleInfo.g.SafeSEHQueue, sym );
	}
    }
    i++;
    if ( tokenarray[i].token != T_FINAL ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }

    return( NOT_ERROR );
}

