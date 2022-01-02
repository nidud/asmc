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

IsWeak proto watcall sym:ptr asym {
    retm<( !( [eax].asym.sflags & S_ISCOM ) && [eax].asym.altname )>
    }

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

ElfConvertSectionName proc private uses esi edi ebx sym:ptr asym, buffer:string_t

    mov ecx,sym
    mov esi,[ecx].asym.name
    .for ( ebx = 0: ebx < lengthof( cst ) * conv_section: ebx += conv_section )
        .if ( tmemcmp( esi, cst[ebx].src, cst[ebx].len ) == 0 )
            movzx edi,cst[ebx].len
            .if ( byte ptr [esi+edi] == NULLC )
                .return( cst[ebx].dst )
            .elseif ( ( cst[ebx].flags & CSF_GRPCHK ) && byte ptr [esi+edi] == '$' )
                add esi,edi
                .return( strcat( strcpy( buffer, cst[ebx].dst ), esi ) )
            .endif
        .endif
    .endf
    .return( esi )

ElfConvertSectionName endp

; get number of sections that have relocations

get_num_reloc_sections proc private

    .for ( eax = 0, ecx = SymTables[TAB_SEG*symbol_queue].head: ecx: ecx = [ecx].dsym.next )
        mov edx,[ecx].dsym.seginfo
        .if ( [edx].seg_info.head )
            inc eax
        .endif
    .endf
    ret

get_num_reloc_sections endp

; fill entries in ELF32 symbol table

    assume ebx:ptr elfmod
    assume edi:ptr Elf32_Sym

ifndef ASMC64

set_symtab32 proc private uses esi edi ebx em:ptr elfmod, entries:uint_t, localshead:ptr localname

   .new len:uint_32
   .new strsize:uint_32 = 1
   .new p32:ptr Elf32_Sym
   .new buffer[MAX_ID_LEN + MANGLE_BYTES + 1]:char_t

    mov ebx,em
    imul esi,entries,sizeof( Elf32_Sym )
    mov [ebx].internal_segs[OSYMTAB_IDX].size,esi
    mov [ebx].internal_segs[OSYMTAB_IDX].data,LclAlloc( esi )
    mov edi,eax
    mov ecx,esi
    xor eax,eax
    mov edx,edi
    rep stosb
    lea edi,[edx+Elf32_Sym] ; skip NULL entry

    ; 1. make file entry

    mov [edi].st_name,strsize ; symbol's name in string table
    inc strlen( [ebx].srcname )
    add strsize,eax
    mov [edi].st_info,ELF32_ST_INFO( STB_LOCAL, STT_FILE ) ; symbol's type and binding info
    mov [edi].st_shndx,SHN_ABS ; section index
    add edi,Elf32_Sym

    assume ebx:nothing

    ; 2. make section entries

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head: esi: esi = [esi].dsym.next )

        mov [edi].st_info,ELF32_ST_INFO( STB_LOCAL, STT_SECTION )
        mov [edi].st_shndx,GetSegIdx( [esi].asym.segm )
        add edi,Elf32_Sym
    .endf

    ; 3. locals

    .for ( esi = localshead : esi : esi = [esi].localname.next )

        lea ebx,[Mangle( [esi].localname.sym, &buffer ) + 1]
        mov [edi].st_name,strsize
        mov ecx,[esi].localname.sym
        mov edx,[ecx].asym.segm
        .if ( edx )
            mov eax,[edx].dsym.seginfo
        .endif
        .if ( edx && [eax].seg_info.segtype != SEGTYPE_CODE )
            mov [edi].st_info,ELF32_ST_INFO( STB_LOCAL, STT_OBJECT )
        .else
            mov [edi].st_info,ELF32_ST_INFO( STB_LOCAL, STT_FUNC )
        .endif
        mov [edi].st_value,[ecx].asym.offs
        .if ( edx )
            mov [edi].st_shndx,GetSegIdx( edx )
        .else
            mov [edi].st_shndx,SHN_ABS
        .endif
        add strsize,ebx
        add edi,Elf32_Sym
    .endf

    ; 4. externals + communals (+ protos [since v2.01])

    .for ( esi = SymTables[TAB_EXT*symbol_queue].head: esi: esi = [esi].dsym.next )

        ; skip "weak" (=unused) externdefs

        .continue .if ( !( [esi].asym.sflags & S_ISCOM ) && [esi].asym.sflags & S_WEAK )

        lea ebx,[Mangle( esi, &buffer ) + 1]
        mov [edi].st_name,strsize

        ; for COMMUNALs, store their size in the Value field

        .if ( [esi].asym.sflags & S_ISCOM )

            mov [edi].st_info,ELF32_ST_INFO( STB_GLOBAL, STT_COMMON )
            mov [edi].st_value,[esi].asym.total_size
            mov [edi].st_shndx,SHN_COMMON
        .else
if OWELFIMPORT
            .if IsWeak( esi )
                mov [edi].st_info,ELF32_ST_INFO( STB_WEAK, STT_IMPORT )
            .else
                mov [edi].st_info,ELF32_ST_INFO( STB_GLOBAL, STT_IMPORT )
            .endif
else
            ; todo: set STT_FUNC for prototypes/code labels???
            .if IsWeak( esi )
                mov [edi].st_info,ELF32_ST_INFO( STB_WEAK, STT_NOTYPE )
            .else
                mov [edi].st_info,ELF32_ST_INFO( STB_GLOBAL, STT_NOTYPE )
            .endif
endif
            mov [edi].st_value,[esi].asym.offs ; is always 0
            mov [edi].st_shndx,SHN_UNDEF
        .endif
        add strsize,ebx
        add edi,Elf32_Sym
    .endf

if ELFALIAS

    ; 5. aliases

    .for ( esi = SymTables[TAB_ALIAS*symbol_queue].head: esi: esi = [esi].dsym.next )

        lea ebx,[Mangle( esi, &buffer ) + 1]
        mov [edi].st_name,strsize

if OWELFIMPORT
        mov [edi].st_info,ELF32_ST_INFO( STB_WEAK, STT_IMPORT )
else
        mov [edi].st_info,ELF32_ST_INFO( STB_WEAK, STT_NOTYPE )
endif
        mov [edi].st_value,0 ; is always 0
        mov [edi].st_shndx,SHN_UNDEF
        add strsize,ebx
        add edi,Elf32_Sym
    .endf
endif

    ; 6. PUBLIC entries

    .for ( esi = ModuleInfo.PubQueue.head: esi: esi = [esi].qnode.next )

        mov ebx,[esi].qnode.sym
        mov len,Mangle( ebx, &buffer )

        mov ebx,[ebx].asym.segm
        .if ( ebx )
            mov ecx,[ebx].dsym.seginfo
        .endif
        .if ( ebx && [ecx].seg_info.segtype != SEGTYPE_CODE )
            mov [edi].st_info,ELF32_ST_INFO( STB_GLOBAL, STT_OBJECT )
        .else
            mov [edi].st_info,ELF32_ST_INFO( STB_GLOBAL, STT_FUNC )
        .endif
        mov [edi].st_name,strsize
        mov ecx,[esi].qnode.sym
        mov [edi].st_value,[ecx].asym.offs

        .if ( [ecx].asym.state == SYM_INTERNAL )
            .if ( ebx )
                mov [edi].st_shndx,GetSegIdx( ebx )
            .else
                mov [edi].st_shndx,SHN_ABS
            .endif
        .else
            mov [edi].st_shndx,SHN_UNDEF
        .endif
        add strsize,len
        inc strsize
        add edi,Elf32_Sym
    .endf

if ADDSTARTLABEL
    mov ebx,ModuleInfo.start_label
    .if ( ebx )
        mov len,Mangle( ebx, &buffer )
        mov [edi].st_name,strsize
        mov [edi].st_info,ELF32_ST_INFO( STB_ENTRY, STT_FUNC )
        mov [edi].st_value,[ebx].asym.offs
        mov [edi].st_shndx,GetSegIdx( [ebx].asym.segm )
        add strsize,len
        inc strsize
        add edi,Elf32_Sym
    .endif
endif
    .return( strsize )

set_symtab32 endp

endif

    assume ebx:ptr elfmod
    assume edi:ptr Elf64_Sym

set_symtab64 proc private uses esi edi ebx em:ptr elfmod, entries:uint_t, localshead:ptr localname

   .new len:uint_32
   .new strsize:uint_32 = 1
   .new buffer[MAX_ID_LEN + MANGLE_BYTES + 1]:char_t

    mov ebx,em
    imul esi,entries,sizeof( Elf64_Sym )
    mov [ebx].internal_segs[OSYMTAB_IDX].size,esi
    mov [ebx].internal_segs[OSYMTAB_IDX].data,LclAlloc( esi )

    mov edi,eax
    mov ecx,esi
    xor eax,eax
    mov edx,edi
    rep stosb
    lea edi,[edx+Elf64_Sym] ; skip NULL entry

    ; 1. make file entry

    mov [edi].st_name,1 ; symbol's name in string table
    inc strlen( [ebx].srcname )
    add strsize,eax
    mov [edi].st_info,ELF64_ST_INFO( STB_LOCAL, STT_FILE ) ; symbol's type and binding info
    mov [edi].st_shndx,SHN_ABS ; section index
    add edi,Elf64_Sym

    assume ebx:nothing

    ; 2. make section entries

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head: esi: esi = [esi].dsym.next )

        mov [edi].st_info,ELF64_ST_INFO( STB_LOCAL, STT_SECTION )
        mov [edi].st_shndx,GetSegIdx( [esi].asym.segm )
        add edi,Elf64_Sym
    .endf

    ; 3. locals

    .for ( esi = localshead : esi : esi = [esi].localname.next )

        lea ebx,[Mangle( [esi].localname.sym, &buffer ) + 1]
        mov [edi].st_name,strsize
        mov ecx,[esi].localname.sym
        mov edx,[ecx].asym.segm
        .if ( edx )
            mov eax,[edx].dsym.seginfo
        .endif
        .if ( edx && [eax].seg_info.segtype != SEGTYPE_CODE )
            mov [edi].st_info,ELF64_ST_INFO( STB_LOCAL, STT_OBJECT )
        .else
            mov [edi].st_info,ELF64_ST_INFO( STB_LOCAL, STT_FUNC )
        .endif
        mov dword ptr [edi].st_value[0],[ecx].asym.offs
        .if ( edx )
            mov [edi].st_shndx,GetSegIdx( edx )
        .else
            mov [edi].st_shndx,SHN_ABS
        .endif
        add strsize,ebx
        add edi,Elf64_Sym
    .endf

    ; 4. externals + communals ( + protos [since v2.01])


    .for ( esi = SymTables[TAB_EXT*symbol_queue].head: esi: esi = [esi].dsym.next )

        ; skip "weak" (=unused) externdefs

        .continue .if ( !( [esi].asym.sflags & S_ISCOM ) && [esi].asym.sflags & S_WEAK )

        lea ebx,[Mangle( esi, &buffer ) + 1]
        mov [edi].st_name,strsize

        ; for COMMUNALs, store their size in the Value field

        .if ( [esi].asym.sflags & S_ISCOM )

            mov [edi].st_info,ELF64_ST_INFO( STB_GLOBAL, STT_COMMON )
            mov dword ptr [edi].st_value[0],[esi].asym.total_size
            mov [edi].st_shndx,SHN_COMMON
        .else
if OWELFIMPORT
            .if IsWeak( esi )
                mov [edi].st_info,ELF64_ST_INFO( STB_WEAK, STT_IMPORT )
            .else
                mov [edi].st_info,ELF64_ST_INFO( STB_GLOBAL, STT_IMPORT )
            .endif
else
            ; todo: set STT_FUNC for prototypes???
            .if IsWeak( esi )
                mov [edi].st_info,ELF64_ST_INFO( STB_WEAK, STT_NOTYPE )
            .else
                mov [edi].st_info,ELF64_ST_INFO( STB_GLOBAL, STT_NOTYPE )
            .endif
endif
            mov dword ptr [edi].st_value[0],[esi].asym.offs ; is always 0
            mov [edi].st_shndx,SHN_UNDEF
        .endif
        add strsize,ebx
        add edi,Elf64_Sym
    .endf

if ELFALIAS

    ; 5. aliases

    .for ( esi = SymTables[TAB_ALIAS*symbol_queue].head: esi: esi = [esi].dsym.next )

        lea ebx,[Mangle( esi, &buffer ) + 1]
        mov [edi].st_name,strsize

if OWELFIMPORT
        mov [edi].st_info,ELF64_ST_INFO( STB_WEAK, STT_IMPORT )
else
        mov [edi].st_info,ELF64_ST_INFO( STB_WEAK, STT_NOTYPE )
endif
        mov [edi].st_shndx,SHN_UNDEF
        add strsize,ebx
        add edi,Elf64_Sym
    .endf
endif

    ; 6. PUBLIC entries

    .for ( esi = ModuleInfo.PubQueue.head: esi: esi = [esi].qnode.next )

        mov ebx,[esi].qnode.sym
        mov len,Mangle( ebx, &buffer )

        mov edx,[ebx].asym.segm
        .if ( edx )
            mov ecx,[edx].dsym.seginfo
        .endif
        .if ( edx && [ecx].seg_info.segtype != SEGTYPE_CODE )
            mov [edi].st_info,ELF32_ST_INFO( STB_GLOBAL, STT_OBJECT )
        .else
            mov [edi].st_info,ELF32_ST_INFO( STB_GLOBAL, STT_FUNC )
        .endif
        mov [edi].st_name,strsize
        mov dword ptr [edi].st_value[0],[ebx].asym.offs
        .if ( [ebx].asym.state == SYM_INTERNAL )
            .if ( edx )
                mov [edi].st_shndx,GetSegIdx( edx )
            .else
                mov [edi].st_shndx,SHN_ABS
            .endif
        .else
            mov [edi].st_shndx,SHN_UNDEF
        .endif
        add strsize,len
        inc strsize
        add edi,Elf64_Sym
    .endf

if ADDSTARTLABEL
    mov ebx,ModuleInfo.start_label
    .if ( ebx )
        mov len,Mangle( ebx, &buffer )
        mov [edi].st_name,strsize
        mov [edi].st_info,ELF64_ST_INFO( STB_ENTRY, STT_FUNC )
        mov [edi].st_value,[ebx].asym.offs
        mov [edi].st_shndx,GetSegIdx( [ebx].asym.segm )
        add strsize,len
        inc strsize
        add edi,Elf64_Sym
    .endif
endif
    .return( strsize )

set_symtab64 endp


; calculate size of .symtab + .strtab section
; set content of these sections.

    assume ebx:ptr elfmod

.template locals
    head ptr localname ?
    tail ptr localname ?
   .ends

set_symtab_values proc private uses esi edi ebx em:ptr elfmod

   .new entries:int_32
   .new strsize:int_32
   .new l:locals = { NULL, NULL }

    ; symbol table. there is
    ; - 1 NULL entry,
    ; - 1 entry for the module/file,
    ; - 1 entry for each section and
    ; - n entries for local symbols
    ; - m entries for global symbols

    mov ebx,em

    ; symbol table starts with 1 NULL entry + 1 file entry

    mov [ebx].symindex,1 + 1

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head: esi: esi = [esi].dsym.next )

        mov [esi].asym.ext_idx,[ebx].symindex
        inc [ebx].symindex
    .endf

    ; add local symbols to symbol table

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head: esi: esi = [esi].dsym.next )
        mov ecx,[esi].dsym.seginfo
        .if ( [ecx].seg_info.num_relocs )
            mov edi,[ecx].seg_info.head
            assume edi:ptr fixup
            .for ( : edi : edi = [edi].nextrlc )

                ; if it's not EXTERNAL/PUBLIC, add symbol.
                ; however, if it's an assembly time variable
                ; use a raw section reference

                mov ecx,[edi].sym
                .if ( [ecx].asym.flags & S_VARIABLE )
                    mov [edi].sym,[edi].segment_var
                .elseif ( [ecx].asym.state == SYM_INTERNAL && \
                        !( [ecx].asym.flag1 & S_INCLUDED ) && !( [ecx].asym.flags & S_ISPUBLIC ) )

                    or [ecx].asym.flag1,S_INCLUDED
                    LclAlloc( sizeof( localname ) )
                    mov [eax].localname.next,NULL
                    mov ecx,[edi].sym
                    mov [eax].localname.sym,ecx
                    .if ( l.tail )
                        mov edx,l.tail
                        mov [edx].localname.next,eax
                        mov l.tail,eax
                    .else
                        mov l.head,eax
                        mov l.tail,eax
                    .endif
                    mov [ecx].asym.ext_idx,[ebx].symindex
                    inc [ebx].symindex
                .endif
            .endf
        .endif
    .endf
    mov [ebx].start_globals,[ebx].symindex

    ; count EXTERNs and used EXTERNDEFs (and PROTOs [since v2.01])

    .for ( ecx = SymTables[TAB_EXT*symbol_queue].head : ecx : ecx = [ecx].dsym.next )
        .if ( !( [ecx].asym.sflags & S_ISCOM ) && [ecx].asym.sflags & S_WEAK )
            .continue
        .endif
        mov [ecx].asym.ext_idx,[ebx].symindex
        inc [ebx].symindex
    .endf

if ELFALIAS

    ; count aliases

    .for ( ecx = SymTables[TAB_ALIAS*symbol_queue].head : ecx : ecx = [ecx].dsym.next )

        mov [ecx].asym.idx,[ebx].symindex
        inc [ebx].symindex
    .endf
endif

    ; count publics

    .for ( ecx = ModuleInfo.PubQueue.head: ecx: ecx = [ecx].qnode.next )

        mov edx,[ecx].qnode.sym
        mov [edx].asym.ext_idx,[ebx].symindex
        inc [ebx].symindex
    .endf

    ; size of symbol table is defined

    mov entries,[ebx].symindex

if ADDSTARTLABEL
    .if ( ModuleInfo.start_label )
        inc entries
    .endif
endif

    .if ( ModuleInfo.defOfssize == USE64 )
        mov strsize,set_symtab64( ebx, entries, l.head )
ifndef ASMC64
    .else
        mov strsize,set_symtab32( ebx, entries, l.head )
endif
    .endif

    ; generate the string table

    mov [ebx].internal_segs[OSTRTAB_IDX].size,strsize
    mov [ebx].internal_segs[OSTRTAB_IDX].data,LclAlloc( strsize )
if 0 ; zero alloc..
    memset( eax, 0, strsize )
endif
    lea edi,[eax+1]
    mov esi,[ebx].srcname
    .while ( byte ptr [esi] )
        movsb
    .endw
    movsb
    .for ( esi = l.head : esi : esi = [esi].localname.next )
        lea edi,[edi+Mangle( [esi].localname.sym, edi ) + 1]
    .endf

    .for ( esi = SymTables[TAB_EXT*symbol_queue].head : esi : esi = [esi].dsym.next )
        .if ( !( [esi].asym.sflags & S_ISCOM ) && [esi].asym.sflags & S_WEAK )
            .continue
        .endif
        lea edi,[edi+Mangle( esi, edi ) + 1]
    .endf

if ELFALIAS
    .for ( esi = SymTables[TAB_ALIAS*symbol_queue].head : esi : esi = [esi].dsym.next )
        lea edi,[edi+Mangle( esi, edi ) + 1]
    .endf
endif

    .for ( esi = ModuleInfo.PubQueue.head: esi: esi = [esi].qnode.next )
        mov ecx,[esi].qnode.sym
        lea edi,[edi+Mangle( ecx, edi ) + 1]
    .endf
if ADDSTARTLABEL
    .if ( ModuleInfo.g.start_label )
        Mangle( ModuleInfo.start_label, edi )
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

    assume ebx:nothing
    assume edi:nothing

set_shstrtab_values proc private uses esi edi ebx em:ptr elfmod

   .new size:dword = 1 ; the first byte at offset 0 is the NULL section name
   .new buffer[MAX_ID_LEN+1]:char_t

    ; get size of section names defined in the program & relocation sections )

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head : esi : esi = [esi].dsym.next )

        ; v2.07: ALIAS name defined?

        mov ebx,[esi].dsym.seginfo
        .if ( [ebx].seg_info.aliasname )
            mov edi,[ebx].seg_info.aliasname
        .else
            mov edi,ElfConvertSectionName( esi, &buffer )
        .endif

        add size,strlen( edi )
        inc size

        .if ( [ebx].seg_info.head )
            add size,strlen( edi )
            .if ( ModuleInfo.defOfssize == USE64 )
                add size,6;sizeof(".rela")
            .else
                add size,5;sizeof(".rel")
            .endif
        .endif
    .endf

    ; get internal section name sizes

    .for ( edi = &internal_segparms,
           ebx = 0 : ebx < NUM_INTSEGS : ebx++, edi += intsegparm )

        strlen( [edi].intsegparm.name )
        inc eax
        add size,eax
    .endf

    assume ebx:ptr elfmod

    mov ebx,em
    mov [ebx].internal_segs[OSHSTRTAB_IDX].size,size

    ; size is known, now alloc .shstrtab data buffer and fill it

    mov [ebx].internal_segs[OSHSTRTAB_IDX].data,LclAlloc( size )
    mov edi,eax
    mov byte ptr [edi],NULLC ; NULL section name
    inc edi

    ; 1. names of program sections

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head : esi : esi = [esi].dsym.next )

        mov ecx,[esi].dsym.seginfo
        .if ( [ecx].seg_info.aliasname )
            mov eax,[ecx].seg_info.aliasname
        .else
            ElfConvertSectionName( esi, &buffer )
        .endif
        strcpy( edi, eax )
        lea edi,[edi+strlen( edi ) + 1]
    .endf

    ; 2. names of internal sections

    .for ( esi = 0: esi < NUM_INTSEGS: esi++ )

        imul ecx,esi,intsegparm
        strcpy( edi, internal_segparms[ecx].name )
        lea edi,[edi+strlen( edi ) + 1]
    .endf

    ; 3. names of "relocation" sections

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head : esi : esi = [esi].dsym.next )

        mov ecx,[esi].dsym.seginfo
        .if ( [ecx].seg_info.head )

            .if ( ModuleInfo.defOfssize == USE64 )
                strcpy( edi, ".rela" )
            .else
                strcpy( edi, ".rel" )
            .endif
            add edi,strlen( edi )

            mov ecx,[esi].dsym.seginfo
            .if ( [ecx].seg_info.aliasname )
                mov eax,[ecx].seg_info.aliasname
            .else
                ElfConvertSectionName( esi, &buffer )
            .endif
            strcpy( edi, eax )
            lea edi,[edi+strlen( edi ) + 1]
        .endif
    .endf
    ret

set_shstrtab_values endp

get_relocation_count proc watcall private curr:ptr dsym

    .for ( ecx = [eax].dsym.seginfo, eax = 0,
           ecx = [ecx].seg_info.head: ecx : ecx = [ecx].fixup.nextrlc, eax++ )
    .endf
    ret

get_relocation_count endp

Get_Alignment proc watcall private curr:ptr dsym

    mov ecx,[eax].dsym.seginfo
    .if ( [ecx].seg_info.alignment == MAX_SEGALIGNMENT )
        .return( 0 )
    .endif
    mov cl,[ecx].seg_info.alignment
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
    assume ebx:ptr elfmod

ifndef ASMC64

elf_write_section_table32 proc private uses esi edi ebx modinfo:ptr module_info, em:ptr elfmod, fileoffset:dword

   .new shdr32:Elf32_Shdr

    add fileoffset,0xF
    and fileoffset,not 0xF

    ; set contents and size of internal .shstrtab section

    set_shstrtab_values( em )

    ; write the NULL entry

    memset( &shdr32, 0, sizeof( shdr32) )

    ; write the empty NULL entry

    .if ( fwrite( &shdr32, 1, sizeof(shdr32), CurrFile[OBJ*4] ) != sizeof(shdr32) )
        WriteError()
    .endif

    ; use p to scan strings (=section names) of .shstrtab

    mov ebx,em
    mov edi,[ebx].internal_segs[OSHSTRTAB_IDX].data
    inc edi ; skip 'name' of NULL entry

    ; write the section headers defined in the module,

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head : esi : esi = [esi].dsym.next )

        memset( &shdr32, 0, sizeof(shdr32) )

        mov eax,edi
        sub eax,[ebx].internal_segs[OSHSTRTAB_IDX].data
        mov shdr32.sh_name,eax
        lea edi,[edi+strlen( edi ) + 1]

        mov ecx,[esi].dsym.seginfo
        .if ( [ecx].seg_info.info ) ; v2.07:added; v2.12: highest priority
            mov shdr32.sh_type,SHT_NOTE
        .else
            .if ( [ecx].seg_info.segtype != SEGTYPE_BSS )
                mov shdr32.sh_type,SHT_PROGBITS
            .else
                mov shdr32.sh_type,SHT_NOBITS
            .endif
            .if ( [ecx].seg_info.segtype == SEGTYPE_CODE )
                mov shdr32.sh_flags,SHF_EXECINSTR or SHF_ALLOC
            .elseif ( [ecx].seg_info.readonly == TRUE )
                mov shdr32.sh_flags,SHF_ALLOC
            .else
                mov shdr32.sh_flags,SHF_WRITE or SHF_ALLOC
                .if ( [ecx].seg_info.clsym )
                    mov ecx,[ecx].seg_info.clsym
                    .if ( tstrcmp( [ecx].asym.name, "CONST" ) == 0 )
                        mov shdr32.sh_flags,SHF_ALLOC ; v2.07: added
                    .endif
                .endif
            .endif
        .endif

        mov shdr32.sh_offset,fileoffset ; start of section in file
        mov ecx,[esi].dsym.seginfo
        mov [ecx].seg_info.fileoffset,eax ; save the offset in the segment
        mov shdr32.sh_size,[esi].asym.max_offset
        mov shdr32.sh_addralign,Get_Alignment( esi )

        .if ( fwrite( &shdr32, 1, sizeof(shdr32), CurrFile[OBJ*4] ) != sizeof(shdr32) )
            WriteError()
        .endif
        get_relocation_count( esi )
        mov ecx,[esi].dsym.seginfo
        mov [ecx].seg_info.num_relocs,eax

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

    set_symtab_values( ebx )

    ; write headers of internal sections

    memset( &shdr32, 0, sizeof(shdr32) )

    .for ( esi = 0: esi < NUM_INTSEGS: esi++ )

        mov eax,edi
        sub eax,[ebx].internal_segs[OSHSTRTAB_IDX].data
        mov shdr32.sh_name,eax
        lea edi,[edi+strlen( edi ) + 1]

        imul ecx,esi,intsegparm
        mov shdr32.sh_type,internal_segparms[ecx].type
        mov shdr32.sh_offset,fileoffset ; start of section in file

        imul ecx,esi,intseg
        mov [ebx].internal_segs[ecx].fileoffset,fileoffset
        mov shdr32.sh_size,[ebx].internal_segs[ecx].size

        ; section .symtab is special

        .if ( esi == SYMTAB_IDX )
            mov ecx,modinfo
            mov eax,[ecx].module_info.num_segs
            add eax,1 + STRTAB_IDX
            mov shdr32.sh_link,eax
            mov shdr32.sh_info,[ebx].start_globals
            mov shdr32.sh_addralign,4
            mov shdr32.sh_entsize,sizeof( Elf32_Sym )
        .else
            mov shdr32.sh_link,0
            mov shdr32.sh_info,0
            mov shdr32.sh_addralign,1
            mov shdr32.sh_entsize,0
        .endif
        .if ( fwrite( &shdr32, 1, sizeof( shdr32 ), CurrFile[OBJ*4] ) != sizeof( shdr32 ) )
            WriteError()
        .endif

        add fileoffset,shdr32.sh_size
        add fileoffset,0xF
        and fileoffset,not 0xF
    .endf

    ; write headers of reloc sections

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head : esi : esi = [esi].dsym.next )

        mov ecx,[esi].dsym.seginfo
        .continue .if ( [ecx].seg_info.head == NULL )

        memset( &shdr32, 0, sizeof( shdr32 ) )

        mov eax,edi
        sub eax,[ebx].internal_segs[OSHSTRTAB_IDX].data
        mov shdr32.sh_name,eax
        lea edi,[edi+strlen( edi ) + 1]
        mov shdr32.sh_type,SHT_REL
        mov shdr32.sh_offset,fileoffset ; start of section in file

        ; save the file offset in the slot reserved for ELF relocs

        mov ecx,[esi].dsym.seginfo
        mov [ecx].seg_info.reloc_offset,eax

        ; size of section in file

        mov eax,sizeof( Elf32_Rel )
        mul [ecx].seg_info.num_relocs
        mov shdr32.sh_size,eax

        mov ecx,modinfo
        mov eax,[ecx].module_info.num_segs
        add eax,1 + SYMTAB_IDX
        mov shdr32.sh_link,eax

        ;; set info to the src section index

        mov shdr32.sh_info,GetSegIdx( [esi].asym.segm )
        mov shdr32.sh_addralign,4
        mov shdr32.sh_entsize,sizeof( Elf32_Rel )

        .if ( fwrite( &shdr32, 1, sizeof( shdr32 ), CurrFile[OBJ*4] ) != sizeof( shdr32 ) )
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

elf_write_section_table64 proc private uses esi edi ebx modinfo:ptr module_info, em:ptr elfmod, fileoffset:uint_t

   .new shdr64:Elf64_Shdr

    add fileoffset,0xF
    and fileoffset,not 0xF

    ; set contents and size of internal .shstrtab section

    set_shstrtab_values( em )

    ; write the NULL entry

    memset( &shdr64, 0, sizeof( shdr64) )

    ; write the empty NULL entry

    .if ( fwrite( &shdr64, 1, sizeof(shdr64), CurrFile[OBJ*4] ) != sizeof(shdr64) )
        WriteError()
    .endif

    ; use p to scan strings (=section names) of .shstrtab

    mov ebx,em
    mov edi,[ebx].internal_segs[OSHSTRTAB_IDX].data
    inc edi ; skip 'name' of NULL entry

    ; write the section headers defined in the module

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head : esi : esi = [esi].dsym.next )

        memset( &shdr64, 0, sizeof(shdr64) )

        mov eax,edi
        sub eax,[ebx].internal_segs[OSHSTRTAB_IDX].data
        mov shdr64.sh_name,eax
        lea edi,[edi+strlen( edi ) + 1]

        mov ecx,[esi].dsym.seginfo
        .if ( [ecx].seg_info.info == TRUE ) ; v2.07:added; v2.12: highest priority
            mov shdr64.sh_type,SHT_NOTE
        .else
            .if ( [ecx].seg_info.segtype != SEGTYPE_BSS )
                mov shdr64.sh_type,SHT_PROGBITS
             .else
                mov shdr64.sh_type,SHT_NOBITS
             .endif
            .if ( [ecx].seg_info.segtype == SEGTYPE_CODE )
                mov dword ptr shdr64.sh_flags[0],SHF_EXECINSTR or SHF_ALLOC
            .elseif ( [ecx].seg_info.readonly == TRUE )
                mov dword ptr shdr64.sh_flags[0],SHF_ALLOC
            .else
                mov dword ptr shdr64.sh_flags[0],SHF_WRITE or SHF_ALLOC
                .if ( [ecx].seg_info.clsym )
                    mov ecx,[ecx].seg_info.clsym
                    .if ( tstrcmp( [ecx].asym.name, "CONST" ) == 0 )
                        mov dword ptr shdr64.sh_flags[0],SHF_ALLOC ; v2.07: added
                    .endif
                .endif
            .endif
        .endif

        mov dword ptr shdr64.sh_offset,fileoffset ; start of section in file
        mov ecx,[esi].dsym.seginfo
        mov [ecx].seg_info.fileoffset,eax ; save the offset in the segment
        mov dword ptr shdr64.sh_size,[esi].asym.max_offset
        mov dword ptr shdr64.sh_addralign,Get_Alignment( esi )

        .if ( fwrite( &shdr64, 1, sizeof(shdr64), CurrFile[OBJ*4] ) != sizeof(shdr64) )
            WriteError()
        .endif
        get_relocation_count( esi )
        mov ecx,[esi].dsym.seginfo
        mov [ecx].seg_info.num_relocs,eax

        ; v2.12: don't adjust fileoffset for SHT_NOBITS sections

        .if ( shdr64.sh_type != SHT_NOBITS )
            add fileoffset,dword ptr shdr64.sh_size
            add fileoffset,0xF
            and fileoffset,not 0xF
        .endif
    .endf

    ; set size and contents of .symtab and .strtab sections

    set_symtab_values( ebx )

    ; write headers of internal sections

    memset( &shdr64, 0, sizeof(shdr64) )

    .for ( esi = 0: esi < NUM_INTSEGS: esi++ )

        mov eax,edi
        sub eax,[ebx].internal_segs[OSHSTRTAB_IDX].data
        mov shdr64.sh_name,eax
        lea edi,[edi+strlen( edi ) + 1]

        imul ecx,esi,intsegparm
        mov shdr64.sh_type,internal_segparms[ecx].type
        mov dword ptr shdr64.sh_offset[0],fileoffset ; start of section in file

        imul ecx,esi,intseg
        mov [ebx].internal_segs[ecx].fileoffset,eax
        mov dword ptr shdr64.sh_size[0],[ebx].internal_segs[ecx].size

        ; section .symtab is special

        .if ( esi == SYMTAB_IDX )
            mov ecx,modinfo
            mov eax,[ecx].module_info.num_segs
            add eax,1 + STRTAB_IDX
            mov shdr64.sh_link,eax
            mov shdr64.sh_info,[ebx].start_globals
            mov dword ptr shdr64.sh_addralign,4
            mov dword ptr shdr64.sh_entsize,sizeof( Elf64_Sym )
        .else
            mov shdr64.sh_link,0
            mov shdr64.sh_info,0
            mov dword ptr shdr64.sh_addralign,1
            mov dword ptr shdr64.sh_entsize,0
        .endif
        .if ( fwrite( &shdr64, 1, sizeof( shdr64 ), CurrFile[OBJ*4] ) != sizeof( shdr64 ) )
            WriteError()
        .endif

        add fileoffset,dword ptr shdr64.sh_size
        add fileoffset,0xF
        and fileoffset,not 0xF
    .endf

    ; write headers of reloc sections

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head : esi : esi = [esi].dsym.next )

        mov ecx,[esi].dsym.seginfo
        .continue .if ( [ecx].seg_info.head == NULL )

        memset( &shdr64, 0, sizeof(shdr64) )

        mov eax,edi
        sub eax,[ebx].internal_segs[OSHSTRTAB_IDX].data
        mov shdr64.sh_name,eax
        lea edi,[edi+strlen( edi ) + 1]

        mov shdr64.sh_type,SHT_RELA ; v2.05: changed REL to RELA
        mov dword ptr shdr64.sh_offset,fileoffset ; start of section in file

        ; save the file offset in the slot reserved for ELF relocs

        mov ecx,[esi].dsym.seginfo
        mov [ecx].seg_info.reloc_offset,eax

        ; size of section in file

        mov eax,sizeof( Elf64_Rela )
        mul [ecx].seg_info.num_relocs
        mov dword ptr shdr64.sh_size,eax

        mov ecx,modinfo
        mov eax,[ecx].module_info.num_segs
        add eax,SYMTAB_IDX + 1
        mov shdr64.sh_link,eax

        ; set info to the src section index

        mov shdr64.sh_info,GetSegIdx( [esi].asym.segm )
        mov dword ptr shdr64.sh_addralign,4
        mov dword ptr shdr64.sh_entsize,sizeof( Elf64_Rela )

        .if ( fwrite( &shdr64, 1, sizeof( shdr64 ), CurrFile[OBJ*4] ) != sizeof( shdr64 ) )
            WriteError()
        .endif

        add fileoffset,dword ptr shdr64.sh_size
        add fileoffset,0xF
        and fileoffset,not 0xF
    .endf
    .return( NOT_ERROR )

elf_write_section_table64 endp

; write 1 section's relocations (32-bit)

    assume esi:ptr fixup

write_relocs32 proc private uses esi edi ebx em:ptr elfmod, curr:ptr dsym

   .new elftype:byte
   .new reloc32:Elf32_Rel

    mov ebx,em
    mov edx,curr
    mov ecx,[edx].dsym.seginfo

    .for ( esi = [ecx].seg_info.head: esi: esi = [esi].nextrlc )

        mov reloc32.r_offset,[esi].locofs

        .switch ( [esi].type )
        .case FIX_OFF32        : mov elftype,R_386_32       : .endc
        .case FIX_RELOFF32     : mov elftype,R_386_PC32     : .endc
        .case FIX_OFF32_IMGREL : mov elftype,R_386_RELATIVE : .endc
if GNURELOCS
        .case FIX_OFF16    : mov [ebx].extused,TRUE : mov elftype,R_386_16   : .endc
        .case FIX_RELOFF16 : mov [ebx].extused,TRUE : mov elftype,R_386_PC16 : .endc
        .case FIX_OFF8     : mov [ebx].extused,TRUE : mov elftype,R_386_8    : .endc
        .case FIX_RELOFF8  : mov [ebx].extused,TRUE : mov elftype,R_386_PC8  : .endc
endif
        .default
            mov elftype,R_386_NONE
            mov ecx,curr
            .if ( [esi].type < FIX_LAST )
                mov edx,ModuleInfo.fmtopt
                asmerr( 3019, [edx].format_options.formatname, [esi].type, [ecx].asym.name, [esi].locofs )
            .else
                asmerr( 3014, [esi].type, [ecx].asym.name, [esi].locofs )
            .endif
        .endsw

        ; the low 8 bits of info are type
        ; the high 24 bits are symbol table index

        mov ecx,[esi].sym
        mov reloc32.r_info,ELF32_R_INFO( [ecx].asym.ext_idx, elftype )
        .if ( fwrite( &reloc32, 1, sizeof(reloc32), CurrFile[OBJ*4] ) != sizeof(reloc32) )
            WriteError()
        .endif
    .endf
    ret

write_relocs32 endp

; write 1 section's relocations (64-bit)

write_relocs64 proc private uses esi edi ebx curr:ptr dsym

   .new reloc64:Elf64_Rela ; v2.05: changed to Rela

    mov edx,curr
    mov ecx,[edx].dsym.seginfo

    .for ( esi = [ecx].seg_info.head: esi: esi = [esi].nextrlc )

        mov ecx,[esi].sym
        mov edi,[ecx].asym.ext_idx
        mov dword ptr reloc64.r_offset[4],0
        mov dword ptr reloc64.r_offset[0],[esi].locofs
        movzx eax,[esi].addbytes
        neg eax
        cdq
        mov dword ptr reloc64.r_addend[0],eax
        mov dword ptr reloc64.r_addend[4],edx

        movzx eax,[esi].type
        .switch ( eax )
        .case FIX_RELOFF32     : mov ebx,R_X86_64_PC32      : .endc
        .case FIX_OFF64        : mov ebx,R_X86_64_64        : .endc
        .case FIX_OFF32_IMGREL : mov ebx,R_X86_64_RELATIVE  : .endc
        .case FIX_OFF32        : mov ebx,R_X86_64_32        : .endc
        .case FIX_OFF16        : mov ebx,R_X86_64_16        : .endc
        .case FIX_RELOFF16     : mov ebx,R_X86_64_PC16      : .endc
        .case FIX_OFF8         : mov ebx,R_X86_64_8         : .endc
        .case FIX_RELOFF8      : mov ebx,R_X86_64_PC8       : .endc
        .default
            mov ecx,curr
            mov ebx,R_X86_64_NONE
            .if ( [esi].type < FIX_LAST )
                mov edx,ModuleInfo.fmtopt
                asmerr( 3019, [edx].format_options.formatname, [esi].type, [ecx].asym.name, [esi].locofs )
            .else
                asmerr( 3014, [esi].type, [ecx].asym.name, [esi].locofs )
            .endif
        .endsw
        mov dword ptr reloc64.r_info[0],ebx
        mov dword ptr reloc64.r_info[4],edi
        .if ( fwrite( &reloc64, 1, sizeof( reloc64 ), CurrFile[OBJ*4] ) != sizeof(reloc64) )
            WriteError()
        .endif
    .endf
    ret

write_relocs64 endp

; write section contents and fixups

    assume edi:nothing
    assume esi:nothing

elf_write_data proc private uses esi edi ebx modinfo:ptr module_info, em:ptr elfmod

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head : esi : esi = [esi].dsym.next )

        mov edi,[esi].dsym.seginfo
        mov ebx,[esi].asym.max_offset
        sub ebx,[edi].seg_info.start_loc
        .if ( [edi].seg_info.segtype != SEGTYPE_BSS && ebx )
            .if ( [edi].seg_info.CodeBuffer == NULL )
                fseek( CurrFile[OBJ*4], ebx, SEEK_CUR )
            .else
                mov ecx,[edi].seg_info.fileoffset
                add ecx,[edi].seg_info.start_loc
                fseek( CurrFile[OBJ*4], ecx, SEEK_SET )
                .if ( fwrite( [edi].seg_info.CodeBuffer, 1, ebx, CurrFile[OBJ*4] ) != ebx )
                    WriteError()
                .endif
            .endif
        .endif
    .endf

    ; write internal sections

    mov ebx,em
    .for ( esi = 0: esi < NUM_INTSEGS: esi++ )
        imul edi,esi,intseg
        .if ( [ebx].internal_segs[edi].data )
            fseek( CurrFile[OBJ*4], [ebx].internal_segs[edi].fileoffset, SEEK_SET )
            .if ( fwrite( [ebx].internal_segs[edi].data, 1, [ebx].internal_segs[edi].size, CurrFile[OBJ*4] ) != [ebx].internal_segs[edi].size )
                WriteError()
            .endif
        .endif
    .endf

    ; write reloc sections content

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head : esi : esi = [esi].dsym.next )

        mov edi,[esi].dsym.seginfo
        .if ( [edi].seg_info.num_relocs )
            fseek( CurrFile[OBJ*4], [edi].seg_info.reloc_offset, SEEK_SET )
            mov ecx,modinfo
            .if ( [ecx].module_info.defOfssize == USE64 )
                write_relocs64( esi )
            .else
                write_relocs32( ebx, esi )
            .endif
        .endif
    .endf
if GNURELOCS
    .if ( [ebx].extused )
        asmerr( 8013 )
    .endif
endif
    .return( NOT_ERROR )
elf_write_data endp

; write ELF module

elf_write_module proc private uses esi modinfo:ptr module_info

   .new em:elfmod

    memset( &em, 0, sizeof( em ) )

    mov esi,CurrFName[ASM*4]
    lea edx,[esi+strlen(esi)]

    ; the path part is stripped. todo: check if this is ok to do

    .while ( edx > esi )

        .break .if ( byte ptr [edx-1] == '\' )
        .break .if ( byte ptr [edx-1] == '/' )
        dec edx
    .endw
    mov em.srcname,edx

    ; position at 0 ( probably unnecessary, since there were no writes yet )

    fseek( CurrFile[OBJ*4], 0, SEEK_SET )

    mov esi,modinfo
ifndef ASMC64
    .switch ( [esi].module_info.defOfssize )
    .case USE64
endif
        memcpy( &em.ehdr64.e_ident, ELF_SIGNATURE, ELF_SIGNATURE_LEN )
        mov em.ehdr64.e_ident[EI_CLASS],ELFCLASS64
        mov em.ehdr64.e_ident[EI_DATA],ELFDATA2LSB
        mov em.ehdr64.e_ident[EI_VERSION],EV_CURRENT
        mov em.ehdr64.e_ident[EI_OSABI],[esi].module_info.elf_osabi

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
        add eax,[esi].module_info.num_segs
        add eax,1 + 3
        mov em.ehdr64.e_shnum,ax

        mov eax,[esi].module_info.num_segs
        add eax,1 + SHSTRTAB_IDX
        mov em.ehdr64.e_shstrndx,ax ; set index of .shstrtab section

        .if ( fwrite( &em.ehdr64, 1, sizeof( em.ehdr64 ), CurrFile[OBJ*4] ) != sizeof( em.ehdr64 ) )
            WriteError()
        .endif
        movzx eax,em.ehdr64.e_shnum
        mul em.ehdr64.e_shentsize
        add eax,sizeof( Elf64_Ehdr )
        elf_write_section_table64( esi, &em, eax )

ifndef ASMC64

        .endc
    .default
        memcpy( &em.ehdr32.e_ident, ELF_SIGNATURE, ELF_SIGNATURE_LEN )
        mov em.ehdr32.e_ident[EI_CLASS],ELFCLASS32
        mov em.ehdr32.e_ident[EI_DATA],ELFDATA2LSB
        mov em.ehdr32.e_ident[EI_VERSION],EV_CURRENT
        mov em.ehdr32.e_ident[EI_OSABI],[esi].module_info.elf_osabi

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
        add eax,[esi].module_info.num_segs
        add eax,1 + 3
        mov em.ehdr32.e_shnum,ax

        mov eax,[esi].module_info.num_segs
        add eax,1 + SHSTRTAB_IDX
        mov em.ehdr32.e_shstrndx,ax ; set index of .shstrtab section

        .if ( fwrite( &em.ehdr32, 1, sizeof( em.ehdr32 ), CurrFile[OBJ*4] ) != sizeof( em.ehdr32 ) )
            WriteError()
        .endif
        movzx eax,em.ehdr32.e_shnum
        mul em.ehdr32.e_shentsize
        add eax,sizeof( Elf32_Ehdr )
        elf_write_section_table32( esi, &em, eax )
    .endsw
endif
    elf_write_data( esi, &em )
    .return( NOT_ERROR )

elf_write_module endp

; format-specific init.
; called once per module.

elf_init proc modinfo:ptr module_info
    mov ecx,modinfo
    mov [ecx].module_info.elf_osabi,ELFOSABI_LINUX
    mov [ecx].module_info.WriteModule,elf_write_module
    ret
elf_init endp

    end
