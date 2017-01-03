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
* Description:  Object file processing routines specific to OMF.
*
****************************************************************************/


#include <string.h>
#include "linkstd.h"
#include "msg.h"
#include "wlnkmsg.h"
#include "alloc.h"
#include <pcobj.h>
#include "obj2supp.h"
#include "objnode.h"
#include "objcalc.h"
#include "objio.h"
#include "objcache.h"
#include "wcomdef.h"
#include "cmdline.h"
#include "loadfile.h"
#include "dbgall.h"
#include "objpass1.h"
#include "objstrip.h"
#include "omfreloc.h"
#include "carve.h"
#include "strtab.h"
#include "permdata.h"
#include "virtmem.h"
#include "impexp.h"
#include "objomf.h"
#include "specials.h"

/* forward declarations */

#if BORLAND_EXT==0
#define FindSegNode FindNode
#endif

static void     Pass1Cmd( byte, struct objbuff * );
static void     ProcTHEADR( struct objbuff * );
static void     Comment( struct objbuff * );
static void     AddNames( struct objbuff * );
static void     ProcSegDef( struct objbuff * );
static void     ProcPubdef( bool static_sym, struct objbuff * );
static void     UseSymbols( bool static_sym, bool iscextdef, struct objbuff * );
static void     DefineGroup( struct objbuff * );
static void     ProcLinnum( struct objbuff * );
static void     ProcLxdata( bool islidata, struct objbuff * );
static void     ProcModuleEnd( struct objbuff * );
static void     ProcAlias( struct objbuff * );
static void     DoLazyExtdef( bool isweak, struct objbuff * );
static void     ProcVFTableRecord( bool ispure, struct objbuff * );
static void     ProcVFReference( struct objbuff * );
static void     GetObject( segdata *seg, unsigned_32 obj_offset, bool lidata, struct objbuff * );

byte            OMFAlignTab[] = {0,0,1,4,8,2,12};

extern lobject_data CurrRec;

enum dll_entry_type { DLL_RELOC_NAME, DLL_RELOC_ORDINAL };

#if BORLAND_EXT
void * FindSegNode( NODEARRAY *list, unsigned index )
/*******************************************************/
{
#if 1
    if ( index > 0x4000 ) {
        LnkMsg( LOC_REC+FTL+MSG_VIRDEF_UNSUPPORTED, NULL );
    }
    return( FindNode( list, index ) );
#else
    return( FindNode( list, index > 0x4000 ? index - 0x4000 : index ) );
#endif
}

#endif


void ResetObjOMF( void )
/**********************/
{
//    ObjBuff = NULL;
//    EOObjRec = NULL;
}

static unsigned long ProcObj( file_list *file, unsigned long loc,
                              void (*procrtn)( byte, struct objbuff * ) )
/****************************************************************/
/* Process an object file. */
{
    obj_record          *rec;
    byte                cmd;
    unsigned_16         len;
    struct objbuff      ob;


    RecNum = 0;
    do {
        ObjFormat &= ~FMT_MS_386;   // assume not a Microsoft 386 .obj file
        rec = CacheRead( file, loc, sizeof(obj_record) );
        if( rec == NULL ) {
            EarlyEOF();
            break;
        }
        loc += sizeof( obj_record );
        len = rec->length;
        cmd = rec->command;
        if( procrtn != NULL ) {
            RecNum++;
            ob.curr = CacheRead( file, loc, len );
            if( ob.curr == NULL ) {
                EarlyEOF();
                break;
            }
            ob.end = ob.curr + len - 1;       // 1 for the checksum.
            (*procrtn)( cmd, &ob );           /* process the record */
            if( ob.curr > ob.end ) {
                DEBUG((DBG_OLD, "objomf.ProcObj(): error, record size invalid" ));
                BadObject();
                break;
            }
        }
        loc += len;
    } while( cmd != CMD_MODEND && cmd != CMD_MODE32 );
    return( loc );
}

static void CheckUninit( void *_seg, void *dummy )
/************************************************/
{
    segnode *seg = _seg;

    dummy = dummy;
    if( !(seg->info & SEG_LXDATA_SEEN) ) {
        seg->entry->isuninit = TRUE;
        if( seg->entry->data ) {
            ReleaseInfo( seg->entry->data );
            seg->entry->data = 0;
        }
    }
}

unsigned long OMFPass1( void )
/***********************************/
// do pass 1 for OMF object files
{
    unsigned long retval;

	DEBUG((DBG_OLD, "objomf.OMFPass1(): enter" ));
    PermStartMod( CurrMod );
    if( LinkState & (HAVE_MACHTYPE_MASK & ~HAVE_I86_CODE) ) {
        LnkMsg( WRN+MSG_MACHTYPE_DIFFERENT, "s", CurrMod->f.source->file->name);
    } else {
        LinkState |= HAVE_I86_CODE;
    }
    CurrMod->omfdbg = OMF_DBG_CODEVIEW; // Assume MS style LINNUM records
    retval = ProcObj( CurrMod->f.source, CurrMod->location, &Pass1Cmd );
    IterateNodelist( SegNodes, CheckUninit, NULL );
    ResolveComdats();
	DEBUG((DBG_OLD, "objomf.OMFPass1(): exit" ));
    return( retval );
}

static void Pass1Cmd( byte cmd, struct objbuff *ob )
/******************************/
/* Process an object record for pass 1 */
{
    switch( cmd ) {
    case CMD_THEADR:
        ProcTHEADR( ob );
        break;
    case CMD_COMENT:
        Comment( ob );
        break;
    case CMD_LLNAME:
    case CMD_LNAMES:
        AddNames( ob );
        break;
    case CMD_SEGD32:
        ObjFormat |= FMT_MS_386;
    case CMD_SEGDEF:
        CurrMod->modinfo |= MOD_NEED_PASS_2;
        ProcSegDef( ob );
        break;
    case CMD_STATIC_PUBD32:
        ObjFormat |= FMT_MS_386;
    case CMD_STATIC_PUBDEF:
        ProcPubdef( TRUE, ob );
        break;
    case CMD_PUBD32:
        ObjFormat |= FMT_MS_386;
    case CMD_PUBDEF:
        ProcPubdef( FALSE, ob );
        break;
    case CMD_STATIC_EXTDEF:
    case CMD_STATIC_EXTD32:
    case CMD_EXTDEF:
        CurrMod->modinfo |= MOD_NEED_PASS_2;
        UseSymbols( ( cmd == CMD_EXTDEF ? FALSE : TRUE ), FALSE, ob );
        break;
    case CMD_CEXTDF:
        CurrMod->modinfo |= MOD_NEED_PASS_2;
        UseSymbols( FALSE, TRUE, ob );
        break;
    case CMD_GRPDEF:
        DefineGroup( ob );
        break;
    case CMD_LINN32:
        ObjFormat |= FMT_MS_386;
    case CMD_LINNUM:
		if ( CurrMod->omfdbg == OMF_DBG_CODEVIEW ) {
			DEBUG((DBG_OLD, "objomf.Pass1Cmd(): LINNUM record found" ));
			ProcLinnum( ob );
		}
        break;
    case CMD_LINS32:
        ObjFormat |= FMT_MS_386;
    case CMD_LINSYM:
        ProcLinsym( ob );
        break;
    case CMD_STATIC_COMDEF:
    case CMD_COMDEF:
        CurrMod->modinfo |= MOD_NEED_PASS_2;
        ProcComdef( (cmd == CMD_COMDEF ? FALSE : TRUE ), ob );
        break;
    case CMD_COMD32:
        ObjFormat |= FMT_MS_386;
    case CMD_COMDAT:
        CurrMod->modinfo |= MOD_NEED_PASS_2;
        ProcComdat( ob );
        break;
    case CMD_LEDA32:
        ObjFormat |= FMT_MS_386;
    case CMD_LEDATA:
        ProcLxdata( FALSE, ob );
        break;
    case CMD_LIDA32:
        ObjFormat |= FMT_MS_386;
    case CMD_LIDATA:
        ProcLxdata( TRUE, ob );
        break;
    case CMD_FIXU32:
        ObjFormat |= FMT_MS_386;
    case CMD_FIXUP:         /* count the fixups for each seg_leader */
        CurrMod->modinfo |= MOD_NEED_PASS_2;
        DoRelocs( ob );
        ObjFormat &= ~FMT_UNSAFE_FIXUPP;
        break;
    case CMD_MODE32:
        ObjFormat |= FMT_MS_386;
    case CMD_MODEND:
        ProcModuleEnd( ob );
        break;
    case CMD_ALIAS:
        ProcAlias( ob );
        break;
    case CMD_VERNUM:
    case CMD_VENDEXT:
    case CMD_BAKPAT:
    case CMD_BAKP32:
    case CMD_NBKPAT:
    case CMD_NBKP32:    /* ignore bakpats in pass 1 */
    case CMD_LOCSYM:
    case CMD_TYPDEF:
    case CMD_DEBSYM:
    case CMD_BLKDEF:
    case CMD_BLKD32:
    case CMD_BLKEND:
    case CMD_BLKE32:
        /* ignore the Intel debugging records */
        break;
    case CMD_RHEADR:
    case CMD_REGINT:
    case CMD_REDATA:
    case CMD_RIDATA:
    case CMD_OVLDEF:
    case CMD_ENDREC:
    case CMD_LHEADR:
    case CMD_PEDATA:
    case CMD_PIDATA:
    case CMD_LIBHED:
    case CMD_LIBNAM:
    case CMD_LIBLOC:
    case CMD_LIBDIC:
        LnkMsg( LOC_REC+WRN+MSG_REC_NOT_DONE, "x", cmd );
        break;
    default:
        CurrMod->f.source->file->flags |= INSTAT_IOERR;
        LnkMsg( LOC_REC+ERR+MSG_BAD_REC_TYPE, "x", cmd );
        break;
    }
    return;
}

bool IsOMF( file_list *list, unsigned long loc )
/******************************************************/
{
    byte        *rec;

    rec = CacheRead( list, loc, sizeof(unsigned_8) );
    return( rec != NULL && *rec == CMD_THEADR );
}

char *GetOMFName( file_list *list, unsigned long *loc )
/**************************************************************/
{
    obj_record  *rec;
    char        *name;
    unsigned    len;

    rec = CacheRead( list, *loc, sizeof(obj_record) );
    if( rec == NULL )
        return( NULL );
    *loc += sizeof( obj_record );
    len = rec->length;
    name = CacheRead( list, *loc, rec->length );
    *loc += len;
    if( name == NULL )
        return( NULL );
    len = *(unsigned char *)name;        // get actual name length
    return( ChkToString( name + 1, len ) );
}

void OMFSkipObj( file_list *list, unsigned long *loc )
/***********************************************************/
{
    *loc = ProcObj( list, *loc, NULL );
}

static void ProcTHEADR( struct objbuff *ob )
/****************************/
{
    char    name[256];
    char    *sym_name;
    int     sym_len;

    if( CurrMod->omfdbg == OMF_DBG_CODEVIEW ) {
        sym_name = ( (obj_name UNALIGN *) ob->curr )->name;
        sym_len = ( (obj_name UNALIGN *) ob->curr )->len;
        if( sym_len == 0 ) {
			DEBUG((DBG_OLD, "objomf.ProcTHEADR(): error, sym_len == 0" ));
            BadObject();
        }
        memcpy( name, sym_name, sym_len );
        name[sym_len] = '\0';
    }
}

static void LinkDirective( struct objbuff *ob )
/*******************************/
{
    char            directive;
    lib_priority    priority;
    segnode         *seg;

    directive = *(char *)(ob->curr);
    ob->curr++;
    switch( directive ) {
    case LDIR_DEFAULT_LIBRARY:
        if( ob->curr + 1 < ob->end ) {
            priority = *ob->curr;
            ob->curr++;
            AddCommentLib( (char *)ob->curr, ob->end - ob->curr, priority );
        }
        break;
    case LDIR_SOURCE_LANGUAGE:
        DBIP1Source( ob->curr, ob->end );
        break;
    case LDIR_VF_PURE_DEF:
        ProcVFTableRecord( TRUE, ob );
        break;
    case LDIR_VF_TABLE_DEF:
        ProcVFTableRecord( FALSE, ob );
        break;
    case LDIR_VF_REFERENCE:
        ProcVFReference( ob );
        break;
    case LDIR_PACKDATA:
        if( !(LinkFlags & PACKDATA_FLAG) ) {
            PackDataLimit = _GetU32UN( ob->curr );
            LinkFlags |= PACKDATA_FLAG;
        }
        break;
    case LDIR_OPT_FAR_CALLS:
        seg = (segnode *)FindSegNode( SegNodes, GetIdx( ob ) );
        seg->entry->canfarcall = TRUE;
        seg->entry->iscode = TRUE;
        break;
    case LDIR_FLAT_ADDRS:
        CurrMod->modinfo |= MOD_FLATTEN_DBI;
        break;
    case LDIR_OPT_UNSAFE:
        ObjFormat |= FMT_UNSAFE_FIXUPP;
        break;
    }
    return;
}

static void ReadName( length_name *ln_name, struct objbuff *ob )
/******************************************/
{
    ln_name->len = *(unsigned_8 *)(ob->curr);
    ob->curr += sizeof( unsigned_8 );
    ln_name->name = (char *)(ob->curr);
    ob->curr += ln_name->len;
    return;
}

#define EXPDEF_ORDINAL  0x80

static void ProcExportKeyword( struct objbuff *ob )
/***********************************/
{
    unsigned_8  flags;
    length_name intname;
    length_name expname;
    unsigned    ordinal;

    flags = *ob->curr++;
    ReadName( &expname, ob );
    ReadName( &intname, ob );
    ordinal = 0;
    if( flags & EXPDEF_ORDINAL ) {
        ordinal = GET_U16_UN( ob->curr );
    }
    HandleExport( &expname, &intname, flags, ordinal );
    return;
}

static void ProcImportKeyword( struct objbuff *ob )
/***********************************/
{
    length_name intname;
    length_name modname;
    length_name extname;
    unsigned_8  info;

    info = *(ob->curr);
    ob->curr += sizeof( unsigned char );
    ReadName( &intname, ob );
    ReadName( &modname, ob );
    if( info == DLL_RELOC_NAME ) {
        if( *ob->curr == 0 ) {   /* use internal name */
            HandleImport( &intname, &modname, &intname, NOT_IMP_BY_ORDINAL );
        } else {
            ReadName( &extname, ob );
            HandleImport( &intname, &modname, &extname, NOT_IMP_BY_ORDINAL );
        }
    } else {
        HandleImport(&intname, &modname, &extname, GET_U16_UN(ob->curr) );
    }
    return;
}


static void DoMSOMF( struct objbuff *ob )
/***********************************/
/* Figure out debug info type and handle it accordingly later. */
{
    if( ob->curr == ob->end )
        CurrMod->omfdbg = OMF_DBG_CODEVIEW;    /* Assume MS style */
    else {
        unsigned_8  version;
        char        *dbgtype;

        version = *ob->curr++;
        dbgtype = (char *)ob->curr;
        ob->curr += 2;
        if( strncmp( dbgtype, "CV", 2 ) == 0 ) {
            CurrMod->omfdbg = OMF_DBG_CODEVIEW;
        } else if( strncmp( dbgtype, "HL", 2 ) == 0 ) {
            CurrMod->omfdbg = OMF_DBG_HLL;
        } else {
            CurrMod->omfdbg = OMF_DBG_UNKNOWN;
        }
    }
    return;
}

static void Comment( struct objbuff *ob )
/*************************/
/* Process a comment record. */
{
    unsigned char       attribute;
    unsigned char       class;
    int                 proc;
    unsigned char       which;

    attribute = *ob->curr;
    ob->curr += sizeof( unsigned char );
    class = *ob->curr;
    ob->curr += sizeof( unsigned char );

    switch( class ) {
    case CMT_DLL_ENTRY:
        which = *ob->curr;
        ob->curr += sizeof( unsigned char );
        switch( which ) {
        case MOMF_IMPDEF:
        case MOMF_EXPDEF:
            SeenDLLRecord();
            if( which == MOMF_EXPDEF ) {
                ProcExportKeyword( ob );
            } else {
                ProcImportKeyword( ob );
            }
            break;
        case MOMF_PROT_LIB:
            if( FmtData.type & MK_WIN_NE ) {
                FmtData.u.os2.is_private_dll = TRUE;
            }
            break;
        }
        break;
    case CMT_WAT_PROC_MODEL:
    case CMT_MS_PROC_MODEL:
        proc = GET_U8_UN( ob->curr ) - '0';
        if( proc > FmtData.cpu_type )
            FmtData.cpu_type = proc;
        break;
    case CMT_DOSSEG:
        LinkState |= DOSSEG_FLAG;
        break;
    case CMT_DEFAULT_LIBRARY:
        AddCommentLib( (char *)(ob->curr), ob->end - ob->curr, LIB_PRIORITY_MAX - 1 );
        break;
    case CMT_LINKER_DIRECTIVE:
        LinkDirective( ob );
        break;
    case CMT_WKEXT:
        DoLazyExtdef( TRUE, ob );
        break;
    case CMT_LZEXT:
        DoLazyExtdef( FALSE, ob );
        break;
    case CMT_EASY_OMF:
        if( memcmp( ob->curr, EASY_OMF_SIGNATURE, 5 ) == 0 ) {
            ObjFormat |= FMT_EASY_OMF;
        }
        break;
    case CMT_SOURCE_NAME:
        DBIComment();
        break;
    case CMT_MS_OMF:
        DoMSOMF( ob );
        break;
    case 0x80:      /* Code Gen used to put bytes out in wrong order */
        if( attribute == CMT_SOURCE_NAME ) {    /* no longer generated */
            DBIComment();
        } else if( attribute == CMT_LINKER_DIRECTIVE ) {  /* linker directive */
            LinkDirective( ob );
        }
        break;
    }
    return;
}

static void ProcAlias( struct objbuff *ob )
/***************************/
/* process a symbol alias directive */
{
    char        *alias;
    unsigned    aliaslen;
    unsigned    targetlen;
    symbol      *sym;

    while( ob->curr < ob->end ) {
        aliaslen = *ob->curr;
        ob->curr++;
        alias = (char *)ob->curr;
        ob->curr += aliaslen;
        targetlen = *ob->curr;
        ob->curr++;
        sym = SymOp( ST_FIND | ST_NOALIAS, alias, aliaslen );
        if( !sym || !(sym->info & SYM_DEFINED) ) {
            MakeSymAlias( alias, aliaslen, (char *)(ob->curr), targetlen );
        }
        ob->curr += targetlen;
    }
    return;
}

static void ProcModuleEnd( struct objbuff *ob )
/*******************************/
{
    byte        frame;
    byte        target;
    unsigned    targetidx;
    segnode     *seg;
    extnode     *ext;
    bool        hasdisp;

    if( StartInfo.user_specd )
        return;
    if( *ob->curr & 0x40 ) {
        ob->curr++;
        if( ob->curr == ob->end )               /* CSet/2 stupidity */
            return;
        frame = (*ob->curr >> 4) & 0x7;
        target = *ob->curr & 0x3;
        hasdisp = (*ob->curr & 0x4) == 0;
        ob->curr++;
        if( frame <= 2 ) {              /* frame requires an index */
            SkipIdx( ob );
        }
        targetidx = GetIdx( ob );
        switch( target ) {
        case TARGET_SEGWD:
            if( StartInfo.type != START_UNDEFED ) {
                LnkMsg( LOC+WRN+MSG_MULT_START_ADDRS, NULL );
                return;                 // <-------- NOTE: premature return
            }
            seg = (segnode *)FindSegNode( SegNodes, targetidx );
            StartInfo.type = START_IS_SDATA;
            StartInfo.targ.sdata= seg->entry;
            if( seg->info & SEG_CODE && LinkFlags & STRIP_CODE ) {
                RefSeg( (segdata *) seg->entry );
            }
            StartInfo.mod = CurrMod;
            break;
        case TARGET_EXTWD:
            ext = (extnode *) FindNode( ExtNodes, targetidx );
            SetStartSym( ext->entry->name );
            break;
        case TARGET_ABSWD:
        case TARGET_GRPWD:
            DEBUG((DBG_OLD, "objomf.ProcModuleEnd(): target %h invalid", target ));
            BadObject();        // no one does these, right???
            break;
        }
        if( hasdisp ) {
            if( ObjFormat & FMT_32BIT_REC ) {
                _TargU32toHost( _GetU32UN( ob->curr ), StartInfo.off );
            } else {
                _TargU16toHost( _GetU16UN( ob->curr ), StartInfo.off );
            }
        }
    }
    return;
}

static void AddNames( struct objbuff *ob )
/**************************/
/* Process NAMES record */
{
    int                 name_len;
    list_of_names       **entry;

    DEBUG(( DBG_OLD, "AddNames()" ));
    while( ob->curr < ob->end ) {
        name_len = ( (obj_name UNALIGN *) (ob->curr) )->len;
        entry = AllocNode( NameNodes );
        *entry = MakeListName( ((obj_name UNALIGN *)(ob->curr) )->name, name_len );
        ob->curr += name_len + sizeof( byte );
    }
    return;
}

static void ProcSegDef( struct objbuff *ob )
/****************************/
/* process a segdef record */
{
    segdata             *sdata;
    segnode             *snode;
    list_of_names       *clname;
    list_of_names       *name;
    byte                acbp;
    unsigned            comb;

    DEBUG(( DBG_OLD, "ProcSegDef() enter" ));
    sdata = AllocSegData();
    acbp = *ob->curr;
    ++ob->curr;
    comb = (acbp >> 2) & 7;
    if( comb == COMB_INVALID || comb == COMB_BAD ) {
        sdata->combine = COMBINE_INVALID;
    } else if( comb == COMB_COMMON ) {
        sdata->combine = COMBINE_COMMON;
    } else if( comb == COMB_STACK ) {    /* jwlink: stack combine type added */
        sdata->combine = COMBINE_STACK;  
    } else {
        sdata->combine = COMBINE_ADD;
    }
    sdata->align = OMFAlignTab[acbp >> 5];
    if( ObjFormat & FMT_EASY_OMF ) {   // set USE_32 flag.
        sdata->is32bit = TRUE;
    } else if( acbp & 1 ) {
        sdata->is32bit = TRUE;
    }
    switch( acbp >> 5 ) {
    case ALIGN_ABS:
        _TargU16toHost( _GetU16UN( ob->curr ), sdata->frame );
        sdata->isabs = TRUE;
        ob->curr += sizeof( unsigned_16 );
        ob->curr += sizeof( byte );
        break;
    case ALIGN_LTRELOC:
// in 32 bit object files, ALIGN_LTRELOC is actually ALIGN_4KPAGE
        if( ( ObjFormat & FMT_32BIT_REC ) || ( FmtData.type & MK_RAW ) )
            break;
        sdata->align = OMFAlignTab[ALIGN_PARA];
        ob->curr += 5;   /*  step over ltldat, max_seg_len, grp_offs fields */
        break;
    }
    if( ObjFormat & FMT_32BIT_REC ) {
        if( acbp & 2 ) {
            DEBUG((DBG_OLD, "objomf.ProcSegDef(): error, 4 GB segment found" ));
            BadObject();        // we can't handle 4 GB segments properly
            return;
        }
        _TargU32toHost( _GetU32UN( ob->curr ), sdata->length );
        ob->curr += sizeof( unsigned_32 );
    } else {
        if( acbp & 2 ) {
            sdata->length = 65536;          // 64k segment
        } else {
            _TargU16toHost( _GetU16UN( ob->curr ), sdata->length );
        }
        ob->curr += sizeof( unsigned_16 );
    }
    name = FindName( GetIdx( ob ) );
    DEBUG(( DBG_OLD, "ProcSegDef: name=%s", name->name ));
    sdata->u.name = name->name;
    clname = FindName( GetIdx( ob ) );
    if( ObjFormat & FMT_EASY_OMF ) {
        SkipIdx( ob );        // skip overlay name index
        if( ob->curr < ob->end ) {      // the optional attribute field present
            if( !(*ob->curr & 0x4) ) {      // if USE32 bit not set;
                sdata->is32bit = FALSE;
            }
        }
    }
    sdata->iscode = IsCodeClass( clname->name, strlen(clname->name) );
    snode = AllocNode( SegNodes );
    snode->entry = sdata;
    AllocateSegment( snode, clname->name );
    DEBUG(( DBG_OLD, "ProcSegDef(%s) exit, class=\"%s\" comb=%d", name->name, clname->name, sdata->combine ));
    return;
}

static void DefineGroup( struct objbuff *ob )
/*****************************/
/* Define a group. */
{
    int                 num_segs;
    byte                *anchor;
    segnode             *seg;
    list_of_names       *grp_name;
    grpnode             *newnode;
    group_entry         *group;

    grp_name = FindName( GetIdx( ob ) );
    DEBUG(( DBG_OLD, "DefineGroup() - %s", grp_name->name ));
    anchor = ob->curr;
    num_segs = 0;
    for( ;; ) {
        if( ob->curr >= ob->end )
            break;
        if( *ob->curr != GRP_SEGIDX ) {
            DEBUG((DBG_OLD, "objomf.DefineGroup(): error, invalid entry in group def" ));
            BadObject();
            return;
        }
        ++ob->curr;
        SkipIdx( ob );/*  skip segment index */
        ++num_segs;
    }
    newnode = AllocNode( GrpNodes );
    group = SearchGroups( grp_name->name );
    if( group == NULL ) {
        if( num_segs == 0 ) {
            DEBUG(( DBG_OLD, "DefineGroup(%s): group has 0 segments", grp_name->name ));
            newnode->entry = NULL;
            return;                     // NOTE: premature return!
        }
        group = AllocGroup( grp_name->name, &Groups );
        /* jwlink: reset read-only flag for groups */
        if ( FmtData.type & MK_PE )
            group->segflags &= ~SEG_READ_ONLY;
    }
    newnode->entry = group;
    ob->curr = anchor;
    for( ;; ) {
        if( ob->curr >= ob->end )
            break;
        ++ob->curr;
        seg = (segnode *)FindSegNode( SegNodes, GetIdx( ob ) );
        AddToGroup( group, seg->entry->u.leader );
    }
    return;
}

static void ProcPubdef( bool static_sym, struct objbuff *ob )
/***************************************/
/* Define symbols. */
{
    symbol          *sym;
    char            *sym_name;
    segnode         *seg;
    offset          off;
    unsigned        sym_len;
    unsigned_16     frame;
    unsigned_16     segidx;

    DEBUG(( DBG_OLD, "ProcPubdef(static=%d)", static_sym ));
    SkipIdx( ob );
    segidx = GetIdx( ob );
    if( segidx != 0 ) {
        seg = (segnode *) FindSegNode( SegNodes, segidx );
#ifdef _INT_DEBUG
        if ( seg == NULL ) {
            DEBUG((DBG_OLD, "objomf.ProcPubdef(): invalid segidx %d", segidx ));
            BadObject();
            return;
        }
#endif
    } else {
        seg = NULL;
        _TargU16toHost( _GetU16UN( ob->curr ), frame );
        ob->curr += sizeof( unsigned_16 );
    }
    DEBUG(( DBG_OLD, "segidx = %d", segidx ));
    while( ob->curr < ob->end ) {
        sym_name = ( (obj_name UNALIGN *) (ob->curr) )->name;
        sym_len = ( (obj_name UNALIGN *) (ob->curr) )->len;
        if( sym_len == 0 ) {
            DEBUG((DBG_OLD, "objomf.ProcPubdef(): error, sym_len == 0" ));
            BadObject();
            return;
        }
        ob->curr += sym_len + sizeof( byte );
        if( ObjFormat & FMT_32BIT_REC ) {
            _TargU32toHost( _GetU32UN( ob->curr ), off );
            ob->curr += sizeof( unsigned_32 );
        } else {
            _TargU16toHost( _GetU16UN( ob->curr ), off );
            ob->curr += sizeof( unsigned_16 );
        }
        if( static_sym ) {
            sym = SymOp( ST_DEFINE_SYM | ST_STATIC, sym_name, sym_len );
        } else {
            sym = SymOp( ST_DEFINE_SYM, sym_name, sym_len );
        }
        DefineSymbol( sym, seg, off, frame );
        SkipIdx( ob );   /* skip type index */
    }
    return;
}

static void DoLazyExtdef( bool isweak, struct objbuff *ob )
/*************************************/
/* handle the lazy and weak extdef comments */
{
    extnode     *ext;
    symbol      *sym;
    unsigned    idx;

    while( ob->curr < ob->end ) {
        ext = (extnode *) FindNode( ExtNodes, GetIdx( ob ) );
        sym = ext->entry;
        ext->isweak = TRUE;
        idx = GetIdx( ob );
        ext = (extnode *) FindNode( ExtNodes, idx );
        DefineLazyExtdef( sym, ext->entry, isweak );
    }
    return;
}

static void *GetVFListStart( struct objbuff *ob )
/**********************************/
{
    return( ob->curr );
}

static void SetVFListStart( struct objbuff *ob, void *start )
/****************************************/
{
    ob->curr = start;
}

static bool EndOfVFList( struct objbuff *ob )
/*****************************/
{
    return( ob->curr >= ob->end );
}

static char *GetVFListName( struct objbuff *ob )
/*********************************/
{
    list_of_names       *lname;

    lname = FindName( GetIdx( ob ) );
    return( lname->name );
}

static void ProcVFTableRecord( bool ispure, struct objbuff *ob )
/******************************************/
// process the watcom virtual function table information extension
{
    extnode     *ext;
    symbol      *sym;
    vflistrtns  rtns;

    if( !(LinkFlags & VF_REMOVAL) )
        return;
    ext = (extnode *) FindNode( ExtNodes, GetIdx( ob ) );
    sym = ext->entry;
    ext->isweak = TRUE;
    ext = (extnode *) FindNode( ExtNodes, GetIdx( ob ) );
    rtns.getstart = GetVFListStart;
    rtns.setstart = SetVFListStart;
    rtns.isend = EndOfVFList;
    rtns.getname = GetVFListName;
    rtns.ob = ob;
    DefineVFTableRecord( sym, ext->entry, ispure, &rtns );
}

static void ProcVFReference( struct objbuff *ob )
/*********************************/
/* process a vftable reference record */
{
    extnode             *ext;
    segnode             *seg;
    symbol              *sym;
    list_of_names       *lname;
    unsigned            index;

    if( !(LinkFlags & VF_REMOVAL) )
        return;
    index = GetIdx( ob );
    if( index == 0 ) {
        LnkMsg( WRN+LOC+MSG_NOT_COMPILED_VF_ELIM, NULL );
        return;
    }
    ext = (extnode *) FindNode( ExtNodes, index );
    if( LinkFlags & STRIP_CODE ) {
        if( *ob->curr == 0 ) {   /* it is a comdat index */
            ob->curr++;
            lname = FindName( GetIdx( ob ) );
            sym = FindISymbol( lname->name );
            if( sym == NULL ) {
                sym = MakeWeakExtdef( lname->name, NULL );
            }
            DefineVFReference( sym, ext->entry, TRUE );
        } else {                /* it's a seg idx */
            seg = (segnode *)FindSegNode( SegNodes, GetIdx( ob ) );
            DefineVFReference( seg, ext->entry, FALSE );
        }
    }
    if( !(ext->entry->info & SYM_DEFINED) ) {
        ext->entry->info |= SYM_VF_MARKED;
    }
}

static void UseSymbols( bool static_sym, bool iscextdef, struct objbuff *ob )
/*******************************************************/
/* Define all external references. */
{
    list_of_names       *lnptr;
    char                *sym_name;
    unsigned            sym_len;
    extnode             *newnode;
    symbol              *sym;
    sym_flags           flags;

    DEBUG(( DBG_OLD, "UseSymbols(static=%d is_cextdef=%d )", static_sym, iscextdef ));
    flags = ST_CREATE | ST_REFERENCE;
    if( static_sym ) {
        flags |= ST_STATIC;
    }
    while( ob->curr < ob->end ) {
        if( iscextdef ) {
            lnptr = FindName( GetIdx( ob ) );
            sym = RefISymbol( lnptr->name );
        } else {
            sym_len = ( (obj_name *) (ob->curr) )->len;
            sym_name = ( (obj_name *) (ob->curr) )->name;
            if( sym_len == 0 ) {
				DEBUG((DBG_OLD, "objomf.UseSymbols(): error, sym_len == 0" ));
                BadObject();
            }
            ob->curr += sym_len + sizeof( byte );
            sym = SymOp( flags, sym_name, sym_len );
        }
        newnode = AllocNode( ExtNodes );
        newnode->entry = sym;
        newnode->isweak = FALSE;
        DefineReference( sym );
        SkipIdx( ob );/*  skip type index */
    }
}

void SkipIdx( struct objbuff *ob )
/*************************/
/* skip the index */
{
    if (*ob->curr++ & IS_2_BYTES) {
        ob->curr++;
    }
}

unsigned_16 GetIdx( struct objbuff *ob )
/*******************************/
/* Get an index. */
{
    unsigned_16 index;

    index = *ob->curr++;
    if (index & IS_2_BYTES) {
        index = (index & 0x7f) * 256 + *ob->curr;
        ++ob->curr;
    }
    return( index );
}

list_of_names *FindName( unsigned_16 index )
/**************************************************/
/* Find name of specified index. */
{
    return( *((list_of_names **)FindNode( NameNodes, index ) ) );
}

static void ProcLxdata( bool islidata, struct objbuff *ob )
/*************************************/
/* process ledata and lidata records */
{
    segnode     *seg;
    unsigned_32 obj_offset;

    seg = (segnode *) FindSegNode( SegNodes, GetIdx( ob ) );
#ifdef _INT_DEBUG
    if ( seg == NULL ) {
        DEBUG((DBG_OLD, "objomf.ProcLxdata(): error, invalid seg index" ));
        BadObject();
        return;
    }
#endif
    seg->entry->u.leader->info |= SEG_LXDATA_SEEN;
    seg->info |= SEG_LXDATA_SEEN;
    if( ObjFormat & FMT_32BIT_REC ) {
        _TargU32toHost( _GetU32UN( ob->curr ), obj_offset );
        ob->curr += sizeof( unsigned_32 );
    } else {
        _TargU16toHost( _GetU16UN( ob->curr ), obj_offset );
        ob->curr += sizeof( unsigned_16 );
    }
#if _DEVELOPMENT == _ON
    if( stricmp( seg->entry->u.leader->segname, "_BSS" ) == 0 ) {
        LnkMsg( LOC_REC+ERR+MSG_INTERNAL, "s", "Initialized BSS found" );
    }
#endif
    GetObject( seg->entry, obj_offset, islidata, ob );
    return;
}

static void ProcLinnum( struct objbuff *ob )
/****************************/
/* do some processing for the linnum record */
{
    segnode     *seg;
    bool        is32bit;

    SkipIdx( ob );          /* don't need the group idx */
    seg = (segnode *) FindSegNode( SegNodes, GetIdx( ob ) );
	DEBUG((DBG_OLD, "objomf.ProcLinnum(): seg=%h (%s) info=%h iscode=%x", seg, seg->entry->u.leader->segname, seg->info, seg->entry->iscode ));
    if( seg->info & SEG_DEAD )                  /* ignore dead segments */
		return;

#if 0
	/* jwlink: autochange to code if a linnum record is found? */
	seg->entry->iscode = TRUE;
	seg->entry->u.leader->info |= SEG_CODE;
	seg->info |= SEG_CODE;
#endif

    is32bit = (ObjFormat & FMT_32BIT_REC) != 0;
    DBIAddLines( seg->entry, ob->curr, ob->end - ob->curr, is32bit );
    return;
}

static void ProcIDBlock( virt_mem *dest, struct objbuff *ob, unsigned_32 iterate )
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
            PutInfo( *dest, ob->curr, len );
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
                    ProcIDBlock( dest, ob, rep );
                } while( --inner != 0 );
            } while( --iterate != 0 );
        } else {
            do {
                ob->curr = anchor;
                inner = count;
                do {
                    _TargU16toHost( _GetU16UN(ob->curr), rep );
                    ob->curr += sizeof(unsigned_16);
                    ProcIDBlock( dest, ob, rep );
                } while( --inner != 0 );
            } while( --iterate != 0 );
        }
    }
    return;
}

static void DoLIData( virt_mem start, struct objbuff *ob )
/********************************************************/
/* Expand logically iterated data. */
{
    unsigned_32 rep;

    while( ob->curr < ob->end ) {
        if( ObjFormat & FMT_MS_386 ) {
            _TargU32toHost( _GetU32UN( ob->curr ), rep );
            ob->curr += sizeof( unsigned_32 );
        } else {
            _TargU16toHost( _GetU16UN( ob->curr ), rep );
            ob->curr += sizeof( unsigned_16 );
        }
        ProcIDBlock( &start, ob, rep );
    }
}

static void GetObject( segdata *seg, unsigned_32 obj_offset, bool lidata, struct objbuff *ob )
/*************************************************************************/
/* Load object code, LEDATA and LIDATA. */
{
    unsigned    size;
    virt_mem    start;

    if( seg->isdead || seg->isabs ) {   /* ignore dead or abs segments */
        ObjFormat |= FMT_IGNORE_FIXUPP; /* and any corresponding fixupps */
        return;
    }
    ObjFormat &= ~(FMT_IGNORE_FIXUPP|FMT_IS_LIDATA);
    if( lidata ) {
        ObjFormat |= FMT_IS_LIDATA;
    }
    if( ob->curr != ob->end ) {
        start = seg->data + obj_offset;
        if( lidata ) {
            ob->start_lidata = ob->curr;  /* jwlink: save all info in case */
            ob->end_lidata = ob->end;     /* a RELOC record follows        */
            ob->objformat = ObjFormat;
            DoLIData( start, ob );
        } else {
            size = ob->end - ob->curr;
            if( size + obj_offset > seg->length ) {
                LnkMsg( LOC_REC+FTL+MSG_OBJ_FILE_ATTR, NULL );
            }
            PutInfo( start, ob->curr, size );
        }
    }
    SetCurrSeg( seg, obj_offset, NULL );
}
