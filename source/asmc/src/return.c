/* RETURN.C--
 *
 * Copyright (c) The Asmc Contributors. All rights reserved.
 * Consult your license regarding permissions and restrictions.
 *
 * .return [val] [.if ...]
 */

#include <globals.h>
#include <parser.h>
#include <proc.h>
#include <hllext.h>

static int GetValue( int i, struct asm_tok tokenarray[], int *count, int *directive, int *retval )
{

    int b;

    *directive = 0;
    *count = 0;
    *retval = 0;

    if ( tokenarray[i].token != T_FINAL ) {

        if ( tokenarray[i].token == T_DIRECTIVE ) {

            *directive = i;

        } else {

            *retval = i;
            (*count)++;
            i++;

            if ( tokenarray[i-1].token == T_OP_BRACKET ) {

                for ( b = 1; tokenarray[i].token != T_FINAL; i++ ) {

                    (*count)++;
                    if ( tokenarray[i].token == T_OP_BRACKET ) {
                        b++;
                    } else if ( tokenarray[i].token == T_CL_BRACKET ) {
                        b--;
                        if ( b == 0 ) break;
                    }
                }
                if ( tokenarray[i].token == T_CL_BRACKET ) {
                    (*count)++;
                    i++;
                }
            } else {
                for ( ; tokenarray[i].token != T_FINAL && tokenarray[i].token != T_DIRECTIVE; i++ )
                    (*count)++;
            }
            if ( tokenarray[i].token == T_DIRECTIVE )
                *directive = i;
        }
    }
    return i;
}

extern const unsigned int regax[];

static void AssignValue( int *i, struct asm_tok tokenarray[], int count )
{
    struct  expr opnd;
    int     reg = regax[ModuleInfo.Ofssize];
    int     retval;
    int     directive;
    int     x, Assign;
    char    buffer[256];

    if ( ExpandHllProc(buffer, *i, tokenarray) != ERROR ) {

        if ( *buffer ) {

            QueueTestLines(buffer);
            GetValue(*i, tokenarray, &count, &directive, &retval);
        }
    }

    if ( count ) {

        x = (int)(tokenarray[*i+count].tokpos - tokenarray[*i].tokpos);

        buffer[x] = 0;
        memcpy(buffer, tokenarray[*i].tokpos, x);
    } else {
        strcpy(buffer, tokenarray[*i].string_ptr);
    }

    if ( EvalOperand( i, tokenarray, *i + count, &opnd, EXPF_NOUNDEF ) == NOT_ERROR ) {

        Assign = 1;

        if ( opnd.kind == EXPR_CONST ) {

            if ( !opnd.hvalue && opnd.value > 0 ) {
                x = reg;
                if ( x == T_RAX )
                    x = T_EAX;
                AddLineQueueX( "mov %r,%d", x, opnd.value );
                Assign--;
            } else if ( !opnd.value && !opnd.hvalue ) {
                x = reg;
                if ( x == T_RAX )
                    x = T_EAX;
                AddLineQueueX( "xor %r,%r", x, x );
                Assign--;
            }

        } else if ( opnd.kind == EXPR_REG && !( opnd.indirect ) ) {

            if ( opnd.base_reg->tokval == T_EAX || opnd.base_reg->tokval == T_RAX ) {
                Assign--;
            } else {
                switch ( SizeFromRegister(opnd.base_reg->tokval) ) {
                case 2: reg = T_AX; break;
                case 4: reg = T_EAX; break;
                case 8: reg = T_RAX; break;
                }
            }

        } else if ( opnd.kind == EXPR_ADDR ) {

            switch ( opnd.mem_type ) {
            case MT_BYTE:
            case MT_SBYTE: reg = T_AL; break;
            case MT_WORD:
            case MT_SWORD: reg = T_AX; break;
            case MT_DWORD:
            case MT_SDWORD: reg = T_EAX; break;
#if 0
            case MT_OWORD:
            case MT_REAL2:
            case MT_REAL4:
            case MT_REAL8:
            case MT_REAL10:
            case MT_REAL16: reg = T_XMM0; break;
#endif
            }
        }

        if ( Assign )
            AddLineQueueX( "mov %r,%s", reg, buffer );
    }
}

int ReturnDirective( int i, struct asm_tok tokenarray[] )
{
    int     count;
    int     retval;
    int     directive;
    int     x;
    char    label[16];
    struct  hll_item *p = ModuleInfo.g.RetStack;

    if ( CurrProc == NULL )
        return asmerr(2012);

    if ( !ModuleInfo.g.RetStack ) {

        p = LclAlloc(sizeof(struct hll_item));
        ModuleInfo.g.RetStack = p;

        p->next = NULL;
        p->labels[LSTART] = 0;
        p->labels[LTEST] = 0;
        p->condlines = NULL;
        p->caselist = NULL;
        p->cmd = HLL_RETURN;
        p->labels[LEXIT] = GetHllLabel();
    }
    ExpandCStrings(tokenarray);

    /* .return [[val]] [[.if ...]] */

    i++;
    GetValue( i, tokenarray, &count, &directive, &retval );
    GetLabelStr( p->labels[LEXIT], label );

    if ( directive ) {

        if ( retval ) {

            x = i;
            i += count;
            p->labels[LSTART] = GetHllLabel();
            HllContinueIf( p, &i, tokenarray, LSTART, p, 0 );
            i = x;
            AssignValue( &i, tokenarray, count );
            AddLineQueueX( "jmp %s", label );
            AddLineQueueX( "%s:", GetLabelStr( p->labels[LSTART], label ) );
        } else {
            i += count;
            HllContinueIf( p, &i, tokenarray, LEXIT, p, 1 );
        }

    } else if ( retval ) {

        AssignValue( &i, tokenarray, count );
        AddLineQueueX( " jmp %s", label );
    } else {
        AddLineQueueX( " jmp %s", label );
    }

    if ( ModuleInfo.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 );
    if ( ModuleInfo.g.line_queue.head )
        RunLineQueue();
    return ( NOT_ERROR );
}

