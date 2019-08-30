#include <globals.h>
#include <memalloc.h>
#include <input.h>

#if defined(__UNIX__) || defined(__CYGWIN__)
#define HANDLECTRLZ 0
#define SWITCHCHAR 0
#else
#define HANDLECTRLZ 1
#define SWITCHCHAR 1
#endif

extern int banner_printed;

struct global_options Options = {
	0,			// .quiet
	0,			// .line_numbers
	0,			// .debug_symbols
	0,			// .debug_ext
	FPO_NO_EMULATION,	// .floating_point
	50,			// .error_limit
	0,			// .no_error_disp
	2,			// .warning_level
	0,			// .warning_error
	0,			// .process_subdir
	{0,0,0,0,0,0,0,0,0},	// .names OPTN_LAST dup(0)
	{0,0,0},		// .queues OPTQ_LAST dup(0)
	0,			// .no_comment_in_code_rec
	0,			// .no_opt_farcall
	0,			// .no_file_entry
	0,			// .no_static_procs
	0,			// .no_section_aux_entry
	0,			// .no_cdecl_decoration
	STDCALL_FULL,		// .stdcall_decoration
	0,			// .no_export_decoration
	0,			// .entry_decorated
	0,			// .write_listing
	0,			// .write_impdef
	0,			// .case_sensitive
	0,			// .convert_uppercase
	0,			// .preprocessor_stdout
	0,			// .masm51_compat
	0,			// .strict_masm_compat
	0,			// .masm_compat_gencode
	0,			// .masm8_proc_visibility
	0,			// .listif
	0,			// .list_generated_code
	LM_LISTMACRO,		// .list_macro
	0,			// .do_symbol_listing
	0,			// .first_pass_listing
	0,			// .all_symbols_public
	0,			// .safeseh
#ifdef __ASMC64__
	OFORMAT_COFF,		// .output_format
	SFORMAT_64BIT,		// .sub_format
	LANG_FASTCALL,		// .langtype
	MODEL_FLAT,		// ._model
	P_64,			// .cpu
	FCT_WIN64,		// .fctype
#else
	OFORMAT_OMF,		// .output_format
	SFORMAT_NONE,		// .sub_format
	LANG_NONE,		// .langtype
	MODEL_NONE,		// ._model
	P_86,			// .cpu
	FCT_MSC,		// .fctype
#endif
	0,			// .codepage
	0,			// .ignore_include
	0,			// .fieldalign
	0,			// .syntax_check_only
#ifdef __ASMC64__
	OPT_REGAX,		// .xflag
#else
	0,			// .xflag
#endif
	0,			// .loopalign
	0,			// .casealign
	0,			// .epilogueflags
	4,			// .segmentalign
	0,			// .pe_subsystem
	0,			// .win64_flags
	0,			// .chkstack
	0			// .nolib

};

char *DefaultDir[NUM_FILE_TYPES] = { NULL };
static int OptValue;

void define_name( char *, char * );

/* current cmdline string is done, get the next one! */

static char *getnextcmdstring( char **cmdline )
{
    char **src;
    char **dst;

    for ( dst = cmdline, src = cmdline+1; *src; )
	*dst++ = *src++;
    *dst = *src;
    return( *cmdline );
}

static char *GetNumber( char *p )
{
    OptValue = 0;
    for( ;*p >= '0' && *p <= '9'; p++ )
	OptValue = OptValue * 10 + *p - '0';
    return( p );
}

static char *getfilearg(char **args, char *p) // -Fo<file> or -Fo <file>
{
    char *q;

    if ( *p == 0 && (q = getnextcmdstring(args)) != NULL)
	p = q;
    else if ( *p == '=' )
	p++;

    if ( *p == 0 ) {
	asmerr( 1006, *args );
	return NULL;
    }
    return p;
}

/*
 * queue a text macro, include path or "forced" include files.
 * this is called for cmdline options -D, -I and -Fi
 */
static void queue_item(int i, char *string)
{
    struct qitem *p;
    struct qitem *q;

    p = MemAlloc( strlen( string ) + sizeof( struct qitem ) );
    p->next = NULL;
    strcpy( p->value, string );
    q = Options.queues[i];
    if ( q ) {
	for ( ; q->next; q = q->next );
	q->next = p;
    } else {
	Options.queues[i] = p;
    }
}

static void get_fname( int type, char *token )
{
    char name[_MAX_PATH];
    char *p;

    if ( *token == '=' )
	token++;

    p = GetFNamePart( token );
   /*
    * If name's ending with a '\' (or '/' in Unix), it's supposed
    * to be a directory name only.
    */
    if ( *p == 0 ) {
	if ( type < NUM_FILE_TYPES && *token ) {
	    if ( DefaultDir[type] )
		free( DefaultDir[type] );
	    DefaultDir[type] = malloc( strlen( token ) + 1 );
	    strcpy( DefaultDir[type], token );
	}
	return;
    }
    name[0] = 0;
    if ( token == p && type < NUM_FILE_TYPES && DefaultDir[type] )
	strcpy( name, DefaultDir[type] );
    strcat( name, token );
    free( Options.names[type] );
    Options.names[type] = malloc( strlen( name ) + 1 );
    strcpy( Options.names[type], name );
}

static void set_option_n_name( int idx, const char *name )
{
    char c = *name;

    if ( c != '.' ) {
	if (!(_ltype[c+1] & (_LDIGIT | _LABEL)))
	    c = 0;
    }
    if ( c ) {
	free( Options.names[idx] );
	Options.names[idx] = malloc( strlen( name ) + 1 );
	strcpy( Options.names[idx], name );
    } else {
	asmerr( 1006, name );
    }
}


/*
 * A '@' was found in the cmdline. It's not an environment variable,
 * so check if it is a file and, if yes, read it.
 */

static char *ReadParamFile( const char *name )
{
    char *env;
    FILE *file;
    int	 len;

    env = NULL;
    file = fopen( name, "rb" );
    if( file == NULL ) {
	asmerr( 1000, name );
	return( NULL );
    }
    len = 0;
    if ( fseek( file, 0, SEEK_END ) == 0 ) {
	len = ftell( file );
	rewind( file );
	env = MemAlloc( len + 1 );
#if defined(__GNUC__) /* gcc warns if return value of fread() is "ignored" */
	if ( fread( env, 1, len, file ) )
	;
#else
	fread( env, 1, len, file );
#endif
	env[len] = NULLC;
    }
    fclose( file );
    if ( len == 0)
	return( NULL );
    return( env );
}

/*
 * get a "name"
 * type=@ : filename ( -Fd, -Fi, -Fl, -Fo, -Fw, -I )
 * type=$ : (macro) identifier [=value] ( -D, -nc, -nd, -nm, -nt )
 * type=0 : something else ( -0..-10 )
 */
static char *GetNameToken( char *dst, char *str, int max, char type )
{
    int equatefound = FALSE;

is_quote:
    if( *str == '"' ) {
	++str;
	for( ; max && *str; max-- ) {
	    if ( *str == '"' ) {
		++str;
		break;
	    }
	    /* handle the \"" case */
	    if ( *str == '\\' && *(str+1) == '"' ) {
		++str;
	    }
	    *dst++ = *str++;
	}
    } else {
	for( ; max; max-- ) {
	    /* v2.10: don't stop for white spaces */
	    if ( *str == NULLC )
		break;
	    if ( *str == '\r' || *str == '\n' )
		break;
	    /* v2.10: don't stop for white spaces if filename
	       is expected and true cmdline is parsed */
	    if ( ( *str == ' ' || *str == '\t' ) && ( type != '@' ) )
		break;
	    if ( type == 0 )
		if ( *str == '-'
#if SWITCHCHAR
		    || *str == '/'
#endif
		   )
		    break;
	    if ( *str == '=' && type == '$' && equatefound == FALSE ) {
		equatefound = TRUE;
		*dst++ = *str++;
		if (*str == '"')
		    goto is_quote;
	    }
	    *dst++ = *str++;
	}
    }
    *dst = NULLC;
    return( str );
}


/* array for options -0..10 */

static int cpu_option[] = {
    P_86,
    P_186,
    P_286,
    P_386,
    P_486,
    P_586,
    P_686,
    P_686 | P_MMX,
    P_686 | P_MMX | P_SSE1,
    P_686 | P_MMX | P_SSE1 | P_SSE2,
    P_64
};

static void ProcessOption( char **cmdline, char *buffer )
{
    int i;
    int j;
    char *p = *cmdline;

#ifndef __ASMC64__
    /* numeric option (-0, -1, ... ) handled separately since
     * the value can be >= 10.
     */
    if ( *p >= '0' && *p <= '9' ) {
	p = GetNumber( p );
	if ( OptValue < sizeof(cpu_option)/sizeof(cpu_option[0]) ) {
	    p = GetNameToken( buffer, p, 16, 0 ); /* get optional 'p' */
	    *cmdline = p;
	    i = cpu_option[OptValue];
	    Options.cpu &= ~( P_CPU_MASK | P_EXT_MASK | P_PM );
	    Options.cpu |= i;
	    if ( buffer[1] == 'p' && Options.cpu >= P_286 )
		Options.cpu |= P_PM;
	    return;
	}
	p = *cmdline;	/* v2.11: restore option pointer */
    }
#endif
    if ( *p == 'D' ) {	// -D<name>[=text]
	*cmdline = GetNameToken( buffer, p+1, 256, '$' );
	queue_item( OPTQ_MACRO, buffer );
	return;
    }
    if ( *p == 'I' ) {	// -I<file>
	*cmdline = GetNameToken( buffer, p+1, 256, '@' );
	queue_item( OPTQ_INCPATH, buffer );
	return;
    }

    *cmdline = GetNameToken( buffer, p, 16, 0 );
    j = *(int *)buffer;

    if ( buffer[1] == 0 )
	j &= 0xFF;
    else if ( buffer[2] == 0 )
	j &= 0xFFFF;

    switch ( j ) {
    case 'essa':	// -assert
	Options.xflag |= OPT_ASSERT;
	return;
    case 'otua':	// -autostack
	Options.win64_flags |= W64F_AUTOSTACKSP;
	return;
    case 'c':		// -c
	return;
    case 'ffoc':	// -coff
	Options.output_format = OFORMAT_COFF;
	Options.sub_format = SFORMAT_NONE;
	return;
    case 'PE':		// -EP
	Options.preprocessor_stdout = 1;
    case 'q':		// -q
	Options.quiet = 1;
    case 'olon':	// -nologo
	banner_printed = 1;
	return;
    case 'nib':		// -bin
	Options.output_format = OFORMAT_BIN;
	Options.sub_format = SFORMAT_NONE;
	return;
    case 'pC':		// -Cp
	Options.case_sensitive = 1;
	Options.convert_uppercase = 0;
	return;
    case 'sC':		// -Cs
	Options.xflag |= OPT_CSTACK;
	return;
    case 'uC':		// -Cu
	Options.case_sensitive = 0;
	Options.convert_uppercase = 1;
	return;
    case 'iuc':		// -cui - subsystem:console
	Options.pe_subsystem = 0;
	return;
    case 'xC':		// -Cx
	Options.case_sensitive = 0;
	Options.convert_uppercase = 0;
	return;
    case 'qe':		// -eq
	Options.no_error_disp = 1;
	return;
    case '6fle':	// -elf64
	Options.output_format = OFORMAT_ELF;
	define_name( "_LINUX", "2" );
#ifndef __ASMC64__
	Options.sub_format = SFORMAT_64BIT;
	define_name( "_WIN64", "1" );
#else
	Options.langtype = LANG_SYSCALL;
	Options.fctype = FCT_ELF64;
#endif
	return;
#ifndef __ASMC64__
    case 'fle':		// -elf
	Options.output_format = OFORMAT_ELF;
	Options.sub_format = SFORMAT_NONE;
	define_name( "_LINUX", "1" );
	return;
    case '8iPF':	// -FPi87
	Options.floating_point = FPO_NO_EMULATION;
	return;
    case 'iPF':		// -Fpi
	Options.floating_point = FPO_EMULATION;
	return;
    case '0pf':		// -fp0
	Options.cpu = P_87;
	return;
    case '2pf':		// -fp2
	Options.cpu = P_287;
	return;
    case '3pf':		// -fp3
	Options.cpu = P_387;
	return;
    case 'cpf':		// -fpc
	Options.cpu = P_NO87;
	return;
    case 'cG':		// -Gc
	Options.langtype = LANG_PASCAL;
	return;
    case 'dG':		// -Gd
	Options.langtype = LANG_C;
	return;
#endif
    case 'eG':		// -Ge
	Options.chkstack = 1;
	return;
    case 'rG':		// -Gr
	Options.langtype = LANG_FASTCALL;
	return;
    case 'vG':		// -Gv
	Options.langtype = LANG_VECTORCALL;
	return;
#ifndef __ASMC64__
    case 'zG':		// -Gz
	Options.langtype = LANG_STDCALL;
	return;
#endif
    case 'iug':		// -gui - subsystem:windows
	Options.pe_subsystem = 1;
	define_name( "__GUI__", "1" );
	return;
    case '?':
    case 'h':
	write_options();
	exit( 1 );
    case 'emoh':	// -homeparams
	Options.win64_flags |= W64F_SAVEREGPARAMS;
	return;
#ifndef __ASMC64__
    case 'zm':		// -mz
	Options.output_format = OFORMAT_BIN;
	Options.sub_format = SFORMAT_MZ;
	return;
    case 'cm':		// -mc
	Options.model = MODEL_COMPACT;
	return;
    case 'fm':		// -mf
	Options.model = MODEL_FLAT;
	return;
    case 'hm':		// -mh
	Options.model = MODEL_HUGE;
	return;
    case 'lm':		// -ml
	Options.model = MODEL_LARGE;
	return;
    case 'mm':		// -mm
	Options.model = MODEL_MEDIUM;
	return;
    case 'sm':		// -ms
	Options.model = MODEL_SMALL;
	return;
    case 'tm':		// -mt
	Options.model = MODEL_TINY;
	return;
    case 'ilon':	// -nolib
	Options.nolib = TRUE;
	return;
    case 'fmo':		// -omf
	Options.output_format = OFORMAT_OMF;
	Options.sub_format = SFORMAT_NONE;
	return;
#endif
    case 'fp':		// -pf
	Options.epilogueflags = 1;
	return;
    case 'ep':		// -pe
	if ( Options.sub_format != SFORMAT_64BIT )
	    Options.sub_format = SFORMAT_PE;
	Options.output_format = OFORMAT_BIN;
	define_name( "__PE__", "1" );
	return;
    case 'r':		// -r
	Options.process_subdir = 1;
	return;
    case 'aS':		// -Sa
	return;
    case 'fS':		// -Sf
	Options.first_pass_listing = 1;
	return;
    case 'gS':		// -Sg
	Options.list_generated_code = 1;
	return;
    case 'nS':		// -Sn
	Options.no_symbol_listing = 1;
	return;
    case 'cats':	// -stackalign
	Options.win64_flags |= W64F_STACKALIGN16;
	return;
    case 'xS':		// -Sx
	Options.listif = 1;
	return;
    case 'pws':		// -swp
	Options.xflag |= OPT_PASCAL;
	return;
    case 'cws':		// -swc
	Options.xflag &= ~OPT_PASCAL;
	return;
    case 'rws':		// -swr
	Options.xflag |= OPT_REGAX;
	return;
    case 'nws':		// -swn
	Options.xflag |= OPT_NOTABLE;
	return;
    case 'tws':		// -swt
	Options.xflag &= ~OPT_NOTABLE;
	return;
    case 'efas':	// -safeseh
	Options.safeseh = 1;
	return;
    case 'w':		// -w
	Options.warning_level = 0;
	return;
    case 'sw':		// -ws
	Options.xflag |= OPT_WSTRING;
	define_name( "_UNICODE", "1" );
	return;
    case 'XW':		// -WX
	Options.warning_error = 1;
	return;
    case '6niw':	// -win64
#ifndef __ASMC64__
	if ( Options.output_format != OFORMAT_BIN ) {
	    Options.output_format = OFORMAT_COFF;
	} else {
	    Options.model = MODEL_FLAT;
	    if ( Options.langtype != LANG_VECTORCALL )
		Options.langtype = LANG_FASTCALL;
	}
	Options.sub_format = SFORMAT_64BIT;
	define_name( "_WIN64", "1" );
	Options.xflag |= OPT_REGAX;
#endif
	return;
    case 'X':		// -X
	Options.ignore_include = 1;
	return;
#ifndef __ASMC64__
    case 'mcz':		// -zcm
	Options.no_cdecl_decoration = 0;
	return;
    case 'wcz':		// -zcw
	Options.no_cdecl_decoration = 1;
	return;
#endif
    case 'fZ':		// -Zf
	Options.all_symbols_public = 1;
	return;
#ifdef __ASMC64__
    case '0fz':		// -zf0
	Options.fctype = FCT_MSC;
	return;
    case '1fz':		// -zf1
	Options.fctype = FCT_WATCOMC;
	return;
#endif
    case 'gZ':		// -Zg
	Options.masm_compat_gencode = 1;
	return;
    case 'dZ':		// -Zd
	Options.line_numbers = 1;
	return;
    case 'clz':		// -zlc
	Options.no_comment_in_code_rec = 1;
	return;
    case 'dlz':		// -zld
	Options.no_opt_farcall = 1;
	return;
    case 'flz':		// -zlf
	Options.no_file_entry = 1;
	return;
    case 'plz':		// -zlp
	Options.no_static_procs = 1;
	return;
    case 'slz':		// -zls
	Options.no_section_aux_entry = 1;
	return;
#ifndef __ASMC64__
    case 'mZ':		// -Zm
	Options.masm51_compat = 1;
#endif
    case 'enZ':		// -Zne
	Options.strict_masm_compat = 1;
	return;
    case 'sZ':		// -Zs
	Options.syntax_check_only = 1;
	return;
#ifndef __ASMC64__
    case '0tz':		// -zt0
	Options.stdcall_decoration = 0;
	return;
    case '1tz':		// -zt1
	Options.stdcall_decoration = 1;
	return;
    case '2tz':		// -zt2
	Options.stdcall_decoration = 2;
	return;
    case '8vZ':		// -Zv8
	Options.masm8_proc_visibility = 1;
	return;
#endif
    case 'ezz':		// -zze
	Options.no_export_decoration = 1;
	return;
    case 'szz':		// -zzs
	Options.entry_decorated = 1;
	return;
    }

    *cmdline = p;
    if ( *p == 'e' ) {	// -e<number>
	*cmdline = GetNumber( p + 1 );
	Options.error_limit = OptValue;
	return;
    }
    if ( *p == 'W' ) {	// -W<number>
	*cmdline = GetNumber( p + 1 );
	if ( OptValue < 0 )
	    asmerr( 8000, p );
	else if ( OptValue > 3 )
	    asmerr( 4008, p );
	else
	    Options.warning_level = OptValue;
	return;
    }

    j &= 0xFFFF;
    *cmdline = GetNumber( p + 2 );
    switch ( j ) {
    case 'sw':		// -ws<number>
	Options.codepage = OptValue;
	Options.xflag |= OPT_WSTRING;
	define_name( "_UNICODE", "1" );
	return;
    case 'pS':		// -Zp<number>
	j = 0;
	do {
	    i = ( 1 << j++ );
	    if ( i > MAX_SEGMENT_ALIGN )
		asmerr( 1006, p );
	} while ( i != OptValue );
	Options.segmentalign = j - 1;
	return;
    case 'pZ':		// -Zp<number>
	j = 0;
	do {
	    i = ( 1 << j++ );
	    if ( i > MAX_STRUCT_ALIGN )
		asmerr( 1006, p );
	} while ( i != OptValue );
	Options.fieldalign = j - 1;
	return;
    case 'iZ':		// -Zi[0|1|2|3]
	Options.line_numbers = 1;
	Options.debug_symbols = 1;
	Options.debug_ext = CVEX_NORMAL;
	if ( OptValue ) {
	    if ( OptValue > CVEX_MAX )
		asmerr( 1006, p );
	    Options.debug_ext = OptValue;
	}
	return;
    }

    *cmdline = GetNameToken( buffer, p+2, 256, '$' );
    switch ( j ) {
    case 'cn':		// -nc<name>
	set_option_n_name( OPTN_CODE_CLASS, buffer );
	return;
    case 'dn':		// -nd<name>
	set_option_n_name( OPTN_DATA_SEG, buffer );
	return;
    case 'mn':		// -nm<name>
	set_option_n_name( OPTN_MODULE_NAME, buffer );
	return;
    case 'tn':		// -nt<name>
	set_option_n_name( OPTN_TEXT_SEG, buffer );
	return;
    }

    *cmdline = GetNameToken( buffer, p+2, 256, '@' );
    switch ( j ) {
    case 'dF':		// -Fd[file]
	Options.write_impdef = 1;
	get_fname( OPTN_LNKDEF_FN, buffer );
	return;
    case 'lF':		// -Fl[file]
	Options.write_listing = 1;
	get_fname( OPTN_LST_FN, buffer );
	return;
    }
    if ( (p = getfilearg( cmdline, p+2 )) != NULL ) {
	*cmdline = GetNameToken( buffer, p, 256, '@' );
	if ( j == 'iF' ) {	// -Fi<file>
	    queue_item( OPTQ_FINCLUDE, buffer );
	    return;
	}
	if ( j == 'oF' ) {	// -Fo<file>
	    get_fname( OPTN_OBJ_FN, buffer );
	    return;
	}
	if ( j == 'wF' ) {	// -Fw<file>
	    get_fname( OPTN_ERR_FN, buffer );
	    return;
	}
    }
    asmerr( 1006, p );
}

char *ParseCmdline( char **cmdline, int *numargs )
{
    int i;
    char *str = *cmdline;
    char paramfile[_MAX_PATH];

    for ( i = 0; i < NUM_FILE_TYPES; i++ )
	if ( Options.names[i] != NULL ) {
	    MemFree( Options.names[i] );
	    Options.names[i] = NULL;
	}
    for( ; str; ) {
	switch( *str ) {
	case '\r':
	case '\n':
	case '\t':
	case ' ':
	    str++;
	    break;
	case NULLC:
	    str = getnextcmdstring( cmdline );
	    break;
	case '-':
#if SWITCHCHAR
	case '/':
#endif
	    str++;
	    *cmdline = str;
	    ProcessOption( cmdline, paramfile );
	    (*numargs)++;
	    str = *cmdline;
	    break;
	case '@':
	    str++;
	    *cmdline = GetNameToken( paramfile, str, sizeof( paramfile ) - 1, '@' );
	    str = NULL;
	    if ( paramfile[0] )
		str = getenv( paramfile );
	    if( str == NULL ) {
		str = ReadParamFile( paramfile );
		if ( str == NULL ) {
		    break;
		}
	    }
	    break;
	default: /* collect  file name */
	    str = GetNameToken( paramfile, str, sizeof( paramfile ) - 1, '@' );
	    Options.names[ASM] = MemAlloc( strlen( paramfile ) + 1 );
	    strcpy( Options.names[ASM], paramfile );
	    (*numargs)++;
	    *cmdline = str;
	    return( Options.names[ASM] );
	}
    }
    *cmdline = str;
    return( NULL );
}

void CmdlineFini(void)
{
    struct qitem *q, *x;
    char *p;
    int i = 0;

    while ( i < NUM_FILE_TYPES ) {
	p = DefaultDir[i];
	DefaultDir[i] = NULL;
	Options.names[i] = NULL;
	free( p );
	i++;
    }
    i = 0;
    while ( i < OPTQ_LAST ) {
	q = Options.queues[i];
	while ( q ) {
		x = q->next;
		free( q );
		q = x;
	}
	Options.queues[i] = NULL;
	i++;
    }
}

