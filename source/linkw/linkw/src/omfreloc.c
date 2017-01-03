/****************************************************************************
*
*                            Open Watcom Project
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
* Description:  Routines specific processing relocations in OMF.
*
****************************************************************************/


#include "linkstd.h"
#include "msg.h"
#include "wlnkmsg.h"
#include "alloc.h"
#include "newmem.h"
#include "virtmem.h"
#include "reloc.h"
#include <pcobj.h>
#include <string.h>
#include "obj2supp.h"
#include "objnode.h"
#include "objio.h"
#include "overlays.h"
#include "objstrip.h"
#include "objomf.h"
#include "objpass2.h"
#include "ring.h"
#include "omfreloc.h"

#if BORLAND_EXT==0
#define FindSegNode FindNode
#else
void * FindSegNode( NODEARRAY *list, unsigned index );
#endif

typedef struct bakpatlist {
    struct bakpatlist   *next;
    virt_mem            addr;
    unsigned_16         len;
    byte                loctype;
    bool                is32bit;
    char                data[1];
} bakpat_list;

static bakpat_list      *BakPats;

#define MAX_THREADS 4

static frame_spec       FrameThreads[MAX_THREADS];
static frame_spec       TargThreads[MAX_THREADS];

static fix_type RelocTypeMap[] = {
    FIX_OFFSET_8,       // LOC_OFFSET_LO
    FIX_OFFSET_16,      // LOC_OFFSET
    FIX_BASE,           // LOC_BASE
    FIX_BASE_OFFSET_16, // LOC_BASE_OFFSET
    FIX_HIGH_OFFSET_8,  // LOC_OFFSET_HI
    FIX_OFFSET_32,      // LOC_OFFSET_32
    FIX_BASE_OFFSET_32, // LOC_BASE_OFFSET_32
    FIX_OFFSET_16 | FIX_LOADER_RES      // modified loader resolved off_16
};

static void GetTarget( unsigned loc, frame_spec *targ, struct objbuff * );
static void GetFrame( unsigned frame, frame_spec *refframe, struct objbuff * );

void ResetOMFReloc( void )
/*******************************/
{
    BakPats = NULL;
}

#if 1

/* handle relocations in LIDATA.
 * due to the way relocations are handled in this linker,
 * it's a bit complicated to manage this case.
 */

struct fixinfo {
	fix_type type;
	frame_spec *frame;
	frame_spec *targ;
	offset addend;
};

static void ProcIDBlock( obj_format ObjFormat, unsigned_32 *dest, struct objbuff *ob, unsigned_32 iterate, struct fixinfo *fi )
/***************************************************************************/
/* Process logically iterated data blocks. */
{
    byte            len;
    byte            *anchor;
    unsigned_16     count;
    unsigned_16     inner;
    unsigned_32     rep;

    if( iterate == 0 ) {  // no iterations, so abort.
        ob->curr = ob->end;
        return;
    }
    _TargU16toHost( _GetU16UN( ob->curr ), count );
    ob->curr += sizeof( unsigned_16 );
    if( count == 0 ) {
        len = *ob->curr;
        ++ob->curr;
        do {
            DEBUG((DBG_OLD, "ProcIDBlock(): curr/start/*dest=%h/%h/%h result=%h, iterate=%d", ob->curr, ob->start_lidata, *dest, *dest - ( ob->curr - ob->start_lidata ), iterate ));
            StoreFixup( *dest - ( ob->curr - ob->start_lidata ), fi->type, fi->frame, fi->targ, fi->addend );
            *dest += len;
        } while( --iterate != 0 );
        ob->curr += len;
    } else {
        anchor = ob->curr;
        if( ObjFormat & FMT_MS_386 ) {
            do {
                ob->curr = anchor;
                inner = count;
                do {
                    _TargU32toHost( _GetU32UN(ob->curr), rep );
                    ob->curr += sizeof(unsigned_32);
                    ProcIDBlock( ObjFormat, dest, ob, rep, fi );
                } while( --inner != 0 );
            } while( --iterate != 0 );
        } else {
            do {
                ob->curr = anchor;
                inner = count;
                do {
                    _TargU16toHost( _GetU16UN(ob->curr), rep );
                    ob->curr += sizeof(unsigned_16);
                    ProcIDBlock( ObjFormat, dest, ob, rep, fi );
                } while( --inner != 0 );
            } while( --iterate != 0 );
        }
    }
    return;
}

void StoreLidataFixup( offset off, fix_type type, frame_spec *frame,
                      frame_spec *targ, offset addend, obj_format ObjFormat, struct objbuff *ob )
/****************************************************************************/
{
    /* <off> is relative position in LIDATA record, which is a quite
     * different thing than a rel. position in LEDATA!
     */
    unsigned_32 rep;
    struct fixinfo fi;
    unsigned_32 start = off;

    fi.type = type;
    fi.frame = frame;
    fi.targ = targ;
    fi.addend = addend;

    while( ob->curr < ob->end ) {
        if( ObjFormat & FMT_MS_386 ) {
            _TargU32toHost( _GetU32UN( ob->curr ), rep );
            ob->curr += sizeof( unsigned_32 );
        } else {
            _TargU16toHost( _GetU16UN( ob->curr ), rep );
            ob->curr += sizeof( unsigned_16 );
        }
        ProcIDBlock( ObjFormat, &start, ob, rep, &fi );
    }
}
#endif

void DoRelocs( struct objbuff *ob )
/**************************/
/* Process FIXUP records. */
{
    fix_type    fixtype;
    unsigned    typ;
    unsigned    omftype;
    offset      place_to_fix;
    unsigned    loc;
    signed_32   addend;
    frame_spec  fthread;
    frame_spec  tthread;

    if( ObjFormat & FMT_IGNORE_FIXUPP )
        return;
    do {
        typ = GET_U8_UN( ob->curr );
        ++ob->curr;
        omftype = (typ >> 2) & 7;
        if( (typ & 0x80) == 0 ) {   /*  thread */
            if( typ & 0x40 ) {      /*  frame */
                GetFrame( omftype, &FrameThreads[typ & 3], ob );
            } else {                /*  target */
                GetTarget( omftype, &TargThreads[typ & 3], ob );
            }
        } else {                    /* fixup */
            if( typ & 0x20 ) {      // used in 32-bit microsoft fixups.
                switch( omftype ) {
                case LOC_OFFSET:
                case LOC_MS_LINK_OFFSET:
                    omftype = LOC_OFFSET_32;
                    break;
                case LOC_BASE_OFFSET:
                    omftype = LOC_BASE_OFFSET_32;
                    break;
                }
            } else if( omftype == LOC_MS_LINK_OFFSET
                        && !(ObjFormat & FMT_32BIT_REC) ) {
                omftype = LOC_BASE_OFFSET_32 + 1; // index of special table.
            }
            fixtype = RelocTypeMap[omftype];
            if( !(typ & 0x40) ) {
                fixtype |= FIX_REL;
            }
            place_to_fix = ((typ & 3) << 8) + GET_U8_UN( ob->curr );
            ++ob->curr;
            typ = *ob->curr;
            ++ob->curr;
            loc = typ >> 4 & 7;
            if( typ & 0x80 ) {
                fthread = FrameThreads[loc & 3];
            } else {
                GetFrame( loc, &fthread, ob );
            }
            loc = typ & 7;
            if( typ & 8 ) {
                tthread = TargThreads[loc & 3];
            } else {
                GetTarget( loc, &tthread, ob );
            }
            addend = 0;
            if( loc <= TARGET_ABSWD ) {  /*  if( (loc & 4) == 0 )then */
                if( ObjFormat & FMT_32BIT_REC ) {
                    addend = *((signed_32 UNALIGN *)ob->curr);
                    ob->curr += sizeof( signed_32 );
                } else {
                    addend = GET_U16_UN(ob->curr);
                    ob->curr += sizeof( unsigned_16 );
                }
            }
            if( ObjFormat & FMT_IS_LIDATA ) {
                struct objbuff tmp;
                tmp.curr = tmp.start_lidata = ob->start_lidata;
                tmp.end  = ob->end_lidata;
                StoreLidataFixup( place_to_fix, fixtype, &fthread, &tthread, addend, ob->objformat, &tmp );
            } else
                StoreFixup( place_to_fix, fixtype, &fthread, &tthread, addend );
        }
    } while( ob->curr < ob->end );
    return;
}

static void GetFrame( unsigned frame, frame_spec *refframe, struct objbuff *ob )
/**********************************************************/
/* Get frame for fixup. */
{
    extnode     *ext;
    grpnode     *group;
    segnode     *seg;
    unsigned    index;

    if( frame < FRAME_LOC ) {
        index = GetIdx( ob );
    }
    refframe->type = frame;
    switch( frame ) {
    case FRAME_SEG:
        seg = (segnode *) FindSegNode( SegNodes, index );
//#ifdef _INT_DEBUG
        if ( seg == NULL ) {
            DEBUG((DBG_OLD, "omfreloc.GetFrame(): error, invalid seg index %h", index ));
            BadObject();
            break;
        }
//#endif
        refframe->u.sdata = seg->entry;
        break;
    case FRAME_GRP:
        group = (grpnode *) FindNode( GrpNodes, index );
//#ifdef _INT_DEBUG
        if ( group == NULL ) {
            DEBUG((DBG_OLD, "omfreloc.GetFrame(): error, invalid grp index %h", index ));
            BadObject();
            break;
        }
//#endif
        if( group->entry == NULL ) {
            refframe->type = FIX_FRAME_FLAT;
        } else {
            refframe->u.group = group->entry;
        }
        break;
    case FRAME_EXT:
        ext = (extnode *) FindNode( ExtNodes, index );
//#ifdef _INT_DEBUG
        if ( ext == NULL ) {
            DEBUG((DBG_OLD, "omfreloc.GetFrame(): error, invalid ext index %h", index ));
            BadObject();
            break;
        }
//#endif
        if( IS_SYM_IMPORTED( ext->entry ) ) {
            refframe->type = FIX_FRAME_TARG;
        } else {
            refframe->u.sym = ext->entry;
        }
        break;
    case FRAME_TARG:
    case FRAME_LOC:
        break;
    default:
        DEBUG((DBG_OLD, "omfreloc.GetFrame(): error, unknown frame type %h", frame ));
        BadObject();
    }
}

static void GetTarget( unsigned loc, frame_spec *targ, struct objbuff *ob )
/*****************************************************/
{
    extnode             *ext;
    grpnode             *group;
    segnode             *seg;

    targ->type = loc & 3;
    switch( loc ) {
    case TARGET_SEGWD:
    case TARGET_SEG:
        seg = (segnode *) FindSegNode( SegNodes, GetIdx( ob ) );
//#ifdef _INT_DEBUG
        if ( seg == NULL ) {
            DEBUG((DBG_OLD, "omfreloc.GetTarget(): error, invalid seg index" ));
            BadObject();
            break;
        }
//#endif
        targ->u.sdata = seg->entry;
        break;
    case TARGET_GRPWD:
    case TARGET_GRP:
        group = (grpnode *) FindNode( GrpNodes, GetIdx( ob ) );
//#ifdef _INT_DEBUG
        if ( group == NULL ) {
            DEBUG((DBG_OLD, "omfreloc.GetTarget(): error, invalid grp index" ));
            BadObject();
            break;
        }
//#endif
        targ->u.group = group->entry;
        break;
    case TARGET_EXTWD:
    case TARGET_EXT:
        ext = (extnode *) FindNode( ExtNodes, GetIdx( ob ) );
//#ifdef _INT_DEBUG
        if ( ext == NULL ) {
            DEBUG((DBG_OLD, "omfreloc.GetTarget(): error, invalid ext index" ));
            BadObject();
            break;
        }
//#endif
        targ->u.sym = ext->entry;
        break;
    case TARGET_ABSWD:
    case TARGET_ABS:
        _TargU16toHost( _GetU16UN( ob->curr ), targ->u.abs );
        ob->curr += sizeof( unsigned_16 );
        break;
    }
}

#if 0
static void StoreBakPat( segnode *seg, byte loctype )
/****************************************************/
/* store a bakpat record away for future processing. */
{
    unsigned            len;
    bakpat_list         *bkptr;

    len = EOObjRec - ObjBuff;
    _ChkAlloc( bkptr, sizeof(bakpat_list) + len - 1 );
    bkptr->len = len;
    bkptr->addr = seg->entry->data;
    bkptr->loctype = loctype;
    bkptr->is32bit = (ObjFormat & FMT_32BIT_REC) != 0;
    memcpy( bkptr->data, ObjBuff, len );
    LinkList( &BakPats, bkptr );
}

void ProcBakpat( void )
/****************************/
/* store the bakpat record away for future processing */
{
    segnode             *seg;
    byte                loctype;

    seg = (segnode *) FindSegNode( SegNodes, GetIdx() );
    if( seg->info & SEG_DEAD )
        return;
    loctype = *ObjBuff++;
    StoreBakPat( seg, loctype );
}

void DoBakPats( void )
/***************************/
/* go through the list of stored bakpats and apply them all */
{
    char                *data;
    bakpat_list         *bkptr;
    bakpat_list         *next;
    offset              off;
    offset              value;
    unsigned_8          value8;
    unsigned_16         value16;
    unsigned_32         value32;
    virt_mem            vmemloc;

    bkptr = BakPats;
    while( bkptr != NULL ) {
        next = bkptr->next;
        data = bkptr->data;
        off = 0;
        value = 0;
        while( bkptr->len > 0 ) {
            if( bkptr->is32bit ) {
                _TargU32toHost( _GetU32( data ), off );
                data += sizeof(unsigned_32);
                _TargU32toHost( _GetU32( data ), value );
                data += sizeof(unsigned_32);
                bkptr->len -= 2 * sizeof(unsigned_32);
            } else {
                _TargU16toHost( _GetU16( data ), off );
                data += sizeof(unsigned_16);
                _TargU16toHost( _GetU16( data ), value );
                data += sizeof(unsigned_16);
                bkptr->len -= 2 * sizeof(unsigned_16);
            }
            vmemloc = bkptr->addr + off;
            switch( bkptr->loctype ) {
            case 0:
                ReadInfo( vmemloc, &value8, sizeof(unsigned_8) );
                value8 += value;
                PutInfo( vmemloc, &value8, sizeof(unsigned_8) );
                break;
            case 1:
                ReadInfo( vmemloc, &value16, sizeof(unsigned_16) );
                value16 += value;
                PutInfo( vmemloc, &value16, sizeof(unsigned_16) );
                break;
            case 2:
                ReadInfo( vmemloc, &value32, sizeof(unsigned_32) );
                value32 += value;
                PutInfo( vmemloc, &value32, sizeof(unsigned_32) );
                break;
            }
        }
        _LnkFree( bkptr );
        bkptr = next;
    }
    BakPats = NULL;
}

void ProcNbkpat( void )
/****************************/
/* process a named bakpat record */
{
    list_of_names       *symname;
    symbol              *sym;
    segnode             seg;
    byte                loctype;

    loctype = *ObjBuff++;
    symname = FindName( GetIdx() );
    sym = RefISymbol( symname->name );
    if( !IS_SYM_COMDAT(sym) )           /* can't handle these otherwise */
        return;
    if( sym->info & SYM_DEAD )
        return;
    seg.entry = sym->p.seg;
    StoreBakPat( &seg, loctype );
}
#endif
