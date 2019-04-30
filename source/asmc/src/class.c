#include <string.h>
#include <globals.h>
#include <hllext.h>
#include <types.h>
//
// item for .CLASS, .ENDS, and .COMDEF
//
struct com_item {
    int     cmd;
    char   *class;
    int     langtype;
};

static void AddVirtualTable(void)
{
    int i;
    char l_p[16];
    char l_t[16];
    struct com_item *p;

    p = ModuleInfo.g.ComStack;
    AddLineQueueX( "%s ends", p->class );

    if ( p->cmd == T_DOT_CLASS ) {

        i = 4;
        if ( ModuleInfo.Ofssize == USE64 )
            i = 8;
        AddLineQueueX( "%sVtbl struct %d", p->class, i );

        ModuleInfo.class_label++;
        sprintf( l_t, "T$%04X", ModuleInfo.class_label );
        sprintf( l_p, "P$%04X", ModuleInfo.class_label );

        if ( p->langtype )
            AddLineQueueX( "%s typedef proto %r :ptr %s", l_t, p->langtype, p->class );
        else
            AddLineQueueX( "%s typedef proto :ptr %s", l_t, p->class );
        AddLineQueueX( "%s typedef ptr %s", l_p, l_t );
        AddLineQueueX( "Release %s ?", l_p );
    } else {
        AddLineQueueX( "%sVtbl struct", p->class );
    }
}

int ProcType(int i, struct asm_tok tokenarray[], char *buffer)
{
    int     rc = NOT_ERROR;
    char    l_p[16];
    char    l_t[16];
    char    language[32];
    char    *p, *id = tokenarray[i-1].string_ptr;
    int     x, q, IsCom = 0;
    struct  com_item *o = ModuleInfo.g.ComStack;

    ModuleInfo.class_label++;
    sprintf(l_t, "T$%04X", ModuleInfo.class_label );
    sprintf(l_p, "P$%04X", ModuleInfo.class_label );

    p = CurrStruct->sym.name;
    x = strlen(p);

    if ( x > 4 ) {

        p += x - 4;
        if ( _memicmp(p, "Vtbl", 4) == 0 )
            IsCom++;
    }

    if ( !IsCom && o ) {

        if ( Token_Count > 2 && tokenarray[i+1].tokval == T_LOCAL ) {

            i++;
        } else {

            AddVirtualTable();
            IsCom++;
        }
    }

    strcpy(buffer, l_t);
    strcat(buffer, " typedef proto");
    if ( o && o->cmd == T_DOT_COMDEF )
        strcat(buffer, " WINAPI");

    i++;
    q = 0;

    if ( tokenarray[i].token != T_FINAL ) {

        if ( IsCom ) {

            if ( tokenarray[i].tokval >= T_CCALL && tokenarray[i].tokval <= T_VECTORCALL )
                q = 1;
            if ( tokenarray[i+1].token == T_FINAL || q ||
               ( tokenarray[i].token != T_COLON && tokenarray[i+1].token != T_COLON ) ) {
                strcat(buffer, " ");
                strcat(buffer, tokenarray[i].string_ptr);
                i++;
            } else if ( !q && o && o->langtype ) {
                GetResWName( o->langtype, language );
                strcat( buffer, " " );
                strcat( buffer, language );
            }
            q = 0;
        }

        for ( x = i; tokenarray[x].token != T_FINAL; x++ ) {

            if ( tokenarray[x].token == T_COLON ) {

                q++;
                break;
            }
        }
    } else if ( IsCom && o && o->langtype ) {

        GetResWName( o->langtype, language );
        strcat( buffer, " " );
        strcat( buffer, language );
    }

    if ( IsCom ) {

        strcat(buffer, " :ptr");

        if ( o ) {

            if ( o->cmd == T_DOT_CLASS ) {

                strcat(buffer, " ");
                strcat(buffer, o->class);
            }
        }
        if ( q )
            strcat(buffer, ",");
    }

    if ( q ) {

        strcat(buffer, " ");
        strcat(buffer, tokenarray[i].tokpos);
    }

    AddLineQueue( buffer );
    AddLineQueueX( "%s typedef ptr %s", l_p, l_t );
    AddLineQueueX( "%s %s ?", id, l_p );

    if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 );
    if ( is_linequeue_populated() )
        RunLineQueue();
    return rc;
}

int ClassDirective( int i, struct asm_tok tokenarray[] )
{
    int     rc = NOT_ERROR;
    int     x,q,cmd,args;
    char    buffer[MAX_LINE_LEN];
    char *  p;
    struct  com_item *o = ModuleInfo.g.ComStack;

    cmd = tokenarray[i].tokval;
    i++;

    switch ( cmd ) {
    case T_DOT_ENDS:

        if ( !o )
            return asmerr(1011);

        p = CurrStruct->sym.name;
        x = strlen(p);
        if ( x > 4 && _memicmp(p + x - 4, "Vtbl", 4) != 0 ) {

            AddVirtualTable();
            AddLineQueueX( "%sVtbl ends", o->class );
        } else {
            AddLineQueueX( "%s ends", p );
        }
        ModuleInfo.g.ComStack = NULL;
        break;

    case T_DOT_COMDEF:
    case T_DOT_CLASS:

        if ( o )
            return asmerr(1011);

        o = LclAlloc( sizeof( struct com_item ) );
        ModuleInfo.g.ComStack = o;
        o->cmd = cmd;
        o->langtype = 0;
        p = tokenarray[i].string_ptr;
        o->class = LclAlloc( strlen(p) + 1 );
        strcpy(o->class, p);
        strcat( strcpy( buffer, "LP" ), p );

        if ( cmd == T_DOT_CLASS )
            _strupr( buffer );

        args = i + 1;
        if( tokenarray[args].token == T_ID && (tokenarray[args].string_ptr[0] | 0x20) == 'c'
            && tokenarray[args].string_ptr[1] == '\0') {
            tokenarray[args].token = T_RES_ID;
            tokenarray[args].tokval = T_CCALL;
            tokenarray[args].bytval = 1;
        }

        if ( tokenarray[args].token != T_FINAL && tokenarray[args].tokval >= T_CCALL
            && tokenarray[args].tokval <= T_VECTORCALL ) {
            o->langtype = tokenarray[args].tokval;
            args++;
        }

        if ( cmd == T_DOT_CLASS ) {

            AddLineQueueX( "%s typedef ptr %s", buffer, p );
            AddLineQueueX( "%sVtbl typedef ptr %sVtbl", buffer, p );

            for ( x = 0, q = args; tokenarray[q].token != T_FINAL; q++ ) {

                if ( tokenarray[q].token == T_COLON ) {
                    x++;
                    break;
                }
            }

            if ( o->langtype ) {
                if ( x )
                    AddLineQueueX( "%s::%s proto %s %s", p, p, tokenarray[args-1].string_ptr, tokenarray[args].tokpos );
                else
                    AddLineQueueX( "%s::%s proto %s", p, p, tokenarray[args-1].string_ptr );
            } else {
                if ( x )
                    AddLineQueueX( "%s::%s proto %s", p, p, tokenarray[args].tokpos );
                else
                    AddLineQueueX( "%s::%s proto", p, p );
            }
        }

        x = 4;
        if ( ModuleInfo.Ofssize == USE64 )
            x = 8;

        if ( cmd == T_DOT_CLASS ) {

            AddLineQueueX( "%s struct %d", p, x );
            AddLineQueueX( "lpVtbl %sVtbl ?", buffer );
        } else {
            AddLineQueueX( "%s struct", p );
            AddLineQueue ( "lpVtbl PVOID ?" );
        }
        break;
    }

    if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 );
    if ( is_linequeue_populated() )
        RunLineQueue();
    return rc;
}

void ClassInit(void)
{
    ModuleInfo.class_label = 0;
}

int ClassCheckOpen(void)
{
    if ( ModuleInfo.g.ComStack )
        return asmerr( 1010, ".comdef-.classdef-.ends" );
    return NOT_ERROR;
}
