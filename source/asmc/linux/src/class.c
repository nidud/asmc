#include <string.h>
#include <globals.h>
#include <hllext.h>
#include <types.h>
#include <macro.h>

static void ClassProto(char *name, int langtype, char *args, int type)
{
    char pargs[1024];
    char *p = pargs;
    char *q = args;
    char c = 1;

    while ( c ) { /* default args :abs=<val> */
        c = *q++;
        if ( c == '=' ) {
            c = *q++;
            while ( c && c != '>' )
                c = *q++;
            if ( c )
                c = *q++;
        }
        *p++ = c;
    }
    if ( langtype )
        AddLineQueueX( "%s %r %r %s", name, type, langtype, pargs );
    else
        AddLineQueueX( "%s %r %s", name, type, pargs );
}

static void ClassProto2( char *name, char *method, struct com_item *item, char *args )
{
    char buffer[256];

    strcpy( buffer, name );
    if ( item->vector || item->method == T_DOT_STATIC )
        strcat( buffer, "_" );
    else
        strcat( buffer, "::" );
    strcat( buffer, method );
    ClassProto( buffer, item->langtype, args, T_PROTO );
}

static void AddPublic( struct com_item *com, struct dsym *sp )
{
    char q[256];
    char *name;
    char *method;
    struct sfield *fl;
    struct asym *sym;

    if ( sp->sym.total_size && Parse_Pass == 0 ) {

        for ( fl = sp->e.structinfo->head; fl; fl = fl->next ) {

            sym = &fl->sym;
            if ( sym->type ) {

                if ( sym->type->typekind == TYPE_STRUCT ) {

                    AddPublic( com, (struct dsym *)sym->type );

                } else {

                    name = sym->name;
                    strcpy( q, sp->sym.name );
                    q[sp->sym.name_size-4] = '\0';
                    sym = SymFind( strcat( strcat( q, "_" ), name ) );

                    if ( sym ) {

                        method = sym->name;
                        if ( sym->state == SYM_TMACRO )
                            method = sym->string_ptr;

                        AddLineQueueX( "%s_%s equ <%s>", com->class, name, method );
                    }
                }
            }
        }
    }
}

static int OpenVtbl( struct com_item *com )
{
    char q[256];
    struct asym *sym;

    AddLineQueueX( "%sVtbl struct", com->class );

    /* v2.30.32 - : public class */

    sym = com->publsym;
    if ( sym == NULL )
        return 0;

    sym = SymFind( strcat( strcpy( q, sym->name ), "Vtbl" ) );
    if ( sym == NULL )
        return 1;

    if ( sym->total_size ) {
        AddLineQueueX( "%s <>", q );
        AddPublic( com, (struct dsym *)sym );
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
    int *count, int *isid, int *context, int *langtype )
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
    if ( tokenarray[i].token == T_RES_ID ) { /* fastcall... */
        *langtype = tokenarray[i].tokval;
        i++;
    }
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
  int brachets;
  char name[16];
  char size[16];
  char curr[256];
  char vector[128];
  struct input_status oldstat;
  char *p;
  int langtype = 0;

    /* class :: + (...) / (...) */

    while ( 1 ) {

        i = get_param_name( i, tokenarray, name, size, &arg_count, &id, &context, &langtype );
        if ( i == ERROR )
            return ERROR;

        j = i;
        if ( tokenarray[i].token == T_OP_BRACKET ) {
            j++;
            brachets = 1;
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
        } else {

            if ( tokenarray[i].token == T_FINAL )
                return asmerr( 2008, tokenarray[i-1].string_ptr );

            brachets = 0;
            i++;
            arg_count++;
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
            strcat( p, tokenarray[j].tokpos );
            if ( !brachets )
                strcat( p, ")" );
            break;
        }

        p += strlen(p);
        k = ( tokenarray[i].tokpos - tokenarray[j].tokpos );
        memcpy( p, tokenarray[j].tokpos, k );
        if ( brachets == 0 )
            p[k++] = ')';
        p[k] = '\0';
        if ( is_linequeue_populated() )
            RunLineQueue();
        AddLineQueue( curr );
        InsertLineQueue();
    }
    return i;
}

enum {
    tiImmediat,
    tiFloat,
    tiRegister,
    tiMemory,
    tiPointer
};

int GetTypeId( char *buffer, struct asm_tok tokenarray[] )
{
  int addr,i,j,g,e;
  struct expr opnd;
  int tokval;
  char id[256];
  int type;
  int size;
  int is_void;
  int is_id;
  char name[256];
  struct asym *sym;
  struct asym *stp;

    /* find first instance of macro in line */

    i = 0;
    while ( tokenarray[i].token != T_FINAL ) {
        if ( tokenarray[i].token == T_ID ) {
            if ( !_stricmp( tokenarray[i].string_ptr, "typeid" ) ) {

                tokenarray[i].string_ptr[0] = '?';
                break;
            }
        }
        i++;
    }

    if ( tokenarray[i].token == T_FINAL && tokenarray[i+1].token == T_OP_BRACKET )
        i++;
    else if ( tokenarray[i].token != T_FINAL )
        i++;
    else
        i = 0;

    if ( tokenarray[i].token != T_OP_BRACKET )
        return 0;

    i++;
    id[0] = '\0';
    is_id = 0;
    if ( tokenarray[i+1].token == T_COMMA ) {
        is_id = 1;
        strcpy( id, tokenarray[i].string_ptr );
        i += 2;
    }

    addr = 0;
    if ( tokenarray[i].token == T_RES_ID && tokenarray[i].tokval == T_ADDR ) {
        i++;
        addr++;
    }

    for ( g = 1, j = i, e = i; tokenarray[j].token != T_FINAL; j++, e++ ) {
        if ( tokenarray[j].token == T_OP_BRACKET )
            g++;
        else if ( tokenarray[j].token == T_CL_BRACKET ) {
            g--;
            if ( g == 0 )
                break;
        }
    }
    if ( EvalOperand( &i, tokenarray, e, &opnd, 0 ) == ERROR )
        return 0;

    type = 0;
    size = 0;
    name[0] = '\0';
    is_void = 0;

    switch ( opnd.kind ) {

    case EXPR_REG:

        if ( !opnd.indirect ) {
            g = SizeFromRegister( opnd.base_reg->tokval );
            size = ( g << 3 );
            type = tiRegister;
            break;
        }

    case EXPR_ADDR:

        type = tiMemory;
        if ( addr )
            type = tiPointer;

        sym = opnd.sym;
        stp = opnd.type;
        if ( opnd.mbr )
            sym = opnd.mbr;

        if ( !sym || sym->state == SYM_UNDEFINED ) {
            is_void = 1;
            break;
        }
        if ( sym->mem_type == MT_TYPE && sym->type )
            sym = sym->type;

        if ( sym->target_type &&
            ( sym->mem_type == MT_PTR || sym->ptr_memtype == MT_TYPE ) ) {

            if ( sym->mem_type == MT_PTR )
                type = tiPointer;
            sym = sym->target_type;
        }

        if ( sym->state == SYM_TYPE && sym->typekind == TYPE_STRUCT ) {

            strcpy( name, sym->name );
            break;
        }

        if ( opnd.type ) {
            if ( opnd.type->state == SYM_TYPE && opnd.type->typekind == TYPE_STRUCT ) {

                strcpy( name, opnd.type->name );
                break;
            }
        }

        if ( sym->state == SYM_INTERNAL ||
             sym->state == SYM_STACK ||
             sym->state == SYM_STRUCT_FIELD ||
             sym->state == SYM_TYPE ) {

            g = sym->mem_type;
            if ( g == MT_PTR ) {
                type = tiPointer;
                if ( sym->is_ptr == 1 && g != sym->ptr_memtype )
                    g = sym->ptr_memtype;
            }

            switch ( g ) {
            case MT_BYTE:   e = T_BYTE;   break;
            case MT_SBYTE:  e = T_SBYTE;  break;
            case MT_WORD:   e = T_WORD;   break;
            case MT_SWORD:  e = T_SWORD;  break;
            case MT_REAL2:  e = T_REAL2;  break;
            case MT_DWORD:  e = T_DWORD;  break;
            case MT_SDWORD: e = T_SDWORD; break;
            case MT_REAL4:  e = T_REAL4;  break;
            case MT_FWORD:  e = T_FWORD;  break;
            case MT_QWORD:  e = T_QWORD;  break;
            case MT_SQWORD: e = T_SQWORD; break;
            case MT_REAL8:  e = T_REAL8;  break;
            case MT_TBYTE:  e = T_TBYTE;  break;
            case MT_REAL10: e = T_REAL10; break;
            case MT_OWORD:  e = T_OWORD;  break;
            case MT_REAL16: e = T_REAL16; break;
            case MT_YWORD:  e = T_YWORD;  break;
            case MT_ZWORD:  e = T_ZWORD;  break;
            case MT_PROC:   e = T_PROC;   break;
            case MT_NEAR:   e = T_NEAR;   break;
            case MT_FAR:    e = T_FAR;    break;
            case MT_PTR:    e = T_PTR;    break;
            default:
                is_void = 1;
                break;
            }
            if ( !is_void )
                _strupr( GetResWName( e, name ) );
            break;
        }
        is_void = 1;
        break;

    case EXPR_CONST:
        type = tiImmediat;
        size = 32;
        if ( opnd.hlvalue )
            size = 128;
        else if ( opnd.hvalue )
            size = 64;
        break;
    case EXPR_FLOAT:
        type = tiFloat;
        break;
    }

    if ( is_void )
        strcpy( name, "VOID" );

    if ( is_id ) {
        strcpy( buffer, id );
        buffer += strlen( buffer );
    }

    switch ( type ) {
    case tiImmediat:
        sprintf( buffer, "IMM%d", size );
        return 1;
    case tiFloat:
        strcpy( buffer, "IMMFLT" );
        return 1;
    case tiRegister:
        sprintf( buffer, "REG%d", size );
        return 1;
    case tiMemory:
        strcpy( buffer, name );
        return 1;
    case tiPointer:
        strcpy( buffer, "P" );
        strcat( buffer, name );
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
    char    *p, *id = tokenarray[i-1].string_ptr;
    int     x, q, IsCom = 0;
    struct  com_item *o = ModuleInfo.g.ComStack;
    struct  asym *sym;
    int     IsType = 0;
    int     constructor = 0;

    if ( o ) {

        if ( strcmp( id, o->class ) == 0 ) {

            ClassProto2( id, id, o, tokenarray[i+1].tokpos );
            constructor = 1;
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

    if ( IsCom && ( !ModuleInfo.g.ComStack || ModuleInfo.g.ComStack->method != T_DOT_STATIC ) ) {

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
    if ( constructor ) {
        strcpy(buffer, id);
        strcat(buffer, "_");
        strcat(buffer, id);
        if ( ( sym = SymFind( buffer ) ) != NULL )
            sym->method = 1;
    }
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

    if ( q || tokenarray[j+k].tokval == T_ENDP || tokenarray[j+k].token == T_OP_BRACKET ) {

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

        while ( *p == '\t' || *p == ' ' )
            p++;

        if ( *p == ':' || !is_valid_id_first_char( *p ) ) {

            q += sprintf( q, "_%u, ", i );

        } else {

            while ( is_valid_id_char( *p ) )
                *q++ = *p++;

            *q++ = ',';
            *q++ = ' ';
            *q = '\0';
        }

        s = p;
        if ( ( p = strchr( p, ',' ) ) != NULL)
            p++;
        else
            p = s + strlen(s);

        if ((s = strchr(s, '=')) != NULL) {

            if ( s < p ) {

                q--;
                *(q-1) = ':';
                x = p - s;
                if ( *(p-1) == ',' )
                    x--;
                memcpy(q, s, x);
                q += x;
                *q++ = ',';
                *q++ = ' ';
                *q = '\0';
            }
        }
    }
    return q;
}

void MacroInline( char *name, int count, char *args, char *data, int vargs )
{
    int i;
    char *p, *q, *e;
    char mac[512];
    char buf[512];
    struct com_item *o;
    struct asm_tok *tokenarray;

    if ( Parse_Pass > PASS_1 )
        return;

    mac[0] = '\0';
    strcpy( buf, args );
    o = ModuleInfo.g.ComStack;
    tokenarray = ModuleInfo.tokenarray;

    if ( tokenarray[1].tokval == T_PROTO ) {

        /* name proto [name1]:type, ... { ... } */
        /* args: _1, _2, ... */

        p = mac;
        if ( count ) {

            p = ParseMacroArgs( p, count + 1, buf );
            p -= 2;
        }
        *p = 0;

    } else if ( o && o->vector ) {

        p = ParseMacroArgs( mac, count, buf );
        strcat( p, "this:=<" );
        strcat( p, GetResWName( o->vector, NULL ) );
        strcat( p, ">" );
    } else {
        p = strcpy( mac, "this" ) + 4;
        if ( count > 1 ) {
            p = strcpy( p, ", " ) + 2;
            p = ParseMacroArgs( p, count, buf );
            p -= 2;
            *p = 0;
        }
    }

    if ( vargs )
        strcpy( p, ":vararg" );
    AddLineQueueX( "%s macro %s", name, mac );

    p = data;
    while ( *p == ' ' || *p == 9 )
        p++;
    for ( e = NULL; ( q = strchr( p, '\n' ) ) != NULL; ) {

        *q = '\0';
        if ( *p ) {
            e = p;
            AddLineQueue( p );
        }
        *q++ = '\n';
        p = q;
    }
    while ( *p == ' ' || *p == 9 )
        p++;
    if ( *p ) {
        e = p;
        AddLineQueue( p );
    }
    if ( e == NULL )
        AddLineQueue( "exitm<>" );
    else {
        i = _memicmp( e, "exitm", 5 );
        if ( i )
            i = _memicmp( e, "retm", 4 );
        if ( i )
            AddLineQueue( "exitm<>" );
    }
    AddLineQueue( "endm" );
    MacroLineQueue();
}

int ClassDirective( int i, struct asm_tok tokenarray[] )
{
    int         rc = NOT_ERROR;
    int         cmd = tokenarray[i].tokval;
    int         x,q,args;
    char        clname[256];
    char *      p;
    char *      ptr;
    char *      public_class;
    int         is_id;
    int         is_vararg;
    char        token[256];
    char        name[512];
    uint_32     u;
    int         context;
    int         constructor = 0;
    struct asym *sym;
    struct com_item *o = ModuleInfo.g.ComStack;
    int         langtype;
    struct asym *vtable;

    i++;

    switch ( cmd ) {
    case T_DOT_ENDS:
        if ( o == NULL ) {
            if ( CurrStruct )
                rc = asmerr( 1011 );
            return rc;
        }
        ModuleInfo.g.ComStack = NULL;
        if ( o->type )
            break;
        if ( !CurrStruct )
            return asmerr( 1011 );

        AddLineQueueX( "%s ends", CurrStruct->sym.name );
        if ( o->publsym ) {
            if ( !strcmp( o->class, CurrStruct->sym.name ) ) {
                if ( SymFind( strcat( strcpy( clname, o->publsym->name ), "Vtbl" ) ) != NULL ) {
                    OpenVtbl(o);
                    AddLineQueueX( "%sVtbl ends", CurrStruct->sym.name );
                }
            }
        }
        break;

    case T_DOT_STATIC:
    case T_DOT_OPERATOR:
    case T_DOT_INLINE:

        if ( o && o->type )
            ;
        else if ( o == NULL || CurrStruct == NULL )
            return ( asmerr( 1011 ) );
        o->method = cmd;
        langtype = o->langtype;

        /* .operator + :type, :type */
        is_vararg = 0;
        i = get_param_name( i, tokenarray, token, clname, &args, &is_id, &context, &langtype );
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
        if ( o->publsym )
            ptr = o->publsym->name;

        sym = SymFind( strcat( strcpy( clname, ptr ), "Vtbl" ) );
        vtable = sym;
        if ( sym == NULL )
            sym = (struct asym *)CurrStruct;

        if ( sym != NULL ) {
            if ( SearchNameInStruct( sym, name, &u, 0 ) == NULL || vtable == NULL ) {
                if ( strcmp( name, ptr ) != 0 )
                    ClassProto( name, langtype, tokenarray[i].tokpos, T_PROC );
                else {
                    ClassProto2( ptr, name, o, tokenarray[i].tokpos );
                    constructor++;
                }
            }
        } else if ( o->type ) {
            ClassProto2( ptr, name, o, tokenarray[i].tokpos );
            constructor++;
        }

        if ( p == NULL || Parse_Pass > PASS_1 )
            break;

        /* .operator + :type { ... } */

        sprintf( token, "%s_%s", o->class, name );
        if ( ModuleInfo.list )
            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 );
        RunLineQueue();
        if ( constructor ) {
            sym = SymFind( token );
            if ( sym ) {
                if ( cmd != T_DOT_STATIC )
                    sym->method = 1;
                if ( cmd == T_DOT_STATIC && is_vararg == 0 )
                    sym->isstatic = 1;
            }
        }
        MacroInline( token, args, tokenarray[i].tokpos, p, is_vararg );
        if ( !constructor && ( cmd == T_DOT_STATIC && is_vararg == 0 ) ) {
            sym = SymFind( token );
            if ( sym )
                sym->isstatic = 1;
        }
        return rc;

    case T_DOT_COMDEF:
    case T_DOT_CLASS:
    case T_DOT_TEMPLATE:
        if ( o != NULL )
            return ( asmerr( 1011 ) );

        o = LclAlloc( sizeof( struct com_item ) );
        ModuleInfo.g.ComStack = o;
        o->cmd = cmd;
        o->type = 0;
        o->langtype = 0;
        o->publsym = NULL;
        o->vector = 0;
        o->sym = NULL;

        p = tokenarray[i++].string_ptr;
        o->class = LclAlloc( strlen(p) + 1 );
        strcpy( o->class, p );
        /* v2.32.20 - removed typedefs */
        strcpy( clname, p );

        if ( tokenarray[i].token == T_ID && ( tokenarray[i].string_ptr[0] | 0x20 ) == 'c'
            && tokenarray[i].string_ptr[1] == '\0') {
            tokenarray[i].token = T_RES_ID;
            tokenarray[i].tokval = T_CCALL;
            tokenarray[i].bytval = 1;
        }

        if ( tokenarray[i].token != T_FINAL && tokenarray[i].tokval >= T_CCALL
            && tokenarray[i].tokval <= T_WATCALL ) {
            o->langtype = tokenarray[i].tokval;
            i++;
        }

        sym = NULL;
        if ( tokenarray[i].token == T_COLON ) {

            /* v2.30.32 - : public class */

            if ( tokenarray[i+1].token  == T_DIRECTIVE &&
                 tokenarray[i+1].tokval == T_PUBLIC ) {

                sym = SymFind( tokenarray[i+2].string_ptr );
                if ( sym == NULL )
                    return asmerr( 2006, tokenarray[i+2].string_ptr );
                ModuleInfo.g.ComStack->publsym = sym;
            }
        }

        if ( cmd == T_DOT_CLASS ) {

            x = ModuleInfo.Ofssize << 2;
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

        sym = o->publsym;
        if ( sym ) {
            if ( cmd != T_DOT_TEMPLATE ) {
                if ( !SearchNameInStruct( sym, "lpVtbl", &u, 0 ) )
                    AddLineQueueX( "lpVtbl ptr %sVtbl ?", clname );
            }
            AddLineQueueX( "%s <>", sym->name );
        } else if ( cmd != T_DOT_TEMPLATE )
            AddLineQueueX( "lpVtbl ptr %sVtbl ?", clname );
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
