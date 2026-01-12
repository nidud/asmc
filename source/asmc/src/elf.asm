; ELF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; ELF output routines
;

include asmc.inc
include memalloc.inc
include parser.inc
include fixup.inc
include segment.inc
include extern.inc
include elfspec.inc

if DWARF_SUPP
dwarf_create_sections proto __ccall
endif

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
IsWeak proto watcall :asym_t {
    retm<( !( [rax].asym.iscomm ) && [rax].asym.altname )>
    }
else
IsWeak proto watcall :asym_t {
    retm<( !( [eax].asym.iscomm ) && [eax].asym.altname )>
    }
endif

movl macro a, b
ifdef _LIN64
    mov a,b
endif
    endm

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
    sym     asym_t ?
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

    option proc:private

    assume rdi:ptr conv_section

ElfConvertSectionName proc __ccall uses rsi rdi rbx sym:asym_t, buffer:string_t

    ldr rcx,sym

    mov rsi,[rcx].asym.name

    .for ( rdi = &cst, ebx = 0 : ebx < lengthof(cst) : ebx++, rdi += conv_section )

        .ifd ( tmemcmp( rsi, [rdi].src, [rdi].len ) == 0 )

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

    endp

    assume rdi:nothing


; get number of sections that have relocations

get_num_reloc_sections proc

    .for ( eax = 0, rcx = SymTables[TAB_SEG].head : rcx : rcx = [rcx].asym.next )

        mov rdx,[rcx].asym.seginfo
        .if ( [rdx].seg_info.head )
            inc eax
        .endif
    .endf
    ret
    endp


; fill entries in ELF32 symbol table

    assume rbx:ptr elfmod

set_symtab proc __ccall uses rsi rdi rbx em:ptr elfmod, entries:uint_t, localshead:ptr localname

   .new len:uint_32
   .new strsize:uint_32 = 1
   .new buffer[MAX_ID_LEN+MANGLE_BYTES+1]:char_t

    ldr rbx,em

    mov eax,Elf32_Sym
    .if ( MODULE.defOfssize == USE64 )
        mov eax,Elf64_Sym
    .endif

    mov esi,eax
    mul ldr(entries)
    mov [rbx].internal_segs[OSYMTAB_IDX].size,eax
    mov [rbx].internal_segs[OSYMTAB_IDX].data,LclAlloc( eax )
    lea rdi,[rax+rsi] ; skip NULL entry

    ; 1. make file entry

    mov [rdi].Elf32_Sym.st_name,1 ; symbol's name in string table
    inc tstrlen( [rbx].srcname )
    add strsize,eax
    .if ( MODULE.defOfssize == USE64 )
        mov [rdi].Elf64_Sym.st_info,ELF64_ST_INFO( STB_LOCAL, STT_FILE ) ; symbol's type and binding info
        mov [rdi].Elf64_Sym.st_shndx,SHN_ABS ; section index
    .else
        mov [rdi].Elf32_Sym.st_info,ELF32_ST_INFO( STB_LOCAL, STT_FILE )
        mov [rdi].Elf32_Sym.st_shndx,SHN_ABS
    .endif
    add rdi,rsi

    assume rbx:nothing

    ; 2. make section entries

    .for ( ebx = esi, rsi = SymTables[TAB_SEG].head : rsi : rsi = [rsi].asym.next )

        GetSegIdx( [rsi].asym.segm )
        .if ( MODULE.defOfssize == USE64 )
            mov [rdi].Elf64_Sym.st_info,ELF64_ST_INFO( STB_LOCAL, STT_SECTION )
            mov [rdi].Elf64_Sym.st_shndx,ax
        .else
            mov [rdi].Elf32_Sym.st_info,ELF32_ST_INFO( STB_LOCAL, STT_SECTION )
            mov [rdi].Elf32_Sym.st_shndx,ax
        .endif
        add rdi,rbx
    .endf

    ; 3. locals

    .for ( rsi = localshead : rsi : rsi = [rsi].localname.next )

        lea ecx,[Mangle( [rsi].localname.sym, &buffer ) + 1]
        mov [rdi].Elf32_Sym.st_name,strsize
        add strsize,ecx

        mov rcx,[rsi].localname.sym
        mov rdx,[rcx].asym.segm
        .if ( rdx )
            mov eax,[rdx].asym.total_size ; v2.37.52: set st_size to segment size
            .if ( MODULE.defOfssize == USE64 )
                mov size_t ptr [rdi].Elf64_Sym.st_size,rax
            .else
                mov [rdi].Elf32_Sym.st_size,eax
            .endif
            mov rax,[rdx].asym.seginfo
        .endif
        .if ( rdx && [rax].seg_info.segtype != SEGTYPE_CODE )
            mov eax,ELF32_ST_INFO( STB_LOCAL, STT_OBJECT )
        .else
            mov eax,ELF32_ST_INFO( STB_LOCAL, STT_FUNC )
        .endif
        .if ( MODULE.defOfssize == USE64 )
            mov [rdi].Elf64_Sym.st_info,al
        .else
            mov [rdi].Elf32_Sym.st_info,al
        .endif
        mov eax,[rcx].asym.offs
        .if ( MODULE.defOfssize == USE64 )
            mov size_t ptr [rdi].Elf64_Sym.st_value,rax
        .else
            mov [rdi].Elf32_Sym.st_value,eax
        .endif
        mov eax,SHN_ABS
        .if ( rdx )
            GetSegIdx( rdx )
        .endif
        .if ( MODULE.defOfssize == USE64 )
            mov [rdi].Elf64_Sym.st_shndx,ax
        .else
            mov [rdi].Elf32_Sym.st_shndx,ax
        .endif
        add rdi,rbx
    .endf

    ; 4. externals + communals (+ protos [since v2.01])

    .for ( rsi = SymTables[TAB_EXT].head : rsi : rsi = [rsi].asym.next )

        ; skip "weak" (=unused) externdefs

        .continue .if ( !( [rsi].asym.iscomm ) && [rsi].asym.weak )

        lea ecx,[Mangle( rsi, &buffer ) + 1]
        mov [rdi].Elf32_Sym.st_name,strsize
        add strsize,ecx

        ; for COMMUNALs, store their size in the Value field

        .if ( [rsi].asym.iscomm )

            mov eax,ELF32_ST_INFO( STB_GLOBAL, STT_COMMON )
            mov ecx,[rsi].asym.total_size
            mov edx,SHN_COMMON
        .else
if OWELFIMPORT
            .if IsWeak( rsi )
                mov eax,ELF32_ST_INFO( STB_WEAK, STT_IMPORT )
            .else
                mov eax,ELF32_ST_INFO( STB_GLOBAL, STT_IMPORT )
            .endif
else
            ; todo: set STT_FUNC for prototypes/code labels???
            .if IsWeak( rsi )
                mov eax,ELF32_ST_INFO( STB_WEAK, STT_NOTYPE )
            .else
                mov eax,ELF32_ST_INFO( STB_GLOBAL, STT_NOTYPE )
            .endif
endif
            mov ecx,[rsi].asym.offs ; is always 0
            mov edx,SHN_UNDEF
        .endif
        .if ( MODULE.defOfssize == USE64 )
            mov [rdi].Elf64_Sym.st_info,al
            mov size_t ptr [rdi].Elf64_Sym.st_value,rcx
            mov [rdi].Elf64_Sym.st_shndx,dx
        .else
            mov [rdi].Elf32_Sym.st_info,al
            mov [rdi].Elf32_Sym.st_value,ecx
            mov [rdi].Elf32_Sym.st_shndx,dx
        .endif
        add rdi,rbx
    .endf

if ELFALIAS

    ; 5. aliases

    .for ( rsi = SymTables[TAB_ALIAS].head : rsi : rsi = [rsi].asym.next )

        lea ecx,[Mangle( rsi, &buffer ) + 1]
        mov [rdi].Elf32_Sym.st_name,strsize
        add strsize,ecx

if OWELFIMPORT
        mov eax,ELF32_ST_INFO( STB_WEAK, STT_IMPORT )
else
        mov eax,ELF32_ST_INFO( STB_WEAK, STT_NOTYPE )
endif
        xor ecx,ecx ; is always 0
        mov edx,SHN_UNDEF
        .if ( MODULE.defOfssize == USE64 )
            mov [rdi].Elf64_Sym.st_info,al
            mov size_t ptr [rdi].Elf64_Sym.st_value,rcx
            mov [rdi].Elf64_Sym.st_shndx,dx
        .else
            mov [rdi].Elf32_Sym.st_info,al
            mov [rdi].Elf32_Sym.st_value,ecx
            mov [rdi].Elf32_Sym.st_shndx,dx
        .endif
        add rdi,rbx
    .endf
endif

    ; 6. PUBLIC entries

    .for ( rsi = MODULE.PubQueue.head : rsi : rsi = [rsi].qnode.next )

        lea ecx,[Mangle( [rsi].qnode.sym, &buffer ) + 1]
        mov [rdi].Elf32_Sym.st_name,strsize
        add strsize,ecx

        mov rax,[rsi].qnode.sym
        mov rdx,[rax].asym.segm
        .if ( rdx )
            mov eax,[rdx].asym.total_size ; v2.37.52: set st_size to segment size
            .if ( MODULE.defOfssize == USE64 )
                mov size_t ptr [rdi].Elf64_Sym.st_size,rax
            .else
                mov [rdi].Elf32_Sym.st_size,eax
            .endif
            mov rcx,[rdx].asym.seginfo
        .endif
        mov eax,ELF32_ST_INFO( STB_GLOBAL, STT_FUNC )
        .if ( rdx && [rcx].seg_info.segtype != SEGTYPE_CODE )
            mov eax,ELF32_ST_INFO( STB_GLOBAL, STT_OBJECT )
        .endif
        mov rcx,[rsi].qnode.sym
        mov ecx,[rcx].asym.offs
        .if ( MODULE.defOfssize == USE64 )
            mov [rdi].Elf64_Sym.st_info,al
            mov size_t ptr [rdi].Elf64_Sym.st_value,rcx
        .else
            mov [rdi].Elf32_Sym.st_info,al
            mov [rdi].Elf32_Sym.st_value,ecx
        .endif
        mov eax,SHN_UNDEF
        mov rcx,[rsi].qnode.sym
        .if ( [rcx].asym.state == SYM_INTERNAL )
            mov eax,SHN_ABS
            .if ( rdx )
                GetSegIdx( rdx )
            .endif
        .endif
        .if ( MODULE.defOfssize == USE64 )
            mov [rdi].Elf64_Sym.st_shndx,ax
        .else
            mov [rdi].Elf32_Sym.st_shndx,ax
        .endif
        add rdi,rbx
    .endf
if ADDSTARTLABEL
    mov rsi,MODULE.start_label
    .if ( rsi )

        lea ecx,[Mangle( rsi, &buffer ) + 1]
        mov [rdi].Elf32_Sym.st_name,strsize
        add strsize,ecx
        GetSegIdx( [rsi].asym.segm )
        mov ecx,[rsi].asym.offs
        mov edx,ELF32_ST_INFO( STB_ENTRY, STT_FUNC )
        .if ( MODULE.defOfssize == USE64 )
            mov [rdi].Elf64_Sym.st_info,dl
            mov size_t ptr [rdi].Elf64_Sym.st_value,rcx
            mov [rdi].Elf64_Sym.st_shndx,ax
        .else
            mov [rdi].Elf32_Sym.st_info,dl
            mov [rdi].Elf32_Sym.st_value,ecx
            mov [rdi].Elf32_Sym.st_shndx,ax
        .endif
    .endif
endif
    mov eax,strsize
    ret
    endp


; calculate size of .symtab + .strtab section
; set content of these sections.

    assume rbx:ptr elfmod

.template locals
    head ptr localname ?
    tail ptr localname ?
   .ends

set_symtab_values proc __ccall uses rsi rdi rbx em:ptr elfmod

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

    .for ( rsi = SymTables[TAB_SEG].head: rsi: rsi = [rsi].asym.next )

        mov [rsi].asym.ext_idx,[rbx].symindex
        inc [rbx].symindex
    .endf

    ; add local symbols to symbol table

    .for ( rsi = SymTables[TAB_SEG].head: rsi: rsi = [rsi].asym.next )
        mov rcx,[rsi].asym.seginfo
        .if ( [rcx].seg_info.num_relocs )
            mov rdi,[rcx].seg_info.head
            assume rdi:ptr fixup
            .for ( : rdi : rdi = [rdi].nextrlc )

                ; if it's not EXTERNAL/PUBLIC, add symbol.
                ; however, if it's an assembly time variable
                ; use a raw section reference

                mov rcx,[rdi].sym
                .if ( [rcx].asym.isvariable )
                    mov [rdi].sym,[rdi].segment_var
                .elseif ( [rcx].asym.state == SYM_INTERNAL &&
                         ![rcx].asym.ispublic && ![rcx].asym.included )

                    mov [rcx].asym.included,1
                    LclAlloc( sizeof( localname ) )
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

    .for ( rcx = SymTables[TAB_EXT].head : rcx : rcx = [rcx].asym.next )
        .if ( !( [rcx].asym.iscomm ) && [rcx].asym.weak )
            .continue
        .endif
        mov [rcx].asym.ext_idx,[rbx].symindex
        inc [rbx].symindex
    .endf

if ELFALIAS

    ; count aliases

    .for ( rcx = SymTables[TAB_ALIAS].head : rcx : rcx = [rcx].asym.next )

        mov [rcx].asym.idx,[rbx].symindex
        inc [rbx].symindex
    .endf
endif

    ; count publics

    .for ( rcx = MODULE.PubQueue.head: rcx: rcx = [rcx].qnode.next )

        mov rdx,[rcx].qnode.sym
        mov [rdx].asym.ext_idx,[rbx].symindex
        inc [rbx].symindex
    .endf

    ; size of symbol table is defined

    mov entries,[rbx].symindex

if ADDSTARTLABEL
    .if ( MODULE.start_label )
        inc entries
    .endif
endif

    mov strsize,set_symtab( rbx, entries, l.head )

    ; generate the string table

    mov [rbx].internal_segs[OSTRTAB_IDX].size,strsize
    mov [rbx].internal_segs[OSTRTAB_IDX].data,LclAlloc( strsize )
    lea rdi,[rax+1]
    mov rsi,[rbx].srcname
    .while ( byte ptr [rsi] )
        movsb
    .endw
    movsb
    .for ( rsi = l.head : rsi : rsi = [rsi].localname.next )
        lea rdi,[rdi+Mangle( [rsi].localname.sym, rdi ) + 1]
    .endf

    .for ( rsi = SymTables[TAB_EXT].head : rsi : rsi = [rsi].asym.next )
        .if ( !( [rsi].asym.iscomm ) && [rsi].asym.weak )
            .continue
        .endif
        lea rdi,[rdi+Mangle( rsi, rdi ) + 1]
    .endf

if ELFALIAS
    .for ( rsi = SymTables[TAB_ALIAS].head : rsi : rsi = [rsi].asym.next )
        lea rdi,[rdi+Mangle( rsi, rdi ) + 1]
    .endf
endif

    .for ( rsi = MODULE.PubQueue.head: rsi: rsi = [rsi].qnode.next )
        mov rcx,[rsi].qnode.sym
        lea rdi,[rdi+Mangle( rcx, rdi ) + 1]
    .endf
if ADDSTARTLABEL
    .if ( MODULE.g.start_label )
        Mangle( MODULE.start_label, rdi )
    .endif
endif
    ret
    endp


; set content + size of .shstrtab section.
; this section contains the names of all sections.
; three groups of sections are handled:
; - sections defined in the program
; - ELF internal sections
; - relocation sections
; alloc .shstrtab

    assume rbx:nothing, rdi:nothing

set_shstrtab_values proc __ccall uses rsi rdi rbx em:ptr elfmod

   .new size:dword = 1 ; the first byte at offset 0 is the NULL section name
   .new buffer[MAX_ID_LEN+1]:char_t

    ; get size of section names defined in the program & relocation sections )

    .for ( rsi = SymTables[TAB_SEG].head : rsi : rsi = [rsi].asym.next )

        ; v2.07: ALIAS name defined?

        mov rbx,[rsi].asym.seginfo
        .if ( [rbx].seg_info.aliasname )
            mov rdi,[rbx].seg_info.aliasname
        .else
            mov rdi,ElfConvertSectionName( rsi, &buffer )
        .endif

        add size,tstrlen( rdi )
        inc size

        .if ( [rbx].seg_info.head )
            add size,tstrlen( rdi )
            .if ( MODULE.defOfssize == USE64 )
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
    lea rdi,[rax+1] ; NULL section name

    ; 1. names of program sections

    .for ( rsi = SymTables[TAB_SEG].head : rsi : rsi = [rsi].asym.next )

        mov rcx,[rsi].asym.seginfo
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

    .for ( rsi = SymTables[TAB_SEG].head : rsi : rsi = [rsi].asym.next )

        mov rcx,[rsi].asym.seginfo
        .if ( [rcx].seg_info.head )

            .if ( MODULE.defOfssize == USE64 )
                tstrcpy( rdi, ".rela" )
            .else
                tstrcpy( rdi, ".rel" )
            .endif
            add rdi,tstrlen(rdi)

            mov rcx,[rsi].asym.seginfo
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
    endp


get_relocation_count proc watcall curr:asym_t

    .for ( rcx = [rax].asym.seginfo, eax = 0,
           rcx = [rcx].seg_info.head: rcx : rcx = [rcx].fixup.nextrlc, eax++ )
    .endf
    ret
    endp


Get_Alignment proc watcall curr:asym_t

    mov rcx,[rax].asym.seginfo
    .if ( [rcx].seg_info.alignment == MAX_SEGALIGNMENT )
        .return( 0 )
    .endif
    mov cl,[rcx].seg_info.alignment
    mov eax,1
    shl eax,cl
    ret
    endp

;
; write ELF32 section table.
; fileoffset: start of section data ( behind elf header and section table )
; there are 3 groups of sections to handle:
; - the sections defined in the module
; - the internal ELF sections ( .shstrtab, .symtab, .strtab )
; - the 'relocation' sections
;
    assume rbx:ptr elfmod

ElfShdr union
dr32    Elf32_Shdr <>
dr64    Elf64_Shdr <>
ElfShdr ends

elf_write_section_table proc __ccall uses rsi rdi rbx em:ptr elfmod, fileoffset:dword

   .new sh:ElfShdr
   .new size:dword
   .new addralign:dword
ifdef _LIN64
   .new _rsi:ptr
   .new _rdi:ptr
endif

    ldr rbx,em

    add fileoffset,0xF
    and fileoffset,not 0xF

    ; set contents and size of internal .shstrtab section

    set_shstrtab_values( rbx )

    ; write the NULL entry

    mov ecx,Elf32_Shdr
    .if ( MODULE.defOfssize == USE64 )
        mov ecx,Elf64_Shdr
    .endif
    mov size,ecx
    lea rdi,sh
    xor eax,eax
    rep stosb

    ; write the empty NULL entry

    .ifd ( fwrite( &sh, 1, size, CurrFile[TOBJ] ) != size )
        WriteError()
    .endif

    ; use p to scan strings (=section names) of .shstrtab

    mov rdi,[rbx].internal_segs[OSHSTRTAB_IDX].data
    inc rdi ; skip 'name' of NULL entry

    ; write the section headers defined in the module,

    .for ( rsi = SymTables[TAB_SEG].head : rsi : rsi = [rsi].asym.next )

        tmemset( &sh, 0, size )

        mov rax,rdi
        sub rax,[rbx].internal_segs[OSHSTRTAB_IDX].data
        mov sh.dr32.sh_name,eax
        lea rdi,[rdi+tstrlen(rdi) + 1]

        mov rcx,[rsi].asym.seginfo
        .if ( [rcx].seg_info.information ) ; v2.07:added; v2.12: highest priority
            mov sh.dr32.sh_type,SHT_NOTE
        .else
            mov eax,SHT_NOBITS
            .if ( [rcx].seg_info.segtype != SEGTYPE_BSS )
                mov eax,SHT_PROGBITS
            .endif
            mov sh.dr32.sh_type,eax
            mov rax,[rcx].seg_info.clsym
            .if ( rax )
                mov rax,[rax].asym.name
                mov eax,[rax]
            .endif
            mov edx,SHF_WRITE or SHF_ALLOC
            .if ( [rcx].seg_info.segtype == SEGTYPE_CODE )
                mov edx,SHF_EXECINSTR or SHF_ALLOC
            .elseif ( [rcx].seg_info.readonly )
                mov edx,SHF_ALLOC
            .elseif ( eax == 'SNOC' )
                mov edx,SHF_ALLOC ; v2.07: added
if DWARF_SUPP
            .elseif ( [rcx].seg_info.internal && eax == 'RAWD' )
                xor edx,edx ; v2.21
endif
            .endif
            mov sh.dr32.sh_flags,edx
        .endif

        Get_Alignment(rsi)
        mov ecx,fileoffset ; start of section in file
        mov [rsi].asym.fileoffset_elf,ecx
        mov edx,[rsi].asym.max_offset
        .if ( MODULE.defOfssize == USE64 )
            mov dword ptr sh.dr64.sh_offset,ecx
            mov dword ptr sh.dr64.sh_size,edx
            mov dword ptr sh.dr64.sh_addralign,eax
        .else
            mov sh.dr32.sh_offset,ecx
            mov sh.dr32.sh_size,edx
            mov sh.dr32.sh_addralign,eax
        .endif
        movl _rsi,rsi
        movl _rdi,rdi
        fwrite( &sh, 1, size, CurrFile[TOBJ] )
        movl rdi,_rdi
        movl rsi,_rsi

        .if ( eax != size )
            WriteError()
        .endif
        get_relocation_count(rsi)
        mov rcx,[rsi].asym.seginfo
        mov [rcx].seg_info.num_relocs,eax

        ; v2.12: don't adjust fileoffset for SHT_NOBITS sections.
        ; it didn't cause fatal damage previously, but made the
        ; object module unnecessary large.

        .if ( sh.dr32.sh_type != SHT_NOBITS )

            mov eax,sh.dr32.sh_size
            .if ( MODULE.defOfssize == USE64 )
                mov eax,dword ptr sh.dr64.sh_size
            .endif
            add eax,fileoffset
            add eax,0xF
            and eax,not 0xF
            mov fileoffset,eax
        .endif
    .endf

    ; set size and contents of .symtab and .strtab sections

    set_symtab_values(rbx)

    ; write headers of internal sections

    tmemset( &sh, 0, size )

    .for ( esi = 0 : esi < NUM_INTSEGS : esi++ )

        mov rax,rdi
        sub rax,[rbx].internal_segs[OSHSTRTAB_IDX].data
        mov sh.dr32.sh_name,eax
        lea rdi,[rdi+tstrlen(rdi)+1]

        imul ecx,esi,intsegparm
        lea rdx,internal_segparms
        mov sh.dr32.sh_type,[rdx+rcx].intsegparm.type
        imul ecx,esi,intseg
        mov [rbx].internal_segs[rcx].fileoffset,fileoffset
        mov ecx,[rbx].internal_segs[rcx].size
        .if ( MODULE.defOfssize == USE64 )
            mov dword ptr sh.dr64.sh_offset,eax
            mov dword ptr sh.dr64.sh_size,ecx
        .else
            mov sh.dr32.sh_offset,eax
            mov sh.dr32.sh_size,ecx
        .endif

        ; section .symtab is special

        xor eax,eax
        xor ecx,ecx
        xor edx,edx
        mov addralign,1
        .if ( esi == SYMTAB_IDX )
            mov eax,MODULE.num_segs
            add eax,1 + STRTAB_IDX
            mov ecx,[rbx].start_globals
            mov addralign,4
            mov edx,sizeof( Elf32_Sym )
            .if ( MODULE.defOfssize == USE64 )
                mov edx,sizeof( Elf64_Sym )
            .endif
        .endif
        .if ( MODULE.defOfssize == USE64 )
            mov sh.dr64.sh_link,eax
            mov sh.dr64.sh_info,ecx
            mov dword ptr sh.dr64.sh_entsize,edx
            mov eax,addralign
            mov dword ptr sh.dr64.sh_addralign,eax
        .else
            mov sh.dr32.sh_link,eax
            mov sh.dr32.sh_info,ecx
            mov sh.dr32.sh_entsize,edx
            mov sh.dr32.sh_addralign,addralign
        .endif

        movl _rsi,rsi
        movl _rdi,rdi
        fwrite( &sh, 1, size, CurrFile[TOBJ] )
        movl rsi,_rsi
        movl rdi,_rdi
        .if ( eax != size )
            WriteError()
        .endif

        mov eax,sh.dr32.sh_size
        .if ( MODULE.defOfssize == USE64 )
            mov eax,dword ptr sh.dr64.sh_size
        .endif
        add eax,fileoffset
        add eax,0xF
        and eax,not 0xF
        mov fileoffset,eax
    .endf

    ; write headers of reloc sections

    .for ( rsi = SymTables[TAB_SEG].head : rsi : rsi = [rsi].asym.next )

        mov rcx,[rsi].asym.seginfo
        .continue .if ( [rcx].seg_info.head == NULL )

        tmemset( &sh, 0, size )

        mov rax,rdi
        sub rax,[rbx].internal_segs[OSHSTRTAB_IDX].data
        mov sh.dr32.sh_name,eax
        lea rdi,[rdi+tstrlen(rdi)+1]

        ; save the file offset in the slot reserved for ELF relocs

        mov rdx,[rsi].asym.seginfo
        mov [rdx].seg_info.reloc_offset,fileoffset ; start of section in file
        .if ( MODULE.defOfssize == USE64 )
            mov dword ptr sh.dr64.sh_offset,eax
            mov ecx,SHT_RELA
        .else
            mov sh.dr32.sh_offset,eax
            mov ecx,SHT_REL
        .endif
        mov sh.dr32.sh_type,ecx

        ; size of section in file

        mov eax,sizeof( Elf32_Rel )
        .if ( MODULE.defOfssize == USE64 )
            mov eax,sizeof( Elf64_Rela )
        .endif
        mov ecx,eax
        mul [rdx].seg_info.num_relocs
        mov edx,MODULE.num_segs
        add edx,1 + SYMTAB_IDX
        .if ( MODULE.defOfssize == USE64 )
            mov dword ptr sh.dr64.sh_size,eax
            mov dword ptr sh.dr64.sh_link,edx
            mov dword ptr sh.dr64.sh_entsize,ecx
        .else
            mov sh.dr32.sh_size,eax
            mov sh.dr32.sh_link,edx
            mov sh.dr32.sh_entsize,ecx
        .endif

        ; set info to the src section index

        GetSegIdx( [rsi].asym.segm )
        mov ecx,4
        .if ( MODULE.defOfssize == USE64 )
            mov sh.dr64.sh_info,eax
            mov dword ptr sh.dr64.sh_addralign,ecx
        .else
            mov sh.dr32.sh_info,eax
            mov sh.dr32.sh_addralign,ecx
        .endif
        movl _rsi,rsi
        movl _rdi,rdi
        fwrite( &sh, 1, size, CurrFile[TOBJ] )
        movl rsi,_rsi
        movl rdi,_rdi
        .if ( eax != size )
            WriteError()
        .endif

        mov eax,sh.dr32.sh_size
        .if ( MODULE.defOfssize == USE64 )
            mov eax,dword ptr sh.dr64.sh_size
        .endif
        add eax,fileoffset
        add eax,0xF
        and eax,not 0xF
        mov fileoffset,eax
    .endf
    xor eax,eax
    ret
    endp


; write 1 section's relocations (32-bit)

    assume rsi:ptr fixup

write_relocs32 proc __ccall uses rsi rbx em:ptr elfmod, curr:asym_t

   .new reloc32:Elf32_Rel

    ldr rbx,em
    ldr rdx,curr
    mov rcx,[rdx].asym.seginfo

    .for ( rsi = [rcx].seg_info.head : rsi : rsi = [rsi].nextrlc )

        mov reloc32.r_offset,[rsi].locofs
        movzx eax,[rsi].type
        .switch pascal eax
        .case FIX_RELOFF32
            mov edx,R_386_PC32
            mov rcx,[rsi].sym
            .if ( MODULE.pic && [rcx].asym.isproc ) ; added v2.34.25
                mov edx,R_386_PLT32
            .endif
        .case FIX_OFF32        : mov edx,R_386_32
        .case FIX_OFF32_IMGREL : mov edx,R_386_RELATIVE
if GNURELOCS
        .case FIX_OFF16    : mov [rbx].extused,TRUE : mov edx,R_386_16
        .case FIX_RELOFF16 : mov [rbx].extused,TRUE : mov edx,R_386_PC16
        .case FIX_OFF8     : mov [rbx].extused,TRUE : mov edx,R_386_8
        .case FIX_RELOFF8  : mov [rbx].extused,TRUE : mov edx,R_386_PC8
endif
        .default
            mov rcx,curr
            .if ( [rsi].type < FIX_LAST )
                mov rdx,MODULE.fmtopt
                asmerr( 3019, [rdx].format_options.formatname, [rsi].type, [rcx].asym.name, [rsi].locofs )
            .else
                asmerr( 3014, [rsi].type, [rcx].asym.name, [rsi].locofs )
            .endif
            mov edx,R_386_NONE
        .endsw

        ; the low 8 bits of info are type
        ; the high 24 bits are symbol table index

        mov rcx,[rsi].sym
        mov reloc32.r_info,ELF32_R_INFO( [rcx].asym.ext_idx, edx )
        movl rbx,rsi
        .ifd ( fwrite( &reloc32, 1, sizeof(reloc32), CurrFile[TOBJ] ) != sizeof(reloc32) )
            WriteError()
        .endif
        movl rsi,rbx
        movl rbx,em
    .endf
    ret
    endp


; write 1 section's relocations (64-bit)

write_relocs64 proc __ccall uses rsi rdi rbx curr:asym_t

   .new reloc64:Elf64_Rela ; v2.05: changed to Rela

    ldr rdx,curr
    mov rcx,[rdx].asym.seginfo

    .for ( rsi = [rcx].seg_info.head : rsi : rsi = [rsi].nextrlc )

        mov rcx,[rsi].sym
        mov edi,[rcx].asym.ext_idx
        mov eax,[rsi].locofs
        mov size_t ptr reloc64.r_offset,rax
ifndef _WIN64
        mov dword ptr reloc64.r_offset[4],0
endif
        mov edx,[rsi].offs
        movzx rax,[rsi].addbytes
        sub rax,rdx
        neg rax
        mov size_t ptr reloc64.r_addend,rax
ifndef _WIN64
        cdq
        mov dword ptr reloc64.r_addend[4],edx
endif
        movzx eax,[rsi].type
        .switch pascal eax
        .case FIX_RELOFF32
            mov ebx,R_X86_64_PC32
            ;
            ; v2.34.25: added isproc
            ; v2.37.49: PLT32 used as default unless -fno-pic (dynamic link if -fpic)
            ;
            .if ( !MODULE.nopic )
                .if ( [rcx].asym.isproc )
                    mov ebx,R_X86_64_PLT32
                .elseif ( MODULE.fPIC && [rcx].asym.ispublic )
                    mov ebx,R_X86_64_REX_GOTPCRELX
                .endif
            .endif
        .case FIX_OFF64
if 0        ;
            ; v2.21: in case the 64-bit reloc refer to a segment only, the addend has to be set.
            ; it's needed for dwarf internal fixups at least. Further tests needed!
            ;
            .if ( [rcx].asym.state == SYM_SEG )
                mov eax,[rsi].offs
                mov size_t ptr reloc64.r_addend,rax
              ifndef _WIN64
                mov dword ptr reloc64.r_addend[4],0
              endif
            .endif
endif
            mov ebx,R_X86_64_64
        .case FIX_OFF32_IMGREL : mov ebx,R_X86_64_RELATIVE
        .case FIX_OFF32        : mov ebx,R_X86_64_32
        .case FIX_OFF16        : mov ebx,R_X86_64_16
        .case FIX_RELOFF16     : mov ebx,R_X86_64_PC16
        .case FIX_OFF8         : mov ebx,R_X86_64_8
        .case FIX_RELOFF8      : mov ebx,R_X86_64_PC8
        .default
            mov rcx,curr
            mov ebx,R_X86_64_NONE
            .if ( [rsi].type < FIX_LAST )
                mov rdx,MODULE.fmtopt
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
        .ifd ( fwrite( &reloc64, 1, sizeof( reloc64 ), CurrFile[TOBJ] ) != sizeof(reloc64) )
            WriteError()
        .endif
        movl rsi,_rsi
        movl rdi,_rdi
    .endf
    ret
    endp

    assume rdi:nothing, rsi:nothing


; write section contents and fixups


elf_write_data proc __ccall uses rsi rdi rbx em:ptr elfmod
ifdef _LIN64
    .new _rsi:ptr
    .new _rdi:ptr
endif
    .new i:int_t
    .new b:byte = 0

    .for ( rsi = SymTables[TAB_SEG].head : rsi : rsi = [rsi].asym.next )

        mov rdi,[rsi].asym.seginfo
        mov ebx,[rsi].asym.max_offset
        sub ebx,[rdi].seg_info.start_loc
        .if ( [rdi].seg_info.segtype != SEGTYPE_BSS && ebx )
            movl _rsi,rsi
            movl _rdi,rdi
            .for ( i = [rdi].seg_info.start_loc : i : i-- )
                fwrite( &b, 1, 1, CurrFile[TOBJ] )
            .endf
            movl rsi,_rsi
            movl rdi,_rdi
            .if ( [rdi].seg_info.CodeBuffer == NULL )
                fseek( CurrFile[TOBJ], ebx, SEEK_CUR )
            .else
                fseek( CurrFile[TOBJ], [rsi].asym.fileoffset_elf, SEEK_SET )
                movl rdi,_rdi
                .if ( fwrite( [rdi].seg_info.CodeBuffer, 1, ebx, CurrFile[TOBJ] ) != rbx )
                    WriteError()
                .endif
            .endif
            movl rsi,_rsi
        .endif
    .endf

    ; write internal sections

    mov rbx,em
    .for ( esi = 0: esi < NUM_INTSEGS: esi++ )

        imul edi,esi,intseg
        .if ( [rbx].internal_segs[rdi].data )
            movl _rsi,rsi
            movl _rdi,rdi
            fseek( CurrFile[TOBJ], [rbx].internal_segs[rdi].fileoffset, SEEK_SET )
            movl rdi,_rdi
            fwrite( [rbx].internal_segs[rdi].data, 1, [rbx].internal_segs[rdi].size, CurrFile[TOBJ] )
            movl rsi,_rsi
            movl rdi,_rdi
            .if ( eax != [rbx].internal_segs[rdi].size )
                WriteError()
            .endif
        .endif
    .endf

    ; write reloc sections content

    .for ( rsi = SymTables[TAB_SEG].head : rsi : rsi = [rsi].asym.next )

        mov rdi,[rsi].asym.seginfo
        .if ( [rdi].seg_info.num_relocs )
            movl _rsi,rsi
            movl _rdi,rdi
            fseek( CurrFile[TOBJ], [rdi].seg_info.reloc_offset, SEEK_SET )
            movl rsi,_rsi
            movl rdi,_rdi
            .if ( MODULE.defOfssize == USE64 )
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
    xor eax,eax
    ret
    endp


; write ELF module

elf_write_module proc uses rsi rdi rbx

   .new em:elfmod

    tmemset( &em, 0, sizeof( em ) )

    mov rdi,CurrFName[TASM]
    lea rdx,[rdi+tstrlen(rdi)]

    ; the path part is stripped. todo: check if this is ok to do

    .while ( rdx > rdi )

        .break .if ( byte ptr [rdx-1] == '\' )
        .break .if ( byte ptr [rdx-1] == '/' )
        dec rdx
    .endw
    mov em.srcname,rdx
if DWARF_SUPP
    .if ( Options.line_numbers )
        dwarf_create_sections()
    .endif
endif

    ; position at 0 ( probably unnecessary, since there were no writes yet )

    fseek( CurrFile[TOBJ], 0, SEEK_SET )
    tmemcpy( &em.ehdr32.e_ident, ELF_SIGNATURE, ELF_SIGNATURE_LEN )

    mov em.ehdr32.e_ident[EI_DATA],ELFDATA2LSB
    mov em.ehdr32.e_ident[EI_VERSION],EV_CURRENT
    mov em.ehdr32.e_ident[EI_OSABI],MODULE.elf_osabi
    mov em.ehdr32.e_type,ET_REL ; file type
    mov em.ehdr32.e_version,EV_CURRENT

ifndef ASMC64
    .if ( MODULE.defOfssize == USE64 )
endif
        mov em.ehdr64.e_ident[EI_CLASS],ELFCLASS64

        ; v2.07: set abiversion to 0

        mov em.ehdr64.e_machine,EM_X86_64
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
        add eax,MODULE.num_segs
        add eax,1 + 3
        mov em.ehdr64.e_shnum,ax

        mov eax,MODULE.num_segs
        add eax,1 + SHSTRTAB_IDX
        mov em.ehdr64.e_shstrndx,ax ; set index of .shstrtab section

        .ifd ( fwrite( &em.ehdr64, 1, sizeof( em.ehdr64 ), CurrFile[TOBJ] ) != sizeof( em.ehdr64 ) )
            WriteError()
        .endif
        movzx eax,em.ehdr64.e_shnum
        mul em.ehdr64.e_shentsize
        add eax,sizeof( Elf64_Ehdr )
ifndef ASMC64
    .else

        mov em.ehdr32.e_ident[EI_CLASS],ELFCLASS32

        ; v2.07: set abiversion to 0

        mov em.ehdr32.e_machine,EM_386
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
        add eax,MODULE.num_segs
        add eax,1 + 3
        mov em.ehdr32.e_shnum,ax

        mov eax,MODULE.num_segs
        add eax,1 + SHSTRTAB_IDX
        mov em.ehdr32.e_shstrndx,ax ; set index of .shstrtab section

        .ifd ( fwrite( &em.ehdr32, 1, sizeof( em.ehdr32 ), CurrFile[TOBJ] ) != sizeof( em.ehdr32 ) )
            WriteError()
        .endif
        movzx eax,em.ehdr32.e_shnum
        mul em.ehdr32.e_shentsize
        add eax,sizeof( Elf32_Ehdr )
    .endif
endif
    elf_write_section_table( &em, eax )
    elf_write_data( &em )
    xor eax,eax
    ret
    endp


; format-specific init.
; called once per module.

elf_init proc public

    mov MODULE.elf_osabi,ELFOSABI_SYSV
    mov MODULE.WriteModule,&elf_write_module
    ret
    endp

    end
