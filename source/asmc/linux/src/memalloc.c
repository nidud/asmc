/****************************************************************************
*
*  This code is Public Domain.
*
*  ========================================================================
*
* Description:	Memory allocation routines.
*
****************************************************************************/

#include "globals.h"
#include "memalloc.h"

/* what items are stored in the heap?
 * - symbols + symbol names ( asym, dsym; symbol.c )
 * - macro lines ( StoreMacro(); macro.c )
 * - file names ( CurrFName[]; assemble.c )
 * - temp items + buffers ( omf.c, bin.c, coff.c, elf.c )
 * - contexts ( reused; context.c )
 * - codeview debug info ( dbgcv.c )
 * - library names ( includelib; directiv.c )
 * - src lines for FASTPASS ( fastpass.c )
 * - fixups ( fixup.c )
 * - hll items (reused; .IF, .WHILE, .REPEAT; hll.c )
 * - one big input buffer ( src line buffer, tokenarray, string buffer; input.c )
 * - src filenames array ( AddFile(); input.c )
 * - line number info ( -Zd, -Zi; linnum.c )
 * - macro parameter array + default values ( macro.c )
 * - prologue, epilogue macro names ??? ( option.c )
 * - dll names ( OPTION DLLIMPORT; option.c )
 * - std queue items ( see queues in struct module_vars; globals.h, queue.c )
 * - renamed keyword queue ( reswords.c )
 * - safeseh queue ( safeseh.c )
 * - segment alias names ( segment.c )
 * - segment stack ( segment.c )
 * - segment buffers ( 1024 for omf, else may be HUGE ) ( segment.c )
 * - segment names for simplified segment directives (simsegm.c )
 * - strings of text macros ( string.c )
 * - struct/union/record member items + default values ( types.c )
 * - procedure prologue argument, debug info ( proc.c )
 */

/* FASTMEM is a simple memory alloc approach which allocates chunks of 512 kB
 * and will release it only at MemFini().
 *
 * May be considered to create an additional "line heap" to store lines of
 * loop macros and generated code - since this is hierarchical, a simple
 * Mark/Release mechanism will do the memory management.
 * currently generated code lines are stored in the C heap, while
 * loop macro lines go to the "fastmem" heap.
 */

#define ALIGNMENT	16
#define BLKSIZE		0x80000

struct linked_list {
    struct linked_list *next;
};
static struct linked_list *pBase; /* start list of 512 kB blocks; to be moved to ModuleInfo.g */
static uint_8 *pCurr; /* points into current block; to be moved to ModuleInfo.g */
static uint_32 currfree; /* free memory left in current block; to be moved to ModuleInfo.g */

void MemInit( void )
{
    pBase = NULL;
    pCurr = NULL;
    currfree = 0;
}

void MemFini( void )
{
    struct linked_list *p;

    while ( pBase ) {

	p = pBase;
	pBase = pBase->next;
	free( p );
    }
}

void *LclAlloc( size_t size )
{
    void *ptr;
    struct linked_list *p;
    int z;

    size += ALIGNMENT-1;
    size &= -ALIGNMENT;

    if (size > currfree) {

	z = size;
	if (z <= BLKSIZE-ALIGNMENT)
	    z = BLKSIZE-ALIGNMENT;
	currfree = z;
	z += ALIGNMENT;
	if( (p = malloc(z)) == NULL )
	    asmerr( 1901 );
	memset(p, 0, z);
	p->next = pBase;
	pBase = p;
	pCurr = (uint_8 *)p;
	pCurr += ALIGNMENT;
    }
    ptr = pCurr;
    pCurr += size;
    currfree -= size;
    return ptr;
}

void *MemAlloc( size_t size )
{
    void *ptr;
    ptr = malloc( size );
    if( ptr == NULL ) {
	asmerr( 1901 );
    }
    return( ptr );
}

