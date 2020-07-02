#include <string.h>
#include <globals.h>
#include <hllext.h>
#include <types.h>
#include <proc.h>

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
            } else
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
