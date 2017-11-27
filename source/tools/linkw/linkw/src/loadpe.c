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
* Description:  Utilities for creation of PE (Win32) executable files.
*
****************************************************************************/


#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <time.h>
#include "linkstd.h"
#include "exeos2.h"
#include "loados2.h"
#include "exepe.h"
#include "reloc.h"
#include "specials.h"
#include "alloc.h"
#include "pcobj.h"
#include "msg.h"
#include "wlnkmsg.h"
#include "virtmem.h"
#include "objnode.h"
#include "loadfile.h"
#include "objcalc.h"
#include "fileio.h"
#include "dbgcomm.h"
#include "dbgall.h"
#include "dbgcv.h"
#include "objpass1.h"
#include "ring.h"
#include "strtab.h"
#include "carve.h"
#include "permdata.h"
#include "loadpe.h"
#include "reserr.h"
#include "wres.h"
#include "exerespe.h"
#include "param.h"
#include "pass2.h"
#include "sharedio.h"
#include "impexp.h"
#include "toc.h"
#include "objstrip.h"

#define I386_TRANSFER_OP1       0xff    /* first byte of a "JMP [FOO]" */
#define I386_TRANSFER_OP2       0x25    /* second byte of a "JMP [FOO]" */

#define MINIMUM_SEG_SHIFT       2       /* Corresponds to 2^2 == 4 bytes */
#define DEFAULT_SEG_SHIFT       9       /* Corresponds to 2^9 == 512 bytes */

#define STUB_ALIGN 8    /* for PE format */

#pragma pack(1)

typedef struct {
    unsigned_8  op1;
    unsigned_8  op2;
    unsigned_32 dest;
} i386_transfer;

static i386_transfer    I386Jump = { I386_TRANSFER_OP1, I386_TRANSFER_OP2, 0 };

#define I386_TRANSFER_SIZE (sizeof(i386_transfer))

#define ALPHA_TRANSFER_OP1      0x277F
#define ALPHA_TRANSFER_OP2      0xA37B
#define ALPHA_TRANSFER_OP3      0x6BFB

typedef struct {
    unsigned_16 high;
    unsigned_16 op1;
    unsigned_16 low;
    unsigned_16 op2;
    unsigned_16 zero;
    unsigned_16 op3;
} alpha_transfer;

#pragma pack()

typedef struct local_import {
    struct local_import *next;
    symbol              *iatsym;
    symbol              *locsym;
} local_import;

static alpha_transfer   AlphaJump = {   0, ALPHA_TRANSFER_OP1,
                                        0, ALPHA_TRANSFER_OP2,
                                        0, ALPHA_TRANSFER_OP3 };

#define ALPHA_TRANSFER_SIZE (sizeof(alpha_transfer))

static unsigned_32 PPCJump[]= {
    0x81620000,         //   lwz        r11,[tocv]__imp_RtlMoveMemory(rtoc)
    0x818B0000,         //   lwz        r12,(r11)
    0x90410004,         //   stw        rtoc,0x4(sp)
    0x7D8903A6,         //   mtctr      r12
    0x804B0004,         //   lwz        rtoc,0x4(r11)
    0x4E800420          //   bctr
};

#define PPC_TRANSFER_SIZE (sizeof(PPCJump))

#define TRANSFER_SEGNAME "TRANSFER CODE"

static module_import    *PEImpList;  /* list of imported modules */
static unsigned         NumMods;
static segdata          *XFerSegData; /* linker-generated thunk data */
static local_import     *PELocalImpList;
static unsigned         NumLocalImports;

static struct {
    offset      ilt_off;
    offset      eof_ilt_off;
    offset      iat_off;
    offset      mod_name_off;
    offset      hint_off;
    offset      total_size;
    segdata     *sdata;
} IData;

#if 1 /* JWLink */
static struct {
    segdata     *sdata;
} EData;
#endif

#define WALK_IMPORT_SYMBOLS(sym) \
    for( (sym) = HeadSym; (sym) != NULL; (sym) = (sym)->link ) \
        if( IS_SYM_IMPORTED(sym) && (sym)->p.import != NULL \
            /*&& !((sym)->info & SYM_DEAD)*/)

static offset CalcIDataSize( void )
/*******************************/
{
    struct module_import        *mod;
    struct import_name          *imp;
    unsigned_32 iatsize;
    unsigned_32 size;

    if ( FmtData.u.pe.win64 )
        iatsize = (NumImports+NumMods) * sizeof( pe_va64 );
    else
        iatsize = (NumImports+NumMods) * sizeof( pe_va );
    if( 0 == iatsize ) {
        return( 0 );
    }
    //printf(" iatsize=%X, tocsize=%X\n", iatsize, TocSize );
    IData.ilt_off = (NumMods + 1) * sizeof( pe_import_directory );
    if ( FmtData.u.pe.win64 && ( IData.ilt_off & 4 ) )
        IData.ilt_off += 4;
    IData.eof_ilt_off = IData.ilt_off + iatsize;
    IData.iat_off = IData.eof_ilt_off + TocSize;
    IData.mod_name_off = IData.iat_off + iatsize;
    size = 0;
    for( mod = PEImpList; mod != NULL; mod = mod->next ) {
        size += mod->mod->len + 1;
    }
    IData.hint_off = IData.mod_name_off + size;
    size = IData.hint_off;
    for( mod = PEImpList; mod != NULL; mod = mod->next ) {
        for( imp = mod->imports; imp != NULL; imp = imp->next ) {
            if( imp->imp != NULL ) {
                size += (size & 1); /* round up */
                size += imp->imp->len + sizeof( unsigned_16 ) + sizeof( unsigned_8 );
            }
        }
    }
    DEBUG(( DBG_OLD, "CalcIDataSize: size import data=%h", size ));
    IData.total_size = size;
    return( IData.total_size );
}

void ResetLoadPE( void )
/*****************************/
{
    PEImpList = NULL;
    XFerSegData = NULL;
    NumMods = 0;
    NumImports = 0;
    memset( &IData, 0, sizeof( IData ) );
#if 1 /* JWLink: exports */
    memset( &EData, 0, sizeof( EData ) );
#endif
}

static offset CalcIATAbsOffset( void )
/************************************/
{
    seg_leader                  *idata;
#if 0 /* JWLink: idata */
    //return( IDataGroup->linear + FmtData.base + IData.iat_off );
#else
    idata = FindSegment( Root, CoffIDataSegName );
    return( idata->group->linear + GetLeaderDelta( idata ) +
           FmtData.base + IData.iat_off );
#endif
}

static void CalcImpOff( dll_sym_info *dll, unsigned *off )
/********************************************************/
{
    if( dll != NULL) { // if not end of mod marker
        dll->iatsym->addr.off = *off;
        dll->iatsym->addr.seg = 0;
        //printf("symbol %s: offs=%X\n", dll->iatsym->name, dll->iatsym->addr.off );
    }
    if ( FmtData.u.pe.win64 )
        *off += 8;
    else
        *off += 4;
}

static void XFerReloc( offset off, group_entry *group, unsigned type )
/********************************************************************/
{
    reloc_item  reloc;
    size_t      size;

    size = sizeof(pe_reloc_item);
    reloc.pe = ((off + group->linear) & OSF_PAGE_MASK) | type;
    if( type == PE_FIX_HIGHADJ ) {
        size = sizeof( high_pe_reloc_item );
        reloc.hpe.low_off = AlphaJump.low;
    }
    WriteReloc( group, off, &reloc, size );
}

static int GetTransferGlueSize( int lnk_state )
/*********************************************/
{
    switch( lnk_state & HAVE_MACHTYPE_MASK ) {
    case HAVE_ALPHA_CODE:   return( ALPHA_TRANSFER_SIZE );
    case HAVE_I86_CODE:     return( I386_TRANSFER_SIZE );
    case HAVE_PPC_CODE:     return( PPC_TRANSFER_SIZE );
    default:                DbgAssert( 0 ); return( 0 );
    }
}

static void *GetTransferGlueCode( int lnk_state )
/************************************************/
{
    switch( lnk_state & HAVE_MACHTYPE_MASK ) {
    case HAVE_ALPHA_CODE:   return( &AlphaJump );
    case HAVE_I86_CODE:     return( &I386Jump );
    case HAVE_PPC_CODE:     return( &PPCJump );
    default:                DbgAssert( 0 ); return( NULL );
    }
}

offset FindIATSymAbsOff( symbol *sym )
/********************************************/
{
    dll_sym_info        *dll;

    dll = sym->p.import;
    DbgAssert( IS_SYM_IMPORTED(sym) && dll != NULL );
    return( dll->iatsym->addr.off );
}

signed_32 FindSymPosInTocv( symbol *sym )
/***********************************************/
{
    offset off = FindIATSymAbsOff(sym) - IDataGroup->linear - FmtData.base;
    off = off - TocShift - IData.eof_ilt_off;
    return( off );
}

static void GenPETransferTable( void )
/************************************/
{
    offset          off;
    offset          base;
    symbol          *sym;
    void*           data;
    size_t          datalen;
    group_entry     *group;
    local_import    *loc_imp;
    pe_va           addr;
    pe_va           xferbase;

    DEBUG(( DBG_OLD, "GenPETransferTable() enter, IDataGroup=%h, XFerSegData=%h", IDataGroup, XFerSegData ));
    if( IDataGroup == NULL )
        return;
    if( XFerSegData == NULL )
        return;
    group = XFerSegData->u.leader->group;
    /* for 64-bit, get the address of the xfer segment */
    xferbase = group->linear + GetLeaderDelta( XFerSegData->u.leader ) + FmtData.base;
    base = XFerSegData->u.leader->seg_addr.off + XFerSegData->a.delta;
    datalen = GetTransferGlueSize( LinkState );
    data = GetTransferGlueCode( LinkState );
    WALK_IMPORT_SYMBOLS(sym) {
        DEBUG(( DBG_OLD, "GenPETransferTable(): import=%s info=%h", sym->name, sym->info ));
        if( LinkState & HAVE_ALPHA_CODE ) {
            offset dest = FindIATSymAbsOff( sym );
            AlphaJump.high = dest >> 16;
            AlphaJump.low = dest;
            if( LinkState & MAKE_RELOCS ) {
                if( !(FmtData.objalign & 0xFFFF) ) {
                    XFerReloc( sym->addr.off+offsetof(alpha_transfer, high),
                               group, PE_FIX_HIGH );
                } else {
                    XFerReloc( sym->addr.off+offsetof(alpha_transfer, low),
                               group, PE_FIX_LOW );
                    XFerReloc( sym->addr.off+offsetof(alpha_transfer, high),
                                group, PE_FIX_HIGHADJ );
                }
            }
        } else if( LinkState & HAVE_I86_CODE ) {
            offset dest = FindIATSymAbsOff( sym );
            /* jwlink: don't write jmp instruction if not referenced */
            if (!(sym->info & SYM_REFERENCED ))
                continue;
            if ( FmtData.u.pe.win64 == 0 ) {
                I386Jump.dest = dest;
                DEBUG(( DBG_OLD, "GenPETransferTable, %s: jmp thunk has been used", sym->name ));
                if( LinkState & MAKE_RELOCS ) {
                    XFerReloc( sym->addr.off + offsetof(i386_transfer,dest),
                              group, PE_FIX_HIGHLOW );
                }
            } else {
                /* no relocs for 64-bit, jump addr is PC-rel */
                I386Jump.dest = dest - ( xferbase + ( sym->addr.off - base + 6 ) ) ;
                DEBUG(( DBG_OLD, "GenPETransferTable, %s: I386Jump.dest=%h [ dest=%h - ( xferbase=%h + ( sym->addr.off=%h - base=%h + 6 ) )]",
                       sym->name, I386Jump.dest, dest, xferbase, sym->addr.off, base ));
            }
        } else {
            int_16 pos;
            pos = FindSymPosInTocv(sym);
            PPCJump[0] &= 0xffff0000;
            PPCJump[0] |= 0x0000ffff & pos;
        }
        off = sym->addr.off - base;
		DbgAssert( off + datalen <= XFerSegData->length );
        DEBUG(( DBG_OLD, "GenPETransferTable, %s: copy thunk (size=%d) to ofs=%h [tab size=%h]", sym->name, datalen, off, XFerSegData->length ));
        PutInfo( XFerSegData->data + off, data, datalen );
    }
    /* dump the local addresses table */
    for( loc_imp = PELocalImpList; loc_imp != NULL; loc_imp = loc_imp->next ) {
        off = loc_imp->iatsym->addr.off - base;
        addr = FindLinearAddr( &loc_imp->locsym->addr ) + FmtData.base;
        PutInfo( XFerSegData->data + off, &addr, sizeof( addr ) );
    }
    if( LinkState & MAKE_RELOCS ) {
        for( loc_imp = PELocalImpList; loc_imp != NULL; loc_imp = loc_imp->next ) {
            XFerReloc( loc_imp->iatsym->addr.off, group, PE_FIX_HIGHLOW );
        }
    }
    group->size = group->totalsize;
}

static void WriteDataPages( pe_header *header, pe_object *object )
/*****************************************************************/
/* write the enumerated data pages */
{
    group_entry *group;
    char        *name;
    pe_va       linear;
    seg_leader *leader;
    unsigned_32 size_v;
    unsigned_32 size_ph;

    header->code_base = 0xFFFFFFFFUL;
    header->data_base = 0xFFFFFFFFUL;
    for( group = Groups; group != NULL; group = group->next_group) {
        if( group->totalsize == 0 ) continue;   // DANGER DANGER DANGER <--!!!
        name = group->sym->name;
        leader = Ring2First( group->leaders );
        if( name == NULL || name[0] == 0 ) {
            name = leader->segname;
            if( name == NULL ) name = "";
        }
        strncpy( object->name, name, PE_OBJ_NAME_LEN );
        size_ph = CalcGroupSize( group );
        DEBUG(( DBG_OLD, "WriteDataPages(): grp=%s grp.segflgs=%h size_ph=%h", name, group->segflags, size_ph ));
        if( group == DataGroup && FmtData.dgroupsplitseg != NULL ) {
            size_v = group->totalsize;
            if( StackSegPtr != NULL ) {
                size_v -= StackSize;
            }
        } else {
            size_v = size_ph;
        }

        if ( group->alignment > header->object_align )
            LnkMsg( ERR+MSG_SECTIONALIGN_GT_OBJALIGN, "sd", name, group->alignment );

        linear = ROUND_UP( size_v, header->object_align );
        linear += group->linear;
        if( StartInfo.addr.seg == group->grp_addr.seg ) {
            header->entry_rva = group->linear + StartInfo.addr.off;
        }
        object->rva = group->linear;
        /*
        //  Why weren't we filling in this field? MS do!
        */
        object->virtual_size = size_v;
        object->physical_size = ROUND_UP( size_ph, header->file_align );

        object->flags = 0;
        /* segflags are in OS/2 V1.x format, we have to translate them
            into the appropriate PE bits */
        if( group->segflags & SEG_DATA ) {
            object->flags |= PE_OBJ_INIT_DATA | PE_OBJ_READABLE;
            if( !(group->segflags & SEG_READ_ONLY) ) {
                object->flags |= PE_OBJ_WRITABLE;
            }
            if( group->segflags & SEG_EXECUTABLE ) {
                DEBUG(( DBG_OLD, "WriteDataPages(): seg %s marked executable", name ));
                object->flags |= PE_OBJ_EXECUTABLE;
            }
            header->init_data_size += object->physical_size;
            if( object->rva < header->data_base ) {
                header->data_base = object->rva;
            }
        } else {
            object->flags |= PE_OBJ_CODE | PE_OBJ_EXECUTABLE;
            if( !(group->segflags & SEG_READ_ONLY) ) {
                object->flags |= PE_OBJ_READABLE;
            }
            if( group->segflags & SEG_WRITABLE ) {
                DEBUG(( DBG_OLD, "WriteDataPages(): seg %s marked writable", name ));
                object->flags |= PE_OBJ_WRITABLE;
            }
            if( group->segflags & SEG_NOPAGE) {
                object->flags |= PE_OBJ_NOT_PAGABLE;
            }
            header->code_size += object->physical_size;
            if( object->rva < header->code_base ) {
                header->code_base = object->rva;
            }
        }
        if( group->segflags & SEG_PURE ) {
            object->flags |= PE_OBJ_SHARED;
        }
        if( size_ph != 0 ) {
            object->physical_offset = NullAlign( header->file_align );
            WriteGroupLoad( group );
            PadLoad( size_ph - group->size );
        }
        if ( FmtData.u.pe.win64 && ( strcmp( object->name, ".pdata" ) == 0 ) ) {
            header->table[PE_TBL_EXCEPTION].size = size_v;
            header->table[PE_TBL_EXCEPTION].rva = object->rva;
        }

        ++object;
    }
    header->image_size = linear;
    if( header->code_base == 0xFFFFFFFFUL ) {
        header->code_base = 0;
    }
    if( header->data_base == 0xFFFFFFFFUL ) {
        header->data_base = 0;
    }
}

static void WalkImportsMods( void (*action)(dll_sym_info *, unsigned*),
                             void *cookie )
/****************************************************************/
{
    struct module_import        *mod;
    struct import_name          *imp;

    for( mod = PEImpList; mod != NULL; mod = mod->next ) {
        for( imp = mod->imports; imp != NULL; imp = imp->next ) {
            action( imp->dll, cookie );
        }
        action( NULL, cookie );
    }
}

static void WriteIAT( virt_mem buf, offset linear )
/*************************************************/
{
    struct module_import        *mod;
    struct import_name          *imp;
    pe_va       iat;
    pe_va64     iat64;
    offset      pos;
    offset      hint_rva ;

    pos = 0;
    hint_rva = IData.hint_off + linear;
    for( mod = PEImpList; mod != NULL; mod = mod->next ) {
        for( imp = mod->imports; imp != NULL; imp = imp->next ) {
            if( imp->imp != NULL ) {
                hint_rva += (hint_rva & 1); /* round up */
                iat = PE_IMPORT_BY_NAME | hint_rva;
                hint_rva += imp->imp->len +
                        (sizeof( unsigned_16 ) + sizeof( unsigned_8 ));
            } else {
                iat = PE_IMPORT_BY_ORDINAL | imp->dll->u.ordinal;
            }
            if ( FmtData.u.pe.win64 ) {
                iat64 = iat;
                PutInfo( buf+pos, &iat64, sizeof( iat64 ) ); pos += sizeof ( iat64 );
            } else {
                PutInfo( buf+pos, &iat, sizeof( iat ) ); pos += sizeof ( iat );
            }
        }
        /* NULL entry marks end of list */
        if ( FmtData.u.pe.win64 ) {
            iat64 = 0;
            PutInfo( buf+pos, &iat64, sizeof( iat64 ) ); pos += sizeof ( iat64 );
        } else {
            iat = 0;
            PutInfo( buf+pos, &iat, sizeof( iat ) ); pos += sizeof ( iat );
        }
    }
}

static void WriteImportInfo( void )
/*********************************/
{
    pe_import_directory         dir;
    unsigned_16                 hint;
    virt_mem                    buf;
    offset                      pos;
    group_entry                 *group;
#if 1 /* JWLink */
    seg_leader                  *idata;
#endif
    struct module_import        *mod;
    struct import_name          *imp;
    unsigned_32                 size;
    unsigned_32                 mod_name_rva;
    offset                      linear;

    if( IDataGroup == NULL ) {
        return;
    }
    group = IDataGroup;
#if 0 /* JWLink: imports */
    linear = group->linear;
    group->size = IData.total_size;
#else
    idata = FindSegment( Root, CoffIDataSegName );
    linear = idata->group->linear + GetLeaderDelta( idata );
    //printf("Idata linear=%Xh, total_size=%Xh\n", linear, IData.total_size );
#endif
    buf = IData.sdata->data;
    pos = 0;
    dir.time_stamp = 0;
    dir.major = 0;
    dir.minor = 0;
    /* dump the directory table */
    size = 0;
    mod_name_rva = IData.mod_name_off + linear;
    for( mod = PEImpList; mod != NULL; mod = mod->next ) {
        dir.name_rva = mod_name_rva;
        if ( FmtData.u.pe.win64 ) {
            dir.import_lookup_table_rva  = IData.ilt_off + size * 2 + linear;
            dir.import_address_table_rva = IData.iat_off + size * 2 + linear;
            //printf( "start ilt iat : %X %X\n", dir.import_lookup_table_rva, dir.import_address_table_rva );
        } else {
            dir.import_lookup_table_rva  = IData.ilt_off + size + linear;
            dir.import_address_table_rva = IData.iat_off + size + linear;
        }
        size += (mod->num_entries + 1) * sizeof( pe_va );
        mod_name_rva += mod->mod->len + 1;
        PutInfo( buf+pos, &dir, sizeof(dir) );
        pos += sizeof(dir);
    }
    PutNulls( buf+pos, sizeof(dir) );    /* NULL entry marks end of table */
    pos += sizeof(dir);
    WriteIAT(buf+IData.ilt_off, linear ); // Import Lookup table
    WriteToc(buf+IData.eof_ilt_off);
    for( pos = IData.eof_ilt_off; pos < IData.iat_off; pos += sizeof(pe_va)) {
        XFerReloc( pos, group, PE_FIX_HIGHLOW );
    }
    WriteIAT(buf+IData.iat_off, linear ); // Import Address table
    pos = IData.mod_name_off;            /* write the module names */
    for( mod = PEImpList; mod != NULL; mod = mod->next ) {
        int size = mod->mod->len + 1;
        PutInfo( buf+pos, mod->mod->name, size);
        pos += size;
    }
    pos = IData.hint_off;        /* write out the import names */
    for( mod = PEImpList; mod != NULL; mod = mod->next ) {
        hint = 1;
        for( imp = mod->imports; imp != NULL; imp = imp->next ) {
            if( imp->imp != NULL ) {
                PutNulls( buf+pos, pos & 1);
                pos += pos & 1;/* round up */
                PutInfo(buf+pos, &hint, sizeof(hint));
                pos += sizeof(hint);
                size = imp->imp->len;
                PutInfo(buf+pos, imp->imp->name, size);
                pos += size;
                PutNulls( buf+pos, 1);
                pos++;
                hint++;
            }
        }
    }
}

static int namecmp( const void *pn1, const void *pn2 )
/****************************************************/
{
    entry_export        *n1;
    entry_export        *n2;

    n1 = *(entry_export **)pn1;
    n2 = *(entry_export **)pn2;
    return( strcmp( n1->name, n2->name ) );
}

#if 0 /* JWLink: exports */
static void WriteExportInfo( pe_header *header, pe_object *object )
#else
static void WriteExportInfo( pe_header *header )
#endif
/*****************************************************************/
{
//    unsigned long       size;
    pe_export_directory dir;
    char                *name;
    unsigned            namelen;
    entry_export        **sort;
    entry_export        *exp;
    unsigned            i;
    unsigned_16         ord;
    pe_va               eat;
    unsigned            next_ord;
    unsigned            high_ord;
    unsigned            num_entries;
    unsigned            num_names;
#if 1 /* JWLink: exports */
    seg_leader          *edata;
    offset              pos;
    virt_mem            buf;
    offset              start;
#endif

#if 1 /* JWLink: exports */
    DEBUG(( DBG_OLD, "WriteExportInfo() enter" ));
    if ( FmtData.u.os2.exports == NULL )
        return;
    edata = FindSegment( Root, ".edata" );
    buf = EData.sdata->data;
    pos = 0;
    start = edata->group->linear + GetLeaderDelta( edata );
#else
    strncpy( object->name, ".edata", PE_OBJ_NAME_LEN );
    object->physical_offset = NullAlign( header->file_align );
    object->rva = header->image_size;
    object->flags = PE_OBJ_INIT_DATA | PE_OBJ_READABLE;
#endif
    dir.flags = 0;
    dir.time_stamp = 0;
    dir.major = 0;
    dir.minor = 0;
#if 0 /* JWLink: exports */
    dir.name_rva = object->rva + sizeof( dir );
#else
    dir.name_rva = start + sizeof( dir );
#endif
    dir.ordinal_base = FmtData.u.os2.exports->ordinal;
    if( FmtData.u.os2.res_module_name != NULL ) {
        name = FmtData.u.os2.res_module_name;
    } else {
        name = RemovePath( Root->outfile->fname, &namelen );
    }
    /* RemovePath strips the extension, which we don't want */
    namelen = strlen( name ) + 1;
    dir.address_table_rva = ROUND_UP( dir.name_rva+namelen,
                                                (unsigned long)sizeof(pe_va) );
    num_entries = 0;
    num_names = 0;
    for( exp = FmtData.u.os2.exports; exp != NULL; exp = exp->next ) {
        high_ord = exp->ordinal;
        ++num_entries;
        DEBUG(( DBG_OLD, "WriteExportInfo(): %s", exp->name ));
        if( !exp->isprivate ) {
            if( exp->isanonymous ) {
                if( exp->impname != NULL ) {
                    AddImpLibEntry( exp->impname, NULL, exp->ordinal );
                } else {
                    AddImpLibEntry( exp->sym->name, NULL, exp->ordinal );
                }
            } else {
                num_names++;
                if( exp->impname != NULL ) {
                    AddImpLibEntry( exp->impname, exp->name, NOT_IMP_BY_ORDINAL );
                } else {
                    AddImpLibEntry( exp->sym->name, exp->name, NOT_IMP_BY_ORDINAL );
                }
            }
        }
    }
    dir.num_eat_entries = high_ord - dir.ordinal_base + 1;
    dir.num_name_ptrs = num_names;
    DEBUG(( DBG_OLD, "WriteExportInfo(): # of EAT entries=%h, # of names=%h, ordinal base=%h", dir.num_eat_entries, dir.num_name_ptrs, dir.ordinal_base ));
    dir.name_ptr_table_rva = dir.address_table_rva +
                                dir.num_eat_entries * sizeof( pe_va );
    dir.ordinal_table_rva = dir.name_ptr_table_rva +
                                num_names * sizeof( pe_va );
    _ChkAlloc( sort, sizeof( entry_export * ) * num_entries );

    /* write the export directory table and module name */
    PutInfo( buf+pos, &dir, sizeof(dir) );
    pos += sizeof(dir);
    PutInfo( buf+pos, name, namelen );
    pos += namelen;
    pos = (pos+3) & ~3;

    /* write the export address table */
    i = 0;
    next_ord = dir.ordinal_base;
    for( exp = FmtData.u.os2.exports; exp != NULL; exp = exp->next ) {
        sort[ i++ ] = exp;
        eat = exp->addr.off;
        if( next_ord < exp->ordinal ) {
            pos += (exp->ordinal - next_ord) * sizeof( pe_va );
        }
        next_ord = exp->ordinal + 1;
        PutInfo( buf+pos, &eat, sizeof( eat ) );
        pos += sizeof( eat );
    }

    qsort( sort, num_entries, sizeof( entry_export * ), &namecmp );

    /* write out the export name ptr table */
    eat = dir.ordinal_table_rva + num_names * sizeof( unsigned_16 );
    for( i = 0; i < num_entries; ++i ) {
        exp = sort[i];
        if( exp->isanonymous ) continue;
        PutInfo( buf+pos, &eat, sizeof( eat ) );
        pos += sizeof( eat );
        eat += strlen( exp->name ) + 1;
    }
    /* write out the export ordinal table */
    for( i = 0; i < num_entries; ++i ) {
        exp = sort[i];
        if( exp->isanonymous ) continue;
        ord = sort[i]->ordinal - dir.ordinal_base;
        PutInfo( buf+pos, &ord, sizeof( ord ) );
        pos += sizeof( ord );
    }
    /* write out the export name table */
    for( i = 0; i < num_entries; ++i ) {
        exp = sort[i];
        if( exp->isanonymous ) continue;
        PutInfo( buf+pos, exp->name, strlen( exp->name) + 1 );
        pos += strlen( exp->name) + 1;
    }
    _LnkFree( sort );
#if 0 /* JWLink: exports */
    size = eat - object->rva;
    object->physical_size = ROUND_UP( size, header->file_align );
    header->table[PE_TBL_EXPORT].size = size;
    header->table[PE_TBL_EXPORT].rva = object->rva;
    header->image_size += ROUND_UP( size, header->object_align );
#else
    header->table[PE_TBL_EXPORT].size = pos;
    header->table[PE_TBL_EXPORT].rva = start;
#endif
    DEBUG(( DBG_OLD, "WriteExportInfo() exit" ));
}

#define PAGE_COUNT( size )  (((size)+(0x1000-1))>>0xC)

static unsigned_32 WriteRelocList( void **reloclist, unsigned_32 size,
                                   unsigned_32 pagerva, unsigned limit )
/**********************************************************************/
{
    unsigned_32 pagesize;
    bool        padme;

    while( limit > 0 ) {
        pagesize = RelocSize( *reloclist );
        if( pagesize != 0 ) {
            padme = FALSE;
            if( (pagesize / sizeof(pe_reloc_item)) & 0x1 ) {
                pagesize += sizeof(pe_reloc_item);
                padme = TRUE;
            }
            pagesize += 2*sizeof(unsigned_32);
            WriteLoad( &pagerva, sizeof(unsigned_32) );
            WriteLoad( &pagesize, sizeof(unsigned_32) );
            DumpRelocList( *reloclist );
            if( padme ) {
                PadLoad( sizeof(pe_reloc_item) );
            }
            size += pagesize;
        }
        pagerva += OSF_PAGE_SIZE;
        reloclist++;
        limit--;
    }
    return( size );
}

static void WriteFixupInfo( pe_header *header, pe_object *object )
/*****************************************************************/
/* dump the fixup table */
{
    unsigned_32         numpages;
    unsigned_32         highidx;
    unsigned_32         pagerva;
    group_entry         *group;
    void ***            reloclist;
    unsigned long       size;
    unsigned long       count;

    strncpy( object->name, ".reloc", PE_OBJ_NAME_LEN );
    object->physical_offset = NullAlign( header->file_align );
    object->rva = header->image_size;
    object->flags = PE_OBJ_INIT_DATA | PE_OBJ_READABLE | PE_OBJ_DISCARDABLE;
    size = 0;
    count = 0;
    for( group = Groups; group != NULL; group = group->next_group ) {
        reloclist = group->g.grp_relocs;
        if( reloclist != NULL ) {
            pagerva = group->linear;
            numpages = PAGE_COUNT( group->size );
            highidx = OSF_RLIDX_HIGH( numpages );
            while( highidx > 0 ) {
                size = WriteRelocList(*reloclist, size, pagerva, OSF_RLIDX_MAX);
                highidx--;
                reloclist++;
                pagerva += OSF_PAGE_SIZE * ((unsigned_32) OSF_RLIDX_MAX);
            }
            size = WriteRelocList( *reloclist, size, pagerva,
                                                     OSF_RLIDX_LOW(numpages) );
        }
    }
    if ( size == 0 ) {
        size = sizeof(pe_fixup_header);
        pagerva = 0;
        WriteLoad( &pagerva, sizeof(unsigned_32) );
        WriteLoad( &size, sizeof(unsigned_32) );
    }
    PadLoad( sizeof(pe_fixup_header) );
    object->virtual_size = size;
    object->physical_size = ROUND_UP( size, header->file_align );
    /* jwlink: set virtual size of base relocation section */
    header->table[PE_TBL_FIXUP].size = size;
    header->table[PE_TBL_FIXUP].rva = object->rva;
    header->image_size += ROUND_UP( size, header->object_align );
}

static void WriteDescription( pe_header *header, pe_object *object )
/******************************************************************/
{
    size_t      desc_len;

    desc_len = strlen( FmtData.u.os2.description );
    strncpy( object->name, ".desc", PE_OBJ_NAME_LEN );
    object->physical_offset = NullAlign( header->file_align );
    object->rva = header->image_size;
    object->flags = PE_OBJ_INIT_DATA | PE_OBJ_READABLE;
    object->physical_size = ROUND_UP( desc_len, header->file_align );
    WriteLoad( FmtData.u.os2.description, desc_len );
    header->image_size += ROUND_UP( desc_len, header->object_align );
}

void *RcMemMalloc( size_t size )
{
    void        *retval;

    _ChkAlloc( retval, size );
    return( retval );
}

void *RcMemRealloc( void *old_ptr, size_t newsize )
{
    _LnkReAlloc( old_ptr, old_ptr, newsize );
    return( old_ptr );
}

void RcMemFree( void *ptr )
{
    _LnkFree( ptr );
}

int  RcWrite( int hdl, const void *buf, size_t len )
{
    hdl = hdl;
    WriteLoad( (void *) buf, len );
    return( len );
}

long RcSeek( int hdl, long off, int pos )
{
    DbgAssert( pos != SEEK_END );
    DbgAssert( !(pos == SEEK_CUR && off < 0) );

    if( hdl == Root->outfile->handle ) {
        if( pos == SEEK_CUR ) {
            PadLoad( pos );
        } else {
            SeekLoad( off );
        }
    } else {
        QLSeek( hdl, off, pos, "resource file" );
    }
    if( pos == SEEK_CUR ) {
        return( off + pos );
    } else {
        return( pos );
    }
}

long RcTell( int hdl )
{
    DbgAssert( hdl == Root->outfile->handle );

    hdl = hdl;
    return( PosLoad() );
}

int RcPadFile( int handle, long pad )
{
    DbgAssert( handle == Root->outfile->handle );

    handle = handle;
    PadLoad( pad );
    return( FALSE );
}

void CheckDebugOffset( ExeFileInfo *info )
{
    info = info;
}

RcStatus CopyExeData( int inhandle, int outhandle, uint_32 length )
/*****************************************************************/
{
    outhandle = outhandle;
    while( length > MAX_HEADROOM ) {
        QRead( inhandle, TokBuff, MAX_HEADROOM, "resource file" );
        WriteLoad( TokBuff, MAX_HEADROOM );
        length -= MAX_HEADROOM;
    }
    if( length > 0 ) {
        QRead( inhandle, TokBuff, length, "resource file" );
        WriteLoad( TokBuff, length );
    }
    return( RS_OK );
}

void DoAddResource( char *name )
/*************************************/
{
    list_of_names       *info;
    unsigned            len;

    len = strlen( name );
    _PermAlloc( info, sizeof(list_of_names) + len );
    memcpy( info->name, name, len + 1 );
    info->next_name = FmtData.u.pe.resources;
    FmtData.u.pe.resources = info;
}

static void WritePEResources( pe_header *header, pe_object *object )
/******************************************************************/
{
    ExeFileInfo einfo;
    ResFileInfo *rinfo;
    int         allopen;
    int         status;

    memset( &einfo, 0, sizeof(einfo) );

    if( FmtData.resource != NULL ) {
        DoAddResource( FmtData.resource );
        FmtData.resource = NULL;
    }
    status = OpenResFiles( (ExtraRes *) FmtData.u.pe.resources, &rinfo,
                           &allopen, RC_TARGET_OS_WIN32, Root->outfile->fname );
    if( !status )               // we had a problem opening
        return;
    einfo.IsOpen = TRUE;
    einfo.Handle = Root->outfile->handle;
    einfo.name = Root->outfile->fname;
    einfo.u.PEInfo.WinHead = header;
    einfo.Type = EXE_TYPE_PE;
    status = BuildResourceObject( &einfo, rinfo, object, header->image_size,
                                  NullAlign( header->file_align ), !allopen );
    /* jwlink: added. PE resource section size */
    object->virtual_size = einfo.u.PEInfo.Res.ResSize;
    header->table[PE_TBL_RESOURCE].size = einfo.u.PEInfo.Res.ResSize;
    CloseResFiles( rinfo );
    header->image_size += ROUND_UP(object->physical_size, header->object_align);
}

static void WriteDebugTable( pe_header *header, pe_object *object, const char *symfilename )
/******************************************************************************************/
{
    int                 num_entries = 2;
    debug_directory     dir;

    DEBUG(( DBG_OLD, "WriteDebugTable() enter - write PE debug directory" ));
    if( symfilename != NULL )
        num_entries--;
    strncpy( object->name, ".rdata", PE_OBJ_NAME_LEN );
    object->physical_offset = NullAlign( header->file_align );
    object->rva = header->image_size;
    object->flags = PE_OBJ_INIT_DATA | PE_OBJ_READABLE;
    object->physical_size = ROUND_UP( num_entries * sizeof( debug_directory ), header->file_align);

    /* write debug dir entry for DEBUG_TYPE_MISC */
    dir.flags = 0;
    dir.time_stamp = header->time_stamp;
    dir.major = 0;
    dir.minor = 0;
    dir.debug_type = DEBUG_TYPE_MISC;
    dir.debug_size = sizeof( debug_misc_dbgdata );
    dir.data_rva = 0;
    dir.data_seek = object->physical_offset + object->physical_size;
    WriteLoad( &dir, sizeof( debug_directory ) );

    /* remember current file offset of this directory entry for later use */
    CVDebugDirEntryPos = PosLoad();

    if( symfilename == NULL ) {
        /* write debug dir entry for DEBUG_TYPE_CODEVIEW */
        dir.flags = 0;
        dir.time_stamp = header->time_stamp;
        dir.major = 0;
        dir.minor = 0;
        dir.debug_type = DEBUG_TYPE_CODEVIEW;
        dir.debug_size = CVSize;
        dir.data_rva = 0;
        dir.data_seek = object->physical_offset + object->physical_size + sizeof( debug_misc_dbgdata );
        WriteLoad( &dir, sizeof( debug_directory ) );
    }

    header->table[PE_TBL_DEBUG].size = num_entries * sizeof( debug_directory );
    header->table[PE_TBL_DEBUG].rva = object->rva;
    header->image_size += ROUND_UP( num_entries * sizeof( debug_directory ), header->object_align );
}

static void CheckNumRelocs( void )
/********************************/
// don't want to generate a .reloc section if we don't have any relocs
{
    group_entry *group;
    symbol      *sym;

    if( !(LinkState & MAKE_RELOCS) )
        return;
    for( group = Groups; group != NULL; group = group->next_group ) {
        if( group->g.grp_relocs != NULL ) {
            return;
        }
    }
    WALK_IMPORT_SYMBOLS( sym ) {
        if( LinkState & HAVE_MACHTYPE_MASK ) {
            return;
        }
    }
	//LinkState &= ~MAKE_RELOCS; /* jwlink: don't set "RELOCS stripped" if no relocs */
}

static seg_leader *SetLeaderTable( char *name, pe_hdr_table_entry *entry )
/*************************************************************************/
{
    seg_leader *leader;

    leader = FindSegment( Root, name );
    if( leader != NULL ) {
        entry->rva =  leader->group->linear + GetLeaderDelta( leader );
        entry->size = leader->size;
#if 1 /* JWLink: debug msg */
        //printf("SetLeaderTable(%s): rva=%Xh, size=%Xh\n", name, entry->rva, entry->size );
    } else {
        //printf("SetLeaderTable(%s): not found!\n", name );
#endif
    }
    return( leader );
}

static int CmpDesc( virt_mem a, virt_mem b )
/******************************************/
{
    unsigned_32 a32;
    unsigned_32 b32;

    GET32INFO( *((virt_mem *)a), a32 );
    GET32INFO( *((virt_mem *)b), b32 );
    return( (signed_32)a32 - b32 );
}

static void SwapDesc( virt_mem a, virt_mem b )
/********************************************/
{
    procedure_descriptor        tmp;

    a = *((virt_mem *)a);
    b = *((virt_mem *)b);
    ReadInfo( a, &tmp, sizeof(procedure_descriptor) );
    CopyInfo( a, b, sizeof(procedure_descriptor) );
    PutInfo( b, &tmp, sizeof(procedure_descriptor) );
}

static bool SetPDataArray( void *_sdata, void *_array )
/*****************************************************/
{
    segdata    *sdata = _sdata;
    virt_mem  **array = _array;
    offset      size;
    virt_mem    data;

    if( !sdata->isdead ) {
        size = sdata->length;
        data = sdata->data;
        while( size >= sizeof(procedure_descriptor) ) {
            **array = data;
            *array += 1;
            data += sizeof(procedure_descriptor);
            size -= sizeof(procedure_descriptor);
        }
    }
    return( FALSE );
}

static void SetMiscTableEntries( pe_header *hdr )
/***********************************************/
{
    seg_leader  *leader;
    virt_mem    *sortarray;
    virt_mem    *temp;
    unsigned    numpdatas;
    symbol      *sym;

#if 0 /* JWLink: import group */
    SetLeaderTable( IDataGrpName, &hdr->table[PE_TBL_IMPORT] );
#else
    SetLeaderTable( CoffIDataSegName, &hdr->table[PE_TBL_IMPORT] );
#endif
    sym = FindISymbol( TLSSym );
    if( sym != NULL ) {
        hdr->table[PE_TBL_THREAD].rva = FindLinearAddr( &sym->addr );
        hdr->table[PE_TBL_THREAD].size = sym->p.seg->length;
    }
    /* 64-bit also may have .pdata, but it's handled differently */
    if ( FmtData.u.pe.win64 )
        return;
    leader = SetLeaderTable( CoffPDataSegName, &hdr->table[PE_TBL_EXCEPTION] );
    /* The .pdata section may end up being empty if the symbols got optimized out */
    if( leader != NULL && leader->size ) {
        numpdatas = leader->size / sizeof(procedure_descriptor);
        _ChkAlloc( sortarray, numpdatas * sizeof(virt_mem *) );
        temp = sortarray;
        RingLookup( leader->pieces, SetPDataArray, &temp );
        VMemQSort( (virt_mem) sortarray, numpdatas, sizeof(virt_mem *),
                   SwapDesc, CmpDesc );
        _LnkFree( sortarray );
    }
}

static unsigned FindNumObjects( void )
/************************************/
{
    unsigned            num_objects;

    num_objects = NumGroups;
    if( LinkState & MAKE_RELOCS ) ++num_objects;
#if 0 /* JWLink: export section is already created */
    if( FmtData.u.os2.exports != NULL ) ++num_objects;
#endif
    if( LinkFlags & CV_DBI_FLAG ) ++num_objects;
    if( FmtData.u.os2.description != NULL ) ++num_objects;
    if( FmtData.resource != NULL || FmtData.u.pe.resources != NULL ) ++num_objects;
    return( num_objects );
}

static unsigned long CalcPEChecksum( unsigned long dwInitialCount, unsigned short *pwBuffer, unsigned long dwWordCount )
{
    unsigned long      __wCrc      = dwInitialCount;
    unsigned short     *__pwBuffer = pwBuffer;
    unsigned long      __dwCount   = dwWordCount;

    while( 0 != __dwCount-- ) {
        __wCrc += *__pwBuffer++;

        __wCrc = ( __wCrc & 0x0000FFFF ) + ( __wCrc >> 16 );
    }

    __wCrc = ( ( __wCrc >> 16 ) + __wCrc );

    return( __wCrc & 0x0000FFFF );
}

void FiniPELoadFile( void )
/********************************/
/* make a PE executable file */
{
    pe_header   exe_head;
    pe_header64 exe_head64;
    unsigned_32 stub_len;
    pe_object   *object;
    unsigned    num_objects;
    pe_object   *tbl_obj;
    unsigned    head_size;

    DEBUG(( DBG_OLD, "FiniPELoadFile() enter" ));
#if 1 /* JWLink: don't check # of relocs if dll */
    if (!FmtData.dll)
#endif
        CheckNumRelocs();
    num_objects = FindNumObjects();

    if ( FmtData.u.pe.os2.segment_shift == -1 )
        FmtData.u.pe.os2.segment_shift = DEFAULT_SEG_SHIFT;
#if 0 /* jwlink: the alignment is checked against segment alignment */
    /*
     *  I have changed this to allow programmers to control this shift. MS has 0x20 byte segments
     *  in some drivers! Who are we to argue? Never mind it's against the PE spec.
     */
    if( FmtData.u.pe.os2.segment_shift < MINIMUM_SEG_SHIFT ) {
        LnkMsg( WRN+MSG_VALUE_INCORRECT, "s", "alignment" );
    }
#endif

    head_size = sizeof(pe_header);
    memset( &exe_head, 0, head_size ); /* zero all header fields */
    if( FmtData.u.pe.tnt ) {
        exe_head.signature = PL_SIGNATURE;
    } else if( FmtData.u.pe.hx ) {
        exe_head.signature = PX_SIGNATURE;
    } else {
        exe_head.signature = PE_SIGNATURE;
    }
    if( LinkState & HAVE_I86_CODE ) {
        exe_head.cpu_type = PE_CPU_386;
    } else if( LinkState & HAVE_ALPHA_CODE ) {
        exe_head.cpu_type = PE_CPU_ALPHA;
    } else {
        exe_head.cpu_type = PE_CPU_POWERPC;
    }
    exe_head.magic = 0x10b; /* PE32 */
    exe_head.num_objects = num_objects;
    exe_head.time_stamp = time( NULL );
    exe_head.nt_hdr_size = head_size - offsetof(pe_header,flags)
        - sizeof(exe_head.flags);
    /* MS link won't set reverse byte flag */
    //exe_head.flags = PE_FLG_REVERSE_BYTE_LO | PE_FLG_32BIT_MACHINE;
    exe_head.flags = PE_FLG_32BIT_MACHINE;
#if 1 /* JWLink */
    exe_head.flags |= PE_FLG_LINNUM_STRIPPED | PE_FLG_LOCALS_STRIPPED;
    if (( FmtData.u.pe.win64 && (!FmtData.u.pe.nolargeaddressaware)) ||
        ( (!FmtData.u.pe.win64) && FmtData.u.pe.largeaddressaware ))
        exe_head.flags |= PE_FLG_LARGEADDRESSAWARE;
#endif
    if( !(LinkState & MAKE_RELOCS) ) {
        exe_head.flags |= PE_FLG_RELOCS_STRIPPED;
    }
    if( !(LinkState & LINK_ERROR) ) {
        exe_head.flags |= PE_FLG_IS_EXECUTABLE;
    }
    if( FmtData.dll ) {
        exe_head.flags |= PE_FLG_LIBRARY;
        /* the INIT/TERM flags are obsolete! */
        if( FmtData.u.os2.flags & INIT_INSTANCE_FLAG ) {
            exe_head.dll_flags |= PE_DLL_PERPROC_INIT;
        } else if( FmtData.u.os2.flags & INIT_THREAD_FLAG ) {
            exe_head.dll_flags |= PE_DLL_PERTHRD_INIT;
        }
        if( FmtData.u.os2.flags & TERM_INSTANCE_FLAG ) {
            exe_head.dll_flags |= PE_DLL_PERPROC_TERM;
        } else if( FmtData.u.os2.flags & TERM_THREAD_FLAG ) {
            exe_head.dll_flags |= PE_DLL_PERTHRD_TERM;
        }
    }
    if ( FmtData.u.pe.nxcompat )
        exe_head.dll_flags |= PE_DLL_NXCOMPAT;

    if( FmtData.u.pe.lnk_specd ) {
        exe_head.lnk_major = FmtData.u.pe.linkmajor;
        exe_head.lnk_minor = FmtData.u.pe.linkminor;
    } else {
        exe_head.lnk_major = PE_LNK_MAJOR;
        exe_head.lnk_minor = PE_LNK_MINOR;
    }
    exe_head.image_base = FmtData.base;
    exe_head.object_align = FmtData.objalign;

    exe_head.file_align = 1UL << FmtData.u.os2.segment_shift;
    if( FmtData.u.pe.osv_specd ) {
        exe_head.os_major = FmtData.u.pe.osmajor;
        exe_head.os_minor = FmtData.u.pe.osminor;
    } else {
#if 1 /* JWLink */
        exe_head.os_major = 4;
        exe_head.os_minor = 0;
#else
        exe_head.os_major = PE_OS_MAJOR;
        exe_head.os_minor = PE_OS_MINOR + 0xb;      // KLUDGE!
#endif
    }
    exe_head.user_major = FmtData.major;
    exe_head.user_minor = FmtData.minor;
    if( FmtData.u.pe.sub_specd ) {
        exe_head.subsys_major = FmtData.u.pe.submajor;
        exe_head.subsys_minor = FmtData.u.pe.subminor;
    } else {
#if 1 /* JWLink */
        exe_head.subsys_major = 4;
        exe_head.subsys_minor = 0;
#else
        exe_head.subsys_major = 3;
        exe_head.subsys_minor = 0xa;
#endif
    }
    if( FmtData.u.pe.subsystem != PE_SS_UNKNOWN ) {
        exe_head.subsystem = FmtData.u.pe.subsystem;
    } else {
        exe_head.subsystem = PE_SS_WINDOWS_CHAR;
    }
    exe_head.stack_reserve_size = StackSize;
    if( FmtData.u.pe.stackcommit == PE_DEF_STACK_COMMIT ) {
#if 1 /* JWLink */
        if ( StackSize > 0x1000 )
            exe_head.stack_commit_size = 0x1000;
        else
#endif
            exe_head.stack_commit_size = StackSize;
#if 0 /* JWLink */
        if( exe_head.stack_commit_size > (64*1024UL) ) {
            exe_head.stack_commit_size = 64*1024UL;
        }
#endif
    } else if( FmtData.u.pe.stackcommit > StackSize ) {
        exe_head.stack_commit_size = StackSize;
    } else {
        exe_head.stack_commit_size = FmtData.u.pe.stackcommit;
    }
    exe_head.heap_reserve_size = FmtData.u.os2.heapsize;
    if( FmtData.u.pe.heapcommit > FmtData.u.os2.heapsize ) {
        exe_head.heap_commit_size = FmtData.u.os2.heapsize;
    } else {
        exe_head.heap_commit_size = FmtData.u.pe.heapcommit;
    }
    exe_head.num_tables = PE_TBL_NUMBER;

    if ( FmtData.u.pe.win64 ) {
        head_size = sizeof(pe_header64);
        memset( &exe_head64, 0, head_size ); /* zero all header fields */
        exe_head64.signature = PE_SIGNATURE;
        exe_head64.cpu_type = PE_CPU_AMD64;
        exe_head64.magic = 0x20b;
        exe_head64.num_objects = num_objects;
        exe_head64.time_stamp = time( NULL );
        exe_head64.nt_hdr_size = head_size - offsetof(pe_header64,flags)
            - sizeof(exe_head64.flags);

        exe_head64.flags = exe_head.flags;

        if( FmtData.u.pe.lnk_specd ) {
            exe_head64.lnk_major = FmtData.u.pe.linkmajor;
            exe_head64.lnk_minor = FmtData.u.pe.linkminor;
        } else {
            exe_head64.lnk_major = PE_LNK_MAJOR;
            exe_head64.lnk_minor = PE_LNK_MINOR;
        }
        exe_head64.image_base = FmtData.base;
        exe_head64.object_align = FmtData.objalign;
        exe_head64.file_align = 1UL << FmtData.u.os2.segment_shift;
        if( FmtData.u.pe.osv_specd ) {
            exe_head64.os_major = FmtData.u.pe.osmajor;
            exe_head64.os_minor = FmtData.u.pe.osminor;
        } else {
            exe_head64.os_major = 4;
            exe_head64.os_minor = 0;
        }
        exe_head64.user_major = FmtData.major;
        exe_head64.user_minor = FmtData.minor;
        if( FmtData.u.pe.sub_specd ) {
            exe_head64.subsys_major = FmtData.u.pe.submajor;
            exe_head64.subsys_minor = FmtData.u.pe.subminor;
        } else {
            exe_head64.subsys_major = 5;
            exe_head64.subsys_minor = 1; /* is this the expected default? */
        }
        if( FmtData.u.pe.subsystem != PE_SS_UNKNOWN ) {
            exe_head64.subsystem = FmtData.u.pe.subsystem;
        } else {
            /* perhaps it's ok to display a warning here? */
            exe_head64.subsystem = PE_SS_WINDOWS_CHAR;
        }
        exe_head64.stack_reserve_size = StackSize;
        if( FmtData.u.pe.stackcommit == PE_DEF_STACK_COMMIT ) {
            if ( StackSize > 0x1000 )
                exe_head64.stack_commit_size = 0x1000;
            else
                exe_head64.stack_commit_size = StackSize;
        } else if( FmtData.u.pe.stackcommit > StackSize ) {
            exe_head64.stack_commit_size = StackSize;
        } else {
            exe_head64.stack_commit_size = FmtData.u.pe.stackcommit;
        }
        exe_head64.heap_reserve_size = FmtData.u.os2.heapsize;
        if( FmtData.u.pe.heapcommit > FmtData.u.os2.heapsize ) {
            exe_head64.heap_commit_size = FmtData.u.os2.heapsize;
        } else {
            exe_head64.heap_commit_size = FmtData.u.pe.heapcommit;
        }
        exe_head64.num_tables = PE_TBL_NUMBER;
    }

    CurrSect = Root;
    SeekLoad( 0 );
    stub_len = Write_Stub_File( STUB_ALIGN );
    _ChkAlloc( object, num_objects * sizeof( pe_object ) );
    memset( object, 0, num_objects * sizeof( pe_object ) );
    /* leave space for the header and object table */
    PadLoad( head_size + num_objects * sizeof(pe_object) );
    GenPETransferTable();
    WriteImportInfo();
#if 1 /* JWLink */
    WriteExportInfo( &exe_head );
#endif
    SetMiscTableEntries( &exe_head );
    WriteDataPages( &exe_head, object ); /* may set exe_head.entry_rva */
    tbl_obj = &object[ NumGroups ];
#if 0 /* JWLink: exports are already written */
    if( FmtData.u.os2.exports != NULL ) {
        WriteExportInfo( &exe_head, tbl_obj );
        ++tbl_obj;
    }
#endif
    if( LinkState & MAKE_RELOCS ) {
        WriteFixupInfo( &exe_head, tbl_obj );
        ++tbl_obj;
    }
    if( FmtData.u.os2.description != NULL ) {
        WriteDescription( &exe_head, tbl_obj );
        ++tbl_obj;
    }
    if( FmtData.resource || FmtData.u.pe.resources != NULL ) {
        WritePEResources( &exe_head, tbl_obj );
        ++tbl_obj;
    }
    if( LinkFlags & CV_DBI_FLAG ) {
        WriteDebugTable( &exe_head, tbl_obj, SymFileName );
        ++tbl_obj;
    }
    NullAlign( exe_head.file_align ); /* pad out last page */
    exe_head.header_size = object->physical_offset;
    exe_head64.header_size = object->physical_offset;
    DBIWrite();
    SeekLoad( stub_len );

    if( FmtData.u.pe.checksumfile ) {
        exe_head.file_checksum = 0L;    /* Ensure checksum is 0 before we calculate it */
        exe_head64.file_checksum = 0L;    /* Ensure checksum is 0 before we calculate it */
    }

    if ( FmtData.u.pe.win64 ) {
        exe_head64.entry_rva = exe_head.entry_rva;
        exe_head64.code_size = exe_head.code_size;
        exe_head64.init_data_size = exe_head.init_data_size;
        exe_head64.uninit_data_size = exe_head.uninit_data_size;
        exe_head64.code_base = exe_head.code_base;
        exe_head64.image_size = exe_head.image_size;
        memcpy( &exe_head64.table, &exe_head.table, sizeof ( exe_head.table ) );
        WriteLoad( &exe_head64, head_size );
    } else
        WriteLoad( &exe_head, head_size );
    WriteLoad( object, num_objects * sizeof( pe_object ) );

    if( FmtData.u.pe.checksumfile ) {
        unsigned long   crc = 0L;
        unsigned long   buffsize;
        unsigned long   currpos = 0L;
        unsigned long   totalsize = 0L;
        outfilelist     *outfile;
        char            *buffer = NULL;
        /*
         *  Checksum required. We have already written the EXE header with a NULL checksum
         *  We need to calculate the checksum over all blocks
         *  We flush the buffers by seeking back to 0, then repeatedly reading all the file back in
         *  and checksumming it. The MS checksum is completed by adding the total file size to the
         *  calculated CRC. We then add this to the header and rewrite the header.
         */
        SeekLoad( 0 ); /* Flush the buffer */
        outfile = CurrSect->outfile;
        DbgAssert( outfile->buffer == NULL );

        totalsize = QFileSize( outfile->handle );

#define CRC_BUFF_SIZE   (16*1024)
        _ChkAlloc( buffer, CRC_BUFF_SIZE );

        if( buffer ) {
            while( currpos < totalsize ) {
                memset( buffer, 0, CRC_BUFF_SIZE );
                buffsize = QRead( outfile->handle, buffer, CRC_BUFF_SIZE, outfile->fname );
                DbgAssert( ( buffsize % 2 ) != 1 ); /* check for odd length */
                currpos += buffsize;

                crc = CalcPEChecksum( crc, (unsigned short *)buffer, (buffsize / sizeof(unsigned short)) );
            }

            _LnkFree( buffer );
            crc += totalsize;

            exe_head.file_checksum = crc;
            exe_head64.file_checksum = crc;
            SeekLoad( stub_len );
            if ( FmtData.u.pe.win64 )
                WriteLoad( &exe_head64, head_size );
            else
                WriteLoad( &exe_head, head_size );
        }
    }

    _LnkFree( object );
}

unsigned long GetPEHeaderSize( void )
/******************************************/
{
    unsigned long       size;
    unsigned            num_objects;

    num_objects = FindNumObjects();
    size = ROUND_UP( GetStubSize(), STUB_ALIGN );
    size += sizeof( pe_header ) + num_objects * sizeof( pe_object );
    return( ROUND_UP( size, FmtData.objalign ) );
}

static void ReadExports( unsigned_32 namestart, unsigned_32 nameend,
                         unsigned_32 ordstart, unsigned numords,
                         unsigned ord_base, f_handle file, char *fname )
/***********************************************************************/
{
    unsigned_16         *ordbuf;
    unsigned_16         *ordptr;
    char                *nameptr;

    _ChkAlloc( ordbuf, numords * sizeof(unsigned_16) );
    QSeek( file, ordstart, fname );
    QRead( file, ordbuf, numords * sizeof(unsigned_16), fname );
    QSeek( file, namestart, fname );
    QRead( file, TokBuff, nameend - namestart, fname );
    nameptr = TokBuff,
    ordptr = ordbuf;
    while( numords > 0 ) {
        CheckExport( nameptr, *ordptr + ord_base, &strcmp );
        while( *nameptr != '\0' ) nameptr++;
        nameptr++;
        ordptr++;
        numords--;
    }
    _LnkFree( ordbuf );
}

void ReadPEExportTable( f_handle file, pe_hdr_table_entry *base )
/***********************************************************************/
/* read a PE export table, and set ordinal values accordingly. */
{
    pe_export_directory table;
    char                *fname;
    unsigned_32         *nameptrs;
    unsigned            nameptrsize;
    unsigned            numentries;
    unsigned_32         entrystart;
    unsigned_32         *curr;
    unsigned_32         namestart;

    fname = FmtData.u.os2.old_lib_name;
    QRead( file, &table, sizeof(pe_export_directory), fname );
    nameptrsize = table.num_name_ptrs * sizeof(unsigned_32);
    if( nameptrsize == 0 )                      /* NOTE: <-- premature return */
        return;
    _ChkAlloc( nameptrs, nameptrsize + sizeof(unsigned_32) );
    QSeek( file, table.name_ptr_table_rva - base->rva, fname );
    QRead( file, nameptrs, nameptrsize, fname );
    numentries = 1;
    entrystart = table.ordinal_table_rva - base->rva;
    curr = nameptrs;
    *curr -= base->rva;
    namestart = *curr++;
    nameptrsize -= sizeof(unsigned_32);
    while( nameptrsize > 0 ) {
        *curr -= base->rva;
        if( *curr - namestart > TokSize ) {
            ReadExports( namestart, *(curr - 1), entrystart, numentries,
                         table.ordinal_base, file, fname );
            entrystart += numentries * sizeof(unsigned_16);
            numentries = 1;
            namestart = *(curr - 1);
        }
        numentries++;
        curr++;
        nameptrsize -= sizeof(unsigned_32);
    }   /* NOTE! this assumes the name table is at the end */
    ReadExports( namestart, base->size + *nameptrs, entrystart, numentries,
                 table.ordinal_base, file, fname );
    _LnkFree( nameptrs );
}

static void CreateIDataSection( void )
/************************************/
{
    segdata     *sdata;
    class_entry *class;

    DEBUG(( DBG_OLD, "loadpe:CreateIDataSection() enter" ));
    PrepareToc();
    if( 0 != CalcIDataSize() ) {
		IDataGroup = GetGroup( IDataGrpName );
#if 1 /* JWLink */
        /* dont put idata into dgroup */
        class = FindClass( Root, ConstClassName, 1, 0, 0 );
        class->flags |= CLASS_IDATA | CLASS_LXDATA_SEEN;
#else
        class = FindClass( Root, CoffIDataSegName, 1, 0, 0 );
        class->flags |= CLASS_IDATA | CLASS_LXDATA_SEEN;
#endif
        sdata = AllocSegData();
        sdata->length = IData.total_size;
        sdata->u.name = CoffIDataSegName;
        sdata->align = ( FmtData.u.pe.win64 ? 4 : 2 );
        sdata->combine = COMBINE_ADD;
        sdata->is32bit = TRUE;
        sdata->isabs = FALSE;
        AddSegment( sdata, class );
        sdata->data = AllocStg( sdata->length );
        sdata->u.leader->segflags |= SEG_READ_ONLY;
        IData.sdata = sdata;
        AddToGroup( IDataGroup, sdata->u.leader );
        DEBUG(( DBG_OLD, "loadpe:CreateIDataSection() size=%h", IData.total_size ));
    }
}

#if 1 /* JWLink */
static offset CalcEDataSize( void )
/*******************************/
{
    unsigned_32    size;
    unsigned_32    names = 0;
    int            num_entries  = 0;
    int            num_names  = 0;
    int            num_eat_entries = 0;
    entry_export   *exp;
    char           *name;
    unsigned       high_ord;
    unsigned       namelen;

    /* there might be "holes" in the table */
    for( exp = FmtData.u.os2.exports; exp != NULL; exp = exp->next ) {
        high_ord = exp->ordinal; /* fixme: exp->ordinal not set yet? */
        ++num_entries;
        if( !(exp->isanonymous) ) { /* jwlink */
            num_names++;
            names += strlen( exp->name ) + 1;
        }
    }
    if ( num_entries == 0 )
        return( 0 );
    if ( FmtData.u.os2.exports->ordinal )
        num_eat_entries = high_ord - FmtData.u.os2.exports->ordinal + 1;
    else
        num_eat_entries = high_ord;

    if ( num_eat_entries < num_entries )
        num_eat_entries = num_entries;
    DEBUG(( DBG_OLD, "CalcEDataSize(): # of EAT entries=%h, # of names=%h, highest ordinal=%h, base ordinal=%h", num_eat_entries, num_entries, high_ord, FmtData.u.os2.exports->ordinal ));
    size = sizeof( pe_export_directory );
    if( FmtData.u.os2.res_module_name != NULL ) {
        name = FmtData.u.os2.res_module_name;
    } else {
        name = RemovePath( Root->outfile->fname, &namelen );
    }
    /* RemovePath strips the extension, which we don't want */
    namelen = strlen( name ) + 1;
    size += namelen;
    size = (size+3) & ~3;
    size += num_eat_entries * sizeof(pe_va) + num_names * ( sizeof(pe_va) + sizeof(unsigned_16));
    size += names;
    DEBUG(( DBG_OLD, "CalcEDataSize()=%h", size ));
    return( size );
}

static void CreateEDataSection( void )
/************************************/
{
    segdata     *sdata;
    int         size;
    class_entry *class;
    group_entry *EDataGroup;

    //PrepareToc();
    if( size = CalcEDataSize() ) {
        EDataGroup = GetGroup( ".rdata" );
        //class = FindClass( Root, CoffIDataSegName, 1, 0, 0 );
        //class = FindClass( Root, DataClassName, 1, 0, 0 );
        class = FindClass( Root, ConstClassName, 1, 0, 0 );
        sdata = AllocSegData();
        sdata->length = size;
        sdata->u.name = ".edata";
        sdata->align = ( FmtData.u.pe.win64 ? 4 : 2 );
        sdata->combine = COMBINE_ADD;
        sdata->is32bit = TRUE;
        sdata->isabs = FALSE;
        AddSegment( sdata, class );
        sdata->data = AllocStg( sdata->length );
        EData.sdata = sdata;
        AddToGroup( EDataGroup, sdata->u.leader );
        //printf("CreateEDataSection: size=%Xh\n", size );
    }
}
#endif

static void RegisterImport( dll_sym_info *sym )
/*********************************************/
{
    struct module_import        *mod;
    struct import_name          *imp;
    struct import_name          *chk;
    struct import_name          **owner;
    name_list                   *os2_imp;
    int                         cmp;
    unsigned                    len;

    for( mod = PEImpList; mod != NULL; mod = mod->next ) {
        if( mod->mod == sym->m.modnum ) {
            break;
        }
    }
    if( mod == NULL ) {
        ++NumMods;
        _PermAlloc( mod, sizeof( struct module_import ) );
        mod->next = PEImpList;
        PEImpList = mod;
        mod->mod = sym->m.modnum;
        mod->imports = NULL;
        mod->num_entries = 0;
    }
    if( !sym->isordinal ) {
        os2_imp = sym->u.entry;
    } else {
        os2_imp = NULL;
    }
    mod->num_entries++;
    _PermAlloc( imp, sizeof( struct import_name ) );
    imp->dll = sym;
    imp->imp = os2_imp;
    /* keep the list sorted by name for calculating hint values */
    owner = &mod->imports;
    if( os2_imp != NULL ) {
        for( ;; ) {
            chk = *owner;
            if( chk == NULL ) break;
            if( chk->imp != NULL ) {
                len = chk->imp->len;
                if( len > os2_imp->len ) len = os2_imp->len;
                cmp = memcmp( chk->imp->name, os2_imp->name, len );
                if( cmp > 0 ) break;
                if( cmp == 0 && len > chk->imp->len ) break;
            }
            owner = &chk->next;
        }
    } else {
        chk = *owner;
    }
    imp->next = chk;
    *owner = imp;
    ++NumImports;
}

static void SetConstGrp( void *_seg )
/***********************************/
{
    group_entry *group;
    seg_leader  *curr = _seg;

    if ( curr->group == NULL ) {
        group = GetGroup( ".rdata" );
        AddToGroup( group, curr );
    }
}

/* ChkPEData() is called just before final address calculation */

void ChkPEData( void )
/***************************/
{
    symbol      *sym;
    class_entry *class;
    class_entry *code = NULL;
    segdata     *sdata;
    int         glue_size;
    offset      size;

    DEBUG(( DBG_OLD, "ChkPEData() enter" ));
    /* find the last code class in the program;
     * and move "CONST" class members to .rdata group if they don't
     * belong to a group yet.
     */
    for( class = Root->classlist; class != NULL; class = class->next_class ) {
        if( class->flags & CLASS_CODE )
            code = class;
        else if( class->flags & CLASS_READ_ONLY ) {
            RingWalk( class->segs, SetConstGrp );
        }
    }
    if( code ) {
        CurrMod = FakeModule;
        size = 0;
        glue_size = GetTransferGlueSize(LinkState);
        WALK_IMPORT_SYMBOLS(sym) {
            if ( sym->info & SYM_REFERENCED ) {
                size += glue_size;
            }
            DEBUG(( DBG_OLD, "ChkPEData(): import=%s info=%h ts.size=%h", sym->name, sym->info, size ));
            RegisterImport( sym->p.import );
            DBIAddGlobal( sym );
        }
        size += NumLocalImports * sizeof( pe_va );
        if( size != 0 ) {
            code->flags |= CLASS_TRANSFER;
            sdata = AllocSegData();
            sdata->length = size;
            sdata->u.name = TRANSFER_SEGNAME;
            sdata->align = 2;
            sdata->combine = COMBINE_ADD;
            sdata->is32bit = TRUE;
            sdata->isabs = FALSE;
            AddSegment( sdata, code );
            sdata->data = AllocStg( sdata->length );
            XFerSegData = sdata;
            DEBUG(( DBG_OLD, "ChkPEData(): XFerSegData size=%h", size ));
        }
    }
    CreateIDataSection();
    CreateEDataSection(); /* new for jwlink */
    ChkOS2Data();  /* set segment flags */
    CurrMod = NULL;
    DEBUG(( DBG_OLD, "ChkPEData() exit" ));
}

void AllocPETransferTable( void )
/**************************************/
{
    symbol              *sym;
    class_entry         *class;
    group_entry         *group;
    seg_leader          *lead;
    segdata             *piece;
    segdata             *save;
    offset              off;
    segment             seg;
    int                 glue_size;
    local_import        *loc_imp;

    /*
     *  Moved export check here as otherwise flags don't get propagated
     */
    DEBUG(( DBG_OLD, "AllocPETransferTable() enter, IDataGroup=%h", IDataGroup ));
    ChkOS2Exports();
    if( IDataGroup == NULL ) {
        return;
    }
    class = Root->classlist;
    for( ; class; class = class->next_class ) {
        if( class->flags & CLASS_TRANSFER ) break;
    }
    if( class == NULL )
        XFerSegData = NULL;
	else {
		lead = RingLast( class->segs );
		piece = RingLast( lead->pieces );
		CurrMod = FakeModule;
		group = lead->group;
		seg = group->grp_addr.seg;
		off = group->grp_addr.off + group->totalsize;
		// now calc addresses for imported local symbols
		for( loc_imp = PELocalImpList; loc_imp != NULL; loc_imp = loc_imp->next ) {
			off -= sizeof( pe_va );
			loc_imp->iatsym->addr.off = off;
			loc_imp->iatsym->addr.seg = seg;
			save = loc_imp->locsym->p.seg;
			loc_imp->locsym->p.seg = piece;
			DBIGenGlobal( loc_imp->locsym, Root );
			loc_imp->locsym->p.seg = save;
		}
		glue_size = GetTransferGlueSize( LinkState );
		WALK_IMPORT_SYMBOLS( sym ) {
			if ( sym->info & SYM_REFERENCED ) {
				off -= glue_size;
				sym->addr.seg = seg;
				sym->addr.off = off;
				save = sym->p.seg;
				sym->p.seg = piece;
				DEBUG(( DBG_OLD, "AllocPETransferTable(): sym=%s off=%h", sym->name, off ));
				DBIGenGlobal( sym, Root );
				sym->p.seg = save;
			}
		}
	}
    off = CalcIATAbsOffset();   // now calc addresses for IAT symbols
    WalkImportsMods( CalcImpOff, &off );
    SetTocAddr( IData.eof_ilt_off, IDataGroup ); // Set toc's address.
    CurrMod = NULL;
    DEBUG(( DBG_OLD, "AllocPETransferTable() exit" ));
}

#define PREFIX_LEN (sizeof(ImportSymPrefix)-1)

void AddPEImportLocalSym( symbol *locsym, symbol *iatsym )
/********************************************************/
{
    local_import    *imp;

    /* an imported symbol is also defined locally */

    _ChkAlloc( imp, sizeof( local_import ) );
    LinkList( &PELocalImpList, imp );
    imp->iatsym = iatsym;
    imp->locsym = locsym;
    ++NumLocalImports;
}

bool ImportPELocalSym( symbol *iatsym )
/*************************************/
{
    char            *name;
    symbol          *locsym;

    name = iatsym->name;
    if( memcmp( name, ImportSymPrefix, PREFIX_LEN ) != 0 )
        return( FALSE );
    locsym = FindISymbol( name + PREFIX_LEN );
    if( locsym == NULL )
        return( FALSE );
    if( IS_SYM_IMPORTED( locsym ) )
        return( FALSE );
    LnkMsg( WRN+MSG_IMPORT_LOCAL, "s", locsym->name );
    iatsym->info |= SYM_DEFINED | SYM_DCE_REF;
    if( LinkFlags & STRIP_CODE ) {
        DefStripImpSym( iatsym );
    }
    AddPEImportLocalSym( locsym, iatsym );
    return( TRUE );
}

void FreePELocalImports( void )
/*****************************/
{
    FreeList( PELocalImpList );
    PELocalImpList = NULL;
    NumLocalImports = 0;
}
