#include <globals.h>
#include <hllext.h>

struct asym *CurrEnum = NULL;

int EnumDirective(int i, struct asm_tok tokenarray[] )
{
    int rc = NOT_ERROR;
    char *name;
    struct expr opndx;
    struct asym *sym;
    int type;
    int x;

    if ( Parse_Pass > PASS_1 )
        return NOT_ERROR;

    if ( CurrEnum == NULL ) {

        CurrEnum = LclAlloc(sizeof(struct asym));
        CurrEnum->name = NULL;
        CurrEnum->value = 0;
        CurrEnum->total_size = 4;
        CurrEnum->mem_type = MT_SDWORD;

        i++;

        if ( tokenarray[i].token != T_FINAL ) {
            if ( tokenarray[i].token == T_STRING ) {
                CurrEnum->name = tokenarray[i].string_ptr;
                name = tokenarray[i].tokpos;
                i++;
                if ( name[0] == '{' && name[1] ) {
                    name++;
                    Token_Count += Tokenize( name, 0, &tokenarray[i], TOK_DEFAULT );
                }
            } else {
                type = T_SDWORD;
                name = tokenarray[i].string_ptr;
                i++;
                if ( tokenarray[i].token == T_COLON ) {
                    i++;
                    x = i + 1;
                    rc = EvalOperand( &i, tokenarray, x, &opndx, 0 );
                    if ( rc != ERROR ) {
                        CurrEnum->total_size = opndx.value;
                        if ( opndx.mem_type & MT_SIGNED ) {
                            if ( opndx.value == 2 ) {
                                type = T_SWORD;
                                CurrEnum->mem_type = MT_SWORD;
                            } else if ( opndx.value == 1 ) {
                                type = T_SBYTE;
                                CurrEnum->mem_type = MT_SBYTE;
                            }
                        } else {
                            switch ( opndx.value ) {
                            case 4:
                                type = T_DWORD;
                                CurrEnum->mem_type = MT_DWORD;
                            case 2:
                                type = T_WORD;
                                CurrEnum->mem_type = MT_WORD;
                            case 1:
                                type = T_BYTE;
                                CurrEnum->mem_type = MT_BYTE;
                            }
                        }
                    }
                }
                AddLineQueueX( "%s typedef %r", name, type );
            }
            if ( tokenarray[i].token == T_STRING ) {
                CurrEnum->name = tokenarray[i].string_ptr;
                name = tokenarray[i].tokpos;
                i++;
                if ( name[0] == '{' && name[1] ) {
                    name++;
                    Token_Count += Tokenize( name, 0, &tokenarray[i], TOK_DEFAULT );
                }
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

        opndx.value = CurrEnum->value;
        CurrEnum->value++;

        if ( tokenarray[i].token == T_DIRECTIVE && tokenarray[i].tokval == T_EQU ) {

            i++;
            for ( x = i; x < Token_Count; x++ ) {
                if ( tokenarray[x].token == T_COMMA ||
                     tokenarray[x].token == T_STRING ||
                     tokenarray[x].token == T_FINAL )
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
            x = 1;
            if ( opndx.value & 0xFFFF0000 )
                x = 4;
            else if ( opndx.value & 0xFF00 )
                x = 2;
            if ( opndx.hvalue || x > CurrEnum->total_size ) {
                if ( opndx.hvalue == -1 )
                    opndx.value |= 0x80000000;
                else {
                    rc = asmerr(2071);
                    break;
                }
            }
            CurrEnum->value = opndx.value + 1;
        }
        if ( CurrEnum->mem_type & MT_SIGNED )
            AddLineQueueX("%s equ %d", name, opndx.value);
        else
            AddLineQueueX("%s equ %u", name, opndx.value);
        if ( tokenarray[i].token == T_COMMA )
            i++;
        else if ( tokenarray[i].token == T_FINAL && CurrEnum->name == NULL )
            CurrEnum = NULL;
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
