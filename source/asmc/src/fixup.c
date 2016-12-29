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
* Description:	handles fixups
*
****************************************************************************/

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <fixup.h>
#include <segment.h>
#include <omfspec.h>

#define GNURELOCS 1

extern struct asym *SegOverride;

int_8	Frame_Type;   /* curr fixup frame type: SEG|GRP|EXT|ABS|NONE; see omfspec.h */
uint_16 Frame_Datum;  /* curr fixup frame value */

struct fixup *CreateFixup( struct asym *sym, enum fixup_types type, enum fixup_options option )
/*********************************************************************************************/
/*
 * called when an instruction operand or a data item is relocatable:
 * - Parser.idata_fixup()
 * - Parser.memory_operand()
 * - branch.process_branch()
 * - data.data_item()
 * - dbgcv()
 * - fpfixup()
 * creates a new fixup item and initializes it using symbol <sym>.
 * put the correct target offset into the link list when forward reference of
 * relocatable is resolved;
 * Global vars Frame_Type and Frame_Datum "should" be set.
 */
{
    struct fixup     *fixup;

    fixup = (struct fixup *)LclAlloc( sizeof( struct fixup ) );

    /* add the fixup to the symbol's linked list (used for backpatch)
     * this is done for pass 1 only.
     */
    if ( Parse_Pass == PASS_1 ) {
	if ( sym ) { /* changed v1.96 */
	    fixup->nextbp = sym->bp_fixup;
	    sym->bp_fixup = fixup;
	}
	/* v2.03: in pass one, create a linked list of
	 * fixup locations for a segment. This is to improve
	 * backpatching, because it allows to adjust fixup locations
	 * after a distance has changed from short to near
	 */
	if ( CurrSeg ) {
	    fixup->nextrlc = CurrSeg->e.seginfo->FixupList.head;
	    CurrSeg->e.seginfo->FixupList.head = fixup;
	}
    }
    /* initialize locofs member with current offset.
     * It's unlikely to be the final location, but sufficiently exact for backpatching.
     */
    fixup->locofs = GetCurrOffset();
    fixup->offset = 0;
    fixup->type = type;
    fixup->option = option;
    fixup->flags = 0;
    fixup->frame_type = Frame_Type;	/* this is just a guess */
    fixup->frame_datum = Frame_Datum;
    fixup->def_seg = CurrSeg;		/* may be NULL (END directive) */
    fixup->sym = sym;

    return( fixup );
}

/* remove a fixup from the segment's fixup queue */

void FreeFixup( struct fixup *fixup )
/***********************************/
{
    struct dsym *dir;
    struct fixup *fixup2;

    if ( Parse_Pass == PASS_1 ) {
	dir = fixup->def_seg;
	if ( dir ) {
	    if ( fixup == dir->e.seginfo->FixupList.head ) {
		dir->e.seginfo->FixupList.head = fixup->nextrlc;
	    } else {
		for ( fixup2 = dir->e.seginfo->FixupList.head; fixup2; fixup2 = fixup2->nextrlc ) {
		    if ( fixup2->nextrlc == fixup ) {
			fixup2->nextrlc = fixup->nextrlc;
			break;
		    }
		}
	    }
	}
    }
}

/*
 * Set global variables Frame_Type and Frame_Datum.
 * segment override with a symbol (i.e. DGROUP )
 * it has been checked in the expression evaluator that the
 * symbol has type SYM_SEG/SYM_GRP.
 */

void SetFixupFrame( const struct asym *sym, char ign_grp )
/********************************************************/
{
    struct dsym *grp;

    if( sym ) {
	switch ( sym->state ) {
	case SYM_INTERNAL:
	case SYM_EXTERNAL:
	    if( sym->segment != NULL ) {
		if( ign_grp == FALSE && ( grp = (struct dsym *)GetGroup( sym ) ) ) {
		    Frame_Type = FRAME_GRP;
		    Frame_Datum = grp->e.grpinfo->grp_idx;
		} else {
		    Frame_Type = FRAME_SEG;
		    Frame_Datum = GetSegIdx( sym->segment );
		}
	    }
	    break;
	case SYM_SEG:
	    Frame_Type = FRAME_SEG;
	    Frame_Datum = GetSegIdx( sym->segment );
	    break;
	case SYM_GRP:
	    Frame_Type = FRAME_GRP;
	    Frame_Datum = ((struct dsym *)sym)->e.grpinfo->grp_idx;
	    break;
	}
    }
}

/*
 * Store fixup information in segment's fixup linked list.
 * please note: forward references for backpatching are written in PASS 1 -
 * they no longer exist when store_fixup() is called.
 */

void store_fixup( struct fixup *fixup, struct dsym *seg, int_32 *pdata )
/**********************************************************************/
{
    fixup->offset = *pdata;

    fixup->nextrlc = NULL;
    if ( Options.output_format == OFORMAT_OMF ) {

	/* for OMF, the target's offset is stored at the fixup's location. */
	if( fixup->type != FIX_SEG && fixup->sym ) {
	    *pdata += fixup->sym->offset;
	}

    } else {

	if ( Options.output_format == OFORMAT_ELF ) {
	    /* v2.07: inline addend for ELF32 only.
	     * Also, in 64-bit, pdata may be a int_64 pointer (FIX_OFF64)!
	     */
	    if ( ModuleInfo.defOfssize == USE64 ) {
	    } else
	    if ( fixup->type == FIX_RELOFF32 )
		*pdata = -4;
#if GNURELOCS /* v2.04: added */
	    else if ( fixup->type == FIX_RELOFF16 )
		*pdata = -2;
	    else if ( fixup->type == FIX_RELOFF8 )
		*pdata = -1;
#endif
	}
	/* special handling for assembly time variables needed */
	if ( fixup->sym && fixup->sym->variable ) {
	    /* add symbol's offset to the fixup location and fixup's offset */
	    *pdata += fixup->sym->offset;
	    fixup->offset	  += fixup->sym->offset;
	    /* and save symbol's segment in fixup */
	    fixup->segment_var = fixup->sym->segment;
	}
    }
    if( seg->e.seginfo->FixupList.head == NULL ) {
	seg->e.seginfo->FixupList.tail = seg->e.seginfo->FixupList.head = fixup;
    } else {
	seg->e.seginfo->FixupList.tail->nextrlc = fixup;
	seg->e.seginfo->FixupList.tail = fixup;
    }
    return;
}
