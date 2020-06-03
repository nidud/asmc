#include <string.h>
#include <globals.h>
#include <hllext.h>
#include <types.h>
#include <macro.h>

/* item for .CLASS, .ENDS, and .COMDEF */
struct com_item {
    int cmd;
    char *class;
    int langtype;
    struct asym *sym;
    int type;
    int vector;
};

static void ClassProto(char *name, int langtype, char *args, int type)
{
    if ( langtype )
        AddLineQueueX( "%s %r %r %s", name, type, langtype, args );
    else
        AddLineQueueX( "%s %r %s", name, type, args );
}

static void ClassProto2(char *name, char *method, struct com_item *item, char *args)
{
    char buffer[128];

    strcpy( buffer, name );
    if ( item->vector )
        strcat( buffer, "_" );
    else
        strcat( buffer, "::" );
    strcat( buffer, method );
    ClassProto( buffer, item->langtype, args, T_PROTO );
}

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

static int get_operator(char *token)
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

static int size_from_token( struct asm_tok *tokenarray )
{
    struct asym *sym;

    if ( tokenarray->token == T_STYPE )
        return SizeFromMemtype( GetMemtypeSp( tokenarray->tokval ), USE_EMPTY, 0 );
    else if ( tokenarray->token == T_ID ) {
        sym = SymFind( tokenarray->string_ptr );
        if ( sym )
            return SizeFromMemtype( sym->mem_type, USE_EMPTY, sym->type );
    } else if ( tokenarray->token == T_REG )
        return SizeFromRegister( tokenarray->tokval );
    return 0;
}

static int get_param_size( struct asm_tok *tokenarray )
{
    int size = size_from_token( tokenarray );

    if ( size == 0 || size > 64 )
        return ( 2 << ModuleInfo.Ofssize );

    return size;
}

static int get_token_size( struct asm_tok *tokenarray, char *name )
{
    struct asym *sym;
    int size = size_from_token( tokenarray );

    if ( size )
        return size;

    sym = SymFind( name );
    if ( sym )
        size = SizeFromMemtype( sym->mem_type, USE_EMPTY, sym->type );

    if ( size == 0 || size > 64 )
        return ( 2 << ModuleInfo.Ofssize );

    return size;
}

static int get_param_name( int i, struct asm_tok tokenarray[], char *token, char *size,
    int *count, int *isid, int *context )
{
    int k, q;
    struct com_item *cs;
    char *tokpos = tokenarray[i].tokpos;

    *isid = 0;
    *size = '\0';
    *context = 0;
    *token = 'r';

    q = get_operator( tokpos );
    switch ( q ) {
    case 0:
        if ( tokenarray[i].token != T_ID ) {
            cs = ModuleInfo.g.ComStack;
            if ( !( cs && cs->type && \
                 ( tokenarray[i].token == T_STYPE || tokenarray[i].token == T_INSTRUCTION ) ) )
                return asmerr( 1011 );
        }
        strcpy( token, tokenarray[i].string_ptr );
        *isid = 1;
        break;
    case T_EQU:
        *token = 'm';
        break;
    case T_ANDN:
    case T_INC:
    case T_DEC:
        i++;
        break;
    }

    if ( q )
        GetResWName( q, &token[1] );
    i++;
    if ( tokenarray[i].token == T_DIRECTIVE && tokenarray[i].tokval == T_EQU ) {
        i++;
        *token = 'm';
    }
    if ( tokpos[1] == '=' || tokpos[2] == '=' )
        *token = 'm';

    for ( q = i, k = 1; tokenarray[q].token != T_FINAL; q++ ) {
        if ( tokenarray[q].token == T_STRING && tokenarray[q].bytval == '{' ) {
            *context = q;
            break;
        } else if ( tokenarray[q].token == T_COLON ) {
            if ( k < 4 )
                size += sprintf( size, "%u", get_param_size( &tokenarray[q+1] ) );
            k++;
        }
    }
    *count = k;
    return i;
}

static int GetClassVectorSize( char *name )
{
    int retval = 0;
    struct asym *sym = SymFind( name );

    if ( sym ) {

        retval = SizeFromMemtype( sym->mem_type, USE_EMPTY, sym->type );
        switch ( retval ) {
        case 2:
        case 4:
        case 8:
            if ( sym->mem_type & MT_FLOAT )
                retval = 16;
        case 1:
        case 16:
        case 32:
        case 64:
            break;
        default:
            retval = 0;
            break;
        }
    }
    return retval;
}

static int GetClassVectorToken( char *name, int *size )
{
    int reg = T_XMM0;

    *size = GetClassVectorSize( name );

    switch ( *size ) {
    case 1  : reg = T_AL;   break;
    case 2  : reg = T_AX;   break;
    case 4  : reg = T_EAX;  break;
    case 8  : reg = T_RAX;  break;
    case 16 : reg = T_XMM0; break;
    case 32 : reg = T_YMM0; break;
    case 64 : reg = T_ZMM0; break;
    }
    return reg;
}

static int GetClassVector( char *name, char *vector, int *reg )
{
    int size;

    *reg = GetClassVectorToken( name, &size );
    GetResWName( *reg, vector );
    return size;
}

int ParseOperator( char *cname, int i, struct asm_tok tokenarray[], char *buffer )
{
  int arg_count;
  int id;
  int j,k;
  int context;
  char name[16];
  char size[16];
  char curr[256];
  char vector[64];
  struct input_status oldstat;
  char *p;

    /* class :: + (...) / (...) */

    while ( 1 ) {

        i = get_param_name( i, tokenarray, name, size, &arg_count, &id, &context );
        if ( i = ERROR )
            return ERROR;

        if ( tokenarray[i].token != T_OP_BRACKET )
            return asmerr( 2008, tokenarray[i].string_ptr );

        j = i;
        for ( k = 0; tokenarray[i].token != T_FINAL; i++ ) {
            switch ( tokenarray[i].token ) {
            case T_OP_BRACKET:
                k++;
                break;
            case T_CL_BRACKET:
                k--;
                if ( k != 0 )
                    break;
                if ( tokenarray[i-1].token != T_OP_BRACKET )
                    arg_count++;
                i++;
                goto done;
            case T_COMMA:
                if ( k == 1 )
                    arg_count++;
                break;
            }
        }
done:
        p = buffer;
        if ( tokenarray[i].token != T_FINAL ) {
            p = curr;
            strcpy( p, cname );
            strcat( p, "_" );
        }
        strcat( p, &name[1] );
        strcat( p, "( " );

        if ( GetClassVector( cname, vector, &k ) >= 16 ) {
            strcat( p, vector );
            if ( arg_count > 1 )
                strcat( p, ", " );
        }

        if ( tokenarray[i].token == T_FINAL ) {
            strcat( p, tokenarray[j+1].tokpos );
            break;
        }

        p += strlen(p);
        k = ( tokenarray[i].tokpos - tokenarray[j+1].tokpos );
        memcpy( p, tokenarray[j+1].tokpos, k );
        p[k] = '\0';

        if ( Parse_Pass == PASS_1 ) {

            PushInputStatus( &oldstat );
            strcpy( ModuleInfo.currsource, curr );
            ModuleInfo.token_count =
            Tokenize( ModuleInfo.currsource, 0, ModuleInfo.tokenarray, TOK_DEFAULT );
            ParseLine( ModuleInfo.tokenarray );
            PopInputStatus( &oldstat );
        }
    }
    return i;
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
    int     IsType = 0;

    if ( o ) {

        if ( strcmp( id, o->class ) == 0 ) {

            ClassProto2( id, id, o, tokenarray[i+1].tokpos );
            goto done;
        }
    }

    p = CurrStruct->sym.name;
    x = strlen(p);

    if ( x > 4 ) {
        p += x - 4;
        if ( memcmp(p, "Vtbl", 4) == 0 )
            IsCom++;
    }
    if ( !IsCom && o ) {

        if ( o->type )
            IsType = 1;

        if ( Token_Count > 2 && tokenarray[i+1].tokval == T_LOCAL ) {
            i++;
        } else if ( IsType == 0 ) {
            AddLineQueueX( "%s ends", o->class );
            rc = OpenVtbl(o);
            IsCom++;
        }
    }

    ModuleInfo.class_label++;
    sprintf(l_t, "T$%04X", ModuleInfo.class_label );
    sprintf(l_p, "P$%04X", ModuleInfo.class_label );

    strcpy(buffer, l_t);
    strcat(buffer, " typedef proto");
    if ( o && o->cmd == T_DOT_COMDEF ) {
        if ( ModuleInfo.Ofssize == USE32 && ModuleInfo.langtype != LANG_STDCALL )
            strcat(buffer, " stdcall");
    }

    i++;
    q = 0;

    if ( tokenarray[i].token != T_FINAL ) {

        if ( IsCom || IsType ) {

            if ( tokenarray[i].tokval >= T_CCALL && tokenarray[i].tokval <= T_WATCALL )
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
    } else if ( ( IsType || IsCom ) && o && o->langtype ) {

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
    if ( o && o->type ) {
        AddLineQueueX( "%s::%s %s", o->class, id, buffer+15 );
    } else {
        AddLineQueue( buffer );
        AddLineQueueX( "%s typedef ptr %s", l_p, l_t );
        AddLineQueueX( "%s %s ?", id, l_p );
    }
done:
    if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 );
    if ( is_linequeue_populated() )
        RunLineQueue();
    return rc;
}

int ParseClass( int j, struct asm_tok tokenarray[], char *buffer )
{
    int     i,q,k;
    char *  clas;
    char *  name;
    int     tokval;
    struct  asym *sym;

    i = 0;
    q = ( tokenarray[j-1].tokpos - tokenarray[i].tokpos );
    if ( q ) {

        memcpy( buffer, tokenarray[i].tokpos, q );
        buffer[q] = ' ';
        buffer[q+1] = '\0';
    } else
        buffer[q] = '\0';

    if ( tokenarray[j].token != T_DBL_COLON )
        return 0;

    clas = tokenarray[j-1].string_ptr;
    name = tokenarray[j+1].string_ptr;

    q = get_operator( tokenarray[j+1].tokpos );
    k = 2;
    if ( q == T_ANDN || q == T_INC || q == T_DEC )
        k++;

    if ( tokenarray[j+k].tokval == T_ENDP || tokenarray[j+k].token == T_OP_BRACKET ) {

        tokval = q;
        strcat( buffer, clas );
        strcat( buffer, "_" );

        if ( tokval ) {
            j++;
            ParseOperator( clas, j, tokenarray, buffer );
        } else {
            strcat( buffer, name );
            strcat( buffer, " " );
            strcat( buffer, tokenarray[j+2].tokpos );
        }
        Token_Count = Tokenize( buffer, 0, tokenarray, TOK_DEFAULT );
        return 1;
    }

    tokval = tokenarray[j+2].tokval;
    if ( tokval != T_PROC && tokval != T_PROTO )
        return 0;

    /* class :: name proc syscall private uses a b c:dword, */

    strcpy( buffer, clas );
    strcat( buffer, "_" );
    strcat( buffer, name );
    strcat( buffer, " " );
    strcat( buffer, tokenarray[j+2].string_ptr );
    strcat( buffer, " " );

    i = j + 3;

    while ( tokenarray[i].token != T_FINAL &&
            tokenarray[i].token != T_COLON &&
            tokenarray[i+1].token != T_COLON ) {

        if ( tokenarray[i].token == T_STRING ) {

            if ( tokenarray[i].string_delim != '<' )
                break;

            strcat( buffer, "<" );
            strcat( buffer, tokenarray[i].string_ptr );
            strcat( buffer, "> " );

        } else {

            strcat( buffer, tokenarray[i].string_ptr );
            strcat( buffer, " " );
        }
        i++;
    }

    if ( tokenarray[i].token != T_FINAL && tokenarray[i+1].token == T_COLON ) {

        switch ( tokenarray[i].token ) {
        case T_ID:
            if ( tokval == T_PROC ) {
                k = _stricmp( tokenarray[i].string_ptr, "PRIVATE" );
                if ( k )
                    k = _stricmp( tokenarray[i].string_ptr, "EXPORT" );
                if ( k )
                    break;
            } else
                break;
        case T_INSTRUCTION:
        case T_REG:
        case T_DIRECTIVE:
        case T_STYPE:
        case T_RES_ID:
            strcat( buffer, tokenarray[i].string_ptr );
            strcat( buffer, " " );
            i++;
            break;
        }
    }

    if ( tokval == T_PROC )
        strcat( buffer, "this" );
    strcat( buffer, ":" );

    switch ( tokenarray[j-1].token ) {
      case T_INSTRUCTION:
      case T_REG:
      case T_DIRECTIVE:
      case T_STYPE:
      case T_RES_ID:
        break;
      case T_ID:
        sym = SymSearch( clas );
        if ( sym ) {
            if ( sym->state == SYM_TYPE && sym->typekind == TYPE_TYPEDEF )
                break;
        }
      default:
        strcat( buffer, "ptr " );
        break;
    }
    strcat( buffer, clas );

    if ( tokenarray[i].token != T_FINAL ) {
        if ( tokenarray[i].token == T_STRING && tokenarray[i].string_delim == '{' )
            strcat( buffer, " " );
        else
            strcat( buffer, ", " );
        strcat( buffer, tokenarray[i].tokpos );
    }
    strcpy( CurrSource, buffer );
    Token_Count = Tokenize( buffer, 0, tokenarray, TOK_DEFAULT );
    return 1;
}

char *ParseMacroArgs(char *buffer, int count, char *args)
{
    int i,x;
    char *p,*q,*s;

    for ( p = args, q = buffer, i = 1; i < count; i++ ) {

        q += sprintf( q, "_%u, ", i );
        s = p;
        if ( (p = strchr(p, ',')) != NULL)
            p++;
        else
            p += strlen(s);

        if ((s = strchr(s, '=')) != NULL) {

            if ( s < p ) {

                x = p - s;
                memcpy(q-1, s, x);
                *(q-2) = ':';
                *(q+x) = '\0';
                q += x;
            }
        }
    }
    return q;
}

void MacroInline( char *name, int count, char *args, char *data, int vargs )
{
    int i;
    char *p, *q;
    char macroargs[256];
    struct com_item *o;

    if ( Parse_Pass > PASS_1 )
        return;

    if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 );
    RunLineQueue();

    o = ModuleInfo.g.ComStack;
    if ( o && o->vector ) {
        macroargs[0] = '\0';
        p = macroargs;
        for ( i = 1; i < count; i++ )
            p += sprintf( p, "_%u, ", i );
        strcat( p, "this:=<" );
        strcat( p, GetResWName( o->vector, NULL ) );
        strcat( p, ">" );
    } else {
        for ( i = 1, p = strcpy( macroargs, "this" ) + 4; i < count; i++ )
            p += sprintf( p, ", _%u", i );
    }

    if ( vargs )
        AddLineQueueX( "%s macro this:vararg", name );
    else {
        for ( i = 1, p = strcpy( macroargs, "this" ) + 4; i < count; i++ )
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
    int cmd = tokenarray[i].tokval;
    int x,q,args;
    char clname[64];
    char *p;
    char *ptr;
    char *public_class;
    struct asym *sym;
    struct com_item *o = ModuleInfo.g.ComStack;
    int is_id;
    int is_vararg;
    char token[64];
    char name[128];
    uint_32 u;
    int context;

    i++;

    switch ( cmd ) {
    case T_DOT_ENDS:
        if ( o == NULL ) {
            if ( CurrStruct )
                return ( asmerr( 1011 ) );
            break;
        }
        ModuleInfo.g.ComStack = NULL;
        if ( o->type ) {
            break;
        }
        AddLineQueueX( "%s ends", CurrStruct->sym.name );
        if ( o->sym ) {
            if ( !strcmp( o->class, CurrStruct->sym.name ) ) {
                OpenVtbl(o);
                AddLineQueueX( "%sVtbl ends", CurrStruct->sym.name );
            }
        }
        break;

    case T_DOT_OPERATOR:
        if ( o && o->type )
            ;
        else if ( o == NULL || CurrStruct == NULL )
            return ( asmerr( 1011 ) );

        /* .operator + :type, :type */
        is_vararg = 0;
        i = get_param_name( i, tokenarray, token, clname, &args, &is_id, &context );
        if ( i == ERROR )
            return ERROR;

        p = NULL;
        if ( context ) {
            if ( tokenarray[context].token == T_STRING &&
                 tokenarray[context].bytval == '{' ) {
                if ( tokenarray[context-1].token == T_RES_ID &&
                     tokenarray[context-1].tokval == T_VARARG )
                    is_vararg++;
                p = tokenarray[context].string_ptr;
                ptr = tokenarray[context].tokpos;
                *ptr = 0;
                while ( *(ptr-1) <= ' ' ) {
                    if ( ptr <= tokenarray[context-1].tokpos )
                        break;
                    ptr--;
                }
                *ptr = 0;
                tokenarray[context].token = T_FINAL;
            }
        }
        ptr = token;
        if ( is_id || o->type ) {
            clname[0] = 0;
            if ( o->type && is_id == 0 )
                ptr++;
        }
        sprintf( name, "%s%s", ptr, clname );

        ptr = o->class;
        if ( o->sym )
            ptr = o->sym->name;

        sym = SymFind( strcat( strcpy( clname, ptr ), "Vtbl" ) );
        if ( sym == NULL )
            sym = (struct asym *)CurrStruct;

        if ( sym != NULL ) {
            if ( SearchNameInStruct( sym, name, &u, 0 ) == NULL ) {
                if ( strcmp( name, ptr ) != 0 )
                    ClassProto( name, o->langtype, tokenarray[i].tokpos, T_PROC );
                else
                    ClassProto2( ptr, name, o, tokenarray[i].tokpos );
            }
        } else if ( o->type )
            ClassProto2( ptr, name, o, tokenarray[i].tokpos );


        if ( p == NULL || Parse_Pass > PASS_1 )
            break;

        /* .operator + :type { ... } */

        sprintf( token, "%s_%s", ptr, name );
        MacroInline( token, args, tokenarray[i].tokpos, p, is_vararg );
        return rc;

    case T_DOT_COMDEF:
    case T_DOT_CLASS:
    case T_DOT_TEMPLATE:
        if ( o != NULL )
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
            && tokenarray[args].tokval <= T_WATCALL ) {
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
#if 0
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
#endif
            if ( public_class != NULL )
                public_class[0] = ':';

            x = 4;
            if ( ModuleInfo.Ofssize == USE64 )
                x = 8;
            if ( ( 1 << ModuleInfo.fieldalign ) < x )
                AddLineQueueX( "%s struct %d", p, x );
            else
                AddLineQueueX( "%s struct", p );

        } else {

            x = 0;
            q = 0;

            switch ( tokenarray[1].token ) {
            case T_DIRECTIVE:
            case T_INSTRUCTION:
            case T_REG:
            case T_RES_ID:
            case T_STYPE:
                x = size_from_token( &tokenarray[1] );
                q = tokenarray[1].tokval;
                break;
            default:
                sym = SymFind( p );
                if ( sym ) {
                    if ( sym->state == SYM_TYPE && \
                         sym->typekind == TYPE_TYPEDEF ) {
                        x = SizeFromMemtype( sym->mem_type, USE_EMPTY, sym->type );
                        if ( x < 16 && sym->mem_type & MT_FLOAT )
                            x = 16;
                        q = T_TYPEDEF;
                    }
                }
            }

            if ( q ) {
                o->type = q;
                if ( x < 16 ) {
                    q = T_RAX;
                    switch ( x ) {
                    case 1 : q = T_AL;  break;
                    case 2 : q = T_AX;  break;
                    case 4 : q = T_EAX; break;
                    }
                    o->vector = q;
                }
            } else {
                AddLineQueueX( "%s struct", p );
            }
        }

        sym = o->sym;
        if ( sym ) {
            if ( cmd != T_DOT_TEMPLATE ) {
                if ( !SearchNameInStruct( sym, "lpVtbl", &u, 0 ) )
                    AddLineQueueX( "lpVtbl %sVtbl ?", clname );
            }
            AddLineQueueX( "%s <>", sym->name );
        } else if ( cmd != T_DOT_TEMPLATE )
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
