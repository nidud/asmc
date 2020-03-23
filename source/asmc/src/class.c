#include <string.h>
#include <globals.h>
#include <hllext.h>
#include <types.h>
#include <macro.h>
//
// item for .CLASS, .ENDS, and .COMDEF
//
struct com_item {
    int         cmd;
    char        *class;
    int         langtype;
    struct asym *sym;
};

static int OpenVtbl(struct com_item* p)
{
    char pubclass[64];
    struct asym *sym;

    AddLineQueueX( "%sVtbl struct", p->class );

    /* v2.30.32 - : public class */

    sym = p->sym;
    if ( sym == NULL )
        return 0;

    sym = SymFind( strcat( strcpy( pubclass, sym->name ), "Vtbl" ) );
    if ( sym == NULL )
        return asmerr( 2006, pubclass );

    if ( sym->total_size ) {
        AddLineQueueX( "%s <>", pubclass );
        return 1;
    }
    return 0;
}

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
            rc = OpenVtbl(o);
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

int get_operator(char *token)
{
    switch ( token[0] ) {
    case '=':
        return T_EQU;
    case '&':
        if ( token[1] == '~' )
            return T_ANDN;
        return T_AND;
    case '|':
        return T_OR;
    case '^':
        return T_XOR;
    case '*':
        return T_MUL;
    case '/':
        return T_DIV;
    case '<':
        if ( token[1] == '<' )
            return T_SHL;
        break;
    case '>':
        if ( token[1] == '>' )
            return T_SHR;
        break;
    case '+':
        if ( token[1] == '+' )
            return T_INC;
        return T_ADD;
    case '-':
        if ( token[1] == '-' )
            return T_DEC;
        return T_SUB;
    case '~':
        return T_NOT;
    case '%':
        return T_MOD;
    }
    return 0;
}

void MacroInline( char *name, int args, char *data, int vargs )
{
    int i;
    char *p, *q;
    char macroargs[256];

    if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 );
    RunLineQueue();

    if ( vargs )
        AddLineQueueX( "%s macro this:vararg", name );
    else {
        for ( i = 1, p = strcpy( macroargs, "this" ) + 4; i < args; i++ )
            p += sprintf( p, ", _%u", i );
        AddLineQueueX( "%s macro %s", name, macroargs );
    }

    for ( p = data; ( q = strchr( p, '\n' ) ) != NULL; ) {

        *q = '\0';
        if ( *p )
            AddLineQueue( p );
        *q++ = '\n';
        p = q;
    }
    if ( *p )
        AddLineQueue( p );
    AddLineQueue( "endm" );
    MacroLineQueue();
}

int ClassDirective( int i, struct asm_tok tokenarray[] )
{
    int rc = NOT_ERROR;
    int x,q,cmd,args;
    char clname[64];
    char *p;
    char *ptr;
    char *public_class;
    struct asym *sym;
    struct com_item *o = ModuleInfo.g.ComStack;
    int is_id;
    int is_equ;
    int is_vararg;
    char token[64];
    char name[128];
    char macro[128];
    uint_32 u;

    cmd = tokenarray[i].tokval;
    i++;

    switch ( cmd ) {
    case T_DOT_ENDS:
        if ( o == NULL ) {
            if ( CurrStruct )
                return ( asmerr( 1011 ) );
            break;
        }
        ModuleInfo.g.ComStack = NULL;
        AddLineQueueX( "%s ends", CurrStruct->sym.name );
        if ( o->sym ) {
            if ( !strcmp( o->class, CurrStruct->sym.name ) ) {
                OpenVtbl(o);
                AddLineQueueX( "%sVtbl ends", CurrStruct->sym.name );
            }
        }
        break;

    case T_DOT_OPERATOR:
        if ( o == NULL ) {
            if ( CurrStruct )
                return ( asmerr( 1011 ) );
            break;
        }

        /* .operator + :type, :type */
        is_id = 0;  /* name proc :qword, :qword */
        is_equ = 0; /* [m|r]add88 proc :qword, :qword */
        is_vararg = 0;
        p = tokenarray[i].tokpos;
        x = get_operator( p );
        switch ( x ) {
        case 0:
            if ( tokenarray[i].token != T_ID )
                return asmerr( 1011 );
            is_id++;
            strcpy( token, tokenarray[i].string_ptr );
            x = 0;
            break;
        case T_EQU:
            is_equ++;
            break;
        case T_ANDN:
        case T_INC:
        case T_DEC:
            i++;
            break;
        }
        if ( x ) {
            token[0] = 'r';
            GetResWName( x, &token[1] );
        }
        i++;
        if ( tokenarray[i].token == T_DIRECTIVE && tokenarray[i].tokval == T_EQU ) {
            i++;
            is_equ++;
        }
        if ( p[1] == '=' || p[2] == '=' )
            is_equ++;
        if ( is_equ )
            token[0] = 'm';
        clname[0] = 0;
        p = NULL;
        x = i;
        ptr = clname;
        for ( args = 1; tokenarray[x].token != T_FINAL; x++ ) {
            if ( tokenarray[x].token == T_STRING && tokenarray[x].bytval == '{' ) {
                if ( tokenarray[x-1].token == T_RES_ID && tokenarray[x-1].tokval == T_VARARG )
                    is_vararg++;
                p = tokenarray[x].string_ptr;
                tokenarray[x].tokpos[0] = '\0';
                tokenarray[x].token = T_FINAL;
                break;
            }
            if ( tokenarray[x].token == T_COLON ) {
                int size = 0;
                if ( tokenarray[x+1].token == T_STYPE ) {
                    size = SizeFromMemtype(GetMemtypeSp(tokenarray[x+1].tokval), USE_EMPTY, 0 );
                } else if ( tokenarray[x+1].token == T_ID ) {
                    sym = SymFind( tokenarray[x+1].string_ptr );
                    if ( sym )
                        size = SizeFromMemtype( sym->mem_type, USE_EMPTY, sym->type );
                }
                if ( size == 0 || size > 64 ) {
                    size = 4;
                    if ( ModuleInfo.Ofssize == USE64 )
                        size = 8;
                }
                if ( args < 4 )
                    ptr += sprintf(ptr, "%u", size);
                args++;
            }
        }
        if ( is_id )
            clname[0] = '\0';

        sprintf( name, "%s%s", token, clname );
        ptr = o->class;
        if ( o->sym )
            ptr = o->sym->name;
        sym = SymFind( strcat( strcpy( clname, ptr ), "Vtbl" ) );
        if ( sym == NULL )
            sym = (struct asym *)CurrStruct;
        if ( !SearchNameInStruct( sym, name, &u, 0 ) )
            AddLineQueueX( " %s proc %s", name, tokenarray[i].tokpos );
        if ( p == NULL || Parse_Pass > PASS_1 )
            break;
        /*
         * .operator + :type, :type {
         *   add _1,_2
         *   ...
         *   exitm<...>
         * }
         */
        sprintf( macro, "%s_%s", ptr, name );
        MacroInline( macro, args, p, is_vararg );
        return rc;

    case T_DOT_COMDEF:
    case T_DOT_CLASS:
    case T_DOT_TEMPLATE:
        if ( ModuleInfo.g.ComStack != NULL )
            return ( asmerr( 1011 ) );

        o = LclAlloc( sizeof( struct com_item ) );
        ModuleInfo.g.ComStack = o;
        o->cmd = cmd;
        o->langtype = 0;
        p = tokenarray[i].string_ptr;
        o->class = LclAlloc( strlen(p) + 1 );
        strcpy(o->class, p);
        strcat( strcpy( clname, "LP" ), p );
        _strupr( clname );

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

        if ( cmd != T_DOT_TEMPLATE ) {

            AddLineQueueX( "%sVtbl typedef ptr %sVtbl", clname, p );
            if ( cmd == T_DOT_CLASS )
                AddLineQueueX( "%s typedef ptr %s", clname, p );
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
        else if ( cmd != T_DOT_TEMPLATE )
            AddLineQueueX( "lpVtbl %sVtbl ?", clname );
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
