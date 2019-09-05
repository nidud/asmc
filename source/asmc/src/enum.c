#include <globals.h>
#include <hllext.h>

struct asym *CurrEnum = NULL;

int EnumDirective(int i, struct asm_tok tokenarray[] )
{
    int rc = NOT_ERROR;
    char *name;
    struct expr opndx;
    struct asym *sym;
    int value;
    int x;

    if ( Parse_Pass > PASS_1 )
        return NOT_ERROR;

    if ( CurrEnum == NULL ) {

        CurrEnum = LclAlloc(sizeof(struct asym));
        CurrEnum->name = NULL;
        CurrEnum->value = 0;
        CurrEnum->mem_type = MT_SDWORD;

        i++;

        if ( tokenarray[i].token != T_FINAL ) {

            if ( tokenarray[i].token == T_STRING )
                CurrEnum->name = tokenarray[i].string_ptr;
            else
                AddLineQueueX( "%s typedef sdword", tokenarray[i].string_ptr );

            i++;
            if ( tokenarray[i].token == T_STRING ) {
                CurrEnum->name = tokenarray[i].string_ptr;
                i++;
            }
        }
        if ( ModuleInfo.list )
            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 );
    }

    while ( tokenarray[i].token != T_FINAL ) {

        name = tokenarray[i].string_ptr;
        i++;
        if ( tokenarray[i-1].token == T_STRING && name[0] == '}' ) {
            CurrEnum = NULL;
            break;
        }

        value = CurrEnum->value;
        CurrEnum->value++;

        if ( tokenarray[i].token == T_DIRECTIVE && tokenarray[i].tokval == T_EQU ) {

            i++;
            for ( x = i; x < Token_Count; x++ ) {
                if ( tokenarray[x].token == T_COMMA || tokenarray[x].token == T_FINAL )
                    break;
            }
            if ( x == i - 1 )
                break;
            rc = EvalOperand( &i, tokenarray, x, &opndx, 0 );
            if ( rc == ERROR )
                break;
            if ( opndx.kind != EXPR_CONST ) {
                rc = asmerr( 2026 );
                break;
            }
            value = opndx.value;
            CurrEnum->value = value + 1;
        }

        if ( tokenarray[i].token == T_COMMA )
            i++;
        else if ( tokenarray[i].token == T_FINAL && CurrEnum->name == NULL )
            CurrEnum = NULL;

        AddLineQueueX( "%s equ %d", name, value );
    }
    if ( tokenarray[i].token != T_FINAL )
        return asmerr( 2008, tokenarray[i].tokpos );

    if ( ModuleInfo.g.line_queue.head ) {
        sym = CurrEnum;
        CurrEnum = NULL;
        RunLineQueue();
        CurrEnum = sym;
    }
    return rc;
}
