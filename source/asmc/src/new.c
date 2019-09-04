#include <string.h>
#include <globals.h>
#include <hllext.h>
#include <types.h>
#include <proc.h>

extern enum proc_status ProcStatus;
void SetLocalOffsets( struct proc_info *info );

int AddLocalDir( int i, struct asm_tok tokenarray[] )
{
  char *p;
  char *name;
  char *type;
  char constructor[128]; /* class_class */
  struct asym *syma;
  struct dsym *sym;
  struct dsym *curr;
  struct proc_info *info;
  struct qualified_type ti;
  struct expr opndx;
  int j, q;
  int creat;
#if 0
    if ( Parse_Pass == PASS_1 ) {
        info = CurrProc->e.procinfo;
        if ( GetRegNo( info->basereg ) == 4 ) {
            info->fpo = TRUE;
            ProcStatus |= PRST_FPO;
        }
    }
#endif
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
                if( tokenarray[i].token == T_CL_BRACKET )
                    i++; /* go past ')' */
                else
                    return asmerr( 2045 );

                p = strcat(strcat(strcpy(constructor, p), "_"), p);

                if ( Parse_Pass > PASS_1 ) {

                    if ( ( syma = SymFind( p ) ) ) {

                        if ( syma->state == SYM_UNDEFINED )
                            /*
                             * x::x proto
                             *
                             * undef x_x
                             * x_x macro this
                             */
                            syma->state = SYM_MACRO;
                    }
                }
                if ( tokenarray[i-2].token == T_OP_BRACKET ) {
                    if ( tokenarray[j-1].token == T_COLON )
                        AddLineQueueX( "%s(&%s)", p, name );
                    else if ( type )
                        AddLineQueueX( "mov %s,%s(0)", name, p );
                    else
                        AddLineQueueX( "%s(0)", p );
                } else {
                    tokenarray[i-1].tokpos[0] = 0;
                    if ( tokenarray[j-1].token == T_COLON )
                        AddLineQueueX( "%s(&%s, %s)", p, name, tokenarray[j+2].tokpos );
                    else if ( type )
                        AddLineQueueX( "mov %s,%s(0, %s)", name, p, tokenarray[j+2].tokpos );
                    else
                        AddLineQueueX( "%s(0, %s)", p, tokenarray[j+2].tokpos );
                    tokenarray[i-1].tokpos[0] = ')';
                }
            } else
                return asmerr( 2065, "," );
        }

    } while ( i < Token_Count );

    if ( creat && Parse_Pass == PASS_1 )
        SetLocalOffsets(info);

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
