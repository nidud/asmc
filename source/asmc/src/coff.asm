; COFF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description:  COFF output routines
;

include time.inc

include asmc.inc
include memalloc.inc
include mangle.inc
include parser.inc
include fixup.inc
include segment.inc
include extern.inc
include coff.inc
include coffspec.inc
include input.inc
include omfspec.inc
include linnum.inc
include dbgcv.inc

define SIZE_CV_SEGBUF ( MAX_LINE_LEN * 2 )

define MANGLE_BYTES 8 ; extra size required for name decoration

; v2.04: to make JWasm always add static (=private) procs to the symbol table
; set STATIC_PROCS to 1. Normally those procs are only added if line
; number/symbolic debugging information is generated.

define STATIC_PROCS 1 ; v2.10: changed to 1, because Masm 6-10 DOES add static procs
define COMPID       0 ; 1=add comp.id absolute symbol

; size of codeview temp segment buffer; prior to v2.12 it was 1024 - but this may be
; insufficient if MAX_ID_LEN has been enlarged.

.template stringitem
    next    ptr stringitem ?
    string  db 1 dup(?)
   .ends

cv_write_debug_tables proto __ccall :asym_t, :asym_t, :ptr

; v2.10: COMDAT CRC calculation ( suggestion by drizz, slightly modified )

.data?
CRC32Table uint_32 256 dup(?) ; table is initialized if needed

.data

CRC32_Init  uint_32 FALSE

; -Zi option section info
SymDebName string_t @CStr(".debug$S"), @CStr(".debug$T")

szdrectve equ <".drectve">

    .code

    option proc:private

; alloc a string which will be stored in the COFF string table

    assume rbx:ptr coffmod

Coff_AllocString proc __ccall uses rsi rdi rbx cm:ptr coffmod, string:string_t, len:int_t


    ldr rsi,string
    ldr rbx,cm
    mov edi,[rbx].size

    mov ecx,len
    lea eax,[rcx+1]
    add [rbx].size,eax

    LclAlloc( &[rax + sizeof( stringitem ) - 1] )

    mov ecx,len
    mov edx,edi
    lea rdi,[rax].stringitem.string
    inc ecx
    rep movsb

    .if ( [rbx].head )

        mov rcx,[rbx].tail
        mov [rcx].stringitem.next,rax
        mov [rbx].tail,rax
    .else
        mov [rbx].head,rax
        mov [rbx].tail,rax
    .endif
    .return( edx )

Coff_AllocString endp


; return number of line number items

GetLinnumItems proc fastcall q:ptr qdesc

    UNREFERENCED_PARAMETER(q)

    .for ( eax = 0, rdx = [rcx].qdesc.head: rdx: eax++ )
        mov rdx,[rdx].line_num_info.next
    .endf
    ret

GetLinnumItems endp


; write COFF section table

coff_write_section_table proc __ccall uses rsi rdi rbx cm:ptr coffmod

  local segtype:dword
  local ish:IMAGE_SECTION_HEADER
  local buffer[MAX_ID_LEN+1]:char_t

    ; calculated file offset for section data, relocs and linenumber info

    imul esi,MODULE.num_segs,sizeof( IMAGE_SECTION_HEADER )
    add  esi,sizeof( IMAGE_FILE_HEADER )

    mov rbx,cm
    mov [rbx].start_data,esi

    .for ( rdi = SegTable: rdi: rdi = [rdi].asym.next )

        mov segtype,SEGTYPE_UNDEF

        ; v2.07: prefer ALIAS name if defined.

        mov rdx,[rdi].asym.seginfo
        mov rax,[rdx].seg_info.aliasname
        .if ( rax == NULL )

            ConvertSectionName( rdi, &segtype, &buffer )
        .endif
        mov rbx,rax

        ; if section name is longer than 8 chars, a '/' is stored,
        ; followed by a number in ascii which is the offset for the string table

        .if ( tstrlen( rax ) <= IMAGE_SIZEOF_SHORT_NAME )
            tstrncpy( &ish.Name, rbx, IMAGE_SIZEOF_SHORT_NAME )
        .else
            tsprintf( &ish.Name, "/%u", Coff_AllocString( cm, rbx, eax ) )
        .endif

        mov ish.SizeOfRawData,[rdi].asym.max_offset
        .if ( eax )
            mov eax,esi
        .endif
        mov ish.PointerToRawData,eax

        xor eax,eax
        mov ish.Misc.PhysicalAddress,eax
        mov ish.VirtualAddress,eax
        mov ish.PointerToRelocations,eax
        mov ish.PointerToLinenumbers,eax
        mov ish.NumberOfRelocations,ax
        mov ish.NumberOfLinenumbers,ax
        mov ish.Characteristics,eax

        ; set field Characteristics; optionally reset PointerToRawData/SizeOfRawData

        mov rdx,[rdi].asym.seginfo
        assume rdx:segment_t

        .if ( [rdx].information )

            ; v2.09: set "remove" flag for .drectve section, as it was done in v2.06 and earlier
            mov rcx,cm
            .if ( rdi == [rcx].coffmod.directives )
                mov ish.Characteristics, ( IMAGE_SCN_LNK_INFO or IMAGE_SCN_LNK_REMOVE )
            .else
                mov ish.Characteristics, ( IMAGE_SCN_LNK_INFO or IMAGE_SCN_CNT_INITIALIZED_DATA )
            .endif

        .else

            .if ( [rdx].alignment != MAX_SEGALIGNMENT ) ; ABS not possible

                movzx eax,[rdx].alignment
                inc eax
                shl eax,20
                or ish.Characteristics,eax
            .endif

            .if ( [rdx].comdatselection )

                or ish.Characteristics,IMAGE_SCN_LNK_COMDAT
            .endif

            xor ecx,ecx
            .if [rdx].clsym

                mov rax,[rdx].clsym
                mov rax,[rax].asym.name

                .if dword ptr [rax] == 'SNOC' && word ptr [rax+4] == 'T'

                    inc ecx
                .endif
            .endif

            .if ( [rdx].segtype == SEGTYPE_CODE )
                or ish.Characteristics,IMAGE_SCN_CNT_CODE or IMAGE_SCN_MEM_EXECUTE or IMAGE_SCN_MEM_READ
            .elseif ( [rdx].readonly )
                or ish.Characteristics,IMAGE_SCN_CNT_INITIALIZED_DATA or IMAGE_SCN_MEM_READ
            .elseif ( ecx )
                or ish.Characteristics,IMAGE_SCN_CNT_INITIALIZED_DATA or IMAGE_SCN_MEM_READ
            .elseif ( [rdx].segtype == SEGTYPE_BSS || segtype == SEGTYPE_BSS )

                ; v2.12: if segtype is bss, ensure that seginfo->segtype is also bss; else
                ; the segment might be written in coff_write_data().

                mov [rdx].segtype,SEGTYPE_BSS
                or  ish.Characteristics,IMAGE_SCN_CNT_UNINITIALIZED_DATA or IMAGE_SCN_MEM_READ or IMAGE_SCN_MEM_WRITE
                mov ish.PointerToRawData,0
            .elseif ( [rdx].combine == COMB_STACK && [rdx].bytes_written == 0 )
                or  ish.Characteristics,IMAGE_SCN_CNT_UNINITIALIZED_DATA or IMAGE_SCN_MEM_READ or IMAGE_SCN_MEM_WRITE
                mov ish.SizeOfRawData,0
                mov ish.PointerToRawData,0
            .else
                or ish.Characteristics,IMAGE_SCN_CNT_INITIALIZED_DATA or IMAGE_SCN_MEM_READ or IMAGE_SCN_MEM_WRITE
            .endif
        .endif

        ; manual characteristics set?

        .if ( [rdx].characteristics )

            and ish.Characteristics,0x1FFFFFF ; clear the IMAGE_SCN_MEM flags
            movzx eax,[rdx].characteristics
            and eax,0xFE
            shl eax,24
            or ish.Characteristics,eax
        .endif

        .if ( ish.PointerToRawData )

            add esi,ish.SizeOfRawData
        .endif

        ; set fields PointerToRelocations/NumberOfRelocations; update 'fileoffset'.
        ; v2.10: don't use the 16-bit NumberOfRelocations member to count relocs!
        ; if the true number of relocs doesn't fit in 16-bits, set the appropriate
        ; flag in the section header!

        assume rcx:ptr fixup

        mov rcx,[rdx].head
        .if ( rcx )

            .for ( : rcx : rcx = [rcx].nextrlc )

                .if ( [rcx].sym == NULL )

                    .if ( [rcx].type == FIX_RELOFF32 )

                        mov eax,[rcx].locofs
                        sub eax,[rdx].start_loc
                        add rax,[rdx].CodeBuffer
                        movzx edx,[rcx].addbytes
                        add edx,[rcx].locofs
                        sub [rax],edx
                        mov rdx,[rdi].asym.seginfo
                    .endif
                    mov [rcx].type,FIX_VOID
                    .continue
                .endif
                inc [rdx].num_relocs
            .endf

            inc esi
            and esi,not 1
            mov ish.PointerToRelocations,esi

            ; v2.10: handle the "relocs overflow"-case

            imul eax,[rdx].num_relocs,sizeof( IMAGE_RELOCATION )
            add esi,eax

            .if ( [rdx].num_relocs <= 0xffff )
                mov eax,[rdx].num_relocs
                mov ish.NumberOfRelocations,ax
            .else
                mov ish.NumberOfRelocations,0xffff
                or  ish.Characteristics,IMAGE_SCN_LNK_NRELOC_OVFL

                ; add 1 relocation - the true number of relocations is stored
                ; in the first relocation item

                add esi,sizeof( IMAGE_RELOCATION )
            .endif
        .endif

        ; set fields PointerToLinenumbers/NumberOfLinenumbers; update 'fileoffset'

        .if ( [rdx].LinnumQueue && Options.debug_symbols != 4 )

            mov ish.PointerToLinenumbers,esi
            mov ish.NumberOfLinenumbers,GetLinnumItems( [rdx].LinnumQueue )
            movzx eax,ish.NumberOfLinenumbers
            imul eax,eax,sizeof( IMAGE_LINENUMBER )
            add esi,eax
        .endif
ifdef _LIN64
        push rsi
        push rdi
endif
        .ifd ( fwrite( &ish, 1, sizeof( ish ), CurrFile[OBJ*string_t] ) != sizeof( ish ) )
            WriteError()
        .endif
ifdef _LIN64
        pop rdi
        pop rsi
endif
    .endf
    .return( NOT_ERROR )

coff_write_section_table endp


;
; get value for field 'type' ( IMAGE_SYM_TYPE_x ) in symbol table.
; MS tools use only 0x0 or 0x20.
;
    assume rdx:nothing
    assume rcx:asym_t

CoffGetType proc fastcall sym:asym_t

    UNREFERENCED_PARAMETER(sym)

    .return( 0x20 ) .if ( [rcx].isproc )
    .return( IMAGE_SYM_TYPE_NULL )

CoffGetType endp


; get value for field 'class' ( IMAGE_SYM_CLASS_x ) in symbol table.

CoffGetClass proc fastcall sym:asym_t

    UNREFERENCED_PARAMETER(sym)

    .if ( [rcx].state == SYM_EXTERNAL )
        .if ( !( [rcx].iscomm ) && [rcx].altname )
            .return( IMAGE_SYM_CLASS_WEAK_EXTERNAL )
        .else
            .return( IMAGE_SYM_CLASS_EXTERNAL )
        .endif
    .elseif ( [rcx].ispublic )
        .return( IMAGE_SYM_CLASS_EXTERNAL )

    ; v2.09: don't declare private procs as label
    .elseif ( [rcx].mem_type == MT_NEAR && !( [rcx].isproc ) )
        .return( IMAGE_SYM_CLASS_LABEL )
    .endif
    .return( IMAGE_SYM_CLASS_STATIC )

CoffGetClass endp

    assume rcx:nothing
    assume rdi:nothing


;
; calc number of entries in symbol table for a file entry
;

GetFileAuxEntries proc __ccall file:uint_16, fname:ptr string_t

    GetFName( file )

    .if ( fname )

        mov rcx,fname
        mov [rcx],rax
    .endif
    tstrlen( rax )

    cdq
    mov     ecx,IMAGE_AUX_SYMBOL
    div     ecx
    add     eax,edx
    mov     eax,0
    setnz   al
    ret

GetFileAuxEntries endp


CRC32Comdat proc __ccall uses rsi rbx lpBuffer:ptr byte, dwBufLen:uint_32, dwCRC:uint_32

    .if ( !CRC32_Init )

        mov CRC32_Init,TRUE
        .for ( ecx = 0: ecx < 256: ecx++ )
            .for ( edx = 0, eax = ecx: edx < 8: edx++ )

                mov ebx,eax
                and ebx,1
                imul ebx,ebx,0xEDB88320
                shr eax,1
                xor eax,ebx
            .endf
            lea rdx,CRC32Table
            mov [rdx+rcx*4],eax
        .endf
    .endif

    mov eax,dwCRC
    mov rcx,lpBuffer

    .if ( rcx ) ; v2.11: lpBuffer may be NULL ( uninitialized data segs )
        .for ( ebx = dwBufLen, edx = 0 : ebx : ebx-- )

            mov dl,[rcx]
            inc rcx
            xor dl,al
            shr eax,8
            lea rsi,CRC32Table
            xor eax,[rsi+rdx*4]
        .endf
    .endif
    ret

CRC32Comdat endp


; write COFF symbol table
; contents of the table
; - @@feat.00 if .SAFESEH was set
; - file (+ 1-n aux)
; - 2 entries per section
; - externals, communals and publics
; - entries for relocations (internal)
; - aliases (weak externals)


coff_write_symbol proc __ccall uses rsi rdi name:string_t, strpos:dword, value:dword,
        section:dword, type:dword, storageclass:dword, aux:dword

  local sym:IMAGE_SYMBOL

    .if ( name )
        tstrncpy( &sym.N.ShortName, name, IMAGE_SIZEOF_SHORT_NAME )
    .else
        mov sym.N.LongName[0],0
        mov sym.N.LongName[4],strpos
    .endif
    mov sym.Value,value
    mov sym.SectionNumber,section
    mov sym.Type,type
    mov sym.StorageClass,storageclass
    mov sym.NumberOfAuxSymbols,aux
    .ifd ( fwrite( &sym, 1, sizeof( IMAGE_SYMBOL ), CurrFile[OBJ*string_t] ) != sizeof( IMAGE_SYMBOL ) )
        WriteError()
    .endif
    ret

coff_write_symbol endp


coff_write_aux proc __ccall uses rsi rdi sym:ptr, name:string_t

    .if ( name )
        tstrncpy( sym, name, IMAGE_AUX_SYMBOL )
    .endif
    .ifd ( fwrite( sym, 1, IMAGE_AUX_SYMBOL, CurrFile[OBJ*string_t] ) != IMAGE_AUX_SYMBOL )
        WriteError()
    .endif
    ret

coff_write_aux endp


GetStartLabel proc __ccall uses rbx buffer:string_t, msg:dword

  local mangle[MAX_ID_LEN + MANGLE_BYTES + 1]:char_t

    lea rbx,mangle
    xor eax,eax

    .if ( MODULE.start_label )

        Mangle( MODULE.start_label, rbx )

        .if ( !Options.entry_decorated )

            mov rdx,MODULE.start_label
            movzx eax,[rdx].asym.langtype
            .if ( eax != LANG_C && eax != LANG_STDCALL && eax != LANG_SYSCALL )

                mov rdx,[rdx].asym.name
                .if ( byte ptr [rdx] != '_' )

                    .if ( msg && ( MODULE.defOfssize != USE64 ) )

                        asmerr( 8011, rdx )
                    .endif
                .else
                    inc rbx
                .endif
            .else
                inc rbx
            .endif
        .endif
        tstrlen( tstrcpy( buffer, rbx ) )
        add eax,8 ; == size of " -entry:"
    .endif
    ret

GetStartLabel endp


coff_write_symbols proc __ccall uses rsi rdi rbx cm:ptr coffmod

  .new cntSymbols:uint_32 = 0
  .new p:string_t
  .new ias:IMAGE_AUX_SYMBOL
  .new lastfile:word = 0
  .new buffer[MAX_ID_LEN + MANGLE_BYTES + 1]:char_t
  .new strpos:int_32 = 0
  .new value:int_32
  .new section:int_t
  .new type:int_t
  .new aux:int_t
  .new count:int_t

if COMPID
    ; write "@comp.id" entry
    .if ( Options.debug_symbols == 4 )
        coff_write_symbol( "@comp.id", 0, 0x01037296, ;; value of Masm v14.00.24210.0
                IMAGE_SYM_ABSOLUTE, IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_STATIC, 0 )
        inc cntSymbols
    .endif
endif
    ; "@feat.00" entry (for SafeSEH)
    .if ( Options.safeseh )
        mov ecx,1
        .if ( Options.debug_symbols == 4 )
            mov ecx,16
        .endif
        coff_write_symbol( "@feat.00", 0, ecx,
                IMAGE_SYM_ABSOLUTE, IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_STATIC, 0 )
        inc cntSymbols
    .endif

    ; .file item (optionally disabled by -zlf)

    .if ( Options.no_file_entry == FALSE )

        ; index of next .file entry
        mov rbx,cm
        mov rsi,[rbx].dot_file_value
        tstrlen( rsi )
        mov ecx,sizeof(IMAGE_AUX_SYMBOL)
        cdq
        div ecx
        .if edx
            inc eax
        .endif
        mov aux,eax
        xor ecx,ecx
        .if Options.line_numbers
            mov ecx,[rbx].start_files
        .endif
        coff_write_symbol( ".file", 0, ecx, IMAGE_SYM_DEBUG, IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_FILE, aux )
        .for ( edi = aux : edi: edi--, rsi += sizeof(IMAGE_AUX_SYMBOL) )
            coff_write_aux( &ias, rsi )
        .endf
        mov eax,aux
        inc eax
        add cntSymbols,eax
    .endif

    ; next are section entries

    .for ( ebx = 1, rdi = SegTable: rdi: rdi = [rdi].asym.next, ebx++ )

        ; v2.07: prefer ALIAS name if defined

        mov rdx,[rdi].asym.seginfo
        mov rax,[rdx].seg_info.aliasname
        .if ( rax == NULL )
            ConvertSectionName( rdi, NULL, &buffer )
        .endif
        mov rsi,rax
        tstrlen( rax )
        .if ( eax > IMAGE_SIZEOF_SHORT_NAME )
            mov strpos,Coff_AllocString( cm, rsi, eax )
            mov esi,NULL
        .endif
        xor ecx,ecx
        .if Options.no_section_aux_entry == FALSE
            inc ecx
        .endif
        coff_write_symbol( rsi, strpos, 0, ebx, IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_STATIC, ecx )
        inc cntSymbols

        ; write the auxiliary symbol record for sections.
        ; may be suppressed with option -zls.

        mov rsi,[rdi].asym.seginfo
        assume rsi:segment_t

        .if ( Options.no_section_aux_entry == FALSE || [rsi].comdatselection )

            tmemset( &ias, 0, sizeof(ias) )
            mov ias.Section.Length,[rdi].asym.max_offset
            mov eax,[rsi].num_relocs
            .if ( eax > 0xffff )
                mov eax,0xffff
            .endif
            mov ias.Section.NumberOfRelocations,ax
            .if ( Options.line_numbers && Options.debug_symbols != 4 )
                mov ias.Section.NumberOfLinenumbers,[rsi].num_linnums
            .endif

            ; CheckSum, Number and Selection are for COMDAT sections only

            .if ( [rsi].comdatselection )
                mov ias.Section.CheckSum,CRC32Comdat( [rsi].CodeBuffer, [rdi].asym.max_offset, 0 )
                mov ias.Section.Number,[rsi].comdat_number
                mov ias.Section.Selection,[rsi].comdatselection
            .endif
            coff_write_aux( &ias, NULL )
            inc cntSymbols
        .endif

        assume rsi:nothing

    .endf

    ; third are externals + communals ( + protos [since v2.01] )

    .for ( rdi = ExtTable : rdi != NULL : rdi = [rdi].asym.next )

        ; skip "weak" (=unused) externdefs

        .continue .if ( !( [rdi].asym.iscomm ) && [rdi].asym.weak )

        lea rbx,buffer
        mov ecx,Mangle( rdi, rbx )

        ; for COMMUNALs, store their size in the Value field

        .if ( [rdi].asym.iscomm )
            mov value,[rdi].asym.total_size
        .else
            mov value,[rdi].asym.offs ;; is always 0
        .endif

        .if ( ecx > IMAGE_SIZEOF_SHORT_NAME )
            mov strpos,Coff_AllocString( cm, rbx, ecx )
            xor ebx,ebx
        .endif
        mov esi,CoffGetClass( rdi )
        mov ecx,CoffGetType( rdi )
        xor eax,eax
        .if ( !( [rdi].asym.iscomm ) && [rdi].asym.altname )
            inc eax
        .endif
        coff_write_symbol( rbx, strpos, value, IMAGE_SYM_UNDEFINED, ecx, esi, eax )
        inc cntSymbols

        ; for weak externals, write the auxiliary record

        .if ( !( [rdi].asym.iscomm ) && [rdi].asym.altname )

            tmemset( &ias, 0, sizeof(ias) )
            mov rcx,[rdi].asym.altname
            mov ias.Sym.TagIndex,[rcx].asym.ext_idx

            ; v2.10: weak externals defined via "extern sym (altsym) ..."
            ; are to have characteristics IMAGE_WEAK_EXTERN_SEARCH_LIBRARY.

            mov ias.Sym.Misc.TotalSize,IMAGE_WEAK_EXTERN_SEARCH_LIBRARY
            coff_write_aux( &ias, NULL )
            inc cntSymbols
        .endif
    .endf

    ; publics and internal symbols. The internal symbols have
    ; been written to the "public" queue inside coff_write_data().

    .for ( rdi = MODULE.PubQueue.head: rdi: rdi = [rdi].qnode.next )

        mov rsi,[rdi].qnode.sym
        mov ebx,Mangle( rsi, &buffer )
        mov rcx,[rsi].asym.debuginfo

        .if ( Options.line_numbers && Options.debug_symbols != 4 &&
              [rsi].asym.isproc &&
              [rcx].debug_info.file != lastfile )

            mov lastfile,[rcx].debug_info.file
            mov aux,GetFileAuxEntries( [rcx].debug_info.file, &p )
            mov rdx,[rsi].asym.debuginfo
            coff_write_symbol( ".file", 0, [rdx].debug_info.next_file,
                    IMAGE_SYM_DEBUG, IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_FILE, aux )

            .for ( rdx = p, eax = aux: eax: eax-- )
                add rdx,sizeof(IMAGE_AUX_SYMBOL)
            .endf
            coff_write_aux( &ias, rdx )
            mov eax,aux
            inc eax
            add cntSymbols,eax
        .endif

        .if ( [rsi].asym.state == SYM_INTERNAL )
            .if ( [rsi].asym.segm )
                mov section,GetSegIdx( [rsi].asym.segm )
            .else
                mov section,IMAGE_SYM_ABSOLUTE
            .endif
        .else
            mov section,IMAGE_SYM_UNDEFINED
        .endif
        mov aux,0
        .if ( Options.line_numbers && [rsi].asym.isproc && Options.debug_symbols != 4 )
            inc aux
        .endif
        mov ecx,ebx
        lea rbx,buffer
        .if ( ecx > IMAGE_SIZEOF_SHORT_NAME )
            mov strpos,Coff_AllocString( cm, rbx, ecx )
            xor ebx,ebx
        .endif
        mov p,rbx
        mov value,[rsi].asym.offs
        mov ebx,CoffGetType( rsi )
        mov ecx,CoffGetClass( rsi )
        coff_write_symbol( p, strpos, value, section, ebx, ecx, aux )
        inc cntSymbols

        .if ( Options.line_numbers && [rsi].asym.isproc && Options.debug_symbols != 4 )

            ; write:
            ; 1.   the aux for the proc
            ; 2+3. a .bf record with 1 aux
            ; 4.   a .lf record with 0 aux
            ; 5+6. a .ef record with 1 aux

            mov eax,cntSymbols
            inc eax
            mov ias.Sym.TagIndex,eax
            mov ias.Sym.Misc.TotalSize,[rsi].asym.total_size
            mov rdx,[rsi].asym.debuginfo
            mov ias.Sym.FcnAry.Function.PointerToLinenumber,[rdx].debug_info.ln_fileofs
            mov ias.Sym.FcnAry.Function.PointerToNextFunction,[rdx].debug_info.next_proc
            coff_write_aux( &ias, NULL )

            mov type,IMAGE_SYM_TYPE_NULL
            mov ebx,IMAGE_SYM_CLASS_FUNCTION
            coff_write_symbol(".bf", 0, value, section, type, ebx, 1 )

            mov ias.Sym.TagIndex,0
            mov rdx,[rsi].asym.debuginfo
            mov ias.Sym.Misc.LnSz.Linenumber,[rdx].debug_info.start_line
            .if ( [rdx].debug_info.next_proc )
                mov eax,[rdx].debug_info.next_proc
                add eax,2
                mov ias.Sym.FcnAry.Function.PointerToNextFunction,eax
            .else
                mov ias.Sym.FcnAry.Function.PointerToNextFunction,0
            .endif
            coff_write_aux( &ias, NULL )

            mov rdx,[rsi].asym.debuginfo
            mov value,[rdx].debug_info.line_numbers
            coff_write_symbol( ".lf", 0, value, section, type, ebx, 0 )

            mov eax,[rsi].asym.offs
            add eax,[rsi].asym.total_size
            mov value,eax
            coff_write_symbol( ".ef", 0, value, section, type, ebx, 1 )

            mov ias.Sym.TagIndex,0
            mov rdx,[rsi].asym.debuginfo
            mov ias.Sym.Misc.LnSz.Linenumber,[rdx].debug_info.end_line
            coff_write_aux( &ias, NULL )
            add cntSymbols,6
        .endif
    .endf

    ; aliases. A weak external entry with 1 aux entry is created.

    .for ( rdi = AliasTable : rdi : rdi = [rdi].asym.next )

        mov edx,Mangle( rdi, &buffer )
        lea rcx,buffer
        .if ( edx > IMAGE_SIZEOF_SHORT_NAME )
            mov strpos,Coff_AllocString( cm, rcx, edx )
            xor ecx,ecx
        .endif
        coff_write_symbol( rcx, strpos, 0, IMAGE_SYM_UNDEFINED,
                IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_WEAK_EXTERNAL, 1 )
        inc cntSymbols

        tmemset( &ias, 0, sizeof(ias) )

        ;; v2.04b: adjusted to new field <substitute>

        mov rdx,[rdi].asym.substitute
        .if ( rdx )
            mov ias.Sym.TagIndex,[rdx].asym.ext_idx
        .endif
        mov ias.Sym.Misc.TotalSize,IMAGE_WEAK_EXTERN_SEARCH_ALIAS
        coff_write_aux( &ias, NULL )
        inc cntSymbols
    .endf
    .return( cntSymbols )

coff_write_symbols endp


; callback to flush contents of codeview symbolic debug info sections

    assume rsi:segment_t

coff_flushfunc proc __ccall uses rsi rdi rbx s:asym_t, curr:ptr uint_8, size:dword, pv:ptr

    ldr rdi,s
    mov rsi,[rdi].asym.seginfo
    ldr rbx,curr
    sub rbx,[rsi].CodeBuffer
    ldr eax,size
    add eax,ebx

    .if ( eax > SIZE_CV_SEGBUF )

        .if ( ebx )

            LclAlloc( &[rbx + sizeof( qditem )] )
            mov [rax].qditem.size,ebx
            mov rdx,rsi
            mov rcx,rbx
            lea rdi,[rax+sizeof( qditem )]
            mov rsi,[rsi].CodeBuffer
            rep movsb
            mov rsi,rdx

            mov rdx,pv
            lea rcx,[rdx].coffmod.SymDeb[dbg_section]
            mov rdi,[rcx].dbg_section.s
            .if rdi != s
                sub rcx,sizeof( dbg_section )
            .endif

            .if ( [rcx].dbg_section.q.head == NULL )
                mov [rcx].dbg_section.q.head,rax
                mov [rcx].dbg_section.q.tail,rax
            .else
                mov rdx,[rcx].dbg_section.q.tail
                mov [rdx].qditem.next,rax
                mov [rcx].dbg_section.q.tail,rax
            .endif
            mov eax,[rsi].start_loc
            add eax,ebx
            mov [rsi].current_loc,eax
            mov [rsi].start_loc,eax
        .endif
        .return( [rsi].CodeBuffer )
    .endif
    .return( curr )

coff_flushfunc endp

    assume rsi:nothing


; calc the current number of entries in the symbol table
; so we know the index if a new entry has to be added
; called by coff_write_data()

SetSymbolIndices proc __ccall uses rsi rdi rbx cm:ptr coffmod

  local index:uint_32
  local lastfproc:asym_t
  local lastfile:dword

    xor esi,esi
    ldr rbx,cm

    mov lastfile,esi
    mov [rbx].lastproc,rsi
    mov [rbx].start_files,esi ;; v2.11: added

if COMPID
    .if ( Options.debug_symbols == 4 )
        inc esi
    .endif
endif
    ; add absolute symbol @@feat.00 if -SAFESEH is set
    .if ( Options.safeseh )
        inc esi
    .endif

    ; count AUX entries for .file. Depends on sizeof filename

    .if ( Options.no_file_entry == FALSE )

        tstrlen( [rbx].dot_file_value )
        cdq
        mov ecx,IMAGE_AUX_SYMBOL
        div ecx
        inc eax
        .if edx
            inc eax
        .endif
        add esi,eax
    .endif

    ; add entries for sections

    mov [rbx].sectionstart,esi
    add esi,MODULE.num_segs
    .if ( Options.no_section_aux_entry == FALSE )
        add esi,MODULE.num_segs
    .endif

    ; count externals and protos

    .for ( rdi = ExtTable : rdi : rdi = [rdi].asym.next )

        .continue .if ( !( [rdi].asym.iscomm ) && [rdi].asym.weak )

        mov [rdi].asym.ext_idx,esi
        inc esi

        ; weak externals need an additional aux entry

        .if ( !( [rdi].asym.iscomm ) && [rdi].asym.altname )

            inc esi
        .endif
    .endf

    mov index,esi

if STATIC_PROCS

    ; v2.04: count private procedures (will become static symbols)

    .if ( Options.no_static_procs == FALSE )

        .for( rdi = ProcTable : rdi : rdi = [rdi].asym.nextproc )

            .if ( [rdi].asym.state == SYM_INTERNAL &&
                  !( [rdi].asym.ispublic ) &&
                  !( [rdi].asym.included ) )

                mov [rdi].asym.included,1
                AddPublicData( rdi )
            .endif
        .endf
    .endif
endif

    ; count items in public queue

    .for ( rdi = MODULE.PubQueue.head: rdi: rdi = [rdi].qnode.next )

        mov rsi,[rdi].qnode.sym

        ; if line numbers are on, co, add 6 entries for procs

        .if ( Options.line_numbers && [rsi].asym.isproc && Options.debug_symbols != 4 )

            mov rdx,[rsi].asym.debuginfo
            mov rbx,cm

            .if (  [rdx].debug_info.file != lastfile )
                .if ( [rbx].start_files == 0 )
                    mov [rbx].start_files,index
                .else
                    mov rcx,lastfproc
                    mov rcx,[rcx].asym.debuginfo
                    mov [rcx].debug_info.next_file,index
                .endif
                mov lastfproc,rsi
                mov rcx,[rsi].asym.debuginfo
                inc GetFileAuxEntries( [rcx].debug_info.file, NULL )
                add index,eax
                mov rdx,[rsi].asym.debuginfo
                mov lastfile,[rdx].debug_info.file
            .endif
            mov [rsi].asym.ext_idx,index
            add index,7
        .else
            mov [rsi].asym.ext_idx,index
            inc index
        .endif
    .endf
    .return( index )

SetSymbolIndices endp


; write fixups for a section.

coff_write_fixup proc __ccall uses rsi rdi adr:uint_32, index:uint_32, type:uint_16

  local ir:IMAGE_RELOCATION

    mov ir.VirtualAddress,adr
    mov ir.SymbolTableIndex,index
    mov ir.Type,type

    .ifd ( fwrite( &ir, 1, sizeof(ir), CurrFile[OBJ*string_t] ) != sizeof(ir) )
        WriteError()
    .endif
    ret

coff_write_fixup endp


coff_write_fixups proc __ccall uses rsi rdi rbx section:asym_t, poffset:ptr uint_32, pindex:ptr uint_32

   .new offs:uint_32
   .new type:uint_16

    ldr rdx,poffset
    mov eax,[rdx]
    mov offs,eax
    ldr rdx,pindex
    mov esi,[rdx]
    ldr rcx,section
    mov rdi,[rcx].asym.seginfo

    ; v2.10: handle the reloc-overflow-case

    .if ( [rdi].seg_info.num_relocs > 0xffff )

        mov ecx,[rdi].seg_info.num_relocs
        inc ecx
        coff_write_fixup( ecx, 0, IMAGE_REL_I386_ABSOLUTE ) ; doesn't matter if 32- or 64-bit
        add offs,sizeof( IMAGE_RELOCATION )
    .endif

    assume rbx:ptr fixup

    mov [rdi].seg_info.num_relocs,0 ; reset counter

    .for ( rbx = [rdi].seg_info.head: rbx: rbx = [rbx].nextrlc )

        movzx eax,[rbx].type
        xor ecx,ecx

        .if ( [rdi].seg_info.Ofssize == USE64 )

            .switch eax
            .case FIX_VOID
                .continue
            .case FIX_RELOFF32  ; 32bit offset
                ; translated to IMAGE_REL_AMD64_REL32_[1|2|3|4|5]
                movzx ecx,[rbx].addbytes
                sub ecx,4
                add ecx,IMAGE_REL_AMD64_REL32
                .endc
            .case FIX_OFF32     ; 32bit offset
                mov ecx,IMAGE_REL_AMD64_ADDR32
                .endc
            .case FIX_OFF32_IMGREL
                mov ecx,IMAGE_REL_AMD64_ADDR32NB
                .endc
            .case FIX_OFF32_SECREL
                mov ecx,IMAGE_REL_AMD64_SECREL
                .endc
            .case FIX_OFF64     ; 64bit offset
                mov ecx,IMAGE_REL_AMD64_ADDR64
                .endc
            .case FIX_SEG       ; segment fixup
                mov ecx,IMAGE_REL_AMD64_SECTION ;; ???
                .endc
            .endsw

        .else

            .switch eax
            .case FIX_VOID
                .continue
            .case FIX_RELOFF16  ; 16bit offset
                mov ecx,IMAGE_REL_I386_REL16
                .endc
            .case FIX_OFF16     ; 16bit offset
                mov ecx,IMAGE_REL_I386_DIR16
                .endc
            .case FIX_RELOFF32  ; 32bit offset
                mov ecx,IMAGE_REL_I386_REL32
                .endc
            .case FIX_OFF32     ; 32bit offset
                mov ecx,IMAGE_REL_I386_DIR32
                .endc
            .case FIX_OFF32_IMGREL
                mov ecx,IMAGE_REL_I386_DIR32NB
                .endc
            .case FIX_OFF32_SECREL
                mov ecx,IMAGE_REL_I386_SECREL
                .endc
            .case FIX_SEG       ; segment fixup
                mov ecx,IMAGE_REL_I386_SECTION ;; ???
                .endc
            .endsw

        .endif

        .if ( !ecx ) ; v2.03: skip this fixup

            mov rcx,section
            asmerr( 3014, [rbx].type, [rcx].asym.name, [rbx].locofs )
            .continue
        .endif

        mov type,cx
        mov rcx,[rbx].sym

        .if ( [rcx].asym.isvariable )

            ; just use the segment entry. This approach requires
            ; that the offset is stored inline at the reloc location
            ; (patch in fixup.c)

            mov [rbx].sym,[rbx].segment_var
            mov rcx,rax

        .elseif ( ( [rcx].asym.state == SYM_INTERNAL ) &&
                   !( [rcx].asym.ispublic ) &&
                   !( [rcx].asym.included ) )

            mov [rcx].asym.included,1
            AddPublicData( rcx )
            mov rcx,[rbx].sym
            mov [rcx].asym.ext_idx,esi
            inc esi
            .if ( Options.line_numbers && [rcx].asym.isproc && Options.debug_symbols != 4 )
                add esi,6
            .endif
        .endif

        coff_write_fixup( [rbx].locofs, [rcx].asym.ext_idx, type )

        add offs,sizeof( IMAGE_RELOCATION )
        inc [rdi].seg_info.num_relocs

    .endf

    mov rdx,poffset
    mov [rdx],offs
    mov rdx,pindex
    mov [rdx],esi
    ret

coff_write_fixups endp


; write section data

coff_write_data proc __ccall uses rsi rdi rbx cm:ptr coffmod

  .new section:asym_t
  .new offs:uint_32 = 0 ; offset within section contents
  .new i:int_t
  .new index:uint_32

    ; calc the current index for the COFF symbol table
    mov index,SetSymbolIndices( cm )

    ; fill the SafeSEH array

    assume rbx:ptr coffmod

    mov rbx,cm

    .if ( MODULE.SafeSEHQueue.head )

        mov rax,[rbx].sxdata
        mov rax,[rax].asym.seginfo

        .for ( rdx = MODULE.SafeSEHQueue.head, rcx = [rax].seg_info.CodeBuffer : rdx : rcx += 4 )

            mov rax,[rdx].qnode.elmt
            mov eax,[rax].asym.ext_idx
            mov [rcx],eax
            mov rdx,[rdx].qnode.next
        .endf
    .endif

    .for ( ecx = 0, rdi = SegTable : rdi : ecx++, rdi = [rdi].asym.next )

        mov eax,[rbx].sectionstart
        add eax,ecx
        mov [rdi].asym.ext_idx,eax
        .if ( Options.no_section_aux_entry == FALSE )
            add [rdi].asym.ext_idx,ecx
        .endif
    .endf

    ; now scan the section's relocations. If a relocation refers to
    ; a symbol which is not public/external, it must be added to the
    ; symbol table. If the symbol is an assembly time variable, a helper
    ; symbol - name is $$<offset:6> is to be added.

    assume rsi:segment_t
    .for ( rdi = SegTable: rdi : rdi = [rdi].asym.next )

        mov ebx,[rdi].asym.max_offset
        mov rsi,[rdi].asym.seginfo

        ; don't write section data for bss and uninitialized stack segments

        .continue .if ( [rsi].combine == COMB_STACK && [rsi].bytes_written == 0 )
        .continue .if ( [rsi].segtype == SEGTYPE_BSS )
ifdef _LIN64
        .new _rsi:ptr = rsi
        .new _rdi:ptr = rdi
endif
        .if ( ebx )
            add offs,ebx
            .if ( ( offs & 1 ) && [rsi].head )
                inc offs
                inc ebx
            .endif

            .if ( [rsi].CodeBuffer == NULL )
                fseek( CurrFile[OBJ*string_t], ebx, SEEK_CUR )
            .else

                ; if there was an ORG, the buffer content will
                ; start with the ORG address. The bytes from
                ; 0 - ORG must be written by moving the file pointer!

                mov eax,[rsi].start_loc
                .if ( eax )

                    ; v2.19: write null bytes instead of fseek()

                    ;fseek( CurrFile[OBJ*string_t], [rsi].start_loc, SEEK_CUR )

                    .new nullbyt:char_t = NULLC
                    .for ( i = eax : i : i-- )
                        fwrite( &nullbyt, 1, 1, CurrFile[OBJ*string_t] )
                    .endf
ifdef _LIN64
                    mov rsi,_rsi
endif
                    sub ebx,[rsi].start_loc
                .endif
                mov rax,[rsi].CodeBuffer
                .if ( fwrite( rax, 1, ebx, CurrFile[OBJ*string_t] ) != rbx )
                    WriteError()
                .endif
            .endif
ifdef _LIN64
            mov rsi,_rsi
            mov rdi,_rdi
endif
            coff_write_fixups( rdi, &offs, &index )
        .endif

        mov rbx,cm

        ; v2.07: the following block has beem moved outside of "if(size)" block,
        ; because it may happen that a segment has size 0 and still debug info.
        ; In any case it's important to initialize section->e.seginfo->num_linnums

        ; write line number data. The peculiarity of COFF (compared to OMF) is
        ; that line numbers are always relative to a function start.
        ;
        ; an item with line number 0 has a special meaning - it contains a reference
        ; ( a symbol table index ) to the function whose line numbers are to follow.
        ; this item is to be followed by an item with line number 32767, which then
        ; tells the function's start offset ( undocumented! ).
        ;

        .if ( Options.line_numbers && [rsi].LinnumQueue && Options.debug_symbols != 4 )

            .new il:IMAGE_LINENUMBER
            .new last:asym_t
            .new line_numbers:uint_32 = 0

            mov rax,[rsi].LinnumQueue
            assume rsi:ptr line_num_info

            mov last,NULL
            mov rsi,[rax].qdesc.head

            .for ( : rsi: rsi = [rsi].next )

                .if ( [rsi].number == 0 )

                    mov last,[rsi].sym

                    .if ( [rbx].lastproc )

                        mov rcx,[rbx].lastproc
                        mov rcx,[rcx].asym.debuginfo
                        mov edx,[rax].asym.ext_idx
                        mov [rcx].debug_info.next_proc,edx
                    .endif

                    mov [rbx].lastproc,rax
                    mov rcx,[rax].asym.debuginfo
                    mov [rcx].debug_info.next_proc,0
                    mov il.Linenumber,0
                    mov il.Type.SymbolTableIndex,[rax].asym.ext_idx
                    mov [rcx].debug_info.start_line,[rsi].line_number
                    mov eax,[rbx].start_data
                    add eax,offs
                    mov [rcx].debug_info.ln_fileofs,eax

                .else

                    mov rcx,last
                    mov rcx,[rcx].asym.debuginfo
                    mov eax,[rsi].number
                    sub eax,[rcx].debug_info.start_line
                    mov il.Linenumber,ax

                    ; if current line number - start line number is 0,
                    ; generate a "32767" line number item.

                    .if ( il.Linenumber == 0 )
                        mov il.Linenumber,0x7FFF
                    .endif
                    mov il.Type.VirtualAddress,[rsi].offs
                .endif

                mov rcx,last
                mov rcx,[rcx].asym.debuginfo
                inc [rcx].debug_info.line_numbers
                mov [rcx].debug_info.end_line,[rsi].number

ifdef _LIN64
                mov _rsi,rsi
                mov _rdi,rdi
endif
                .ifd ( fwrite( &il, 1, sizeof(il), CurrFile[OBJ*string_t] ) != sizeof(il) )
                    WriteError()
                .endif
ifdef _LIN64
                mov rsi,_rsi
                mov rdi,_rdi
endif
                add offs,sizeof(il)
                inc line_numbers
            .endf

            mov rdx,[rdi].asym.seginfo
            mov [rdx].seg_info.num_linnums,line_numbers
        .endif

    .endf

    mov rbx,cm
    mov [rbx].size_data,offs
   .return( NOT_ERROR )

coff_write_data endp


;
; check if a .drectve section has to be created.
; if yes, create it and set its contents.
;

coff_create_drectve proc __ccall uses rsi rdi rbx cm:ptr coffmod

  .new exp:asym_t
  .new imp:asym_t = NULL
  .new buffer[MAX_ID_LEN+MANGLE_BYTES+1]:char_t

    ; does a proc exist with the EXPORT attribute?

    .for ( rdi = MODULE.PubQueue.head : rdi : rdi = [rdi].qnode.next )

        mov rcx,[rdi].qnode.sym
        .break .if ( [rcx].asym.isexport )
    .endf
    mov exp,rdi

    ; check if an impdef record is there

    .if ( Options.write_impdef && !Options.names[OPTN_LNKDEF_FN*string_t] )

        .for ( rdi = ExtTable: rdi: rdi = [rdi].asym.next )

            .if ( [rdi].asym.isproc &&
                 ( !( [rdi].asym.weak ) || [rdi].asym.iat_used ) )

                mov rdx,[rdi].asym.dll
                .if ( rdx )
                    .break .if [rdx].dll_desc.name
                .endif
            .endif
        .endf
        mov imp,rdi
    .endif

    ; add a .drectve section if
    ; - a start_label is defined    and/or
    ; - a library is included       and/or
    ; - a proc is exported          and/or
    ; - impdefs are to be written (-Zd)

    .if ( MODULE.start_label != NULL ||
          MODULE.LibQueue.head != NULL ||
          imp != NULL || exp != NULL || MODULE.LinkQueue.head != NULL )

         mov rbx,cm
         mov [rbx].directives,CreateIntSegment( szdrectve, "", MAX_SEGALIGNMENT, MODULE.Ofssize, FALSE )

        .if ( rax )

            xor ebx,ebx
            mov rdi,[rax].asym.seginfo
            mov [rdi].seg_info.information,1

            ; calc the size for this segment

            ; 1. exports

            .for ( rdi = exp : rdi : rdi = [rdi].qnode.next )

                mov rcx,[rdi].qnode.sym
                .if ( [rcx].asym.isexport )

                    Mangle( rcx, &buffer )
                    lea rbx,[rbx+rax+9]
                    .if ( Options.no_export_decoration == TRUE )

                        mov rcx,[rdi].qnode.sym
                        add ebx,[rcx].asym.name_size
                        inc ebx
                    .endif
                .endif
            .endf

            ; 2. defaultlibs

            .for ( rdi = MODULE.LibQueue.head : rdi : rdi = [rdi].qitem.next )

                tstrlen( &[rdi].qitem.value ) ; sizeof("-defaultlib:")
                lea rbx,[rbx+rax+13]

                ; if the name isn't enclosed in double quotes and contains
                ; a space, add 2 bytes to enclose it

                .if ( [rdi].qitem.value != '"' )
                    .if ( tstrchr( &[rdi].qitem.value, ' ') )
                        add rbx,2
                    .endif
                .endif
            .endf

            ; 3. start label

            add ebx,GetStartLabel( &buffer, TRUE )

            ; 4. impdefs

            .for ( rdi = imp : rdi : rdi = [rdi].asym.next )

                .if ( [rdi].asym.isproc &&
                     ( !( [rdi].asym.weak ) || [rdi].asym.iat_used ) &&
                      [rdi].asym.dll )

                    mov rdx,[rdi].asym.dll
                    .if ( [rdx].dll_desc.name )

                        ; format is:
                        ; "-import:<mangled_name>=<module_name>.<unmangled_name>" or
                        ; "-import:<mangled_name>=<module_name>"

                        tstrlen( &[rdx].dll_desc.name )
                        lea rbx,[rbx+rax+9+1]
                        add ebx,Mangle( rdi, &buffer )
                        add ebx,[rdi].asym.name_size
                        inc ebx
                    .endif
                .endif
            .endf

            ; 5. pragma comment(linker,"/..")

            .for ( rdi = MODULE.LinkQueue.head: rdi: rdi = [rdi].qitem.next )

                tstrlen( &[rdi].qitem.value )
                lea rbx,[rbx+rax+1]
            .endf

            mov ecx,ebx
            mov rbx,cm
            mov rdx,[rbx].directives
            mov [rdx].asym.max_offset,ecx
            mov rdi,[rdx].asym.seginfo
            inc ecx
            mov [rdi].seg_info.CodeBuffer,LclAlloc( ecx )
            mov rbx,rax

            assume rbx:nothing

            ; copy the data

            ; 1. exports

            .for ( rdi = exp : rdi : rdi = [rdi].qnode.next )

                mov rcx,[rdi].qnode.sym
                .if ( [rcx].asym.isexport )

                    Mangle( rcx, &buffer )
                    .if ( Options.no_export_decoration == FALSE )
                        add rbx,tsprintf( rbx, "-export:%s ", &buffer )
                    .else
                        mov rcx,[rdi].qnode.sym
                        add rbx,tsprintf( rbx, "-export:%s=%s ", [rcx].asym.name, &buffer )
                    .endif
                .endif
            .endf

            ; 2. libraries

            .for ( rdi = MODULE.LibQueue.head : rdi : rdi = [rdi].qitem.next )

                .if ( tstrchr( &[rdi].qitem.value, ' ') && [rdi].qitem.value != '"' )
                    add rbx,tsprintf( rbx, "-defaultlib:\"%s\" ", &[rdi].qitem.value )
                .else
                    add rbx,tsprintf( rbx, "-defaultlib:%s ", &[rdi].qitem.value )
                .endif
            .endf

            ; 3. entry

            .if ( MODULE.start_label )

                GetStartLabel( &buffer, FALSE )
                add rbx,tsprintf( rbx, "-entry:%s ", &buffer )
            .endif

            ; 4. impdefs

            .for ( rdi = imp : rdi : rdi = [rdi].asym.next )

                .if ( [rdi].asym.isproc &&
                     ( !( [rdi].asym.weak ) || [rdi].asym.iat_used ) && [rdi].asym.dll )

                    mov rdx,[rdi].asym.dll
                    .if ( [rdx].dll_desc.name )

                        tstrcpy( rbx, "-import:" )
                        add rbx,8
                        add rbx,Mangle( rdi, rbx )
                        mov byte ptr [rbx],'='
                        inc rbx
                        mov rcx,[rdi].asym.dll
                        tstrcpy( rbx, &[rcx].dll_desc.name )
                        add rbx,tstrlen( rbx )
                        mov byte ptr [rbx],'.'
                        inc rbx
                        tmemcpy( rbx, [rdi].asym.name, [rdi].asym.name_size )
                        mov edx,[rdi].asym.name_size
                        add rbx,rdx
                        mov byte ptr [rbx],' '
                        inc rbx
                    .endif
                .endif
            .endf

            ; 5. pragma comment(linker,"/..")

            .for ( rdi = MODULE.LinkQueue.head : rdi : rdi = [rdi].qitem.next )

                add rbx,tsprintf( rbx, "%s ", &[rdi].qitem.value )
            .endf
        .endif
    .endif
    ret

coff_create_drectve endp

    assume rsi:nothing

;
; Write current object module in COFF format.
; This function is called AFTER all assembly passes have been done.
;
coff_write_module proc uses rsi rdi rbx

  local cm:coffmod
  local ifh:IMAGE_FILE_HEADER

    tmemset( &cm, 0, sizeof( cm ) )
    mov cm.size,sizeof( uint_32 )

    ; get value for .file symbol
    mov cm.dot_file_value,CurrFName[ASM*string_t]

    ; it might be necessary to add "internal" sections:
    ; - .debug$S and .debug$T sections if -Zi was set
    ; - .sxdata section if .SAFESEH was used
    ; - .drectve section if start label, exports or includelibs are used

    ; if -Zi is set, add .debug$S and .debug$T sections

    .if ( Options.debug_symbols )

        .for ( ebx = 0 : ebx < DBGS_MAX : ebx++ )

            imul edi,ebx,dbg_section
            lea rcx,SymDebName

            mov cm.SymDeb[rdi].s,CreateIntSegment( [rcx+rbx*string_t], "", 0, USE32, TRUE )
           .break .if ( eax == NULL )

            mov rcx,[rax].asym.seginfo
            mov [rcx].seg_info.characteristics,( IMAGE_SCN_MEM_READ or IMAGE_SCN_MEM_DISCARDABLE ) shr 24

            ; use the source line buffer as code buffer. It isn't needed anymore

            imul eax,ebx,SIZE_CV_SEGBUF
            add rax,CurrSource

            mov [rcx].seg_info.CodeBuffer,rax
            mov [rcx].seg_info.flushfunc,&coff_flushfunc
            mov cm.SymDeb[rdi].q.head,NULL
        .endf

        .if ( ebx == DBGS_MAX )

            cv_write_debug_tables( cm.SymDeb[DBGS_SYMBOLS*dbg_section].s,
                    cm.SymDeb[DBGS_TYPES*dbg_section].s, &cm )

            ; the contents have been written in queues. now
            ; copy all queue items in ONE buffer.

            .for ( ebx = 0 : ebx < DBGS_MAX : ebx++ )

                imul edi,ebx,dbg_section

                mov rcx,cm.SymDeb[rdi].s
                mov rsi,[rcx].asym.seginfo

                .if ( [rcx].asym.max_offset )
                    .if ( [rcx].asym.max_offset > SIZE_CV_SEGBUF )
                        mov [rsi].seg_info.CodeBuffer,LclAlloc( [rcx].asym.max_offset )
                    .endif
                    mov rdx,[rsi].seg_info.CodeBuffer
                    mov rsi,cm.SymDeb[rdi].q.head

                    .for ( rdi = rdx: rsi: rsi = [rsi].qditem.next )
                        mov ecx,[rsi].qditem.size
                        lea rdx,[rsi+qditem]
                        xchg rsi,rdx
                        rep movsb
                        mov rsi,rdx
                    .endf
                .endif
            .endf
        .endif
    .endif

    ;; if safeSEH procs are defined, add a .sxdata section

    .if ( MODULE.SafeSEHQueue.head )

        mov cm.sxdata,CreateIntSegment( ".sxdata", "", MAX_SEGALIGNMENT, MODULE.Ofssize, FALSE )

        .if ( rax )

            mov rdi,[rax].asym.seginfo
            mov [rdi].seg_info.information,1

            ; calc the size for this segment

            .for ( rdx = MODULE.SafeSEHQueue.head, ecx = 0 : rdx : rdx = [rdx].qnode.next, ecx++ )
            .endf
            shl ecx,2
            mov rdx,cm.sxdata
            mov [rdx].asym.max_offset,ecx
            mov [rdi].seg_info.CodeBuffer,LclAlloc( ecx )
        .endif
    .endif

    ; create .drectve section if necessary

    coff_create_drectve( &cm )

    .if ( MODULE.defOfssize == USE64 )
        mov ifh.Machine,IMAGE_FILE_MACHINE_AMD64
    .else
        mov ifh.Machine,IMAGE_FILE_MACHINE_I386
    .endif
    mov ifh.NumberOfSections,MODULE.num_segs
    time(&ifh.TimeDateStamp)
    mov ifh.SizeOfOptionalHeader,0
    mov ifh.Characteristics,0

    ; position behind coff file header

    fseek( CurrFile[OBJ*string_t], sizeof( ifh ), SEEK_SET )
    coff_write_section_table( &cm )
    coff_write_data( &cm )
    mov ifh.NumberOfSymbols,coff_write_symbols( &cm )
    xor eax,eax
    .if ( ifh.NumberOfSymbols )
        mov eax,cm.start_data
        add eax,cm.size_data
    .endif
    mov ifh.PointerToSymbolTable,eax

    .ifd ( fwrite( &cm.size, 1, sizeof( cm.size ),
            CurrFile[OBJ*size_t] ) != sizeof( cm.size ) )
        WriteError()
    .endif

    assume rbx:ptr stringitem
    .for ( rbx = cm.head : rbx : rbx = [rbx].next )
        inc tstrlen( &[rbx].string )
ifdef _LIN64
        .new len:int_t = eax
        fwrite( &[rbx].string, 1, len, CurrFile[OBJ*string_t] )
        .if ( eax != len )
else
        mov edi,eax
        .if ( fwrite( &[rbx].string, 1, edi, CurrFile[OBJ*string_t] ) != rdi )
endif
            WriteError()
        .endif
    .endf

    ; finally write the COFF file header

    fseek( CurrFile[OBJ*string_t], 0, SEEK_SET )
    .ifd ( fwrite( &ifh, 1, sizeof( ifh ), CurrFile[OBJ*string_t] ) != sizeof( ifh ) )
        WriteError()
    .endif
    .return( NOT_ERROR )

coff_write_module endp


coff_init proc public

    mov MODULE.WriteModule,&coff_write_module
    ret

coff_init endp

    end
