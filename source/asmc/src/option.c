/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	Processing of OPTION directive.
*
****************************************************************************/

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <reswords.h>
#include <expreval.h>
#include <equate.h>

/* prototypes */
#ifndef __ASMC64__
extern struct asym *sym_Interface;
#endif

#define OPTQUAL
#define OPTFUNC( name ) static ret_code OPTQUAL name( int *pi, struct asm_tok tokenarray[] )

/* OPTION directive helper functions */

/* OPTION DOTNAME */

OPTFUNC( SetDotName )
/*******************/
{
    ModuleInfo.dotname = TRUE;
    return( NOT_ERROR );
}

/* OPTION NODOTNAME */

OPTFUNC( SetNoDotName )
/*********************/
{
    ModuleInfo.dotname = FALSE;
    return( NOT_ERROR );
}

/* OPTION CASEMAP:NONE | NOTPUBLIC | ALL */

OPTFUNC( SetCaseMap )
/*******************/
{
    int i = *pi;
    if ( tokenarray[i].token == T_ID ) {
	if ( 0 == _stricmp( tokenarray[i].string_ptr, "NONE" ) ) {
	    ModuleInfo.case_sensitive = TRUE;	     /* -Cx */
	    ModuleInfo.convert_uppercase = FALSE;
	} else if ( 0 == _stricmp( tokenarray[i].string_ptr, "NOTPUBLIC" ) ) {
	    ModuleInfo.case_sensitive = FALSE;	     /* -Cp */
	    ModuleInfo.convert_uppercase = FALSE;
	} else if ( 0 == _stricmp( tokenarray[i].string_ptr, "ALL" ) ) {
	    ModuleInfo.case_sensitive = FALSE;	     /* -Cu */
	    ModuleInfo.convert_uppercase = TRUE;
	} else {
	    return( asmerr(2008, tokenarray[i].tokpos ) );
	}
	i++;
	SymSetCmpFunc();
    } else {
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION M510 */

OPTFUNC( SetM510 )
/****************/
{
    SetMasm510( TRUE );
    return( NOT_ERROR );
}

/* OPTION NOM510 */

OPTFUNC( SetNoM510 )
/******************/
{
    SetMasm510(FALSE);
    return( NOT_ERROR );
}

/* OPTION SCOPED */

OPTFUNC( SetScoped )
/******************/
{
    ModuleInfo.scoped = TRUE;
    return( NOT_ERROR );
}

/* OPTION NOSCOPED */

OPTFUNC( SetNoScoped )
/********************/
{
    ModuleInfo.scoped = FALSE;
    return( NOT_ERROR );
}

/* OPTION OLDSTRUCTS */

OPTFUNC( SetOldStructs )
/**********************/
{
    ModuleInfo.oldstructs = TRUE;
    return( NOT_ERROR );
}

/* OPTION NOOLDSTRUCTS */

OPTFUNC( SetNoOldStructs )
/************************/
{
    ModuleInfo.oldstructs = FALSE;
    return( NOT_ERROR );
}

/* OPTION EMULATOR */

OPTFUNC( SetEmulator )
/********************/
{
    ModuleInfo.emulator = TRUE;
    return( NOT_ERROR );
}

/* OPTION NOEMULATOR */

OPTFUNC( SetNoEmulator )
/**********************/
{
    ModuleInfo.emulator = FALSE;
    return( NOT_ERROR );
}

/* OPTION LJMP */

OPTFUNC( SetLJmp )
/****************/
{
    ModuleInfo.ljmp = TRUE;
    return( NOT_ERROR );
}

/* OPTION NOLJMP */

OPTFUNC( SetNoLJmp )
/******************/
{
    ModuleInfo.ljmp = FALSE;
    return( NOT_ERROR );
}

/* OPTION NOREADONLY */

OPTFUNC( SetNoReadonly )
/**********************/
{
    /* default, nothing to do */
    return( NOT_ERROR );
}

/* OPTION NOOLDMACROS */

OPTFUNC( SetNoOldmacros )
/***********************/
{
    /* default, nothing to do */
    return( NOT_ERROR );
}

/* OPTION EXPR32 */

OPTFUNC( SetExpr32 )
/******************/
{
    /* default, nothing to do */
    return( NOT_ERROR );
}

OPTFUNC( SetNoSignExt )
/*********************/
{
    ModuleInfo.NoSignExtend = TRUE;
    return( NOT_ERROR );
}

static void SkipOption( int *pi, struct asm_tok tokenarray[] )
/************************************************************/
{
    while ( tokenarray[*pi].token != T_FINAL &&
	   tokenarray[*pi].token != T_COMMA )
	(*pi)++;
}

/* OPTION NOKEYWORD: <keyword[,keyword,...]>
 */

OPTFUNC( SetNoKeyword )
/*********************/
{
    int i = *pi;
    //struct ReservedWord *resw;
    unsigned index;
    char *p;

    if( Parse_Pass != PASS_1 ) {
	SkipOption( pi, tokenarray );
	return( NOT_ERROR);
    }
    if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' ) {
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }
    for ( p = tokenarray[i].string_ptr; *p; ) {
	while ( islspace( *p ) ) p++;
	if ( *p ) {
	    char *p2 = p;
	    unsigned char cnt;
	    //struct instr_item *instruct;
	    for ( ;*p; p++ ) {
		if ( islspace( *p ) || *p == ',' )
		    break;
	    }
	    cnt = p - p2;
	    /* todo: if MAX_ID_LEN can be > 255, then check size,
	     * since a reserved word's size must be <= 255
	     */
	    index = FindResWord( p2, cnt );
	    if ( index != 0 )
		DisableKeyword( index );
	    else {
		if ( IsKeywordDisabled( p2, cnt ) ) {
		    return( asmerr( 2086 ) );
		}
	    }
	}
	while ( islspace(*p) ) p++;
	if (*p == ',') p++;
    }
    i++;
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION LANGUAGE:{C|PASCAL|BASIC|FORTRAN|SYSCALL|STDCALL|FASTCALL} */

OPTFUNC( SetLanguage )
/********************/
{
    int i = *pi;

    if( tokenarray[i].token == T_ID && (tokenarray[i].string_ptr[0] | 0x20) == 'c'
	&& tokenarray[i].string_ptr[1] == '\0') {
	tokenarray[i].token = T_RES_ID;
	tokenarray[i].tokval = T_CCALL;
	tokenarray[i].bytval = 1;
    }
    if ( tokenarray[i].token == T_RES_ID ) {
	if ( GetLangType( &i, tokenarray, &ModuleInfo.langtype ) == NOT_ERROR ) {
	    /* update @Interface assembly time variable */
#ifndef __ASMC64__
	    if ( ModuleInfo.model != MODEL_NONE && sym_Interface )
		sym_Interface->value = ModuleInfo.langtype;
#endif
	    *pi = i;
	    return( NOT_ERROR );
	}
    }
    return( asmerr(2008, tokenarray[i].tokpos ) );
}

/* OPTION SETIF2
 * syntax: option setif2:TRUE|FALSE
 */

OPTFUNC( SetSetIF2 )
/******************/
{
    int i = *pi;

    if ( 0 == _stricmp( tokenarray[i].string_ptr, "TRUE" ) ) {
	ModuleInfo.setif2 = TRUE;
	i++;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "FALSE" ) ) {
	ModuleInfo.setif2 = FALSE;
	i++;
    }
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION PROLOGUE:macroname
 the prologue macro must be a macro function with 6 params:
 name macro procname, flag, parmbytes, localbytes, <reglist>, userparms
 procname: name of procedure
 flag: bits 0-2: calling convention
 bit 3: undef
 bit 4: 1 if caller restores ESP
 bit 5: 1 if proc is far
 bit 6: 1 if proc is private
 bit 7: 1 if proc is export
 bit 8: for epilogue: 1 if IRET, 0 if RET
 parmbytes: no of bytes for all params
 localbytes: no of bytes for all locals
 reglist: list of registers to save/restore, separated by commas
 userparms: prologuearg specified in PROC
 */

OPTFUNC( SetPrologue )
/********************/
{
    int i = *pi;

    if ( tokenarray[i].token != T_ID ) {
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }
    if ( ModuleInfo.proc_prologue ) {
	ModuleInfo.proc_prologue = NULL;
    }
    if ( 0 == _stricmp( tokenarray[i].string_ptr, "NONE" ) ) {
	ModuleInfo.prologuemode = PEM_NONE;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "PROLOGUEDEF" ) ) {
	ModuleInfo.prologuemode = PEM_DEFAULT;
    } else {
	ModuleInfo.prologuemode = PEM_MACRO;
	ModuleInfo.proc_prologue = (char *)LclAlloc( strlen( tokenarray[i].string_ptr ) + 1);
	strcpy( ModuleInfo.proc_prologue, tokenarray[i].string_ptr );
    }

    i++;
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION EPILOGUE:macroname */
/*
 do NOT check the macros here!
 */

OPTFUNC( SetEpilogue )
/********************/
{
    int i = *pi;

    if ( tokenarray[i].token != T_ID ) {
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }

    if ( 0 == _stricmp( tokenarray[i].string_ptr, "FLAGS" ) ) {
	ModuleInfo.epilogueflags = 1;
    } else {

	ModuleInfo.proc_epilogue = NULL;

	if ( 0 == _stricmp( tokenarray[i].string_ptr, "NONE" ) ) {
	    ModuleInfo.epiloguemode = PEM_NONE;
	} else if ( 0 == _stricmp( tokenarray[i].string_ptr, "EPILOGUEDEF" ) ) {
	    ModuleInfo.epiloguemode = PEM_DEFAULT;
	} else {
	    ModuleInfo.epiloguemode = PEM_MACRO;
	    ModuleInfo.proc_epilogue = (char *)LclAlloc( strlen( tokenarray[i].string_ptr ) + 1);
	    strcpy( ModuleInfo.proc_epilogue, tokenarray[i].string_ptr );
	}
    }

    i++;
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION OFFSET: GROUP | FLAT | SEGMENT
 * default is GROUP.
 * determines result of OFFSET operator fixups if .model isn't set.
 */
OPTFUNC( SetOffset )
/******************/
{
    int i = *pi;

    if ( 0 == _stricmp( tokenarray[i].string_ptr, "GROUP" ) ) {
	ModuleInfo.offsettype = OT_GROUP;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "FLAT" ) ) {
	ModuleInfo.offsettype = OT_FLAT;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "SEGMENT" ) ) {
	ModuleInfo.offsettype = OT_SEGMENT;
    } else {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    i++;
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION PROC:PRIVATE | PUBLIC | EXPORT */

OPTFUNC( SetProc )
/****************/
{
    int i = *pi;

    switch ( tokenarray[i].token ) {
    case T_ID:
	if ( 0 == _stricmp( tokenarray[i].string_ptr, "PRIVATE" ) ) {
	    ModuleInfo.procs_private = TRUE;
	    ModuleInfo.procs_export = FALSE;
	    i++;
	} else if ( 0 == _stricmp( tokenarray[i].string_ptr, "EXPORT" ) ) {
	    ModuleInfo.procs_private = FALSE;
	    ModuleInfo.procs_export = TRUE;
	    i++;
	}
	break;
    case T_DIRECTIVE: /* word PUBLIC is a directive */
	if ( tokenarray[i].tokval == T_PUBLIC ) {
	    ModuleInfo.procs_private = FALSE;
	    ModuleInfo.procs_export = FALSE;
	    i++;
	}
	break;
    }
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION SEGMENT:USE16|USE32|FLAT
 * this option set the default offset size for segments and
 * externals defined outside of segments.
 */

OPTFUNC( SetSegment )
/*******************/
{
    int i = *pi;

    if ( tokenarray[i].token == T_RES_ID && tokenarray[i].tokval == T_FLAT ) {
	if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_64 )
	    ModuleInfo.defOfssize = USE64;
	else
	    ModuleInfo.defOfssize = USE32;
    } else if ( tokenarray[i].token == T_ID && _stricmp( tokenarray[i].string_ptr, "USE16" ) == 0) {
	ModuleInfo.defOfssize = USE16;
    } else if ( tokenarray[i].token == T_ID && _stricmp( tokenarray[i].string_ptr, "USE32" ) == 0) {
	ModuleInfo.defOfssize = USE32;
    } else if ( tokenarray[i].token == T_ID && _stricmp( tokenarray[i].string_ptr, "USE64" ) == 0) {
	ModuleInfo.defOfssize = USE64;
    } else {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    i++;
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION LOOPALIGN:0|1|2|4|8|16 */

#define MAX_LOOP_ALIGN 16

OPTFUNC( SetLoopAlign )
{
    int i = *pi;
    unsigned temp, temp2;
    struct expr opndx;

    if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
	return( ERROR );
    if ( opndx.kind != EXPR_CONST ) {
	return( asmerr( 2026 ) );
    }
    if( opndx.uvalue > MAX_LOOP_ALIGN ) {
	return( asmerr( 2064 ) );
    }

    temp2 = 0;
    if ( opndx.uvalue ) {
	    for( temp = 1;  temp < opndx.uvalue ; temp <<= 1, temp2++ );
	    if( temp != opndx.uvalue ) {
		return( asmerr( 2063, opndx.value ) );
	    }
    }

    ModuleInfo.loopalign = temp2;
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION CASEALIGN:0|1|2|4|8|16 */

#define MAX_CASE_ALIGN 16

OPTFUNC( SetCaseAlign )
{
    int i = *pi;
    unsigned temp, temp2;
    struct expr opndx;

    if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
	return( ERROR );
    if ( opndx.kind != EXPR_CONST ) {
	return( asmerr( 2026 ) );
    }
    if( opndx.uvalue > MAX_CASE_ALIGN ) {
	return( asmerr( 2064 ) );
    }
    temp2 = 0;
    if ( opndx.uvalue ) {
	    for( temp = 1; temp < opndx.uvalue ; temp <<= 1, temp2++ );
	    if( temp != opndx.uvalue ) {
		return( asmerr( 2063, opndx.value ) );
	    }
    }
    ModuleInfo.casealign = temp2;
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION FIELDALIGN:1|2|4|8|16|32 */

OPTFUNC( SetFieldAlign )
{
    int i = *pi;
    unsigned temp, temp2;
    struct expr opndx;

    if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
	return( ERROR );
    if ( opndx.kind != EXPR_CONST ) {
	return( asmerr( 2026 ) );
    }
    if( opndx.uvalue > MAX_STRUCT_ALIGN ) {
	return( asmerr( 2064 ) );
    }
    for( temp = 1, temp2 = 0; temp < opndx.uvalue ; temp <<= 1, temp2++ );
    if( temp != opndx.uvalue ) {
	return( asmerr( 2063, opndx.value ) );
    }
    ModuleInfo.fieldalign = temp2;
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION PROCALIGN:1|2|4|8|16|32 */

OPTFUNC( SetProcAlign )
/*********************/
{
    int i = *pi;
    int temp, temp2;
    struct expr opndx;

    if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
	return( ERROR );
    if ( opndx.kind != EXPR_CONST ) {
	return( asmerr( 2026 ) );
    }
    if( opndx.value > MAX_STRUCT_ALIGN ) {
	asmerr( 2064 );
    }
    for( temp = 1, temp2 = 0; temp < opndx.value ; temp <<= 1, temp2++ );
    if( temp != opndx.value ) {
	return( asmerr( 2063, opndx.value ) );
    }
    ModuleInfo.procalign = temp2;
    *pi = i;
    return( NOT_ERROR );
}

OPTFUNC( SetMZ )
/**************/
{
    int i = *pi;
    int j;
    uint_16 *parms;
    struct expr opndx;

    for ( j = 0, parms = (uint_16 *)&ModuleInfo.mz_data ; j < 4; j++ ) {
	int k;
	for ( k = i; tokenarray[k].token != T_FINAL; k++ )
	    if ( tokenarray[k].token == T_COMMA ||
		tokenarray[k].token == T_COLON ||
		tokenarray[k].token == T_DBL_COLON )
		break;
	if ( EvalOperand( &i, tokenarray, k, &opndx, 0 ) == ERROR )
	    return( ERROR );
	if ( opndx.kind == EXPR_EMPTY ) {
	} else if ( opndx.kind == EXPR_CONST ) {
	    if ( opndx.value64 > 0xFFFF ) {
		return( EmitConstError( &opndx ) );
	    }
	    if ( ModuleInfo.sub_format == SFORMAT_MZ )
		*(parms + j) = opndx.value;
	} else {
	    return( asmerr( 2026 ) );
	}
	if ( tokenarray[i].token == T_COLON )
	    i++;
	else if ( tokenarray[i].token == T_DBL_COLON ) {
	    i++;
	    j++;
	}
    }

    /* ensure data integrity of the params */
    if ( ModuleInfo.sub_format == SFORMAT_MZ ) {
	if ( ModuleInfo.mz_data.ofs_fixups < 0x1E )
	    ModuleInfo.mz_data.ofs_fixups = 0x1E;

	for( j = 16; j < ModuleInfo.mz_data.alignment; j <<= 1 );
	if( j != ModuleInfo.mz_data.alignment )
	    asmerr( 2189, j );

	if ( ModuleInfo.mz_data.heapmax < ModuleInfo.mz_data.heapmin )
	    ModuleInfo.mz_data.heapmax = ModuleInfo.mz_data.heapmin;
    }
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION FRAME: AUTO | NOAUTO
 * default is NOAUTO
 */
OPTFUNC( SetFrame )
/*****************/
{
    int i = *pi;

    if ( 0 == _stricmp( tokenarray[i].string_ptr, "AUTO" ) ) {
	ModuleInfo.frame_auto = 1;
	i++;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "NOAUTO" ) ) {
	ModuleInfo.frame_auto = 0;
	i++;
    }
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION CSTACK: ON | OFF
 */
OPTFUNC( SetCStack )
/*****************/
{
    int i = *pi;

    if ( 0 == _stricmp( tokenarray[i].string_ptr, "ON" ) ) {
	ModuleInfo.xflag |= OPT_CSTACK;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "OFF" ) ) {
	ModuleInfo.xflag &= ~OPT_CSTACK;
    } else {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    *pi = i + 1;
    return NOT_ERROR;
}

/* OPTION WSTRING: ON | OFF
 */
OPTFUNC( SetWString )
/*****************/
{
    int i = *pi;

    if ( 0 == _stricmp( tokenarray[i].string_ptr, "ON" ) ) {
	ModuleInfo.xflag |= OPT_WSTRING;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "OFF" ) ) {
	ModuleInfo.xflag &= ~OPT_WSTRING;
    } else {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    *pi = i + 1;
    return NOT_ERROR;
}

/* OPTION CODEPAGE: <value>
 */
OPTFUNC( SetCodePage )
/***************/
{
    int i = *pi;
    struct expr opndx;

    if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )
	return( ERROR );
    if ( opndx.kind == EXPR_CONST ) {
	if ( opndx.llvalue > 0xFFFF )
	    return( EmitConstError( &opndx ) );
	ModuleInfo.codepage = opndx.value;
    } else {
	return( asmerr( 2026 ) );
    }
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION SWITCH: C | PASCAL | TABLE | NOTABLE | REGAX | NOREGS
 */
OPTFUNC( SetSwitch )
/*****************/
{
    int i = *pi;

    if ( 0 == _stricmp( tokenarray[i].string_ptr, "C" ) ) {
	ModuleInfo.xflag &= ~OPT_PASCAL;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "PASCAL" ) ) {
	ModuleInfo.xflag |= OPT_PASCAL;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "TABLE" ) ) {
	ModuleInfo.xflag &= ~OPT_NOTABLE;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "NOTABLE" ) ) {
	ModuleInfo.xflag |= OPT_NOTABLE;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "REGAX" ) ) {
	ModuleInfo.xflag |= OPT_REGAX;
    } else if ( 0 == _stricmp( tokenarray[i].string_ptr, "NOREGS" ) ) {
	ModuleInfo.xflag &= ~(OPT_REGAX);
    } else {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    i++;
    *pi = i;
    return( NOT_ERROR );
}

OPTFUNC( SetElf )
/***************/
{
    int i = *pi;
    struct expr opndx;

    if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )
	return( ERROR );
    if ( opndx.kind == EXPR_CONST ) {
	if ( opndx.llvalue > 0xFF ) {
	    return( EmitConstError( &opndx ) );
	}
	if ( Options.output_format == OFORMAT_ELF )
	    ModuleInfo.elf_osabi = opndx.value;
    } else {
	return( asmerr( 2026 ) );
    }
    *pi = i;
    return( NOT_ERROR );
}

/* OPTION RENAMEKEYWORD: <keyword>,new_name */

OPTFUNC( SetRenameKey )
/*********************/
{
    int i = *pi;
    unsigned index;
    char *oldname;

    if ( tokenarray[i].token != T_STRING || tokenarray[i].string_delim != '<' )	 {
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }
    oldname = tokenarray[i].string_ptr;
    i++;
    if ( tokenarray[i].token != T_DIRECTIVE || tokenarray[i].dirtype != DRT_EQUALSGN ) {
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }
    i++;
    if ( tokenarray[i].token != T_ID )	{
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }

    /* todo: if MAX_ID_LEN can be > 255, then check size,
     * since a reserved word's size must be <= 255 */
    index = FindResWord( oldname, (unsigned char)strlen( oldname ) );
    if ( index == 0 ) {
	return( asmerr( 2086 ) );
    }
    RenameKeyword( index, tokenarray[i].string_ptr, (unsigned char)strlen( tokenarray[i].string_ptr ) );
    i++;
    *pi = i;
    return( NOT_ERROR );
}

void InitStackBase( int );

int SetWin64( int *pi, struct asm_tok tokenarray[] )
{
    int i = *pi;
    struct expr opndx;

    /* if -win64 isn't set, skip the option */
    /* v2.09: skip option if Ofssize != USE64 */
    if ( ModuleInfo.defOfssize != USE64 ) {
	SkipOption( pi, tokenarray );
	return( NOT_ERROR);
    }

    if ( tokenarray[i].token == T_NUM ) {
	if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 ) == ERROR )
	    return( ERROR );
	if ( opndx.kind == EXPR_CONST ) {
	    if ( opndx.llvalue & ( ~W64F_ALL ) ) {
		return( EmitConstError( &opndx ) );
	    }
	    ModuleInfo.win64_flags = opndx.value;
	}
    } else {

	while (tokenarray[i].token != T_FINAL) {

	    if (tokenarray[i].token != T_COLON &&
		tokenarray[i].token != T_COMMA) {

		if ( tokenarray[i].tokval == T_RSP ) {
		    InitStackBase( T_RSP );
		    ModuleInfo.win64_flags |= W64F_AUTOSTACKSP;
		} else if ( tokenarray[i].tokval == T_RBP ) {
		    InitStackBase( T_RBP );
		    ModuleInfo.frame_auto = 1;
		    ModuleInfo.win64_flags |= (W64F_AUTOSTACKSP | W64F_SAVEREGPARAMS);
		} else if ( tokenarray[i].tokval == T_ALIGN ) {
		    if ( !ModuleInfo.win64_flags )
			ModuleInfo.win64_flags |= W64F_AUTOSTACKSP;
		    ModuleInfo.win64_flags |= W64F_STACKALIGN16;
		} else if ( !_stricmp( tokenarray[i].string_ptr, "NOALIGN" ) ) {
		    ModuleInfo.win64_flags &= ~W64F_STACKALIGN16;
		} else if ( !_stricmp( tokenarray[i].string_ptr, "SAVE" ) ) {
		    ModuleInfo.win64_flags |= W64F_SAVEREGPARAMS;
		} else if ( !_stricmp( tokenarray[i].string_ptr, "NOSAVE" ) ) {
		    ModuleInfo.win64_flags &= ~W64F_SAVEREGPARAMS;
		} else if ( !_stricmp( tokenarray[i].string_ptr, "AUTO" ) ) {
		    ModuleInfo.win64_flags |= W64F_AUTOSTACKSP;
		} else if ( !_stricmp( tokenarray[i].string_ptr, "NOAUTO" ) ) {
		    ModuleInfo.win64_flags &= ~W64F_AUTOSTACKSP;
		} else if ( tokenarray[i].tokval == T_FRAME ) {
		    ModuleInfo.frame_auto = 1;
		} else if ( !_stricmp( tokenarray[i].string_ptr, "NOFRAME" ) ) {
		    ModuleInfo.frame_auto = 0;
		} else {
		    return( asmerr( 2026 ) );
		}
	    }
	    i++;
	}
    }
    *pi = i;
    return( NOT_ERROR );
}

static struct dll_desc *IncludeDll( const char *name )
/****************************************************/
{
    struct dll_desc **q;
    struct dll_desc *node;

    /* allow a zero-sized name! */
    if ( *name == NULLC )
	return( NULL );

    for ( q = &ModuleInfo.g.DllQueue; *q ; q = &(*q)->next ) {
	if ( _stricmp( (*q)->name, name ) == 0 )
	    return( *q );
    }
    node = (struct dll_desc *)LclAlloc( sizeof( struct dll_desc ) + strlen( name ) );
    node->next = NULL;
    node->cnt = 0;
    strcpy( node->name, name );
    *q = node;

    ModuleInfo.g.imp_prefix = ( ( ModuleInfo.defOfssize == USE64 ) ? "__imp_" : "_imp_" );
    return( node );
}

OPTFUNC( SetDllImport )
/*********************/
{
    int i = *pi;

    if ( tokenarray[i].token == T_ID &&
	( _stricmp( tokenarray[i].string_ptr, "NONE" ) == 0 ) ) {
	ModuleInfo.CurrDll = NULL;
	i++;
    } else if ( tokenarray[i].token == T_STRING && tokenarray[i].string_delim == '<' ) {
	if ( Parse_Pass == PASS_1 )
	    ModuleInfo.CurrDll = IncludeDll( tokenarray[i].string_ptr );
	i++;
    }
    *pi = i;
    return( NOT_ERROR );
}

OPTFUNC( SetCodeView )
/********************/
{
    int i = *pi;
    struct expr opnd;

    if ( EvalOperand( &i, tokenarray, Token_Count, &opnd, 0 ) == ERROR )
	return( ERROR );
    if ( opnd.kind == EXPR_CONST ) {
	ModuleInfo.cv_opt = opnd.value;
    } else {
	return( asmerr( 2026 ) );
    }
    *pi = i;
    return( NOT_ERROR );
}

extern void UpdateStackBase( struct asym *, void * );
extern void UpdateProcStatus( struct asym *, void * );

void InitStackBase(int reg)
{
    ModuleInfo.basereg[ModuleInfo.Ofssize] = reg;
    if ( !ModuleInfo.g.StackBase ) {
	ModuleInfo.g.StackBase = CreateVariable( "@StackBase", 0 );
	ModuleInfo.g.StackBase->predefined = TRUE;
	ModuleInfo.g.StackBase->sfunc_ptr = UpdateStackBase;
	ModuleInfo.g.ProcStatus = CreateVariable( "@ProcStatus", 0 );
	ModuleInfo.g.ProcStatus->predefined = TRUE;
	ModuleInfo.g.ProcStatus->sfunc_ptr = UpdateProcStatus;
    }
}

OPTFUNC( SetStackBase )
/*********************/
{
    int i = *pi;

    if ( tokenarray[i].token != T_REG ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }
    if ( !( GetSflagsSp( tokenarray[i].tokval ) & SFR_IREG ) ) {
	return( asmerr( 2031 ) );
    }
    InitStackBase( tokenarray[i].tokval );
    i++;
    *pi = i;
    return( NOT_ERROR );
}

OPTFUNC( Unsupported )
/********************/
{
    return( asmerr( 3006, tokenarray[(*pi)-2].tokpos ) );
}

struct asm_option {
    const char *name;
    ret_code OPTQUAL (*func)(int *, struct asm_tok[] );
};

/* the table must be here after the option helper functions
 * to avoid having to define prototypes.
 * the options without arguments must come first!
 */
static const struct asm_option optiontab[] = {
    { "DOTNAME",      SetDotName     },
    { "NODOTNAME",    SetNoDotName   },
    { "M510",	      SetM510	     },
    { "NOM510",	      SetNoM510	     },
    { "SCOPED",	      SetScoped	     },
    { "NOSCOPED",     SetNoScoped    },
    { "OLDSTRUCTS",   SetOldStructs  },
    { "NOOLDSTRUCTS", SetNoOldStructs},
    { "EMULATOR",     SetEmulator    },
    { "NOEMULATOR",   SetNoEmulator  },
    { "LJMP",	      SetLJmp	     },
    { "NOLJMP",	      SetNoLJmp	     },
    { "READONLY",     Unsupported    },
    { "NOREADONLY",   SetNoReadonly  },
    { "OLDMACROS",    Unsupported    },
    { "NOOLDMACROS",  SetNoOldmacros },
    { "EXPR16",	      Unsupported    },
    { "EXPR32",	      SetExpr32	     },
    { "NOSIGNEXTEND", SetNoSignExt   },
#define NOARGOPTS 19 /* number of options without arguments */
    { "CASEMAP",      SetCaseMap     }, /* CASEMAP:NONE|..   */
    { "PROC",	      SetProc	     }, /* PROC:PRIVATE|..   */
    { "PROLOGUE",     SetPrologue    }, /* PROLOGUE: <name>  */
    { "EPILOGUE",     SetEpilogue    }, /* EPILOGUE: <name>  */
    { "LANGUAGE",     SetLanguage    }, /* LANGUAGE: <name>  */
    { "NOKEYWORD",    SetNoKeyword   }, /* NOKEYWORD: <id>   */
    { "SETIF2",	      SetSetIF2	     }, /* SETIF2: <value>   */
    { "OFFSET",	      SetOffset	     }, /* OFFSET: GROUP|..  */
    { "SEGMENT",      SetSegment     }, /* SEGMENT: USE16|.. */
#define MASMOPTS 28 /* number of options compatible with Masm */
    { "FIELDALIGN",   SetFieldAlign  }, /* FIELDALIGN: <value> */
    { "PROCALIGN",    SetProcAlign   }, /* PROCALIGN: <value> */
    { "MZ",	      SetMZ	     }, /* MZ: <value>:<value>.. */
    { "FRAME",	      SetFrame	     }, /* FRAME: AUTO|.. */
    { "ELF",	      SetElf	     }, /* ELF: <value> */
    { "RENAMEKEYWORD",SetRenameKey   }, /* RENAMEKEYWORD: <id>=<> */
    { "WIN64",	      SetWin64	     }, /* WIN64: <value> */
    { "DLLIMPORT",    SetDllImport   }, /* DLLIMPORT: <NONE|library> */
    { "CODEVIEW",     SetCodeView    }, /* CODEVIEW: <value> */
    { "STACKBASE",    SetStackBase   }, /* STACKBASE: <reg> */
    { "CSTACK",	      SetCStack	     },
    { "SWITCH",	      SetSwitch	     },
    { "LOOPALIGN",    SetLoopAlign   }, /* LOOPALIGN: <value> */
    { "CASEALIGN",    SetCaseAlign   }, /* CASEALIGN: <value> */
    { "WSTRING",      SetWString     }, /* WSTRING: <ON|OFF> */
    { "CODEPAGE",     SetCodePage    }, /* CODEPAGE: <value> */
};

#define TABITEMS sizeof( optiontab) / sizeof( optiontab[0] )

/* handle OPTION directive
 * syntax:
 * OPTION option[:value][,option[:value,...]]
 */
int OptionDirective( int i, struct asm_tok tokenarray[] )
/************************************************************/
{
    int idx = -1;

    i++; /* skip OPTION directive */
    while ( tokenarray[i].token != T_FINAL ) {
	_strupr( tokenarray[i].string_ptr );
	for ( idx = 0; idx < TABITEMS; idx++ ) {
	    if ( 0 == strcmp( tokenarray[i].string_ptr, optiontab[idx].name ) )
		break;
	}
	if ( idx >= TABITEMS )
	    break;
	i++;
	/* v2.06: check for colon separator here */
	if ( idx >= NOARGOPTS ) {
	    if ( tokenarray[i].token != T_COLON ) {
		return( asmerr( 2065, "" ) );
	    }
	    i++;
	    /* there must be something after the colon */
	    if ( tokenarray[i].token == T_FINAL ) {
		i -= 2; /* position back to option identifier */
		break;
	    }
	    /* reject option if -Zne is set */
	    if ( idx >= MASMOPTS && ModuleInfo.strict_masm_compat ) {
		i -= 2;
		break;
	    }
	}
	if ( optiontab[idx].func( &i, tokenarray ) == ERROR )
	    return( ERROR );
	if ( tokenarray[i].token != T_COMMA )
	    break;
	i++;
    }
    if ( idx >= TABITEMS  || tokenarray[i].token != T_FINAL ) {
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }
    return( NOT_ERROR );
}

