; ELF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; ELF output routines
;

include time.inc

include asmc.inc
include memalloc.inc
include parser.inc
include mangle.inc
include fixup.inc
include segment.inc
include extern.inc
include elf.inc
include elfspec.inc

; v2.03: create weak externals for ALIAS symbols.
; Since the syntax of the ALIAS directive requires
; 2 names and, OTOH, the ELF implementation of weak
; externals has no "default resolution", the usefullness
; of this option is questionable. Additionally, there's
; the "EXTERN <name> (<altname>)" syntax, which also allows
; to define a weak external.

define ELFALIAS 0

; start label is always public for COFF/ELF, no need to add it
define ADDSTARTLABEL 0

; there's no STT_IMPORT type for ELF, it's OW specific
define OWELFIMPORT 0

; use GNU extensions for LD ( 16bit and 8bit relocations )
define GNURELOCS 1

define MANGLE_BYTES 8 ; extra size required for name decoration

ifdef _WIN64
IsWeak proto watcall :ptr asym {
    retm<( !( [rax].asym.sflags & S_ISCOM ) && [rax].asym.altname )>
    }
else
IsWeak proto watcall :ptr asym {
    retm<( !( [eax].asym.sflags & S_ISCOM ) && [eax].asym.altname )>
    }
endif
;
; section attributes for ELF
;         execute write  alloc  type
;---------------------------------------
; CODE      x              x    progbits
; CONST                    x    progbits
; DATA              x      x    progbits
; BSS               x      x    nobits
; STACK             x      x    progbits
; others            x      x    progbits
;
; todo: translate section bits:
; - INFO    -> SHT_NOTE  (added in v2.07)
; - DISCARD ->
; - SHARED  ->
; - EXECUTE -> SHF_EXECINSTR
; - READ    ->
; - WRITE   -> SHF_WRITE
;

.template localname
    next    ptr ?
    sym     ptr asym ?
   .ends

.enum internal_sections {
    SHSTRTAB_IDX,
    SYMTAB_IDX,
    STRTAB_IDX,
    NUM_INTSEGS
    }

.template intsegparm
    name    string_t ?
    type    dd ?
   .ends

.data

; constant parameters of internal sections; order must match enum internal_sections
internal_segparms intsegparm \
    { @CStr(".shstrtab"), SHT_STRTAB },
    { @CStr(".symtab"),   SHT_SYMTAB },
    { @CStr(".strtab"),   SHT_STRTAB }


.template intseg
    size        dd ?
    fileoffset  dd ?
    data        ptr sbyte ?
   .ends


; v2.12: all global variables replaced by elfmod
.template elfmod
    symindex        dd ?        ; entries in symbol table
    start_globals   dd ?        ; start index globals in symbol table
    srcname         string_t ?  ; name of source module (name + extension)
if GNURELOCS
    extused         int_t ?     ; gnu extensions used
endif
    internal_segs   intseg NUM_INTSEGS dup(<>)
    union
        ehdr32 Elf32_Ehdr <>
        ehdr64 Elf64_Ehdr <>
    ends
   .ends

.enumt o_internal_sections : intseg  {
    OSHSTRTAB_IDX,
    OSYMTAB_IDX,
    OSTRTAB_IDX
    }

; to help convert section names in COFF, ELF, PE
.template conv_section
    len         db ?
    flags       db ? ; see below
    src         string_t ?
    dst         string_t ?
   .ends

.enum cvs_flags {
    CSF_GRPCHK = 1
    }

cst conv_section \
    { 5, CSF_GRPCHK, @CStr("_TEXT"), @CStr(".text")   },
    { 5, CSF_GRPCHK, @CStr("_DATA"), @CStr(".data")   },
    { 5, CSF_GRPCHK, @CStr("CONST"), @CStr(".rodata") }, ; v2.05: .rdata -> .rodata
    { 4, 0,          @CStr("_BSS"),  @CStr(".bss")    }


; translate section names:
; see cst[] above for details.

    .code

    assume rdi:ptr conv_section

ElfConvertSectionName proc __ccall private uses rsi rdi rbx sym:ptr asym, buffer:string_t

    ldr rcx,sym

    mov rsi,[rcx].asym.name

    .for ( rdi = &cst, ebx = 0 : ebx < lengthof(cst) : ebx++, rdi += conv_section )

        .if ( tmemcmp( rsi, [rdi].src, [rdi].len ) == 0 )

            movzx edx,[rdi].len

            .if ( byte ptr [rsi+rdx] == NULLC )

                .return( [rdi].dst )

            .elseif ( ( [rdi].flags & CSF_GRPCHK ) && byte ptr [rsi+rdx] == '$' )

                add rsi,rdx

               .return( tstrcat( tstrcpy( buffer, [rdi].dst ), rsi ) )
            .endif
        .endif
    .endf
    .return( rsi )

ElfConvertSectionName endp

    assume rdi:nothing


; get number of sections that have relocations

get_num_reloc_sections proc private

    .for ( eax = 0, rcx = SymTables[TAB_SEG*symbol_queue].head : rcx : rcx = [rcx].dsym.next )

        mov rdx,[rcx].dsym.seginfo
        .if ( [rdx].seg_info.head )
            inc eax
        .endif
    .endf
    ret

get_num_reloc_sections endp


; fill entries in ELF32 symbol table

    assume rbx:ptr elfmod
    assume rdi:ptr Elf32_Sym

ifndef ASMC64

set_symtab32 proc __ccall private uses rsi rdi rbx em:ptr elfmod, entries:uint_t, localshead:ptr localname

   .new len:uint_32
   .new strsize:uint_32 = 1
   .new p32:ptr Elf32_Sym
   .new buffer[MAX_ID_LEN+MANGLE_BYTES+1]:char_t

    ldr rbx,em

    imul esi,entries,sizeof( Elf32_Sym )
    mov [rbx].internal_segs[OSYMTAB_IDX].size,esi

    mov [rbx].internal_segs[OSYMTAB_IDX].data,LclAlloc( esi )
    mov rdi,rax

    mov ecx,esi
    xor eax,eax
    mov rdx,rdi
    rep stosb
    lea rdi,[rdx+Elf32_Sym] ; skip NULL entry

    ; 1. make file entry

    mov [rdi].st_name,strsize ; symbol's name in string table
    inc tstrlen( [rbx].srcname )
    add strsize,eax
    mov [rdi].st_info,ELF32_ST_INFO( STB_LOCAL, STT_FILE ) ; symbol's type and binding info
    mov [rdi].st_shndx,SHN_ABS ; section index
    add rdi,Elf32_Sym

    assume rbx:nothing

    ; 2. make section entries

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head: rsi: rsi = [rsi].dsym.next )

        mov [rdi].st_info,ELF32_ST_INFO( STB_LOCAL, STT_SECTION )
        mov [rdi].st_shndx,GetSegIdx( [rsi].asym.segm )
        add rdi,Elf32_Sym
    .endf

    ; 3. locals

    .for ( rsi = localshead : rsi : rsi = [rsi].localname.next )

        lea rbx,[Mangle( [rsi].localname.sym, &buffer ) + 1]
        mov [rdi].st_name,strsize
        mov rcx,[rsi].localname.sym
        mov rdx,[rcx].asym.segm
        .if ( rdx )
            mov rax,[rdx].dsym.seginfo
        .endif
        .if ( rdx && [rax].seg_info.segtype != SEGTYPE_CODE )
            mov [rdi].st_info,ELF32_ST_INFO( STB_LOCAL, STT_OBJECT )
        .else
            mov [rdi].st_info,ELF32_ST_INFO( STB_LOCAL, STT_FUNC )
        .endif
        mov [rdi].st_value,[rcx].asym.offs
        .if ( rdx )
            mov [rdi].st_shndx,GetSegIdx( rdx )
        .else
            mov [rdi].st_shndx,SHN_ABS
        .endif
        add strsize,ebx
        add rdi,Elf32_Sym
    .endf

    ; 4. externals + communals (+ protos [since v2.01])

    .for ( rsi = SymTables[TAB_EXT*symbol_queue].head: rsi: rsi = [rsi].dsym.next )

        ; skip "weak" (=unused) externdefs

        .continue .if ( !( [rsi].asym.sflags & S_ISCOM ) && [rsi].asym.sflags & S_WEAK )

        lea rbx,[Mangle( rsi, &buffer ) + 1]
        mov [rdi].st_name,strsize

        ; for COMMUNALs, store their size in the Value field

        .if ( [rsi].asym.sflags & S_ISCOM )

            mov [rdi].st_info,ELF32_ST_INFO( STB_GLOBAL, STT_COMMON )
            mov [rdi].st_value,[rsi].asym.total_size
            mov [rdi].st_shndx,SHN_COMMON
        .else
if OWELFIMPORT
            .if IsWeak( rsi )
                mov [rdi].st_info,ELF32_ST_INFO( STB_WEAK, STT_IMPORT )
            .else
                mov [rdi].st_info,ELF32_ST_INFO( STB_GLOBAL, STT_IMPORT )
            .endif
else
            ; todo: set STT_FUNC for prototypes/code labels???
            .if IsWeak( rsi )
                mov [rdi].st_info,ELF32_ST_INFO( STB_WEAK, STT_NOTYPE )
            .else
                mov [rdi].st_info,ELF32_ST_INFO( STB_GLOBAL, STT_NOTYPE )
            .endif
endif
            mov [rdi].st_value,[rsi].asym.offs ; is always 0
            mov [rdi].st_shndx,SHN_UNDEF
        .endif
        add strsize,ebx
        add rdi,Elf32_Sym
    .endf

if ELFALIAS

    ; 5. aliases

    .for ( rsi = SymTables[TAB_ALIAS*symbol_queue].head: rsi: rsi = [rsi].dsym.next )

        lea rbx,[Mangle( rsi, &buffer ) + 1]
        mov [rdi].st_name,strsize

if OWELFIMPORT
        mov [rdi].st_info,ELF32_ST_INFO( STB_WEAK, STT_IMPORT )
else
        mov [rdi].st_info,ELF32_ST_INFO( STB_WEAK, STT_NOTYPE )
endif
        mov [rdi].st_value,0 ; is always 0
        mov [rdi].st_shndx,SHN_UNDEF
        add strsize,ebx
        add rdi,Elf32_Sym
    .endf
endif

    ; 6. PUBLIC entries

    .for ( rsi = ModuleInfo.PubQueue.head: rsi: rsi = [rsi].qnode.next )

        mov rbx,[rsi].qnode.sym
        mov len,Mangle( rbx, &buffer )

        mov rbx,[rbx].asym.segm
        .if ( rbx )
            mov rcx,[rbx].dsym.seginfo
        .endif
        .if ( rbx && [rcx].seg_info.segtype != SEGTYPE_CODE )
            mov [rdi].st_info,ELF32_ST_INFO( STB_GLOBAL, STT_OBJECT )
        .else
            mov [rdi].st_info,ELF32_ST_INFO( STB_GLOBAL, STT_FUNC )
        .endif
        mov [rdi].st_name,strsize
        mov rcx,[rsi].qnode.sym
        mov [rdi].st_value,[rcx].asym.offs

        .if ( [rcx].asym.state == SYM_INTERNAL )
            .if ( rbx )
                mov [rdi].st_shndx,GetSegIdx( rbx )
            .else
                mov [rdi].st_shndx,SHN_ABS
            .endif
        .else
            mov [rdi].st_shndx,SHN_UNDEF
        .endif
        add strsize,len
        inc strsize
        add rdi,Elf32_Sym
    .endf

if ADDSTARTLABEL
    mov rbx,ModuleInfo.start_label
    .if ( rbx )
        mov len,Mangle( rbx, &buffer )
        mov [rdi].st_name,strsize
        mov [rdi].st_info,ELF32_ST_INFO( STB_ENTRY, STT_FUNC )
        mov [rdi].st_value,[rbx].asym.offs
        mov [rdi].st_shndx,GetSegIdx( [rbx].asym.segm )
        add strsize,len
        inc strsize
        add rdi,Elf32_Sym
    .endif
endif
    .return( strsize )

set_symtab32 endp

endif


    assume rbx:ptr elfmod
    assume rdi:ptr Elf64_Sym

set_symtab64 proc __ccall private uses rsi rdi rbx em:ptr elfmod, entries:uint_t, localshead:ptr localname

   .new len:uint_32
   .new strsize:uint_32 = 1
   .new buffer[MAX_ID_LEN+MANGLE_BYTES+1]:char_t

    ldr rbx,em
    imul esi,entries,sizeof( Elf64_Sym )
    mov [rbx].internal_segs[OSYMTAB_IDX].size,esi
    mov [rbx].internal_segs[OSYMTAB_IDX].data,LclAlloc( esi )

    mov rdi,rax
    mov rcx,rsi
    xor eax,eax
    mov rdx,rdi
    rep stosb
    lea rdi,[rdx+Elf64_Sym] ; skip NULL entry

    ; 1. make file entry

    mov [rdi].st_name,1 ; symbol's name in string table
    inc tstrlen( [rbx].srcname )
    add strsize,eax
    mov [rdi].st_info,ELF64_ST_INFO( STB_LOCAL, STT_FILE ) ; symbol's type and binding info
    mov [rdi].st_shndx,SHN_ABS ; section index
    add rdi,Elf64_Sym

    assume rbx:nothing

    ; 2. make section entries

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head: rsi: rsi = [rsi].dsym.next )

        mov [rdi].st_info,ELF64_ST_INFO( STB_LOCAL, STT_SECTION )
        mov [rdi].st_shndx,GetSegIdx( [rsi].asym.segm )
        add rdi,Elf64_Sym
    .endf

    ; 3. locals

    .for ( rsi = localshead : rsi : rsi = [rsi].localname.next )

        lea rbx,[Mangle( [rsi].localname.sym, &buffer ) + 1]
        mov [rdi].st_name,strsize
        mov rcx,[rsi].localname.sym
        mov rdx,[rcx].asym.segm
        .if ( rdx )
            mov rax,[rdx].dsym.seginfo
        .endif
        .if ( rdx && [rax].seg_info.segtype != SEGTYPE_CODE )
            mov [rdi].st_info,ELF64_ST_INFO( STB_LOCAL, STT_OBJECT )
        .else
            mov [rdi].st_info,ELF64_ST_INFO( STB_LOCAL, STT_FUNC )
        .endif
        mov dword ptr [rdi].st_value[0],[rcx].asym.offs
        .if ( edx )
            mov [rdi].st_shndx,GetSegIdx( rdx )
        .else
            mov [rdi].st_shndx,SHN_ABS
        .endif
        add strsize,ebx
        add rdi,Elf64_Sym
    .endf

    ; 4. externals + communals ( + protos [since v2.01])


    .for ( rsi = SymTables[TAB_EXT*symbol_queue].head: rsi: rsi = [rsi].dsym.next )

        ; skip "weak" (=unused) externdefs

        .continue .if ( !( [rsi].asym.sflags & S_ISCOM ) && [rsi].asym.sflags & S_WEAK )

        lea rbx,[Mangle( rsi, &buffer ) + 1]
        mov [rdi].st_name,strsize

        ; for COMMUNALs, store their size in the Value field

        .if ( [rsi].asym.sflags & S_ISCOM )

            mov [rdi].st_info,ELF64_ST_INFO( STB_GLOBAL, STT_COMMON )
            mov dword ptr [rdi].st_value[0],[rsi].asym.total_size
            mov [rdi].st_shndx,SHN_COMMON
        .else
if OWELFIMPORT
            .if IsWeak( rsi )
                mov [rdi].st_info,ELF64_ST_INFO( STB_WEAK, STT_IMPORT )
            .else
                mov [rdi].st_info,ELF64_ST_INFO( STB_GLOBAL, STT_IMPORT )
            .endif
else
            ; todo: set STT_FUNC for prototypes???
            .if IsWeak( rsi )
                mov [rdi].st_info,ELF64_ST_INFO( STB_WEAK, STT_NOTYPE )
            .else
                mov [rdi].st_info,ELF64_ST_INFO( STB_GLOBAL, STT_NOTYPE )
            .endif
endif
            mov dword ptr [rdi].st_value[0],[rsi].asym.offs ; is always 0
            mov [rdi].st_shndx,SHN_UNDEF
        .endif
        add strsize,ebx
        add rdi,Elf64_Sym
    .endf

if ELFALIAS

    ; 5. aliases

    .for ( rsi = SymTables[TAB_ALIAS*symbol_queue].head: rsi: rsi = [rsi].dsym.next )

        lea rbx,[Mangle( rsi, &buffer ) + 1]
        mov [rdi].st_name,strsize

if OWELFIMPORT
        mov [rdi].st_info,ELF64_ST_INFO( STB_WEAK, STT_IMPORT )
else
        mov [rdi].st_info,ELF64_ST_INFO( STB_WEAK, STT_NOTYPE )
endif
        mov [rdi].st_shndx,SHN_UNDEF
        add strsize,ebx
        add rdi,Elf64_Sym
    .endf
endif

    ; 6. PUBLIC entries

    .for ( rsi = ModuleInfo.PubQueue.head: rsi: rsi = [rsi].qnode.next )

        mov rbx,[rsi].qnode.sym
        mov len,Mangle( rbx, &buffer )

        mov rdx,[rbx].asym.segm
        .if ( rdx )
            mov rcx,[rdx].dsym.seginfo
        .endif
        .if ( rdx && [rcx].seg_info.segtype != SEGTYPE_CODE )
            mov [rdi].st_info,ELF32_ST_INFO( STB_GLOBAL, STT_OBJECT )
        .else
            mov [rdi].st_info,ELF32_ST_INFO( STB_GLOBAL, STT_FUNC )
        .endif
        mov [rdi].st_name,strsize
        mov dword ptr [rdi].st_value[0],[rbx].asym.offs
        .if ( [rbx].asym.state == SYM_INTERNAL )
            .if ( rdx )
                mov [rdi].st_shndx,GetSegIdx( rdx )
            .else
                mov [rdi].st_shndx,SHN_ABS
            .endif
        .else
            mov [rdi].st_shndx,SHN_UNDEF
        .endif
        add strsize,len
        inc strsize
        add rdi,Elf64_Sym
    .endf

if ADDSTARTLABEL
    mov rbx,ModuleInfo.start_label
    .if ( rbx )
        mov len,Mangle( rbx, &buffer )
        mov [rdi].st_name,strsize
        mov [rdi].st_info,ELF64_ST_INFO( STB_ENTRY, STT_FUNC )
        mov [rdi].st_value,[rbx].asym.offs
        mov [rdi].st_shndx,GetSegIdx( [rbx].asym.segm )
        add strsize,len
        inc strsize
        add rdi,Elf64_Sym
    .endif
endif
    .return( strsize )

set_symtab64 endp


; calculate size of .symtab + .strtab section
; set content of these sections.

    assume rbx:ptr elfmod

.template locals
    head ptr localname ?
    tail ptr localname ?
   .ends

set_symtab_values proc __ccall private uses rsi rdi rbx em:ptr elfmod

   .new entries:int_32
   .new strsize:int_32
   .new l:locals = { NULL, NULL }

    ; symbol table. there is
    ; - 1 NULL entry,
    ; - 1 entry for the module/file,
    ; - 1 entry for each section and
    ; - n entries for local symbols
    ; - m entries for global symbols

    ldr rbx,em

    ; symbol table starts with 1 NULL entry + 1 file entry

    mov [rbx].symindex,1 + 1

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head: rsi: rsi = [rsi].dsym.next )

        mov [rsi].asym.ext_idx,[rbx].symindex
        inc [rbx].symindex
    .endf

    ; add local symbols to symbol table

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head: rsi: rsi = [rsi].dsym.next )
        mov rcx,[rsi].dsym.seginfo
        .if ( [rcx].seg_info.num_relocs )
            mov rdi,[rcx].seg_info.head
            assume rdi:ptr fixup
            .for ( : rdi : rdi = [rdi].nextrlc )

                ; if it's not EXTERNAL/PUBLIC, add symbol.
                ; however, if it's an assembly time variable
                ; use a raw section reference

                mov rcx,[rdi].sym
                .if ( [rcx].asym.flags & S_VARIABLE )
                    mov [rdi].sym,[rdi].segment_var
                .elseif ( [rcx].asym.state == SYM_INTERNAL &&
                        !( [rcx].asym.flags & ( S_INCLUDED or S_ISPUBLIC ) ) )

                    or [rcx].asym.flags,S_INCLUDED
                    LclAlloc( sizeof( localname ) )
                    mov [rax].localname.next,NULL
                    mov rcx,[rdi].sym
                    mov [rax].localname.sym,rcx
                    .if ( l.tail )
                        mov rdx,l.tail
                        mov [rdx].localname.next,rax
                        mov l.tail,rax
                    .else
                        mov l.head,rax
                        mov l.tail,rax
                    .endif
                    mov [rcx].asym.ext_idx,[rbx].symindex
                    inc [rbx].symindex
                .endif
            .endf
        .endif
    .endf
    mov [rbx].start_globals,[rbx].symindex

    ; count EXTERNs and used EXTERNDEFs (and PROTOs [since v2.01])

    .for ( rcx = SymTables[TAB_EXT*symbol_queue].head : rcx : rcx = [rcx].dsym.next )
        .if ( !( [rcx].asym.sflags & S_ISCOM ) && [rcx].asym.sflags & S_WEAK )
            .continue
        .endif
        mov [rcx].asym.ext_idx,[rbx].symindex
        inc [rbx].symindex
    .endf

if ELFALIAS

    ; count aliases

    .for ( rcx = SymTables[TAB_ALIAS*symbol_queue].head : rcx : rcx = [rcx].dsym.next )

        mov [rcx].asym.idx,[rbx].symindex
        inc [rbx].symindex
    .endf
endif

    ; count publics

    .for ( rcx = ModuleInfo.PubQueue.head: rcx: rcx = [rcx].qnode.next )

        mov rdx,[rcx].qnode.sym
        mov [rdx].asym.ext_idx,[rbx].symindex
        inc [rbx].symindex
    .endf

    ; size of symbol table is defined

    mov entries,[rbx].symindex

if ADDSTARTLABEL
    .if ( ModuleInfo.start_label )
        inc entries
    .endif
endif

    .if ( ModuleInfo.defOfssize == USE64 )
        mov strsize,set_symtab64( rbx, entries, l.head )
ifndef ASMC64
    .else
        mov strsize,set_symtab32( rbx, entries, l.head )
endif
    .endif

    ; generate the string table

    mov [rbx].internal_segs[OSTRTAB_IDX].size,strsize
    mov [rbx].internal_segs[OSTRTAB_IDX].data,LclAlloc( strsize )
if 0 ; zero alloc..
    tmemset( rax, 0, strsize )
endif
    lea rdi,[rax+1]
    mov rsi,[rbx].srcname
    .while ( byte ptr [rsi] )
        movsb
    .endw
    movsb
    .for ( rsi = l.head : rsi : rsi = [rsi].localname.next )
        lea rdi,[rdi+Mangle( [rsi].localname.sym, rdi ) + 1]
    .endf

    .for ( rsi = SymTables[TAB_EXT*symbol_queue].head : rsi : rsi = [rsi].dsym.next )
        .if ( !( [rsi].asym.sflags & S_ISCOM ) && [rsi].asym.sflags & S_WEAK )
            .continue
        .endif
        lea rdi,[rdi+Mangle( rsi, rdi ) + 1]
    .endf

if ELFALIAS
    .for ( rsi = SymTables[TAB_ALIAS*symbol_queue].head : rsi : rsi = [rsi].dsym.next )
        lea rdi,[rdi+Mangle( rsi, rdi ) + 1]
    .endf
endif

    .for ( rsi = ModuleInfo.PubQueue.head: rsi: rsi = [rsi].qnode.next )
        mov rcx,[rsi].qnode.sym
        lea rdi,[rdi+Mangle( rcx, rdi ) + 1]
    .endf
if ADDSTARTLABEL
    .if ( ModuleInfo.g.start_label )
        Mangle( ModuleInfo.start_label, rdi )
    .endif
endif
    ret

set_symtab_values endp


; set content + size of .shstrtab section.
; this section contains the names of all sections.
; three groups of sections are handled:
; - sections defined in the program
; - ELF internal sections
; - relocation sections
; alloc .shstrtab

    assume rbx:nothing
    assume rdi:nothing

set_shstrtab_values proc __ccall private uses rsi rdi rbx em:ptr elfmod

   .new size:dword = 1 ; the first byte at offset 0 is the NULL section name
   .new buffer[MAX_ID_LEN+1]:char_t

    ; get size of section names defined in the program & relocation sections )

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].dsym.next )

        ; v2.07: ALIAS name defined?

        mov rbx,[rsi].dsym.seginfo
        .if ( [rbx].seg_info.aliasname )
            mov rdi,[rbx].seg_info.aliasname
        .else
            mov rdi,ElfConvertSectionName( rsi, &buffer )
        .endif

        add size,tstrlen( rdi )
        inc size

        .if ( [rbx].seg_info.head )
            add size,tstrlen( rdi )
            .if ( ModuleInfo.defOfssize == USE64 )
                add size,6;sizeof(".rela")
            .else
                add size,5;sizeof(".rel")
            .endif
        .endif
    .endf

    ; get internal section name sizes

    .for ( rdi = &internal_segparms,
           ebx = 0 : ebx < NUM_INTSEGS : ebx++, rdi += intsegparm )

        tstrlen( [rdi].intsegparm.name )
        inc eax
        add size,eax
    .endf

    assume rbx:ptr elfmod

    mov rbx,em
    mov [rbx].internal_segs[OSHSTRTAB_IDX].size,size

    ; size is known, now alloc .shstrtab data buffer and fill it

    mov [rbx].internal_segs[OSHSTRTAB_IDX].data,LclAlloc( size )
    mov rdi,rax
    mov byte ptr [rdi],NULLC ; NULL section name
    inc rdi

    ; 1. names of program sections

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].dsym.next )

        mov rcx,[rsi].dsym.seginfo
        .if ( [rcx].seg_info.aliasname )
            mov rax,[rcx].seg_info.aliasname
        .else
            ElfConvertSectionName( rsi, &buffer )
        .endif
        tstrcpy( rdi, rax )
        lea rdi,[rdi+tstrlen( rdi ) + 1]
    .endf

    ; 2. names of internal sections

    .for ( esi = 0: esi < NUM_INTSEGS: esi++ )

        imul ecx,esi,intsegparm
        lea rdx,internal_segparms
        tstrcpy( rdi, [rdx+rcx].intsegparm.name )
        lea rdi,[rdi+tstrlen( rdi ) + 1]
    .endf

    ; 3. names of "relocation" sections

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].dsym.next )

        mov rcx,[rsi].dsym.seginfo
        .if ( [rcx].seg_info.head )

            .if ( ModuleInfo.defOfssize == USE64 )
                tstrcpy( rdi, ".rela" )
            .else
                tstrcpy( rdi, ".rel" )
            .endif
            add rdi,tstrlen(rdi)

            mov rcx,[rsi].dsym.seginfo
            .if ( [rcx].seg_info.aliasname )
                mov rax,[rcx].seg_info.aliasname
            .else
                ElfConvertSectionName(rsi, &buffer)
            .endif
            tstrcpy( rdi, rax )
            lea rdi,[rdi+tstrlen(rdi)+1]
        .endif
    .endf
    ret

set_shstrtab_values endp


get_relocation_count proc watcall private curr:ptr dsym

    .for ( rcx = [rax].dsym.seginfo, eax = 0,
           rcx = [rcx].seg_info.head: rcx : rcx = [rcx].fixup.nextrlc, eax++ )
    .endf
    ret

get_relocation_count endp


Get_Alignment proc watcall private curr:ptr dsym

    mov rcx,[rax].dsym.seginfo
    .if ( [rcx].seg_info.alignment == MAX_SEGALIGNMENT )
        .return( 0 )
    .endif
    mov cl,[rcx].seg_info.alignment
    mov eax,1
    shl eax,cl
    ret

Get_Alignment endp

;
; write ELF32 section table.
; fileoffset: start of section data ( behind elf header and section table )
; there are 3 groups of sections to handle:
; - the sections defined in the module
; - the internal ELF sections ( .shstrtab, .symtab, .strtab )
; - the 'relocation' sections
;
    assume rbx:ptr elfmod

ifndef ASMC64

elf_write_section_table32 proc __ccall private uses rsi rdi rbx em:ptr elfmod, fileoffset:dword

   .new shdr32:Elf32_Shdr

    add fileoffset,0xF
    and fileoffset,not 0xF

    ; set contents and size of internal .shstrtab section

    set_shstrtab_values( em )

    ; write the NULL entry

    tmemset( &shdr32, 0, sizeof( shdr32) )

    ; write the empty NULL entry

    .if ( fwrite( &shdr32, 1, sizeof(shdr32), CurrFile[OBJ*string_t] ) != sizeof(shdr32) )
        WriteError()
    .endif

    ; use p to scan strings (=section names) of .shstrtab

    mov rbx,em
    mov rdi,[rbx].internal_segs[OSHSTRTAB_IDX].data
    inc rdi ; skip 'name' of NULL entry

    ; write the section headers defined in the module,

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].dsym.next )

        tmemset( &shdr32, 0, sizeof(shdr32) )

        mov rax,rdi
        sub rax,[rbx].internal_segs[OSHSTRTAB_IDX].data
        mov shdr32.sh_name,eax
        lea rdi,[rdi+tstrlen(rdi) + 1]

        mov rcx,[rsi].dsym.seginfo
        .if ( [rcx].seg_info.info ) ; v2.07:added; v2.12: highest priority
            mov shdr32.sh_type,SHT_NOTE
        .else
            .if ( [rcx].seg_info.segtype != SEGTYPE_BSS )
                mov shdr32.sh_type,SHT_PROGBITS
            .else
                mov shdr32.sh_type,SHT_NOBITS
            .endif
            .if ( [rcx].seg_info.segtype == SEGTYPE_CODE )
                mov shdr32.sh_flags,SHF_EXECINSTR or SHF_ALLOC
            .elseif ( [rcx].seg_info.readonly == TRUE )
                mov shdr32.sh_flags,SHF_ALLOC
            .else
                mov shdr32.sh_flags,SHF_WRITE or SHF_ALLOC
                .if ( [rcx].seg_info.clsym )
                    mov rcx,[rcx].seg_info.clsym
                    .if ( tstrcmp( [rcx].asym.name, "CONST" ) == 0 )
                        mov shdr32.sh_flags,SHF_ALLOC ; v2.07: added
                    .endif
                .endif
            .endif
        .endif

        mov shdr32.sh_offset,fileoffset ; start of section in file
        mov rcx,[rsi].dsym.seginfo
        mov [rcx].seg_info.fileoffset,eax ; save the offset in the segment
        mov shdr32.sh_size,[rsi].asym.max_offset
        mov shdr32.sh_addralign,Get_Alignment(rsi)
ifdef _LIN64
        push rsi
        push rdi
endif
        fwrite( &shdr32, 1, sizeof(shdr32), CurrFile[OBJ*size_t] )
ifdef _LIN64
        pop rdi
        pop rsi
endif
        .if ( eax != sizeof(shdr32) )
            WriteError()
        .endif
        get_relocation_count(rsi)
        mov rcx,[rsi].dsym.seginfo
        mov [rcx].seg_info.num_relocs,eax

        ; v2.12: don't adjust fileoffset for SHT_NOBITS sections.
        ; it didn't cause fatal damage previously, but made the
        ; object module unnecessary large.

        .if ( shdr32.sh_type != SHT_NOBITS )
            add fileoffset,shdr32.sh_size
            add fileoffset,0xF
            and fileoffset,not 0xF
        .endif
    .endf

    ; set size and contents of .symtab and .strtab sections

    set_symtab_values(rbx)

    ; write headers of internal sections

    tmemset( &shdr32, 0, sizeof(shdr32) )

    .for ( esi = 0 : esi < NUM_INTSEGS : esi++ )

        mov rax,rdi
        sub rax,[rbx].internal_segs[OSHSTRTAB_IDX].data
        mov shdr32.sh_name,eax
        lea rdi,[rdi+tstrlen(rdi)+1]

        imul ecx,esi,intsegparm
        lea rdx,internal_segparms
        mov shdr32.sh_type,[rdx+rcx].intsegparm.type
        mov shdr32.sh_offset,fileoffset ; start of section in file

        imul ecx,esi,intseg
        mov [rbx].internal_segs[rcx].fileoffset,fileoffset
        mov shdr32.sh_size,[rbx].internal_segs[rcx].size

        ; section .symtab is special

        .if ( esi == SYMTAB_IDX )

            mov eax,ModuleInfo.num_segs
            add eax,1 + STRTAB_IDX
            mov shdr32.sh_link,eax
            mov shdr32.sh_info,[rbx].start_globals
            mov shdr32.sh_addralign,4
            mov shdr32.sh_entsize,sizeof( Elf32_Sym )
        .else
            mov shdr32.sh_link,0
            mov shdr32.sh_info,0
            mov shdr32.sh_addralign,1
            mov shdr32.sh_entsize,0
        .endif

ifdef _LIN64
        push rsi
        push rdi
endif
        fwrite( &shdr32, 1, sizeof(shdr32), CurrFile[OBJ*size_t] )
ifdef _LIN64
        pop rdi
        pop rsi
endif
        .if ( eax != sizeof(shdr32) )
            WriteError()
        .endif

        add fileoffset,shdr32.sh_size
        add fileoffset,0xF
        and fileoffset,not 0xF
    .endf

    ; write headers of reloc sections

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].dsym.next )

        mov rcx,[rsi].dsym.seginfo
        .continue .if ( [rcx].seg_info.head == NULL )

        tmemset( &shdr32, 0, sizeof( shdr32 ) )

        mov rax,rdi
        sub rax,[rbx].internal_segs[OSHSTRTAB_IDX].data
        mov shdr32.sh_name,eax
        lea rdi,[rdi+tstrlen(rdi)+1]
        mov shdr32.sh_type,SHT_REL
        mov shdr32.sh_offset,fileoffset ; start of section in file

        ; save the file offset in the slot reserved for ELF relocs

        mov rcx,[rsi].dsym.seginfo
        mov [rcx].seg_info.reloc_offset,eax

        ; size of section in file

        mov eax,sizeof( Elf32_Rel )
        mul [rcx].seg_info.num_relocs
        mov shdr32.sh_size,eax

        mov eax,ModuleInfo.num_segs
        add eax,1 + SYMTAB_IDX
        mov shdr32.sh_link,eax

        ;; set info to the src section index

        mov shdr32.sh_info,GetSegIdx( [rsi].asym.segm )
        mov shdr32.sh_addralign,4
        mov shdr32.sh_entsize,sizeof( Elf32_Rel )

ifdef _LIN64
        push rsi
        push rdi
endif
        fwrite( &shdr32, 1, sizeof(shdr32), CurrFile[OBJ*size_t] )
ifdef _LIN64
        pop rdi
        pop rsi
endif
        .if ( eax != sizeof(shdr32) )
            WriteError()
        .endif
        add fileoffset,shdr32.sh_size
        add fileoffset,0xF
        and fileoffset,not 0xF
    .endf
    .return( NOT_ERROR )

elf_write_section_table32 endp

endif


; write ELF64 section table.

elf_write_section_table64 proc __ccall private uses rsi rdi rbx em:ptr elfmod, fileoffset:uint_t

   .new shdr64:Elf64_Shdr

    add fileoffset,0xF
    and fileoffset,not 0xF

    ; set contents and size of internal .shstrtab section

    set_shstrtab_values( em )

    ; write the NULL entry

    tmemset( &shdr64, 0, sizeof( shdr64) )

    ; write the empty NULL entry

    .if ( fwrite( &shdr64, 1, sizeof(shdr64), CurrFile[OBJ*size_t] ) != sizeof(shdr64) )
        WriteError()
    .endif

    ; use p to scan strings (=section names) of .shstrtab

    mov rbx,em
    mov rdi,[rbx].internal_segs[OSHSTRTAB_IDX].data
    inc rdi ; skip 'name' of NULL entry

    ; write the section headers defined in the module

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].dsym.next )

        tmemset( &shdr64, 0, sizeof(shdr64) )

        mov rax,rdi
        sub rax,[rbx].internal_segs[OSHSTRTAB_IDX].data
        mov shdr64.sh_name,eax
        lea rdi,[rdi+tstrlen(rdi)+1]

        mov rcx,[rsi].dsym.seginfo
        .if ( [rcx].seg_info.info == TRUE ) ; v2.07:added; v2.12: highest priority
            mov shdr64.sh_type,SHT_NOTE
        .else
            .if ( [rcx].seg_info.segtype != SEGTYPE_BSS )
                mov shdr64.sh_type,SHT_PROGBITS
             .else
                mov shdr64.sh_type,SHT_NOBITS
             .endif
            .if ( [rcx].seg_info.segtype == SEGTYPE_CODE )
                mov dword ptr shdr64.sh_flags[0],SHF_EXECINSTR or SHF_ALLOC
            .elseif ( [rcx].seg_info.readonly == TRUE )
                mov dword ptr shdr64.sh_flags[0],SHF_ALLOC
            .else
                mov dword ptr shdr64.sh_flags[0],SHF_WRITE or SHF_ALLOC
                .if ( [rcx].seg_info.clsym )
                    mov rcx,[rcx].seg_info.clsym
                    .if ( tstrcmp( [rcx].asym.name, "CONST" ) == 0 )
                        mov dword ptr shdr64.sh_flags[0],SHF_ALLOC ; v2.07: added
                    .endif
                .endif
            .endif
        .endif

        mov dword ptr shdr64.sh_offset,fileoffset ; start of section in file
        mov rcx,[rsi].dsym.seginfo
        mov [rcx].seg_info.fileoffset,eax ; save the offset in the segment
        mov dword ptr shdr64.sh_size,[rsi].asym.max_offset
        mov dword ptr shdr64.sh_addralign,Get_Alignment(rsi)

ifdef _LIN64
        push rsi
        push rdi
endif
        fwrite( &shdr64, 1, sizeof(shdr64), CurrFile[OBJ*size_t] )
ifdef _LIN64
        pop rdi
        pop rsi
endif
        .if ( eax != sizeof(shdr64) )
            WriteError()
        .endif

        get_relocation_count(rsi)
        mov rcx,[rsi].dsym.seginfo
        mov [rcx].seg_info.num_relocs,eax

        ; v2.12: don't adjust fileoffset for SHT_NOBITS sections

        .if ( shdr64.sh_type != SHT_NOBITS )
            add fileoffset,dword ptr shdr64.sh_size
            add fileoffset,0xF
            and fileoffset,not 0xF
        .endif
    .endf

    ; set size and contents of .symtab and .strtab sections

    set_symtab_values(rbx)

    ; write headers of internal sections

    tmemset( &shdr64, 0, sizeof(shdr64) )

    .for ( esi = 0 : esi < NUM_INTSEGS : esi++ )

        mov rax,rdi
        sub rax,[rbx].internal_segs[OSHSTRTAB_IDX].data
        mov shdr64.sh_name,eax
        lea rdi,[rdi+tstrlen(rdi)+1]

        imul ecx,esi,intsegparm
        lea rdx,internal_segparms
        mov shdr64.sh_type,[rdx+rcx].intsegparm.type
        mov dword ptr shdr64.sh_offset[0],fileoffset ; start of section in file

        imul ecx,esi,intseg
        mov [rbx].internal_segs[rcx].fileoffset,eax
        mov dword ptr shdr64.sh_size[0],[rbx].internal_segs[rcx].size

        ; section .symtab is special

        .if ( esi == SYMTAB_IDX )

            mov eax,ModuleInfo.num_segs
            add eax,1 + STRTAB_IDX
            mov shdr64.sh_link,eax
            mov shdr64.sh_info,[rbx].start_globals
            mov dword ptr shdr64.sh_addralign,4
            mov dword ptr shdr64.sh_entsize,sizeof( Elf64_Sym )
        .else
            mov shdr64.sh_link,0
            mov shdr64.sh_info,0
            mov dword ptr shdr64.sh_addralign,1
            mov dword ptr shdr64.sh_entsize,0
        .endif
ifdef _LIN64
        push rsi
        push rdi
endif
        fwrite( &shdr64, 1, sizeof(shdr64), CurrFile[OBJ*size_t] )
ifdef _LIN64
        pop rdi
        pop rsi
endif
        .if ( eax != sizeof(shdr64) )
            WriteError()
        .endif

        add fileoffset,dword ptr shdr64.sh_size
        add fileoffset,0xF
        and fileoffset,not 0xF
    .endf

    ; write headers of reloc sections

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].dsym.next )

        mov rcx,[rsi].dsym.seginfo
        .continue .if ( [rcx].seg_info.head == NULL )

        tmemset( &shdr64, 0, sizeof(shdr64) )

        mov rax,rdi
        sub rax,[rbx].internal_segs[OSHSTRTAB_IDX].data
        mov shdr64.sh_name,eax
        lea rdi,[rdi+tstrlen(rdi)+1]

        mov shdr64.sh_type,SHT_RELA ; v2.05: changed REL to RELA
        mov dword ptr shdr64.sh_offset,fileoffset ; start of section in file

        ; save the file offset in the slot reserved for ELF relocs

        mov rcx,[rsi].dsym.seginfo
        mov [rcx].seg_info.reloc_offset,eax

        ; size of section in file

        mov eax,sizeof( Elf64_Rela )
        mul [rcx].seg_info.num_relocs
        mov dword ptr shdr64.sh_size,eax

        mov eax,ModuleInfo.num_segs
        add eax,SYMTAB_IDX + 1
        mov shdr64.sh_link,eax

        ; set info to the src section index

        mov shdr64.sh_info,GetSegIdx( [rsi].asym.segm )
        mov dword ptr shdr64.sh_addralign,4
        mov dword ptr shdr64.sh_entsize,sizeof( Elf64_Rela )

ifdef _LIN64
        push rsi
        push rdi
endif
        fwrite( &shdr64, 1, sizeof(shdr64), CurrFile[OBJ*size_t] )
ifdef _LIN64
        pop rdi
        pop rsi
endif
        .if ( eax != sizeof(shdr64) )
            WriteError()
        .endif

        add fileoffset,dword ptr shdr64.sh_size
        add fileoffset,0xF
        and fileoffset,not 0xF
    .endf
    .return( NOT_ERROR )

elf_write_section_table64 endp


; write 1 section's relocations (32-bit)

    assume rsi:ptr fixup

write_relocs32 proc __ccall private uses rsi rdi rbx em:ptr elfmod, curr:ptr dsym

   .new elftype:byte
   .new reloc32:Elf32_Rel

    ldr rbx,em
    ldr rdx,curr
    mov rcx,[rdx].dsym.seginfo

    .for ( rsi = [rcx].seg_info.head: rsi: rsi = [rsi].nextrlc )

        mov reloc32.r_offset,[rsi].locofs

        .switch ( [rsi].type )
        .case FIX_RELOFF32
            mov elftype,R_386_PC32
            mov rcx,[rsi].sym
            .if ( ModuleInfo.pic && [rcx].asym.state == SYM_EXTERNAL )
                .if ( [rcx].asym.flags & S_ISPROC ) ; added v2.34.25
                    mov elftype,R_386_PLT32
                .endif
            .endif
            .endc
        .case FIX_OFF32        : mov elftype,R_386_32       : .endc
        .case FIX_OFF32_IMGREL : mov elftype,R_386_RELATIVE : .endc
if GNURELOCS
        .case FIX_OFF16    : mov [rbx].extused,TRUE : mov elftype,R_386_16   : .endc
        .case FIX_RELOFF16 : mov [rbx].extused,TRUE : mov elftype,R_386_PC16 : .endc
        .case FIX_OFF8     : mov [rbx].extused,TRUE : mov elftype,R_386_8    : .endc
        .case FIX_RELOFF8  : mov [rbx].extused,TRUE : mov elftype,R_386_PC8  : .endc
endif
        .default
            mov elftype,R_386_NONE
            mov rcx,curr
            .if ( [rsi].type < FIX_LAST )
                mov rdx,ModuleInfo.fmtopt
                asmerr( 3019, [rdx].format_options.formatname, [rsi].type, [rcx].asym.name, [rsi].locofs )
            .else
                asmerr( 3014, [rsi].type, [rcx].asym.name, [rsi].locofs )
            .endif
        .endsw

        ; the low 8 bits of info are type
        ; the high 24 bits are symbol table index

        mov rcx,[rsi].sym
        mov reloc32.r_info,ELF32_R_INFO( [rcx].asym.ext_idx, elftype )
ifdef _LIN64
        mov rbx,rsi
endif
        .ifd ( fwrite( &reloc32, 1, sizeof(reloc32), CurrFile[OBJ*size_t] ) != sizeof(reloc32) )
            WriteError()
        .endif
ifdef _LIN64
        mov rsi,rbx
        mov rbx,em
endif
    .endf
    ret

write_relocs32 endp


; write 1 section's relocations (64-bit)

write_relocs64 proc __ccall private uses rsi rdi rbx curr:ptr dsym

   .new reloc64:Elf64_Rela ; v2.05: changed to Rela

    ldr rdx,curr
    mov rcx,[rdx].dsym.seginfo

    .for ( rsi = [rcx].seg_info.head : rsi : rsi = [rsi].nextrlc )

        mov rcx,[rsi].sym
        mov edi,[rcx].asym.ext_idx
        mov eax,[rsi].locofs
ifndef _WIN64
        xor edx,edx
endif
        .s8 reloc64.r_offset
        mov edx,[rsi].offs
        movzx rax,[rsi].addbytes
        sub rax,rdx
        neg rax
ifndef _WIN64
        cdq
endif
        .s8 reloc64.r_addend

         movzx eax,[rsi].type
        .switch ( eax )
        .case FIX_RELOFF32
            mov ebx,R_X86_64_PC32
            .if ( ModuleInfo.pic && [rcx].asym.state == SYM_EXTERNAL )
                .if ( [rcx].asym.flags & S_ISPROC ) ; added v2.34.25
                    mov ebx,R_X86_64_PLT32
                .endif
            .endif
           .endc
        .case FIX_OFF64        : mov ebx,R_X86_64_64        : .endc
        .case FIX_OFF32_IMGREL : mov ebx,R_X86_64_RELATIVE  : .endc
        .case FIX_OFF32        : mov ebx,R_X86_64_32        : .endc
        .case FIX_OFF16        : mov ebx,R_X86_64_16        : .endc
        .case FIX_RELOFF16     : mov ebx,R_X86_64_PC16      : .endc
        .case FIX_OFF8         : mov ebx,R_X86_64_8         : .endc
        .case FIX_RELOFF8      : mov ebx,R_X86_64_PC8       : .endc
        .default
            mov rcx,curr
            mov ebx,R_X86_64_NONE
            .if ( [rsi].type < FIX_LAST )
                mov rdx,ModuleInfo.fmtopt
                asmerr( 3019, &[rdx].format_options.formatname, [rsi].type, [rcx].asym.name, [rsi].locofs )
            .else
                asmerr( 3014, [rsi].type, [rcx].asym.name, [rsi].locofs )
            .endif
        .endsw
        mov dword ptr reloc64.r_info[0],ebx
        mov dword ptr reloc64.r_info[4],edi
ifdef _LIN64
        .new _rsi:ptr = rsi
        .new _rdi:ptr = rdi
endif
        .if ( fwrite( &reloc64, 1, sizeof( reloc64 ), CurrFile[OBJ*size_t] ) != sizeof(reloc64) )
            WriteError()
        .endif
ifdef _LIN64
        mov rsi,_rsi
        mov rdi,_rdi
endif
    .endf
    ret

write_relocs64 endp


; write section contents and fixups

    assume rdi:nothing
    assume rsi:nothing

elf_write_data proc __ccall private uses rsi rdi rbx em:ptr elfmod
ifdef _LIN64
    .new _rsi:ptr
    .new _rdi:ptr
endif
    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].dsym.next )

        mov rdi,[rsi].dsym.seginfo
        mov ebx,[rsi].asym.max_offset
        sub ebx,[rdi].seg_info.start_loc
        .if ( [rdi].seg_info.segtype != SEGTYPE_BSS && ebx )
ifdef _LIN64
            mov _rsi,rsi
endif
            .if ( [rdi].seg_info.CodeBuffer == NULL )
                fseek( CurrFile[OBJ*size_t], ebx, SEEK_CUR )
            .else
                mov ecx,[rdi].seg_info.fileoffset
                add ecx,[rdi].seg_info.start_loc
                fseek( CurrFile[OBJ*size_t], ecx, SEEK_SET )
ifdef _LIN64
                mov rsi,_rsi
                mov rdi,[rsi].dsym.seginfo
endif
                .if ( fwrite( [rdi].seg_info.CodeBuffer, 1, ebx, CurrFile[OBJ*size_t] ) != rbx )
                    WriteError()
                .endif
            .endif
ifdef _LIN64
            mov rsi,_rsi
endif
        .endif
    .endf

    ; write internal sections

    mov rbx,em
    .for ( esi = 0: esi < NUM_INTSEGS: esi++ )

        imul edi,esi,intseg
        .if ( [rbx].internal_segs[rdi].data )
ifdef _LIN64
            mov _rsi,rsi
            mov _rdi,rdi
endif
            fseek( CurrFile[OBJ*size_t], [rbx].internal_segs[rdi].fileoffset, SEEK_SET )
ifdef _LIN64
            mov rdi,_rdi
endif
            fwrite( [rbx].internal_segs[rdi].data, 1, [rbx].internal_segs[rdi].size, CurrFile[OBJ*size_t] )
ifdef _LIN64
            mov rsi,_rsi
            mov rdi,_rdi
endif
            .if ( eax != [rbx].internal_segs[rdi].size )
                WriteError()
            .endif
        .endif
    .endf

    ; write reloc sections content

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].dsym.next )

        mov rdi,[rsi].dsym.seginfo
        .if ( [rdi].seg_info.num_relocs )
ifdef _LIN64
            mov _rsi,rsi
            mov _rdi,rdi
endif
            fseek( CurrFile[OBJ*size_t], [rdi].seg_info.reloc_offset, SEEK_SET )
ifdef _LIN64
            mov rsi,_rsi
            mov rdi,_rdi
endif
            .if ( ModuleInfo.defOfssize == USE64 )
                write_relocs64( rsi )
            .else
                write_relocs32( rbx, rsi )
            .endif
        .endif
    .endf
if GNURELOCS
    .if ( [rbx].extused )
        asmerr( 8013 )
    .endif
endif
    .return( NOT_ERROR )

elf_write_data endp


; write ELF module

elf_write_module proc private uses rsi rdi rbx

   .new em:elfmod

    tmemset( &em, 0, sizeof( em ) )

    mov rdi,CurrFName[ASM*size_t]
    lea rdx,[rdi+tstrlen(rdi)]

    ; the path part is stripped. todo: check if this is ok to do

    .while ( rdx > rdi )

        .break .if ( byte ptr [rdx-1] == '\' )
        .break .if ( byte ptr [rdx-1] == '/' )
        dec rdx
    .endw
    mov em.srcname,rdx

    ; position at 0 ( probably unnecessary, since there were no writes yet )

    fseek( CurrFile[OBJ*size_t], 0, SEEK_SET )

ifndef ASMC64
    .switch ( ModuleInfo.defOfssize )
    .case USE64
endif
        tmemcpy( &em.ehdr64.e_ident, ELF_SIGNATURE, ELF_SIGNATURE_LEN )
        mov em.ehdr64.e_ident[EI_CLASS],ELFCLASS64
        mov em.ehdr64.e_ident[EI_DATA],ELFDATA2LSB
        mov em.ehdr64.e_ident[EI_VERSION],EV_CURRENT
        mov em.ehdr64.e_ident[EI_OSABI],ModuleInfo.elf_osabi

        ; v2.07: set abiversion to 0

        mov em.ehdr64.e_type,ET_REL ; file type
        mov em.ehdr64.e_machine,EM_X86_64
        mov em.ehdr64.e_version,EV_CURRENT
        mov dword ptr em.ehdr64.e_shoff,sizeof( em.ehdr64 )
        mov em.ehdr64.e_ehsize,sizeof( em.ehdr64 )
        mov em.ehdr64.e_shentsize,sizeof( Elf64_Shdr )

        ; calculate # of sections. Add the following internal sections:
        ; - 1 NULL entry
        ; - 1 .shstrtab
        ; - 1 .symtab
        ; - 1 .strtab
        ; - n .rela<xxx> sections

        get_num_reloc_sections()
        add eax,ModuleInfo.num_segs
        add eax,1 + 3
        mov em.ehdr64.e_shnum,ax

        mov eax,ModuleInfo.num_segs
        add eax,1 + SHSTRTAB_IDX
        mov em.ehdr64.e_shstrndx,ax ; set index of .shstrtab section

        .if ( fwrite( &em.ehdr64, 1, sizeof( em.ehdr64 ), CurrFile[OBJ*size_t] ) != sizeof( em.ehdr64 ) )
            WriteError()
        .endif
        movzx eax,em.ehdr64.e_shnum
        mul em.ehdr64.e_shentsize
        add eax,sizeof( Elf64_Ehdr )
        elf_write_section_table64( &em, eax )

ifndef ASMC64
       .endc

    .default

        tmemcpy( &em.ehdr32.e_ident, ELF_SIGNATURE, ELF_SIGNATURE_LEN )
        mov em.ehdr32.e_ident[EI_CLASS],ELFCLASS32
        mov em.ehdr32.e_ident[EI_DATA],ELFDATA2LSB
        mov em.ehdr32.e_ident[EI_VERSION],EV_CURRENT
        mov em.ehdr32.e_ident[EI_OSABI],ModuleInfo.elf_osabi

        ; v2.07: set abiversion to 0

        mov em.ehdr32.e_type,ET_REL ;; file type
        mov em.ehdr32.e_machine,EM_386
        mov em.ehdr32.e_version,EV_CURRENT
        mov em.ehdr32.e_shoff,sizeof( em.ehdr32 )
        mov em.ehdr32.e_ehsize,sizeof( em.ehdr32 )
        mov em.ehdr32.e_shentsize,sizeof( Elf32_Shdr )

        ; calculate # of sections. Add the following internal sections:
        ; - 1 NULL entry
        ; - 1 .shstrtab
        ; - 1 .symtab
        ; - 1 .strtab
        ; - n .rel<xxx> entries

        get_num_reloc_sections()
        add eax,ModuleInfo.num_segs
        add eax,1 + 3
        mov em.ehdr32.e_shnum,ax

        mov eax,ModuleInfo.num_segs
        add eax,1 + SHSTRTAB_IDX
        mov em.ehdr32.e_shstrndx,ax ; set index of .shstrtab section

        .if ( fwrite( &em.ehdr32, 1, sizeof( em.ehdr32 ), CurrFile[OBJ*size_t] ) != sizeof( em.ehdr32 ) )
            WriteError()
        .endif
        movzx eax,em.ehdr32.e_shnum
        mul em.ehdr32.e_shentsize
        add eax,sizeof( Elf32_Ehdr )
        elf_write_section_table32( &em, eax )
    .endsw
endif
    elf_write_data( &em )
   .return( NOT_ERROR )

elf_write_module endp


; format-specific init.
; called once per module.

elf_init proc

    mov ModuleInfo.elf_osabi,ELFOSABI_SYSV
    mov ModuleInfo.WriteModule,&elf_write_module
    ret

elf_init endp

    end
