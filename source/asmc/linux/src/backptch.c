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
* Description:	backpatch: short forward jump optimization.
*
****************************************************************************/

#include <globals.h>
#include <memalloc.h>
#include <parser.h>
#include <fixup.h>
#include <segment.h>

/*
 * LABELOPT: short jump label optimization.
 * if this is 0, there is just the simple "fixup backpatch",
 * which cannot adjust any label offsets between the forward reference
 * and the newly defined label, resulting in more passes to be needed.
*/
#define LABELOPT 1

#define SkipFixup()

static void DoPatch( struct asym *sym, struct fixup *fixup )
/**********************************************************/
{
    int_32		disp;
    int_32		max_disp;
    unsigned		size;
    struct dsym		*seg;
#if LABELOPT
    struct asym		*sym2;
    struct fixup	*fixup2;
#endif

    /* all relative fixups should occure only at first pass and they signal forward references
     * they must be removed after patching or skiped ( next processed as normal fixup )
     */

    seg = GetSegm( sym );
    if( seg == NULL || fixup->def_seg != seg ) {
	/* if fixup location is in another segment, backpatch is possible, but
	 * complicated and it's a pretty rare case, so nothing's done.
	 */
	SkipFixup();
	return;
    }

    if( Parse_Pass == PASS_1 ) {
	if( sym->mem_type == MT_FAR && fixup->option == OPTJ_CALL ) {
	    /* convert near call to push cs + near call,
	     * (only at first pass) */
	    ModuleInfo.PhaseError = TRUE;
	    sym->offset++;  /* a PUSH CS will be added */
	    /* todo: insert LABELOPT block here */
	    OutputByte( 0 ); /* it's pass one, nothing is written */
	    FreeFixup( fixup );
	    return;
	} else {
	    /* forward reference, only at first pass */
	    switch( fixup->type ) {
	    case FIX_RELOFF32:
	    case FIX_RELOFF16:
		FreeFixup( fixup );
		return;
	    case FIX_OFF8:  /* push <forward reference> */
		if ( fixup->option == OPTJ_PUSH ) {
		    size = 1;	 /* size increases from 2 to 3/5 */
		    goto patch;
		}
	    }
	}
    }
    size = 0;
    switch( fixup->type ) {
    case FIX_RELOFF32:
	size = 2; /* will be 4 finally */
	/* fall through */
    case FIX_RELOFF16:
	size++; /* will be 2 finally */
	/* fall through */
    case FIX_RELOFF8:
	size++;
	/* calculate the displacement */
	disp = fixup->offset + fixup->sym->offset - fixup->locofs - size - 1;
	max_disp = (1UL << ((size * 8)-1)) - 1;
	if( disp > max_disp || disp < (-max_disp-1) ) {
	patch:
	    ModuleInfo.PhaseError = TRUE;
	    /* ok, the standard case is: there's a forward jump which
	     * was assumed to be SHORT, but it must be NEAR instead.
	     */
	    switch( size ) {
	    case 1:
		size = 0;
		switch( fixup->option ) {
		case OPTJ_EXPLICIT:
		    return;
		case OPTJ_EXTEND: /* Jxx for 8086 */
		    size++;	  /* will be 3/5 finally */
		    /* fall through */
		case OPTJ_JXX: /* Jxx for 386 */
		    size++;
		    /* fall through */
		default: /* normal JMP (and PUSH) */
		    if( seg->e.seginfo->Ofssize )
			size += 2; /* NEAR32 instead of NEAR16 */
		    size++;
#if LABELOPT
		    /* v2.04: if there's an ORG between src and dst, skip
		     * the optimization!
		     */
		    if ( Parse_Pass == PASS_1 ) {
			for ( fixup2 = seg->e.seginfo->FixupList.head; fixup2; fixup2 = fixup2->nextrlc ) {
			    if ( fixup2->orgoccured ) {
				return;
			    }
			    /* do this check after the check for ORG! */
			    if ( fixup2->locofs <= fixup->locofs )
				break;
			}
		    }
		    /* scan the segment's label list and adjust all labels
		     * which are between the fixup loc and the current sym.
		     * ( PROCs are NOT contained in this list because they
		     * use the <next>-field of dsym already!)
		     */
		    for ( sym2 = seg->e.seginfo->label_list; sym2; sym2 = (struct asym *)((struct dsym *)sym2)->next ) {
			if ( sym2->offset <= fixup->locofs )
			    break;
			sym2->offset += size;
		    }
		    /* v2.03: also adjust fixup locations located between the
		     * label reference and the label. This should reduce the
		     * number of passes to 2 for not too complex sources.
		     */
		    if ( Parse_Pass == PASS_1 ) /* v2.04: added, just to be safe */
		    for ( fixup2 = seg->e.seginfo->FixupList.head; fixup2; fixup2 = fixup2->nextrlc ) {
			if ( fixup2->sym == sym )
			    continue;
			if ( fixup2->locofs <= fixup->locofs )
			    break;
			fixup2->locofs += size;
		    }
#else
		    sym->offset += size;
#endif
		    /*	it doesn't matter what's actually "written" */
		    for ( ; size; size-- )
			OutputByte( 0xCC );
		    break;
		}
		break;
	    case 2:
	    case 4:
		asmerr( 2075, disp - max_disp ); /* warning ? */
		break;
	    }
	}
	/* v2.04: fixme: is it ok to remove the fixup?
	 * it might still be needed in a later backpatch.
	 */
	FreeFixup( fixup );
	break;
    default:
	SkipFixup();
	break;
    }
    return;
}

int BackPatch( struct asym *sym )
/************************************/
/*
 * patching for forward reference labels in Jmp/Call instructions;
 * called by LabelCreate(), ProcDef() and data_dir(), that is, whenever
 * a (new) label is defined. The new label is the <sym> parameter.
 * During the process, the label's offset might be changed!
 *
 * field sym->fixup is a "descending" list of forward references
 * to this symbol. These fixups are only generated during pass 1.
 */
{
    struct fixup     *fixup;
    struct fixup     *next;

    for( fixup = sym->bp_fixup; fixup; fixup = next ) {
	next = fixup->nextbp;
	DoPatch( sym, fixup );
    }
    sym->bp_fixup = NULL;
    return( NOT_ERROR );
}

