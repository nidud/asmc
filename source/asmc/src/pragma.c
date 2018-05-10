#include <string.h>
#include <globals.h>
#include <types.h>
#include <hllext.h>

#define MAXSTACK 16

static int ListCount = 0;
static int PackCount = 0;
static int CrefCount = 0;

static char PackStack[MAXSTACK];
static char ListStack[MAXSTACK];
static char CrefStack[MAXSTACK];

int PragmaDirective( int i, struct asm_tok tokenarray[] )
{
    struct expr opndx;
    char *p, *q, *s;
    int rc = NOT_ERROR, list_directive = 0;

    i++;
    if ( tokenarray[i].token == T_OP_BRACKET || tokenarray[i].token == T_COMMA )
        i++;
    p = tokenarray[i].string_ptr;
    i++;
    if ( tokenarray[i].token == T_OP_BRACKET )
        i++;

    if ( _stricmp(p, "pack" ) == 0 ) {

        if ( tokenarray[i].tokval == T_POP ) {

            i++;
            if ( tokenarray[i].token == T_CL_BRACKET )
                i++;

            if ( PackCount ) {

                PackCount--;
                ModuleInfo.fieldalign = PackStack[PackCount];
            }

        } else if ( tokenarray[i].tokval == T_PUSH && PackCount < MAXSTACK ) {

            i++;
            PackStack[PackCount++] = ModuleInfo.fieldalign;
            if ( tokenarray[i].token == T_OP_BRACKET || tokenarray[i].token == T_COMMA )
                i++;

            AddLineQueueX( "OPTION FIELDALIGN: %s", tokenarray[i].string_ptr );
            i++;
            if ( tokenarray[i].token == T_CL_BRACKET )
                i++;
        }

    } else if ( _stricmp(p, "list" ) == 0 ) {

        list_directive++;

        if ( tokenarray[i].tokval == T_POP ) {

            if ( ListCount ) {

                ListCount--;
                ModuleInfo.list = ListStack[ListCount];
                i++;
                if ( tokenarray[i].token == T_CL_BRACKET )
                    i++;
            }
        } else if ( tokenarray[i].tokval == T_PUSH && ListCount < MAXSTACK ) {

            i++;
            ListStack[ListCount++] = ModuleInfo.list;
            if ( tokenarray[i].token == T_COMMA )
                i++;

            if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) != ERROR ) {

                if ( opndx.kind != EXPR_CONST )
                    asmerr( 2026 );
                else if ( opndx.uvalue > 1 )
                    asmerr( 2084 );
                else {
                    ModuleInfo.list = opndx.uvalue;
                    if ( opndx.uvalue )
                        ModuleInfo.line_flags |= LOF_LISTED;
                    if ( tokenarray[i].token == T_CL_BRACKET )
                        i++;
                }
            }
        }

    } else if ( _stricmp(p, "cref" ) == 0 ) {

        list_directive++;

        if ( tokenarray[i].tokval == T_POP ) {

            if ( CrefCount ) {

                CrefCount--;
                ModuleInfo.cref = CrefStack[CrefCount];
                i++;
                if ( tokenarray[i].token == T_CL_BRACKET )
                    i++;
            }

        } else if ( tokenarray[i].tokval == T_PUSH && CrefCount < MAXSTACK ) {

            i++;
            CrefStack[CrefCount++] = ModuleInfo.cref;
            if ( tokenarray[i].token == T_COMMA )
                i++;

            if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) != ERROR ) {

                if ( opndx.kind != EXPR_CONST )
                    asmerr( 2026 );
                else if ( opndx.uvalue > 1 )
                    asmerr( 2084 );
                else {
                    ModuleInfo.cref = opndx.uvalue;
                    if ( opndx.uvalue )
                        ModuleInfo.line_flags |= LOF_LISTED;
                    if ( tokenarray[i].token == T_CL_BRACKET )
                        i++;
                }
            }
        }

    } else {

        s = NULL;
        if ( _stricmp(p, "init" ) == 0 )
            s = "INIT";
        else if ( _stricmp(p, "exit" ) == 0 )
            s = "EXIT";
        if ( s ) {

            q = "dw";
            if ( ModuleInfo.Ofssize == USE32 )
                q = "dd";
            else if ( ModuleInfo.Ofssize == USE64 )
                q = "dq";

            AddLineQueueX( "_%s segment PARA FLAT PUBLIC '%s'", s, s );
            AddLineQueueX( " %s %s", q, tokenarray[i].string_ptr );
            i++;
            if ( tokenarray[i].token == T_COMMA )
                i++;
            AddLineQueueX( " %s %s", q, tokenarray[i].string_ptr );
            AddLineQueueX( "_%s ends", s );
            i++;
            if ( tokenarray[i].token == T_CL_BRACKET )
                i++;
        }
    }

    if ( tokenarray[i].token == T_CL_BRACKET )
        i++;
    if ( tokenarray[i].token != T_FINAL )
        rc = asmerr( 2008, tokenarray[i].tokpos );

    if ( !list_directive ) {
        if ( ModuleInfo.list )
            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 );
        if ( is_linequeue_populated() )
            RunLineQueue();
    }
    return rc;
}

void PragmaInit(void)
{
    ListCount = 0;
    PackCount = 0;
    CrefCount = 0;
}

int PragmaCheckOpen(void)
{
    if ( ListCount || PackCount || CrefCount )
        return asmerr( 1010, ".pragma-push-pop" );
    return NOT_ERROR;
}
