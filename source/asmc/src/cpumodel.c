/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	processes .MODEL and cpu directives
*
****************************************************************************/

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <segment.h>
#include <assume.h>
#include <equate.h>
#include <lqueue.h>
#include <tokenize.h>
#include <expreval.h>
#include <fastpass.h>
#include <listing.h>
#include <proc.h>
#include <macro.h>
#include <fixup.h>
#include <bin.h>

#define DOT_XMMARG 0 /* 1=optional argument for .XMM directive */

struct asym *sym_Interface ; /* numeric. requires model */
struct asym *sym_Cpu	   ; /* numeric. This is ALWAYS set */

const struct format_options coff64_fmtopt = { NULL, COFF64_DISALLOWED, "PE32+" };
const struct format_options elf64_fmtopt  = { NULL, ELF64_DISALLOWED,  "ELF64" };

#ifndef __ASMC64__

extern const char szDgroup[];

/* prototypes */

/* the following flags assume the MODEL_xxx enumeration.
 * must be sorted like MODEL_xxx enum:
 * TINY=1, SMALL=2, COMPACT=3, MEDIUM=4, LARGE=5, HUGE=6, FLAT=7
 */
const char * const ModelToken[] = {
    "TINY", "SMALL", "COMPACT", "MEDIUM", "LARGE", "HUGE", "FLAT" };

#define INIT_LANG	0x1
#define INIT_STACK	0x2
#define INIT_OS		0x4

struct typeinfo {
    uint_8 value;  /* value assigned to the token */
    uint_8 init;   /* kind of token */
};

static const char * const ModelAttr[] = {
    "NEARSTACK", "FARSTACK", "OS_OS2", "OS_DOS" };

static const struct typeinfo ModelAttrValue[] = {
    { STACK_NEAR,     INIT_STACK      },
    { STACK_FAR,      INIT_STACK      },
    { OPSYS_DOS,      INIT_OS	      },
    { OPSYS_OS2,      INIT_OS	      },
};

static struct asym *sym_CodeSize  ; /* numeric. requires model */
static struct asym *sym_DataSize  ; /* numeric. requires model */
static struct asym *sym_Model	  ; /* numeric. requires model */

/* find token in a string table */

static int FindToken( const char *token, const char * const *table, int size )
/****************************************************************************/
{
    int i;
    for( i = 0; i < size; i++, table++ ) {
	if( _stricmp( *table, token ) == 0 ) {
	    return( i );
	}
    }
    return( -1 );  /* Not found */
}

static struct asym *AddPredefinedConstant( const char *name, int value )
/**********************************************************************/
{
    struct asym *sym = CreateVariable( name, value );
    if (sym)
	sym->predefined = TRUE;
    return(sym);
}

/* set default wordsize for segment definitions */

static int SetDefaultOfssize( int size )
/*******************************************/
{
    /* outside any segments? */
    if( CurrSeg == NULL ) {
	ModuleInfo.defOfssize = size;
    }
    return( SetOfssize() );
}

/* set memory model, called by ModelDirective()
 * also set predefined symbols:
 * - @CodeSize	(numeric)
 * - @code	(text)
 * - @DataSize	(numeric)
 * - @data	(text)
 * - @stack	(text)
 * - @Model	(numeric)
 * - @Interface (numeric)
 * inactive:
 * - @fardata	(text)
 * - @fardata?	(text)
 * Win64 only:
 * - @ReservedStack (numeric)
 */
static void SetModel( void )
/**************************/
{
    int		value;
    const char	*textvalue;

    /* if model is set, it disables OT_SEGMENT of -Zm switch */
    if ( ModuleInfo.model == MODEL_FLAT ) {
	ModuleInfo.offsettype = OT_FLAT;
	SetDefaultOfssize( ((ModuleInfo.curr_cpu & P_CPU_MASK) >= P_64 ) ? USE64 : USE32 );
	/* v2.03: if cpu is x64 and language is fastcall,
	 * set fastcall type to win64.
	 * This is rather hackish, but currently there's no other possibility
	 * to enable the win64 ABI from the source.
	 */
	if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) == P_64 ) {
	    if ( ModuleInfo.langtype == LANG_FASTCALL ||
		 ModuleInfo.langtype == LANG_SYSCALL ||
		 ModuleInfo.langtype == LANG_VECTORCALL ) {

		if ( ModuleInfo.langtype == LANG_VECTORCALL )
		    ModuleInfo.fctype = FCT_VEC64;
		else if ( Options.output_format != OFORMAT_ELF )
		    ModuleInfo.fctype = FCT_WIN64;
		else
		    ModuleInfo.fctype = FCT_ELF64;
	    }
	} else if ( ModuleInfo.langtype == LANG_VECTORCALL ) {
	    ModuleInfo.fctype = FCT_VEC32;
	}

	/* v2.11: define symbol FLAT - after default offset size has been set! */
	DefineFlatGroup();
    } else
	ModuleInfo.offsettype = OT_GROUP;

    ModelSimSegmInit( ModuleInfo.model ); /* create segments in first pass */
    ModelAssumeInit();

    if ( ModuleInfo.list )
	LstWriteSrcLine();

    RunLineQueue();

    if ( Parse_Pass != PASS_1 )
	return;

    /* Set @CodeSize */
    if ( SIZE_CODEPTR & ( 1 << ModuleInfo.model ) ) {
	value = 1;
    } else {
	value = 0;
    }
    sym_CodeSize = AddPredefinedConstant( "@CodeSize", value );
    AddPredefinedText( "@code", SimGetSegName( SIM_CODE ) );

    /* Set @DataSize */
    switch( ModuleInfo.model ) {
    case MODEL_COMPACT:
    case MODEL_LARGE:
	value = 1;
	break;
    case MODEL_HUGE:
	value = 2;
	break;
    default:
	value = 0;
	break;
    }
    sym_DataSize = AddPredefinedConstant( "@DataSize", value );

    textvalue = ( ModuleInfo.model == MODEL_FLAT ? "FLAT" : szDgroup );
    AddPredefinedText( "@data", textvalue );

    if ( ModuleInfo.distance == STACK_FAR )
	textvalue = "STACK";
    AddPredefinedText( "@stack", textvalue );

    /* Set @Model and @Interface */

    sym_Model	  = AddPredefinedConstant( "@Model", ModuleInfo.model );
    sym_Interface = AddPredefinedConstant( "@Interface", ModuleInfo.langtype );

    if ( ModuleInfo.defOfssize == USE64 &&
	( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 ) ) {
	sym_ReservedStack = AddPredefinedConstant( "@ReservedStack", 0 );
    }
    if ( ModuleInfo.sub_format == SFORMAT_PE ||
       ( ModuleInfo.sub_format == SFORMAT_64BIT && Options.output_format == OFORMAT_BIN ) )
	pe_create_PE_header();
}

/* handle .model directive
 * syntax: .MODEL <FLAT|TINY|SMALL...> [,<C|PASCAL|STDCALL...>][,<NEARSTACK|FARSTACK>][,<OS_DOS|OS_OS2>]
 * sets fields
 * - ModuleInfo.model
 * - ModuleInfo.language
 * - ModuleInfo.distance
 * - ModuleInfo.ostype
 * if model is FLAT, defines FLAT pseudo-group
 * set default segment names for code and data
 */
int ModelDirective( int i, struct asm_tok tokenarray[] )
/***********************************************************/
{
    unsigned char distance;
    unsigned char model;
    unsigned char language;
    unsigned char ostype;

    int index;
    uint_8 init;
    uint_8 initv;

    /* v2.03: it may occur that "code" is defined BEFORE the MODEL
     * directive (i.e. DB directives in AT-segments). For FASTPASS,
     * this may have caused errors because contents of the ModuleInfo
     * structure was saved before the .MODEL directive.
     */
    if( Parse_Pass != PASS_1 && ModuleInfo.model != MODEL_NONE ) {
	/* just set the model with SetModel() if pass is != 1.
	 * This won't set the language ( which can be modified by
	 * OPTION LANGUAGE directive ), but the language in ModuleInfo
	 * isn't needed anymore once pass one is done.
	 */
	SetModel();
	return( NOT_ERROR );
    }

    i++;
    if ( tokenarray[i].token == T_FINAL ) {
	return( asmerr( 2013 ) );
    }
    /* get the model argument */
    index = FindToken( tokenarray[i].string_ptr, ModelToken, sizeof( ModelToken )/sizeof( ModelToken[0] ) );
    if( index >= 0 ) {
	if( ModuleInfo.model != MODEL_NONE ) {
	    asmerr( 4011 );
	}
	model = index + 1; /* model is one-base ( 0 is MODEL_NONE ) */
	i++;
    } else {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }

    /* get the optional arguments: language, stack distance, os */
    init = 0;
    while ( i < ( Token_Count - 1 ) && tokenarray[i].token == T_COMMA ) {
	i++;
	if ( tokenarray[i].token != T_COMMA ) {
	    if ( GetLangType( &i, tokenarray, &language ) == NOT_ERROR ) {
		initv = INIT_LANG;
	    } else {
		index = FindToken( tokenarray[i].string_ptr, ModelAttr, sizeof( ModelAttr )/sizeof( ModelAttr[0] ) );
		if ( index < 0 )
		    break;
		initv = ModelAttrValue[index].init;
		switch ( initv ) {
		case INIT_STACK:
		    if ( model == MODEL_FLAT ) {
			return( asmerr( 2178 ) );
		    }
		    distance = ModelAttrValue[index].value;
		    break;
		case INIT_OS:
		    ostype = ModelAttrValue[index].value;
		    break;
		}
		i++;
	    }
	    /* attribute set already? */
	    if ( initv & init ) {
		i--;
		break;
	    }
	    init |= initv;
	}
    }
    /* everything parsed successfully? */
    if ( tokenarray[i].token != T_FINAL ) {
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }

    if ( model == MODEL_FLAT ) {
	if ( ( ModuleInfo.curr_cpu & P_CPU_MASK) < P_386 ) {
	    return( asmerr( 2085 ) );
	}
	if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) >= P_64 ) /* cpu 64-bit? */
	    switch ( Options.output_format ) {
	    case OFORMAT_COFF: ModuleInfo.fmtopt = &coff64_fmtopt; break;
	    case OFORMAT_ELF:  ModuleInfo.fmtopt = &elf64_fmtopt;  break;
	    };
    }

    ModuleInfo.model = model;
    if ( init & INIT_LANG )
	ModuleInfo.langtype = language;
    if ( init & INIT_STACK )
	ModuleInfo.distance = distance;
    if ( init & INIT_OS )
	ModuleInfo.ostype = ostype;

    SetModelDefaultSegNames();
    SetModel();

    return( NOT_ERROR );
}

/* set CPU and FPU parameter in ModuleInfo.cpu + ModuleInfo.curr_cpu.
 * ModuleInfo.cpu is the value of Masm's @CPU symbol.
 * ModuleInfo.curr_cpu is the old OW Wasm value.
 * additional notes:
 * .[1|2|3|4|5|6]86 will reset .MMX, .K3D and .XMM,
 * OTOH, .MMX/.XMM won't automatically enable .586/.686 ( Masm does! )
*/

int SetCPU( enum cpu_info newcpu )
/*************************************/
{
    int temp;

    if ( newcpu == P_86 || ( newcpu & P_CPU_MASK ) ) {
	/* reset CPU and EXT bits */
	ModuleInfo.curr_cpu &= ~( P_CPU_MASK | P_EXT_MASK | P_PM );

	/* set CPU bits */
	ModuleInfo.curr_cpu |= newcpu & ( P_CPU_MASK | P_PM );

	/* set default FPU bits if nothing is given and .NO87 not active */
	if ( (ModuleInfo.curr_cpu & P_FPU_MASK) != P_NO87 &&
	    ( newcpu & P_FPU_MASK ) == 0 ) {
	    ModuleInfo.curr_cpu &= ~P_FPU_MASK;
	    if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) < P_286 )
		ModuleInfo.curr_cpu |= P_87;
	    else if ( ( ModuleInfo.curr_cpu & P_CPU_MASK ) < P_386 )
		ModuleInfo.curr_cpu |= P_287;
	    else
		ModuleInfo.curr_cpu |= P_387;
	}

    }
    if( newcpu & P_FPU_MASK ) {
	ModuleInfo.curr_cpu &= ~P_FPU_MASK;
	ModuleInfo.curr_cpu |= (newcpu & P_FPU_MASK);
    }
    /* enable MMX, K3D, SSEx for 64bit cpus */
    if ( ( newcpu & P_CPU_MASK ) == P_64 )
	ModuleInfo.curr_cpu |= P_EXT_ALL;
    if( newcpu & P_EXT_MASK ) {
	ModuleInfo.curr_cpu &= ~P_EXT_MASK;
	ModuleInfo.curr_cpu |= (newcpu & P_EXT_MASK);
    }

    /* set the Masm compatible @Cpu value */

    temp = ModuleInfo.curr_cpu & P_CPU_MASK;
    switch ( temp ) {
    case P_186: ModuleInfo.cpu = M_8086 | M_186; break;
    case P_286: ModuleInfo.cpu = M_8086 | M_186 | M_286; break;
    case P_386: ModuleInfo.cpu = M_8086 | M_186 | M_286 | M_386; break;
    case P_486: ModuleInfo.cpu = M_8086 | M_186 | M_286 | M_386 | M_486; break;
    case P_586: ModuleInfo.cpu = M_8086 | M_186 | M_286 | M_386 | M_486 | M_586; break;
    case P_64:
    case P_686: ModuleInfo.cpu = M_8086 | M_186 | M_286 | M_386 | M_486 | M_686; break;
    default: ModuleInfo.cpu = M_8086; break;
    }
    if ( ModuleInfo.curr_cpu & P_PM )
	ModuleInfo.cpu = ModuleInfo.cpu | M_PROT;

    temp = ModuleInfo.curr_cpu & P_FPU_MASK;
    switch (temp) {
    case P_87:	ModuleInfo.cpu = ModuleInfo.cpu | M_8087;     break;
    case P_287: ModuleInfo.cpu = ModuleInfo.cpu | M_8087 | M_287; break;
    case P_387: ModuleInfo.cpu = ModuleInfo.cpu | M_8087 | M_287 | M_387; break;
    }

    if ( ModuleInfo.model == MODEL_NONE )
	if ( ( ModuleInfo.curr_cpu & P_CPU_MASK) >= P_64 ) {
	    SetDefaultOfssize( USE64 );
	} else
	    SetDefaultOfssize( ((ModuleInfo.curr_cpu & P_CPU_MASK) >= P_386) ? USE32 : USE16 );

    /* Set @Cpu */
    /* differs from Codeinfo cpu setting */

    sym_Cpu = CreateVariable( "@Cpu", ModuleInfo.cpu );

    return( NOT_ERROR );
}

/* handles
 .8086,
 .[1|2|3|4|5|6]86[p],
 .8087,
 .[2|3]87,
 .NO87, .MMX, .K3D, .XMM directives.
*/

int CpuDirective( int i, struct asm_tok tokenarray[] )
/*********************************************************/
{
    enum cpu_info newcpu;
    int x;

    newcpu = GetSflagsSp( tokenarray[i].tokval );

#if DOT_XMMARG
    .if ( tokenarray[i].tokval == T_DOT_XMM && tokenarray[i+1].token != T_FINAL ) {
	struct expr opndx;
	i++;
	if ( EvalOperand( &i, Token_Count, &opndx, 0 ) == ERROR )
	    return( ERROR );
	if ( opndx.kind != EXPR_CONST || opndx.value < 1 || opndx.value > 4 ) {
	    return( EmitConstError( &opndx ) );
	}
	newcpy &= ~P_SSEALL;
	switch ( opndx.value ) {
	case 4: newcpy |= P_SSE4;
	case 3: newcpy |= P_SSE3|P_SSSE3;
	case 2: newcpy |= P_SSE2;
	case 1: newcpy |= P_SSE1; break;
	}
    } else
#endif
    i++;

    if ( tokenarray[i].token != T_FINAL ) {
	return( asmerr(2008, tokenarray[i].tokpos ) );
    }

    return( SetCPU( newcpu ) );
}

#else

static struct asym *AddPredefinedConstant( const char *name, int value )
{
    struct asym *sym = CreateVariable( name, value );
    if (sym)
	sym->predefined = TRUE;
    return(sym);
}

int SetCPU( enum cpu_info newcpu )
{
    int temp;


    if ( newcpu == P_86 || ( newcpu & P_CPU_MASK ) ) {
	/* reset CPU and EXT bits */
	ModuleInfo.curr_cpu &= ~( P_CPU_MASK | P_EXT_MASK | P_PM );

	/* set CPU bits */
	ModuleInfo.curr_cpu |= newcpu & ( P_CPU_MASK | P_PM );

	/* set default FPU bits if nothing is given and .NO87 not active */
	if ( ( newcpu & P_FPU_MASK ) == 0 ) {
	    ModuleInfo.curr_cpu &= ~P_FPU_MASK;
	    ModuleInfo.curr_cpu |= P_387;
	}

    }
    if( newcpu & P_FPU_MASK ) {
	ModuleInfo.curr_cpu &= ~P_FPU_MASK;
	ModuleInfo.curr_cpu |= (newcpu & P_FPU_MASK);
    }
    /* enable MMX, K3D, SSEx for 64bit cpus */
    ModuleInfo.curr_cpu |= P_EXT_ALL;
    if( newcpu & P_EXT_MASK ) {
	ModuleInfo.curr_cpu &= ~P_EXT_MASK;
	ModuleInfo.curr_cpu |= (newcpu & P_EXT_MASK);
    }

    /* set the Masm compatible @Cpu value */

    temp = ModuleInfo.curr_cpu & P_CPU_MASK;
    ModuleInfo.cpu = M_8086 | M_186 | M_286 | M_386 | M_486 | M_686;

    if ( ModuleInfo.curr_cpu & P_PM )
	ModuleInfo.cpu = ModuleInfo.cpu | M_PROT;

    ModuleInfo.cpu = ModuleInfo.cpu | M_8087 | M_287 | M_387;
    ModuleInfo.model = MODEL_FLAT;

    /* Set @Cpu */
    /* differs from Codeinfo cpu setting */
    sym_Cpu = (struct asym *)CreateVariable( "@Cpu", ModuleInfo.cpu );

    if ( Options.output_format == OFORMAT_ELF )
	ModuleInfo.fmtopt = &elf64_fmtopt;
    else
	ModuleInfo.fmtopt = &coff64_fmtopt;

    SetModelDefaultSegNames();

    ModuleInfo.offsettype = OT_FLAT;

    if( CurrSeg == NULL )
	ModuleInfo.defOfssize = USE64;
    SetOfssize();

    if ( ModuleInfo.langtype == LANG_VECTORCALL )
	ModuleInfo.fctype = FCT_VEC64;
    else if ( Options.output_format != OFORMAT_ELF )
	ModuleInfo.fctype = FCT_WIN64;
    else
	ModuleInfo.fctype = FCT_ELF64;

    DefineFlatGroup();

    ModelSimSegmInit( ModuleInfo.model ); /* create segments in first pass */
    ModelAssumeInit();

    if ( ModuleInfo.list )
	LstWriteSrcLine();
    //debug_break();

    if ( Parse_Pass != PASS_1 )
	return( NOT_ERROR );

    AddPredefinedConstant( "@CodeSize", 0 );
    AddPredefinedText( "@code", SimGetSegName( SIM_CODE ) );
    AddPredefinedConstant( "@DataSize", 0 );

    AddPredefinedText( "@data",	 "FLAT" );
    AddPredefinedText( "@stack", "FLAT" );

    /* Set @Model and @Interface */

    AddPredefinedConstant( "@Model", ModuleInfo.model );
    sym_Interface = AddPredefinedConstant( "@Interface", ModuleInfo.langtype );

    if ( ( ModuleInfo.fctype == FCT_WIN64 || ModuleInfo.fctype == FCT_VEC64 ) )
	sym_ReservedStack = AddPredefinedConstant( "@ReservedStack", 0 );

    if ( ModuleInfo.sub_format == SFORMAT_PE ||
       ( ModuleInfo.sub_format == SFORMAT_64BIT && Options.output_format == OFORMAT_BIN ) )
	pe_create_PE_header();

    return( NOT_ERROR );
}

#endif
