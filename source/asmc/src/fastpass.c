/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	implements the "fastpass" handling.
*		"fastpass" is an optimization which increases
*		assembly time speed by storing preprocessed lines
*		in memory during the first pass. In further passes,
*		those lines are "read" instead of the original assembly
*		source files.
*		Speed increase is significant if there's a large include
*		file at the top of an assembly source which contains
*		just equates and type definitions, because there's no need
*		to save such lines during pass one.
*
****************************************************************************/

#include "globals.h"
#include "memalloc.h"
#include "parser.h"
#include "input.h"
#include "segment.h"
#include "fastpass.h"

extern uint_32 list_pos;  /* current LST file position */

static struct mod_state modstate; /* struct to store assembly status */
static struct {
    struct line_item *head;
    struct line_item *tail;
} LineStore;
struct line_item *LineStoreCurr; /* must be global! */
int StoreState;
int UseSavedState;
int NoLineStore = 0;

/*
 * save the current status (happens in pass one only) and
 * switch to "save precompiled lines" mode.
 * the status is then restored in further passes,
 * and the precompiled lines are used for assembly then.
 */

static void SaveState( void )
/***************************/
{
    StoreState = TRUE;
    UseSavedState = TRUE;
    modstate.init = TRUE;
    modstate.Equ.head = modstate.Equ.tail = NULL;

    memcpy( &modstate.modinfo, (uint_8 *)&ModuleInfo + sizeof( struct module_vars ), sizeof( modstate.modinfo ) );

    SegmentSaveState();
    AssumeSaveState();
    ContextSaveState(); /* save pushcontext/popcontext stack */
}

void StoreLine( const char *srcline, int flags, uint_32 lst_position )
/********************************************************************/
{
    int i,j;
    char *p;

    if ( NoLineStore != 0 )
	return;
    if ( ModuleInfo.GeneratedCode ) /* don't store generated lines! */
	return;
    if ( StoreState == FALSE ) /* line store already started? */
	SaveState();

    i = strlen( srcline );
    j = ( ( ( flags & 1 ) && ModuleInfo.CurrComment ) ? strlen( ModuleInfo.CurrComment ) : 0 );
    LineStoreCurr = LclAlloc( i + j + sizeof( struct line_item ) );
    LineStoreCurr->next = NULL;
    LineStoreCurr->lineno = GetLineNumber();
    if ( MacroLevel ) {
	LineStoreCurr->srcfile = 0xfff;
    } else {
	LineStoreCurr->srcfile = get_curr_srcfile();
    }
    LineStoreCurr->list_pos = ( lst_position ? lst_position : list_pos );
    if ( j ) {
	memcpy( LineStoreCurr->line, srcline, i );
	memcpy( LineStoreCurr->line + i, ModuleInfo.CurrComment, j + 1 );
    } else
	memcpy( LineStoreCurr->line, srcline, i + 1 );

    /* v2.08: don't store % operator at pos 0 */
    for ( p = LineStoreCurr->line; *p && islspace(*p); p++ );
    if (*p == '%' && ( _memicmp( p+1, "OUT", 3 ) || is_valid_id_char( *(p+4) ) ) )
	*p = ' ';

    if ( LineStore.head )
	LineStore.tail->next = LineStoreCurr;
    else
	LineStore.head = LineStoreCurr;
    LineStore.tail = LineStoreCurr;
}

/* an error has been detected in pass one. it should be
 reported in pass 2, so ensure that a full source scan is done then
 */

void SkipSavedState( void )
/*************************/
{
    UseSavedState = FALSE;
}

/* for FASTPASS, just pass 1 is a full pass, the other passes
 don't start from scratch and they just assemble the preprocessed
 source. To be able to restart the assembly process from a certain
 location within the source, it's necessary to save the value of
 assembly time variables.
 However, to reduce the number of variables that are saved, an
 assembly-time variable is only saved when
 - it is changed
 - it was defined when StoreState() is called
 */

void SaveVariableState( struct asym *sym )
/****************************************/
{
    struct equ_item *p;

    sym->issaved = TRUE; /* don't try to save this symbol (anymore) */
    p = LclAlloc( sizeof( struct equ_item ) );
    p->next = NULL;
    p->sym = sym;
    p->lvalue	 = sym->value;
    p->hvalue	 = sym->value3264; /* v2.05: added */
    p->mem_type	 = sym->mem_type;  /* v2.07: added */
    p->isdefined = sym->isdefined;
    if ( modstate.Equ.tail ) {
	modstate.Equ.tail->next = p;
	modstate.Equ.tail = p;
    } else {
	modstate.Equ.head = modstate.Equ.tail = p;
    }
}

struct line_item *RestoreState( void )
/************************************/
{
    if ( modstate.init ) {
	struct equ_item *curr;
	unsigned char aflag = ( ModuleInfo.aflag & _AF_LSTRING );
	/* restore values of assembly time variables */
	for ( curr = modstate.Equ.head; curr; curr = curr->next ) {
	    /* v2.07: MT_ABS is obsolete */
		curr->sym->value     = curr->lvalue;
		curr->sym->value3264 = curr->hvalue;
		curr->sym->mem_type  = curr->mem_type; /* v2.07: added */
		curr->sym->isdefined = curr->isdefined;
	}
	/* fields in module_vars are not to be restored.
	 * v2.10: the module_vars fields are not saved either.
	 * v2.23: save L"Unicode" flag
	 */
	memcpy( (char *)&ModuleInfo + sizeof( struct module_vars ), &modstate.modinfo, sizeof( modstate.modinfo ) );
	ModuleInfo.aflag |= aflag;
	SetOfssize();
	SymSetCmpFunc();
    }

    return( LineStore.head );
}

void FastpassInit( void )
/***********************/
{
    StoreState = FALSE;
    modstate.init = FALSE;
    LineStore.head = NULL;
    LineStore.tail = NULL;
    UseSavedState = FALSE;
}

