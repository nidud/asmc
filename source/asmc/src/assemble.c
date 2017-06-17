/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	assemble a module.
*
****************************************************************************/

#include <time.h>

#include "globals.h"
#include "memalloc.h"
#include "input.h"
#include "parser.h"
#include "reswords.h"
#include "tokenize.h"
#include "condasm.h"
#include "segment.h"
#include "assume.h"
#include "proc.h"
#include "expreval.h"
#include "hll.h"
#include "context.h"
#include "types.h"
#include "label.h"
#include "macro.h"
#include "extern.h"
#include "fixup.h"
#include "omf.h"
#include "fastpass.h"
#include "listing.h"
#include "linnum.h"
#include "cpumodel.h"
#include "lqueue.h"
#include "mangle.h"
#include "coff.h"
#include "elf.h"
#include "bin.h"

#include <setjmp.h>
jmp_buf jmpenv;

#ifdef __SW_BD
#define EXPQUAL __stdcall
#else
#define EXPQUAL
#endif

#ifdef __UNIX__
#define OBJ_EXT "o"
#else
#define OBJ_EXT "obj"
#endif
#define LST_EXT "lst"
#define ERR_EXT "err"
#define BIN_EXT "BIN"
#define EXE_EXT "exe"

extern int_32 LastCodeBufSize;
extern char *DefaultDir[NUM_FILE_TYPES];
extern const char *ModelToken[];
extern int MacroLocals;

/* parameters for output formats. order must match enum oformat */
static const struct format_options formatoptions[] = {
    { bin_init,	 BIN_DISALLOWED,    "BIN"  },
    { omf_init,	 OMF_DISALLOWED,    "OMF"  },
    { coff_init, COFF32_DISALLOWED, "COFF" },
    { elf_init,	 ELF32_DISALLOWED,  "ELF"  },
};

struct module_info	ModuleInfo;
unsigned int		Parse_Pass;    /* assembly pass */
struct qdesc		LinnumQueue;   /* queue of line_num_info items */
unsigned int		write_to_file; /* write object module */


/* struct to help convert section names in COFF, ELF, PE */
struct conv_section {
    uint_8 len;
    uint_8 flags; /* see below */
    const char *src;
    const char *dst;
};
enum cvs_flags {
    CSF_GRPCHK = 1
};

enum conv_section_index {
    CSI_TEXT = 0,
    CSI_DATA,
    CSI_CONST,
    CSI_BSS
};

/* order must match enum conv_section_index above */
static const struct conv_section cst[] = {
    { 5, CSF_GRPCHK, "_TEXT", ".text"  },
    { 5, CSF_GRPCHK, "_DATA", ".data"  },
    { 5, CSF_GRPCHK, "CONST", ".rdata" },
    { 4, 0,	     "_BSS",  ".bss"   }
};

/* order must match enum conv_section_index above */
static const enum seg_type stt[] = {
    SEGTYPE_CODE, SEGTYPE_DATA, SEGTYPE_DATA, SEGTYPE_BSS
};

/*
 * translate section names (COFF+PE):
 * _TEXT -> .text
 * _DATA -> .data
 * CONST -> .rdata
 * _BSS	 -> .bss
 */

char *ConvertSectionName( const struct asym *sym, unsigned *pst, char *buffer )
{
    int i;

    for ( i = 0; i < sizeof( cst ) / sizeof( cst[0] ); i++ ) {
	if ( memcmp( sym->name, cst[i].src, cst[i].len ) == 0 ) {
	    if ( sym->name[cst[i].len] == NULLC || ( sym->name[cst[i].len] == '$' && ( cst[i].flags & CSF_GRPCHK ) ) ) {

		if ( pst ) {
		    if ( i == CSI_BSS && ( (struct dsym *)sym)->e.seginfo->bytes_written != 0 )
			; /* don't set segment type to BSS if the segment contains initialized data */
		    else
			*pst = stt[i];
		}

		if ( sym->name[cst[i].len] == NULLC ) {
		    return( (char *)cst[i].dst );
		}

		strcpy( buffer, cst[i].dst );
		strcat( buffer, sym->name+cst[i].len );
		return( buffer );
	    }
	}
    }
    return( sym->name );
}

/* Write a byte to the segment buffer.
 * in OMF, the segment buffer is flushed when the max. record size is reached.
 */
void OutputByte( unsigned char byte )
{
    if( write_to_file == TRUE ) {
	uint_32 idx = CurrSeg->e.seginfo->current_loc - CurrSeg->e.seginfo->start_loc;
	if( Options.output_format == OFORMAT_OMF && idx >= MAX_LEDATA_THRESHOLD ) {
	    omf_FlushCurrSeg();
	    idx = CurrSeg->e.seginfo->current_loc - CurrSeg->e.seginfo->start_loc;
	}
	CurrSeg->e.seginfo->CodeBuffer[idx] = byte;
    }
    /* check this in pass 1 only */
    else if( CurrSeg->e.seginfo->current_loc < CurrSeg->e.seginfo->start_loc ) {
	CurrSeg->e.seginfo->start_loc = CurrSeg->e.seginfo->current_loc;
    }
    CurrSeg->e.seginfo->current_loc++;
    CurrSeg->e.seginfo->bytes_written++;
    CurrSeg->e.seginfo->written = TRUE;
    if( CurrSeg->e.seginfo->current_loc > CurrSeg->sym.max_offset )
	CurrSeg->sym.max_offset = CurrSeg->e.seginfo->current_loc;
}

/*
 * this function is to output (small, <= 8) amounts of bytes which must
 * not be separated ( for omf, because of fixups )
 */

void OutputBytes( const unsigned char *pbytes, int len, struct fixup *fixup )
{
    if( write_to_file == TRUE ) {
	uint_32 idx = CurrSeg->e.seginfo->current_loc - CurrSeg->e.seginfo->start_loc;

	if( Options.output_format == OFORMAT_OMF && ((idx + len) >= MAX_LEDATA_THRESHOLD ) ) {
	    omf_FlushCurrSeg();
	    idx = CurrSeg->e.seginfo->current_loc - CurrSeg->e.seginfo->start_loc;
	}
	if ( fixup )
	    store_fixup( fixup, CurrSeg, (int_32 *)pbytes );
	memcpy( &CurrSeg->e.seginfo->CodeBuffer[idx], pbytes, len );
    }
    /* check this in pass 1 only */
    else if( CurrSeg->e.seginfo->current_loc < CurrSeg->e.seginfo->start_loc ) {
	CurrSeg->e.seginfo->start_loc = CurrSeg->e.seginfo->current_loc;
    }
    CurrSeg->e.seginfo->current_loc += len;
    CurrSeg->e.seginfo->bytes_written += len;
    CurrSeg->e.seginfo->written = TRUE;
    if( CurrSeg->e.seginfo->current_loc > CurrSeg->sym.max_offset )
	CurrSeg->sym.max_offset = CurrSeg->e.seginfo->current_loc;
}

void FillDataBytes( unsigned char byte, int len )
{
    if ( ModuleInfo.CommentDataInCode )
	omf_OutSelect( TRUE );
    for( ; len; len-- )
	OutputByte( byte );
}


/* set current offset in a segment (usually CurrSeg) without to write anything */

int SetCurrOffset( struct dsym *seg, uint_32 value, bool relative, bool select_data )
{
    if( relative )
	value += seg->e.seginfo->current_loc;

    if ( Options.output_format == OFORMAT_OMF ) {
	if ( seg == CurrSeg ) {
	    if ( write_to_file == TRUE )
		omf_FlushCurrSeg();

	/* for debugging, tell if data is located in code sections*/
	    if( select_data )
		if ( ModuleInfo.CommentDataInCode )
		    omf_OutSelect( TRUE );
	    LastCodeBufSize = value;
	}
	seg->e.seginfo->start_loc = value;
    /* for -bin, if there's an ORG (relative==false) and no initialized data
     * has been set yet, set start_loc!
     * v1.96: this is now also done for COFF and ELF
     */
    } else if ( !write_to_file && !relative ) {

	if ( seg->e.seginfo->bytes_written == 0 )
	    seg->e.seginfo->start_loc = value;
    }

    seg->e.seginfo->current_loc = value;
    seg->e.seginfo->written = FALSE;

    if( seg->e.seginfo->current_loc > seg->sym.max_offset )
	seg->sym.max_offset = seg->e.seginfo->current_loc;

    return( NOT_ERROR );
}

/* write object module */

static int WriteModule( struct module_info *modinfo )
{
    struct dsym *curr;

    /* final checks */
    /* check limit of segments */
    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {
	if ( curr->e.seginfo->Ofssize == USE16 && curr->sym.max_offset > 0x10000 ) {
	    if ( Options.output_format == OFORMAT_OMF )
		asmerr( 2103, curr->sym.name );
	}
    }
    modinfo->g.WriteModule( modinfo );

    /* is the -Fd option given with a file name? */
    if ( Options.names[OPTN_LNKDEF_FN] ) {
	FILE *ld;
	ld = fopen( Options.names[OPTN_LNKDEF_FN], "w" );
	if ( ld == NULL ) {
	    return( asmerr( 3020, Options.names[OPTN_LNKDEF_FN] ) );
	}
	for ( curr = SymTables[TAB_EXT].head; curr != NULL ; curr = curr->next ) {
	    if ( curr->sym.isproc && ( curr->sym.weak == FALSE || curr->sym.iat_used ) &&
		curr->sym.dll && *(curr->sym.dll->name) != NULLC ) {
		int size;
		Mangle( &curr->sym, StringBufferEnd );
		size = sprintf( CurrSource, "import '%s'  %s.%s\n", StringBufferEnd, curr->sym.dll->name, curr->sym.name );
		if ( fwrite( CurrSource, 1, size, ld ) != size )
		    WriteError();
	    }
	}
	fclose( ld );
    }
    return( NOT_ERROR );
}

/* check name of text macros defined via -D option */

static int is_valid_identifier( char *id )
{
    /* special handling of first char of an id: it can't be a digit,
     but can be a dot (don't care about ModuleInfo.dotname!). */

    if( is_valid_first_char( *id ) == 0 )
	return( ERROR );
    id++;
    for( ; *id != NULLC; id++ ) {
	if ( is_valid_id_char( *id ) == FALSE )
	    return( ERROR );
    }
    /* don't allow a single dot! */
    if ( *(id-1) == '.' )
	return( ERROR );

    return( NOT_ERROR );
}

/* add text macros defined with the -D cmdline switch */

static void add_cmdline_tmacros( void )
{
    struct qitem *p;
    char *name;
    char *value;
    int len;
    struct asym *sym;

    for ( p = Options.queues[OPTQ_MACRO]; p; p = p->next ) {
	name = p->value;
	value = strchr( name, '=' );
	if( value == NULL ) {
	    /* v2.06: ensure that 'value' doesn't point to r/o space */
	    value = name + strlen( name ); /* use the terminating NULL */
	} else {
	    len = value - name;
	    name = (char *)myalloca( len + 1 );
	    memcpy( name, p->value, len );
	    *(name + len) = NULLC;
	    value++;
	}

	/* there's no check whether the name is a reserved word! */
	if( is_valid_identifier( name ) == ERROR ) {
	    asmerr( 2008, name );
	} else {
	    sym = SymSearch( name );
	    if ( sym == NULL ) {
		sym = SymCreate( name );
		sym->state = SYM_TMACRO;
	    }
	    if ( sym->state == SYM_TMACRO ) {
		sym->isdefined = TRUE;
		sym->predefined = TRUE;
		sym->string_ptr = value;
	    } else
		asmerr( 2005, name );
	}
    }
    return;
}

/* add the include paths set by -I option */

static void add_incpaths( void )
{
    struct qitem *p;
    for ( p = Options.queues[OPTQ_INCPATH]; p; p = p->next ) {
	AddStringToIncludePath( p->value );
    }
}

/* this is called for every pass.
 * symbol table and ModuleInfo are initialized.
 */
static void CmdlParamsInit( int pass )
{

    if ( pass == PASS_1 ) {
	char *env;
	/* v2.06: this is done in ModulePassInit now */
	add_cmdline_tmacros();
	add_incpaths();
	if ( Options.ignore_include == FALSE ) {
	    if ( env = getenv( "INCLUDE" ) )
		AddStringToIncludePath( env );
	}
    }
}

void WritePreprocessedLine( const char *string )
/* print out preprocessed source lines */
{
    static bool PrintEmptyLine = TRUE;
    const char *p;

    if ( Token_Count > 0 ) {
	/* v2.08: don't print a leading % (this char is no longer filtered) */
	for ( p = string; islspace( *p ); p++ );
	printf("%s\n", *p == '%' ? p+1 : string );
	PrintEmptyLine = TRUE;
    } else if ( PrintEmptyLine ) {
	PrintEmptyLine = FALSE;
	printf("\n");
    }
}

/* set Masm v5.1 compatibility options */

void SetMasm510( bool value )
/***************************/
{
    ModuleInfo.m510 = value;
    ModuleInfo.oldstructs = value;
    /* ModuleInfo.oldmacros = value; not implemented yet */
    ModuleInfo.dotname = value;
    ModuleInfo.setif2 = value;

    if ( value ) {
	if ( ModuleInfo.model == MODEL_NONE ) {
	    /* if no model is specified, set OFFSET:SEGMENT */
	    ModuleInfo.offsettype = OT_SEGMENT;
	    if ( ModuleInfo.langtype == LANG_NONE ) {
		ModuleInfo.scoped = FALSE;
		ModuleInfo.procs_private = TRUE;
	    }
	}
    }
}

/* called for each pass */

static void ModulePassInit( void )
/********************************/
{
    enum cpu_info cpu = Options.cpu;
    enum model_type model = Options.model;
    struct dsym *curr;

    /* set default values not affected by the masm 5.1 compat switch */
    ModuleInfo.procs_private = FALSE;
    ModuleInfo.procs_export = FALSE;
    ModuleInfo.offsettype = OT_GROUP;
    ModuleInfo.scoped = TRUE;


    /* v2.03: don't generate the code if fastpass is active */
    /* v2.08: query UseSavedState instead of StoreState */
    if ( UseSavedState == FALSE ) {
	ModuleInfo.langtype = Options.langtype;
	ModuleInfo.fctype = Options.fctype;
	if ( ModuleInfo.sub_format == SFORMAT_64BIT ) {
	    /* v2.06: force cpu to be at least P_64, without side effect to Options.cpu */
	    if ( ( cpu &  P_CPU_MASK ) < P_64 ) /* enforce cpu to be 64-bit */
		cpu = P_64;
	    /* ignore -m switch for 64-bit formats.
	     * there's no other model than FLAT possible.
	     */
	    model = MODEL_FLAT;
	    if ( ModuleInfo.langtype == LANG_NONE ) {
		if ( Options.output_format == OFORMAT_COFF )
		    ModuleInfo.langtype = LANG_FASTCALL;
		else
		    ModuleInfo.langtype = LANG_SYSCALL;
	    }
	} else
	    /* if model FLAT is to be set, ensure that cpu is compat. */
	    if ( model == MODEL_FLAT && ( cpu & P_CPU_MASK ) < P_386 ) /* cpu < 386? */
		cpu = P_386;

	SetCPU( cpu );
	/* table ModelToken starts with MODEL_TINY, which is index 1"" */
	if ( model != MODEL_NONE )
	    AddLineQueueX( "%r %s", T_DOT_MODEL, ModelToken[model - 1] );
    }

    SetMasm510( Options.masm51_compat );
    ModuleInfo.defOfssize = USE16;
    ModuleInfo.ljmp	= TRUE;

    ModuleInfo.list   = Options.write_listing;
    ModuleInfo.cref   = TRUE;
    ModuleInfo.listif = Options.listif;
    ModuleInfo.list_generated_code = Options.list_generated_code;
    ModuleInfo.list_macro = Options.list_macro;

    ModuleInfo.case_sensitive = Options.case_sensitive;
    ModuleInfo.convert_uppercase = Options.convert_uppercase;
    SymSetCmpFunc();

    ModuleInfo.segorder = SEGORDER_SEQ;
    ModuleInfo.radix = 10;
    ModuleInfo.fieldalign = Options.fieldalign;
    ModuleInfo.procalign = 0;

    ModuleInfo.aflag &= _AF_LSTRING;
    ModuleInfo.aflag |= Options.aflag;
    ModuleInfo.loopalign = Options.loopalign;
    ModuleInfo.casealign = Options.casealign;
    ModuleInfo.codepage = Options.codepage;

    /* if OPTION DLLIMPORT was used, reset all iat_used flags */
    if ( ModuleInfo.g.DllQueue )
	for ( curr = SymTables[TAB_EXT].head; curr; curr = curr->next )
	    curr->sym.iat_used = FALSE;
}

/* checks after pass one has been finished without errors */

static void PassOneChecks( void )
{
    struct dsym *curr;
    struct dsym *next;
    struct qnode *q;
    struct qnode *qn;

    /* check for open structures and segments has been done inside the
     * END directive handling already
     * v2.10: now done for PROCs as well, since procedures
     * must be closed BEFORE segments are to be closed.
     */
    HllCheckOpen();
    CondCheckOpen();

    if( ModuleInfo.EndDirFound == FALSE )
	asmerr( 2088 );

    /* v2.04: check the publics queue.
     * - only internal symbols can be public.
     * - weak external symbols are filtered ( since v2.11 )
     * - anything else is an error
     * v2.11: moved here ( from inside the "#if FASTPASS"-block )
     * because the loop will now filter weak externals [ this
     * was previously done in GetPublicSymbols() ]
     */
    for( q = ModuleInfo.g.PubQueue.head, qn = (struct qnode *)&ModuleInfo.g.PubQueue ; q; q = q->next ) {

	if ( q->sym->state == SYM_INTERNAL )
	    qn = q;
	else if ( q->sym->state == SYM_EXTERNAL && q->sym->weak == TRUE ) {
	    qn->next = q->next;
	    q = qn;
	} else {
	    SkipSavedState();
	    goto aliases;
	}
    }

    /* check if there's an undefined segment reference.
     * This segment was an argument to a group definition then.
     * Just do a full second pass, the GROUP directive will report
     * the error.
     */
    for( curr = SymTables[TAB_SEG].head; curr; curr = curr->next ) {
	if( curr->sym.segment == NULL ) {
	    SkipSavedState();
	    goto aliases;
	}
    }

    /* if there's an item in the safeseh list which is not an
     * internal proc, make a full second pass to emit a proper
     * error msg at the .SAFESEH directive
     */
    for ( q = ModuleInfo.g.SafeSEHQueue.head; q; q = q->next ) {
	if ( q->sym->state != SYM_INTERNAL || q->sym->isproc == FALSE ) {
	    SkipSavedState();
	    break;
	}
    }

aliases:

    /* scan ALIASes for COFF/ELF */

    if ( Options.output_format == OFORMAT_COFF || Options.output_format == OFORMAT_ELF ) {
	for( curr = SymTables[TAB_ALIAS].head ; curr != NULL ;curr = curr->next ) {
	    struct asym *sym;
	    sym = curr->sym.substitute;
	    /* check if symbol is external or public */
	    if ( sym == NULL ||
		( sym->state != SYM_EXTERNAL &&
		 ( sym->state != SYM_INTERNAL || sym->ispublic == FALSE ))) {
		SkipSavedState();
		break;
	    }
	    /* make sure it becomes a strong external */
	    if ( sym->state == SYM_EXTERNAL )
		sym->used = TRUE;
	}
    }

    /* scan the EXTERN/EXTERNDEF items */

    for( curr = SymTables[TAB_EXT].head ; curr; curr = next ) {
	next = curr->next;
	/* v2.01: externdefs which have been "used" become "strong" */
	if ( curr->sym.used )
	    curr->sym.weak = FALSE;
	/* remove unused EXTERNDEF/PROTO items from queue. */
	if ( curr->sym.weak == TRUE && curr->sym.iat_used == FALSE ) {
	    sym_remove_table( &SymTables[TAB_EXT], curr );
	    continue;
	}
	if ( curr->sym.iscomm == TRUE )
	    continue;
	/* optional alternate symbol must be INTERNAL or EXTERNAL.
	 * COFF ( and ELF? ) also wants internal symbols to be public
	 * ( which is reasonable, since the linker won't know private
	 * symbols and hence will search for a symbol of that name
	 * "elsewhere" ).
	 */
	if ( curr->sym.altname ) {
	    if ( curr->sym.altname->state == SYM_INTERNAL ) {
		/* for COFF/ELF, the altname must be public or external */
		if ( curr->sym.altname->ispublic == FALSE &&
		    ( Options.output_format == OFORMAT_COFF || Options.output_format == OFORMAT_ELF ) ) {
		    SkipSavedState();
		}
	    } else if ( curr->sym.altname->state != SYM_EXTERNAL ) {
		/* do not use saved state, scan full source in second pass */
		SkipSavedState();
	    }
	}
    }

    if ( ModuleInfo.g.error_count == 0 ) {

	/* make all symbols of type SYM_INTERNAL, which aren't
	 a constant, public.  */
	if ( Options.all_symbols_public )
	    SymMakeAllSymbolsPublic();

	if ( Options.syntax_check_only == FALSE )
	    write_to_file = TRUE;

	if ( ModuleInfo.g.Pass1Checks )
	    ModuleInfo.g.Pass1Checks( &ModuleInfo );
    }
}

/* do ONE assembly pass
 * the FASTPASS variant (which is default now) doesn't scan the full source
 * for each pass. For this to work, the following things are implemented:
 * 1. in pass one, save state if the first byte is to be emitted.
 *    <state> is the segment stack, moduleinfo state, ...
 * 2. once the state is saved, all preprocessed lines must be stored.
 *    this can be done here, in OnePass, the line is in <string>.
 *    Preprocessed macro lines are stored in RunMacro().
 * 3. for subsequent passes do
 *    - restore the state
 *    - read preprocessed lines and feed ParseLine() with it
 */
static int OnePass( void )
{

    InputPassInit();
    ModulePassInit();
    SymPassInit( Parse_Pass );
    LabelInit();
    SegmentInit( Parse_Pass );
    ContextInit( Parse_Pass );
    ProcInit();
    TypesInit();
    HllInit( Parse_Pass );
    MacroInit( Parse_Pass ); /* insert predefined macros */
    AssumeInit( Parse_Pass );
    CmdlParamsInit( Parse_Pass );

    ModuleInfo.EndDirFound = FALSE;
    ModuleInfo.PhaseError = FALSE;
    LinnumInit();

    /* the functions above might have written something to the line queue */
    if ( is_linequeue_populated() )
	RunLineQueue();
    StoreState = FALSE;
    if ( Parse_Pass > PASS_1 && UseSavedState == TRUE ) {
	LineStoreCurr = RestoreState();
	while ( LineStoreCurr && ModuleInfo.EndDirFound == FALSE ) {
	    /* the source line is modified in Tokenize() if it contains a comment! */
	    set_curr_srcfile( LineStoreCurr->srcfile, LineStoreCurr->lineno );
	    /* v2.06: list flags now initialized on the top level */
	    ModuleInfo.line_flags = 0;
	    MacroLevel = ( LineStoreCurr->srcfile == 0xFFF ? 1 : 0 );
	    ModuleInfo.CurrComment = NULL; /* v2.08: added (var is never reset because GetTextLine() isn't called) */
	    if ( Token_Count = Tokenize( LineStoreCurr->line, 0, ModuleInfo.tokenarray, TOK_DEFAULT ) )
		ParseLine( ModuleInfo.tokenarray );
	    LineStoreCurr = LineStoreCurr->next;
	}
    } else {
	struct qitem *pq;
	/* v2.11: handle -Fi files here ( previously in CmdlParamsInit ) */
	for ( pq = Options.queues[OPTQ_FINCLUDE]; pq; pq = pq->next ) {
	    if ( SearchFile( pq->value, TRUE ) )
		ProcessFile( ModuleInfo.tokenarray );
	}
	ProcessFile( ModuleInfo.tokenarray ); /* process the main source file */
    }

    LinnumFini();

    if ( Parse_Pass == PASS_1 )
	PassOneChecks();

    ClearSrcStack();

    return( 1 );
}

static void get_module_name( void )
{
    char *p;

    /* v2.08: prefer name given by -nm option */
    if ( Options.names[OPTN_MODULE_NAME] ) {
	strncpy( ModuleInfo.name, Options.names[OPTN_MODULE_NAME], sizeof( ModuleInfo.name ) );
	ModuleInfo.name[ sizeof( ModuleInfo.name ) - 1] = NULLC;
    } else {
	/* v2.12: _splitpath()/_makepath() removed */
	char *fn = GetFNamePart( CurrFName[ASM] );
	char *ext = GetExtPart( fn );
	memcpy( ModuleInfo.name, fn, ext - fn );
	ModuleInfo.name[ ext - fn ] = NULLC;
    }

    _strupr( ModuleInfo.name );
    /* the module name must be a valid identifier, because it's used
     * as part of a segment name in certain memory models.
     */
    for( p = ModuleInfo.name; *p; ++p ) {
	if( !( is_valid_id_char( *p ))) {
	    /* it's not a legal character for a symbol name */
	    *p = '_';
	}
    }
    /* first character can't be a digit either */
    if( isldigit( ModuleInfo.name[0] ) ) {
	ModuleInfo.name[0] = '_';
    }
}

/* called by AssembleInit(), once per source module.
 * symbol table has been initialized here.
 */
static void ModuleInit( void )
{
    ModuleInfo.sub_format = Options.sub_format;
    ModuleInfo.fmtopt = &formatoptions[Options.output_format];
    ModuleInfo.CommentDataInCode = (Options.output_format == OFORMAT_OMF &&
			 Options.no_comment_in_code_rec == FALSE);
    ModuleInfo.g.error_count = 0;
    ModuleInfo.g.warning_count = 0;
    ModuleInfo.model = MODEL_NONE;
    /* ModuleInfo.distance = STACK_NONE; */
    ModuleInfo.ostype = OPSYS_DOS;
    ModuleInfo.emulator = (Options.floating_point == FPO_EMULATION);

    get_module_name(); /* set ModuleInfo.name */

    /* v2.06: ST_PROC has been removed */
    memset( SymTables, 0, sizeof( SymTables[0] ) * TAB_LAST );
    ModuleInfo.fmtopt->init( &ModuleInfo );
}

static void ReswTableInit( void )
{
    int i;

    ResWordsInit();
    if ( Options.output_format == OFORMAT_OMF ) {
	/* for OMF, IMAGEREL and SECTIONREL are disabled */
	DisableKeyword( T_IMAGEREL );
	DisableKeyword( T_SECTIONREL );
    }

    if ( Options.strict_masm_compat == TRUE ) {
	DisableKeyword( T_INCBIN );
	DisableKeyword( T_FASTCALL );
    }
    if ( !( Options.aflag & _AF_ON ) ) {
	/* added v2.22 - HSE */
	for( i = T_DOT_IFA; i <= T_DOT_ENDSW; i++ )
	    DisableKeyword( i );
    }
}

static void open_files( void )
{
    /* open ASM file */
    CurrFile[ASM] = fopen( CurrFName[ASM], "rb" );
    if( CurrFile[ASM] == NULL ) {
	asmerr( 1000, CurrFName[ASM] );
    }
    /* open OBJ file */
    if ( Options.syntax_check_only == FALSE ) {
	CurrFile[OBJ] = fopen( CurrFName[OBJ], "wb" );
	if( CurrFile[OBJ] == NULL ) {
	    asmerr( 1000, CurrFName[OBJ] );
	}
    }
    if( Options.write_listing ) {
	CurrFile[LST] = fopen( CurrFName[LST], "wb" );
	if ( CurrFile[LST] == NULL )
	    asmerr( 1000, CurrFName[LST] );
    }
}

void close_files( void )
/**********************/
{
    /* v2.11: no fatal errors anymore if fclose() fails.
     * That's because Fatal() may cause close_files() to be
     * reentered and thus cause an endless loop.
     */

    /* close ASM file */
    if( CurrFile[ASM] != NULL ) {
	if( fclose( CurrFile[ASM] ) != 0 )
	    asmerr( 3021, CurrFName[ASM] );
	CurrFile[ASM] = NULL;
    }

    /* close OBJ file */
    if ( CurrFile[OBJ] != NULL ) {
	if ( fclose( CurrFile[OBJ] ) != 0 )
	    asmerr( 3021, CurrFName[OBJ] );
	CurrFile[OBJ] = NULL;
    }
    /* delete the object module if errors occured */
    if ( Options.syntax_check_only == FALSE &&
	ModuleInfo.g.error_count > 0 ) {
	remove( CurrFName[OBJ] );
    }

    if( CurrFile[LST] != NULL ) {
	fclose( CurrFile[LST] );
	CurrFile[LST] = NULL;
    }

    /* close ERR file */
    if ( CurrFile[ERR] != NULL ) {
	fclose( CurrFile[ERR] );
	CurrFile[ERR] = NULL;
    } else if ( CurrFName[ERR] )
	/* nothing written, delete any existing ERR file */
	remove( CurrFName[ERR] );
    return;
}

/* get default file extension for error, object and listing files */

static char *GetExt( int type )
{
    switch ( type ) {
    case OBJ:
	if ( Options.output_format == OFORMAT_BIN )
	    if ( Options.sub_format == SFORMAT_MZ || Options.sub_format == SFORMAT_PE )
		return( EXE_EXT );
	    else
		return( BIN_EXT );
	return( OBJ_EXT );
    case LST:
	return( LST_EXT );
    case ERR:
	return( ERR_EXT );
    }
    return( NULL );
}

/* set filenames for .obj, .lst and .err
 * in:
 *  name: assembly source name
 *  DefaultDir[]: default directory part for .obj, .lst and .err
 * in:
 *  CurrFName[] for .obj, .lst and .err ( may be NULL )
 * v2.12: _splitpath()/_makepath() removed.
 */

static void SetFilenames( char *name )
{
    int i;
    char *fn;
    char *ext;
    char path[ FILENAME_MAX ];

    /* set CurrFName[ASM] */
    CurrFName[ASM] = LclAlloc( strlen( name ) + 1 );
    strcpy( CurrFName[ASM], name );

    /* set [OBJ], [ERR], [LST] */
    fn = GetFNamePart( name );
    for ( i = ASM+1; i < NUM_FILE_TYPES; i++ ) {
	if( Options.names[i] == NULL ) {
	    path[0] = NULLC;
	    if ( DefaultDir[i])
		strcpy( path, DefaultDir[i] );
	    strcat( path, fn );
	    ext = GetExtPart( path );
	    *ext++  = '.';
	    strcpy( ext, GetExt( i ) );

	} else {
	    /* filename has been set by cmdline option -Fo, -Fl or -Fr */
	    char *fn2;
	    strcpy( path, Options.names[i] );
	    fn2 = GetFNamePart( path );
	    if( *fn2 == NULLC )
		strcpy( fn2, fn );
	    ext = GetExtPart( fn2 );
	    if( *ext == NULLC ) {
		*ext++	= '.';
		strcpy( ext, GetExt( i ) );
	    }
	}
	CurrFName[i] = LclAlloc( strlen( path ) + 1 );
	strcpy( CurrFName[i], path );
    }
    return;
}

/* init assembler. called once per module */

static void AssembleInit( char *source )
{
    MemInit();
    write_to_file = FALSE;
    LinnumQueue.head = NULL;
    SetFilenames( source );
    FastpassInit();
    open_files();
    ReswTableInit();
    SymInit();
    InputInit();
    ModuleInit();
    CondInit();
    ExprEvalInit();
    LstInit();
}

/* called once per module. AssembleModule() cleanup */

static void AssembleFini( void )
{
    int i;
    SegmentFini();
    ResWordsFini();
    FreePubQueue();
    InputFini();
    close_files();

    for ( i = 0; i < NUM_FILE_TYPES; i++ ) {
	LclFree( CurrFName[i] );
	/* v2.05: make sure the pointer for ERR is cleared */
	CurrFName[i] = NULL;
    }
    MemFini();
}

/* AssembleModule() assembles one source file */

int EXPQUAL AssembleModule( char *source )
{
    uint_32 prev_written = -1;
    uint_32 curr_written;
    struct dsym *seg;
    int q;

    memset( &ModuleInfo, 0, sizeof(ModuleInfo) );

    if ( !Options.quiet )
	printf( " Assembling: %s\n", source );

    /* fatal errors during assembly won't terminate the program,
     * just the assembly step.!
     */
    if ( ( q = setjmp( jmpenv ) ) ) {

	if ( q == 1 ) {

	    ClearSrcStack();
	    AssembleFini();
	    MacroLocals = 0;
	    memset( &ModuleInfo, 0, sizeof(ModuleInfo) );
	    prev_written = -1;
	} else {

	    if ( ModuleInfo.g.src_stack )
		ClearSrcStack(); /* avoid memory leaks! */
	    goto done;
	}
    }

    AssembleInit( source );

    for( Parse_Pass = PASS_1; ; Parse_Pass++ ) {

	OnePass();

	if( ModuleInfo.g.error_count > 0 ) {
	    break;
	}

	/* calculate total size of segments */
	for ( curr_written = 0, seg = SymTables[TAB_SEG].head; seg ; seg = seg->next ) {
	    /* v2.04: use <max_offset> instead of <bytes_written>
	     * (the latter is not always reliable due to backpatching).
	     */
	    curr_written += seg->sym.max_offset;
	}

	/* if there's no phase error and size of segments didn't change, we're done */
	if( !ModuleInfo.PhaseError && prev_written == curr_written )
	    break;

	prev_written = curr_written;

	if ( Parse_Pass % 200 == 199 )
	    asmerr( 3000, Parse_Pass+1 );

	if ( Options.line_numbers ) {
	    if ( Options.output_format == OFORMAT_COFF ) {
		for( seg = SymTables[TAB_SEG].head; seg; seg = seg->next ) {
		    if ( seg->e.seginfo->LinnumQueue )
			QueueDeleteLinnum( seg->e.seginfo->LinnumQueue );
		    seg->e.seginfo->LinnumQueue = NULL;
		}
	    } else {
		QueueDeleteLinnum( &LinnumQueue );
		LinnumQueue.head = NULL;
	    }
	}

	/* set file position of ASM and LST files for next pass */

	rewind( CurrFile[ASM] );
	if ( write_to_file && Options.output_format == OFORMAT_OMF )
	    omf_set_filepos();

	if ( UseSavedState == FALSE && CurrFile[LST] ) {
	    rewind( CurrFile[LST] );
	    LstInit();
	}
    } /* end for() */

    if ( ( Parse_Pass > PASS_1 ) && write_to_file )
	WriteModule( &ModuleInfo );

    /* Write a symbol listing file (if requested) */
    LstWriteCRef();

done:
    AssembleFini();
    return( ModuleInfo.g.error_count == 0 );
}
