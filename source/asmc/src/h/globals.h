#ifndef _GLOBALS_H_INCLUDED
#define _GLOBALS_H_INCLUDED

#define ASMC_VERSSTR "2.31"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> /* needed for errno declaration ( "sometimes" it's defined in stdlib.h ) */

#if defined(__UNIX__) || defined(__CYGWIN__) || defined(__DJGPP__) /* avoid for MinGW! */
#define _stricmp strcasecmp
#ifndef __WATCOMC__
#define _memicmp strncasecmp
#endif
#define _ltoa	ltoa
#define _strupr strupr

#if defined(__UNIX__) /* v2.12: added */
char *strupr( char * ); /* defined in apiemu.c */
#endif

#elif defined(__POCC__)

#pragma warn(disable:2030) /* disable '=' used in a conditional expression */
#pragma warn(disable:2229) /* disable 'local x is potentially used without ...' */
#pragma warn(disable:2231) /* disable 'enum value x not handled in switch statement' */

#elif defined(__BORLANDC__) || defined(__OCC__)

#define _stricmp  stricmp
#define _strnicmp strnicmp
#define _strupr	  strupr
#define _memicmp  memicmp

#endif

#ifndef WINAPI
#ifdef _M_X64
#define WINAPI
#else
#define WINAPI __stdcall
#endif
#endif

#ifdef _ASMC
#define FASTCALL __fastcall
#else
#define FASTCALL
#endif

#define OLDKEYWORDS 1
#define CHEXPREFIX 1

#define MAX_LINE_LEN		2048 /* no restriction for this number */
#define MAX_TOKEN		MAX_LINE_LEN / 4  /* max tokens in one line */
#define MAX_STRING_LEN		MAX_LINE_LEN - 32 /* must be < MAX_LINE_LEN */
#define MAX_ID_LEN		247	/* must be < MAX_LINE_LEN */
#define MAX_STRUCT_ALIGN	32
#define MAX_SEGMENT_ALIGN	4096
#define MAX_IF_NESTING		20	/* IFxx block nesting. Must be <=32, see condasm.c */
#define MAX_SEG_NESTING		20	/* limit for segment nesting	 */
#define MAX_MACRO_NESTING	100	/* macro call nesting	 */
#define MAX_STRUCT_NESTING	32	/* limit for "anonymous structs" only */
#define MAX_LNAME		255	/* OMF lnames - length must fit in 1 byte */
#define LNAME_NULL		0	/* OMF first entry in lnames array */

#include "inttype.h"

typedef int	bool;
#define FALSE	0
#define TRUE	1

#include <errmsg.h>  /* must be located AFTER #defines lines */
#include <queue.h>

#define NULLC  '\0'

#define _LUPPER		0x01	/* upper case letter */
#define _LLOWER		0x02	/* lower case letter */
#define _LDIGIT		0x04	/* digit[0-9] */
#define _LSPACE		0x08	/* tab, carriage return, newline, */
				/* vertical tab or form feed */
#define _LPUNCT		0x10	/* punctuation character */
#define _LCONTROL	0x20	/* control character */
#define _LABEL		0x40	/* UPPER + LOWER + '@' + '_' + '$' + '?' */
#define _LHEX		0x80	/* hexadecimal digit */

extern unsigned char _ltype[];	/* Label type array */

#define islalnum(c)  (_ltype[(unsigned char)(c) + 1] & (_LDIGIT | _LUPPER | _LLOWER))
#define islalpha(c)  (_ltype[(unsigned char)(c) + 1] & (_LUPPER | _LLOWER))
#define islascii(c)  ((unsigned char)(c) < 128)
#define islcntrl(c)  (_ltype[(unsigned char)(c) + 1] & _LCONTROL)
#define isldigit(c)  (_ltype[(unsigned char)(c) + 1] & _LDIGIT)
#define islgraph(c)  ((unsigned char)(c) >= 0x21 && (unsigned char)(c) <= 0x7e)
#define isllower(c)  (_ltype[(unsigned char)(c) + 1] & _LLOWER)
#define islprint(c)  ((unsigned char)(c) >= 0x20 && (unsigned char)(c) <= 0x7e)
#define islpunct(c)  (_ltype[(unsigned char)(c) + 1] & _LPUNCT)
#define islspace(c)  (_ltype[(unsigned char)(c) + 1] & _LSPACE)
#define islupper(c)  (_ltype[(unsigned char)(c) + 1] & _LUPPER)
#define islxdigit(c) (_ltype[(unsigned char)(c) + 1] & _LHEX)

#define is_valid_id_char( c ) (_ltype[(unsigned char)(c)+1] & (_LABEL | _LDIGIT))
#define is_valid_id_first_char( c ) \
	((_ltype[(unsigned char)(c) + 1] & _LABEL) || ((c) == '.' && ModuleInfo.dotname))
#define is_valid_id_start( c ) (_ltype[(unsigned char)(c) + 1] & _LABEL)
#define is_valid_first_char( c ) ((_ltype[(unsigned char)(c) + 1] & _LABEL) || ((c) == '.' ))

/* function return values */


#define EMPTY		(-2)
#define ERROR		(-1)
#define NOT_ERROR	0
#define STRING_EXPANDED 1

typedef int	ret_code;

#define PASS_1	0
#define PASS_2	1


/* enumerations */

/* output formats. Order must match formatoptions[] in assemble.c */
enum oformat {
    OFORMAT_BIN, /* used by -bin, -mz and -pe */
    OFORMAT_OMF,
    OFORMAT_COFF,/* used by -coff, -djgpp and -win64 */
    OFORMAT_ELF, /* used by -elf and elf64 */
};

enum sformat {
    SFORMAT_NONE,
    SFORMAT_MZ,	   /* MZ binary */
    SFORMAT_PE,	   /* PE (32- or 64-bit) binary */
    SFORMAT_64BIT, /* 64bit COFF or ELF */
};

enum fpo {
    FPO_NO_EMULATION,  /* -FPi87 (default) */
    FPO_EMULATION      /* -FPi */
};

/* language values.
 * the order cannot be changed, it's
 * returned by OPATTR and used in user-defined prologue/epilogue.
 */
enum lang_type {
    LANG_NONE	  = 0,
    LANG_C	  = 1,
    LANG_SYSCALL  = 2,
    LANG_STDCALL  = 3,
    LANG_PASCAL	  = 4,
    LANG_FORTRAN  = 5,
    LANG_BASIC	  = 6,
    LANG_FASTCALL = 7,
    LANG_VECTORCALL = 8
};

/* Memory model type.
 * the order cannot be changed, it's
 * the value of the predefined @Model symbol.
 */
enum model_type {
    MODEL_NONE	  = 0,
    MODEL_TINY	  = 1,
    MODEL_SMALL	  = 2,
    MODEL_COMPACT = 3,
    MODEL_MEDIUM  = 4,
    MODEL_LARGE	  = 5,
    MODEL_HUGE	  = 6,
    MODEL_FLAT	  = 7,
};

#define SIZE_DATAPTR 0x68 /* far for COMPACT, LARGE, HUGE */
#define SIZE_CODEPTR 0x70 /* far for MEDIUM, LARGE, HUGE  */

enum seg_order {
    SEGORDER_SEQ = 0,  /* .SEQ (default) */
    SEGORDER_DOSSEG,   /* .DOSSEG */
    SEGORDER_ALPHA     /* .ALPHA */
};

/* .NOLISTMACRO, .LISTMACRO and .LISTMACROALL directives setting */
enum listmacro {
    LM_NOLISTMACRO,
    LM_LISTMACRO,
    LM_LISTMACROALL
};

/* assume values are used as index in codegen.c / invoke.c.
 * Order must match the one in special.h. Don't change!
 */
enum assume_segreg {
    ASSUME_NOTHING = EMPTY,
    ASSUME_ES = 0,
    ASSUME_CS,
    ASSUME_SS,
    ASSUME_DS,
    ASSUME_FS,
    ASSUME_GS
};

enum cpu_info {
    /* bit count from left:
     * bit 0-2:	  Math coprocessor
     * bit 3:	  privileged?
     * bit 4-7:	  cpu type
     * bit 8-15;  extension set
     */
    P_NO87  = 0x0001,	      /* no FPU */
    P_87    = 0x0002,	      /* 8087 */
    P_287   = 0x0003,	      /* 80287 */
    P_387   = 0x0004,	      /* 80387 */

    P_PM    = 0x0008,	      /* privileged opcode */

    P_86    = 0x0000,	      /* 8086, default */
    P_186   = 0x0010,	      /* 80186 */
    P_286   = 0x0020,	      /* 80286 */
    P_386   = 0x0030,	      /* 80386 */
    P_486   = 0x0040,	      /* 80486 */
    P_586   = 0x0050,	      /* pentium */
    P_686   = 0x0060,	      /* ppro */
    P_64    = 0x0070,	      /* x64 cpu */

    P_286p  = P_286 | P_PM,   /* 286, priv mode */
    P_386p  = P_386 | P_PM,   /* 386, priv mode */
    P_486p  = P_486 | P_PM,   /* 486, priv mode */
    P_586p  = P_586 | P_PM,   /* 586, priv mode */
    P_686p  = P_686 | P_PM,   /* 686, priv mode */
    P_64p   = P_64 | P_PM,    /* x64, priv mode */

    P_MMX   = 0x0100,	      /* MMX extension instructions */
    P_K3D   = 0x0200,	      /* 3DNow extension instructions */
    P_SSE1  = 0x0400,	      /* SSE1 extension instructions */
    P_SSE2  = 0x0800,	      /* SSE2 extension instructions */
    P_SSE3  = 0x1000,	      /* SSE3 extension instructions */
    P_SSSE3 = 0x2000,	      /* SSSE3 extension instructions */
    P_SSE4  = 0x4000,	      /* SSE4 extension instructions */
    P_AVX   = 0x8000,	      /* AVX extension instructions */
    /* all SSE extension instructions */
    P_SSEALL = P_SSE1 | P_SSE2 | P_SSE3 | P_SSSE3 | P_SSE4 | P_AVX,
    NO_OPPRFX = P_MMX | P_SSEALL,

    P_FPU_MASK = 0x0007,
    P_CPU_MASK = 0x00F0,

    P_EXT_MASK = P_MMX | P_K3D | P_SSEALL,
    P_EXT_ALL  = P_MMX | P_K3D | P_SSEALL
};

/* the MASM compatible @CPU value flags: */
enum masm_cpu {
    M_8086 = 0x0001, /* 8086 */
    M_186  = 0x0002, /* 186 */
    M_286  = 0x0004, /* 286 */
    M_386  = 0x0008, /* 386 */
    M_486  = 0x0010, /* 486 */
    M_586  = 0x0020, /* Pentium */
    M_686  = 0x0040, /* PPro */
    M_CPUMSK = 0x007F,
    M_PROT = 0x0080, /* protected instructions ok */
    M_8087 = 0x0100, /* 8087 */
    M_287  = 0x0400, /* 287 */
    M_387  = 0x0800  /* 387 */
};

enum segofssize {
    USE_EMPTY = 0xFE,
    USE16 = 0, /* don't change values of USE16,USE32,USE64! */
    USE32 = 1,
    USE64 = 2
};

/* fastcall types. if order is to be changed or entries
 * added, also adjust tables in proc.c, mangle.c and probably invoke.c!
 */

#define FCT_MSC		0 /* MS 16-/32-bit fastcall (ax,dx,cx / ecx,edx) */
#define FCT_WATCOMC	1 /* OW register calling convention (eax, ebx, ecx, edx) */
#define FCT_WIN64	2 /* Win64 fastcall convention (rcx, rdx, r8, r9) */
#define FCT_ELF64	3 /* Linux 64 calling convention (rdi, esi, rdx, rcx, r8, r9) */
#define FCT_VEC32	4 /* Win32 vectorcall convention */
#define FCT_VEC64	5 /* Win64 vectorcall convention */

enum stdcall_decoration {
    STDCALL_FULL,
    STDCALL_NONE,
    STDCALL_HALF
};

struct qitem {
    void *next;
    char value[1];
};

/* file extensions. Order must match first entries in enum opt_names! */
enum file_extensions {
    ASM, /* must be first; see SetFilenames() in assembly.c */
    OBJ,
    LST,
    ERR,
    NUM_FILE_TYPES
};

/* first 4 entries must match enum file_extensions! */
enum opt_names {
    OPTN_ASM_FN,
    OPTN_OBJ_FN,	      /* -Fo option */
    OPTN_LST_FN,	      /* -Fl option */
    OPTN_ERR_FN,	      /* -Fr option */
    OPTN_LNKDEF_FN,	      /* -Fd option */
    OPTN_MODULE_NAME,	      /* -nm option */
    OPTN_TEXT_SEG,	      /* -nt option */
    OPTN_DATA_SEG,	      /* -nd option */
    OPTN_CODE_CLASS,	      /* -nc option */
    OPTN_LAST
};

/* queues to store multiple cmdline switch values */
enum opt_queues {
    OPTQ_FINCLUDE, /* -Fi option values */
    OPTQ_MACRO,	   /* -D option values */
    OPTQ_INCPATH,  /* -I option values */
    OPTQ_LAST
};

enum prologue_epilogue_mode {
    PEM_DEFAULT, /* must be value 0 */
    PEM_MACRO,
    PEM_NONE
};

/* Stack distance */
enum dist_type {
    STACK_NEAR,
    STACK_FAR,
};

/* Type of operating system */
enum os_type {
    OPSYS_DOS,
    OPSYS_OS2,
};

enum offset_type {
    OT_GROUP = 0,  /* OFFSET:GROUP (default, must be 0) */
    OT_FLAT,	   /* OFFSET:FLAT    */
    OT_SEGMENT	   /* OFFSET:SEGMENT */
};

enum line_output_flags {
    LOF_LISTED = 1, /* line written to .LST file */
    LOF_SKIPPOS = 2, /* suppress setting list_pos */
};

/* flags for win64_flags */
enum win64_flag_values {
    W64F_SAVEREGPARAMS = 0x01, /* 1=save register params in shadow space on proc entry */
    W64F_AUTOSTACKSP   = 0x02, /* 1=calculate required stack space for arguments of INVOKE */
    W64F_STACKALIGN16  = 0x04, /* 1=stack variables are 16-byte aligned; added in v2.12 */
    W64F_ALL = W64F_SAVEREGPARAMS | W64F_AUTOSTACKSP | W64F_STACKALIGN16, /* all valid flags */
};

/* codeview debug info extend */
enum cvex_values {
    CVEX_MIN	 = 0, /* globals */
    CVEX_REDUCED = 1, /* globals and locals */
    CVEX_NORMAL	 = 2, /* globals, locals and types */
    CVEX_MAX	 = 3, /* globals, locals, types and constants */
};

/* codeview debug info option flags */
enum cvoption_flags {
    CVO_STATICTLS = 1, /* handle static tls */
};

enum seg_type {
    SEGTYPE_UNDEF,
    SEGTYPE_CODE,
    SEGTYPE_DATA,
    SEGTYPE_BSS,
    SEGTYPE_STACK,
    SEGTYPE_ABS,
    SEGTYPE_HDR,   /* only used in bin.c for better sorting */
    SEGTYPE_CDATA, /* only used in bin.c for better sorting */
    SEGTYPE_RELOC, /* only used in bin.c for better sorting */
    SEGTYPE_RSRC,  /* only used in bin.c for better sorting */
    SEGTYPE_ERROR, /* must be last - an "impossible" segment type */
};

#define OPT_CSTACK	0x01
#define OPT_WSTRING	0x02 /* convert "string" to unicode */
#define OPT_LSTRING	0x04 /* L"Unicode" used --> allow dw "string" */
#define OPT_PASCAL	0x08 /* auto insert break after .case */
#define OPT_NOTABLE	0x10 /* no indexed jump table */
#define OPT_REGAX	0x20 /* use [E]AX or R10+R11 to render jump-code */
#define OPT_ASSERT	0x40 /* Generate .assert code */
#define OPT_PUSHF	0x80 /* Push/Pop flags */

struct global_options {
unsigned char	quiet;			/* -q option */
unsigned char	line_numbers;		/* -Zd option */
unsigned char	debug_symbols;		/* -Zi option */
unsigned char	debug_ext;		/* -Zi option numeric argument */
unsigned	floating_point;		/* -FPi, -FPi87 */
unsigned	error_limit;		/* -e option  */
unsigned char	no_error_disp;		/* -eq option */
unsigned char	warning_level;		/* -Wn option */
unsigned char	warning_error;		/* -WX option */
unsigned char	process_subdir;		/* -r option */
char *		names[OPTN_LAST];
struct qitem *	queues[OPTQ_LAST];
unsigned char	no_comment_in_code_rec; /* -zlc option */
unsigned char	no_opt_farcall;		/* -zld option */
unsigned char	no_file_entry;		/* -zlf option */
unsigned char	no_static_procs;	/* -zlp option */
unsigned char	no_section_aux_entry;	/* -zls option	 */
unsigned char	no_cdecl_decoration;	/* -zcw & -zcm option */
unsigned char	stdcall_decoration;	/* -zt<0|1|2> option */
unsigned char	no_export_decoration;	/* -zze option */
unsigned char	entry_decorated;	/* -zzs option	 */
unsigned char	write_listing;		/* -Fl option	*/
unsigned char	write_impdef;		/* -Fd option	*/
unsigned char	case_sensitive;		/* -C<p|x|u> options */
unsigned char	convert_uppercase;	/* -C<p|x|u> options */
unsigned char	preprocessor_stdout;	/* -EP option	*/
unsigned char	masm51_compat;		/* -Zm option	*/
unsigned char	strict_masm_compat;	/* -Zne option	 */
unsigned char	masm_compat_gencode;	/* -Zg option	*/
unsigned char	masm8_proc_visibility;	/* -Zv8 option	 */
unsigned char	listif;			/* -Sx, -Sa option  */
unsigned char	list_generated_code;	/* -Sg, -Sa option  */
unsigned	list_macro;		/* -Sa option	*/
unsigned char	no_symbol_listing;	/* -Sn option	*/
unsigned char	first_pass_listing;	/* -Sf option	*/
unsigned char	all_symbols_public;	/* -Zf option	*/
unsigned char	safeseh;		/* -safeseh option */
unsigned	output_format;		/* -bin, -omf, -coff, -elf options */
unsigned	sub_format;		/* -mz, -pe, -win64, -elf64 options */
unsigned	langtype;		/* -Gc|d|z option */
unsigned	model;			/* -mt|s|m|c|l|h|f option */
unsigned	cpu;			/* -0|1|2|3|4|5|6 & -fp{0|2|3|5|6|c} option */
unsigned	fctype;			/* -zf0 & -zf1 option */
unsigned	codepage;		/* -ws[n] Unicode code page */
unsigned char	ignore_include;		/* -X option */
unsigned char	fieldalign;		/* -Zp option	*/
unsigned char	syntax_check_only;	/* -Zs option */
unsigned char	xflag;			/* extended options */
unsigned char	loopalign;		/* OPTION:LOOPALIGN setting */
unsigned char	casealign;		/* OPTION:CASEALIGN setting */
unsigned char	epilogueflags;		/* OPTION EPILOGUE: FLAGS */
unsigned char	segmentalign;		/* -Sp[n] Set segment alignment */
unsigned char	pe_subsystem;		/* -cui, -gui */
unsigned char	win64_flags;		/* -homeparams, -autostack, -alignstack16 */
unsigned char	chkstack;		/* _chkstk() */
unsigned char	nolib;			/* skip includelib directives */
unsigned char	masm_keywords;		/* -Znk */
};

/* if the structure changes, option.c, SetMZ() might need adjustment! */
struct MZDATA {
    unsigned short ofs_fixups; /* offset start fixups */
    unsigned short alignment; /* header alignment: 16,32,64,128,256,512 */
    unsigned short heapmin;
    unsigned short heapmax;
};

struct dll_desc {
    struct dll_desc *next;
    int cnt;	 /* a function of this dll was used by INVOKE */
    char name[1];
};

/* Information about the module */

struct src_item;
struct hll_item;
struct str_item;
struct com_item;
struct context;

struct module_info;

struct module_vars {
unsigned	error_count;	 /* total of errors so far */
unsigned	warning_count;	 /* total of warnings so far */
unsigned	num_segs;	 /* number of segments in module */
struct qdesc	PubQueue;	 /* PUBLIC items */
struct qdesc	LnameQueue;	 /* LNAME items (segments, groups and classes) */
struct qdesc	SafeSEHQueue;	 /* list of safeseh handlers */
struct qdesc	LibQueue;	 /* includelibs */
struct dll_desc *DllQueue;	 /* dlls of OPTION DLLIMPORT */
char *		imp_prefix;
FILE *		curr_file[NUM_FILE_TYPES];  /* ASM, ERR, OBJ and LST */
char *		curr_fname[NUM_FILE_TYPES];
char *		*FNames;	 /* array of input files */
unsigned	cnt_fnames;	 /* items in FNames array */
char *		IncludePath;
struct qdesc	line_queue;	 /* line queue */
struct src_item *src_stack;	 /* source item (files & macros) stack */
union {
struct fixup *	start_fixup;	 /* OMF only */
struct asym *	start_label;	 /* non-OMF only: start label */
};
unsigned	start_displ;	 /* OMF only, optional displ for start label */
struct str_item *StrStack;	 /* v2.20 string stack */
struct hll_item *HllStack;	 /* for .WHILE, .IF, .REPEAT */
struct hll_item *HllFree;	 /* v2.06: stack of free <struct hll>-items */
struct com_item *ComStack;	 /* for .CLASS, .COMDEF */
struct hll_item *RetStack;	 /* v2.30: .return info */
struct context *ContextStack;
struct context *ContextFree;	 /* v2.10: "free items" heap implemented. */
struct context *SavedContexts;
int		cntSavedContexts;
    /* v2.10: moved here from module_info due to problems if @@: occured on the very first line */
unsigned	anonymous_label; /* "anonymous label" counter */
struct asym	*StackBase;
struct asym	*ProcStatus;
int		(*WriteModule)( struct module_info * );
int		(*EndDirHook)( struct module_info * );
int		(*Pass1Checks)( struct module_info * );
unsigned	pe_flags;	 /* for PE */
};

struct format_options;

struct module_info {
    struct module_vars	g;
    char		*proc_prologue;		/* prologue macro if PEM_MACRO */
    char		*proc_epilogue;		/* epilogue macro if PEM_MACRO */
    struct dll_desc	*CurrDll;		/* OPTION DLLIMPORT dll */
    const struct format_options *fmtopt;	/* v2.07: added */
    unsigned		hll_label;		/* hll directive label counter */
    unsigned char	distance;		/* stack distance */
    unsigned char	model;			/* memory model */
    unsigned char	langtype;		/* language */
    unsigned char	ostype;			/* operating system */
    unsigned char	sub_format;		/* sub-output format */
    unsigned char	fctype;			/* fastcall type */
    unsigned char	segorder;		/* .alpha, .seq, .dosseg */
    unsigned char	offsettype;		/* OFFSET:GROUP|FLAT|SEGMENT */
    unsigned		cpu;			/* cpu setting (value @cpu symbol); */
    unsigned		curr_cpu;		/* cpu setting (OW stylex); */
    unsigned char	radix;			/* current .RADIX setting */
    unsigned char	fieldalign;		/* -Zp, OPTION:FIELDALIGN setting */
    unsigned char	line_flags;		/* current line has been printed */
    unsigned char	procalign;		/* current OPTION:PROCALIGN setting */
    unsigned		list_macro;		/* current .LISTMACRO setting */
    unsigned char	Ofssize;		/* current offset size (USE16,USE32,USE64) */
    unsigned char	defOfssize;		/* default segment offset size (16,32 [,64]-bit) */
    unsigned char	wordsize;		/* current word size (2,4,8) */
    unsigned char	inside_comment;		/* v2.10: moved from tokenize.c */
    unsigned char	case_sensitive;		/* option casemap */
    unsigned char	convert_uppercase;	/* option casemap */
    unsigned char	procs_private;		/* option proc:private */
    unsigned char	procs_export;		/* option proc:export */
    unsigned char	dotname;		/* option dotname */
    unsigned char	ljmp;			/* option ljmp */
    unsigned char	m510;			/* option m510 */
    unsigned char	scoped;			/* option scoped */
    unsigned char	oldstructs;		/* option oldstructs */
    unsigned char	emulator;		/* option emulator */
    unsigned char	setif2;			/* option setif2 */
    unsigned char	list;			/* .list/.nolist */
    unsigned char	cref;			/* .cref/.nocref */
    unsigned char	listif;			/* .listif/.nolistif */
    unsigned char	list_generated_code;	/* .listall, -Sa, -Sg */
    unsigned char	StartupDirectiveFound;
    unsigned char	EndDirFound;
    unsigned char	frame_auto;		/* win64 only */
    unsigned char	NoSignExtend;		/* option nosignextend */
    unsigned char	simseg_init;		/* simplified segm dir flags */
    union {
	struct {
	unsigned char	elf_osabi;		/* for ELF */
	unsigned char	win64_flags;		/* for WIN64 + PE(32+) */
	};
	struct MZDATA	mz_data;		/* for MZ */
    };
    unsigned char	simseg_defd;		/* v2.09: flag if seg was defined before simseg dir */
    unsigned char	PhaseError;		/* phase error flag */
    unsigned char	CommentDataInCode;	/* OMF: emit coment records about data in code segs */
    unsigned char	prologuemode;		/* current PEM_ enum value for OPTION PROLOGUE */
    unsigned char	epiloguemode;		/* current PEM_ enum value for OPTION EPILOGUE */
    unsigned char	invoke_exprparm;	/* flag: forward refs for INVOKE params ok? */
    unsigned char	cv_opt;			/* option codeview */
    unsigned char	strict_masm_compat;	/* -Zne option	 */
    unsigned		srcfile;		/* main source file - is an index for FNames[] */
    struct dsym		*currseg;		/* currently active segment */
    struct dsym		*flat_grp;		/* magic FLAT group */
    unsigned char	*pCodeBuff;
    unsigned int	GeneratedCode;		/* nesting level generated code */
    /* input members */
    char		*currsource;		/* current source line */
    char		*CurrComment;		/* current comment */
    struct asm_tok	*tokenarray;		/* start token buffer */
    char		*stringbufferend;	/* start free space in string buffer */
    int			token_count;		/* number of tokens in curr line */
    unsigned		basereg[3];		/* stack base register (16-, 32-, 64-bit */
    char		name[FILENAME_MAX];	/* name of module */
    unsigned char	xflag;			/* extended options */
    unsigned char	loopalign;		/* OPTION:LOOPALIGN setting */
    unsigned char	casealign;		/* OPTION:CASEALIGN setting */
    unsigned char	epilogueflags;		/* OPTION EPILOGUE: FLAGS */
    char *		assert_proc;		/* .assert:<handler> */
    unsigned		codepage;		/* Unicode code page */
    unsigned		class_label;
};

#define CurrSource	ModuleInfo.currsource
#define Token_Count	ModuleInfo.token_count
#define StringBufferEnd ModuleInfo.stringbufferend
#define CurrFile	ModuleInfo.g.curr_file
#define CurrFName	ModuleInfo.g.curr_fname
#define CurrSeg		ModuleInfo.currseg
#define CurrWordSize	ModuleInfo.wordsize

struct format_options {
    void (*init)( struct module_info * );
    short invalid_fixup_type;
    const char formatname[6];
};

/* global variables */

extern struct global_options Options;
extern struct module_info    ModuleInfo;

extern unsigned int  Parse_Pass;    /* assembly pass */
extern unsigned char MacroLevel;    /* macro nesting level */
extern unsigned int  write_to_file; /* 1=write the object module */

int asmerr(int, ...);

/* functions in assemble.asm */

struct fixup;

int  FASTCALL DelayExpand( struct asm_tok *);
void OutputByte( unsigned char );
void FillDataBytes( unsigned char, int );
void OutputBytes( const unsigned char *, int, struct fixup * );
int  AssembleModule( char * );
void SetMasm510( int );
void close_files( void );
char *ConvertSectionName( const struct asym *, unsigned *, char * );

char *myltoa( uint_32, char *, unsigned, bool, bool );
void AddLinnumDataRef( unsigned, uint_32 );

void _atoow(void *, const char *, int, int);
void write_logo(void);
void write_usage(void);
void write_options(void);
void RewindToWin64(void);

#endif
