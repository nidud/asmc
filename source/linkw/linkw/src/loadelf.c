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
* Description:  Routines for creating ELF executable images.
*
****************************************************************************/


/*
-----------
Historical note - the ELF output support in wlink was initially developed
for IBM's OS/2 for PowerPC which used ELF, hence references to OS/2.
-----------

Layout of OS/2 ELF Executable:

----------------------------------------------------------------------------
Elf header
----------------------------------------------------------------------------
Program headers:
----------------------------------------------------------------------------
Groups data
----------------------------------------------------------------------------
Various symbol tables
----------------------------------------------------------------------------
Debug data (for dwarf)
----------------------------------------------------------------------------
Section headers:    - Empty unused section
                    - Section for each group in Groups
                    - Various symbol tables sections
                    - Relocations
----------------------------------------------------------------------------
String table for sections
----------------------------------------------------------------------------
*/

#include <string.h>
#include "walloca.h"
#include "linkstd.h"
#include "exeelf.h"
#include "loadelf.h"
#include "loadelf2.h"
#include "reloc.h"
#include "alloc.h"
#include "strtab.h"
#include "impexp.h"
#include "specials.h"
#include "loadfile.h"
#include "wlnkmsg.h"
#include "msg.h"
#include "virtmem.h"
#include "fileio.h"
#include "dbgcomm.h"
#include "dbgall.h"
#include "dbgdwarf.h"
#include "objcalc.h"

#define DEFAULT_SEG_SHIFT       12      /* Corresponds to 2^12 == 4096 bytes */
#define PHDRSECT 0

static stringtable      SymStrTab;
static ElfSymTable *    ElfSymTab;

/* Put debugging info into section WITHIN the file instead of appending a
 * separate elf file at the end */

#define INJECT_DEBUG ( SymFileName == NULL && LinkFlags & DWARF_DBI_FLAG )

static void AddSecIdxName( ElfHdr *hdr, int idx, char *name )
/***********************************************************/
{
    if( idx == 0 )
		return;
	if ( FmtData.u.elf.elf64 ) {
		Elf64_Shdr *sh64 = hdr->sh64+idx;
		sh64->sh_name = AddSecName( hdr, name );
	} else {
		Elf32_Shdr *sh32 = hdr->sh32+idx;
		sh32->sh_name = AddSecName( hdr, name );
	};
}


static void InitSections( ElfHdr *hdr)
/************************************/
{
    int         num;
    group_entry *group;

    num = 1;
    memset( &hdr->i, 0, sizeof hdr->i );
    hdr->i.secstr = num++;
	if ( FmtData.u.elf.elf64 )
		hdr->eh64.e_shstrndx = hdr->i.secstr;
	else
		hdr->eh32.e_shstrndx = hdr->i.secstr;
    hdr->i.grpbase = num;
    hdr->i.grpnum = NumGroups;
    if( FmtData.dgroupsplitseg != NULL ) {
        hdr->i.grpnum++;
        if( StackSegPtr != NULL ) {
            hdr->i.grpnum++;
        }
    }
    num += hdr->i.grpnum;
    hdr->i.relbase = num;
    for( group = Groups; group != NULL; group = group->next_group ) {
        if( group->g.grp_relocs != NULL ) {
            hdr->i.relnum++;
        }
    }
    num += hdr->i.relnum;
    hdr->i.symtab = num++;
    hdr->i.symstr = num++;
    hdr->i.symhash = num++;
    if( INJECT_DEBUG ) {
        hdr->i.dbgnum = DwarfCountDebugSections();
    }
    hdr->i.dbgbegin = num;
    num += hdr->i.dbgnum;
    num += FmtData.u.elf.extrasects;
    if ( FmtData.u.elf.elf64 ) {
		hdr->eh64.e_shnum = num;
        hdr->sh_size = sizeof(Elf64_Shdr) * hdr->eh64.e_shnum;
    } else {
		hdr->eh32.e_shnum = num;
        hdr->sh_size = sizeof(Elf32_Shdr) * hdr->eh32.e_shnum;
    }
    _ChkAlloc( hdr->sh32, hdr->sh_size );
    memset( hdr->sh32, 0, hdr->sh_size );
    AddSecIdxName(hdr, hdr->i.symtab, ".symtab");
}

static void SetHeaders( ElfHdr *hdr )
/***********************************/
{
    memcpy( hdr->eh32.e_ident, ELF_SIGNATURE, ELF_SIGNATURE_LEN );
#ifdef __BIG_ENDIAN__
    hdr->eh32.e_ident[EI_DATA] = ELFDATA2MSB;
#else
    hdr->eh32.e_ident[EI_DATA] = ELFDATA2LSB;
#endif
    hdr->eh32.e_ident[EI_VERSION] = EV_CURRENT;
    hdr->eh32.e_ident[EI_OSABI] = FmtData.u.elf.abitype;
    hdr->eh32.e_ident[EI_ABIVERSION] = FmtData.u.elf.abiversion;
    memset( &hdr->eh32.e_ident[EI_PAD], 0, EI_NIDENT - EI_PAD );
    hdr->eh32.e_type = ET_EXEC;
    if( LinkState & HAVE_PPC_CODE ) {
        hdr->eh32.e_machine = EM_PPC;
    } else if( LinkState & HAVE_MIPS_CODE ) {
        hdr->eh32.e_machine = EM_MIPS;
    } else if ( FmtData.u.elf.elf64 ) {
        hdr->eh32.e_machine = EM_X86_64;
    } else {
        hdr->eh32.e_machine = EM_386;
    }
	hdr->eh32.e_version = EV_CURRENT;

    /* EHdr for 32- and 64-bit is identical up to e_version */

    if ( FmtData.u.elf.elf64 ) {
        hdr->eh64.e_ident[EI_CLASS] = ELFCLASS64;
		if( StartInfo.type == START_UNDEFED ) {
			hdr->eh64.e_entry = 0;
		} else {
			hdr->eh64.e_entry = FindLinearAddr2( &StartInfo.addr );
		}
		hdr->eh64.e_flags = 0;
        hdr->eh64.e_ehsize = sizeof(Elf64_Ehdr);
        hdr->eh64.e_phentsize = sizeof(Elf64_Phdr);
		hdr->eh64.e_shentsize = sizeof(Elf64_Shdr);
#if PHDRSECT
		hdr->eh64.e_phnum = NumGroups + 1;
#else
		hdr->eh64.e_phnum = NumGroups;
#endif
        hdr->eh64.e_phoff = sizeof(Elf64_Ehdr);
        hdr->ph_size = sizeof(Elf64_Phdr) * hdr->eh64.e_phnum;
		_ChkAlloc( hdr->ph64, hdr->ph_size );
#if PHDRSECT
        /* set the first program header */
        hdr->ph64->p_type = PT_PHDR;
        hdr->ph64->p_offset = sizeof(Elf64_Ehdr);
        hdr->ph64->p_vaddr = sizeof(Elf64_Ehdr) + FmtData.base;
		hdr->ph64->p_paddr = 0;
		hdr->ph64->p_filesz = hdr->ph_size;
		hdr->ph64->p_memsz = hdr->ph_size;
		hdr->ph64->p_flags = PF_R | PF_X;
		hdr->ph64->p_align = 0;
#endif
	} else {
		hdr->eh32.e_ident[EI_CLASS] = ELFCLASS32;
		if( StartInfo.type == START_UNDEFED ) {
			hdr->eh32.e_entry = 0;
		} else {
			hdr->eh32.e_entry = FindLinearAddr2( &StartInfo.addr );
		}
		hdr->eh32.e_flags = 0;
        hdr->eh32.e_ehsize = sizeof(Elf32_Ehdr);
        hdr->eh32.e_phentsize = sizeof(Elf32_Phdr);
        hdr->eh32.e_shentsize = sizeof(Elf32_Shdr);
#if PHDRSECT
        hdr->eh32.e_phnum = NumGroups + 1;
#else
		hdr->eh32.e_phnum = NumGroups;
#endif
        hdr->eh32.e_phoff = sizeof(Elf32_Ehdr);
        hdr->ph_size = sizeof(Elf32_Phdr) * hdr->eh32.e_phnum;
        _ChkAlloc( hdr->ph32, hdr->ph_size );
#if PHDRSECT
        hdr->ph32->p_type = PT_PHDR;
        hdr->ph32->p_offset = sizeof(Elf32_Ehdr);
        hdr->ph32->p_vaddr = sizeof(Elf32_Ehdr) + FmtData.base;
		hdr->ph32->p_paddr = 0;
		hdr->ph32->p_filesz = hdr->ph_size;
		hdr->ph32->p_memsz = hdr->ph_size;
		hdr->ph32->p_flags = PF_R | PF_X;
		hdr->ph32->p_align = 0;
#endif
	}

    InitStringTable( &hdr->secstrtab, FALSE );
    AddCharStringTable( &hdr->secstrtab, '\0' );
    InitSections( hdr );
#if PHDRSECT
	if ( FmtData.u.elf.elf64 )
		hdr->curr_off = hdr->eh64.e_ehsize + hdr->ph_size;
	else
		hdr->curr_off = hdr->eh32.e_ehsize + hdr->ph_size;
	hdr->curr_off = ROUND_UP( hdr->curr_off, 0x100 );
	SeekLoad( hdr->curr_off );
#else
    hdr->curr_off = 0;
#endif
}

unsigned GetElfHeaderSize( void )
/**************************************/
{
    unsigned    size;

#if PHDRSECT
    if ( FmtData.u.elf.elf64 )
        size = sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) * (NumGroups + 1);
    else
		size = sizeof(Elf32_Ehdr) + sizeof(Elf32_Phdr) * (NumGroups + 1);
    return ROUND_UP( size, 0x100 );
#else
    if ( FmtData.u.elf.elf64 )
        size = sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) * NumGroups;
    else
		size = sizeof(Elf32_Ehdr) + sizeof(Elf32_Phdr) * NumGroups;
    return ( size );
#endif
}

//unsigned_32 AddSecName( ElfHdr *hdr, Elf32_Shdr *sh, char *name )
unsigned_32 AddSecName( ElfHdr *hdr, char *name )
/*************************************************/
{
    unsigned_32 result;
    //sh->sh_name = GetStringTableSize( &hdr->secstrtab );
    result = GetStringTableSize( &hdr->secstrtab );
	AddStringStringTable( &hdr->secstrtab, name );
    return( result );
}


static void WriteSHStrings( ElfHdr *hdr, char *name, int str_idx, stringtable *strtab )
/*************************************************************************/
{
    if ( FmtData.u.elf.elf64 ) {
        Elf64_Shdr *sh64;
        sh64 = hdr->sh64+str_idx;
        sh64->sh_name = AddSecName( hdr, name );

        sh64->sh_offset = hdr->curr_off;
        sh64->sh_type = SHT_STRTAB;
        sh64->sh_size = GetStringTableSize( strtab );
        hdr->curr_off += sh64->sh_size;
        DEBUG(( DBG_OLD, "WriteSHStrings(): %s sh_offset=%h sh_size=%h",
               name, sh64->sh_offset, sh64->sh_size ));
    } else {
        Elf32_Shdr *sh32;
        sh32 = hdr->sh32+str_idx;
        sh32->sh_name = AddSecName( hdr, name );

        sh32->sh_offset = hdr->curr_off;
        sh32->sh_type = SHT_STRTAB;
        sh32->sh_size = GetStringTableSize( strtab );
        hdr->curr_off += sh32->sh_size;
        DEBUG(( DBG_OLD, "WriteSHStrings(): %s sh_offset=%h sh_size=%h",
               name, sh32->sh_offset, sh32->sh_size ));
    }
    WriteStringTable( strtab, WriteLoad3, NULL );
}

static void SetGroupHeaders32( group_entry *group, offset off, Elf32_Phdr *ph,
                             Elf32_Shdr *sh )
/**************************************************************************/
{
    sh->sh_type = SHT_PROGBITS;
    sh->sh_flags = SHF_ALLOC;
    ph->p_flags = PF_R;
    if( group->segflags & SEG_READ_ONLY ) { /* jwlink */
    } else if( group->segflags & SEG_DATA ) {
        sh->sh_flags |= SHF_WRITE;
        ph->p_flags |= PF_W;
    } else { // if code group
        sh->sh_flags |= SHF_EXECINSTR;
        ph->p_flags |= PF_X;
    }
    sh->sh_addr = ph->p_vaddr = group->linear + FmtData.base;
    ph->p_type = PT_LOAD;
    ph->p_filesz = sh->sh_size = group->size;
    ph->p_memsz = group->totalsize;
    if( group == DataGroup && StackSegPtr != NULL ) {
        ph->p_memsz -= StackSize;
    }
    sh->sh_link = SHN_UNDEF;
    sh->sh_info = 0;
    //sh->sh_addralign = 4;  /* ??? */
    if ( group->leaders )
        sh->sh_addralign = ( 1 << group->leaders->align );
    else
        sh->sh_addralign = 4;
    sh->sh_entsize = 0;
    ph->p_offset = sh->sh_offset = off;  /* offset in file */
    ph->p_paddr = 0;
    ph->p_align = FmtData.objalign;
}

static void SetGroupHeaders64( group_entry *group, offset off, Elf64_Phdr *ph,
                             Elf64_Shdr *sh )
/**************************************************************************/
{
    sh->sh_type = SHT_PROGBITS;
    sh->sh_flags = SHF_ALLOC;
    ph->p_flags = PF_R;
    if( group->segflags & SEG_READ_ONLY ) { /* jwlink */
    } else if( group->segflags & SEG_DATA ) {
        sh->sh_flags |= SHF_WRITE;
        ph->p_flags |= PF_W;
    } else { // if code group
        sh->sh_flags |= SHF_EXECINSTR;
        ph->p_flags |= PF_X;
    }
    sh->sh_addr = ph->p_vaddr = group->linear + FmtData.base;
    ph->p_type = PT_LOAD;
    ph->p_filesz = sh->sh_size = group->size;
    ph->p_memsz = group->totalsize;
    if( group == DataGroup && StackSegPtr != NULL ) {
        ph->p_memsz -= StackSize;
    }
    sh->sh_link = SHN_UNDEF;
    sh->sh_info = 0;
    //sh->sh_addralign = 4;  /* ??? */
    if ( group->leaders )
        sh->sh_addralign = ( 1 << group->leaders->align );
    else
        sh->sh_addralign = 4;
    sh->sh_entsize = 0;
    ph->p_offset = sh->sh_offset = off; /* offset in file */
    ph->p_paddr = 0;
    ph->p_align = FmtData.objalign;
}

static void InitBSSSect32( Elf32_Shdr *sh, offset off, offset size, offset start, int alignment )
/******************************************************************************/
{
    sh->sh_type = SHT_NOBITS;
    sh->sh_flags = SHF_ALLOC | SHF_WRITE;
    sh->sh_addr = start;
    sh->sh_offset = off;
    sh->sh_size = size;
    sh->sh_link = SHN_UNDEF;
    sh->sh_info = 0;
    sh->sh_addralign = alignment;
    sh->sh_entsize = 0;
}
static void InitBSSSect64( Elf64_Shdr *sh, offset off, offset size, offset start, int alignment )
/******************************************************************************/
{
    sh->sh_type = SHT_NOBITS;
    sh->sh_flags = SHF_ALLOC | SHF_WRITE;
    sh->sh_addr = start;
    sh->sh_offset = off;
    sh->sh_size = size;
    sh->sh_link = SHN_UNDEF;
    sh->sh_info = 0;
    sh->sh_addralign = alignment;
    sh->sh_entsize = 0;
}

static char * GroupSecName( group_entry *group )
/**********************************************/
{
    if( group->segflags & SEG_READ_ONLY ) {
        return ".rodata";
    } else if( group->segflags & SEG_DATA ) {
        return ".data";
    } else {
        return ".text";
    }
}

static void WriteELFGroups( ElfHdr *hdr )
/***************************************/
{
    group_entry *group;
    offset      off;
	offset      linear;
	unsigned alignment;
#if PHDRSECT==0
    bool first = TRUE;
#endif


    DEBUG(( DBG_OLD, "WriteELFGroups() enter" ));
    off = hdr->curr_off;
	if ( FmtData.u.elf.elf64 ) {
		Elf64_Shdr *sh64;
		Elf64_Phdr *ph64;
		sh64 = hdr->sh64 + hdr->i.grpbase;
#if PHDRSECT
		ph64 = hdr->ph64 + 1;
#else
		ph64 = hdr->ph64;
#endif
		for( group = Groups; group != NULL; group = group->next_group ) {
			if( group->totalsize == 0 ) continue;   // DANGER DANGER DANGER <--!!!
			off = ( off & ~(FmtData.objalign - 1) ) + ( group->linear & (FmtData.objalign - 1) );
			SetGroupHeaders64( group, off, ph64, sh64 );
#if PHDRSECT==0
			if ( first ) {
				ph64->p_filesz  += ph64->p_offset;
				ph64->p_memsz   += ph64->p_offset;
				ph64->p_vaddr   -= ph64->p_offset;
				ph64->p_offset  = 0;
				first = FALSE;
			}
#endif
			SeekLoad( off );
			DEBUG(( DBG_OLD, "WriteELFGroups(): %s grp.totalsize=%h p_vaddr=%h sh_addr=%h off=%h", GroupSecName( group ), group->totalsize, ph64->p_vaddr, sh64->sh_addr, off ));
			WriteGroupLoad( group );
			off += group->size;

			sh64->sh_name = AddSecName( hdr, GroupSecName(group) );
			sh64++;
			if( group == DataGroup && FmtData.dgroupsplitseg != NULL ) {
				sh64->sh_name = AddSecName( hdr, ".bss" );
				DEBUG(( DBG_OLD, "WriteELFGroups(): .bss split from %s group", GroupSecName( group ) ));
				if ( group->alignment > ( 1 << FmtData.u.elf.segment_shift ) ) {
					alignment = group->alignment;
				} else
					alignment = 1 << FmtData.u.elf.segment_shift;
				linear = ph64->p_vaddr + ROUND_UP( ph64->p_filesz, alignment );
				InitBSSSect64( sh64, off, CalcSplitSize(), linear, alignment );
				DEBUG(( DBG_OLD, "WriteELFGroups(): .bss sh_addr=%h sh_offset=%h sh_size=%h", sh64->sh_addr, sh64->sh_offset, sh64->sh_size ));
				linear = ROUND_UP( linear + sh64->sh_size, alignment );
				sh64++;
				if( StackSegPtr != NULL ) {
					sh64->sh_name = AddSecName( hdr, ".stack" );
					InitBSSSect64( sh64, off, StackSize, linear, alignment );
					DEBUG(( DBG_OLD, "WriteELFGroups(): .stack size=%h", sh64->sh_size ));
					sh64++;
				}
			}
			ph64++;
		}
	} else {
		Elf32_Shdr *sh32;
		Elf32_Phdr *ph32;
		sh32 = hdr->sh32 + hdr->i.grpbase;
#if PHDRSECT
		ph32 = hdr->ph32 + 1;
#else
		ph32 = hdr->ph32;
#endif
		for( group = Groups; group != NULL; group = group->next_group ) {
			if( group->totalsize == 0 ) continue;   // DANGER DANGER DANGER <--!!!

			off = ( off & ~(FmtData.objalign - 1) ) + ( group->linear & (FmtData.objalign - 1) );
			SetGroupHeaders32( group, off, ph32, sh32 );
#if PHDRSECT==0
			if ( first ) {
				ph32->p_filesz  += ph32->p_offset;
				ph32->p_memsz   += ph32->p_offset;
				ph32->p_vaddr   -= ph32->p_offset;
				ph32->p_offset  = 0;
				first = FALSE;
			}
#endif
			SeekLoad( off );
			DEBUG(( DBG_OLD, "WriteELFGroups(): %s grp.totalsize=%h p_vaddr=%h sh_addr=%h off=%h", GroupSecName( group ), group->totalsize, ph32->p_vaddr, sh32->sh_addr, off ));
			WriteGroupLoad( group );
			off += group->size;
			sh32->sh_name = AddSecName( hdr, GroupSecName(group) );
			sh32++;
			if( group == DataGroup && FmtData.dgroupsplitseg != NULL ) {
				sh32->sh_name = AddSecName( hdr, ".bss" );
				DEBUG(( DBG_OLD, "WriteELFGroups(): .bss split from %s group", GroupSecName( group ) ));
				if ( group->alignment > ( 1 << FmtData.u.elf.segment_shift ) ) {
					alignment = group->alignment;
				} else
					alignment = 1 << FmtData.u.elf.segment_shift;
				linear = ph32->p_vaddr + ROUND_UP( ph32->p_filesz, alignment );
				InitBSSSect32( sh32, off, CalcSplitSize(), linear, alignment );
				DEBUG(( DBG_OLD, "WriteELFGroups(): .bss sh_addr=%h sh_offset=%h sh_size=%h", sh32->sh_addr, sh32->sh_offset, sh32->sh_size ));
				linear = ROUND_UP( linear + sh32->sh_size, alignment );
				sh32++;
				if( StackSegPtr != NULL ) {
					sh32->sh_name = AddSecName( hdr, ".stack" );
					InitBSSSect32( sh32, off, StackSize, linear, alignment );
					DEBUG(( DBG_OLD, "WriteELFGroups(): .stack size=%h", sh32->sh_size ));
					sh32++;
				}
			}
			ph32++;
		}
	}
    hdr->curr_off = off;
}

#define RELA_NAME_SIZE sizeof(RelASecName)

static unsigned_32 SetRelocSectName( ElfHdr *hdr, char *secname )
/************************************************************************/
{
    size_t      len;
    char        *name;

    len = strlen( secname );
    name = alloca( RELA_NAME_SIZE + len );
    memcpy( name, RelASecName, RELA_NAME_SIZE - 1 );
    memcpy( name + RELA_NAME_SIZE - 1, secname, len + 1 );
    return( AddSecName( hdr, name ) );
}


static void WriteRelocsSections( ElfHdr *hdr )
/********************************************/
{
    group_entry *group;
    int         currgrp;
    void        *relocs;
    char        *secname;

	currgrp = hdr->i.grpbase;
	if ( FmtData.u.elf.elf64 ) {
		Elf64_Shdr  *sh64;
		sh64 = hdr->sh64 + hdr->i.relbase;
		for( group = Groups; group != NULL; group = group->next_group ) {
			relocs = group->g.grp_relocs;
			if( relocs != NULL ) {
				sh64->sh_offset = hdr->curr_off;
				sh64->sh_entsize = sizeof(elf64_reloc_item);
				sh64->sh_type = SHT_RELA;
				sh64->sh_flags = SHF_ALLOC;
				sh64->sh_addr = 0;
				sh64->sh_link = hdr->i.symtab;
				sh64->sh_info = currgrp;
				sh64->sh_addralign = 8;
				sh64->sh_size = RelocSize( relocs );
				secname = GroupSecName( group );
				sh64->sh_name = SetRelocSectName( hdr, secname );
				DEBUG(( DBG_OLD, "WriteRelocSections(): %s sh_offset=%h",
					   secname, sh64->sh_offset ));
				DumpRelocList( relocs );
				hdr->curr_off += sh64->sh_size;
				sh64++;
			}
			currgrp++;
		}
	} else {
		Elf32_Shdr  *sh32;
		sh32 = hdr->sh32 + hdr->i.relbase;
		for( group = Groups; group != NULL; group = group->next_group ) {
			relocs = group->g.grp_relocs;
			if( relocs != NULL ) {
				sh32->sh_offset = hdr->curr_off;
				sh32->sh_entsize = sizeof(elf32_reloc_item);
				sh32->sh_type = SHT_RELA;
				sh32->sh_flags = SHF_ALLOC;
				sh32->sh_addr = 0;
				sh32->sh_link = hdr->i.symtab;
				sh32->sh_info = currgrp;
				sh32->sh_addralign = 4;
				sh32->sh_size = RelocSize( relocs );
				secname = GroupSecName( group );
				sh32->sh_name = SetRelocSectName( hdr, secname );
				DEBUG(( DBG_OLD, "WriteRelocSections(): %s sh_offset=%h",
					   secname, sh32->sh_offset ));
				DumpRelocList( relocs );
				hdr->curr_off += sh32->sh_size;
				sh32++;
			}
			currgrp++;
		}
	}
}

void FiniELFLoadFile( void )
/*********************************/
{
    ElfHdr      hdr;

    SetHeaders( &hdr );
    #if 0
    if( IS_PPC_OS2 ) {
        // Development temporarly on hold
        // BuildOS2Imports(); // Build .got section
    }
    #endif

    WriteELFGroups( &hdr ); // Write out all groups
    WriteRelocsSections( &hdr );        // Relocations
    if( INJECT_DEBUG ) {                // Debug info
        hdr.curr_off = DwarfWriteElf( hdr.curr_off, &hdr.secstrtab,
                                hdr.sh32+hdr.i.dbgbegin );
    }
    if( ElfSymTab != NULL ) {           // Symbol tables
        WriteElfSymTable( ElfSymTab, &hdr, hdr.i.symhash, hdr.i.symtab,
                          hdr.i.symstr);
        ZapElfSymTable( ElfSymTab );
    }
    if( hdr.i.symstr != 0 ) {           // String sections
        WriteSHStrings( &hdr, ".strtab", hdr.i.symstr, &SymStrTab );
    }
    WriteSHStrings( &hdr, ".shstrtab", hdr.i.secstr, &hdr.secstrtab );

	/* write section table */
	if ( FmtData.u.elf.elf64 ) {
		hdr.eh64.e_shoff = hdr.curr_off;
		DEBUG(( DBG_OLD, "FiniElfLoadFile(): write section table, e_shoff=%h sh_size=%h",
			   hdr.eh64.e_shoff, hdr.sh_size ));
	} else {
		hdr.eh32.e_shoff = hdr.curr_off;
		DEBUG(( DBG_OLD, "FiniElfLoadFile(): write section table, e_shoff=%h sh_size=%h",
			   hdr.eh32.e_shoff, hdr.sh_size ));
	}
	WriteLoad( hdr.sh32, hdr.sh_size ); /* works for 32- and 64-bit */
    hdr.curr_off += hdr.sh_size;
    if( !INJECT_DEBUG ) {
        DBIWrite();
	}
    /* now write the ELF header + Pheader */
    SeekLoad( 0 );
	if ( FmtData.u.elf.elf64 ) {
		WriteLoad( &hdr.eh64, sizeof(Elf64_Ehdr) );
		WriteLoad( hdr.ph64, hdr.ph_size );
	} else {
		WriteLoad( &hdr.eh32, sizeof(Elf32_Ehdr) );
		WriteLoad( hdr.ph32, hdr.ph_size );
	}
    _LnkFree( hdr.sh32 );
    _LnkFree( hdr.ph32 );
    FiniStringTable( &hdr.secstrtab );
    FiniStringTable( &SymStrTab );
    SeekLoad( hdr.curr_off );
}

void ChkElfData( void )
/****************************/
{
    group_entry *group;
    symbol *    sym;

    NumExports = NumImports = 0;
    for( sym = HeadSym; sym != NULL; sym = sym->link ) {
        if( IsSymElfImported(sym) ) {
            NumImports++;
        } else if( IsSymElfExported(sym) ) {
            if( !(sym->info & SYM_DEFINED) ) {
                LnkMsg( ERR+MSG_EXP_SYM_NOT_FOUND, "s", sym->name );
            }
            NumExports++;
        }
    }
    InitStringTable( &SymStrTab, FALSE );
    AddCharStringTable( &SymStrTab, '\0' );
    ElfSymTab = CreateElfSymTable( NumImports + NumExports + NumGroups,
                                   &SymStrTab);
    for( group = Groups; group != NULL; group = group->next_group ) {
        if( group->totalsize != 0 ) {
            AddSymElfSymTable( ElfSymTab, group->sym );
        }
    }
    for( sym = HeadSym; sym != NULL; sym = sym->link ) {
        if( IsSymElfImpExp(sym) ) {
            AddSymElfSymTable(ElfSymTab, sym);
        }
    }

}

int FindElfSymIdx( symbol *sym )
/*************************************/
{
    return FindSymIdxElfSymTable( ElfSymTab, sym );
}

