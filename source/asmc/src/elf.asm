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

define DWARF_SUPP 1 ; v2.21: dwarf debug info added - just line numbers (-Zd) for now

if DWARF_SUPP
include linnum.inc
include dbgdw.inc
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

if DWARF_SUPP

define DWLINE_OPCODE_BASE 13 ; max is 13
define DW_MIN_INSTR_LENGTH 1
define DWLINE_BASE (-1)
define DWLINE_RANGE 4

.enum {
    NULL_ABBREV_CODE,
    COMPUNIT_ABBREV_CODE,
    }

.pragma pack(push, 1)

.template dwarf_info32
    hdr             dwarf_compilation_unit_header32 <>
    abbrev_code     db ?
    low_pc          dd ?
    high_pc         dd ?
    stmt_list       dd ?
    name            char_t 1 dup(?)
   .ends

.template dwarf_info64
    hdr             dwarf_compilation_unit_header32 <>
    abbrev_code     db ?
    low_pc          dq ?
    high_pc         dq ?
    stmt_list       dd ?
    name            char_t 1 dup(?)
   .ends

.pragma pack(pop)
endif

.data

; constant parameters of internal sections; order must match enum internal_sections
internal_segparms intsegparm \
    { @CStr(".shstrtab"), SHT_STRTAB },
    { @CStr(".symtab"),   SHT_SYMTAB },
    { @CStr(".strtab"),   SHT_STRTAB }

if DWARF_SUPP
.enum dwarf_sections {
    DWINFO_IDX,
    DWABBREV_IDX,
    DWLINE_IDX,
    NUM_DWSEGS
    }
dwarf_segnames string_t \
    @CStr(".debug_info"),
    @CStr(".debug_abbrev"),
    @CStr(".debug_line")

FlatStandardAbbrevs char_t \
    COMPUNIT_ABBREV_CODE,
    DW_TAG_compile_unit,
    DW_CHILDREN_no,
    DW_AT_low_pc,       DW_FORM_addr,
    DW_AT_high_pc,      DW_FORM_addr,
    DW_AT_stmt_list,    DW_FORM_data4,
    DW_AT_name,         DW_FORM_string,
    0,                  0,
    0,                  0

stdopsparms db 0,1,1,1,1,0,0,0,1,0,0,1

endif

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
if DWARF_SUPP
    dwarf_seg       asym_t NUM_DWSEGS dup(?)
endif
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

    .for ( eax = 0, rcx = SymTables[TAB_SEG*symbol_queue].head : rcx : rcx = [rcx].asym.next )

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

    .for ( ebx = esi, rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].asym.next )

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

    .for ( rsi = SymTables[TAB_EXT*symbol_queue].head : rsi : rsi = [rsi].asym.next )

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

    .for ( rsi = SymTables[TAB_ALIAS*symbol_queue].head : rsi : rsi = [rsi].asym.next )

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

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head: rsi: rsi = [rsi].asym.next )

        mov [rsi].asym.ext_idx,[rbx].symindex
        inc [rbx].symindex
    .endf

    ; add local symbols to symbol table

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head: rsi: rsi = [rsi].asym.next )
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

    .for ( rcx = SymTables[TAB_EXT*symbol_queue].head : rcx : rcx = [rcx].asym.next )
        .if ( !( [rcx].asym.iscomm ) && [rcx].asym.weak )
            .continue
        .endif
        mov [rcx].asym.ext_idx,[rbx].symindex
        inc [rbx].symindex
    .endf

if ELFALIAS

    ; count aliases

    .for ( rcx = SymTables[TAB_ALIAS*symbol_queue].head : rcx : rcx = [rcx].asym.next )

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

    .for ( rsi = SymTables[TAB_EXT*symbol_queue].head : rsi : rsi = [rsi].asym.next )
        .if ( !( [rsi].asym.iscomm ) && [rsi].asym.weak )
            .continue
        .endif
        lea rdi,[rdi+Mangle( rsi, rdi ) + 1]
    .endf

if ELFALIAS
    .for ( rsi = SymTables[TAB_ALIAS*symbol_queue].head : rsi : rsi = [rsi].asym.next )
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

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].asym.next )

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

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].asym.next )

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

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].asym.next )

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

if DWARF_SUPP

    assume rbx:ptr elfmod

dwarf_set_info proc __ccall uses rsi rdi rbx em:ptr elfmod, seginfo:asym_t

   .new size:int_t
   .new curr:asym_t

    ldr rbx,em
    ldr rsi,seginfo

    mov rcx,MODULE.FNames
    tstrlen([rcx])
    mov ecx,dwarf_info32
    .if ( MODULE.defOfssize == USE64 )
        mov ecx,dwarf_info64
    .endif
    add eax,ecx
    mov size,eax
    mov [rsi].asym.max_offset,eax
    mov rdi,LclAlloc(eax)

    mov rcx,[rsi].asym.seginfo
    mov [rcx].seg_info.CodeBuffer,rdi

    mov eax,size
    sub eax,4
    mov [rdi].dwarf_info32.hdr.unit_length,eax
    mov [rdi].dwarf_info32.hdr.version,2
    ;mov [rdi].dwarf_info32.hdr.debug_abbrev_offset,0 ; needs a fixup

    CreateFixup( [rbx].dwarf_seg[DWABBREV_IDX*asym_t], FIX_OFF32, OPTJ_NONE )
    mov [rax].fixup.locofs,dwarf_info32.hdr.debug_abbrev_offset
    lea rcx,[rdi].dwarf_info32.hdr.debug_abbrev_offset
    store_fixup( rax, rsi, rcx )

    mov eax,4
    .if ( MODULE.defOfssize == USE64 )
        mov eax,8
    .endif
    mov [rdi].dwarf_info32.hdr.address_size,al
    mov [rdi].dwarf_info32.abbrev_code,COMPUNIT_ABBREV_CODE

    ; search for the first segment with line numbers

    .for ( rcx = SymTables[TAB_SEG*symbol_queue].head : rcx : rcx = [rcx].asym.next )

        mov rax,[rcx].asym.seginfo
        .break .if ( [rax].seg_info.LinnumQueue )
    .endf

    .if ( rcx )

        mov curr,rcx
        .if ( MODULE.defOfssize == USE64 )

            ;mov [rdi].dwarf_info64.low_pc,0
            CreateFixup( rcx, FIX_OFF64, OPTJ_NONE )
            mov [rax].fixup.locofs,dwarf_info64.low_pc
            lea rcx,[rdi].dwarf_info64.low_pc
            store_fixup( rax, rsi, rcx )
            mov rcx,curr
            mov eax,[rcx].asym.max_offset
            mov dword ptr [rdi].dwarf_info64.high_pc,eax
            CreateFixup( rcx, FIX_OFF64, OPTJ_NONE )
            mov [rax].fixup.locofs,dwarf_info64.high_pc
            lea rcx,[rdi].dwarf_info64.high_pc
            store_fixup( rax, rsi, rcx )
            ;mov [rdi].dwarf_info64.stmt_list,0
            CreateFixup( [rbx].dwarf_seg[DWLINE_IDX*asym_t], FIX_OFF32, OPTJ_NONE )
            mov [rax].fixup.locofs,dwarf_info64.stmt_list
            lea rcx,[rdi].dwarf_info64.stmt_list
            store_fixup( rax, rsi, rcx )
            mov rdx,MODULE.FNames
            tstrcpy( &[rdi].dwarf_info64.name, [rdx] )
        .else
            ;mov [rdi].dwarf_info32.low_pc,0
            CreateFixup( rcx, FIX_OFF32, OPTJ_NONE )
            mov [rax].fixup.locofs,dwarf_info32.low_pc
            lea rcx,[rdi].dwarf_info32.low_pc
            store_fixup( rax, rsi, rcx )
            mov rcx,curr
            mov [rdi].dwarf_info32.high_pc,[rcx].asym.max_offset
            CreateFixup( rcx, FIX_OFF32, OPTJ_NONE )
            mov [rax].fixup.locofs,dwarf_info32.high_pc
            lea rcx,[rdi].dwarf_info32.high_pc
            store_fixup( rax, rsi, rcx )
            ;mov [rdi].dwarf_info32.stmt_list,0
            CreateFixup( [rbx].dwarf_seg[DWLINE_IDX*asym_t], FIX_OFF32, OPTJ_NONE )
            mov [rax].fixup.locofs,dwarf_info32.stmt_list
            lea rcx,[rdi].dwarf_info32.stmt_list
            store_fixup( rax, rsi, rcx )
            mov rdx,MODULE.FNames
            tstrcpy( &[rdi].dwarf_info32.name, [rdx] )
        .endif
    .endif
    ret
    endp


dwarf_set_abbrev proc __ccall uses rsi rdi em:ptr elfmod, curr:asym_t

    ldr rsi,curr
    mov [rsi].asym.max_offset,sizeof(FlatStandardAbbrevs)
    mov rdi,LclAlloc(sizeof(FlatStandardAbbrevs))
    mov rcx,[rsi].asym.seginfo
    mov [rcx].seg_info.CodeBuffer,rdi
    mov ecx,sizeof(FlatStandardAbbrevs)
    lea rsi,FlatStandardAbbrevs
    rep movsb
    ret
    endp


LEB128 proc fastcall buf:ptr byte, value:int_t

    ; we can only handle an arithmetic right shift

    test edx,edx
    .ifns
        .while 1

            mov eax,edx
            shr edx,7
            and eax,0x7F
            .break .if ( edx == 0 && !( eax & 0x40 ) )
            or  al,0x80
            mov [rcx],al
            inc rcx
        .endw
    .else
        .while 1
            mov eax,edx
            sar edx,7
            and eax,0x7F
            .break .if ( edx == -1 && ( eax & 0x40 ) )
            or  al,0x80
            mov [rcx],al
            inc rcx
        .endw
    .endif
    mov [rcx],al
    lea rax,[rcx+1]
    ret
    endp


dwarf_line_gen proc __ccall uses rsi rdi line_incr:int_t, addr_incr:int_t, buf:ptr byte

   .new opcode:dword
   .new pend:ptr byte
   .new address:int_t

    ldr rdi,buf
    xor esi,esi

    .if ( line_incr < DWLINE_BASE || line_incr > DWLINE_BASE + DWLINE_RANGE - 1 )

        ; line_incr is out of bounds... emit standard opcode

        mov byte ptr [rdi],DW_LNS_advance_line
        LEB128( &[rdi+1], line_incr )
        sub rax,rdi
        mov esi,eax
        mov line_incr,0
    .endif

    .if ( addr_incr < 0 )

        lea rcx,[rdi+rsi+1]
        mov eax,DW_LNS_advance_pc
        mov [rcx-1],al
        LEB128( rcx, addr_incr )
        sub rax,rdi
        mov esi,eax
        mov addr_incr,0
    .else
        mov eax,addr_incr
        xor edx,edx
        mov ecx,DW_MIN_INSTR_LENGTH
        div ecx
        mov addr_incr,eax
    .endif
    .if ( addr_incr == 0 && line_incr == 0 )

        mov eax,esi
        mov ecx,DW_LNS_copy
        mov [rdi+rax],cl
        inc eax
       .return
    .endif

    ; calculate the opcode with overflow checks

    sub line_incr,DWLINE_BASE
    imul eax,addr_incr,DWLINE_RANGE
    mov opcode,eax
    .if ( eax < addr_incr )
        jmp overflow
    .endif
    add eax,line_incr
    .if ( eax < opcode )
        jmp overflow
    .endif
    mov opcode,eax

    ; can we use a special opcode?

    .if ( eax <= 255 - DWLINE_OPCODE_BASE )

        add eax,DWLINE_OPCODE_BASE
        mov [rdi+rsi],al
        lea eax,[rsi+1]
       .return
    .endif


    ; We can't use a special opcode directly... but we may be able to
    ; use a CONST_ADD_PC followed by a special opcode.  So we calculate
    ; if addr_incr lies in this range.  MAX_ADDR_INCR is the addr
    ; increment for special opcode 255.

define MAX_ADDR_INCR   ( ( 255 - DWLINE_OPCODE_BASE ) / DWLINE_RANGE )

    .if ( addr_incr < 2*MAX_ADDR_INCR )

        mov eax,DW_LNS_const_add_pc
        mov [rdi+rsi],al
        inc esi
        mov eax,opcode
        sub eax,MAX_ADDR_INCR*DWLINE_RANGE
        add eax,DWLINE_OPCODE_BASE
        mov [rdi+rsi],al
        lea eax,[rsi+1]
       .return
    .endif

    ; Emit an ADVANCE_PC followed by a special opcode.
    ;
    ; We use MAX_ADDR_INCR - 1 to prevent problems if special opcode
    ; 255 - DWLINE_OPCODE_BASE - DWLINE_BASE + 1 isn't an integral multiple
    ; of DWLINE_RANGE.

overflow:
    mov eax,DW_LNS_advance_pc
    mov [rdi+rsi],al

    .if ( line_incr == 0 - DWLINE_BASE )
        mov opcode,DW_LNS_copy
    .else
        mov eax,addr_incr
        xor edx,edx
        mov ecx,MAX_ADDR_INCR - 1
        div ecx
        sub addr_incr,edx
        imul eax,edx,DWLINE_RANGE
        add eax,line_incr
        add eax,DWLINE_OPCODE_BASE
        mov opcode,eax
    .endif
    LEB128( &[rdi+rsi+1], addr_incr )
    mov ecx,opcode
    mov [rax],cl
    sub rax,rdi
    ret
    endp


dwarf_set_line proc __ccall uses rsi rdi rbx em:ptr elfmod, seg_linenum:asym_t

   .new curr:asym_t
   .new lni:ptr line_num_info

    ldr rbx,em
    ldr rsi,seg_linenum

    ; get linnum program size; currently we count the items and assume avg size is 2

    .for ( edx = 0, rcx = SymTables[TAB_SEG*symbol_queue].head : rcx : rcx = [rcx].asym.next )

        mov rax,[rcx].asym.seginfo
        mov rax,[rax].seg_info.LinnumQueue
        .if ( rax )
            .for ( rax = [rax].qdesc.head : rax : edx++, rax = [rax].line_num_info.next )
            .endf
        .endif
    .endf
    mov rdi,LclAlloc(&[rdx+rdx+0x200])
    mov rcx,[rsi].asym.seginfo
    mov [rcx].seg_info.CodeBuffer,rdi
    mov [rdi].dwarf_stmt_header32.version,2
    mov [rdi].dwarf_stmt_header32.minimum_instruction_length,1
    mov [rdi].dwarf_stmt_header32.default_is_stmt,1
    mov [rdi].dwarf_stmt_header32.line_base,DWLINE_BASE
    mov [rdi].dwarf_stmt_header32.line_range,DWLINE_RANGE
    mov [rdi].dwarf_stmt_header32.opcode_base,DWLINE_OPCODE_BASE
    lea rcx,[tmemcpy( &[rdi].dwarf_stmt_header32.stdopcode_lengths, &stdopsparms, DWLINE_OPCODE_BASE - 1 ) + DWLINE_OPCODE_BASE]
    mov eax,1
    mov [rcx-1],ah

    ; file entries sequence (entry consists of name and 3 LEBs (dir idx, time, size))
    ; if multiple file entries are to be supported, allocation size above has to be adjusted!

    .for ( rdx = MODULE.FNames, rdx = [rdx] : eax : rdx++, rcx++ )

        mov al,[rdx]
        mov [rcx],al
    .endf
    mov [rcx],eax
    lea rbx,[rcx+4]
    lea rax,[rdi].dwarf_stmt_header32.header_length
    sub rcx,rax
    mov [rdi].dwarf_stmt_header32.header_length,ecx

    ; now generate the line number "program"

    assume rbx:ptr byte

    .for ( rcx = SymTables[TAB_SEG*symbol_queue].head : rcx : rcx = [rcx].asym.next )

        mov rax,[rcx].asym.seginfo
        mov rax,[rax].seg_info.LinnumQueue

        .if ( rax )

            mov rdx,[rax].qdesc.head
            mov lni,rdx
            mov curr,rcx

            ; create "set address" extended opcode with fixup

            mov [rbx],0
            inc rbx

            .if ( MODULE.defOfssize == USE64 )

                mov [rbx],1+8
                inc rbx
                mov [rbx],DW_LNE_set_address
                inc rbx
                mov eax,[rdx].line_num_info.offs
                mov size_t ptr [rbx],rax
                CreateFixup( rcx, FIX_OFF64, OPTJ_NONE )
                mov rcx,rbx
                sub rcx,rdi
                mov [rax].fixup.locofs,ecx
                store_fixup( rax, rsi, rbx )
                add rbx,8
            .else
                mov [rbx],1+4
                inc rbx
                mov [rbx],DW_LNE_set_address
                inc rbx
                mov eax,[rdx].line_num_info.offs
                mov dword ptr [rbx],eax
                CreateFixup( rcx, FIX_OFF32, OPTJ_NONE )
                mov rcx,rbx
                sub rcx,rdi
                mov [rax].fixup.locofs,ecx
                store_fixup( rax, rsi, rbx )
                add rbx,4
            .endif
            mov rdx,lni
            mov ecx,[rdx].line_num_info.number
            dec ecx
            add rbx,dwarf_line_gen( ecx, [rdx].line_num_info.offs, rbx )

            .for ( rdx = lni : rdx : rdx = [rdx].line_num_info.next )

                .if ( [rdx].line_num_info.line_number & 0xFFF00000 )
                    .continue ; currently support 1 source file only
                .endif
                mov rax,[rdx].line_num_info.next
                .if ( !rax )
                    mov lni,rdx
                    mov rcx,curr
                    mov eax,[rcx].asym.max_offset
                    sub eax,[rdx].line_num_info.offs
                    dwarf_line_gen( 1, eax, rbx )
                .elseif ( [rax].line_num_info.line_number & 0xFFF00000 )
                    .continue
                .else
                    mov lni,rdx
                    mov ecx,[rax].line_num_info.number
                    sub ecx,[rdx].line_num_info.number
                    mov eax,[rax].line_num_info.offs
                    sub eax,[rdx].line_num_info.offs
                    dwarf_line_gen( ecx, eax, rbx )
                .endif
                add rbx,rax
                mov rdx,lni
            .endf
            mov rcx,curr
        .endif
    .endf

    mov [rbx],0
    inc rbx
    mov [rbx],1
    inc rbx
    mov [rbx],DW_LNE_end_sequence ; 1. 00=extended opcode, 2. size=1, 3. opcode
    inc rbx
    lea rax,[rdi].dwarf_stmt_header32.unit_length
    sub rbx,rax
    sub ebx,4
    mov [rdi].dwarf_stmt_header32.unit_length,ebx
    add ebx,4
    mov [rsi].asym.max_offset,ebx
    ret
    endp


    assume rbx:ptr elfmod

dwarf_create_sections proc __ccall uses rsi rdi rbx em:ptr elfmod

    ldr rbx,em
    .for ( rsi = &dwarf_segnames, edi = 0 : edi < NUM_DWSEGS : edi++ )
        CreateIntSegment( [rsi+rdi*string_t], "DWARF", 0, MODULE.Ofssize, FALSE )
        mov [rbx].dwarf_seg[rdi*asym_t],rax
    .endf
    dwarf_set_info( rbx, [rbx].dwarf_seg[DWINFO_IDX*asym_t] )
    dwarf_set_abbrev( rbx, [rbx].dwarf_seg[DWABBREV_IDX*asym_t] )
    dwarf_set_line( rbx, [rbx].dwarf_seg[DWLINE_IDX*asym_t] )
    ret
    endp

endif

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

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].asym.next )

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

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].asym.next )

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
    .return( NOT_ERROR )

    endp


; write 1 section's relocations (32-bit)

    assume rsi:ptr fixup

write_relocs32 proc __ccall uses rsi rdi rbx em:ptr elfmod, curr:asym_t

   .new elftype:byte
   .new reloc32:Elf32_Rel

    ldr rbx,em
    ldr rdx,curr
    mov rcx,[rdx].asym.seginfo

    .for ( rsi = [rcx].seg_info.head: rsi: rsi = [rsi].nextrlc )

        mov reloc32.r_offset,[rsi].locofs

        .switch ( [rsi].type )
        .case FIX_RELOFF32
            mov elftype,R_386_PC32
            mov rcx,[rsi].sym
            .if ( MODULE.pic && [rcx].asym.state == SYM_EXTERNAL )
                .if ( [rcx].asym.isproc ) ; added v2.34.25
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
                mov rdx,MODULE.fmtopt
                asmerr( 3019, [rdx].format_options.formatname, [rsi].type, [rcx].asym.name, [rsi].locofs )
            .else
                asmerr( 3014, [rsi].type, [rcx].asym.name, [rsi].locofs )
            .endif
        .endsw

        ; the low 8 bits of info are type
        ; the high 24 bits are symbol table index

        mov rcx,[rsi].sym
        mov reloc32.r_info,ELF32_R_INFO( [rcx].asym.ext_idx, elftype )
        movl rbx,rsi
        .ifd ( fwrite( &reloc32, 1, sizeof(reloc32), CurrFile[TOBJ] ) != sizeof(reloc32) )
            WriteError()
        .endif
        movl rsi,rbx
        movl rbx,em
    .endf
    ret

write_relocs32 endp


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
        .switch eax
        .case FIX_RELOFF32
            mov ebx,R_X86_64_PC32
            .if ( MODULE.pic && [rcx].asym.state == SYM_EXTERNAL )
                .if ( [rcx].asym.isproc ) ; added v2.34.25
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

write_relocs64 endp

    assume rdi:nothing, rsi:nothing


; write section contents and fixups


elf_write_data proc __ccall uses rsi rdi rbx em:ptr elfmod
ifdef _LIN64
    .new _rsi:ptr
    .new _rdi:ptr
endif
    .new i:int_t
    .new b:byte = 0

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].asym.next )

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

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].asym.next )

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
    .return( NOT_ERROR )

elf_write_data endp


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
        dwarf_create_sections( &em )
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
   .return( NOT_ERROR )

elf_write_module endp


; format-specific init.
; called once per module.

elf_init proc public

    mov MODULE.elf_osabi,ELFOSABI_SYSV
    mov MODULE.WriteModule,&elf_write_module
    ret

elf_init endp

    end
