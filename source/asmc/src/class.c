#include <string.h>
#include <globals.h>
#include <hllext.h>
#include <types.h>
//
// item for .CLASS, .ENDS, and .COMDEF
//
struct com_item {
    int         cmd;
    char        *class;
    int         langtype;
    struct asym *sym;
};

int ProcType(int i, struct asm_tok tokenarray[], char *buffer)
{
    int     rc = NOT_ERROR;
    char    l_p[16];
    char    l_t[16];
    char    language[32];
    char    pubclass[128];
    char    *p, *id = tokenarray[i-1].string_ptr;
    int     x, q, IsCom = 0;
    struct  com_item *o = ModuleInfo.g.ComStack;
    struct  asym *sym;

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

            AddLineQueueX( "%s ends", o->class );
            AddLineQueueX( "%sVtbl struct", o->class );

            /* v2.30.32 - : public class */

            sym = ModuleInfo.g.ComStack->sym;

            if ( sym != NULL ) {

                sym = SymFind( strcat( strcpy( pubclass, sym->name ), "Vtbl" ) );

                if ( sym != NULL ) {

                    if ( sym->total_size )
                        AddLineQueueX( "%s <>", pubclass );

                } else {
                    rc = asmerr( 2006, pubclass );
                }
            }

            IsCom++;
        }
    }

    strcpy(buffer, l_t);
    strcat(buffer, " typedef proto");
    if ( o && o->cmd == T_DOT_COMDEF ) {
        if ( ModuleInfo.Ofssize == USE32 && ModuleInfo.langtype != LANG_STDCALL )
            strcat(buffer, " stdcall");
    }

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
    int rc = NOT_ERROR;
    int x,q,cmd,args;
    char LPClass[64];
    char LPClassVtbl[64];
    char *p;
    char *public_class;
    struct asym *sym;
    struct com_item *o = ModuleInfo.g.ComStack;

    cmd = tokenarray[i].tokval;
    i++;

    switch ( cmd ) {
    case T_DOT_ENDS:
        if ( ModuleInfo.g.ComStack == NULL ) {
            if ( CurrStruct )
                return ( asmerr( 1011 ) );
            break;
        }
        ModuleInfo.g.ComStack = NULL;
        AddLineQueueX( "%s ends", CurrStruct->sym.name );
        break;

    case T_DOT_COMDEF:
    case T_DOT_CLASS:
        if ( ModuleInfo.g.ComStack != NULL )
            return ( asmerr( 1011 ) );

        o = LclAlloc( sizeof( struct com_item ) );
        ModuleInfo.g.ComStack = o;
        o->cmd = cmd;
        o->langtype = 0;
        p = tokenarray[i].string_ptr;
        o->class = LclAlloc( strlen(p) + 1 );
        strcpy(o->class, p);
        strcat( strcpy( LPClass, "LP" ), p );
        _strupr( LPClass );

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

        AddLineQueueX( "%sVtbl typedef ptr %sVtbl", LPClass, p );

        if ( cmd == T_DOT_CLASS ) {
            AddLineQueueX( "%s typedef ptr %s", LPClass, p );
        }

        sym = NULL;
        public_class = NULL;

        for ( x = 0, q = args; tokenarray[q].token != T_FINAL; q++ ) {

            if ( tokenarray[q].token == T_COLON ) {

                /* v2.30.32 - : public class */

                if ( tokenarray[q+1].token  == T_DIRECTIVE &&
                     tokenarray[q+1].tokval == T_PUBLIC ) {

                    public_class = tokenarray[q].tokpos;
                    sym = SymFind( tokenarray[q+2].string_ptr );
                    if ( sym == NULL )
                        return asmerr( 2006, tokenarray[q+2].string_ptr );

                    public_class[0] = '\0';
                    ModuleInfo.g.ComStack->sym = sym;
                    break;

                } else {

                    x++;
                }
            }
        }

        if ( cmd == T_DOT_CLASS ) {
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

            if ( public_class != NULL )
                public_class[0] = ':';

            x = 4;
            if ( ModuleInfo.Ofssize == USE64 )
                x = 8;
            if ( ( 1 << ModuleInfo.fieldalign ) < x )
                AddLineQueueX( "%s struct %d", p, x );
            else
                AddLineQueueX( "%s struct", p );
        } else
            AddLineQueueX( "%s struct", p );

        if ( sym != NULL )
            AddLineQueueX( "%s <>", sym->name );
        else
            AddLineQueueX( "lpVtbl %sVtbl ?", LPClass );
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
