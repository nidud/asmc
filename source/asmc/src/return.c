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

static int GetValue( int i, struct asm_tok tokenarray[], int *type,
        int *count, int *directive, int *retval )
{
    int b;
    int rc = i;

    *directive = 0;
    *count = 0;
    *retval = 0;
    *type = 0;

    if ( tokenarray[i].token != T_FINAL ) {

        /* .return real4(1.0) */

        if ( tokenarray[i].token == T_STYPE && tokenarray[i+1].token == T_OP_BRACKET ) {

            *type = i;
            i++;
            rc++;
        }

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
    return rc;
}

int CreateFloat( int, struct expr *, char * );

extern const unsigned int regax[];

static void AssignValue( int *iptr, struct asm_tok tokenarray[], int type, int count )
{
    struct  expr opnd;
    int     reg = regax[ModuleInfo.Ofssize];
    int     op = T_MOV;
    int     retval;
    int     directive;
    int     x, Assign;
    int     address;
    char    buffer[256];
    char *  p;
    char *  q;
    int     last_id;
    int     i = *iptr;

    if ( ExpandHllProc(buffer, i, tokenarray) != ERROR ) {

        if ( *buffer ) {

            QueueTestLines(buffer);
            *iptr = GetValue(i, tokenarray, &type, &count, &directive, &retval);
        }
    }

    if ( count ) {

        x = (int)(tokenarray[i+count].tokpos - tokenarray[i].tokpos);

        buffer[x] = 0;
        memcpy(buffer, tokenarray[i].tokpos, x);
    } else {
        strcpy(buffer, tokenarray[i].string_ptr);
    }

    p = buffer;
    address = 0;
    last_id = count + *iptr;
    if ( tokenarray[i].token == '(' && tokenarray[i+1].token == '&' ) {
        while ( *p != '&' )
            p++;
        p++;
        for ( q = p; *q; q++ ) ;
        q--;
        while ( *q <= ' ' ) {
            *q = '\0';
            q--;
        }
        if ( *q == ')' )
            *q = '\0';
        address++;
        (*iptr) += 2;
    } else if ( *p == '&' ) {
        p++;
        address++;
        (*iptr)++;
    }

    if ( EvalOperand( iptr, tokenarray, last_id, &opnd, EXPF_NOUNDEF ) == NOT_ERROR ) {

        Assign = 1;

        if ( address ) {

            op = T_LEA;

        } else if ( opnd.kind == EXPR_CONST ) {

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

        } else if ( opnd.kind == EXPR_FLOAT ) {

            if ( type == 0 && ( ( tokenarray[i].token == T_FLOAT && tokenarray[i].floattype ) ||
                  ( tokenarray[i].token == T_OP_BRACKET &&
                    tokenarray[i+1].token == T_FLOAT &&
                    tokenarray[i+1].floattype &&
                    tokenarray[i+2].token == T_CL_BRACKET ) ) ) {

                /* .return [(] 3F800000r [)] [[ .if ]] */

                if ( tokenarray[i].token == T_OP_BRACKET )
                    q = tokenarray[i+1].string_ptr;
                else
                    q = tokenarray[i].string_ptr;

                x = ( ( strlen( q ) - 1 ) / 2 );

                switch ( x ) {
                case 3:
                case 5:
                case 9:
                case 11:
                case 17:
                    if ( p[0] == '0' )
                        x--;
                    break;
                }

            } else {

                if ( type )
                    x = GetMemtypeSp(tokenarray[type].tokval);
                else
                    x = opnd.mem_type;
                x = SizeFromMemtype((unsigned char)x, USE_EMPTY, 0);
            }

            switch ( x ) {
            case 2:
                AddLineQueueX( " mov %r, %s", T_AX, p );
                AddLineQueueX( " movd %r, %r", T_XMM0, T_EAX );
                return;
            case 4:
                AddLineQueueX( " mov %r, %s", T_EAX, p );
                AddLineQueueX( " movd %r, %r", T_XMM0, T_EAX );
                return;
            case 8:
                AddLineQueueX( " mov %r, %s", T_RAX, p );
                AddLineQueueX( " movq %r, %r", T_XMM0, T_RAX );
                return;
            case 10:
                CreateFloat( 10, &opnd, buffer );
                AddLineQueueX( " movaps %r, xmmword ptr %s", T_XMM0, buffer );
                return;
            case 16:
                CreateFloat( 16, &opnd, buffer );
                AddLineQueueX( " movaps %r, %s", T_XMM0, buffer );
                return;
            }

        } else if ( opnd.kind == EXPR_ADDR ) {

            switch ( opnd.mem_type ) {
            case MT_BYTE:
            case MT_SBYTE:
            case MT_WORD:
                op = T_MOVZX;
                if ( reg == T_RAX )
                    reg = T_EAX;
                break;
            case MT_SWORD:
                if ( reg != T_AX ) {
                    op = T_MOVSX;
                    reg = T_EAX;
                }
                break;
            case MT_DWORD:
            case MT_SDWORD:
                reg = T_EAX;
                break;
            case MT_OWORD:
                if ( reg == T_RAX ) {
                    AddLineQueueX( "mov rax,qword ptr %s", p );
                    AddLineQueueX( "mov rdx,qword ptr %s[8]", p );
                    return;
                }
                break;
            case MT_REAL2:
                reg = T_AX;
                break;
            case MT_REAL4:
                reg = T_XMM0;
                op = T_MOVSS;
                break;
            case MT_REAL8:
                reg = T_XMM0;
                op = T_MOVSD;
                break;
            case MT_REAL16:
                reg = T_XMM0;
                op = T_MOVAPS;
                break;
            }
        }

        if ( Assign )
            AddLineQueueX( "%r %r,%s", op, reg, p );
    }
}

int ReturnDirective( int i, struct asm_tok tokenarray[] )
{
    int     type;
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
    i = GetValue( i, tokenarray, &type, &count, &directive, &retval );
    GetLabelStr( p->labels[LEXIT], label );

    if ( directive ) {

        if ( retval ) {

            x = i;
            i += count;
            p->labels[LSTART] = GetHllLabel();
            HllContinueIf( p, &i, tokenarray, LSTART, p, 0 );
            i = x;
            AssignValue( &i, tokenarray, type, count );
            AddLineQueueX( "jmp %s", label );
            AddLineQueueX( "%s:", GetLabelStr( p->labels[LSTART], label ) );
        } else {
            i += count;
            HllContinueIf( p, &i, tokenarray, LEXIT, p, 1 );
        }

    } else if ( retval ) {

        AssignValue( &i, tokenarray, type, count );
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
