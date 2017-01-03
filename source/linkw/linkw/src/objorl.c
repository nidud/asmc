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
* Description:  Object file processing routines specific to ORL.
*
****************************************************************************/


#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "linkstd.h"
#include "msg.h"
#include "wlnkmsg.h"
#include "alloc.h"
#include <orl.h>
#include "specials.h"
#include "obj2supp.h"
#include "objnode.h"
#include "objcache.h"
#include "objio.h"
#include "cmdline.h"
#include "dbgall.h"
#include "objpass1.h"
#include "objpass2.h"
#include "objorl.h"
#include "strtab.h"
#include "carve.h"
#include "wcomdef.h"
#include "permdata.h"
#include "command.h"    // NYI: don't want to include this!
#include "impexp.h"
#include "virtmem.h"
#include "loadfile.h"
#include "objstrip.h"
#include "toc.h"
#include "walloca.h"

static orl_handle       ORLHandle;
static long             ORLFilePos;

static long             ORLSeek( void *, long, int );
static void             *ORLRead( void *, size_t );
static void             ClearCachedData( file_list *list );

static orl_funcs        ORLFuncs = { ORLRead, ORLSeek, ChkLAlloc, LFree };
static orl_reloc        SavedReloc;
static char             *ImpExternalName;
static char             *ImpModName;
static char             *FirstCodeSymName;
static char             *FirstDataSymName;
static unsigned_32      ImpOrdinal;


typedef struct readcache READCACHE;

typedef struct readcache {
    READCACHE   *next;
    void        *data;
} readcache;

static readcache   *ReadCacheList;

void InitObjORL( void )
/****************************/
{
    ORLHandle = ORLInit( &ORLFuncs );
    ReadCacheList = NULL;
}

void ObjORLFini( void )
/****************************/
{
    ORLFini( ORLHandle );
}

static long ORLSeek( void *_list, long pos, int where )
/*****************************************************/
{
    file_list *list = _list;

    if( where == SEEK_SET ) {
        ORLFilePos = pos;
    } else if( where == SEEK_CUR ) {
        ORLFilePos += pos;
    } else {
        ORLFilePos = list->file->len - pos;
    }
    return( ORLFilePos );
}

static void *ORLRead( void *_list, size_t len )
/**********************************************/
{
    file_list   *list = _list;
    void        *result;
    readcache   *cache;

    result = CachePermRead( list, ORLFilePos, len );
    ORLFilePos += len;
    _ChkAlloc( cache, sizeof( readcache ) );
    cache->next = ReadCacheList;
    ReadCacheList = cache;
    cache->data = result;
    return( result );
}

bool IsORL( file_list *list, unsigned loc )
/*************************************************/
// return TRUE if this is can be handled by ORL
{
    orl_file_format     type;
    bool                isOK;

    isOK = TRUE;
    ORLSeek( list, loc, SEEK_SET );
    type = ORLFileIdentify( ORLHandle, list );
    if( type == ORL_ELF ) {
        ObjFormat |= FMT_ELF;
    } else if( type == ORL_COFF ) {
        ObjFormat |= FMT_COFF;
    } else {
        isOK = FALSE;
    }
    ClearCachedData( list );
    return( isOK );
}

static orl_file_handle InitFile( void )
/*************************************/
{
    orl_file_format     type;

    ImpExternalName = NULL;
    ImpModName = NULL;
    ImpOrdinal = 0;
    FirstCodeSymName = NULL;
    FirstDataSymName = NULL;
    if( IS_FMT_ELF(ObjFormat) ) {
        type = ORL_ELF;
    } else {
        type = ORL_COFF;
    }
    return( ORLFileInit( ORLHandle, CurrMod->f.source, type ) );
}

static void ClearCachedData( file_list *list )
/********************************************/
{
    readcache   *cache;
    readcache   *next;

    for( cache = ReadCacheList; cache != NULL; cache = next ) {
        next = cache->next;
        CacheFree( list, cache->data );
        _LnkFree( cache );
    }
    ReadCacheList = NULL;
}

static void FiniFile( orl_file_handle filehdl, file_list *list )
/**************************************************************/
{
    ORLFileFini( filehdl );
    ClearCachedData( list );
    if( ImpModName != NULL ) {
        _LnkFree( ImpModName );
        ImpModName = NULL;
    }
}

void ORLSkipObj( file_list *list, unsigned long *loc )
/***********************************************************/
// skip the object file.
// NYI: add an entry point in ORL for a more efficient way of doing this.
{
    orl_file_handle     filehdl;

    ORLSeek( list, *loc, SEEK_SET );
    filehdl = InitFile();               // assumes that entire file is read!
    *loc = ORLSeek( list, 0, SEEK_CUR );
    FiniFile( filehdl, list );
}

static bool CheckFlags( orl_file_handle filehdl )
/***********************************************/
{
    orl_machine_type    machtype;
    stateflag           typemask;
    stateflag           test;
    orl_file_flags      flags;

    machtype = ORLFileGetMachineType( filehdl );
    DEBUG((DBG_OLD, "objorl.CheckFlags(): machtype=%x", machtype ) );

    switch( machtype ) {
    case ORL_MACHINE_TYPE_AMD64: /* JWlink */
        if ( FmtData.type & MK_PE )
            FmtData.u.pe.win64 = 1;
        else if ( FmtData.type & MK_ELF )
            FmtData.u.elf.elf64 = 1;
        typemask = HAVE_I86_CODE;
        break;
    case ORL_MACHINE_TYPE_I386:
        typemask = HAVE_I86_CODE;
        break;
    case ORL_MACHINE_TYPE_ALPHA:
        typemask = HAVE_ALPHA_CODE;
        break;
    case ORL_MACHINE_TYPE_PPC601:
        typemask = HAVE_PPC_CODE;
        break;
    case ORL_MACHINE_TYPE_R3000:
        typemask = HAVE_MIPS_CODE;
        break;
    case ORL_MACHINE_TYPE_NONE:
        typemask = 0;
        break;
    default:
        typemask = HAVE_MACHTYPE_MASK;  // trigger the error
        break;
    }
    test = (typemask | LinkState) & HAVE_MACHTYPE_MASK;
    test &= test - 1;           // turn off one bit
    if( test != 0 ) {   // multiple bits were turned on.
        LnkMsg( WRN+MSG_MACHTYPE_DIFFERENT, "s", CurrMod->f.source->file->name);
    } else {
        LinkState |= typemask;
    }
    if( ORLFileGetType( filehdl ) != ORL_FILE_TYPE_OBJECT ) {
		DEBUG((DBG_OLD, "objorl.CheckFlags(): error, type %h != ORL_FILE_TYPE_OBJECT", ORLFileGetType( filehdl ) ) );
        BadObject();
        return( FALSE );
    }
    flags = ORLFileGetFlags( filehdl );
#if 0
    if( flags & ORL_FILE_FLAG_BIG_ENDIAN ) {    // MS lies about this.
        LnkMsg( ERR+LOC+MSG_NO_BIG_ENDIAN, NULL );
        return( FALSE );
    }
#endif
    if( flags & ORL_FILE_FLAG_16BIT_MACHINE ) {
        Set16BitMode();
    } else if ( machtype == ORL_MACHINE_TYPE_AMD64 ) { /* jwlink */
        Set64BitMode();
    } else {
        Set32BitMode();
    }
    return( TRUE );
}

static orl_return NullFunc( orl_sec_handle dummy )
/************************************************/
// section type is ignored
{
    dummy = dummy;
    return( ORL_OKAY );
}

static orl_return ExportCmd( char *name, void *dummy )
/****************************************************/
{
    length_name lname;
#if 1 /* JWLink */
    length_name intname;
#endif

    dummy = dummy;
    lname.name = name;
#if 1 /* JWLink: allow "internal name" suffix */
    if ( intname.name = strchr( name, '=' ) ) {
        lname.len = intname.name - name;
        intname.name++;
        intname.len = strlen(intname.name);
        HandleExport( &lname, &intname, 0, 0 );
        return( ORL_OKAY );
    }
#endif
    lname.len = strlen(name);
    HandleExport( &lname, &lname, 0, 0 );
    return( ORL_OKAY );
}

/* this is new for jwlink
 * syntax for item is:
 *   internal_name=module_name[.entry_name | ordinal ]
 */
static orl_return ImportCmd( char *item, void *dummy )
/****************************************************/
{
    length_name intname;
    length_name module;
    length_name entry;
    int ordinal = NOT_IMP_BY_ORDINAL;

    intname.name = item;
    module.name = strchr( item, '=' );
    if ( module.name == NULL )
        return( ORL_ERROR );
    intname.len = module.name - item;
    *module.name++ = '\0';
    if ( entry.name = strchr( module.name, '.' ) ) {
        char *tmp;
        if ( tmp = strchr( entry.name + 1, '.' ) )   /* module name may contain a '.' */
            entry.name = tmp;
        module.len = entry.name - module.name;
        *entry.name++ = '\0';
        entry.len = strlen( entry.name );
        if ( isdigit( *entry.name ) )
            ordinal = atol( entry.name );
    } else {
        module.len = strlen( module.name );
        entry.name = intname.name;
        entry.len = intname.len;
    }
    DEBUG((DBG_OLD, "ImportCmd: intname=%s module=%s entry=%s", intname.name, module.name, entry.name ));
    HandleImport( &intname, &module, ordinal == NOT_IMP_BY_ORDINAL ? &entry : NULL, ordinal );
    return( ORL_OKAY );
}

static orl_return EntryCmd( char *name, void *dummy )
/***************************************************/
{
    if( !StartInfo.user_specd ) {
#if 1 /* JWLink: add underscore prefix for 32-bit PE */
        if ( ( FmtData.type & MK_PE ) && FmtData.u.pe.win64 == 0 ) {
            char *tmpname;
            int i = strlen( name );
            tmpname = alloca( i + 2 );
            tmpname[0] = '_';
            strcpy( tmpname+1, name );
            SetStartSym( tmpname );
        } else
#endif
            SetStartSym( name );
    }
    return( ORL_OKAY );
}

static orl_return DeflibCmd( char *name, void *dummy )
/****************************************************/
{
    char *end;

    dummy = dummy;
    /* library name may be enclosed in double quotes! */
    for( ; *name; ) {
        if ( *name == '"' ) {
            name++;
            end = strchr( name, '"' );
            if ( end == NULL )
                return( ORL_ERROR );
            *end++ = '\0';
        } else {
            for ( end = name; *end ; end++ )
                if ( *end == ' ' || *end == '\t' || *end == ',' )
                    break;
            if ( *end )
                *end++ = '\0';
        }
        AddCommentLib( name, strlen(name), LIB_PRIORITY_MAX - 1 );
        name = end;
    }
    return( ORL_OKAY );
}

struct cmditem {
    const char *cmd;
    orl_return (*pfn)( char *, void * );
};

static const struct cmditem cmdtab[] = {
    { "defaultlib", DeflibCmd },
    { "entry"     , EntryCmd  },
    { "export"    , ExportCmd },
    { "import"    , ImportCmd },
};
#define NUMLNKCMDS ( sizeof( cmdtab ) / sizeof( cmdtab[0] ) )

static orl_return LnkCmdCallback( char *cmd, char *value, void *dummy )
/********************************************************************/
{
    int i;
    DEBUG((DBG_OLD, "LnkCmdCallback: cmd=%s, value=%s", cmd, value ));

    for( i = 0; i < NUMLNKCMDS; i++ )
        if ( strcmp( cmd, cmdtab[i].cmd ) == 0 )
            return( cmdtab[i].pfn( value, dummy ) );

    LnkMsg( WRN+LOC+MSG_UNKNOWN_DIRECTIVE_IGNORED, "s", cmd );
    return( ORL_OKAY );
}

static orl_return P1Note( orl_sec_handle sec )
/********************************************/
// handle extra object file information records
{
    orl_note_callbacks cb;

    /* jwlink: the linker will parse the cmd */
    cb.lnk_cmd_fn = LnkCmdCallback;
    //cb.export_fn = ExportCallback;
    //cb.deflib_fn = DeflibCallback;
    //cb.entry_fn = EntryCallback;
    ORLNoteSecScan( sec, &cb, NULL );
    return( ORL_OKAY );
}

static orl_return Unsupported( orl_sec_handle dummy )
/***************************************************/
// NYI
{
    dummy = dummy;
    return( ORL_OKAY );
}

static void AllocSeg( void *_snode, void *dummy )
/***********************************************/
{
    segnode             *snode = _snode;
    segdata             *sdata;
    char                *clname;
    char                *sname;
    group_entry         *group;
    bool                isdbi;

    dummy = dummy;
    sdata = snode->entry;
    if( sdata == NULL )
        return;
    DbgAssert( sdata->u.name );
    DEBUG((DBG_OLD,"objorl: AllocSeg() - %s iscode=%d isuninit=%d isreadonly=%d isidata=%d iscdat=%d snode.info=%h",
           sdata->u.name, sdata->iscode, sdata->isuninit, sdata->isreadonly, sdata->isidata, sdata->iscdat, snode->info ));
    sname = sdata->u.name;
    if( CurrMod->modinfo & MOD_IMPORT_LIB ) {
        if( sdata->isidata || sdata->iscode ) {
            if( sdata->iscode ) {
                snode->info |= SEG_CODE;
            }
            if ( sdata->isreadonly ) { /* jwlink */
                snode->info |= SEG_READ_ONLY;
            }
            snode->info |= SEG_DEAD;
            DEBUG((DBG_OLD,"objorl: AllocSeg() - SEG_DEAD is ON (1)" ));
            snode->entry = NULL;
            FreeSegData( sdata );
            return;
        }
    }
    isdbi = FALSE;
    if( memicmp( CoffDebugPrefix, sdata->u.name,
                sizeof(CoffDebugPrefix) - 1 ) == 0 ) {
        if( CurrMod->modinfo & MOD_IMPORT_LIB ) {
            DEBUG((DBG_OLD,"objorl: AllocSeg() - SEG_DEAD is ON (2)" ));
            snode->info |= SEG_DEAD;
            snode->entry = NULL;
            FreeSegData( sdata );
            return;
        }
        isdbi = TRUE;
        if( stricmp(CoffDebugSymName, sdata->u.name ) == 0 ) {
            clname = _MSLocalClass;
        } else if( stricmp(CoffDebugTypeName, sdata->u.name ) == 0 ) {
            clname = _MSTypeClass;
        } else {
            clname = _DwarfClass;
        }
    } else if( memicmp( TLSSegPrefix, sdata->u.name,
                        sizeof(TLSSegPrefix) - 1 ) == 0 ) {
        clname = TLSClassName;
    } else if( sdata->iscode ) {
        clname = CodeClassName;
    } else if( sdata->isuninit ) {
        clname = BSSClassName;
    } else if ( ( FmtData.type & (MK_PE|MK_ELF) ) && ( sdata->isreadonly ) ) { /* jwlink */
        clname = ConstClassName;
    } else {
        clname = DataClassName;
        if( memcmp( sname, CoffPDataSegName, sizeof(CoffPDataSegName) ) == 0 ) {
            sdata->ispdata = TRUE;
        } else if( memcmp(sname, CoffReldataSegName,
                                   sizeof(CoffReldataSegName) ) == 0 ) {
            sdata->isreldata = TRUE;
        }
    }
    DEBUG((DBG_OLD,"objorl: AllocSeg() - classname=%s", clname ));
    AllocateSegment( snode, clname );
    if( clname == TLSClassName ) {
        group = GetGroup( TLSGrpName );
        AddToGroup( group, snode->entry->u.leader );
    } else if( !sdata->iscode && !isdbi  ) {
#if 1 /* JWLink */
        if( ( FmtData.type & MK_PE ) && FmtData.u.pe.win64 &&
           ( memcmp( sname, ".pdata", 6 ) == 0 ) &&
           ( *(sname+6) == '\0' || *(sname+6) == '$' ) )
            group = GetGroup( ".pdata" );
        else if( sdata->isreadonly && ( FmtData.type & (MK_PE|MK_ELF) ) )
            group = GetGroup( ".rdata" );
        else
#endif
            group = GetGroup( DataGrpName );
        AddToGroup( group, snode->entry->u.leader );
    }
    if( sdata->isuninit ) {
        snode->contents = NULL;
    } else {
        snode->entry->u.leader->info |= SEG_LXDATA_SEEN;
        if( !sdata->isdead ) {
            ORLSecGetContents( snode->handle, &snode->contents );
            if( !sdata->iscdat && ( snode->contents != NULL )) {
                PutInfo( sdata->data, snode->contents, sdata->length );
            }
        }
    }
}

static void DefNosymComdats( void *_snode, void *dummy )
/******************************************************/
{
    segnode             *snode = _snode;
    segdata             *sdata;

    dummy = dummy;
    sdata = snode->entry;
    if( sdata == NULL || snode->info & SEG_DEAD )
        return;
    if( sdata->iscdat && !sdata->hascdatsym && ( snode->contents != NULL )) {
        sdata->data = AllocStg( sdata->length );
        PutInfo( sdata->data, snode->contents, sdata->length );
    }
}

static orl_return DeclareSegment( orl_sec_handle sec )
/****************************************************/
// declare the "segment"
{
    segdata             *sdata;
    segnode             *snode;
    char                *name;
    unsigned_32 UNALIGN *contents;
    size_t              len;
    orl_sec_flags       flags;
    orl_sec_type        type;
    unsigned            numlines;
    unsigned            segidx;

    type = ORLSecGetType( sec );
    if( type != ORL_SEC_TYPE_NO_BITS && type != ORL_SEC_TYPE_PROG_BITS ) {
         return( ORL_OKAY );
    }
    flags = ORLSecGetFlags( sec );
    name = ORLSecGetName( sec );
    DEBUG((DBG_OLD, "objorl.DeclareSegment(): %s", name ));
    sdata = AllocSegData();
    segidx = ORLCvtSecHdlToIdx( sec );
    snode = AllocNodeIdx( SegNodes, segidx );
    snode->entry = sdata;
    snode->handle = sec;
    sdata->iscdat = (flags & ORL_SEC_FLAG_COMDAT) != 0;
    len = sizeof( CoffIDataSegName ) - 1;
    if( strnicmp( CoffIDataSegName, name, len ) == 0 ) {
        SeenDLLRecord();
        CurrMod->modinfo |= MOD_IMPORT_LIB;
        /* .idata$4, .idata$5 (IAT) and .idata$6 */
        if( name[len + 1] == '6' ) {    /* .idata$6 - is to contain the import's name */
            ORLSecGetContents( sec, (unsigned_8 **)&ImpExternalName );
            ImpExternalName += 2;
        } else if( name[len + 1] == '4' ) {     /* .idata$4 - is to contain imports by ordinal */
            /* jwlink v19b9: check for error */
            if ( ORLSecGetContents( sec, (void *) &contents ) == ORL_ERROR ) {
                DEBUG((DBG_OLD, "objorl.DeclareSegment(%s): ORLSecGetContents() returned with error ", name ));
            } else
                ImpOrdinal = *contents;
        }
        sdata->isdead = TRUE;
        sdata->isidata = TRUE;
    }
    sdata->combine = COMBINE_ADD;
    if( flags & ORL_SEC_FLAG_NO_PADDING ) {
        sdata->align = 0;
    } else {
        sdata->align = ORLSecGetAlignment( sec );
    }
    sdata->is32bit = TRUE;
    sdata->length = ORLSecGetSize( sec );
    sdata->u.name = name;
    if( flags & ORL_SEC_FLAG_EXEC ) {
        sdata->iscode = TRUE;
    } else if( ( flags & ( ORL_SEC_FLAG_READ_PERMISSION | ORL_SEC_FLAG_WRITE_PERMISSION ) ) ==
              ORL_SEC_FLAG_READ_PERMISSION ) {
        sdata->isreadonly = TRUE;  /* jwlink */
    } else if( flags & ORL_SEC_FLAG_UNINITIALIZED_DATA ) {
        sdata->isuninit = TRUE;
#if _DEVELOPMENT == _ON
    } else {
        unsigned namelen;

        namelen = strlen(name);
        if( namelen >= 3 && memicmp(name + namelen - 3, "bss", 3) == 0 ) {
            LnkMsg( ERR+MSG_INTERNAL, "s", "Initialized BSS found" );
        }
#endif
    }
    numlines = ORLSecGetNumLines( sec );
    if( numlines > 0 ) {
        numlines *= sizeof(orl_linnum);
        DBIAddLines( sdata, ORLSecGetLines( sec ), numlines, TRUE );
    }
    DEBUG((DBG_OLD, "objorl.DeclareSegment(): %s iscdat=%d", name, sdata->iscdat ));
    return( ORL_OKAY );
}

static segnode *FindSegNode( orl_sec_handle sechdl )
/***************************************************/
{
    orl_table_index     idx;

    if( sechdl == NULL )
        return( NULL );
    idx = ORLCvtSecHdlToIdx( sechdl );
    if( idx == 0 ) {
        return( NULL );
    } else {
        return( FindNode( SegNodes, idx ) );
    }
}

#define PREFIX_LEN (sizeof(ImportSymPrefix) - 1)

static void ImpProcSymbol( segnode *snode, orl_symbol_type type, char *name,
                           size_t namelen )
/***************************************************************************/
{
    if( type & ORL_SYM_TYPE_UNDEFINED ) {
        if( namelen > sizeof(CoffImportRefName) - 1 ) {
            namelen -= sizeof(CoffImportRefName) - 1;
            if( memicmp( name + namelen, CoffImportRefName,
                         sizeof(CoffImportRefName) - 1 ) == 0 ) {
                _ChkAlloc( ImpModName, namelen + 5 );
                memcpy( ImpModName, name, namelen );
                if( memicmp( CurrMod->name + strlen(CurrMod->name)
                             - 4, ".drv", 4 ) == 0 ) { //KLUDGE!!
                    memcpy( ImpModName + namelen, ".drv", 5 );
                } else {
                    memcpy( ImpModName + namelen, ".dll", 5 );
                }
            }
        }
    } else if( snode != NULL && snode->info & SEG_CODE ) {
        if( FirstCodeSymName == NULL ) {
            FirstCodeSymName = name;
        }
    } else {
        if( FirstDataSymName == NULL &&
                memcmp( name, ImportSymPrefix, PREFIX_LEN ) == 0 ) {
            FirstDataSymName = name + PREFIX_LEN;
        }
    }
}

static void DefineComdatSym( segnode *seg, symbol *sym, orl_symbol_value value )
/******************************************************************************/
{
    unsigned    select;
    sym_info    sym_type;
    segdata     *sdata;

    sdata = seg->entry;
    sdata->hascdatsym = TRUE;
    select = sdata->select;
    if( select == 0 ) {
        sym_type = SYM_CDAT_SEL_ANY;
    } else {
        sym_type = (select - 1) << SYM_CDAT_SEL_SHIFT;
    }
    DefineComdat( sdata, sym, value, sym_type, seg->contents );
}

static orl_return ProcSymbol( orl_symbol_handle symhdl )
/******************************************************/
{
    orl_symbol_type     type;
    char                *name;
    orl_symbol_value    value;
    orl_sec_handle      sechdl;
    symbol              *sym;
    size_t              namelen;
    sym_flags           symop;
    extnode             *newnode;
    segnode             *snode;
    bool                isweak;
    orl_symbol_handle   assocsymhdl;
    symbol              *assocsym;
    orl_symbol_binding  binding;

    sechdl = ORLSymbolGetSecHandle( symhdl );
    snode = FindSegNode( sechdl );
    type = ORLSymbolGetType( symhdl );
    name = ORLSymbolGetName( symhdl );
	DEBUG((DBG_OLD, "objorl.ProcSymbol(%s) enter", name ));
    if( type & ORL_SYM_TYPE_FILE ) {
        if( !(CurrMod->modinfo & MOD_GOT_NAME) ) {
            CurrMod->modinfo |= MOD_GOT_NAME;
            _LnkFree( CurrMod->name );
            CurrMod->name = AddStringStringTable( &PermStrings, name );
        }
        return( ORL_OKAY );
    }
    if( type & ORL_SYM_TYPE_DEBUG )
        return( ORL_OKAY );
    if( type & (ORL_SYM_TYPE_OBJECT|ORL_SYM_TYPE_FUNCTION) ||
        (type & (ORL_SYM_TYPE_NOTYPE|ORL_SYM_TYPE_UNDEFINED) &&
         name != NULL)) {
        namelen = strlen( name );
        if( namelen == 0 ) {
            DEBUG((DBG_OLD, "objorl.ProcSymbol(): error, namelen == 0" ));
            BadObject();
        }

        /* jwlink: this is probably not correct. Not all symbols in an import lib
         * are necessarily to be handled by ImpProcSymbol()
         */
        if( CurrMod->modinfo & MOD_IMPORT_LIB ) {
            DEBUG((DBG_OLD, "objorl.ProcSymbol(): calling ImpProcSymbol()" ));
            ImpProcSymbol( snode, type, name, namelen );
            return( ORL_OKAY );
        }

        newnode = AllocNode( ExtNodes );
        newnode->handle = symhdl;
        binding = ORLSymbolGetBinding( symhdl );
        symop = ST_CREATE;
        if( binding == ORL_SYM_BINDING_LOCAL ) {
            //symop |= ST_STATIC;
            symop |= ST_STATIC | ST_DUPLICATE;
        }
        if( type & ORL_SYM_TYPE_UNDEFINED && binding != ORL_SYM_BINDING_ALIAS ){
            symop |= ST_REFERENCE;
        } else {
            symop |= ST_NOALIAS;
        }
        sym = SymOp( symop, name, namelen );
        CheckIfTocSym( sym );
        if( type & ORL_SYM_TYPE_COMMON ) {
			DEBUG((DBG_OLD, "objorl.ProcSymbol(%s): type ORL_SYM_TYPE_COMMON", name ));
            value = ORLSymbolGetValue( symhdl );
            sym = MakeCommunalSym( sym, value, FALSE, TRUE );
        } else if( type & ORL_SYM_TYPE_UNDEFINED ) {
			DEBUG((DBG_OLD, "objorl.ProcSymbol(%s): type ORL_SYM_TYPE_UNDEFINED", name ));
            DefineReference( sym );
            isweak = FALSE;
            switch( binding ) {
            case ORL_SYM_BINDING_WEAK:
                isweak = TRUE;
            case ORL_SYM_BINDING_ALIAS:
            case ORL_SYM_BINDING_LAZY:
                assocsymhdl = ORLSymbolGetAssociated( symhdl );
                name = ORLSymbolGetName( assocsymhdl );
                namelen = strlen(name);
                if( binding == ORL_SYM_BINDING_ALIAS ) {
                    MakeSymAlias( sym->name, strlen(sym->name), name, namelen );
                } else {
                    assocsym = SymOp( ST_CREATE | ST_REFERENCE, name, namelen );
                    DefineLazyExtdef( sym, assocsym, isweak );
                    newnode->isweak = TRUE;
                }
            }
        } else {
			DEBUG((DBG_OLD, "objorl.ProcSymbol(%s): type=%h", name, type ));
            newnode->isdefd = TRUE;
            value = ORLSymbolGetValue( symhdl );
            if( type & ORL_SYM_TYPE_COMMON && type & ORL_SYM_TYPE_OBJECT
                        && sechdl == NULL) {
                sym = MakeCommunalSym( sym, value, FALSE, TRUE );
            } else if( snode != NULL && snode->entry != NULL
                                     && snode->entry->iscdat ) {
                DefineComdatSym( snode, sym, value );
            } else {
				DEBUG((DBG_OLD, "objorl.ProcSymbol(%s info=%h): calling DefineSymbol", name, sym->info ));
                sym->info |= SYM_DEFINED;
                DefineSymbol( sym, snode, value, 0 );
            }
        }
        newnode->entry = sym;
    } else if( type & ORL_SYM_TYPE_SECTION && type & ORL_SYM_CDAT_MASK
                            && snode != NULL && !(snode->info & SEG_DEAD) ) {
        snode->entry->select = (type & ORL_SYM_CDAT_MASK) >> ORL_SYM_CDAT_SHIFT;
    }
    return( ORL_OKAY );
}

static orl_return SymTable( orl_sec_handle sec )
/**********************************************/
{
    return( ORLSymbolSecScan( sec, ProcSymbol ) );
}

static orl_return DoReloc( orl_reloc *reloc )
/*******************************************/
{
    fix_type    type;
    frame_spec  frame;
    frame_spec  targ;
    offset      addend;
    unsigned    adjust;
    segnode     *seg;
    segnode     *symseg;
    extnode     *ext;
    bool        skip;
    bool        istoc;

	DEBUG((DBG_OLD, "objorl.DoReloc(): enter" ));
    skip = FALSE;
    istoc = FALSE;
    type = 0;
    switch( reloc->type ) {
    case ORL_RELOC_TYPE_PAIR:
        skip = TRUE;
        break;
    case ORL_RELOC_TYPE_ABSOLUTE:
        type = FIX_OFFSET_32 | FIX_ABS;
        break;
    case ORL_RELOC_TYPE_WORD_16:
        type = FIX_OFFSET_16;
        break;
    case ORL_RELOC_TYPE_WORD_26:
        type = FIX_OFFSET_26 | FIX_SHIFT;
        break;
    case ORL_RELOC_TYPE_TOCREL_14:  // relative ref to 14-bit offset from TOC base.
        type = FIX_SHIFT;           // NOTE fall through
    case ORL_RELOC_TYPE_TOCREL_16:  // relative ref to 16-bit offset from TOC base.
    case ORL_RELOC_TYPE_GOT_16:     // relative ref to 16-bit offset from TOC base.
        type |= FIX_TOC | FIX_OFFSET_16;
        istoc = TRUE;
        break;
    case ORL_RELOC_TYPE_TOCVREL_14:  // relative ref to 14-bit offset from TOC base.
        type = FIX_SHIFT;        // NOTE fall through
    case ORL_RELOC_TYPE_TOCVREL_16:  // relative ref to 16-bit offset from TOC base.
        type |= FIX_TOCV | FIX_OFFSET_16;
        break;
    case ORL_RELOC_TYPE_IFGLUE:
        type = FIX_IFGLUE | FIX_OFFSET_32;
        break;
    case ORL_RELOC_TYPE_IMGLUE:
        skip = TRUE;                 // NYI: do we need this?
        break;
    case ORL_RELOC_TYPE_JUMP:
        type = FIX_OFFSET_32 | FIX_REL;
        break;
    case ORL_RELOC_TYPE_REL_21_SH:
        type = FIX_OFFSET_21 | FIX_REL | FIX_SHIFT;
        break;
    case ORL_RELOC_TYPE_REL_24:
        type = FIX_OFFSET_24 | FIX_REL;
        break;
    case ORL_RELOC_TYPE_REL_32:
        type = FIX_OFFSET_32 | FIX_REL;
        break;
    case ORL_RELOC_TYPE_REL_32_NOADJ:
        type = FIX_OFFSET_32 | FIX_REL | FIX_NOADJ;
        break;
    case ORL_RELOC_TYPE_SEGMENT:
        type = FIX_BASE;
        break;
    case ORL_RELOC_TYPE_WORD_32_NB:
        type = FIX_OFFSET_32 | FIX_NO_BASE;
        break;
    case ORL_RELOC_TYPE_SEC_REL:
        type = FIX_OFFSET_32 | FIX_SEC_REL;
        break;
    case ORL_RELOC_TYPE_SECTION:
        type = FIX_BASE;
        break;
    case ORL_RELOC_TYPE_WORD_32:
        type = FIX_OFFSET_32;
        if ( FmtData.u.pe.win64 && ( LinkState & MAKE_RELOCS ) && ( FmtData.u.pe.nolargeaddressaware == 0 ) ) {
            LnkMsg( ERR+MSG_NEED_NOLARGEADDRESSAWARE, "s", ORLSymbolGetName( reloc->symbol ) );
        }
        break;
    case ORL_RELOC_TYPE_GOT_32:     // relative ref to 32-bit offset from TOC base.
        type = FIX_OFFSET_32 | FIX_TOC;
        break;
    case ORL_RELOC_TYPE_HALF_HI:
    case ORL_RELOC_TYPE_HALF_HA:
        SavedReloc = *reloc;
        skip = TRUE;
        break;
    case ORL_RELOC_TYPE_HALF_LO:
        if( SavedReloc.type == ORL_RELOC_TYPE_NONE ) {    // we recursed
            type = FIX_OFFSET_16 | FIX_SIGNED;
        } else {
            SavedReloc.type = ORL_RELOC_TYPE_NONE;      // flag recursion
            DoReloc( reloc );
            reloc = &SavedReloc;
            type = FIX_HIGH_OFFSET_16;
        }
        break;
    case ORL_RELOC_TYPE_REL_32_ADJ1: /* jwlink */
    case ORL_RELOC_TYPE_REL_32_ADJ2: // relative ref to a 32-bit address, need special adjustment
    case ORL_RELOC_TYPE_REL_32_ADJ3:
    case ORL_RELOC_TYPE_REL_32_ADJ4:
    case ORL_RELOC_TYPE_REL_32_ADJ5:
        adjust = reloc->type - ORL_RELOC_TYPE_REL_32_ADJ1 + 1;
        /* jwlink: store adjustment in upper 4 bits of type */
        type = FIX_OFFSET_32 | FIX_REL | (adjust << 28);
        //printf( "32-bit PC-relative fixup %X at %X, adjust=%u\n", reloc->type, reloc->offset, adjust );
        break;
    case ORL_RELOC_TYPE_WORD_64: /* jwlink */
        type = FIX_OFFSET_64;
        break;
    case ORL_RELOC_TYPE_NONE:
    default:
        printf( "unknown reloc type %X at %s:%X\n", reloc->type, ORLSecGetName( reloc->section ), reloc->offset );
        LnkMsg( LOC+ERR+MSG_BAD_RELOC_TYPE, NULL );
        skip = TRUE;
        break;
    }
    if( !skip ) {
        seg = FindSegNode( reloc->section );
        DEBUG(( DBG_OLD, "DoReloc(): seg=%s", seg ? seg->entry->u.leader->segname : "NULL" ))
        addend = 0;
        if( seg != NULL && !(seg->info & SEG_DEAD) && seg->entry != NULL
                                                   && !seg->entry->isdead ) {
            SetCurrSeg( seg->entry, 0, seg->contents );
            frame.type = FIX_FRAME_TARG;
            ext = FindExtHandle( reloc->symbol );
            if( ext == NULL ) {
                symseg = FindSegNode( ORLSymbolGetSecHandle(reloc->symbol) );
                if( symseg != NULL && !(seg->info & SEG_DEAD) ) {
                    addend = ORLSymbolGetValue( reloc->symbol );
                    targ.u.sdata = symseg->entry;
                    targ.type = FIX_FRAME_SEG;
                    if( istoc ) {
                        AddSdataOffToToc( symseg->entry, addend );
                    }
                } else {
                    skip = TRUE;
                }
            } else {
                targ.u.sym = ext->entry;
                targ.type = FIX_FRAME_EXT;
                if( istoc ) {
                    AddSymToToc( targ.u.sym );
                }
            }
            if( !skip ) {
                StoreFixup( reloc->offset, type, &frame, &targ, addend );
            }
        }
    }
    return( ORL_OKAY );
}

static orl_return P1Relocs( orl_sec_handle sec )
/**********************************************/
{
    return( ORLRelocSecScan( sec, DoReloc ) );
}

static void HandleImportSymbol( char *name )
/******************************************/
{
    length_name intname;
    length_name modname;
    length_name extname;

    intname.name = name;
    intname.len = strlen(name);
    if( ImpModName == NULL ) {
        ImpModName = FileName( CurrMod->name,strlen(CurrMod->name),E_DLL,FALSE);
    }
    modname.name = ImpModName;
    modname.len = strlen(ImpModName);
    if( ImpExternalName == NULL ) {
        if( ImpOrdinal == 0 ) {
            ImpOrdinal = NOT_IMP_BY_ORDINAL;
        } else {
            ImpOrdinal &= 0x7FFFFFFF;           // get rid of that high bit
        }
        HandleImport( &intname, &modname, &intname, ImpOrdinal );
    } else {
        extname.name = ImpExternalName;
        extname.len = strlen(ImpExternalName);
        HandleImport( &intname, &modname, &extname, NOT_IMP_BY_ORDINAL );
    }
    _LnkFree( ImpModName );
    ImpModName = NULL;
}

static void ScanImported( void )
/******************************/
{
    if( CurrMod->modinfo & MOD_IMPORT_LIB ) {
        if( FirstCodeSymName != NULL ) {
            HandleImportSymbol( FirstCodeSymName );
        } else if( FirstDataSymName != NULL ) {
            HandleImportSymbol( FirstDataSymName );
        }
    }
}

static orl_sec_return_func SegmentJumpTable[] = {
    NullFunc,           // ORL_SEC_TYPE_NONE
    DeclareSegment,     // ORL_SEC_TYPE_NO_BITS (bss)
    DeclareSegment,     // ORL_SEC_TYPE_PROG_BITS
    NullFunc,           // ORL_SEC_TYPE_SYM_TABLE
    NullFunc,           // ORL_SEC_TYPE_DYN_SYM_TABLE
    NullFunc,           // ORL_SEC_TYPE_STR_TABLE
    NullFunc,           // ORL_SEC_TYPE_RELOCS
    NullFunc,           // ORL_SEC_TYPE_RELOCS_EXPAND
    NullFunc,           // ORL_SEC_TYPE_HASH
    NullFunc,           // ORL_SEC_TYPE_DYNAMIC
    NullFunc,           // ORL_SEC_TYPE_NOTE
    NullFunc,           // ORL_SEC_TYPE_LINK_INFO
};

static orl_sec_return_func SymbolJumpTable[] = {
    NullFunc,           // ORL_SEC_TYPE_NONE
    NullFunc,           // ORL_SEC_TYPE_NO_BITS (bss)
    NullFunc,           // ORL_SEC_TYPE_PROG_BITS
    SymTable,           // ORL_SEC_TYPE_SYM_TABLE
    NullFunc,           // ORL_SEC_TYPE_DYN_SYM_TABLE
    NullFunc,           // ORL_SEC_TYPE_STR_TABLE
    NullFunc,           // ORL_SEC_TYPE_RELOCS
    NullFunc,           // ORL_SEC_TYPE_RELOCS_EXPAND
    NullFunc,           // ORL_SEC_TYPE_HASH
    NullFunc,           // ORL_SEC_TYPE_DYNAMIC
    NullFunc,           // ORL_SEC_TYPE_NOTE
    NullFunc            // ORL_SEC_TYPE_LINK_INFO
};

static orl_sec_return_func P1SpecificJumpTable[] = {
    NullFunc,           // ORL_SEC_TYPE_NONE
    NullFunc,           // ORL_SEC_TYPE_NO_BITS (bss)
    NullFunc,           // ORL_SEC_TYPE_PROG_BITS
    NullFunc,           // ORL_SEC_TYPE_SYM_TABLE
    Unsupported,        // ORL_SEC_TYPE_DYN_SYM_TABLE
    NullFunc,           // ORL_SEC_TYPE_STR_TABLE
    P1Relocs,           // ORL_SEC_TYPE_RELOCS
    P1Relocs,           // ORL_SEC_TYPE_RELOCS_EXPAND
    NullFunc,           // ORL_SEC_TYPE_HASH
    Unsupported,        // ORL_SEC_TYPE_DYNAMIC
    P1Note,             // ORL_SEC_TYPE_NOTE
    NullFunc            // ORL_SEC_TYPE_LINK_INFO
};

static orl_return ProcSegments( orl_sec_handle hdl )
/**************************************************/
{
    return( (SegmentJumpTable[ORLSecGetType( hdl )])( hdl ) );
}

static orl_return ProcSymbols( orl_sec_handle hdl )
/*********************************************/
{
    return( (SymbolJumpTable[ORLSecGetType( hdl )])( hdl ) );
}

static orl_return ProcP1Specific( orl_sec_handle hdl )
/****************************************************/
{
    return( (P1SpecificJumpTable[ORLSecGetType( hdl )])( hdl ) );
}

unsigned long ORLPass1( void )
/***********************************/
// do pass 1 for an object file handled by ORL.
{
    orl_file_handle     filehdl;

    /* jwlink: why setting dosseg? */
    //LinkState |= DOSSEG_FLAG;

    DEBUG((DBG_OLD, "objorl.ORLPass1(): CurrMod=%s", CurrMod->f.source->file->name ));
    PermStartMod( CurrMod );
    filehdl = InitFile();
    if( filehdl == NULL ) {
        LnkMsg( FTL+MSG_BAD_OBJECT, "s", CurrMod->f.source->file->name );
        CurrMod->f.source->file->flags |= INSTAT_IOERR;
        return( -1 );
    }
    if( CheckFlags( filehdl ) ) {
        if( LinkState & HAVE_PPC_CODE && !FmtData.toc_initialized ) {
            InitToc();
            FmtData.toc_initialized = 1;
        }
        if( LinkFlags & DWARF_DBI_FLAG ) {
            CurrMod->modinfo |= MOD_FLATTEN_DBI;
        }
        CurrMod->modinfo |= MOD_NEED_PASS_2;
        ORLFileScan( filehdl, NULL, ProcSegments );
        IterateNodelist( SegNodes, AllocSeg, NULL );
        ORLFileScan( filehdl, NULL, ProcSymbols );
        ScanImported();
        ORLFileScan( filehdl, NULL, ProcP1Specific );
        IterateNodelist( SegNodes, DefNosymComdats, NULL );
    }
    FiniFile( filehdl, CurrMod->f.source );
    return( ORLSeek( CurrMod->f.source, 0, SEEK_CUR ) );
}
