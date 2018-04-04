#include <string.h>
#include <globals.h>
#include <types.h>
#include <hllext.h>

int PragmaDirective( int i, struct asm_tok tokenarray[] )
{
    int  rc = NOT_ERROR;
    char *p, *q, *s;

    i++;
    p = tokenarray[i].string_ptr;
    i++;
    if ( tokenarray[i].token == T_OP_BRACKET )
        i++;
    q = "dw";
    if ( ModuleInfo.Ofssize == USE32 )
        q = "dd";
    else if ( ModuleInfo.Ofssize == USE64 )
        q = "dq";
    s = "EXIT";
    if ( _stricmp(p, "init" ) == 0 )
        s = "INIT";
    AddLineQueueX( "_%s segment PARA FLAT PUBLIC '%s'", s, s );
    AddLineQueueX( " %s %s", q, tokenarray[i].string_ptr );
    i++;
    if ( tokenarray[i].token == T_COMMA )
        i++;
    AddLineQueueX( " %s %s", q, tokenarray[i].string_ptr );
    AddLineQueueX( "_%s ends", s );

    if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 );
    if ( is_linequeue_populated() )
        RunLineQueue();
    return rc;
}
