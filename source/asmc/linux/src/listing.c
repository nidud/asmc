/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	listing support
*
****************************************************************************/

#include <stdarg.h>

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <reswords.h>
#include <segment.h>
#include <tokenize.h>
#include <macro.h>
#include <fastpass.h>
#include <listing.h>
#include <input.h>
#include <types.h>
#include <omfspec.h>

#define CODEBYTES 9
#define OFSSIZE 8
#define PREFFMTSTR "20" /* v2.24 -- memory error: johnsa */
#define USELSLINE 1	/* also in assemble.c! */

#ifdef __UNIX__
#define NLSIZ 1
#define NLSTR "\n"
#else
#define NLSIZ 2
#define NLSTR "\r\n"
#endif

extern int_32  LastCodeBufSize;
extern enum special_token basereg[];
extern char cp_logo[];

uint_32 list_pos; /* current pos in LST file */

#define DOTSMAX 32
static const char  dots[] = " . . . . . . . . . . . . . . . .";

static const char  szFmtProcStk[] = "  %s %s        %-17s %s %c %04" I32_SPEC "X";

enum list_strings {
#define ltext( index, string ) LS_ ## index,
#include <ltext.h>
#undef ltext
};

static const char * const strings[] = {
#define ltext( index, string ) string ,
#include <ltext.h>
#undef ltext
};

static const char szCount[] = "count";

/* cref definitions */

enum list_queues {
    LQ_MACROS,
    LQ_STRUCTS,
    LQ_RECORDS,
    LQ_TYPEDEFS,
    LQ_SEGS,
    LQ_GRPS,
    LQ_PROCS,
    LQ_LAST
};

enum pr_flags {
    PRF_ADDSEG = 0x01
};

struct print_item {
    short type;
    short flags;
    const short *capitems;
    void (*function)();
};


static const short maccap[] = { LS_TXT_MACROS,	LS_TXT_MACROCAP	 ,0 };
static const short strcap[] = { LS_TXT_STRUCTS, LS_TXT_STRUCTCAP, 0 };
static const short reccap[] = { LS_TXT_RECORDS, LS_TXT_RECORDCAP, 0 };
static const short tdcap[]  = { LS_TXT_TYPEDEFS,LS_TXT_TYPEDEFCAP, 0 };
static const short segcap[] = { LS_TXT_SEGS,	LS_TXT_SEGCAP, 0 };
static const short prccap[] = { LS_TXT_PROCS,	LS_TXT_PROCCAP, 0 };

static void log_macro(	 const struct asym * );
static void log_struct(	 const struct asym *, const char *name, int_32 );
static void log_record(	 const struct asym * );
static void log_typedef( const struct asym * );
static void log_segment( const struct asym *, const struct asym *group );
static void log_group(	 const struct asym *, const struct dsym * );
static void log_proc(	 const struct asym * );

static const struct print_item cr[] = {
    { LQ_MACROS,	  0, maccap, log_macro	 },
    { LQ_STRUCTS,	  0, strcap, log_struct	 },
    { LQ_RECORDS,	  0, reccap, log_record	 },
    { LQ_TYPEDEFS,	  0, tdcap,  log_typedef },
    { LQ_SEGS,		  0, segcap, log_segment },
    { LQ_GRPS,	 PRF_ADDSEG, NULL,   log_group	 },
    { LQ_PROCS,		  0, prccap, log_proc	 },
};

struct lstleft {
    struct lstleft *next;
    char buffer[4*8];
    char last;
};

/* write a source line to the listing file
 * global variables used inside:
 *  CurrSource:	   the - expanded - source line
 *  CurrSeg:	   current segment
 *  GeneratedCode: flag if code is generated
 *  MacroLevel:	   macro depth
 *
 */

void LstWrite( enum lsttype type, uint_32 oldofs, void *value )
{
    uint_32 newofs;
    struct asym *sym = value;
    int	    len;
    int	    len2;
    int	    idx;
    int	    srcfile;
    char    *p1;
    char    *p2;
    char    *pSrcline;
    struct lstleft *pll;
    struct lstleft ll;

    if ( ModuleInfo.list == FALSE || CurrFile[LST] == NULL || ( ModuleInfo.line_flags & LOF_LISTED ) )
	return;
    if ( ModuleInfo.GeneratedCode && ( ModuleInfo.list_generated_code == FALSE ) )
	return;
    if ( MacroLevel ) {
	switch ( ModuleInfo.list_macro ) {
	case LM_NOLISTMACRO:
	    return;
	case LM_LISTMACRO:
	    /* todo: filter certain macro lines */
	    break;
	}
    }

    ModuleInfo.line_flags |= LOF_LISTED;

    pSrcline = CurrSource;
    if ( ( Parse_Pass > PASS_1 ) && UseSavedState ) {
	if ( ModuleInfo.GeneratedCode == 0 ) {
	    if ( !( ModuleInfo.line_flags & LOF_SKIPPOS ) )
	       list_pos = LineStoreCurr->list_pos;
#if USELSLINE /* either use CurrSource + CurrComment or LineStoreCurr->line (see assemble.c, OnePass() */
	    pSrcline = LineStoreCurr->line;
	    if ( ModuleInfo.CurrComment ) { /* if comment was removed, readd it! */
		*( LineStoreCurr->line + strlen( LineStoreCurr->line ) ) = ';';
		ModuleInfo.CurrComment = NULL;
	    }
#endif
	}
	fseek( CurrFile[LST], list_pos, SEEK_SET );

    }

    ll.next = NULL;
    memset( ll.buffer, ' ', sizeof( ll.buffer ) );
    srcfile = get_curr_srcfile();

    switch ( type ) {
    case LSTTYPE_DATA:
	if ( Parse_Pass == PASS_1 && Options.first_pass_listing == FALSE ) {
	    break;
	}
	/* no break */
    case LSTTYPE_CODE:
	newofs = GetCurrOffset();
	sprintf( ll.buffer, "%08" I32_SPEC "X", oldofs );
	ll.buffer[OFSSIZE] = ' ';

	if ( CurrSeg == NULL )
	    break;
	//if ( write_to_file == FALSE )
	if ( Options.first_pass_listing ) {
	    if ( Parse_Pass > PASS_1 )
		break;
	} else if ( Parse_Pass == PASS_1 )  /* changed v1.96 */
	    break;

	len = CODEBYTES;
	p2 = ll.buffer + OFSSIZE + 2;

	if ( CurrSeg->e.seginfo->CodeBuffer == NULL ||
	    CurrSeg->e.seginfo->written == FALSE ) {
	    while ( oldofs < newofs && len ) {
		*p2++ = '0';
		*p2++ = '0';
		oldofs++;
		len--;
	    }
	    break;
	}

	/* OMF hold just a small buffer for one LEDATA record */
	/* if it has been flushed, use LastCodeBufSize */
	idx = (CurrSeg->e.seginfo->current_loc - CurrSeg->e.seginfo->start_loc)
	    - (newofs - oldofs);
	if ( Options.output_format == OFORMAT_OMF ) {
	    /* v2.11: additional check to make the hack more robust [ test case:  db 800000h dup (0) ] */
	    if ( ( idx+LastCodeBufSize ) < 0 )
		break; /* just exit. The code bytes area will remain empty */
	    while ( idx < 0 && len ) {
		sprintf( p2, "%02X", CurrSeg->e.seginfo->CodeBuffer[idx+LastCodeBufSize] );
		p2 += 2;
		idx++;
		oldofs++;
		len--;
	    }
	} else if (idx < 0)
	    idx = 0;

	while ( oldofs < newofs && len ) {
	    sprintf( p2, "%02X", CurrSeg->e.seginfo->CodeBuffer[idx] );
	    p2 += 2;
	    idx++;
	    oldofs++;
	    len--;
	}
	*p2 = ' ';
	break;
    case LSTTYPE_EQUATE:
	/* v2.10: display current offset if equate is an alias for a label in this segment */
	idx = 1;
	if ( sym->segment && sym->segment == &CurrSeg->sym ) {
	    sprintf( ll.buffer, "%08" I32_SPEC "X", GetCurrOffset() );
	    idx = 10;
	}
	ll.buffer[idx] = '=';
	if ( sym->value3264 != 0 && ( sym->value3264 != -1 || sym->value >= 0 ) )
	    sprintf( &ll.buffer[idx+2], "%-" PREFFMTSTR I64_SPEC "X", (uint_64)sym->value + ( (uint_64)sym->value3264 << 32 ) );
	else
	    sprintf( &ll.buffer[idx+2], "%-" PREFFMTSTR I32_SPEC "X", sym->value );
	ll.buffer[idx+22] = ' '; /* v2.25 - binary zero fix -- John Hankinson */
	break;
    case LSTTYPE_TMACRO:
	ll.buffer[1] = '=';
	for ( p1 = sym->string_ptr, p2 = &ll.buffer[3], pll = &ll; *p1; ) {
	    if ( p2 >= &pll->buffer[28] ) {
		struct lstleft *next = myalloca( sizeof( struct lstleft ) );
		pll->next = next;
		pll = next;
		pll->next = NULL;
		memset( pll->buffer, ' ', sizeof( pll->buffer) );
		p2 = &pll->buffer[3];
	    }
	    *p2++ = *p1++;
	}
	break;
    case LSTTYPE_MACROLINE:
	ll.buffer[1] = '>';
	pSrcline = value;
	break;
    case LSTTYPE_LABEL:
	oldofs = GetCurrOffset();
	/* no break */
    case LSTTYPE_STRUCT:
	sprintf( ll.buffer, "%08" I32_SPEC "X", oldofs );
	ll.buffer[8] = ' ';
	break;
    case LSTTYPE_DIRECTIVE:
	if ( CurrSeg || value ) {
	    sprintf( ll.buffer, "%08" I32_SPEC "X", oldofs );
	    ll.buffer[8] = ' ';
	}
	break;
    default: /* LSTTYPE_MACRO */
	if ( *pSrcline == NULLC && ModuleInfo.CurrComment == NULL && srcfile == ModuleInfo.srcfile ) {
	    fwrite( NLSTR, 1, NLSIZ, CurrFile[LST] );
	    list_pos += NLSIZ;
	    return;
	}
	break;
    }

    if ( Parse_Pass == PASS_1 || UseSavedState == FALSE ) {
	idx = sizeof( ll.buffer );
	if ( ModuleInfo.GeneratedCode )
	    ll.buffer[28] = '*';
	if ( MacroLevel ) {
	    len = sprintf( &ll.buffer[29], "%u", MacroLevel );
	    ll.buffer[29+len] = ' ';
	}
	if ( srcfile != ModuleInfo.srcfile ) {
	    ll.buffer[30] = 'C';
	}
    } else {
	idx = OFSSIZE + 2 + 2 * CODEBYTES;
    }
    fwrite( ll.buffer, 1, idx, CurrFile[LST] );

    len = strlen( pSrcline );
    len2 = ( ModuleInfo.CurrComment ? strlen( ModuleInfo.CurrComment ) : 0 );

    list_pos += sizeof( ll.buffer ) + len + len2 + NLSIZ;
    /* write source and comment part */
    if ( Parse_Pass == PASS_1 || UseSavedState == FALSE ) {
	if ( len )
	    fwrite( pSrcline, 1, len, CurrFile[LST] );
	if ( len2 ) {
	    fwrite( ModuleInfo.CurrComment, 1, len2, CurrFile[LST] );
	}
	fwrite( NLSTR, 1, NLSIZ, CurrFile[LST] );
    }

    /* write optional additional lines.
     * currently works in pass one only.
     */
    for ( pll = ll.next; pll; pll = pll->next ) {
	fwrite( pll->buffer, 1, 32, CurrFile[LST] );
	fwrite( NLSTR, 1, NLSIZ, CurrFile[LST] );
	list_pos += 32 + NLSIZ;
    }
    return;
}

void LstWriteSrcLine( void )
{
    LstWrite( LSTTYPE_MACRO, 0, NULL );
}

void LstPrintf( const char *format, ... )
{
    va_list	args;

    if( CurrFile[LST] ) {
	va_start( args, format );
	list_pos += vfprintf( CurrFile[LST], format, args );
	va_end( args );
    }
}

void LstNL( void )
{
    if( CurrFile[LST] ) {
	fwrite( NLSTR, 1, NLSIZ, CurrFile[LST] );
	list_pos += NLSIZ;
    }
}

/* set the list file's position
 * this is only needed if generated code is to be
 * executed BEFORE the original source line is listed.
 */

void LstSetPosition( void )
{
    if( CurrFile[LST] && ( Parse_Pass > PASS_1 ) && UseSavedState && ModuleInfo.GeneratedCode == 0 ) {
	list_pos = LineStoreCurr->list_pos;
	fseek( CurrFile[LST], list_pos, SEEK_SET );
	ModuleInfo.line_flags |= LOF_SKIPPOS;
    }
}

static const char *get_seg_align( const struct seg_info *seg, char *buffer )
{
    switch( seg->alignment ) {
    case 0:    return( strings[LS_BYTE]	 );
    case 1:    return( strings[LS_WORD]	 );
    case 2:    return( strings[LS_DWORD] );
    case 3:    return( strings[LS_QWORD] );
    case 4:    return( strings[LS_PARA]	 );
    case 8:    return( strings[LS_PAGE]	 );
    case MAX_SEGALIGNMENT:
	       return( strings[LS_ABS]	 );
    default:
	sprintf( buffer, "%u", 1 << seg->alignment );
	return( buffer );
    }
}

static const char *get_seg_combine( const struct seg_info *seg )
{
    switch( seg->combine ) {
    case COMB_INVALID:	  return( strings[LS_PRIVATE] );
    case COMB_STACK:	  return( strings[LS_STACK]   );
    case COMB_ADDOFF:	  return( strings[LS_PUBLIC]  );
    /* v2.06: added */
    case COMB_COMMON:	  return( strings[LS_COMMON]  );
    }
    return( "?" );
}

static void log_macro( const struct asym *sym )
{
    int i = sym->name_size;
    const char *pdots;
    const char *type = (sym->isfunc) ? strings[LS_FUNC] : strings[LS_PROC];

    pdots = ((i >= DOTSMAX) ? "" : dots + i + 1 );
    LstPrintf( "%s %s        %s", sym->name, pdots ,type );
    LstNL();
    return;
}

static const char *SimpleTypeString( unsigned char mem_type )
{
    int size = ( mem_type & MT_SIZE_MASK ) + 1;
    switch ( size ) {
    case 1: return( strings[LS_BYTE] );
    case 2: return( strings[LS_WORD] );
    case 4: return( strings[LS_DWORD] );
    case 6: return( strings[LS_FWORD] );
    case 8: return( strings[LS_QWORD] );
    case 10:return( strings[LS_TBYTE] );
    case 16:return( strings[LS_OWORD] );
    }
    return( "" );
}

/* called by log_struct and log_typedef
 * that is, the symbol is ensured to be a TYPE!
 * argument 'buffer' is either NULL or "very" large ( StringBufferEnd ).
 */

static const char *GetMemtypeString( const struct asym *sym, char *buffer )
{
    const char *p;
    //enum memtype mem_type;
    unsigned char mem_type;

    if ( (sym->mem_type & MT_SPECIAL) == 0 )
	return( SimpleTypeString( sym->mem_type ) );

    /* v2.05: improve display of stack vars */
    mem_type = sym->mem_type;
    if ( sym->state == SYM_STACK && sym->is_ptr )
	mem_type = MT_PTR;

    switch ( mem_type ) {
    case MT_PTR:
	if ( sym->Ofssize == USE64 )
	    p = strings[LS_NEAR];
	else
	    if ( sym->isfar )
		p = strings[LS_FAR16 + sym->Ofssize];
	    else
		p = strings[LS_NEAR16 + sym->Ofssize];

	if ( buffer ) { /* Currently, 'buffer' is only != NULL for typedefs */
	    int i;
	    char *b2 = buffer;
	    /* v2.10: improved pointer TYPEDEF display */
	    for ( i = sym->is_ptr; i; i-- ) {
		b2 += sprintf( b2, "%s %s ", p, strings[LS_PTR] );
	    }
	    /* v2.05: added. */
	    if ( sym->state == SYM_TYPE && sym->typekind == TYPE_TYPEDEF ) {
		//strcat( buffer, " ");
		if ( sym->target_type )
		    strcpy( b2, sym->target_type->name );
		else if ( ( sym->ptr_memtype & MT_SPECIAL ) == 0 )
		    strcpy( b2, SimpleTypeString( sym->ptr_memtype ) );
	    }
	    return( buffer );
	}
	return( p );
    case MT_FAR:
	if ( sym->segment )
	    return( strings[LS_LFAR] );
	return( strings[LS_LFAR16 + GetSymOfssize( sym )] );
    case MT_NEAR:
	if ( sym->segment )
	    return( strings[LS_LNEAR] );
	return( strings[LS_LNEAR16 + GetSymOfssize( sym )] );
    case MT_TYPE:
	if ( *(sym->type->name) )  /* there are a lot of unnamed types */
	    return( sym->type->name );
	return( GetMemtypeString( sym->type, buffer ) );
    case MT_EMPTY: /* number, via EQU or = directive */
	return( strings[LS_NUMBER] );
    }
    return("?");
}

static const char *GetLanguage( const struct asym *sym )
{
    if ( sym->langtype <= LANG_WATCALL )
	return( strings[sym->langtype + LS_VOID] );
    return( "?" );
}

/* display STRUCTs and UNIONs */

static void log_struct( const struct asym *sym, const char *name, int_32 ofs )
{
    unsigned	  i;
    struct dsym	  *dir;
    const char	  *pdots;
    struct struct_info *si;
    struct sfield *f;
    static int	  prefix = 0;

    dir = (struct dsym *)sym;
    si = dir->e.structinfo;

    if ( !name )
	name = sym->name;
    i = strlen ( name );
    pdots = (( (i+prefix) >= DOTSMAX) ? "" : dots + i + prefix + 1 );
    for ( i = 0; i < prefix; i++ )
	LstPrintf(" ");
    if ( prefix == 0 )
	if ( dir->e.structinfo->alignment > 1)
	    LstPrintf( "%s %s        %8" I32_SPEC "X (%u)", name, pdots, sym->total_size, si->alignment );
	else
	    LstPrintf( "%s %s        %8" I32_SPEC "X", name, pdots, sym->total_size );
    else
	LstPrintf( "%s %s        %8" I32_SPEC "X", name, pdots, sym->offset + ofs);
    LstNL();
    prefix += 2;
    for( f = si->head; f; f = f->next ) {
	if ( f->sym.mem_type == MT_TYPE && f->ivalue[0] == NULLC ) {
	    log_struct( f->sym.type, f->sym.name, f->sym.offset + ofs );
	} else {
	    /* don't list unstructured fields without name */
	    /* but do list them if they are structured */
	    if (*(f->sym.name) || (f->sym.mem_type == MT_TYPE)) {
		i = f->sym.name_size + prefix;
		pdots = ((i >= DOTSMAX) ? "" : dots + i + 1 );
		for ( i = 0; i < prefix; i++ )
		    LstPrintf(" ");
		LstPrintf( "%s %s        %8" I32_SPEC "X   ", f->sym.name, pdots, f->sym.offset + sym->offset + ofs);
		LstPrintf( "%s", GetMemtypeString( &f->sym, NULL ) );
		if ( f->sym.isarray )
		    LstPrintf( "[%u]",f->sym.total_length );
		LstNL();
	    }
	}
    }
    prefix -= 2;
}

static void log_record( const struct asym *sym )
{
    uint_64	    mask;
    struct dsym	    *dir = (struct dsym *)sym;
    struct struct_info *si = dir->e.structinfo;
    struct sfield   *f;
    int i = sym->name_size;
    const char *pdots;

    pdots = ((i >= DOTSMAX) ? "" : dots + i + 1 );
    for( i = 0,f = si->head; f; f = f->next,i++ );
    LstPrintf( "%s %s      %6" I32_SPEC "X  %7X", sym->name, pdots, sym->total_size*8, i );
    LstNL();
    for( f = si->head; f; f = f->next ) {
	i = f->sym.name_size + 2;
	pdots = ((i >= DOTSMAX) ? "" : dots + i + 1 );
	for ( i = f->sym.offset, mask = 0; i < f->sym.offset + f->sym.total_size; i++ )
#if defined(LLONG_MAX) || defined(__GNUC__) || defined(__TINYC__)
	    mask |= 1ULL << i;
#else
	    mask |= 1i64 << i;
#endif
	if ( sym->total_size > 4 )
	    LstPrintf( "  %s %s      %6" I32_SPEC "X  %7" I32_SPEC "X  %016" I64_SPEC "X %s", f->sym.name, pdots, f->sym.offset, f->sym.total_size, mask, f->ivalue[0] ? f->ivalue : "?" );
	else
	    LstPrintf( "  %s %s      %6" I32_SPEC "X  %7" I32_SPEC "X  %08" I32_SPEC "X %s", f->sym.name, pdots, f->sym.offset, f->sym.total_size, (uint_32)mask, f->ivalue[0] ? f->ivalue : "?" );
	LstNL();
    }
}

/* a typedef is a simple struct with no fields. Size might be 0. */

static void log_typedef( const struct asym *sym )
{
    char *p;
    int i = sym->name_size;
    const char *pdots;

    pdots = (( i >= DOTSMAX ) ? "" : dots + i + 1 );
    p = StringBufferEnd;
    *p = NULLC;
    if ( sym->mem_type == MT_PROC && sym->target_type ) { /* typedef proto? */
	strcat( p, strings[LS_PROC] );
	strcat( p, " " );
	if ( *sym->target_type->name ) {  /* the name may be "" */
	    strcat( p, sym->target_type->name );
	    strcat( p," ");
	}
	/* v2.11: target_type has state SYM_TYPE (since v2.09).
	 * This state isn't handled properly by GetSymOfsSize(), which is called by GetMemtypeString(),
	 * so get the strings here.
	 */
	strcat( p, strings[( sym->target_type->mem_type == MT_NEAR ? LS_LNEAR16 : LS_LFAR16 ) + sym->Ofssize ] );
	strcat( p," " );
	strcat( p, GetLanguage( sym->target_type ) );
    } else
	p = (char *)GetMemtypeString( sym, p );
    LstPrintf( "%s %s    %8" I32_SPEC "u  %s", sym->name, pdots, sym->total_size, p );
    LstNL();
}

static void log_segment( const struct asym *sym, const struct asym *group )
{
    char buffer[32];
    struct seg_info *seg = ((struct dsym *)sym)->e.seginfo;

    if( seg->group == group ) {
	int i = sym->name_size;
	const char *pdots;
	pdots = (( i >= DOTSMAX ) ? "" : dots + i + 1);
	LstPrintf( "%s %s        ", sym->name, pdots );
	if( seg->Ofssize == USE32 ) {
	    LstPrintf( "32 Bit   %08" I32_SPEC "X ", sym->max_offset );
	} else if( seg->Ofssize == USE64 ) {
	    LstPrintf( "64 Bit   %08" I32_SPEC "X ", sym->max_offset );
	} else {
	    LstPrintf( "16 Bit   %04" I32_SPEC "X     ", sym->max_offset );
	}
	LstPrintf( "%-7s %-8s", get_seg_align( seg, buffer ), get_seg_combine( seg ) );
	LstPrintf( "'%s'", seg->clsym ? seg->clsym->name : "" );
	LstNL();
    }
}

static void log_group( const struct asym *grp, const struct dsym *segs )
{
    unsigned i;
    const char *pdots;
    struct seg_item *curr;

    i = grp->name_size;
    pdots = (( i >= DOTSMAX ) ? "" : dots + i + 1);
    LstPrintf( "%s %s        %s", grp->name, pdots, strings[LS_GROUP] );
    LstNL();

    /* the FLAT groups is always empty */
    if ( grp == (struct asym *)ModuleInfo.flat_grp ) {
	for( ; segs; segs = segs->next ) {
	    log_segment( (struct asym *)segs, grp );
	}
    } else
	for( curr = ((struct dsym *)grp)->e.grpinfo->seglist; curr; curr = curr->next ) {
	    log_segment( (struct asym *)curr->seg, grp );
	}
}

static const char *get_proc_type( const struct asym *sym )
{
    /* if there's no segment associated with the symbol,
     add the symbol's offset size to the distance */
    switch( sym->mem_type ) {
    case MT_NEAR:
	if ( sym->segment == NULL ) {
	    return( strings[LS_NEAR16 + GetSymOfssize( sym )] );
	}
	return( strings[LS_NEAR] );
    case MT_FAR:
	if ( sym->segment == NULL ) {
	    return( strings[LS_FAR16 + GetSymOfssize( sym )] );
	}
	return( strings[LS_FAR] );
    }
    return( " " );
}

static const char *get_sym_seg_name( const struct asym *sym )
{
    if( sym->segment ) {
	return( sym->segment->name );
    } else {
	return( strings[LS_NOSEG] );
    }
}

/* list Procedures and Prototypes */

static void log_proc( const struct asym *sym )
{
    struct dsym *f;
    struct dsym *l;
    const char *p;
    struct dsym *dir = (struct dsym *)sym;
    int i = sym->name_size;
    char Ofssize = GetSymOfssize( sym );
    const char *pdots;

    pdots = (( i >= DOTSMAX ) ? "" : dots + i + 1 );
    if ( Ofssize )
	p = "%s %s        P %-6s %08" I32_SPEC "X %-8s ";
    else
	p = "%s %s        P %-6s %04" I32_SPEC "X     %-8s ";
    LstPrintf( p,
	      sym->name,
	      pdots,
	      get_proc_type( sym ),
	      sym->offset,
	      get_sym_seg_name( sym ));

    /* externals (PROTO) don't have a size. Masm always prints 0000 or 00000000 */
    LstPrintf( "%0*" I32_SPEC "X ", Ofssize > USE16 ? 8 : 4, sym->state == SYM_INTERNAL ? sym->total_size : 0 );

    if( sym->ispublic ) {
	LstPrintf( "%-9s", strings[LS_PUBLIC] );
    } else if ( sym->state == SYM_INTERNAL ) {
	LstPrintf( "%-9s", strings[LS_PRIVATE] );
    } else {
	LstPrintf( sym->weak ? "*%-8s " : "%-9s ", strings[LS_EXTERNAL] );
	if ( sym->dll )
	    LstPrintf( "(%.8s) ", sym->dll->name );
    }

    LstPrintf( "%s", GetLanguage( sym ) );
    LstNL();
    /* for PROTOs, list optional altname */
    if ( sym->state == SYM_EXTERNAL && sym->altname ) {
	struct asym *sym2 = sym->altname;
	LstPrintf( "  ");
	LstPrintf( p,
		  sym2->name,
		  pdots+2,
		  get_proc_type( sym2 ),
		  sym2->offset,
		  get_sym_seg_name( sym2 ));
	LstNL();
    }
    /* for PROCs, list parameters and locals */
    if ( sym->state == SYM_INTERNAL ) {

	/* print the procedure's parameters */

	if ( sym->langtype == LANG_STDCALL || sym->langtype == LANG_C ||
	     sym->langtype == LANG_SYSCALL || sym->langtype == LANG_VECTORCALL ||
	     ( sym->langtype == LANG_FASTCALL && ModuleInfo.Ofssize != USE16 ) ) {

	    int cnt;
	    /* position f2 to last param */
	    for ( cnt = 0, f = dir->e.procinfo->paralist; f; f = f->nextparam )
		cnt++;
	    for ( ; cnt; cnt-- ) {
		int curr;
		for ( curr = 1,f = dir->e.procinfo->paralist; curr < cnt;f = f->nextparam, curr++ );
		i = f->sym.name_size;
		pdots = (( i >= DOTSMAX-2 ) ? "" : dots + i + 1 + 2 );
		/* FASTCALL: parameter may be a text macro (=register name) */
		if ( f->sym.state == SYM_TMACRO )
		    LstPrintf( "  %s %s        %-17s %s", f->sym.name, pdots, GetMemtypeString( &f->sym, NULL ), f->sym.string_ptr );
		else
		    LstPrintf( szFmtProcStk, f->sym.name, pdots,
			    f->sym.is_vararg ? strings[LS_VARARG] : GetMemtypeString( &f->sym, NULL ),
			      GetResWName( dir->e.procinfo->basereg, NULL ), '+', f->sym.offset );
		LstNL();
	    }
	} else {
	    for ( f = dir->e.procinfo->paralist; f; f = f->nextparam ) {
		i = f->sym.name_size;
		pdots = (( i >= DOTSMAX-2 ) ? "" : dots + i + 1 + 2 );
		LstPrintf( szFmtProcStk, f->sym.name, pdots, GetMemtypeString( &f->sym, NULL ),
			  GetResWName( dir->e.procinfo->basereg, NULL ), '+', f->sym.offset );
		LstNL();
	    }
	}

	/* print the procedure's locals */
	for ( l = dir->e.procinfo->locallist; l; l = l->nextlocal ) {
	    char buffer[32];
	    i = l->sym.name_size;
	    pdots = (( i >= DOTSMAX-2 ) ? "" : dots + i + 1 + 2);
	    if ( l->sym.isarray )
		sprintf( buffer, "%s[%" I32_SPEC "u]", GetMemtypeString(&l->sym, NULL), l->sym.total_length );
	    else
		strcpy( buffer, GetMemtypeString( &l->sym, NULL ) );
	    LstPrintf( szFmtProcStk, l->sym.name, pdots, buffer,
		      GetResWName( dir->e.procinfo->basereg, NULL ),
		      l->sym.offset >= 0 ? '+' : '-', l->sym.offset >= 0 ? l->sym.offset : - l->sym.offset );
	    LstNL();
	}

	for ( l = dir->e.procinfo->labellist; l ; l = l->e.nextll ) {
	    struct dsym *l2;
	    for ( l2 = l; l2; l2 = (struct dsym *)l2->sym.nextitem ) {
		/* filter params and locals! */
		if ( l2->sym.state == SYM_STACK || l2->sym.state == SYM_TMACRO )
		    continue;
		i = l2->sym.name_size;
		pdots = (( i >= DOTSMAX-2 ) ? "" : dots + i + 1 + 2);
		if ( Ofssize )
		    p = "  %s %s        L %-6s %08" I32_SPEC "X %s";
		else
		    p = "  %s %s        L %-6s %04" I32_SPEC "X     %s";
		LstPrintf( p,
			  l2->sym.name,
			  pdots,
			  get_proc_type( &l2->sym ),
			  l2->sym.offset,
			  get_sym_seg_name( &l2->sym ));
		LstNL();
	    }
	}
    }
}

/* list symbols */

static void log_symbol( const struct asym *sym )
{
    int i = sym->name_size;
    const char *pdots;

    pdots = ((i >= DOTSMAX) ? "" : dots + i + 1 );

    switch ( sym->state ) {
    case SYM_UNDEFINED:
    case SYM_INTERNAL:
    case SYM_EXTERNAL:
	LstPrintf( "%s %s        ", sym->name, pdots );

	if ( sym->isarray ) {
	    i = sprintf( StringBufferEnd, "%s[%u]", GetMemtypeString( sym, NULL ), sym->total_length );
	    LstPrintf( "%-10s ", StringBufferEnd );
	} else if ( sym->state == SYM_EXTERNAL && sym->iscomm == TRUE ) {
	    LstPrintf( "%-10s ", strings[LS_COMM] );
	} else
	    LstPrintf( "%-10s ", GetMemtypeString( sym, NULL ) );

	/* print value */
	if ( sym->state == SYM_EXTERNAL && sym->iscomm == TRUE )
	    LstPrintf( " %8" I32_SPEC "Xh ", sym->total_size / sym->total_length );
	else if ( sym->mem_type == MT_EMPTY ) { /* also check segment? might be != NULL for equates (var = offset x) */
	    if ( sym->value3264 != 0 && sym->value3264 != -1 )
		LstPrintf( " %" I64_SPEC "Xh ", sym->uvalue, sym->value3264 );
	    else if ( sym->value3264 < 0 )
		LstPrintf( "-%08" I32_SPEC "Xh ", 0 - sym->uvalue );
	    else
		LstPrintf( " %8" I32_SPEC "Xh ", sym->offset );
	} else
	    LstPrintf( " %8" I32_SPEC "Xh ", sym->offset );

	/* print segment */
	if ( sym->segment )
	    LstPrintf( "%s ", get_sym_seg_name( sym ) );

	if ( sym->state == SYM_EXTERNAL && sym->iscomm == TRUE )
	    LstPrintf( "%s=%u ", szCount, sym->total_length );

	if( sym->ispublic )
	    LstPrintf( "%s ", strings[LS_PUBLIC] );

	if ( sym->state == SYM_EXTERNAL ) {
	    LstPrintf( sym->weak ? "*%s " : "%s ", strings[LS_EXTERNAL] );
	} else if ( sym->state == SYM_UNDEFINED ) {
	    LstPrintf( "%s ", strings[LS_UNDEFINED] );
	}

	LstPrintf( "%s", GetLanguage( sym ) );
	LstNL();
	break;
    case SYM_TMACRO:
	LstPrintf( "%s %s        %s   %s", sym->name, pdots, strings[LS_TEXT], sym->string_ptr );
	LstNL();
	break;
    case SYM_ALIAS:
	LstPrintf( "%s %s        %s  %s", sym->name, pdots, strings[LS_ALIAS], sym->substitute->name );
	LstNL();
	break;
    }
}

static void LstCaption( const char *caption, int prefNL )
{
    for (; prefNL; prefNL--)
	LstNL();
    LstPrintf( caption );
    LstNL();
    LstNL();
}

static int compare_syms( const void *p1, const void *p2 )
{
    return( strcmp( (*(struct asym * *)p1)->name, (*(struct asym * *)p2)->name ) );
}

/* write symbol table listing */

void LstWriteCRef( void )
{
    struct asym	    **syms;
    struct dsym	    *dir;
    struct struct_info *si;
    int		    idx;
    uint_32	    i;
    uint_32	    SymCount;
    struct qdesc    queues[LQ_LAST];

    /* no point going through the motions if lst file isn't open */
    if( CurrFile[LST] == NULL || Options.no_symbol_listing == TRUE ) {
	return;
    }

    /* go to EOF */
    fseek( CurrFile[LST], 0, SEEK_END );

    SymCount = SymGetCount();
    syms = (struct asym **)MemAlloc( SymCount * sizeof( struct asym * ) );
    SymGetAll( syms );

    /* sort 'em */
    qsort( syms, SymCount, sizeof( struct asym * ), compare_syms );

    memset( queues, 0, sizeof( queues ) );
    for( i = 0; i < SymCount; ++i ) {
	struct qdesc *q;
	if ( syms[i]->list == FALSE )
	    continue;
	switch (syms[i]->state) {
	case SYM_TYPE:
	    si = ((struct dsym *)syms[i])->e.structinfo;
	    switch ( syms[i]->typekind ) {
	    case TYPE_RECORD:  idx = LQ_RECORDS; break;
	    case TYPE_TYPEDEF: idx = LQ_TYPEDEFS;break;
	    case TYPE_STRUCT:
	    case TYPE_UNION:   idx = LQ_STRUCTS ;break;
#ifdef DEBUG_OUT
	    default:	       idx = LQ_UNDEF_TYPES ;break;
#else
	    default: continue; /* skip "undefined" types */
#endif
	    }
	    break;
	case SYM_MACRO:
	    idx = LQ_MACROS;
	    break;
	case SYM_SEG:
	    idx = LQ_SEGS;
	    break;
	case SYM_GRP:
	    idx = LQ_GRPS;
	    break;
	case SYM_INTERNAL:
	case SYM_EXTERNAL: /* v2.04: added, since PROTOs are now externals */
	    if ( syms[i]->isproc ) {
		idx = LQ_PROCS;
		break;
	    }
	    /* no break */
	default:
	    continue;
	}
	q = &queues[idx];
	if( q->head == NULL ) {
	    q->head = syms[i];
	} else {
	    ((struct dsym *)q->tail)->next = (struct dsym *)syms[i];
	}
	q->tail = syms[i];
	((struct dsym *)syms[i])->next = NULL;
    }
    for ( idx = 0; idx < ( sizeof( cr ) / sizeof(cr[0] ) ); idx++ ) {
	if ( queues[cr[idx].type].head ) {
	    if ( cr[idx].capitems ) {
		const short *ps;
		for ( ps = cr[idx].capitems; *ps; ps++ ) {
			LstCaption( strings[ *ps ], ps == cr[idx].capitems ? 2 : 0 );
		}
	    }
	    for( dir = queues[cr[idx].type].head; dir ; dir = dir->next ) {
		cr[idx].function( &dir->sym, ( cr[idx].flags & PRF_ADDSEG ) ? queues[LQ_SEGS].head : NULL, 0 );
	    }
	}
    }

    /* write out symbols */
    LstCaption( strings[ LS_TXT_SYMBOLS ], 2 );
    LstCaption( strings[ LS_TXT_SYMCAP ], 0 );
    for( i = 0; i < SymCount; ++i ) {
	if ( syms[i]->list == TRUE && syms[i]->isproc == FALSE ) {
	    log_symbol( syms[i] );
	}
    }
    LstNL();

    /* free the sorted symbols */
    MemFree( syms );
}

/* .[NO|X]LIST, .[NO|X]CREF, .LISTALL,
 * .[NO]LISTIF, .[LF|SF|TF]COND,
 * PAGE, TITLE, SUBTITLE, SUBTTL directives
 */

int ListingDirective( int i, struct asm_tok tokenarray[] )
{
    int directive = tokenarray[i].tokval;
    i++;

    switch ( directive ) {
    case T_DOT_LIST:
	if ( CurrFile[LST] )
	    ModuleInfo.list = TRUE;
	break;
    case T_DOT_CREF:
	ModuleInfo.cref = TRUE;
	break;
    case T_DOT_NOLIST:
    case T_DOT_XLIST:
	ModuleInfo.list = FALSE;
	break;
    case T_DOT_NOCREF:
    case T_DOT_XCREF:
	if ( i == Token_Count ) {
	    ModuleInfo.cref = FALSE;
	    break;
	}
	do {
	    struct asym *sym;
	    if ( tokenarray[i].token != T_ID ) {
		return( asmerr(2008, tokenarray[i].tokpos ) );
	    }
	    /* the name may be a forward reference. In this case it will
	     * be created here.
	     * v2.11: function call cannot fail. no need for checks.
	     */
	    sym = SymLookup( tokenarray[i].string_ptr );
	    sym->list = FALSE;
	    i++;
	    if ( i < Token_Count ) {
		if ( tokenarray[i].token != T_COMMA )
		    return( asmerr( 2008, tokenarray[i].tokpos ) );

		/* if there's nothing after the comma, don't increment */
		if ( i < ( Token_Count - 1 ) )
		    i++;
	    }
	} while ( i < Token_Count );
	break;
    case T_DOT_LISTALL: /* list false conditionals and generated code */
	if ( CurrFile[LST] )
	    ModuleInfo.list = TRUE;
	ModuleInfo.list_generated_code = TRUE;
	/* fall through */
    case T_DOT_LISTIF:
    case T_DOT_LFCOND: /* .LFCOND is synonym for .LISTIF */
	ModuleInfo.listif = TRUE;
	break;
    case T_DOT_NOLISTIF:
    case T_DOT_SFCOND: /* .SFCOND is synonym for .NOLISTIF */
	ModuleInfo.listif = FALSE;
	break;
    case T_DOT_TFCOND: /* .TFCOND toggles .LFCOND, .SFCOND */
	ModuleInfo.listif = !ModuleInfo.listif;
	break;
    case T_DOT_PAGE:
    default: /* TITLE, SUBTITLE, SUBTTL */
	/* tiny checks to ensure that these directives
	 aren't used as code labels or struct fields */
	if ( tokenarray[i].token == T_COLON )
	    break;
	/* this isn't really Masm-compatible, but ensures we don't get
	 * struct fields with names page, title, subtitle, subttl.
	 */
	if( CurrStruct ) {
	    return( asmerr( 2037 ) );
	}
	if ( Parse_Pass == PASS_1 )
	    asmerr( 7005, tokenarray[i-1].string_ptr );
	while ( tokenarray[i].token != T_FINAL) i++;
    }

    if ( tokenarray[i].token != T_FINAL ) {
	return( asmerr(2008, tokenarray[i].string_ptr ) );
    }

    return( NOT_ERROR );
}

/* directives .[NO]LISTMACRO, .LISTMACROALL, .[X|L|S]ALL */

int ListMacroDirective( int i, struct asm_tok tokenarray[] )
{
    if ( tokenarray[i+1].token != T_FINAL ) {
	return( asmerr(2008, tokenarray[i+1].string_ptr ) );
    }

    ModuleInfo.list_macro = GetSflagsSp( tokenarray[i].tokval );

    return( NOT_ERROR );
}

void LstInit( void )
{
    const char *fn;

    list_pos = 0;
    if( Options.write_listing ) {
	int namelen;
	list_pos = strlen( cp_logo );
	fwrite( cp_logo, 1, list_pos, CurrFile[LST] );
	LstNL();
	fn = GetFName( ModuleInfo.srcfile );
	namelen = strlen( fn );
	fwrite( fn, 1, namelen, CurrFile[LST] );
	list_pos += namelen;
	LstNL();
    }
}
