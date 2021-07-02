#include <string.h>
#include <globals.h>
#include <hllext.h>
#include <types.h>
#include <proc.h>
#include <expreval.h>
#include <atofloat.h>

extern enum proc_status ProcStatus;
void SetLocalOffsets( struct proc_info *info );

enum ClType { ClNew, ClMem, ClPtr };

int ConstructorCall(
        struct asm_tok tokenarray[],
        char * name,    /* id name */
        int *  end,     /* past ')' of call */
        int    i,       /* past '(' of call */
        char * class,   /* class name */
        char * type )   /* name:<type> */
{

    int acc;
    int reg,r32;
    int cltype;
    char cc[128]; /* class_class */
    struct asym *sym;
    char *p;
    char *q;
    int index;
    int e,g;

    strcat( strcat( strcpy( cc, class ), "_" ), class );
    sym = SymFind(cc);

    if ( Parse_Pass > PASS_1 && sym ) {

        if ( sym->state == SYM_UNDEFINED ) {

            /* x::x proto
             *
             * undef x_x
             * x_x macro this
             */

            sym->state = SYM_MACRO;
        }
    }

    r32 = 0;
    reg = 0;

    if ( sym && sym->state == SYM_MACRO ) {

        r32 = T_ECX;
        reg = T_ECX;

        if ( ModuleInfo.Ofssize == USE64 ) {

            r32 = T_EDI;
            reg = T_RDI;

            if ( sym->langtype != LANG_SYSCALL ) {

                r32 = T_ECX;
                reg = T_RCX;
            }
        }
    }

    index = 0;
    cltype = ClNew;
    if ( tokenarray[i-1].token == T_COLON )
        cltype = ClMem;
    else if ( type )
        cltype = ClPtr;

    if ( tokenarray[i-1].token != T_COLON ) {

        index++;
        if ( type == NULL )
            index++;
    }

    p = tokenarray[i+2].tokpos;
    e = *end;
    if ( tokenarray[e-2].token != T_OP_BRACKET ) {
        index += 3;
        q = tokenarray[e-1].tokpos;
        *q = 0;
    } else
        q = NULL;

    if ( r32 ) {

        switch ( index ) {
        case 0:
        case 3:
            AddLineQueueX( " lea %r,%s", reg, name );
            break;
        case 1:
        case 2:
        case 4:
        case 5:
            AddLineQueueX( " xor %r,%r", r32, r32 );
            break;
        }

        switch ( index ) {
        case 0: AddLineQueueX( " %s(%r)",          cc, reg );           break;
        case 1: AddLineQueueX( " mov %s,%s(%r)",   name, cc, reg );     break;
        case 2: AddLineQueueX( " %s(%r)",          cc, reg );           break;
        case 3: AddLineQueueX( " %s(%r,%s)",       cc, reg, p );        break;
        case 4: AddLineQueueX( " mov %s,%s(%r,%s)", name, cc, reg, p ); break;
        case 5: AddLineQueueX( " %s(%r,%s)",       cc, reg, p );        break;
        }
    } else {
        switch ( index ) {
        case 0: AddLineQueueX( " %s(&%s)",         cc, name );     break;
        case 1: AddLineQueueX( " mov %s,%s(0)",    name, cc );     break;
        case 2: AddLineQueueX( " %s(0)",           cc );           break;
        case 3: AddLineQueueX( " %s(&%s,%s)",      cc, name, p );  break;
        case 4: AddLineQueueX( " mov %s,%s(0,%s)", name, cc, p );  break;
        case 5: AddLineQueueX( " %s(0,%s)",        cc, p );        break;
        }
    }

    if ( q )
        *q = ')';

    /* added 2.31.44 */

    if ( tokenarray[e].token == T_COLON ) { /* Class() : member(value) [ , member(value) ] */

        e++;
        acc = T_EAX;
        if ( ModuleInfo.Ofssize == USE64 )
            acc = T_RAX;
        if ( reg )
            acc = reg;

        while ( tokenarray[e].token == T_ID && tokenarray[e+1].token == T_OP_BRACKET ) {

            p = tokenarray[e].string_ptr;
            e += 2;
            q = tokenarray[e].tokpos;

            for ( g = 1; tokenarray[e].token != T_FINAL; e++ ) {
                if ( tokenarray[e].token == T_OP_BRACKET )
                    g++;
                else if ( tokenarray[e].token == T_CL_BRACKET ) {
                    g--;
                    if ( g == 0 )
                        break;
                }
            }
            if ( tokenarray[e].token != T_CL_BRACKET )
                return asmerr( 2008, tokenarray[e].string_ptr );

            tokenarray[e].tokpos[0] = 0;
            if ( cltype == ClMem )
                AddLineQueueX( " mov %s.%s, %s", name, p, q );
            else
                AddLineQueueX( " mov [%r].%s.%s, %s", acc, class, p, q );
            tokenarray[e].tokpos[0] = ')';

            e++;
            if ( tokenarray[e].token == T_COMMA )
                e++;
        }
        *end = e;
    }
    return 0;
}

/* case = {0,2,..} */

static void AssignString( char *name, struct sfield *fp, char *string )
{
  int i, e;
  struct expr opndx;
  char *p;
  int size;

    size = fp->sym.total_size;
    p = fp->sym.name;

    do {

        if ( size <= 4 )
            break;

        i = Token_Count + 1;
        e = Tokenize( string, i, ModuleInfo.tokenarray, TOK_DEFAULT );
        if ( ModuleInfo.tokenarray[i].token != T_NUM && ModuleInfo.tokenarray[i].token != T_FLOAT )
            break;
        if ( EvalOperand( &i, ModuleInfo.tokenarray, e, &opndx, 0 ) == ERROR )
            break;

        if ( opndx.kind == EXPR_FLOAT ) {
            opndx.kind = EXPR_CONST;
            if ( size != 16 )
                quad_resize( &opndx, size );
        }
        if ( opndx.kind != EXPR_CONST )
            break;
        if ( size == 8 && opndx.hvalue == 0 && ModuleInfo.Ofssize == USE64 )
            break;
        switch ( size ) {
        case 16:
            AddLineQueueX( " mov dword ptr %s.%s[12], 0x%x", name, p, opndx.hlvalue >> 32 );
            AddLineQueueX( " mov dword ptr %s.%s[8], 0x%x", name, p, (uint_32)opndx.hlvalue );
        case 10:
            if ( size == 10 )
                AddLineQueueX( " mov word ptr %s.%s[8], 0x%x", name, p, (uint_32)opndx.hlvalue );
        case 8:
            AddLineQueueX( " mov dword ptr %s.%s[4], 0x%x", name, p, opndx.hvalue );
            AddLineQueueX( " mov dword ptr %s.%s[0], 0x%x", name, p, opndx.value );
            return;
        }
    } while ( 0 );
    AddLineQueueX( " mov %s.%s, %s", name, p, string );
}

static char *AssignStruct( char *name, struct asym *sym, char *string, struct sfield *s )
{
  char val[256];
  int array = 0;
  int c;
  char *p = string;
  char *q;
  struct dsym *d;

    p++;
    if ( sym ) {

        while ( sym->state == SYM_TYPE && sym->type )
            sym = sym->type;

        d = (struct dsym *)sym;
        s = d->e.structinfo->head;
    } else
        array++;

    while ( 1 ) {

        while ( *p == ' ' || *p == '\t' )
            p++;

        if ( *p == '}' || *p == '\0' )
            break;

        q = val;
        if ( *p == '{' ) {

            strcpy( q, name );
            if ( s->sym.name[0] ) {
                strcat( q, "." );
                strcat( q, s->sym.name );
            }
            p = AssignStruct( q, s->sym.type, p, s );
            if ( p == NULL )
                break;
            while ( *p == ' ' || *p == '\t' )
                p++;

        } else {

            int br = 0;
            char *e = q + 255;

            *q = '\0';

            while ( q < e ) {

                if ( *p == '(' )
                    br++;
                else if ( *p == ')' )
                    br--;
                if ( p[0] == '\0' || ( !br && ( p[0] == ',' || p[0] == '}' ) ) )
                    break;
                *q++ = *p++;
            }
            *q = '\0';

            for ( e = val; e < q && ( q[-1] == ' ' || q[-1] == '\t' ); ) {

                q--;
                *q = '\0';
            }

            if ( !array && val[0] && val[0] != '{' && s->sym.isarray ) {
                struct asym *a = SymSearch( val );
                if ( a && a->state == SYM_TMACRO ) {
                    if ( a->string_ptr[0] == '{' ) {
                        e = (char *)myalloca( strlen(p) + a->total_size + 2 );
                        strcpy( e, a->string_ptr );
                        p = strcat( e, p );
                        continue;
                    }
                }
            }

            if ( val[0] ) {
                if ( val[0] == '"' || ( val[0] == 'L' &&  val[1] == '"') )
                    AddLineQueueX( " mov %s.%s,&@CStr(%s)", name, s->sym.name, val );
                else if ( array )
                    AddLineQueueX( " mov %s[%d],%s", name,
                        s->sym.total_size / s->sym.total_length * ( array - 1 ), val );
                else
                    AssignString( name, s, val );
                    //AddLineQueueX( " mov %s.%s,%s", name, s->sym.name, val );
            }
        }

        if ( *p == '\0' )
            break;
        c = *p++;
        if ( c != ',' )
            break;
        if ( array )
            array++;
        else
            s = s->next;
        if ( s == NULL )
            break;
    }
    return p;
}

/* case = {...},{...}, */

static char *AssignId( char *name, struct asym *sym, struct asym *type, char *string )
{
  char Id[128];
  int size;
  struct sfield f;
  char *p;
  int c,i;
  int length;

    if ( type == NULL ) {
        memcpy( &f.sym, sym, sizeof( struct asym ) );
        f.next = NULL;
        return AssignStruct( name, NULL, string, &f );
    }
    if ( !sym->isarray )
        return AssignStruct( name, type, string, NULL );

    p = string + 1;
    while ( *p == ' ' || *p == '\t' )
        p++;

    length = sym->total_length;
    size   = sym->total_size / length;

    for ( i = 0; length ; length--, i += size ) {

        sprintf( Id, "%s[%d]", name, i );
        p = AssignStruct( Id, type, p, NULL );
        c = *p++;
        if ( !c )
            break;

        while ( *p == ' ' || *p == '\t' )
            p++;
        if ( *p != '{' )
            break;
    }
    return p;
}

/* case = {0} */

static void ClearStruct( char *name, struct asym *sym )
{
  int i;
  int size = sym->total_size;

    AddLineQueueX( " xor eax,eax" );
    if ( ModuleInfo.Ofssize == USE64 ) {
        if ( size > 32 ) {
            AddLineQueue ( " push rdi" );
            AddLineQueue ( " push rcx" );
            AddLineQueueX( " lea rdi,%s", name );
            AddLineQueueX( " mov ecx,%d", size );
            AddLineQueue ( " rep stosb" );
            AddLineQueue ( " pop rcx" );
            AddLineQueue ( " pop rdi" );
        } else {
            for ( i = 0; size >= 8; size -= 8, i += 8 )
                AddLineQueueX( " mov qword ptr %s[%d],rax", name, i );
            for ( ; size; size--, i++ )
                AddLineQueueX( " mov byte ptr %s[%d],al", name, i );
        }
    } else {
        if ( size > 16 ) {
            AddLineQueue ( " push edi" );
            AddLineQueue ( " push ecx" );
            AddLineQueueX( " lea edi,%s", name );
            AddLineQueueX( " mov ecx,%d", size );
            AddLineQueue ( " rep stosb" );
            AddLineQueue ( " pop ecx" );
            AddLineQueue ( " pop edi" );
        } else {
            for ( i = 0; size >= 4; size -= 4, i += 4 )
                AddLineQueueX( " mov dword ptr %s[%d],eax", name, i );
            for ( ; size; size--, i++ )
                AddLineQueueX( " mov byte ptr %s[%d],al", name, i );
        }
    }
}

static int AssignValue( char *name, int i, struct asm_tok tokenarray[] )
{
  char cc[128];
  char *p;
  struct expr opndx;
  struct asym *sym;
  int q,x;

    i++;
    if ( tokenarray[i].token == T_STRING && tokenarray[i].bytval == '{' ) {

        sym = SymSearch( name );
        if ( sym == NULL )
            return asmerr( 2008, tokenarray[i].tokpos );

        q = 0;
        p = tokenarray[i].string_ptr;
        while ( *p == ' ' || *p == '\t' )
            p++;

        if ( *p == '0' ) {

            p++;
            while ( *p == ' ' || *p == '\t' )
                p++;

            if ( *p == 0 )
                q++;
        }
        if ( q )
            ClearStruct( name, sym );
        else
            AssignId( name, sym, sym->type, tokenarray[i].tokpos );

        return i + 1;
    }

    p = strcat( strcat( strcpy( cc, " mov " ), name ), ", " );
    q = 0;

    while ( 1 ) {
        if ( tokenarray[i].token == T_FINAL )
            break;
        else if ( tokenarray[i].token == T_COMMA ) {
            if ( q == 0  )
                break;
        } else if ( tokenarray[i].token == T_OP_BRACKET )
            q++;
        else if ( tokenarray[i].token == T_CL_BRACKET )
            q--;

        if ( tokenarray[i].token == T_INSTRUCTION )
            strcat( p, " " );

        if ( !q && tokenarray[i].token == T_STRING && tokenarray[i].bytval == '"' ) {
            sym = SymSearch( name );
            if ( sym && sym->mem_type & MT_PTR ) {
                strcat( p, "&@CStr(" );
                strcat( p, tokenarray[i].string_ptr );
                strcat( p, ")" );
                i++;
                break;
            }
        }
        strcat( p, tokenarray[i].string_ptr );
        if ( ( tokenarray[i].token == T_INSTRUCTION ) ||
            ( tokenarray[i].token == T_RES_ID && tokenarray[i].tokval == T_ADDR ) )
            strcat( p, " " );
        i++;
    }
    if ( q )
        asmerr( 2157 );
    AddLineQueueX( p );
    return i;
}

int AddLocalDir( int i, struct asm_tok tokenarray[] )
{
  char *p;
  char *name;
  char *type;
  struct dsym *sym;
  struct dsym *curr;
  struct proc_info *info;
  struct qualified_type ti;
  struct expr opndx;
  int j, q;
  int creat;

    i++;  /* go past directive */

    do {

        if ( tokenarray[i].token != T_ID )
            return asmerr(2008, tokenarray[i].string_ptr);

        name = tokenarray[i].string_ptr;
        type = NULL;

        ti.symtype = NULL;
        ti.is_ptr = 0;
        ti.ptr_memtype = MT_EMPTY;

        if ( SIZE_DATAPTR & ( 1 << ModuleInfo.model ) )
            ti.is_far = TRUE;
        else
            ti.is_far = FALSE;
        ti.Ofssize = ModuleInfo.Ofssize;

        creat = 0;
        if ((sym = (struct dsym *)SymFind(name)) == NULL) {
            sym = (struct dsym *)SymLCreate(name);
            creat = 1;
        }

        if( !sym )
            return( ERROR );

        if ( creat ) {
            sym->sym.state = SYM_STACK;
            sym->sym.isdefined = TRUE;
            sym->sym.total_length = 1;
        }

        if ( ti.Ofssize == USE16 ) {
            if ( creat )
                sym->sym.mem_type = MT_WORD;
            ti.size = sizeof( uint_16 );
        } else {
            if ( creat )
                sym->sym.mem_type = MT_DWORD;
            ti.size = sizeof( uint_32 );
        }
        i++; /* go past name */

        if( tokenarray[i].token == T_OP_SQ_BRACKET ) {

            i++; /* go past '[' */
            for ( j = i; j < Token_Count; j++ ) {

                if ( tokenarray[j].token == T_COMMA || tokenarray[j].token == T_COLON )
                    break;
            }
            if ( EvalOperand( &i, tokenarray, j, &opndx, 0 ) == ERROR )
                return ERROR;

            if ( opndx.kind != EXPR_CONST ) {

                asmerr( 2026 );
                opndx.value = 1;
            }
            sym->sym.total_length = opndx.value;
            sym->sym.isarray = TRUE;
            if( tokenarray[i].token == T_CL_SQ_BRACKET )
                i++;  /* go past ']' */
            else
                asmerr( 2045 );
        }

        if( tokenarray[i].token == T_COLON ) {

            i++;
            type = tokenarray[i].string_ptr;
            if ( GetQualifiedType( &i, tokenarray, &ti ) == ERROR )
                return( ERROR );

            sym->sym.mem_type = ti.mem_type;
            if ( ti.mem_type == MT_TYPE )
                sym->sym.type = ti.symtype;
            else
                sym->sym.target_type = ti.symtype;
        }

        if ( creat ) {
            sym->sym.is_ptr  = ti.is_ptr;
            sym->sym.isfar   = ti.is_far;
            sym->sym.Ofssize = ti.Ofssize;
            sym->sym.ptr_memtype = ti.ptr_memtype;
            sym->sym.total_size = ti.size * sym->sym.total_length;
        }

        if ( creat && Parse_Pass == PASS_1 ) {

            info = CurrProc->e.procinfo;
            if( info->locallist == NULL ) {
                info->locallist = sym;
            } else {
                for( curr = info->locallist; curr->nextlocal ; curr = curr->nextlocal );
                curr->nextlocal = sym;
            }
        }

        if ( tokenarray[i].token != T_FINAL ) {

            if ( tokenarray[i].token == T_COMMA ) {

                if ( i + 1 < Token_Count )
                    i++;

            } else if ( tokenarray[i].token == T_OP_BRACKET ) {

                j = i - 1;
                p = tokenarray[i-1].string_ptr;
                i++; /* go past '(' */
                for ( q = 1; tokenarray[i].token != T_FINAL; i++ ) {
                    if ( tokenarray[i].token == T_OP_BRACKET )
                        q++;
                    else if ( tokenarray[i].token == T_CL_BRACKET ) {
                        q--;
                        if ( q == 0 )
                            break;
                    }
                }
                if( tokenarray[i].token != T_CL_BRACKET )
                    return asmerr( 2045 );

                i++; /* go past ')' */
                ConstructorCall( tokenarray, name, &i, j, p, type );
            } else if ( tokenarray[i].token == T_DIRECTIVE && tokenarray[i].dirtype == DRT_EQUALSGN )
                i = AssignValue( name, i, tokenarray );
            else
                return asmerr( 2065, "," );
        }
    } while ( i < Token_Count );

    if ( creat && Parse_Pass == PASS_1 ) {
        info->localsize = 0;
        SetLocalOffsets(info);
    }
    return NOT_ERROR;
}

int NewDirective(int i, struct asm_tok tokenarray[] )
{
  int rc;

    if( CurrProc == NULL )
        return asmerr( 2012 );

    rc = AddLocalDir(i, tokenarray);
    if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 );
    if ( ModuleInfo.g.line_queue.head )
        RunLineQueue();

    return rc;
}
