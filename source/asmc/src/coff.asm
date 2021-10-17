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

define MANGLE_BYTES 8 ;; extra size required for name decoration
;; v2.04: to make JWasm always add static (=private) procs to the symbol table
;; set STATIC_PROCS to 1. Normally those procs are only added if line
;; number/symbolic debugging information is generated.
;;
define STATIC_PROCS 1 ;; v2.10: changed to 1, because Masm 6-10 DOES add static procs
define COMPID       0 ;; 1=add comp.id absolute symbol
;; size of codeview temp segment buffer; prior to v2.12 it was 1024 - but this may be
;; insufficient if MAX_ID_LEN has been enlarged.
;;

.template stringitem
    next ptr stringitem ?
    string db 1 dup(?)
   .ends

cv_write_debug_tables proto :ptr dsym, :ptr dsym, :ptr

;; v2.10: COMDAT CRC calculation ( suggestion by drizz, slightly modified )

.data?
CRC32Table uint_32 256 dup(?) ; table is initialized if needed

.data

CRC32_Init  uint_32 FALSE

;; -Zi option section info
SymDebName string_t \
 @CStr( ".debug$S" ),
 @CStr( ".debug$T" )

szdrectve equ <".drectve">

    .code

    option proc:private

;; alloc a string which will be stored in the COFF string table

    assume ebx:ptr coffmod

Coff_AllocString proc uses esi edi ebx cm:ptr coffmod, string:string_t, len:int_t

    mov ebx,cm
    mov edi,[ebx].size
    mov eax,len
    inc eax
    add [ebx].size,eax
    mov esi,LclAlloc( &[eax + sizeof( stringitem ) - 1] )
    mov [esi].stringitem.next,NULL
    strcpy( &[esi].stringitem.string, string )
    .if ( [ebx].head )
        mov edx,[ebx].tail
        mov [edx].stringitem.next,esi
        mov [ebx].tail,esi
    .else
        mov [ebx].head,esi
        mov [ebx].tail,esi
    .endif
    .return( edi )

Coff_AllocString endp

;; return number of line number items

GetLinnumItems proc fastcall q:ptr qdesc

    .for ( eax = 0,
           edx = [ecx].qdesc.head: edx: eax++, edx = [edx].line_num_info.next )
    .endf
    ret

GetLinnumItems endp

;; write COFF section table

    assume esi:ptr module_info

coff_write_section_table proc uses esi edi ebx modinfo:ptr module_info, cm:ptr coffmod

  local segtype:dword
  local ish:IMAGE_SECTION_HEADER
  local buffer[MAX_ID_LEN+1]:char_t

    ;; calculated file offset for section data, relocs and linenumber info

    mov  esi,modinfo
    imul esi,[esi].num_segs,sizeof( IMAGE_SECTION_HEADER )
    add  esi,sizeof( IMAGE_FILE_HEADER )

    mov ebx,cm
    mov [ebx].start_data,esi

    .for ( edi = SegTable: edi: edi = [edi].dsym.next )

        mov segtype,SEGTYPE_UNDEF

        ;; v2.07: prefer ALIAS name if defined.
        mov edx,[edi].dsym.seginfo
        mov eax,[edx].seg_info.aliasname
        .if ( eax == NULL )

            ConvertSectionName( edi, &segtype, &buffer )
        .endif
        mov ebx,eax

        ;; if section name is longer than 8 chars, a '/' is stored,
        ;; followed by a number in ascii which is the offset for the string table

        .if ( strlen( eax ) <= IMAGE_SIZEOF_SHORT_NAME )
            strncpy( &ish.Name, ebx, IMAGE_SIZEOF_SHORT_NAME )
        .else
            tsprintf( &ish.Name, "/%u", Coff_AllocString( cm, ebx, eax ) )
        .endif

        mov ish.SizeOfRawData,[edi].asym.max_offset
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

        ;; set field Characteristics; optionally reset PointerToRawData/SizeOfRawData

        mov edx,[edi].dsym.seginfo
        assume edx:ptr seg_info

        .if ( [edx].info )

            ;; v2.09: set "remove" flag for .drectve section, as it was done in v2.06 and earlier
            mov ecx,cm
            .if ( edi == [ecx].coffmod.directives )
                mov ish.Characteristics, ( IMAGE_SCN_LNK_INFO or IMAGE_SCN_LNK_REMOVE )
            .else
                mov ish.Characteristics, ( IMAGE_SCN_LNK_INFO or IMAGE_SCN_CNT_INITIALIZED_DATA )
            .endif

        .else

            .if ( [edx].alignment != MAX_SEGALIGNMENT ) ;; ABS not possible

                movzx eax,[edx].alignment
                inc eax
                shl eax,20
                or ish.Characteristics,eax
            .endif

            .if ( [edx].comdatselection )

                or ish.Characteristics,IMAGE_SCN_LNK_COMDAT
            .endif

            xor ecx,ecx
            .if [edx].clsym

                mov eax,[edx].clsym
                mov eax,[eax].asym.name

                .if dword ptr [eax] == 'SNOC' && word ptr [eax+4] == 'T'

                    inc ecx
                .endif
            .endif

            .if ( [edx].segtype == SEGTYPE_CODE )
                or ish.Characteristics,IMAGE_SCN_CNT_CODE or IMAGE_SCN_MEM_EXECUTE or IMAGE_SCN_MEM_READ
            .elseif ( [edx].readonly )
                or ish.Characteristics,IMAGE_SCN_CNT_INITIALIZED_DATA or IMAGE_SCN_MEM_READ
            .elseif ( ecx )
                or ish.Characteristics,IMAGE_SCN_CNT_INITIALIZED_DATA or IMAGE_SCN_MEM_READ
            .elseif ( [edx].segtype == SEGTYPE_BSS || segtype == SEGTYPE_BSS )

                ;; v2.12: if segtype is bss, ensure that seginfo->segtype is also bss; else
                ;; the segment might be written in coff_write_data().

                mov [edx].segtype,SEGTYPE_BSS
                or  ish.Characteristics,IMAGE_SCN_CNT_UNINITIALIZED_DATA or IMAGE_SCN_MEM_READ or IMAGE_SCN_MEM_WRITE
                mov ish.PointerToRawData,0
            .elseif ( [edx].combine == COMB_STACK && [edx].bytes_written == 0 )
                or  ish.Characteristics,IMAGE_SCN_CNT_UNINITIALIZED_DATA or IMAGE_SCN_MEM_READ or IMAGE_SCN_MEM_WRITE
                mov ish.SizeOfRawData,0
                mov ish.PointerToRawData,0
            .else
                or ish.Characteristics,IMAGE_SCN_CNT_INITIALIZED_DATA or IMAGE_SCN_MEM_READ or IMAGE_SCN_MEM_WRITE
            .endif
        .endif

        ;; manual characteristics set?

        .if ( [edx].characteristics )

            and ish.Characteristics,0x1FFFFFF ;; clear the IMAGE_SCN_MEM flags
            movzx eax,[edx].characteristics
            and eax,0xFE
            shl eax,24
            or ish.Characteristics,eax
        .endif

        .if ( ish.PointerToRawData )

            add esi,ish.SizeOfRawData
        .endif

        ;; set fields PointerToRelocations/NumberOfRelocations; update 'fileoffset'.
        ;; v2.10: don't use the 16-bit NumberOfRelocations member to count relocs!
        ;; if the true number of relocs doesn't fit in 16-bits, set the appropriate
        ;; flag in the section header!

        assume ecx:ptr fixup

        mov ecx,[edx].head
        .if ( ecx )

            .for ( : ecx : ecx = [ecx].nextrlc )

                .if ( [ecx].sym == NULL )

                    .if ( [ecx].type == FIX_RELOFF32 )

                        mov eax,[ecx].locofs
                        sub eax,[edx].start_loc
                        add eax,[edx].CodeBuffer
                        movzx edx,[ecx].addbytes
                        add edx,[ecx].locofs
                        sub [eax],edx
                        mov edx,[edi].dsym.seginfo
                    .endif
                    mov [ecx].type,FIX_VOID
                    .continue
                .endif
                inc [edx].num_relocs
            .endf

            inc esi
            and esi,not 1
            mov ish.PointerToRelocations,esi

            ;; v2.10: handle the "relocs overflow"-case

            imul eax,[edx].num_relocs,sizeof( IMAGE_RELOCATION )
            add esi,eax

            .if ( [edx].num_relocs <= 0xffff )
                mov eax,[edx].num_relocs
                mov ish.NumberOfRelocations,ax
            .else
                mov ish.NumberOfRelocations,0xffff
                or  ish.Characteristics,IMAGE_SCN_LNK_NRELOC_OVFL

                ;; add 1 relocation - the true number of relocations is stored
                ;; in the first relocation item

                add esi,sizeof( IMAGE_RELOCATION )
            .endif
        .endif

        ;; set fields PointerToLinenumbers/NumberOfLinenumbers; update 'fileoffset'

        .if ( [edx].LinnumQueue && Options.debug_symbols != 4 )

            mov ish.PointerToLinenumbers,esi
            mov ish.NumberOfLinenumbers,GetLinnumItems( [edx].LinnumQueue )
            movzx eax,ish.NumberOfLinenumbers
            imul eax,eax,sizeof( IMAGE_LINENUMBER )
            add esi,eax
        .endif

        .if ( fwrite( &ish, 1, sizeof( ish ), CurrFile[OBJ*4] ) != sizeof( ish ) )
            WriteError()
        .endif
    .endf
    .return( NOT_ERROR )

coff_write_section_table endp


;;
;; get value for field 'type' ( IMAGE_SYM_TYPE_x ) in symbol table.
;; MS tools use only 0x0 or 0x20.
;;
    assume edx:nothing
    assume ecx:ptr asym

CoffGetType proc fastcall sym:ptr asym

    .return( 0x20 ) .if ( [ecx].flag1 & S_ISPROC )
    .return( IMAGE_SYM_TYPE_NULL )

CoffGetType endp

;;
;; get value for field 'class' ( IMAGE_SYM_CLASS_x ) in symbol table.
;;

CoffGetClass proc fastcall sym:ptr asym

    .if ( [ecx].state == SYM_EXTERNAL )
        .if ( !( [ecx].sflags & S_ISCOM ) && [ecx].altname )
            .return( IMAGE_SYM_CLASS_WEAK_EXTERNAL )
        .else
            .return( IMAGE_SYM_CLASS_EXTERNAL )
        .endif
    .elseif ( [ecx].flags & S_ISPUBLIC )
        .return( IMAGE_SYM_CLASS_EXTERNAL )

    ;; v2.09: don't declare private procs as label
    .elseif ( [ecx].mem_type == MT_NEAR && !( [ecx].flag1 & S_ISPROC ) )
        .return( IMAGE_SYM_CLASS_LABEL )
    .endif
    .return( IMAGE_SYM_CLASS_STATIC )

CoffGetClass endp

    assume ecx:nothing
    assume edi:nothing


;;
;; calc number of entries in symbol table for a file entry
;;

GetFileAuxEntries proc file:uint_16, fname:ptr string_t

    GetFName( file )
    .if ( fname )
        mov ecx,fname
        mov [ecx],eax
    .endif
    strlen(eax)
    cdq
    mov ecx,IMAGE_AUX_SYMBOL
    div ecx
    add eax,edx
    mov eax,0
    setnz al
    ret

GetFileAuxEntries endp


CRC32Comdat proc uses ebx lpBuffer:ptr byte, dwBufLen:uint_32, dwCRC:uint_32

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
            mov CRC32Table[ecx*4],eax
        .endf
    .endif

    mov eax,dwCRC
    mov ecx,dwBufLen
    mov ebx,lpBuffer

    .if ( ebx ) ;; v2.11: lpBuffer may be NULL ( uninitialized data segs )
        .for ( edx = 0: ecx: ecx-- )

            mov dl,[ebx]
            inc ebx
            xor dl,al
            shr eax,8
            xor eax,CRC32Table[edx*4]
        .endf
    .endif
    ret

CRC32Comdat endp

;; write COFF symbol table
;; contents of the table
;; - @@feat.00 if .SAFESEH was set
;; - file (+ 1-n aux)
;; - 2 entries per section
;; - externals, communals and publics
;; - entries for relocations (internal)
;; - aliases (weak externals)
;;

coff_write_symbol proc name:string_t, strpos:dword, value:dword,
        section:dword, type:dword, storageclass:dword, aux:dword

  local sym:IMAGE_SYMBOL

    .if ( name )
        strncpy( &sym.N.ShortName, name, IMAGE_SIZEOF_SHORT_NAME )
    .else
        mov sym.N.LongName[0],0
        mov sym.N.LongName[4],strpos
    .endif
    mov sym.Value,value
    mov sym.SectionNumber,section
    mov sym.Type,type
    mov sym.StorageClass,storageclass
    mov sym.NumberOfAuxSymbols,aux
    .if ( fwrite( &sym, 1, sizeof( IMAGE_SYMBOL ), CurrFile[OBJ*4] ) != sizeof( IMAGE_SYMBOL ) )
        WriteError()
    .endif
    ret

coff_write_symbol endp


coff_write_aux proc sym:ptr, name:string_t

    .if ( name )
        strncpy( sym, name, IMAGE_AUX_SYMBOL )
    .endif
    .if ( fwrite( sym, 1, IMAGE_AUX_SYMBOL, CurrFile[OBJ*4] ) != IMAGE_AUX_SYMBOL )
        WriteError()
    .endif
    ret

coff_write_aux endp


GetStartLabel proc uses esi edi modinfo:ptr module_info, buffer:string_t, msg:dword

  local mangle[MAX_ID_LEN + MANGLE_BYTES + 1]:char_t

    mov esi,modinfo
    lea edi,mangle
    xor eax,eax

    .if ( [esi].start_label )

        Mangle( [esi].start_label, edi )

        mov ecx,esi
        mov esi,buffer

        .if ( !Options.entry_decorated )

            mov edx,[ecx].module_info.start_label
            movzx eax,[edx].asym.langtype
            .if ( eax != LANG_C && eax != LANG_STDCALL && eax != LANG_SYSCALL )

                mov edx,[edx].asym.name
                .if ( byte ptr [edx] != '_' )

                    .if ( msg && ( [ecx].module_info.defOfssize != USE64 ) )

                        asmerr( 8011, edx )
                    .endif
                .else
                    inc edi
                .endif
            .else
                inc edi
            .endif
        .endif
        strlen( strcpy( esi, edi ) )
        add eax,8 ; == size of " -entry:"
    .endif
    ret

GetStartLabel endp


coff_write_symbols proc uses esi edi ebx modinfo:ptr module_info, cm:ptr coffmod

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
    ;; write "@comp.id" entry
    .if ( Options.debug_symbols == 4 )
        coff_write_symbol( "@comp.id", 0, 0x01037296, ;; value of Masm v14.00.24210.0
                IMAGE_SYM_ABSOLUTE, IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_STATIC, 0 )
        inc cntSymbols
    .endif
endif
    ;; "@feat.00" entry (for SafeSEH)
    .if ( Options.safeseh )
        mov ecx,1
        .if ( Options.debug_symbols == 4 )
            mov ecx,16
        .endif
        coff_write_symbol( "@feat.00", 0, ecx,
                IMAGE_SYM_ABSOLUTE, IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_STATIC, 0 )
        inc cntSymbols
    .endif

    ;; .file item (optionally disabled by -zlf)

    .if ( Options.no_file_entry == FALSE )

        ;; index of next .file entry
        mov ebx,cm
        mov esi,[ebx].dot_file_value
        strlen( esi )
        mov ecx,sizeof(IMAGE_AUX_SYMBOL)
        cdq
        div ecx
        .if edx
            inc eax
        .endif
        mov aux,eax
        xor ecx,ecx
        .if Options.line_numbers
            mov ecx,[ebx].start_files
        .endif
        coff_write_symbol( ".file", 0, ecx,
                IMAGE_SYM_DEBUG, IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_FILE, aux )
        .for ( edi = aux : edi: edi--, esi += sizeof(IMAGE_AUX_SYMBOL) )
            coff_write_aux( &ias, esi )
        .endf
        mov eax,aux
        inc eax
        add cntSymbols,eax
    .endif

    ;; next are section entries

    .for ( ebx = 1, edi = SegTable: edi: edi = [edi].dsym.next, ebx++ )

        ;; v2.07: prefer ALIAS name if defined

        mov edx,[edi].dsym.seginfo
        mov eax,[edx].seg_info.aliasname
        .if ( eax == NULL )
            ConvertSectionName( edi, NULL, &buffer )
        .endif
        mov esi,eax
        strlen( eax )
        .if ( eax > IMAGE_SIZEOF_SHORT_NAME )
            mov strpos,Coff_AllocString( cm, esi, eax )
            mov esi,NULL
        .endif
        xor ecx,ecx
        .if Options.no_section_aux_entry == FALSE
            inc ecx
        .endif
        coff_write_symbol(esi, strpos, 0, ebx, IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_STATIC, ecx )
        inc cntSymbols

        ;; write the auxiliary symbol record for sections.
        ;; may be suppressed with option -zls.

        mov esi,[edi].dsym.seginfo
        assume esi:ptr seg_info

        .if ( Options.no_section_aux_entry == FALSE || [esi].comdatselection )

            memset( &ias, 0, sizeof(ias) )
            mov ias.Section.Length,[edi].asym.max_offset
            mov eax,[esi].num_relocs
            .if ( eax > 0xffff )
                mov eax,0xffff
            .endif
            mov ias.Section.NumberOfRelocations,ax
            .if ( Options.line_numbers && Options.debug_symbols != 4 )
                mov ias.Section.NumberOfLinenumbers,[esi].num_linnums
            .endif

            ;; CheckSum, Number and Selection are for COMDAT sections only

            .if ( [esi].comdatselection )
                mov ias.Section.CheckSum,CRC32Comdat( [esi].CodeBuffer, [edi].asym.max_offset, 0 )
                mov ias.Section.Number,[esi].comdat_number
                mov ias.Section.Selection,[esi].comdatselection
            .endif
            coff_write_aux( &ias, NULL )
            inc cntSymbols
        .endif

        assume esi:nothing

    .endf

    ;; third are externals + communals ( + protos [since v2.01] )

    .for ( edi = ExtTable : edi != NULL : edi = [edi].dsym.next )

        ;; skip "weak" (=unused) externdefs

        .continue .if ( !( [edi].asym.sflags & S_ISCOM ) && [edi].asym.sflags & S_WEAK )

        lea ebx,buffer
        mov ecx,Mangle( edi, ebx )

        ;; for COMMUNALs, store their size in the Value field

        .if ( [edi].asym.sflags & S_ISCOM )
            mov value,[edi].asym.total_size
        .else
            mov value,[edi].asym.offs ;; is always 0
        .endif

        .if ( ecx > IMAGE_SIZEOF_SHORT_NAME )
            mov strpos,Coff_AllocString( cm, ebx, ecx )
            xor ebx,ebx
        .endif
        mov esi,CoffGetClass( edi )
        mov ecx,CoffGetType( edi )
        xor eax,eax
        .if ( !( [edi].asym.sflags & S_ISCOM ) && [edi].asym.altname )
            inc eax
        .endif
        coff_write_symbol( ebx, strpos, value, IMAGE_SYM_UNDEFINED, ecx, esi, eax )
        inc cntSymbols

        ;; for weak externals, write the auxiliary record
        .if ( !( [edi].asym.sflags & S_ISCOM ) && [edi].asym.altname )

            memset( &ias, 0, sizeof(ias) )
            mov ecx,[edi].asym.altname
            mov ias.Sym.TagIndex,[ecx].asym.ext_idx

            ;; v2.10: weak externals defined via "extern sym (altsym) ..."
            ;; are to have characteristics IMAGE_WEAK_EXTERN_SEARCH_LIBRARY.

            mov ias.Sym.Misc.TotalSize,IMAGE_WEAK_EXTERN_SEARCH_LIBRARY
            coff_write_aux( &ias, NULL )
            inc cntSymbols
        .endif
    .endf

    ;; publics and internal symbols. The internal symbols have
    ;; been written to the "public" queue inside coff_write_data().

    .for ( edi = ModuleInfo.PubQueue.head: edi: edi = [edi].qnode.next )

        mov esi,[edi].qnode.sym
        mov ebx,Mangle( esi, &buffer )
        mov edx,[esi].asym.debuginfo

        .if ( Options.line_numbers && Options.debug_symbols != 4 && \
            [esi].asym.flag1 & S_ISPROC && [edx].debug_info.file != lastfile )

            mov lastfile,[edx].debug_info.file
            mov aux,GetFileAuxEntries( [edx].debug_info.file, &p )
            mov edx,[esi].asym.debuginfo
            coff_write_symbol( ".file", 0, [edx].debug_info.next_file,
                    IMAGE_SYM_DEBUG, IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_FILE, aux )

            .for ( edx = p, eax = aux: eax: eax--, edx += sizeof(IMAGE_AUX_SYMBOL) )
            .endf
            coff_write_aux( &ias, edx )
            mov eax,aux
            inc eax
            add cntSymbols,eax
        .endif

        .if ( [esi].asym.state == SYM_INTERNAL )
            .if ( [esi].asym.segm )
                mov section,GetSegIdx( [esi].asym.segm )
            .else
                mov section,IMAGE_SYM_ABSOLUTE
            .endif
        .else
            mov section,IMAGE_SYM_UNDEFINED
        .endif
        mov aux,0
        .if ( Options.line_numbers && [esi].asym.flag1 & S_ISPROC && Options.debug_symbols != 4 )
            inc aux
        .endif
        mov ecx,ebx
        lea ebx,buffer
        .if ( ecx > IMAGE_SIZEOF_SHORT_NAME )
            mov strpos,Coff_AllocString( cm, ebx, ecx )
            xor ebx,ebx
        .endif
        mov p,ebx
        mov value,[esi].asym.offs
        mov ebx,CoffGetType( esi )
        coff_write_symbol( p, strpos, value, section, ebx, CoffGetClass( esi ), aux )
        inc cntSymbols

        .if ( Options.line_numbers && [esi].asym.flag1 & S_ISPROC && Options.debug_symbols != 4 )

            ;; write:
            ;; 1.   the aux for the proc
            ;; 2+3. a .bf record with 1 aux
            ;; 4.   a .lf record with 0 aux
            ;; 5+6. a .ef record with 1 aux

            mov eax,cntSymbols
            inc eax
            mov ias.Sym.TagIndex,eax
            mov ias.Sym.Misc.TotalSize,[esi].asym.total_size
            mov edx,[esi].asym.debuginfo
            mov ias.Sym.FcnAry.Function.PointerToLinenumber,[edx].debug_info.ln_fileofs
            mov ias.Sym.FcnAry.Function.PointerToNextFunction,[edx].debug_info.next_proc
            coff_write_aux( &ias, NULL )

            mov type,IMAGE_SYM_TYPE_NULL
            mov ebx,IMAGE_SYM_CLASS_FUNCTION
            coff_write_symbol(".bf", 0, value, section, type, ebx, 1 )

            mov ias.Sym.TagIndex,0
            mov edx,[esi].asym.debuginfo
            mov ias.Sym.Misc.LnSz.Linenumber,[edx].debug_info.start_line
            .if ( [edx].debug_info.next_proc )
                mov eax,[edx].debug_info.next_proc
                add eax,2
                mov ias.Sym.FcnAry.Function.PointerToNextFunction,eax
            .else
                mov ias.Sym.FcnAry.Function.PointerToNextFunction,0
            .endif
            coff_write_aux( &ias, NULL )

            mov edx,[esi].asym.debuginfo
            mov value,[edx].debug_info.line_numbers
            coff_write_symbol( ".lf", 0, value, section, type, ebx, 0 )

            mov eax,[esi].asym.offs
            add eax,[esi].asym.total_size
            mov value,eax
            coff_write_symbol( ".ef", 0, value, section, type, ebx, 1 )

            mov ias.Sym.TagIndex,0
            mov edx,[esi].asym.debuginfo
            mov ias.Sym.Misc.LnSz.Linenumber,[edx].debug_info.end_line
            coff_write_aux( &ias, NULL )
            add cntSymbols,6
        .endif
    .endf

    ;; aliases. A weak external entry with 1 aux entry is created.

    .for ( edi = AliasTable : edi : edi = [edi].dsym.next )

        mov edx,Mangle( edi, &buffer )
        lea ecx,buffer
        .if ( edx > IMAGE_SIZEOF_SHORT_NAME )
            mov strpos,Coff_AllocString( cm, ecx, edx )
            xor ecx,ecx
        .endif
        coff_write_symbol( ecx, strpos, 0, IMAGE_SYM_UNDEFINED,
                IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_WEAK_EXTERNAL, 1 )
        inc cntSymbols

        memset( &ias, 0, sizeof(ias) )

        ;; v2.04b: adjusted to new field <substitute>

        mov edx,[edi].asym.substitute
        .if ( edx )
            mov ias.Sym.TagIndex,[edx].asym.ext_idx
        .endif
        mov ias.Sym.Misc.TotalSize,IMAGE_WEAK_EXTERN_SEARCH_ALIAS
        coff_write_aux( &ias, NULL )
        inc cntSymbols
    .endf
    .return( cntSymbols )

coff_write_symbols endp


;; callback to flush contents of codeview symbolic debug info sections

    assume esi:ptr seg_info

coff_flushfunc proc uses esi edi ebx s:ptr dsym, curr:ptr uint_8, size:dword, pv:ptr

    mov edi,s
    mov esi,[edi].dsym.seginfo
    mov ebx,curr
    sub ebx,[esi].CodeBuffer
    mov eax,ebx
    add eax,size

    .if ( ( eax ) > SIZE_CV_SEGBUF )

        .if ( ebx )

            LclAlloc( &[ebx + sizeof( qditem )] )
            mov [eax].qditem.next,NULL
            mov [eax].qditem.size,ebx

            mov edx,esi
            mov ecx,ebx
            lea edi,[eax+sizeof( qditem )]
            mov esi,[esi].CodeBuffer
            rep movsb
            mov esi,edx

            mov edx,pv
            lea ecx,[edx].coffmod.SymDeb[dbg_section]
            mov edi,[ecx].dbg_section.s
            .if edi != s
                sub ecx,sizeof( dbg_section )
            .endif

            .if ( [ecx].dbg_section.q.head == NULL )
                mov [ecx].dbg_section.q.head,eax
                mov [ecx].dbg_section.q.tail,eax
            .else
                mov edx,[ecx].dbg_section.q.tail
                mov [edx].qditem.next,eax
                mov [ecx].dbg_section.q.tail,eax
            .endif
            mov eax,[esi].start_loc
            add eax,ebx
            mov [esi].current_loc,eax
            mov [esi].start_loc,eax
        .endif
        .return( [esi].CodeBuffer )
    .endif
    .return( curr )

coff_flushfunc endp

    assume esi:nothing

;; calc the current number of entries in the symbol table
;; so we know the index if a new entry has to be added
;; called by coff_write_data()
;;
SetSymbolIndices proc uses esi edi ebx modinfo:ptr module_info, cm:ptr coffmod

  local index:uint_32
  local lastfproc:ptr asym
  local lastfile:dword

    xor esi,esi
    mov ebx,cm

    mov lastfile,esi
    mov [ebx].lastproc,esi
    mov [ebx].start_files,esi ;; v2.11: added

if COMPID
    .if ( Options.debug_symbols == 4 )
        inc esi
    .endif
endif
    ;; add absolute symbol @@feat.00 if -SAFESEH is set
    .if ( Options.safeseh )
        inc esi
    .endif

    ;; count AUX entries for .file. Depends on sizeof filename

    .if ( Options.no_file_entry == FALSE )

        strlen( [ebx].dot_file_value )
        cdq
        mov ecx,IMAGE_AUX_SYMBOL
        div ecx
        inc eax
        .if edx
            inc eax
        .endif
        add esi,eax
    .endif

    ;; add entries for sections

    mov [ebx].sectionstart,esi
    mov ecx,modinfo
    add esi,[ecx].module_info.num_segs
    .if ( Options.no_section_aux_entry == FALSE )
        add esi,[ecx].module_info.num_segs
    .endif

    ;; count externals and protos

    .for ( edi = ExtTable : edi : edi = [edi].dsym.next )

        .continue .if ( !( [edi].asym.sflags & S_ISCOM ) && \
                        [edi].asym.sflags & S_WEAK )

        mov [edi].asym.ext_idx,esi
        inc esi

        ;; weak externals need an additional aux entry

        .if ( !( [edi].asym.sflags & S_ISCOM ) && [edi].asym.altname )

            inc esi
        .endif
    .endf

    mov index,esi

if STATIC_PROCS

    ;; v2.04: count private procedures (will become static symbols)

    .if ( Options.no_static_procs == FALSE )

        .for( edi = ProcTable : edi : edi = [edi].dsym.nextproc )

            .if ( [edi].asym.state == SYM_INTERNAL && \
                  !( [edi].asym.flags & S_ISPUBLIC ) && \
                  !( [edi].asym.flag1 & S_INCLUDED ) )

                or [edi].asym.flag1,S_INCLUDED
                AddPublicData( edi )
            .endif
        .endf
    .endif
endif

    ;; count items in public queue

    mov esi,modinfo
    .for ( edi = [esi].module_info.PubQueue.head: edi: edi = [edi].qnode.next )

        mov esi,[edi].qnode.sym

        ;; if line numbers are on, co, add 6 entries for procs

        .if ( Options.line_numbers && [esi].asym.flag1 & S_ISPROC && Options.debug_symbols != 4 )

            mov edx,[esi].asym.debuginfo
            mov ebx,cm

            .if (  [edx].debug_info.file != lastfile )
                .if ( [ebx].start_files == 0 )
                    mov [ebx].start_files,index
                .else
                    mov ecx,lastfproc
                    mov ecx,[ecx].asym.debuginfo
                    mov [ecx].debug_info.next_file,index
                .endif
                mov lastfproc,esi
                mov edx,[esi].asym.debuginfo
                inc GetFileAuxEntries( [edx].debug_info.file, NULL )
                add index,eax
                mov edx,[esi].asym.debuginfo
                mov lastfile,[edx].debug_info.file
            .endif
            mov [esi].asym.ext_idx,index
            add index,7
        .else
            mov [esi].asym.ext_idx,index
            inc index
        .endif
    .endf
    .return( index )

SetSymbolIndices endp


;; write fixups for a section.

coff_write_fixup proc adr:uint_32, index:uint_32, type:uint_16

  local ir:IMAGE_RELOCATION

    mov ir.VirtualAddress,adr
    mov ir.SymbolTableIndex,index
    mov ir.Type,type

    .if ( fwrite( &ir, 1, sizeof(ir), CurrFile[OBJ*4] ) != sizeof(ir) )
        WriteError()
    .endif
    ret

coff_write_fixup endp


coff_write_fixups proc uses esi edi ebx section:ptr dsym, poffset:ptr uint_32, pindex:ptr uint_32

  local offs:uint_32
  local type:uint_16

    mov ecx,poffset
    mov eax,[ecx]
    mov offs,eax
    mov ecx,pindex
    mov esi,[ecx]
    mov ecx,section
    mov edi,[ecx].dsym.seginfo

    ;; v2.10: handle the reloc-overflow-case
    .if ( [edi].seg_info.num_relocs > 0xffff )

        mov ecx,[edi].seg_info.num_relocs
        inc ecx
        coff_write_fixup( ecx, 0,
                IMAGE_REL_I386_ABSOLUTE ) ;; doesn't matter if 32- or 64-bit
        add offs,sizeof( IMAGE_RELOCATION )
    .endif

    assume ebx:ptr fixup

    mov [edi].seg_info.num_relocs,0 ;; reset counter

    .for ( ebx = [edi].seg_info.head: ebx: ebx = [ebx].nextrlc )

        mov al,[ebx].type
        xor ecx,ecx

        .if ( [edi].seg_info.Ofssize == USE64 )

            .switch ( al )
            .case FIX_VOID
                .continue
            .case FIX_RELOFF32  ;; 32bit offset
                ;; translated to IMAGE_REL_AMD64_REL32_[1|2|3|4|5]
                movzx ecx,[ebx].addbytes
                sub ecx,4
                add ecx,IMAGE_REL_AMD64_REL32
                .endc
            .case FIX_OFF32     ;; 32bit offset
                mov ecx,IMAGE_REL_AMD64_ADDR32
                .endc
            .case FIX_OFF32_IMGREL
                mov ecx,IMAGE_REL_AMD64_ADDR32NB
                .endc
            .case FIX_OFF32_SECREL
                mov ecx,IMAGE_REL_AMD64_SECREL
                .endc
            .case FIX_OFF64     ;; 64bit offset
                mov ecx,IMAGE_REL_AMD64_ADDR64
                .endc
            .case FIX_SEG       ;; segment fixup
                mov ecx,IMAGE_REL_AMD64_SECTION ;; ???
                .endc
            .endsw

        .else

            .switch ( al )
            .case FIX_VOID
                .continue
            .case FIX_RELOFF16  ;; 16bit offset
                mov ecx,IMAGE_REL_I386_REL16
                .endc
            .case FIX_OFF16     ;; 16bit offset
                mov ecx,IMAGE_REL_I386_DIR16
                .endc
            .case FIX_RELOFF32  ;; 32bit offset
                mov ecx,IMAGE_REL_I386_REL32
                .endc
            .case FIX_OFF32     ;; 32bit offset
                mov ecx,IMAGE_REL_I386_DIR32
                .endc
            .case FIX_OFF32_IMGREL
                mov ecx,IMAGE_REL_I386_DIR32NB
                .endc
            .case FIX_OFF32_SECREL
                mov ecx,IMAGE_REL_I386_SECREL
                .endc
            .case FIX_SEG       ;; segment fixup
                mov ecx,IMAGE_REL_I386_SECTION ;; ???
                .endc
            .endsw

        .endif

        .if ( !ecx ) ;; v2.03: skip this fixup

            mov ecx,section
            asmerr( 3014, [ebx].type, [ecx].asym.name, [ebx].locofs )
            .continue
        .endif

        mov type,cx
        mov ecx,[ebx].sym

        .if ( [ecx].asym.flags & S_VARIABLE )

            ;; just use the segment entry. This approach requires
            ;; that the offset is stored inline at the reloc location
            ;; (patch in fixup.c)

            mov [ebx].sym,[ebx].segment_var
            mov ecx,eax

        .elseif ( ( [ecx].asym.state == SYM_INTERNAL ) && \
                   !( [ecx].asym.flags & S_ISPUBLIC ) && \
                   !( [ecx].asym.flag1 & S_INCLUDED ) )

            or [ecx].asym.flag1,S_INCLUDED
            AddPublicData( ecx )
            mov ecx,[ebx].sym
            mov [ecx].asym.ext_idx,esi
            inc esi
            .if ( Options.line_numbers && [ecx].asym.flag1 & S_ISPROC && Options.debug_symbols != 4 )
                add esi,6
            .endif
        .endif

        coff_write_fixup( [ebx].locofs, [ecx].asym.ext_idx, type )

        add offs,sizeof( IMAGE_RELOCATION )
        inc [edi].seg_info.num_relocs

    .endf

    mov edx,poffset
    mov [edx],offs
    mov edx,pindex
    mov [edx],esi
    ret

coff_write_fixups endp

;; write section data

coff_write_data proc uses esi edi ebx modinfo:ptr module_info, cm:ptr coffmod

  .new section:ptr dsym
  .new offs:uint_32 = 0 ;; offset within section contents
  .new i:int_t
  .new index:uint_32

    ;; calc the current index for the COFF symbol table
    mov index,SetSymbolIndices( modinfo, cm )

    ;; fill the SafeSEH array

    assume ebx:ptr coffmod

    mov ebx,cm
    mov ecx,modinfo
    .if ( [ecx].module_info.SafeSEHQueue.head )

        mov eax,[ebx].sxdata
        mov eax,[eax].dsym.seginfo
        .for( edx = [ecx].module_info.SafeSEHQueue.head,
              ecx = [eax].seg_info.CodeBuffer: edx : ecx += 4 )

            mov eax,[edx].qnode.elmt
            mov eax,[eax].asym.ext_idx
            mov [ecx],eax
            mov edx,[edx].qnode.next
        .endf
    .endif

    .for( ecx = 0, edi = SegTable : edi : ecx++, edi = [edi].dsym.next )

        mov eax,[ebx].sectionstart
        add eax,ecx
        mov [edi].asym.ext_idx,eax
        .if ( Options.no_section_aux_entry == FALSE )
            add [edi].asym.ext_idx,ecx
        .endif
    .endf

    ;; now scan the section's relocations. If a relocation refers to
    ;; a symbol which is not public/external, it must be added to the
    ;; symbol table. If the symbol is an assembly time variable, a helper
    ;; symbol - name is $$<offset:6> is to be added.

    assume esi:ptr seg_info
    .for ( edi = SegTable: edi : edi = [edi].dsym.next )

        mov ebx,[edi].asym.max_offset
        mov esi,[edi].dsym.seginfo

        ;; don't write section data for bss and uninitialized stack segments

        .continue .if ( [esi].combine == COMB_STACK && [esi].bytes_written == 0 )
        .continue .if ( [esi].segtype == SEGTYPE_BSS )

        .if ( ebx )
            add offs,ebx
            .if ((offs & 1) && [esi].head )
                inc offs
                inc ebx
            .endif
            .if ( [esi].CodeBuffer == NULL )
                fseek( CurrFile[OBJ*4], ebx, SEEK_CUR )
            .else

                ;; if there was an ORG, the buffer content will
                ;; start with the ORG address. The bytes from
                ;; 0 - ORG must be written by moving the file pointer!

                .if ( [esi].start_loc )
                    fseek( CurrFile[OBJ*4], [esi].start_loc, SEEK_CUR )
                    sub ebx,[esi].start_loc
                .endif

                .if ( fwrite( [esi].CodeBuffer, 1, ebx, CurrFile[OBJ*4] ) != ebx )
                    WriteError()
                .endif
            .endif

            coff_write_fixups( edi, &offs, &index )
        .endif

        mov ebx,cm

        ;; v2.07: the following block has beem moved outside of "if(size)" block,
        ;; because it may happen that a segment has size 0 and still debug info.
        ;; In any case it's important to initialize section->e.seginfo->num_linnums

        ;; write line number data. The peculiarity of COFF (compared to OMF) is
        ;; that line numbers are always relative to a function start.
        ;;
        ;; an item with line number 0 has a special meaning - it contains a reference
        ;; ( a symbol table index ) to the function whose line numbers are to follow.
        ;; this item is to be followed by an item with line number 32767, which then
        ;; tells the function's start offset ( undocumented! ).
        ;;

        .if ( Options.line_numbers && [esi].LinnumQueue && Options.debug_symbols != 4 )

            .new il:IMAGE_LINENUMBER
            .new last:ptr asym
            .new line_numbers:uint_32 = 0

            mov eax,[esi].LinnumQueue
            assume esi:ptr line_num_info

            mov last,NULL
            mov esi,[eax].qdesc.head

            .for ( : esi: esi = [esi].next )

                .if ( [esi].number == 0 )

                    mov last,[esi].sym

                    .if ( [ebx].lastproc )

                        mov ecx,[ebx].lastproc
                        mov ecx,[ecx].asym.debuginfo
                        mov edx,[eax].asym.ext_idx
                        mov [ecx].debug_info.next_proc,edx
                    .endif

                    mov [ebx].lastproc,eax
                    mov ecx,[eax].asym.debuginfo
                    mov [ecx].debug_info.next_proc,0
                    mov il.Linenumber,0
                    mov il.Type.SymbolTableIndex,[eax].asym.ext_idx
                    mov [ecx].debug_info.start_line,[esi].line_number
                    mov eax,[ebx].start_data
                    add eax,offs
                    mov [ecx].debug_info.ln_fileofs,eax

                .else

                    mov ecx,last
                    mov ecx,[ecx].asym.debuginfo
                    mov eax,[esi].number
                    sub eax,[ecx].debug_info.start_line
                    mov il.Linenumber,ax

                    ;; if current line number - start line number is 0,
                    ;; generate a "32767" line number item.

                    .if ( il.Linenumber == 0 )
                        mov il.Linenumber,0x7FFF
                    .endif
                    mov il.Type.VirtualAddress,[esi].offs
                .endif

                mov ecx,last
                mov ecx,[ecx].asym.debuginfo
                inc [ecx].debug_info.line_numbers
                mov [ecx].debug_info.end_line,[esi].number

                .if ( fwrite( &il, 1, sizeof(il), CurrFile[OBJ*4] ) != sizeof(il) )
                    WriteError()
                .endif

                add offs,sizeof(il)
                inc line_numbers
            .endf

            mov edx,[edi].dsym.seginfo
            mov [edx].seg_info.num_linnums,line_numbers
        .endif

    .endf

    mov ebx,cm
    mov [ebx].size_data,offs

    .return( NOT_ERROR )

coff_write_data endp


;;
;; check if a .drectve section has to be created.
;; if yes, create it and set its contents.
;;

coff_create_drectve proc uses esi edi ebx modinfo:ptr module_info, cm:ptr coffmod

  .new exp:ptr dsym
  .new imp:ptr dsym = NULL
  .new buffer[MAX_ID_LEN + MANGLE_BYTES + 1]:char_t

    ;; does a proc exist with the EXPORT attribute?

    .for( edi = ProcTable : edi != NULL: edi = [edi].dsym.nextproc )

        mov ecx,[edi].dsym.procinfo
        .break .if ( [ecx].proc_info.flags & PROC_ISEXPORT )
    .endf
    mov exp,edi

    ;; check if an impdef record is there

    .if ( Options.write_impdef && !Options.names[OPTN_LNKDEF_FN*4] )

        .for ( edi = ExtTable: edi: edi = [edi].dsym.next )

            .if ( [edi].asym.flag1 & S_ISPROC && \
                ( !( [edi].asym.sflags & S_WEAK ) || [edi].asym.flags & S_IAT_USED ) )

                mov edx,[edi].asym.dll
                .if ( edx )
                    .break .if [edx].dll_desc.name
                .endif
            .endif
        .endf
        mov imp,edi
    .endif

    ;; add a .drectve section if
    ;; - a start_label is defined    and/or
    ;; - a library is included       and/or
    ;; - a proc is exported          and/or
    ;; - impdefs are to be written (-Zd)

    assume esi:ptr module_info
    mov esi,modinfo

    .if ( [esi].start_label != NULL || [esi].LibQueue.head != NULL || \
         imp != NULL || exp != NULL || [esi].LinkQueue.head != NULL )

         mov ebx,cm
         mov [ebx].directives,CreateIntSegment( szdrectve, "", MAX_SEGALIGNMENT, [esi].Ofssize, FALSE )

        .if ( eax )

            xor ebx,ebx
            mov edi,[eax].dsym.seginfo
            mov [edi].seg_info.info,TRUE

            ;; calc the size for this segment

            ;; 1. exports

            .for ( edi = exp: edi: edi = [edi].dsym.nextproc )

                mov ecx,[edi].dsym.procinfo
                .if ( [ecx].proc_info.flags & PROC_ISEXPORT )

                    Mangle( edi, &buffer )
                    lea ebx,[ebx+eax+9]

                    .if ( Options.no_export_decoration == TRUE )

                        add ebx,[edi].asym.name_size
                        inc ebx
                    .endif
                .endif
            .endf

            ;; 2. defaultlibs

            .for ( edi = [esi].LibQueue.head: edi: edi = [edi].qitem.next )

                strlen( &[edi].qitem.value ) ; sizeof("-defaultlib:")
                lea ebx,[ebx+eax+13]

                ;; if the name isn't enclosed in double quotes and contains
                ;; a space, add 2 bytes to enclose it

                .if ( [edi].qitem.value != '"' )
                    .if ( strchr( &[edi].qitem.value, ' ') )
                        add ebx,2
                    .endif
                .endif
            .endf

            ;; 3. start label

            add ebx,GetStartLabel( esi, &buffer, TRUE )

            ;; 4. impdefs

            .for ( edi = imp: edi: edi = [edi].dsym.next )

                .if ( [edi].asym.flag1 & S_ISPROC && \
                    ( !( [edi].asym.sflags & S_WEAK ) || [edi].asym.flags & S_IAT_USED ) && \
                      [edi].asym.dll )

                    mov edx,[edi].asym.dll
                    .if [edx].dll_desc.name

                        ;; format is:
                        ;; "-import:<mangled_name>=<module_name>.<unmangled_name>" or
                        ;; "-import:<mangled_name>=<module_name>"

                        strlen( &[edx].dll_desc.name )
                        lea ebx,[ebx+eax+9+1]
                        add ebx,Mangle( edi, &buffer )
                        add ebx,[edi].asym.name_size
                        inc ebx
                    .endif
                .endif
            .endf

            ;; 5. pragma comment(linker,"/..")

            .for ( edi = [esi].LinkQueue.head: edi: edi = [edi].qitem.next )

                strlen( &[edi].qitem.value )
                lea ebx,[ebx+eax+1]
            .endf

            mov ecx,ebx
            mov ebx,cm
            mov edx,[ebx].directives
            mov [edx].asym.max_offset,ecx
            mov edi,[edx].dsym.seginfo
            inc ecx
            mov [edi].seg_info.CodeBuffer,LclAlloc( ecx )
            mov ebx,eax

            assume ebx:nothing

            ;; copy the data

            ;; 1. exports

            .for ( edi = exp: edi: edi = [edi].dsym.nextproc )
                mov ecx,[edi].dsym.procinfo
                .if ( [ecx].proc_info.flags & PROC_ISEXPORT )
                    Mangle( edi, &buffer )
                    .if ( Options.no_export_decoration == FALSE )
                        add ebx,tsprintf( ebx, "-export:%s ", &buffer )
                    .else
                        add ebx,tsprintf( ebx, "-export:%s=%s ", [edi].asym.name, &buffer )
                    .endif
                .endif
            .endf

            ;; 2. libraries

            .for ( edi = [esi].LibQueue.head: edi: edi = [edi].qitem.next )
                .if ( strchr( &[edi].qitem.value, ' ') && [edi].qitem.value != '"' )
                    add ebx,tsprintf( ebx, "-defaultlib:\"%s\" ", &[edi].qitem.value )
                .else
                    add ebx,tsprintf( ebx, "-defaultlib:%s ", &[edi].qitem.value )
                .endif
            .endf

            ;; 3. entry

            .if ( [esi].start_label )
                GetStartLabel( esi, &buffer, FALSE )
                add ebx,tsprintf( ebx, "-entry:%s ", &buffer )
            .endif

            ;; 4. impdefs

            .for ( edi = imp: edi: edi = [edi].dsym.next )

                .if ( [edi].asym.flag1 & S_ISPROC && \
                    ( !( [edi].asym.sflags & S_WEAK ) || [edi].asym.flags & S_IAT_USED ) && \
                      [edi].asym.dll )

                    mov edx,[edi].asym.dll
                    .if [edx].dll_desc.name

                        strcpy( ebx, "-import:" )
                        add ebx,8
                        add ebx,Mangle( edi, ebx )
                        mov byte ptr [ebx],'='
                        inc ebx
                        mov ecx,[edi].asym.dll
                        strcpy( ebx, &[ecx].dll_desc.name )
                        add ebx,strlen( ebx )
                        mov byte ptr [ebx],'.'
                        inc ebx
                        memcpy( ebx, [edi].asym.name, [edi].asym.name_size )
                        add ebx,[edi].asym.name_size
                        mov byte ptr [ebx],' '
                        inc ebx
                    .endif
                .endif
            .endf

            ;; 5. pragma comment(linker,"/..")

            .for ( edi = [esi].LinkQueue.head: edi: edi = [edi].qitem.next )

                add ebx,tsprintf( ebx, "%s ", &[edi].qitem.value )
            .endf
        .endif
    .endif
    ret

coff_create_drectve endp

    assume esi:nothing

;;
;; Write current object module in COFF format.
;; This function is called AFTER all assembly passes have been done.
;;

coff_write_module proc uses esi edi ebx modinfo:ptr module_info

  local cm:coffmod
  local ifh:IMAGE_FILE_HEADER

    memset( &cm, 0, sizeof( cm ) )
    mov cm.size,sizeof( uint_32 )

    ;; get value for .file symbol
    mov cm.dot_file_value,CurrFName[ASM*4]

    ;; it might be necessary to add "internal" sections:
    ;; - .debug$S and .debug$T sections if -Zi was set
    ;; - .sxdata section if .SAFESEH was used
    ;; - .drectve section if start label, exports or includelibs are used

    ;; if -Zi is set, add .debug$S and .debug$T sections

    .if ( Options.debug_symbols )

        .for ( ebx = 0: ebx < DBGS_MAX: ebx++ )

            imul edi,ebx,dbg_section

            mov cm.SymDeb[edi].s,CreateIntSegment( SymDebName[ebx*4], "", 0, USE32, TRUE )
           .break .if ( eax == NULL )

            mov ecx,[eax].dsym.seginfo
            mov [ecx].seg_info.characteristics,( IMAGE_SCN_MEM_READ or IMAGE_SCN_MEM_DISCARDABLE ) shr 24

            ;; use the source line buffer as code buffer. It isn't needed anymore

            imul eax,ebx,SIZE_CV_SEGBUF
            add eax,CurrSource

            mov [ecx].seg_info.CodeBuffer,eax
            mov [ecx].seg_info.flushfunc,coff_flushfunc
            mov cm.SymDeb[edi].q.head,NULL
        .endf

        .if ( ebx == DBGS_MAX )

            cv_write_debug_tables( cm.SymDeb[DBGS_SYMBOLS*dbg_section].s,
                    cm.SymDeb[DBGS_TYPES*dbg_section].s, &cm )

            ;; the contents have been written in queues. now
            ;; copy all queue items in ONE buffer.

            .for ( ebx = 0: ebx < DBGS_MAX: ebx++ )

                imul edi,ebx,dbg_section

                mov ecx,cm.SymDeb[edi].s
                mov esi,[ecx].dsym.seginfo

                .if ( [ecx].asym.max_offset )
                    .if ( [ecx].asym.max_offset > SIZE_CV_SEGBUF )
                        mov [esi].seg_info.CodeBuffer,LclAlloc( [ecx].asym.max_offset )
                    .endif
                    mov edx,[esi].seg_info.CodeBuffer
                    mov esi,cm.SymDeb[edi].q.head

                    .for ( edi = edx: esi: esi = [esi].qditem.next )
                        mov ecx,[esi].qditem.size
                        lea edx,[esi+qditem]
                        xchg esi,edx
                        rep movsb
                        mov esi,edx
                    .endf
                .endif
            .endf
        .endif
    .endif

    ;; if safeSEH procs are defined, add a .sxdata section

    mov esi,modinfo
    assume esi:ptr module_info
    .if ( [esi].SafeSEHQueue.head )

        mov cm.sxdata,CreateIntSegment( ".sxdata", "", MAX_SEGALIGNMENT, [esi].Ofssize, FALSE )

        .if ( eax )

            mov edi,[eax].dsym.seginfo
            mov [edi].seg_info.info,TRUE

            ;; calc the size for this segment

            .for ( edx = [esi].SafeSEHQueue.head,
                   ecx = 0 : edx : edx = [edx].qnode.next, ecx++ )
            .endf
            shl ecx,2
            mov edx,cm.sxdata
            mov [edx].asym.max_offset,ecx
            mov [edi].seg_info.CodeBuffer,LclAlloc( ecx )
        .endif
    .endif

    ;; create .drectve section if necessary

    coff_create_drectve( esi, &cm )

    .if ( [esi].defOfssize == USE64 )
        mov ifh.Machine,IMAGE_FILE_MACHINE_AMD64
    .else
        mov ifh.Machine,IMAGE_FILE_MACHINE_I386
    .endif
    mov ifh.NumberOfSections,[esi].num_segs
    time(&ifh.TimeDateStamp)
    mov ifh.SizeOfOptionalHeader,0
    mov ifh.Characteristics,0

    ;; position behind coff file header

    fseek( CurrFile[OBJ*4], sizeof( ifh ), SEEK_SET )

    coff_write_section_table( esi, &cm );
    coff_write_data( esi, &cm );
    mov ifh.NumberOfSymbols,coff_write_symbols( esi, &cm )
    xor eax,eax
    .if ( ifh.NumberOfSymbols )
        mov eax,cm.start_data
        add eax,cm.size_data
    .endif
    mov ifh.PointerToSymbolTable,eax

    .if ( fwrite( &cm.size, 1, sizeof( cm.size ),
            CurrFile[OBJ*4] ) != sizeof( cm.size ) )
        WriteError()
    .endif

    assume ebx:ptr stringitem
    .for ( ebx = cm.head : ebx : ebx = [ebx].next )
        inc strlen( &[ebx].string )
        mov edi,eax
        .if ( fwrite( &[ebx].string, 1, edi, CurrFile[OBJ*4] ) != edi )
            WriteError()
        .endif
    .endf

    ;; finally write the COFF file header

    fseek( CurrFile[OBJ*4], 0, SEEK_SET)
    .if ( fwrite( &ifh, 1, sizeof( ifh ), CurrFile[OBJ*4] ) != sizeof( ifh ) )
        WriteError()
    .endif

    .return( NOT_ERROR )

coff_write_module endp

    option proc:public

coff_init proc modinfo:ptr module_info

    mov ecx,modinfo
    mov [ecx].module_info.WriteModule,coff_write_module
    ret
coff_init endp

    end

