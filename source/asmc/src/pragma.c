#include <string.h>
#include <globals.h>
#include <hllext.h>
#include <types.h>

void AsmcKeywords( unsigned );

#define MAXSTACK 16

typedef struct {
    short   id;
    char    state;
} pragma_warning;

static pragma_warning pragma_wtable[] = {
        { 4003, 0 },
        { 4005, 0 },
        { 4006, 0 },
        { 4007, 0 },
        { 4008, 0 },
        { 4011, 0 },
        { 4012, 0 },
        { 4910, 0 },
        { 6003, 0 },
        { 6004, 0 },
        { 6005, 0 },
        { 8000, 0 },
        { 8001, 0 },
        { 8002, 0 },
        { 8003, 0 },
        { 8004, 0 },
        { 8005, 0 },
        { 8006, 0 },
        { 8007, 0 },
        { 8008, 0 },
        { 8009, 0 },
        { 8010, 0 },
        { 8011, 0 },
        { 8012, 0 },
        { 8013, 0 },
        { 8014, 0 },
        { 8015, 0 },
        { 8017, 0 },
        { 8018, 0 },
        { 8019, 0 },
        { 8020, 0 },
        { 7000, 0 },
        { 7001, 0 },
        { 7002, 0 },
        { 7003, 0 },
        { 7004, 0 },
        { 7005, 0 },
        { 7006, 0 },
        { 7007, 0 },
        { 7008, 0 }
};

#define wtable_count (sizeof(pragma_wtable)/sizeof(pragma_wtable[0]))

static int ListCount = 0;
static int PackCount = 0;
static int CrefCount = 0;
static int WarnCount = 0;
static int AsmcCount = 0;

static char PackStack[MAXSTACK];
static char ListStack[MAXSTACK];
static char CrefStack[MAXSTACK];
static char *WarnStack[MAXSTACK];
static char AsmcStack[MAXSTACK];

int PragmaDirective( int i, struct asm_tok tokenarray[] )
{
    struct expr opndx;
    char *p, *q, *s;
    char stdlib[256];
    char dynlib[256];
    int x, rc = NOT_ERROR, list_directive = 0;

    i++;
    if ( tokenarray[i].token == T_OP_BRACKET || tokenarray[i].token == T_COMMA )
        i++;
    p = tokenarray[i].string_ptr;
    i++;
    if ( tokenarray[i].token == T_OP_BRACKET )
        i++;

    if ( _stricmp(p, "asmc" ) == 0 ) {

        if ( tokenarray[i].tokval == T_POP ) {

            i++;
            if ( tokenarray[i].token == T_CL_BRACKET )
                i++;

            if ( AsmcCount ) {

                AsmcCount--;
                x = ModuleInfo.strict_masm_compat;
                if ( x != AsmcStack[AsmcCount] ) {
                    ModuleInfo.strict_masm_compat = AsmcStack[AsmcCount];
                    AsmcKeywords( x );
                }
            }

        } else if ( tokenarray[i].tokval == T_PUSH && AsmcCount < MAXSTACK ) {

            i++;
            AsmcStack[AsmcCount++] = ModuleInfo.strict_masm_compat;
            if ( tokenarray[i].token == T_OP_BRACKET || tokenarray[i].token == T_COMMA )
                i++;

            if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) != ERROR ) {

                if ( opndx.kind != EXPR_CONST )
                    asmerr( 2026 );
                else if ( opndx.uvalue > 1 )
                    asmerr( 2084 );
                else {
                    x = 1;
                    if ( opndx.uvalue )
                        x = 0;
                    if ( ModuleInfo.strict_masm_compat != x ) {
                        AsmcKeywords( ModuleInfo.strict_masm_compat );
                        ModuleInfo.strict_masm_compat = x;
                    }
                    if ( tokenarray[i].token == T_CL_BRACKET )
                        i++;
                }
            }
        }
    } else if ( _stricmp(p, "pack" ) == 0 ) {

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

    } else if ( _stricmp(p, "warning" ) == 0 ) {

        if ( tokenarray[i].tokval == T_POP ) {

            if ( WarnCount ) {
                i++;
                if ( tokenarray[i].token == T_CL_BRACKET )
                    i++;
                WarnCount--;
                for ( x = 0, p = WarnStack[WarnCount]; x < wtable_count; x++ )
                    pragma_wtable[x].state = p[x];
                MemFree(WarnStack[WarnCount]);
            }

        } else if ( tokenarray[i].tokval == T_PUSH ) {

            if ( WarnCount < MAXSTACK ) {

                i++;
                if ( tokenarray[i].token == T_CL_BRACKET )
                    i++;

                p = MemAlloc(wtable_count);
                WarnStack[WarnCount++] = p;
                for ( x = 0; x < wtable_count; x++ )
                    p[x] = pragma_wtable[x].state;
            }
        } else if ( tokenarray[i+1].token == T_COLON &&
                    _stricmp( tokenarray[i].string_ptr, "disable" ) == 0 ) {
            i += 2;
            if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) != ERROR ) {

                if ( opndx.kind != EXPR_CONST ) {
                    asmerr( 2026 );
                } else {

                    for ( x = 0; x < wtable_count; x++ ) {
                        if ( pragma_wtable[x].id == opndx.uvalue ) {

                            pragma_wtable[x].state = 1;
                            break;
                        }
                    }
                    i++;
                    if ( tokenarray[i].token == T_CL_BRACKET )
                        i++;
                }
            }
        }

    } else if ( _stricmp( p, "comment" ) == 0 &&
                _stricmp( tokenarray[i].string_ptr, "lib" ) == 0  ) {

            i += 2;
            strcpy( stdlib, tokenarray[i].string_ptr );
            if ( stdlib[0] == '"' ) {
                strcpy( stdlib, &stdlib[1] );
                p = strchr( stdlib, '"' );
                if ( p )
                    *p = '\0';
                p = strchr( stdlib, '.' );
                if ( p )
                    *p = '\0';
            }
            dynlib[0] = 0;
            if ( tokenarray[i+1].token == T_COMMA ) {
                i += 2;
                strcpy( dynlib, tokenarray[i].string_ptr );
                if ( dynlib[0] == '"' ) {
                    strcpy( dynlib, &dynlib[1] );
                    p = strchr( dynlib, '"' );
                    if ( p )
                        *p = '\0';
                }
                p = strchr( dynlib, '.' );
                if ( p )
                    *p = '\0';
            }

            p = dynlib;
            if ( Options.output_format == OFORMAT_BIN ) {

                if ( dynlib[0] == '\0' )
                    p = stdlib;

                AddLineQueueX( " option dllimport:<%s>", p );

            } else if ( dynlib[0] == '\0' ) {

                AddLineQueueX( "includelib %s.lib", stdlib );

            } else {

                AddLineQueueX( "ifdef _%s", _strupr( p ) );
                AddLineQueueX( "includelib %s.lib", _strlwr( p ) );
                AddLineQueue(  "else" );
                AddLineQueueX( "includelib %s.lib", stdlib );
                AddLineQueue(  "endif" );
            }
            i++;
            if ( tokenarray[i].token == T_CL_BRACKET )
                i++;

    } else {

        s = NULL;
        if ( _stricmp(p, "init" ) == 0 )
            s = ".CRT$XIA";
        else if ( _stricmp(p, "exit" ) == 0 )
            s = ".CRT$XTA";
        if ( s ) {

            if ( !ModuleInfo.dotname )
                AddLineQueueX( " %r dotname", T_OPTION );
            AddLineQueueX( " %s %r %r(%d) 'CONST'", s, T_SEGMENT, T_ALIGN,
                ( 2 << ModuleInfo.Ofssize ) );
            p = tokenarray[i].string_ptr;
            i++;
            if ( tokenarray[i].token == T_COMMA )
                i++;
            if ( ModuleInfo.Ofssize == USE64 )
                AddLineQueueX( " dd %r %s, %s", T_IMAGEREL, p, tokenarray[i].string_ptr );
            else
                AddLineQueueX( " dd %s, %s", p, tokenarray[i].string_ptr );
            AddLineQueueX( " %s %r", s, T_ENDS );
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
