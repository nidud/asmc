/****************************************************************************
*
*			     Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:	symbol table access
*
****************************************************************************/

#include <time.h>

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "segment.h"
#include "extern.h"
#include "fixup.h"
#include "fastpass.h"
#include "macro.h"
#include "types.h"
#include "proc.h"
#include "input.h"

#if defined(__WATCOMC__) && !defined(__FLAT__)
#define HASH_MAGNITUDE 12  /* for 16bit model */
#else
#define HASH_MAGNITUDE 15  /* is 15 since v1.94, previously 12 */
#endif

/* size of global hash table for symbol table searches. This affects
 * assembly speed.
 */
#if HASH_MAGNITUDE==12
#define GHASH_TABLE_SIZE 2003
#else
#define GHASH_TABLE_SIZE 8192
#endif

/* size of local hash table */
#define LHASH_TABLE_SIZE 128

/* use memcpy()/memcmpi() directly?
 * this may speed-up things, but not with OW.
 * MSVC is a bit faster then.
 */
#define USEFIXSYMCMP 0 /* 1=don't use a function pointer for string compare */
#define USESTRFTIME 0 /* 1=use strftime() */

#if USEFIXSYMCMP
#define SYMCMP( x, y, z ) ( ModuleInfo.case_sensitive ? memcmp( x, y, z ) : _memicmp( x, y, z ) )
#else
#define SYMCMP( x, y, z ) SymCmpFunc( x, y, z )
#endif

extern struct asym *FileCur;  /* @FileCur symbol    */
extern struct asym *LineCur;  /* @Line symbol	    */
extern struct asym *symCurSeg;/* @CurSeg symbol	    */

extern void   UpdateLineNumber( struct asym *, void * );
extern void   UpdateWordSize( struct asym *, void * );
extern void   UpdateCurPC( struct asym *sym, void *p );

static struct asym   *gsym_table[ GHASH_TABLE_SIZE ];
static struct asym   *lsym_table[ LHASH_TABLE_SIZE ];

StrCmpFunc SymCmpFunc;

static struct asym   **gsym;	  /* pointer into global hash table */
static struct asym   **lsym;	  /* pointer into local hash table */
static unsigned	     SymCount;	  /* Number of symbols in global table */
static char	     szDate[12];  /* value of @Date symbol */
static char	     szTime[12];  /* value of @Time symbol */

#if USESTRFTIME
#if defined(__WATCOMC__) || defined(__UNIX__) || defined(__CYGWIN__) || defined(__DJGPP__)
static const char szDateFmt[] = "%D"; /* POSIX date (mm/dd/yy) */
static const char szTimeFmt[] = "%T"; /* POSIX time (HH:MM:SS) */
#else
/* v2.04: MS VC won't understand POSIX formats */
static const char szDateFmt[] = "%x"; /* locale's date */
static const char szTimeFmt[] = "%X"; /* locale's time */
#endif
#endif

static struct asym *symPC; /* the $ symbol */

struct tmitem {
    const char *name;
    char *value;
    struct asym **store;
};

/* table of predefined text macros */
static const struct tmitem tmtab[] = {
    /* @Version contains the Masm compatible version */
    /* v2.06: value of @Version changed to 800 */
    {"@Version",  "800", NULL },
    {"@Date",	  szDate, NULL },
    {"@Time",	  szTime, NULL },
    {"@FileName", ModuleInfo.name, NULL },
    {"@FileCur",  NULL, &FileCur },
    /* v2.09: @CurSeg value is never set if no segment is ever opened.
     * this may have caused an access error if a listing was written.
     */
    {"@CurSeg",	  "", &symCurSeg }
};

struct eqitem {
    const char *name;
    uint_32 value;
    void (* sfunc_ptr)( struct asym *, void * );
    struct asym **store;
};

/* table of predefined numeric equates */
static const struct eqitem eqtab[] = {
    { "__ASMC__",  226, NULL, NULL },
    { "__JWASM__", 212, NULL, NULL },
    { "$",	   0, UpdateCurPC, &symPC },
    { "@Line",	   0, UpdateLineNumber, &LineCur },
    { "@WordSize", 0, UpdateWordSize, NULL }, /* must be last (see SymInit()) */
};


#define _MAX_DYNEQ 10

static int dyneqcount = 0;
static int dyneqvalue[_MAX_DYNEQ];
static char *dyneqtable[_MAX_DYNEQ];

void define_name(char *name, int value)
{
	dyneqvalue[dyneqcount] = value;
	dyneqtable[dyneqcount] = name;
	dyneqcount++;
}

static unsigned int hashpjw( const char *s )
{
    unsigned h;
    unsigned g;

#if HASH_MAGNITUDE==12
    for( h = 0; *s; ++s ) {
	h = (h << 4) + (*s | ' ');
	g = h & ~0x0fff;
	h ^= g;
	h ^= g >> 12;
    }
#else
    for( h = 0; *s; ++s ) {
	h = (h << 5) + (*s | ' ');
	g = h & ~0x7fff;
	h ^= g;
	h ^= g >> 15;
    }
#endif
    return( h );
}

void SymSetCmpFunc( void )
/************************/
{
    SymCmpFunc = ( ModuleInfo.case_sensitive == TRUE ? memcmp : (StrCmpFunc)_memicmp );
    return;
}

/* reset local hash table */

void SymClearLocal( void )
/************************/
{
    memset( &lsym_table, 0, sizeof( lsym_table ) );
    return;
}

/* store local hash table in proc's list of local symbols */

void SymGetLocal( struct asym *proc )
/***********************************/
{
    int i;
    struct dsym	 **l = &((struct dsym *)proc)->e.procinfo->labellist;

    for ( i = 0; i < LHASH_TABLE_SIZE; i++ ) {
	if ( lsym_table[i] ) {
	    *l = (struct dsym *)lsym_table[i];
	    l = &(*l)->e.nextll;
	}
    }
    *l = NULL;

    return;
}

/* restore local hash table.
 * - proc: procedure which will become active.
 * fixme: It might be necessary to reset the "defined" flag
 * for local labels (not for params and locals!). Low priority!
 */

void SymSetLocal( struct asym *proc )
/***********************************/
{
    int i;
    struct dsym *l;

    SymClearLocal();
    for ( l = ((struct dsym *)proc)->e.procinfo->labellist; l; l = l->e.nextll ) {
	i = hashpjw( l->sym.name ) & ( LHASH_TABLE_SIZE - 1 );
	lsym_table[i] = &l->sym;
    }
    return;
}

struct asym *SymAlloc( const char *name )
/***************************************/
{
    int len = strlen( name );
    struct asym *sym;

    sym = LclAlloc( sizeof( struct dsym ) );
    memset( sym, 0, sizeof( struct dsym ) );
#if 1
    /* the tokenizer ensures that identifiers are within limits, so
     * this check probably is redundant */
    if( len > MAX_ID_LEN ) {
	//EmitError( IDENTIFIER_TOO_LONG );
	len = MAX_ID_LEN;
    }
#endif
    sym->name_size = len;
    sym->list = ModuleInfo.cref;
    sym->mem_type = MT_EMPTY;
    if ( len ) {
	sym->name = LclAlloc( len + 1 );
	memcpy( sym->name, name, len );
	sym->name[len] = NULLC;
    } else
	sym->name = "";
    return( sym );
}

struct asym * FASTCALL SymFind( const char *name )
/**************************************/
/* find a symbol in the local/global symbol table,
 * return ptr to next free entry in global table if not found.
 * Note: lsym must be global, thus if the symbol isn't
 * found and is to be added to the local table, there's no
 * second scan necessary.
 */
{
    int i;
    int len;

    len = strlen( name );
    i = hashpjw( name );

    if ( CurrProc ) {
	for( lsym = &lsym_table[ i & ( LHASH_TABLE_SIZE - 1 )]; *lsym; lsym = &((*lsym)->nextitem ) ) {
	    if ( len == (*lsym)->name_size && SYMCMP( name, (*lsym)->name, len ) == 0 ) {
		return( *lsym );
	    }
	}
    }

    for( gsym = &gsym_table[ i & ( GHASH_TABLE_SIZE - 1 ) ]; *gsym; gsym = &((*gsym)->nextitem ) ) {
	if ( len == (*gsym)->name_size && SYMCMP( name, (*gsym)->name, len ) == 0 ) {
	    return( *gsym );
	}
    }

    return( NULL );
}

/* SymLookup() creates a global label if it isn't defined yet */

struct asym *SymLookup( const char *name )
/****************************************/
{
    struct asym	     *sym;

    sym = SymFind( name );
    if( sym == NULL ) {
	sym = SymAlloc( name );
	*gsym = sym;
	++SymCount;
    }

    return( sym );
}

/* SymLookupLocal() creates a local label if it isn't defined yet.
 * called by LabelCreate() [see labels.c]
 */
struct asym *SymLookupLocal( const char *name )
/*********************************************/
{
    //struct asym      **sym_ptr;
    struct asym	     *sym;

    sym = SymFind( name );
    if ( sym == NULL ) {
	sym = SymAlloc( name );
	sym->scoped = TRUE;
	/* add the label to the local hash table */
	*lsym = sym;
    } else if( sym->state == SYM_UNDEFINED && sym->scoped == FALSE ) {
	/* if the label was defined due to a FORWARD reference,
	 * its scope is to be changed from global to local.
	 */
	/* remove the label from the global hash table */
	*gsym = sym->nextitem;
	SymCount--;
	sym->scoped = TRUE;
	/* add the label to the local hash table */
	sym->nextitem = NULL;
	*lsym = sym;
    }

    return( sym );
}

/* free a symbol.
 * the symbol is no unlinked from hash tables chains,
 * hence it is assumed that this is either not needed
 * or done by the caller.
 */

void SymFree( struct asym *sym )
{
    switch( sym->state ) {
    case SYM_INTERNAL:
	if ( sym->isproc )
	    DeleteProc( (struct dsym *)sym );
	break;
    case SYM_EXTERNAL:
	if ( sym->isproc )
	    DeleteProc( (struct dsym *)sym );
	sym->first_size = 0;
	/* The altname field may contain a symbol (if weak == FALSE).
	 * However, this is an independant item and must not be released here
	 */
	break;
    case SYM_MACRO:
	ReleaseMacroData( (struct dsym *)sym );
	break;
    }
}

/* add a symbol to local table and set the symbol's name.
 * the previous name was "", the symbol wasn't in a symbol table.
 * Called by:
 * - ParseParams() in proc.c for procedure parameters.
 */
struct asym *SymAddLocal( struct asym *sym, const char *name )
/************************************************************/
{
    struct asym *sym2;
    /* v2.10: ignore symbols with state SYM_UNDEFINED! */

    if( ( sym2 = SymFind( name ) ) && sym2->state != SYM_UNDEFINED ) {
	/* shouldn't happen */
	asmerr( 2005, name );
	return( NULL );
    }
    sym->name_size = strlen( name );
    sym->name = LclAlloc( sym->name_size + 1 );
    memcpy( sym->name, name, sym->name_size + 1 );
    sym->nextitem = NULL;
    *lsym = sym;
    return( sym );
}

/* add a symbol to the global symbol table.
 * Called by:
 * - RecordDirective() in types.c to add bitfield fields (which have global scope).
 */

struct asym *SymAddGlobal( struct asym *sym )
{
    if( SymFind( sym->name ) ) {
	asmerr( 2005, sym->name );
	return( NULL );
    }
    sym->nextitem = NULL;
    *gsym = sym;
    SymCount++;
    return( sym );
}

struct asym *SymCreate( const char *name )
/* Create symbol and optionally insert it into the symbol table */
{
    struct asym *sym;

    if( SymFind( name ) ) {
	asmerr( 2005, name );
	return( NULL );
    }
    sym = SymAlloc( name );
    *gsym = sym;
    SymCount++;
    return( sym );
}

struct asym *SymLCreate( const char *name )
/* Create symbol and insert it into the local symbol table.
 * This function is called by LocalDir() and ParseParams()
 * in proc.c ( for LOCAL directive and PROC parameters ).
 */
{
    struct asym *sym;

    /* v2.10: ignore symbols with state SYM_UNDEFINED */

    if( ( sym = SymFind( name ) ) && sym->state != SYM_UNDEFINED ) {
	asmerr( 2005, name );
	return( NULL );
    }
    sym = SymAlloc( name );
    *lsym = sym;
    return( sym );
}

void SymMakeAllSymbolsPublic( void )
{
    int i;
    struct asym *sym;

    for( i = 0; i < GHASH_TABLE_SIZE; i++ ) {
	for( sym = gsym_table[i]; sym; sym = sym->nextitem ) {
	    if ( sym->state == SYM_INTERNAL &&
		/* v2.07: MT_ABS is obsolete */
		sym->isequate == FALSE &&     /* no EQU or '=' constants */
		sym->predefined == FALSE && /* no predefined symbols ($) */
		sym->included == FALSE && /* v2.09: symbol already added to public queue? */
		sym->name[1] != '&' && /* v2.10: no @@ code labels */
		sym->ispublic == FALSE ) {
		sym->ispublic = TRUE;
		AddPublicData( sym );
	    }
	}
    }
}

void SymFini( void )
{
}

/* initialize global symbol table */

void SymInit( void )
{
    struct asym *sym;
    int i;
    time_t    time_of_day;
    struct tm *now;

    SymCount = 0;

    /* v2.11: ensure CurrProc is NULL - might be a problem if multiple files are assembled */
    CurrProc = NULL;

    memset( gsym_table, 0, sizeof(gsym_table) );

    time_of_day = time( NULL );
    now = localtime( &time_of_day );
#if USESTRFTIME
    strftime( szDate, 9, szDateFmt, now );
    strftime( szTime, 9, szTimeFmt, now );
#else
    sprintf( szDate, "%02u/%02u/%02u", now->tm_mon + 1, now->tm_mday, now->tm_year % 100 );
    sprintf( szTime, "%02u:%02u:%02u", now->tm_hour, now->tm_min, now->tm_sec );
#endif

    for( i = 0; i < sizeof(tmtab) / sizeof(tmtab[0]); i++ ) {
	sym = SymCreate( tmtab[i].name );
	sym->state = SYM_TMACRO;
	sym->isdefined = TRUE;
	sym->predefined = TRUE;
	sym->string_ptr = tmtab[i].value;
	if ( tmtab[i].store )
	    *tmtab[i].store = sym;
    }

    for( i = 0; i < sizeof(eqtab) / sizeof(eqtab[0]); i++ ) {
	sym = SymCreate( eqtab[i].name );
	sym->state = SYM_INTERNAL;
	sym->isdefined = TRUE;
	sym->predefined = TRUE;
	sym->offset = eqtab[i].value;
	sym->sfunc_ptr = eqtab[i].sfunc_ptr;
	if ( eqtab[i].store )
	    *eqtab[i].store = sym;
    }
    sym->list	= FALSE; /* @WordSize should not be listed */

    for( i = 0; i < dyneqcount; i++ ) {
	sym = SymCreate( dyneqtable[i] );
	sym->state = SYM_TMACRO;
	sym->isdefined = TRUE;
	sym->predefined = TRUE;
	sym->offset = dyneqvalue[i];
	sym->sfunc_ptr = NULL;
    }

    /* $ is an address (usually). Also, don't add it to the list */
    symPC->variable = TRUE;
    symPC->list	    = FALSE;
    LineCur->list   = FALSE;
    return;

}

void SymPassInit( int pass )
{
    unsigned i;

    if ( pass == PASS_1 )
	return;

    /* No need to reset the "defined" flag if FASTPASS is on.
     * Because then the source lines will come from the line store,
     * where inactive conditional lines are NOT contained.
     */
    if ( UseSavedState )
	return;
    /* mark as "undefined":
     * - SYM_INTERNAL - internals
     * - SYM_MACRO - macros
     * - SYM_TMACRO - text macros
     */
    for( i = 0; i < GHASH_TABLE_SIZE; i++ ) {
	struct asym *sym;
	for( sym = gsym_table[i]; sym; sym = sym->nextitem ) {
	    if ( sym->predefined == FALSE ) {
		/* v2.04: all symbol's "defined" flag is now reset. */
		    sym->isdefined = FALSE;
	    }
	}
    }
}

uint_32 SymGetCount( void )
{
    return( SymCount );
}

/* get all symbols in global hash table */

void SymGetAll( struct asym **syms )
{
    struct asym		*sym;
    unsigned		i, j;

    /* copy symbols to table */
    for( i = j = 0; i < GHASH_TABLE_SIZE; i++ ) {
	for( sym = gsym_table[i]; sym; sym = sym->nextitem ) {
	    syms[j++] = sym;
	}
    }
    return;
}

/* enum symbols in global hash table.
 * used for codeview symbolic debug output.
 */

struct asym *SymEnum( struct asym *sym, int *pi )
{
    if ( sym == NULL ) {
	*pi = 0;
	sym = gsym_table[*pi];
    } else {
	sym = sym->nextitem;
    }

    /* v2.10: changed from for() to while() */
    while( sym == NULL && *pi < GHASH_TABLE_SIZE - 1 )
	sym = gsym_table[++(*pi)];
    return( sym );
}

void FASTCALL QEnqueue( struct qdesc *q, void *item )
{
    if( q->head == NULL ) {
	q->head = q->tail = item;
    } else {
	*(void **)q->tail = item;
	q->tail = item;
    }
    *(void**)item = NULL;
}

/* add a new node to a queue */

void FASTCALL QAddItem( struct qdesc *q, const void *data )
{
    struct qnode    *node;

    node = LclAlloc( sizeof( struct qnode ) );
    node->elmt = data;
    QEnqueue( q, node );
}

void FASTCALL AddPublicData( struct asym *sym )
{
    QAddItem( &ModuleInfo.g.PubQueue, sym );
}
