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
* Description:  Routines for creation of DOS EXE and COM files.
*
****************************************************************************/


#include <string.h>
#include "linkstd.h"
#include <exedos.h>
#include "pcobj.h"
#include "newmem.h"
#include "msg.h"
#include "alloc.h"
#include "reloc.h"
#include "wlnkmsg.h"
#include "virtmem.h"
#include "fileio.h"
#include "overlays.h"
#include "loadfile.h"
#include "objcalc.h"
#include "ring.h"
#include "dbgall.h"
#include "loaddos.h"

#define MINHDRSIZE 0

/* jwlink: add 2 bytes to MZ header (gives 0x1E instead of 0x20) */
//#define ADDMZHDR sizeof( unsigned_32 );
#define MZHDRADD sizeof( unsigned_16 )

unsigned_32             OvlTabOffset;

/* jwlink: bugfix for .COM files with more than one group */
static signed long oldchop;

static unsigned_32 WriteDOSRootRelocs( void )
/*******************************************/
/* write all relocs to the file */
{
	unsigned long       header_size;
#if 1 /* JWlink: KNOWEAS */
    int x;
#endif

    DumpRelocList( Root->reloclist );
    NullAlign( 0x10 );
#if 1  /* JWLink: KNOWEAS */
    if ( FmtData.u.dos.knoweas )
        x = 0x40;
    else
#endif
        x = sizeof( dos_exe_header ) + MZHDRADD;

    header_size = (unsigned long)Root->relocs * sizeof( dos_addr ) + x;
    DEBUG(( DBG_OLD, "WriteDOSRootRelocs(): header_size=%h x=%h", header_size, x ));
    return( MAKE_PARA( header_size ) );
}

static void WriteDOSSectRelocs( section *sect, bool repos )
/*********************************************************/
/* write all relocs associated with sect to the file */
{
    unsigned long       loc;
    OUTFILELIST         *out;

    if( sect->relocs != 0 ) {
        loc = sect->u.file_loc + MAKE_PARA( sect->size );
        out = sect->outfile;
        if( out->file_loc > loc ) {
            SeekLoad( loc );
        } else {
            if( repos ) {
                SeekLoad( out->file_loc );
            }
            if( out->file_loc < loc ) {
                PadLoad( loc - out->file_loc );
                out->file_loc = loc;
            }
        }
        loc += sect->relocs * sizeof( dos_addr );
        DumpRelocList( sect->reloclist );
        if( loc > out->file_loc ) {
            out->file_loc = loc;
        }
    }
}

static void AssignFileLocs( section *sect )
/*****************************************/
{
    if( FmtData.u.dos.pad_sections ) {
        sect->outfile->file_loc = ROUND_UP( sect->outfile->file_loc, SECTOR_SIZE );
    }
    sect->u.file_loc = sect->outfile->file_loc;
    sect->outfile->file_loc += MAKE_PARA( sect->size )
                            + MAKE_PARA( sect->relocs * sizeof( dos_addr ) );
    DEBUG((DBG_LOADDOS, "section %d assigned to %l in %s",
            sect->ovl_num, sect->u.file_loc, sect->outfile->fname ));
}

static unsigned long WriteDOSData( void )
/***************************************/
/* copy code from extra memory to loadfile */
{
    group_entry         *group;
    SECTION             *sect;
    unsigned long       header_size;
    outfilelist         *fnode;
    bool                repos;
    unsigned long       root_size;

    DEBUG(( DBG_OLD, "WritingDOSData() enter" ));
    OrderGroups( CompareDosSegments );
    CurrSect = Root;        // needed for WriteInfo.
    header_size = WriteDOSRootRelocs();
#if MINHDRSIZE
    /* if a min header size is required (for better MS link compat) */
    if ( header_size < MINHDRSIZE ) {
        header_size = MINHDRSIZE;
        SeekLoad( header_size );
    }
#endif
    DEBUG(( DBG_OLD, "WritingDOSData(): header_size=%h", header_size ));

    Root->u.file_loc = header_size;
    if( Root->areas != NULL ) {
        Root->outfile->file_loc = header_size + Root->size;
        WalkAllOvl( &AssignFileLocs );
        EmitOvlTable();
    }

// keep track of positions within the file.
    for( fnode = OutFiles; fnode != NULL; fnode = fnode->next ) {
        fnode->file_loc = 0;
    }
    Root->outfile->file_loc = Root->u.file_loc;
    //printf("root file_loc=%X\n", Root->u.file_loc);
    Root->sect_addr = Groups->grp_addr;

/* write groups and relocations */
    for( group = Groups; group != NULL; ) {
        sect = group->section;
        CurrSect = sect;
        fnode = sect->outfile;
        repos = WriteDOSGroup( group );
        //printf(" file_loc=%X\n", fnode->file_loc);
        group = group->next_group;
        if( ( group == NULL ) || ( sect != group->section ) ) {
            if( sect == Root ) {
                root_size = fnode->file_loc;
            } else {
                WriteDOSSectRelocs( sect, repos );
            }
        }
        if( repos ) {
            SeekLoad( fnode->file_loc );
        }
    }
    return( root_size );
}

/*
 * the next set of 3 routines are a big kludge.  This is a lot of copycat
 * code from loadfile to allow the front chunk of a group to be split off
*/

static unsigned long COMAmountWritten;

static bool WriteSegData( void *_sdata, void *_start )
/****************************************************/
{
    segdata *sdata = _sdata;
    signed long *start = _start;
    signed long newpos;
    signed long pad;

    if( !sdata->isuninit && !sdata->isdead ) {
        newpos = *start + sdata->a.delta;
        if( newpos + (signed long)sdata->length <= 0 )
            return( FALSE );
        pad = newpos - COMAmountWritten;
        if( pad > 0 ) {
            DEBUG((DBG_OLD, "loaddos:WriteSegData: pad=%h, calling PadLoad", pad ));
            PadLoad( pad );
            COMAmountWritten += pad;
            pad = 0;
        }
        DEBUG((DBG_OLD, "loaddos:WriteSegData: %s newpos=%h length=%h pad=%h", sdata->u.name, newpos, sdata->length, pad ));
        WriteInfo( sdata->data - pad, sdata->length + pad );
        COMAmountWritten += sdata->length + pad;
    }
    return( FALSE );
}

static bool DoCOMGroup( void *_seg, void *chop )
/**********************************************************/
{
    seg_leader *seg = _seg;
    signed long newstart;

    newstart = *(signed long *)chop + GetLeaderDelta( seg );
    DEBUG((DBG_OLD, "DoCOMGroup: newstart=%h", newstart ));
    RingLookup( seg->pieces, WriteSegData, &newstart );
    return( FALSE );
}

static bool WriteCOMGroup( group_entry *group, signed long chop )
/***************************************************************/
/* write the data for group to the loadfile */
/* returns TRUE if the file should be repositioned */
{
    unsigned long       loc;
    signed  long        diff;
    section             *sect;
    bool                repos;
    outfilelist         *finfo;

    repos = FALSE;
    sect = group->section;
    CurrSect = sect;
    finfo = sect->outfile;
    loc = SUB_ADDR( group->grp_addr, sect->sect_addr ) + sect->u.file_loc;
    DEBUG((DBG_OLD, "WriteCOMGroup(%s, %h) enter: loc=%h group.grp_addr=%h sect.sect_addr=%h sect.file_loc=%h finfo.file_loc=%h",
        group->sym->name, chop, loc, group->grp_addr, sect->sect_addr, sect->u.file_loc, finfo->file_loc ));
    //diff = loc - finfo->file_loc;
    diff = loc - finfo->file_loc + oldchop;
    oldchop += chop;
    if( diff > 0 ) {
        DEBUG((DBG_OLD, "WriteCOMGroup(%s): calling PadLoad( %h )", group->sym->name, diff ));
        PadLoad( diff );
    } else if( diff != 0 ) {
        DEBUG((DBG_OLD, "WriteCOMGroup(%s): calling SeekLoad( %h )", group->sym->name, loc ))
        SeekLoad( loc );
        repos = TRUE;
    }
    DEBUG((DBG_OLD, "WriteCOMGroup(%s): group %a section %d to %l in %s",
            group->sym->name, &group->grp_addr, sect->ovl_num, loc, finfo->fname ));
    COMAmountWritten = 0;
    Ring2Lookup( group->leaders, DoCOMGroup, &chop );
    loc += COMAmountWritten;
    if( loc > finfo->file_loc ) {
        finfo->file_loc = loc;
    }
    DEBUG((DBG_OLD, "WriteCOMGroup(%s): finfo->file_loc=%h", group->sym->name, finfo->file_loc ));
    return( repos );
}

static void WriteCOMFile( void )
/******************************/
// generate a DOS .COM file.
{
    outfilelist         *fnode;
    group_entry         *group;
    bool                repos;
    unsigned long       root_size;
    signed long         chop;

    DEBUG((DBG_OLD, "WriteCOMFile enter" ))
    if( StartInfo.addr.seg != 0 ) {
        LnkMsg( ERR+MSG_INV_COM_START_ADDR, NULL );
        return;
    }
    if( ( StackAddr.seg != 0 ) || ( StackAddr.off != 0 ) ) {
        LnkMsg( WRN+MSG_STACK_SEG_IGNORED, NULL );
    }
    OrderGroups( CompareDosSegments );
    CurrSect = Root;        // needed for WriteInfo.
    fnode = Root->outfile;
    fnode->file_loc = Root->u.file_loc = 0;
    Root->sect_addr = Groups->grp_addr;

    oldchop = 0;
    /* write groups */
    for( group = Groups; group != NULL; group = group->next_group ) {
        chop = SUB_ADDR( group->grp_addr, StartInfo.addr );
        if( chop > 0 ) {
            chop = 0;
        }
        if( (signed long)group->size + chop > 0 ) {
            repos = WriteCOMGroup( group, chop );
            if( repos ) {
                SeekLoad( fnode->file_loc );
            }
        }
#if 0
        if( loc < 0 ) {
            Root->u.file_loc += (unsigned long)loc;  // adjust for missing code
        }
#endif
    }
    root_size = fnode->file_loc;
    //if( root_size > (64 * 1024L - 0x200) ) {
    if( root_size > (64 * 1024L - 0x101) ) {
        LnkMsg( WRN+MSG_COM_TOO_LARGE, NULL );
    }
    DBIWrite();
}

void FiniDOSLoadFile( void )
/*********************************/
/* terminate writing of load file */
{
    unsigned_32         hdr_size;
    unsigned_32         temp;
    unsigned_32         min_size;
    unsigned_32         root_size;
    dos_exe_header      exe_head;

    DEBUG(( DBG_OLD, "FiniDOSLoadFile() enter" ));
    if( FmtData.type & MK_COM ) {
        WriteCOMFile();
        return;
    }
    hdr_size = sizeof( dos_exe_header ) + MZHDRADD;
#if 1  //JWLink: KNOWEAS
	if ( FmtData.u.dos.knoweas ) {
		hdr_size = 0x40;
	}
#endif
    SeekLoad( hdr_size );
	root_size = WriteDOSData();
	//printf("FiniDOSLoadFile: root_size=%X\n", root_size);
    if( FmtData.type & MK_OVERLAYS ) {
        PadOvlFiles();
    }
    // output debug info into root main output file
    CurrSect = Root;
    DBIWrite();
    hdr_size = MAKE_PARA( (unsigned long)Root->relocs * sizeof( dos_addr )
                                                                 + hdr_size );
#if MINHDRSIZE
    if ( hdr_size < MINHDRSIZE )
        hdr_size = MINHDRSIZE;
#endif
    DEBUG((DBG_LOADDOS, "root size %l, hdr size %l", root_size, hdr_size ));
    SeekLoad( 0 );
    _HostU16toTarg( 0x5a4d, exe_head.signature );
    temp = hdr_size / 16U;
    _HostU16toTarg( temp, exe_head.hdr_size );
    _HostU16toTarg( root_size % 512U, exe_head.mod_size );
    temp = ( root_size + 511U ) / 512U;
    _HostU16toTarg( temp, exe_head.file_size );
    _HostU16toTarg( Root->relocs, exe_head.num_relocs );

    min_size = MemorySize() - ( root_size - hdr_size ) + FmtData.SegMask;
    min_size >>= FmtData.SegShift;
    _HostU16toTarg( min_size, exe_head.min_16 );
    _HostU16toTarg( 0xffff, exe_head.max_16 );
    _HostU16toTarg( StartInfo.addr.off, exe_head.IP );
    _HostU16toTarg( StartInfo.addr.seg, exe_head.CS_offset );
    _HostU16toTarg( StackAddr.seg, exe_head.SS_offset );
    _HostU16toTarg( StackAddr.off, exe_head.SP );
    _HostU16toTarg( 0, exe_head.chk_sum );
#if 1  //JWLink: KNOWEAS
    if ( FmtData.u.dos.knoweas )
        _HostU16toTarg( 0x40, exe_head.reloc_offset );
    else
#endif
        _HostU16toTarg( sizeof( dos_exe_header ) + MZHDRADD,
                       exe_head.reloc_offset );
    _HostU16toTarg( 0, exe_head.overlay_num );
    WriteLoad( &exe_head, sizeof( dos_exe_header ) );
    WriteLoad( &OvlTabOffset, MZHDRADD );
}
