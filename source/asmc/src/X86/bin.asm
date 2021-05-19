; BIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include stddef.inc
include time.inc
include asmc.inc
include memalloc.inc
include parser.inc
include fixup.inc
include omfspec.inc
include bin.inc
include listing.inc
include lqueue.inc
include coffspec.inc
include input.inc
include mangle.inc
include segment.inc
include equate.inc
include expreval.inc
include pespec.inc

define RAWSIZE_ROUND 1 ;; SectionHeader.SizeOfRawData is multiple FileAlign. Required by MS COFF spec
define IMGSIZE_ROUND 1 ;; OptionalHeader.SizeOfImage is multiple ObjectAlign. Required by MS COFF spec

IMPDIRSUF  equ <"2"> ;; import directory segment suffix
IMPNDIRSUF equ <"3"> ;; import data null directory entry segment suffix
IMPILTSUF  equ <"4"> ;; ILT segment suffix
IMPIATSUF  equ <"5"> ;; IAT segment suffix
IMPSTRSUF  equ <"6"> ;; import strings segment suffix

;; pespec.inc contains MZ header declaration

include pespec.inc

SortSegments proto :int_t

.data

;; if the structure changes, option.c, SetMZ() might need adjustment!

MZDATA      struct
ofs_fixups  dw ?    ; offset start fixups
alignment   dw ?    ; header alignment: 16,32,64,128,256,512
heapmin     dw ?
heapmax     dw ?
MZDATA      ends

;; default values for OPTION MZ
ifndef __ASMC64__
mzdata MZDATA { 0x1E, 0x10, 0, 0xFFFF }
endif

;; these strings are to be moved to ltext.inc

szCaption    equ <"Binary Map:">
szCaption2   equ <"Segment                  Pos(file)     RVA  Size(fil) Size(mem)">
szSep        equ <"---------------------------------------------------------------">
szHeader     equ <"<header>">
szSegLine    equ <"%-24s %8X %8X %9X %9X">
szTotal      equ <"%-42s %9X %9X">

calc_param          struct
    first           uint_8 ?    ; 1=first call of CalcOffset()
    alignment       uint_8 ?    ; current aligment
    fileoffset      uint_32 ?   ; current file offset
    sizehdr         uint_32 ?   ; -mz: size of MZ header, else 0
    entryoffset     uint_32 ?   ; -bin only: offset of first segment
    entryseg        asym_t ?    ; -bin only: segment of first segment
    imagestart      uint_32 ?   ; -bin: start offset (of first segment), else 0
    rva             uint_32 ?   ; -pe: current RVA
    union
     imagebase      uint_32 ?   ; -pe: image base
     imagebase64    uint_64 ?   ; -pe: image base
    ends
if RAWSIZE_ROUND
    rawpagesize     uint_32 ?
endif
calc_param          ends

dosseg_order seg_type \ ;; reorder segments for DOSSEG:
    SEGTYPE_CODE,       ;; 1. code
    SEGTYPE_UNDEF,      ;; 2. unknown
    SEGTYPE_DATA,       ;; 3. initialized data
    SEGTYPE_BSS,        ;; 4. uninitialized data
    SEGTYPE_STACK,      ;; 5. stack
    SEGTYPE_ABS

flat_order seg_type \
    SEGTYPE_HDR,
    SEGTYPE_CODE,
    SEGTYPE_CDATA,
    SEGTYPE_DATA,
    SEGTYPE_BSS,
    SEGTYPE_RSRC,
    SEGTYPE_RELOC

SIZE_DOSSEG equ ( sizeof( dosseg_order ) / sizeof( seg_type ) )
SIZE_PEFLAT equ ( sizeof( flat_order ) / sizeof( seg_type ) )

.enum pe_flags_values {
    PEF_MZHDR = 0x01,  ;; 1=create mz header
    }

hdrname     equ <".hdr$">
hdrattr     equ <"read public 'HDR'">
edataname   equ <".edata">
edataattr   equ <"FLAT read public alias('.rdata') 'DATA'">

idataname   equ <".idata$">
idataattr   equ <"FLAT read public alias('.rdata') 'DATA'">

mzcode char_t \
    "db 'MZ'",              ;; e_magic
    "dw 68h,1,0,4",         ;; e_cblp, e_cp, e_crlc, e_cparhdr
    "dw 0,-1,0,0B8h",       ;; e_minalloc, e_maxalloc, e_ss, e_sp
    "dw 0,0,0,40h",         ;; e_csum, e_ip, e_cs, e_sp, e_lfarlc
    "org 40h",              ;; e_lfanew, will be set by program
    "push cs",
    "pop ds",
    "mov dx,@F-40h",
    "mov ah,9",
    "int 21h",
    "mov ax,4C01h",
    "int 21h",
    "@@:",
    "db 'This is a PE executable',0Dh,0Ah,'$'",0
mzcodelz char_t 7,12,14,12,7,7,6,13,8,7,12,7,3,0

    align 4

ifndef __ASMC64__

;; default 32-bit PE header

pe32def IMAGE_PE_HEADER32 {
    'EP',
    { IMAGE_FILE_MACHINE_I386, 0, 0, 0, 0, sizeof( IMAGE_OPTIONAL_HEADER32 ),
      IMAGE_FILE_RELOCS_STRIPPED or IMAGE_FILE_EXECUTABLE_IMAGE or \
      IMAGE_FILE_LINE_NUMS_STRIPPED or IMAGE_FILE_LOCAL_SYMS_STRIPPED or \
      IMAGE_FILE_32BIT_MACHINE },
    { IMAGE_NT_OPTIONAL_HDR32_MAGIC,
      5,1,0,0,0,0,0,0, ;; linkervers maj/min, sizeof code/init/uninit, entrypoint, base code/data
      0x400000,        ;; image base
      0x1000, 0x200,   ;; SectionAlignment, FileAlignment
      4,0,0,0,4,0,     ;; OSversion maj/min, Imagevers maj/min, Subsystemvers maj/min
      0,0,0,0,         ;; Win32vers, sizeofimage, sizeofheaders, checksum
      IMAGE_SUBSYSTEM_WINDOWS_CUI,0,  ;; subsystem, dllcharacteristics
      0x100000,0x1000, ;; sizeofstack reserve/commit
      0x100000,0x1000, ;; sizeofheap reserve/commit
      0, IMAGE_NUMBEROF_DIRECTORY_ENTRIES, ;; loaderflags, numberofRVAandSizes
    }}
endif

;; default 64-bit PE header

pe64def IMAGE_PE_HEADER64 {
    'EP',
    { IMAGE_FILE_MACHINE_AMD64, 0, 0, 0, 0, sizeof( IMAGE_OPTIONAL_HEADER64 ),
      IMAGE_FILE_RELOCS_STRIPPED or IMAGE_FILE_EXECUTABLE_IMAGE or \
      IMAGE_FILE_LINE_NUMS_STRIPPED or IMAGE_FILE_LOCAL_SYMS_STRIPPED or \
      IMAGE_FILE_LARGE_ADDRESS_AWARE or IMAGE_FILE_32BIT_MACHINE },
    { IMAGE_NT_OPTIONAL_HDR64_MAGIC,
      5,1,0,0,0,0,0,   ;; linkervers maj/min, sizeof code/init data/uninit data, entrypoint, base code RVA
      0x400000,        ;; image base
      0x1000, 0x200,   ;; SectionAlignment, FileAlignment
      4,0,0,0,4,0,     ;; OSversion maj/min, Imagevers maj/min, Subsystemvers maj/min
      0,0,0,0,         ;; Win32vers, sizeofimage, sizeofheaders, checksum
      IMAGE_SUBSYSTEM_WINDOWS_CUI,0,  ;; subsystem, dllcharacteristics
      0x100000,0x1000, ;; sizeofstack reserve/commit
      0x100000,0x1000, ;; sizeofheap reserve/commit
      0, IMAGE_NUMBEROF_DIRECTORY_ENTRIES, ;; loaderflags, numberofRVAandSizes
    } }

    .code

    B equ <byte ptr>
    W equ <word ptr>

    option proc:private

    ;; calculate starting offset of segments and groups

    assume ebx:ptr calc_param
    assume edi:ptr seg_info

CalcOffset proc uses esi edi ebx curr:ptr dsym, cp:ptr calc_param

  local alignment:uint_32
  local alignbytes:uint_32
  local offs:uint_32
  local grp:ptr dsym

    mov esi,curr
    mov edi,[esi].dsym.seginfo

    .if ( [edi].segtype == SEGTYPE_ABS )
        mov eax,[edi].abs_frame
        shl eax,4
        mov [edi].start_offset,eax
        .return
    .elseif ( [edi].info )
        .return
    .endif

    mov edx,1
    mov ebx,cp
    .if ( [ebx].alignment > [edi].alignment )
        mov cl,[ebx].alignment
    .else
        mov cl,[edi].alignment
    .endif
    shl edx,cl
    mov alignment,edx

    mov ecx,edx
    neg ecx
    dec edx
    add edx,[ebx].fileoffset
    and edx,ecx
    sub edx,[ebx].fileoffset
    mov alignbytes,edx
    add [ebx].fileoffset,edx

    mov grp,[edi].sgroup

    .if eax == NULL

        mov eax,[ebx].fileoffset
        sub eax,[ebx].sizehdr
        mov offs,eax

    .else
        .if ( ModuleInfo.sub_format == SFORMAT_PE || ModuleInfo.sub_format == SFORMAT_64BIT )

            ;; v2.24

            mov offs,[ebx].rva
        .else

            .if [eax].asym.total_size == 0

                mov ecx,[ebx].fileoffset
                sub ecx,[ebx].sizehdr
                mov [eax].asym.offs,ecx
                mov offs,0

            .else

                ;; v2.12: the old way wasn't correct. if there's a segment between the
                ;; segments of a group, it affects the offset as well ( if it
                ;; occupies space in the file )! the value stored in grp->sym.total_size
                ;; is no longer used (or, more exactly, used as a flag only).
                ;;
                ;; offset = ( cp->fileoffset - cp->sizehdr ) - grp->sym.offset;

                mov ecx,[eax].asym.total_size
                add ecx,alignbytes
                mov offs,ecx
            .endif
        .endif
    .endif

    ;; v2.04: added */
    ;; v2.05: this addition did mess sample Win32_5.asm, because the
    ;; "empty" alignment sections are now added to <fileoffset>.
    ;; todo: VA in binary map is displayed wrong.

    .if ( [ebx].first == FALSE )

        ;; v2.05: do the reset more carefully.
        ;; Do reset start_loc only if
        ;; - segment is in a group and
        ;; - group isn't FLAT or segment's name contains '$'

        mov eax,grp
        .if ( eax )
            .if ( eax != ModuleInfo.flat_grp )
                mov [edi].start_loc,0
            .elseif ( strchr( [esi].asym.name, '$' ) )
                mov [edi].start_loc,0
            .endif
        .endif
    .endif

    mov [edi].fileoffset,[ebx].fileoffset
    mov [edi].start_offset,offs

    .if ( ModuleInfo.sub_format == SFORMAT_NONE )

        mov eax,[esi].asym.max_offset
        sub eax,[edi].start_loc
        add [ebx].fileoffset,eax

        .if [ebx].first

            mov [ebx].imagestart,[edi].start_loc
        .endif

        ;; there's no real entry address for BIN, therefore the
        ;; start label must be at the very beginning of the file

        .if [ebx].entryoffset == -1

            mov [ebx].entryoffset,offs
            mov [ebx].entryseg,esi
        .endif
    .else

        mov eax,[esi].asym.max_offset
        sub eax,[edi].start_loc
        add [ebx].rva,eax
        .if ( [edi].segtype != SEGTYPE_BSS )
            add [ebx].fileoffset,eax
        .endif
    .endif

    add offs,[esi].asym.max_offset
    mov ecx,grp
    .if ecx

        mov [ecx].asym.total_size,offs

        ;; v2.07: for 16-bit groups, ensure that it fits in 64 kB

        .if ( [ecx].asym.total_size > 0x10000 && [ecx].asym.Ofssize == USE16 )

            asmerr( 8003, [ecx].asym.name )
        .endif
    .endif
    mov [ebx].first,FALSE
    ret

CalcOffset endp

;; if pDst==NULL: count the number of segment related fixups
;; if pDst!=NULL: write segment related fixups

    assume ebx:ptr fixup

GetSegRelocs proc uses esi edi ebx pDst:ptr uint_16

  .new count:int_t = 0

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head : esi : esi = [esi].dsym.next )

        mov edi,[esi].dsym.seginfo
        .continue .if ( [edi].segtype == SEGTYPE_ABS )

        .for ( ebx = [edi].head : ebx : ebx = [ebx].nextrlc )

            .switch [ebx].type
            .case FIX_PTR32
            .case FIX_PTR16
            .case FIX_SEG

                ;; ignore fixups for absolute segments
                mov ecx,[ebx].sym
                .if ecx

                    mov ecx,[ecx].asym.segm
                    .if ecx && [ecx].dsym.seginfo

                        mov eax,[ecx].dsym.seginfo
                        .endc .if ( [eax].seg_info.segtype == SEGTYPE_ABS )
                    .endif
                .endif

                inc count

                .if ( pDst )

                    ;; v2.04: fixed

                    mov eax,[ebx].locofs
                    mov ecx,[edi].start_offset
                    and ecx,0xf
                    add ecx,eax

                    mov eax,[edi].start_offset
                    shr eax,4

                    .if [edi].sgroup

                        mov edx,[edi].sgroup
                        mov edx,[edx].asym.offs
                        and edx,0xf
                        add ecx,edx
                        mov edx,[edi].sgroup
                        mov edx,[edx].asym.offs
                        shr edx,4
                        add eax,edx
                    .endif

                    .if [ebx].type == FIX_PTR16
                        add ecx,2
                    .elseif [ebx].type == FIX_PTR32
                        add ecx,4
                    .endif

                    ;; offset may be > 64 kB

                    .while ecx >= 0x10000

                        sub ecx,16
                        inc eax
                    .endw

                    mov edx,pDst
                    mov [edx],cx
                    mov [edx+2],ax
                    add pDst,4
                .endif
                .endc
            .endsw
        .endf
    .endf
    .return( count )

GetSegRelocs endp

;; get image size.
;; memimage=FALSE: get size without uninitialized segments (BSS and STACK)
;; memimage=TRUE: get full size

GetImageSize proc uses esi edi ebx memimage:int_t

    .new first:uint_32 = TRUE

    .for ( esi = SymTables[TAB_SEG*symbol_queue].head,
           eax = 0, ebx = 0 : esi : esi = [esi].dsym.next )

        mov edi,[esi].dsym.seginfo
        .continue .if ( [edi].segtype == SEGTYPE_ABS || [edi].info )
        .if ( memimage == FALSE )
            .if ( [edi].bytes_written == 0 )
                .for ( ecx = [esi].dsym.next : ecx : ecx = [ecx].dsym.next )
                    mov edx,[ecx].dsym.seginfo
                    .break .if ( [edx].seg_info.bytes_written )
                .endf
                .break .if !ecx ;; done, skip rest of segments!
            .endif
        .endif
        mov ecx,[esi].asym.max_offset
        sub ecx,[edi].start_loc
        add ecx,[edi].fileoffset
        .if first == FALSE
            add ebx,[edi].start_loc
        .endif
        .if memimage
            add ecx,ebx
        .endif
        .if eax < ecx
            mov eax,ecx
        .endif
        mov first,FALSE
    .endf
    ret

GetImageSize endp


;; micro-linker. resolve internal fixups.

;; handle the fixups contained in a segment

DoFixup proc uses esi edi ebx curr:ptr dsym, cp:ptr calc_param

  local codeptr:ptr
  local sg:ptr dsym
  local value:uint_32
  local value64:uint_64
  local offs:uint_32  ;; v2.07

    mov esi,curr
    mov edi,[esi].dsym.seginfo

    .return( NOT_ERROR ) .if ( [edi].segtype == SEGTYPE_ABS )

    .for ( ebx = [edi].head : ebx : ebx = [ebx].nextrlc )

        mov eax,[ebx].locofs
        sub eax,[edi].start_loc
        add eax,[edi].CodeBuffer
        mov codeptr,eax

        mov ecx,[ebx].sym
        .if ( ecx && ( [ecx].asym.segm || [ecx].asym.flags & S_VARIABLE ) )

            ;; assembly time variable (also $ symbol) in reloc?
            ;; v2.07: moved inside if-block, using new local var "offset"

            .if [ecx].asym.flags & S_VARIABLE

                mov esi,[ebx].segment_var
                mov offs,0

            .else
                mov esi,[ecx].asym.segm
                mov offs,[ecx].asym.offs
            .endif

            mov sg,esi
            mov esi,[esi].dsym.seginfo
            assume esi:ptr seg_info

            ;; the offset result consists of
            ;; - the symbol's offset
            ;; - the fixup's offset (usually the displacement )
            ;; - the segment/group offset in the image

            mov al,[ebx].type
            .switch al

            .case FIX_OFF32_IMGREL

                mov eax,[ebx].offs
                add eax,offs
                add eax,[esi].start_offset
                mov ecx,cp
                sub eax,[ecx].calc_param.imagestart
                mov value,eax
                .endc

            .case FIX_OFF32_SECREL

                mov eax,[ebx].offs
                add eax,offs
                sub eax,[esi].start_loc
                mov value,eax

                ;; check if symbol's segment name contains a '$'.
                ;; If yes, search the segment without suffix.

                mov ecx,sg
                .if ( strchr( [ecx].asym.name, '$' ) )

                    mov ecx,sg
                    sub eax,[ecx].asym.name
                   .new namlen:int_t = eax

                    .for ( edx = SymTables[TAB_SEG*symbol_queue].head : edx : edx = [edx].dsym.next )

                        .if ( [edx].asym.name_size == namlen )

                            push edx
                            mov ecx,sg
                            memcmp( [edx].asym.name, [ecx].asym.name, namlen )
                            pop edx

                            .if eax == 0

                                mov eax,[ebx].offs
                                add eax,offs
                                add eax,[esi].start_offset
                                mov ecx,[edx].dsym.seginfo
                                sub eax,[ecx].seg_info.start_offset
                                mov value,eax
                               .break
                            .endif
                        .endif
                    .endf
                .endif
                .endc

            .case FIX_RELOFF8
            .case FIX_RELOFF16
            .case FIX_RELOFF32

                ;; v1.96: special handling for "relative" fixups
                ;; v2.28: removed fixup->offset..

                mov eax,[esi].start_offset
                add eax,offs
                mov value,eax
                .endc

            .default

                .if ( [esi].sgroup && [ebx].frame_type != FRAME_SEG )

                    mov ecx,[esi].sgroup
                    mov eax,[ecx].asym.offs
                    and eax,0x0F
                    add eax,[esi].start_offset
                    add eax,[ebx].offs
                    add eax,offs
                    mov value,eax

                    .if ( ModuleInfo.sub_format == SFORMAT_PE || ModuleInfo.sub_format == SFORMAT_64BIT )

                        mov ecx,cp
                        .if ( [edi].Ofssize == USE64 )

                            mov eax,dword ptr [ecx].calc_param.imagebase64
                            mov edx,dword ptr [ecx].calc_param.imagebase64[4]
                            add eax,value
                            adc edx,0
                            mov dword ptr value64[4],edx
                            mov dword ptr value64,eax
                        .endif
                        add value,[ecx].calc_param.imagebase
                    .endif
                .else
                    mov eax,[esi].start_offset
                    and eax,0xF
                    add eax,[ebx].offs
                    add eax,offs
                    mov value,eax
                .endif
                .endc
            .endsw
        .else
            mov sg,NULL
            mov value,0
        .endif

        mov ecx,codeptr
        mov eax,value
        movzx edx,[ebx].type
        .switch edx
        .case FIX_RELOFF8
            sub eax,[ebx].locofs
            sub eax,[edi].start_offset
            sub eax,1
            add [ecx],al
            .endc
        .case FIX_RELOFF16
            sub eax,[ebx].locofs
            sub eax,[edi].start_offset
            sub eax,2
            add [ecx],ax
            .endc
        .case FIX_RELOFF32
            ;; adjust the location for EIP-related offsets if USE64
            .if ( [edi].Ofssize == USE64 )
                movzx edx,[ebx].addbytes
                sub edx,4
                add [ebx].locofs,edx
            .endif
            ;; changed in v1.95
            sub eax,[ebx].locofs
            sub eax,[edi].start_offset
            sub eax,4
            add [ecx],eax
            .endc
        .case FIX_OFF8
            mov [ecx],al
            .endc
        .case FIX_OFF16
            mov [ecx],ax
            .endc
        .case FIX_OFF32
        .case FIX_OFF32_IMGREL
        .case FIX_OFF32_SECREL
            mov [ecx],eax
            .endc
        .case FIX_OFF64
            xor edx,edx
            .if ( ( ModuleInfo.sub_format == SFORMAT_PE && [edi].Ofssize == USE64 ) || \
                 ModuleInfo.sub_format == SFORMAT_64BIT )
                mov eax,dword ptr value64
                mov edx,dword ptr value64[4]
            .endif
            mov [ecx],eax
            mov [ecx+4],edx
            .endc
        .case FIX_HIBYTE
            mov [ecx],ah
            .endc
        .case FIX_SEG

            ;; absolute segments are ok

            mov eax,[ebx].sym
            .if eax && [eax].asym.state == SYM_SEG
                mov edx,[eax].dsym.seginfo
                .if [edx].seg_info.segtype == SEGTYPE_ABS
                    mov edx,[edx].seg_info.abs_frame
                    mov [ecx],dx
                    .endc
                .endif
            .endif

            .if ( ModuleInfo.sub_format == SFORMAT_MZ )

                .if ( [eax].asym.state == SYM_GRP )

                    mov sg,eax
                    mov esi,[eax].dsym.seginfo
                    mov edx,[eax].asym.offs
                    shr edx,4
                    mov [ecx],dx

                .elseif ( [eax].asym.state == SYM_SEG )

                    mov sg,eax
                    mov esi,[eax].dsym.seginfo
                    mov edx,[esi].start_offset
                    .if [esi].sgroup
                        mov eax,[esi].sgroup
                        add edx,[eax].asym.offs
                    .endif
                    shr edx,4
                    mov [ecx],dx

                .elseif ( [ebx].frame_type == FRAME_GRP )

                    mov eax,[esi].sgroup
                    mov eax,[eax].asym.offs
                    shr eax,4
                    mov [ecx],ax
                .else
                    mov eax,[esi].start_offset
                    shr eax,4
                    mov [ecx],ax
                .endif
                .endc
            .endif
            mov eax,value

        .case FIX_PTR16
            ;; v2.10: absolute segments are ok
            .if ( sg && [esi].segtype == SEGTYPE_ABS )
                mov [ecx],ax
                mov eax,[esi].abs_frame
                mov [ecx+2],ax
                .endc
            .endif
            .if ( ModuleInfo.sub_format == SFORMAT_MZ )
                mov [ecx],ax
                add ecx,2
                .if ( [ebx].frame_type == FRAME_GRP )
                    mov eax,[esi].sgroup
                    mov eax,[eax].asym.offs
                    shr eax,4
                    mov [ecx],ax
                .else
                    mov eax,[esi].start_offset
                    .if [esi].sgroup
                        mov edx,[esi].sgroup
                        add eax,[edx].asym.offs
                    .endif
                    shr eax,4
                    mov [ecx],ax
                .endif
                .endc
            .endif
            mov eax,value
        .case FIX_PTR32
            ;; v2.10: absolute segments are ok
            .if ( sg && [esi].segtype == SEGTYPE_ABS )
                mov [ecx],eax
                mov eax,[esi].abs_frame
                mov [ecx+4],ax
                .endc
            .endif
            .if ( ModuleInfo.sub_format == SFORMAT_MZ )
                mov [ecx],eax
                .if ( [ebx].frame_type == FRAME_GRP )
                    mov eax,[esi].sgroup
                    mov eax,[eax].asym.offs
                    shr eax,4
                    mov [ecx+4],ax
                .else
                    mov eax,[esi].start_offset
                    .if [esi].sgroup
                        mov edx,[esi].sgroup
                        add eax,[edx].asym.offs
                    .endif
                    shr eax,4
                    mov [ecx+4],ax
                .endif
                .endc
            .endif
        .default
            mov ecx,ModuleInfo.fmtopt
            lea edx,[ecx].format_options.formatname
            mov ecx,curr
            asmerr( 3019, edx, [ebx].type, [ecx].asym.name, [ebx].locofs )
        .endsw
    .endf
    .return( NOT_ERROR )
DoFixup endp

    assume esi:ptr module_info
    assume ebx:nothing
    assume edi:nothing

pe_create_MZ_header proc uses esi edi ebx modinfo:ptr module_info

    mov esi,modinfo
    .if ( Parse_Pass == PASS_1 )
        .if ( SymSearch( hdrname "1" ) == NULL )
            or [esi].pe_flags,PEF_MZHDR
        .endif
    .endif
    .if ( [esi].pe_flags & PEF_MZHDR )

        AddLineQueue( "option dotname" )
        AddLineQueueX("%s1 segment USE16 word %s", hdrname, hdrattr )

        .for ( ebx = 0, esi = &mzcode : mzcodelz[ebx] : ebx++ )

           .new buffer[64]:char_t
            lea edi,buffer
            mov edx,edi
            movzx ecx,mzcodelz[ebx]
            rep movsb
            mov B[edi],0

            AddLineQueue( edx )
        .endf
        AddLineQueue( esi )
        AddLineQueueX("%s1 ends", hdrname )
        RunLineQueue()
        .if SymSearch( hdrname "1" )
            .if ( [eax].asym.state == SYM_SEG )
                mov ecx,[eax].dsym.seginfo
                mov [ecx].seg_info.segtype,SEGTYPE_HDR
            .endif
        .endif
    .endif
    ret

pe_create_MZ_header endp

;; get/set value of @pe_file_flags variable

set_file_flags proc sym:ptr asym, opnd:ptr expr

   .return .if !SymSearch( hdrname "2" )

    mov ecx,[eax].dsym.seginfo
    mov edx,[ecx].seg_info.CodeBuffer
    movzx eax,[edx].IMAGE_PE_HEADER32.FileHeader.Characteristics

    .if ( opnd ) ;; set the value?

        mov ecx,opnd
        mov eax,[ecx].expr.value
        mov [edx].IMAGE_PE_HEADER32.FileHeader.Characteristics,ax
    .endif
    mov ecx,sym
    mov [ecx].asym.value,eax
    ret

set_file_flags endp

    assume esi:ptr seg_info

pe_create_PE_header proc public uses esi edi ebx

    .if ( Parse_Pass == PASS_1 )
        .if ( ModuleInfo._model != MODEL_FLAT )
            asmerr( 3002 )
        .endif
ifndef __ASMC64__
        .if ( ModuleInfo.defOfssize == USE64 )
endif
            mov ebx,IMAGE_PE_HEADER64
            lea edi,pe64def

            mov dword ptr pe64def.OptionalHeader.ImageBase,0x400000
            mov dword ptr pe64def.OptionalHeader.ImageBase[4],0
            mov pe64def.OptionalHeader.Subsystem,IMAGE_SUBSYSTEM_WINDOWS_CUI
            .if ( Options.pe_subsystem == 1 )
                mov pe64def.OptionalHeader.Subsystem,IMAGE_SUBSYSTEM_WINDOWS_GUI
            .endif
            .if ( ModuleInfo.sub_format == SFORMAT_64BIT )
                mov dword ptr pe64def.OptionalHeader.ImageBase,LOW32(0x140000000)
                mov dword ptr pe64def.OptionalHeader.ImageBase[4],HIGH32(0x140000000)
            .endif
ifndef __ASMC64__
        .else
            mov ebx,IMAGE_PE_HEADER32
            lea edi,pe32def
            mov pe32def.OptionalHeader.Subsystem,IMAGE_SUBSYSTEM_WINDOWS_CUI
            .if ( Options.pe_subsystem == 1 )
                mov pe32def.OptionalHeader.Subsystem,IMAGE_SUBSYSTEM_WINDOWS_GUI
            .endif
        .endif
endif

        .if !SymSearch( hdrname "2" )

            CreateIntSegment( hdrname "2", "HDR", 2, ModuleInfo.defOfssize, TRUE )

            mov [eax].asym.max_offset,ebx
            mov esi,[eax].dsym.seginfo
            mov ecx,ModuleInfo.flat_grp
            mov [esi].sgroup,ecx
            mov [esi].combine,COMB_ADDOFF  ;; PUBLIC
            mov [esi].characteristics,(IMAGE_SCN_MEM_READ shr 24)
            mov [esi].readonly,1
            mov [esi].bytes_written,ebx ;; ensure that ORG won't set start_loc (assemble.c, SetCurrOffset)

        .else
            .if ( [eax].asym.max_offset < ebx )
                mov [eax].asym.max_offset,ebx
            .endif
            mov esi,[eax].dsym.seginfo
            mov [esi].internal,TRUE
            mov [esi].start_loc,0
        .endif
        mov [esi].segtype,SEGTYPE_HDR
        mov [esi].CodeBuffer,LclAlloc( ebx )
        mov ebx,memcpy( eax, edi, ebx )
        time( &[ebx].IMAGE_PE_HEADER32.FileHeader.TimeDateStamp )
        CreateVariable( "@pe_file_flags", [edi].IMAGE_PE_HEADER32.FileHeader.Characteristics )
        .if eax
            or [eax].asym.flags,S_PREDEFINED
            lea ecx,set_file_flags
            mov [eax].asym.sfunc_ptr,ecx
        .endif
    .endif
    ret

pe_create_PE_header endp


define CHAR_READONLY ( IMAGE_SCN_MEM_READ shr 24 )

pe_create_section_table proc uses esi edi ebx

    local objtab:ptr dsym
    local bCreated:int_t

    mov bCreated,FALSE

    .if ( Parse_Pass == PASS_1 )
        .if SymSearch( hdrname "3" )
            mov edi,eax
            mov esi,[edi].dsym.seginfo
        .else
            mov bCreated,TRUE
            mov edi,CreateIntSegment( hdrname "3", "HDR", 2, ModuleInfo.defOfssize, TRUE )
            mov esi,[edi].dsym.seginfo
            mov [esi].sgroup,ModuleInfo.flat_grp
            mov [esi].combine,COMB_ADDOFF ;; PUBLIC
        .endif
        mov [esi].segtype,SEGTYPE_HDR

        .return .if ( !bCreated )

        mov objtab,edi

        ;; before objects can be counted, the segment types
        ;; SEGTYPE_CDATA ( for readonly segments ) &
        ;; SEGTYPE_RSRC ( for resource segments )
        ;; SEGTYPE_RELOC ( for relocations )
        ;; must be set  - also, init lname_idx field

        .for ( edi = SymTables[TAB_SEG*symbol_queue].head : edi : edi = [edi].dsym.next )

            mov esi,[edi].dsym.seginfo
            mov [esi].lname_idx,SEGTYPE_ERROR ;; use the highest index possible
            .if ( [esi].segtype == SEGTYPE_DATA )
                .if ( [esi].readonly || [esi].characteristics == CHAR_READONLY )
                    mov [esi].segtype,SEGTYPE_CDATA
                .elseif ( [esi].clsym )
                    mov ecx,[esi].clsym
                    .if ( strcmp( [ecx].asym.name, "CONST" ) == 0 )
                        mov [esi].segtype,SEGTYPE_CDATA
                    .endif
                .endif
            .elseif ( [esi].segtype == SEGTYPE_UNDEF )
                mov ebx,[edi].asym.name
                .if ( memcmp( ebx, ".rsrc", 5 ) == 0 )
                    .if ( B[ebx+5] == 0 || B[ebx+5] == '$' )
                        mov [esi].segtype,SEGTYPE_RSRC
                    .endif
                .elseif ( strcmp( ebx, ".reloc" ) == 0 )
                    mov [esi].segtype,SEGTYPE_RELOC
                .endif
            .endif
        .endf

        ;; count objects ( without header types )

        .for ( ebx = 1, esi = 0: ebx < SIZE_PEFLAT: ebx++ )

            .for ( edi = SymTables[TAB_SEG*symbol_queue].head : edi : edi = [edi].dsym.next )
                mov edx,[edi].dsym.seginfo
                .continue .if ( [edx].seg_info.segtype != flat_order[ebx*4] )
                .if ( [edi].asym.max_offset )
                    inc esi
                    .break
                .endif
            .endf
        .endf

        .if esi

            mov edi,objtab
            imul ebx,esi,IMAGE_SECTION_HEADER
            mov [edi].asym.max_offset,ebx

            ;; alloc space for 1 more section (.reloc)
            mov esi,[edi].dsym.seginfo
            mov [esi].CodeBuffer,LclAlloc( &[ebx+IMAGE_SECTION_HEADER] )
        .endif
    .endif
    ret
pe_create_section_table endp

expitem struct
name string_t ?
idx dd ?
expitem ends

compare_exp proc p1:ptr expitem, p2:ptr expitem
    mov ecx,p1
    mov edx,p2
    .return( strcmp( [ecx].expitem.name, [edx].expitem.name ) )
compare_exp endp

pe_emit_export_data proc uses esi edi ebx

  local timedate:int_32
  local cnt:int_t
  local name:string_t
  local pitems:ptr expitem

    .for ( edi = SymTables[TAB_PROC*symbol_queue].head, ebx = 0 : edi : edi = [edi].dsym.nextproc )
        mov edx,[edi].dsym.procinfo
        .if ( [edx].proc_info.flags & PROC_ISEXPORT )
            inc ebx
        .endif
    .endf
    .return .if ( ebx == 0 )

    lea esi,ModuleInfo.name
    AddLineQueue( "option dotname" )

    ;; create .edata segment
    AddLineQueueX( "%s segment dword %s", edataname, edataattr )
    time( &timedate )

    ;; create export directory: Characteristics, Timedate, MajMin, Name, Base, ...

    AddLineQueueX( "DD 0, 0%xh, 0, imagerel @%s_name, %u, %u, %u, imagerel @%s_func, imagerel @%s_names, imagerel @%s_nameord",
        timedate, esi, 1, ebx, ebx, esi, esi, esi )

    mov name,esi
    mov cnt,ebx

    ;; the name pointer table must be in ascending order!
    ;; so we have to fill an array of exports and sort it.

    imul ecx,ebx,expitem
    mov pitems,alloca(ecx)

    assume esi:ptr expitem
    .for ( edi = SymTables[TAB_PROC*symbol_queue].head,
           esi = eax, ebx = 0 : edi : edi = [edi].dsym.nextproc )

        mov edx,[edi].dsym.procinfo
        .if ( [edx].proc_info.flags & PROC_ISEXPORT )

            mov [esi].name,[edi].asym.name
            mov [esi].idx,ebx
            inc ebx
            add esi,expitem
        .endif
    .endf
    qsort( pitems, cnt, sizeof( expitem ), compare_exp )

    ;; emit export address table.
    ;; would be possible to just use the array of sorted names,
    ;; but we want to emit the EAT being sorted by address.

    AddLineQueueX( "@%s_func label dword", name )

    .for ( edi = SymTables[TAB_PROC*symbol_queue].head : edi : edi = [edi].dsym.nextproc )

        mov edx,[edi].dsym.procinfo
        .if ( [edx].proc_info.flags & PROC_ISEXPORT )

            AddLineQueueX( "DD imagerel %s", [edi].asym.name )
        .endif
    .endf

    ;; emit the name pointer table
    AddLineQueueX( "@%s_names label dword", name )

    .for ( esi = pitems, ebx = 0: ebx < cnt: ebx++, esi += expitem )
        AddLineQueueX( "DD imagerel @%s", [esi].name )
    .endf

    ;; ordinal table. each ordinal is an index into the export address table
    AddLineQueueX( "@%s_nameord label word", name )

    .for ( esi = pitems, ebx = 0: ebx < cnt: ebx++, esi += expitem )
        AddLineQueueX( "DW %u", [esi].idx )
    .endf

    ;; v2.10: name+ext of dll
    .for ( ebx = CurrFName[OBJ*4], ebx += strlen( ebx ): ebx > CurrFName[OBJ*4]: ebx-- )
        .break .if ( B[ebx] == '/' || B[ebx] == '\' || B[ebx] == ':' )
    .endf
    AddLineQueueX( "@%s_name DB '%s',0", name, ebx )

    .for ( edi = SymTables[TAB_PROC*symbol_queue].head : edi : edi = [edi].dsym.nextproc )

        mov edx,[edi].dsym.procinfo
        .if ( [edx].proc_info.flags & PROC_ISEXPORT )

            Mangle( edi, StringBufferEnd )
            mov ecx,StringBufferEnd
            .if Options.no_export_decoration
                mov ecx,[edi].asym.name
            .endif
            AddLineQueueX( "@%s DB '%s',0", [edi].asym.name, ecx )
        .endif
    .endf

    ;; exit .edata segment
    AddLineQueueX( "%s ends", edataname )
    RunLineQueue()
    ret

pe_emit_export_data endp

;; write import data.
;; convention:
;; .idata$2: import directory
;; .idata$3: final import directory NULL entry
;; .idata$4: ILT entry
;; .idata$5: IAT entry
;; .idata$6: strings

pe_emit_import_data proc uses esi edi ebx

    .new type:int_t = 0
    .new ptrtype:int_t = T_QWORD
    .new cpalign:string_t = "ALIGN(8)"
ifndef __ASMC64__
    .if ( ModuleInfo.defOfssize != USE64 )
        mov ptrtype,T_DWORD
        mov cpalign,&@CStr("ALIGN(4)")
    .endif
endif

    assume ebx:ptr dll_desc

    .for ( ebx = ModuleInfo.DllQueue: ebx: ebx = [ebx].next )

        .if ( [ebx].cnt )

            .new pdot:string_t
            .if ( !type )
                mov type,1
                AddLineQueue( "@LPPROC typedef ptr proc" )
                AddLineQueue( "option dotname" )
            .endif

            lea esi,[ebx].name

            ;; avoid . in IDs
            .if ( strchr( esi, '.') )
                mov B[eax],'_'
            .endif
            mov pdot,eax

            ;; import directory entry
            AddLineQueueX( "%s" IMPDIRSUF " segment dword %s", idataname, idataattr )
            AddLineQueueX( "DD imagerel @%s_ilt, 0, 0, imagerel @%s_name, imagerel @%s_iat", esi, esi, esi )
            AddLineQueueX( "%s" IMPDIRSUF " ends", idataname )

            ;; emit ILT
            AddLineQueueX( "%s" IMPILTSUF " segment %s %s", idataname, cpalign, idataattr )
            AddLineQueueX( "@%s_ilt label %r", esi, ptrtype )

            .for ( edi = SymTables[TAB_EXT*symbol_queue].head : edi : edi = [edi].dsym.next )
                .if ( [edi].asym.flags & S_IAT_USED && [edi].asym.dll == ebx )
                    AddLineQueueX( "@LPPROC imagerel @%s_name", [edi].asym.name )
                .endif
            .endf
            ;; ILT termination entry
            AddLineQueueX( "@LPPROC 0" )
            AddLineQueueX( "%s" IMPILTSUF " ends", idataname )

            ;; emit IAT
            AddLineQueueX( "%s" IMPIATSUF " segment %s %s", idataname, cpalign, idataattr )
            AddLineQueueX( "@%s_iat label %r", esi, ptrtype )

            .for ( edi = SymTables[TAB_EXT*symbol_queue].head : edi : edi = [edi].dsym.next )
                .if ( [edi].asym.flags & S_IAT_USED && [edi].asym.dll == ebx )
                    Mangle( edi, StringBufferEnd )
                    AddLineQueueX( "%s%s @LPPROC imagerel @%s_name",
                        ModuleInfo.imp_prefix, StringBufferEnd, [edi].asym.name )
                .endif
            .endf
            ;; IAT termination entry
            AddLineQueueX( "@LPPROC 0" )
            AddLineQueueX( "%s" IMPIATSUF " ends", idataname )

            ;; emit name table
            AddLineQueueX( "%s" IMPSTRSUF " segment word %s", idataname, idataattr )

            .for ( edi = SymTables[TAB_EXT*symbol_queue].head : edi : edi = [edi].dsym.next )
                .if ( [edi].asym.flags & S_IAT_USED && [edi].asym.dll == ebx )
                    AddLineQueueX( "@%s_name dw 0", [edi].asym.name )
                    AddLineQueueX( "db '%s',0", [edi].asym.name )
                    AddLineQueue( "even" )
                .endif
            .endf

            ;; dll name table entry
            .if ( pdot )
                mov edx,pdot
                mov B[edx],0
                inc edx
                AddLineQueueX( "@%s_%s_name db '%s.%s',0", esi, edx, esi, edx )
                mov eax,pdot
                mov B[eax],'.'
            .else
                AddLineQueueX( "@%s_name db '%s',0", esi, esi )
            .endif

            AddLineQueue( "even" );
            AddLineQueueX("%s" IMPSTRSUF " ends", idataname )

        .endif
    .endf
    .if ( is_linequeue_populated() )
        ;; import directory NULL entry
        AddLineQueueX("%s" IMPNDIRSUF " segment dword %s", idataname, idataattr )
        AddLineQueue( "DD 0, 0, 0, 0, 0" )
        AddLineQueueX("%s" IMPNDIRSUF " ends", idataname )
        RunLineQueue()
    .endif
    ret
pe_emit_import_data endp

get_bit proc fastcall value:int_t
    mov eax,-1
    .while( ecx )
        shr ecx,1
        inc eax
    .endw
    ret
get_bit endp

pe_get_characteristics proc fastcall segp:ptr dsym

    mov ecx,[ecx].dsym.seginfo
    mov eax,IMAGE_SCN_CNT_INITIALIZED_DATA or IMAGE_SCN_MEM_READ or IMAGE_SCN_MEM_WRITE

    .switch
    .case ( [ecx].seg_info.segtype == SEGTYPE_CODE )
        mov eax,IMAGE_SCN_CNT_CODE or IMAGE_SCN_MEM_EXECUTE or IMAGE_SCN_MEM_READ
        .endc
    .case ( [ecx].seg_info.segtype == SEGTYPE_BSS )
        mov eax,IMAGE_SCN_CNT_UNINITIALIZED_DATA or IMAGE_SCN_MEM_READ or IMAGE_SCN_MEM_WRITE
        .endc
    .case ( [ecx].seg_info.combine == COMB_STACK && [ecx].seg_info.bytes_written == 0 )
        mov eax,IMAGE_SCN_CNT_UNINITIALIZED_DATA or IMAGE_SCN_MEM_READ or IMAGE_SCN_MEM_WRITE
        .endc
    .case ( [ecx].seg_info.readonly )
        mov eax,IMAGE_SCN_CNT_INITIALIZED_DATA or IMAGE_SCN_MEM_READ
        .endc
    .case ( [ecx].seg_info.clsym )
        mov edx,[ecx].seg_info.clsym
        mov edx,[edx].asym.name
        .if dword ptr [edx] == 'SNOC' && word ptr [edx+4] == 'T'
            mov eax,IMAGE_SCN_CNT_INITIALIZED_DATA or IMAGE_SCN_MEM_READ
        .endif
    .endsw

    ;; manual characteristics set?

    .if ( [ecx].seg_info.characteristics )

        and eax,0x1FFFFFF ;; clear the IMAGE_SCN_MEM flags
        mov dl,[ecx].seg_info.characteristics
        and edx,0xFE
        shl edx,24
        or  eax,edx
    .endif
    ret

pe_get_characteristics endp

;; set base relocations

    assume ebx:ptr fixup
    assume esi:ptr seg_info

pe_set_base_relocs proc uses esi edi ebx reloc:ptr dsym

  .new cnt1:int_t = 0
  .new cnt2:int_t = 0
  .new ftype:int_t
  .new currpage:uint_32 = -1
  .new currloc:uint_32
  .new curr:ptr dsym
  .new fixp:ptr fixup
  .new baserel:ptr IMAGE_BASE_RELOCATION
  .new prel:ptr uint_16

    .for ( edi = SymTables[TAB_SEG*symbol_queue].head : edi : edi = [edi].dsym.next )

        mov esi,[edi].dsym.seginfo
        .continue .if ( [esi].segtype == SEGTYPE_HDR )

        .for ( ebx = [esi].head: ebx: ebx = [ebx].nextrlc )

            .switch ( [ebx].type )
            .case FIX_OFF16
            .case FIX_OFF32
            .case FIX_OFF64
                mov eax,[ebx].locofs
                and eax,0xFFFFF000
                add eax,[esi].start_offset
                .if ( eax != currpage )
                    mov currpage,eax
                    inc cnt2
                    .if ( cnt1 & 1 )
                        inc cnt1
                    .endif
                .endif
                inc cnt1
            .endsw
        .endf
    .endf

    imul ecx,cnt2,IMAGE_BASE_RELOCATION
    imul eax,cnt1,sizeof( uint_16 )
    add ecx,eax
    mov edi,reloc
    mov esi,[edi].dsym.seginfo
    mov [edi].asym.max_offset,ecx
    mov [esi].CodeBuffer,LclAlloc( ecx )
    mov baserel,eax
    mov [eax].IMAGE_BASE_RELOCATION.VirtualAddress,-1
    add eax,IMAGE_BASE_RELOCATION
    mov prel,eax

    .for ( edi = SymTables[TAB_SEG*symbol_queue].head : edi : edi = [edi].dsym.next )

        mov esi,[edi].dsym.seginfo
        .continue .if ( [esi].segtype == SEGTYPE_HDR )

        .for ( ebx = [esi].head: ebx: ebx = [ebx].nextrlc )

            xor ecx,ecx
            mov al,[ebx].type
            .switch al
            .case FIX_OFF16
                mov ecx,IMAGE_REL_BASED_LOW
                .endc
            .case FIX_OFF32
                mov ecx,IMAGE_REL_BASED_HIGHLOW
                .endc
            .case FIX_OFF64
                mov ecx,IMAGE_REL_BASED_DIR64
                .endc
            .endsw

            .if ( ecx )

                mov ftype,ecx
                mov eax,[ebx].locofs
                and eax,0xFFFFF000
                add eax,[esi].start_offset
                mov edx,baserel
                mov ecx,prel

                assume edx:ptr IMAGE_BASE_RELOCATION

                .if ( eax != [edx].VirtualAddress )
                    .if ( [edx].VirtualAddress != -1 )
                        ;; address of relocation header must be DWORD aligned
                        .if ( [edx].SizeOfBlock & 2 )
                            mov W[ecx],0
                            add ecx,2
                            add [edx].SizeOfBlock,sizeof( uint_16 )
                        .endif
                        mov edx,ecx
                        add ecx,sizeof( IMAGE_BASE_RELOCATION )
                    .endif
                    mov [edx].VirtualAddress,eax
                    mov [edx].SizeOfBlock,sizeof( IMAGE_BASE_RELOCATION )
                .endif

                add [edx].SizeOfBlock,sizeof( uint_16 )
                mov baserel,edx

                mov eax,[ebx].locofs
                and eax,0xfff
                mov edx,ftype
                shl edx,12
                or  eax,edx
                mov [ecx],ax
                add ecx,2
                mov prel,ecx

                assume edx:nothing
            .endif
        .endf
    .endf
    ret

pe_set_base_relocs endp

GHF macro x
ifndef __ASMC64__
 .if ( ModuleInfo.defOfssize == USE64 )
endif
    mov eax,ph64
  if sizeof(IMAGE_PE_HEADER64.x) lt 4
    movzx eax,[eax].IMAGE_PE_HEADER64.x
  elseif sizeof(IMAGE_PE_HEADER64.x) eq 4
    mov eax,[eax].IMAGE_PE_HEADER64.x
  else
    mov edx,dword ptr [eax].IMAGE_PE_HEADER64.x[4]
    mov eax,dword ptr [eax].IMAGE_PE_HEADER64.x
   endif
ifndef __ASMC64__
 .else
    mov eax,ph32
  if sizeof(IMAGE_PE_HEADER32.x) lt 4
    movzx eax,[eax].IMAGE_PE_HEADER32.x
  else
    mov eax,[eax].IMAGE_PE_HEADER32.x
  endif
 .endif
endif
 retm<eax>
 endm

;; set values in PE header
;; including data directories:
;; special section names:
;; .edata - IMAGE_DIRECTORY_ENTRY_EXPORT
;; .idata - IMAGE_DIRECTORY_ENTRY_IMPORT, IMAGE_DIRECTORY_ENTRY_IAT
;; .rsrc  - IMAGE_DIRECTORY_ENTRY_RESOURCE
;; .pdata - IMAGE_DIRECTORY_ENTRY_EXCEPTION (64-bit only)
;; .reloc - IMAGE_DIRECTORY_ENTRY_BASERELOC
;; .tls   - IMAGE_DIRECTORY_ENTRY_TLS

    assume ebx:nothing

pe_set_values proc uses esi edi ebx cp:ptr calc_param

    .new i:int_t
    .new falign:int_t
    .new malign:int_t
    .new ff:uint_16
    .new codebase:uint_32 = 0
    .new database:uint_32 = 0
    .new codesize:uint_32 = 0
    .new datasize:uint_32 = 0
    .new sizehdr:uint_32  = 0
    .new sizeimg:uint_32  = 0
    .new mzhdr:ptr dsym
    .new pehdr:ptr dsym
    .new objtab:ptr dsym
    .new reloc:ptr dsym = NULL
ifndef __ASMC64__
    .new ph32:ptr IMAGE_PE_HEADER32
endif
    .new ph64:ptr IMAGE_PE_HEADER64
    .new fh:ptr IMAGE_FILE_HEADER
    .new section:ptr IMAGE_SECTION_HEADER
    .new datadir:ptr IMAGE_DATA_DIRECTORY
    .new secname:string_t
    .new buffer[MAX_ID_LEN+1]:char_t

    mov mzhdr,  SymSearch( hdrname "1" )
    mov esi,[eax].dsym.seginfo
    mov pehdr,  SymSearch( hdrname "2" )
    mov objtab, SymSearch( hdrname "3" )

    ;; make sure all header objects are in FLAT group
    mov [esi].sgroup,ModuleInfo.flat_grp

    mov eax,pehdr
    mov esi,[eax].dsym.seginfo
    mov ecx,[esi].CodeBuffer
ifndef __ASMC64__
    .if ( ModuleInfo.defOfssize == USE64 )
endif
        mov ph64,ecx
        mov ff,[ecx].IMAGE_PE_HEADER64.FileHeader.Characteristics
ifndef __ASMC64__
    .else
        mov ph32,ecx
        mov ff,[ecx].IMAGE_PE_HEADER32.FileHeader.Characteristics
    .endif
endif
    .if ( !( eax & IMAGE_FILE_RELOCS_STRIPPED ) )
        mov reloc,CreateIntSegment( ".reloc", "RELOC", 2, ModuleInfo.defOfssize, TRUE )
        .if ( eax )
            mov esi,[eax].dsym.seginfo
            ;; make sure the section isn't empty ( true size will be calculated later )
            mov [eax].asym.max_offset,sizeof( IMAGE_BASE_RELOCATION )
            mov [esi].sgroup,ModuleInfo.flat_grp
            mov [esi].combine,COMB_ADDOFF
            mov [esi].segtype,SEGTYPE_RELOC
            mov [esi].characteristics,((IMAGE_SCN_MEM_DISCARDABLE or IMAGE_SCN_MEM_READ) shr 24 )
            mov [esi].bytes_written,sizeof( IMAGE_BASE_RELOCATION )
            ;; clear the additionally allocated entry in object table
            mov edx,objtab
            mov esi,[edx].dsym.seginfo
            mov edi,[edx].asym.max_offset
            add [edx].asym.max_offset,sizeof( IMAGE_SECTION_HEADER )
            add edi,[esi].CodeBuffer
            mov ecx,sizeof( IMAGE_SECTION_HEADER )
            xor eax,eax
            rep stosb
        .endif
    .endif

    ;; sort: header, executable, readable, read-write segments, resources, relocs

    .for ( ebx = 0: ebx < SIZE_PEFLAT: ebx++ )
        .for ( edi = SymTables[TAB_SEG*symbol_queue].head : edi : edi = [edi].dsym.next )
            mov esi,[edi].dsym.seginfo
            .if ( [esi].segtype == flat_order[ebx*4] )
                mov [esi].lname_idx,ebx
            .endif
        .endf
    .endf
    SortSegments( 2 )

    mov falign,get_bit( GHF( OptionalHeader.FileAlignment ) )
    mov malign,GHF( OptionalHeader.SectionAlignment )

    ;; assign RVAs to sections

    .for ( edi = SymTables[TAB_SEG*symbol_queue].head, ebx = -1 : edi : edi = [edi].dsym.next )
        mov esi,[edi].dsym.seginfo
        mov edx,cp
        .if ( [esi].lname_idx == SEGTYPE_ERROR || [esi].lname_idx != ebx )
            mov ebx,[esi].lname_idx
            mov [edx].calc_param.alignment,falign
            mov eax,malign

        .else
            mov eax,1
            mov cl,[esi].alignment
            shl eax,cl
            mov [edx].calc_param.alignment,0
        .endif
        dec eax
        mov ecx,eax
        not ecx
        add eax,[edx].calc_param.rva
        and eax,ecx
        mov [edx].calc_param.rva,eax
        CalcOffset( edi, edx )
    .endf

    mov ebx,cp
    .if ( reloc )
        pe_set_base_relocs( reloc )
        mov ecx,reloc
        mov esi,[ecx].dsym.seginfo
        mov eax,[ecx].asym.max_offset
        add eax,[esi].start_offset
        mov [ebx].calc_param.rva,eax
    .endif

    mov sizeimg,[ebx].calc_param.rva

    ;; set e_lfanew of dosstub to start of PE header
    mov eax,mzhdr
    mov ecx,pehdr
    .if ( [eax].asym.max_offset >= 0x40 )
        mov esi,[eax].dsym.seginfo
        mov edx,[esi].CodeBuffer
        mov esi,[ecx].dsym.seginfo
        mov eax,[esi].fileoffset
        mov [edx].IMAGE_DOS_HEADER.e_lfanew,eax
    .endif

    ;; set number of sections in PE file header (doesn't matter if it's 32- or 64-bit)
    mov esi,[ecx].dsym.seginfo
    mov edx,[esi].CodeBuffer
    lea ecx,[edx].IMAGE_PE_HEADER32.FileHeader
    mov fh,ecx
    mov edi,objtab
    mov eax,[edi].asym.max_offset
    mov ecx,sizeof( IMAGE_SECTION_HEADER )
    cdq
    div ecx
    mov ecx,fh
    mov [ecx].IMAGE_FILE_HEADER.NumberOfSections,ax

if RAWSIZE_ROUND
    mov [ebx].calc_param.rawpagesize,GHF(OptionalHeader.FileAlignment)
endif

    ;; fill object table values
    mov esi,[edi].dsym.seginfo
    mov section,[esi].CodeBuffer ;= (struct IMAGE_SECTION_HEADER *)objtab->e.seginfo->CodeBuffer;

    .for ( edi = SymTables[TAB_SEG*symbol_queue].head, ebx = -1 : edi : edi = [edi].dsym.next )
        mov esi,[edi].dsym.seginfo

        .continue .if ( [esi].segtype == SEGTYPE_HDR )
        .continue .if ( [edi].asym.max_offset == 0 ) ;; ignore empty sections

        assume ecx:ptr IMAGE_SECTION_HEADER

        .if ( [esi].lname_idx != ebx )
            mov ebx,[esi].lname_idx
            mov eax,[esi].aliasname
            .if eax == NULL
                ConvertSectionName( edi, NULL, &buffer )
            .endif
            mov secname,eax
            mov ecx,section
            strncpy( &[ecx].Name, secname, sizeof ( IMAGE_SECTION_HEADER.Name ) )

            mov ecx,section
            .if ( [esi].segtype != SEGTYPE_BSS )
                mov [ecx].PointerToRawData,[esi].fileoffset
            .endif
            mov [ecx].VirtualAddress,[esi].start_offset

            ;; file offset of first section in object table defines SizeOfHeader
            .if ( sizehdr == 0 )
                mov sizehdr,[esi].fileoffset
            .endif
        .endif
        pe_get_characteristics( edi )
        mov ecx,section
        or  [ecx].Characteristics,eax
        mov eax,[edi].asym.max_offset
        .if ( [esi].segtype != SEGTYPE_BSS )
            add [ecx].SizeOfRawData,eax
        .endif
        mov edx,[esi].start_offset
        sub edx,[ecx].VirtualAddress
        add eax,edx
        mov [ecx].Misc.VirtualSize,eax

        mov edx,[edi].dsym.next
        .if edx
            mov edx,[edx].dsym.seginfo
        .endif
        .if ( edx == NULL || [edx].seg_info.lname_idx != ebx )
if RAWSIZE_ROUND ;; AntiVir TR/Crypt.XPACK Gen
            mov eax,cp
            mov eax,[eax].calc_param.rawpagesize
            dec eax
            add [ecx].SizeOfRawData,eax
            not eax
            and [ecx].SizeOfRawData,eax
endif
            .if ( [ecx].Characteristics & IMAGE_SCN_MEM_EXECUTE )
                .if ( codebase == 0 )
                    mov codebase,[ecx].VirtualAddress
                .endif
                add codesize,[ecx].SizeOfRawData
            .endif
            .if ( [ecx].Characteristics & IMAGE_SCN_CNT_INITIALIZED_DATA )
                .if ( database == 0 )
                    mov database,[ecx].VirtualAddress
                .endif
                add datasize,[ecx].SizeOfRawData
            .endif
        .endif
        .if ( edx && [edx].seg_info.lname_idx != ebx )
            add section,IMAGE_SECTION_HEADER
        .endif
    .endf

    assume ecx:nothing


    .if ( ModuleInfo.start_label )

        mov eax,ModuleInfo.start_label
        mov edx,[eax].asym.segm
        mov esi,[edx].dsym.seginfo
        mov ecx,[esi].start_offset
        add ecx,[eax].asym.offs

ifndef __ASMC64__
        .if ( ModuleInfo.defOfssize == USE64 )
endif
            mov eax,ph64
            mov [eax].IMAGE_PE_HEADER64.OptionalHeader.AddressOfEntryPoint,ecx
ifndef __ASMC64__
        .else
            mov eax,ph32
            mov [eax].IMAGE_PE_HEADER32.OptionalHeader.AddressOfEntryPoint,ecx
        .endif
endif
    .else
        asmerr( 8009 )
    .endif

ifndef __ASMC64__
    .if ( ModuleInfo.defOfssize == USE64 )
endif
        mov ecx,ph64
if IMGSIZE_ROUND
        ;; round up the SizeOfImage field to page boundary
        mov eax,[ecx].IMAGE_PE_HEADER64.OptionalHeader.SectionAlignment
        dec eax
        mov edx,eax
        not edx
        add eax,sizeimg
        and eax,edx
        mov sizeimg,eax
endif
        mov [ecx].IMAGE_PE_HEADER64.OptionalHeader.SizeOfCode,codesize
        mov [ecx].IMAGE_PE_HEADER64.OptionalHeader.BaseOfCode,codebase
        mov [ecx].IMAGE_PE_HEADER64.OptionalHeader.SizeOfImage,sizeimg
        mov [ecx].IMAGE_PE_HEADER64.OptionalHeader.SizeOfHeaders,sizehdr
        mov datadir,&[ecx].IMAGE_PE_HEADER64.OptionalHeader.DataDirectory
ifndef __ASMC64__
    .else
        mov ecx,ph32
if IMGSIZE_ROUND
        ;; round up the SizeOfImage field to page boundary
        mov eax,[ecx].IMAGE_PE_HEADER32.OptionalHeader.SectionAlignment
        dec eax
        mov edx,eax
        not edx
        add eax,sizeimg
        and eax,edx
        mov sizeimg,eax
endif
        mov [ecx].IMAGE_PE_HEADER32.OptionalHeader.SizeOfCode,codesize
        mov [ecx].IMAGE_PE_HEADER32.OptionalHeader.SizeOfInitializedData,datasize
        mov [ecx].IMAGE_PE_HEADER32.OptionalHeader.BaseOfCode,codebase
        mov [ecx].IMAGE_PE_HEADER32.OptionalHeader.BaseOfData,database
        mov [ecx].IMAGE_PE_HEADER32.OptionalHeader.SizeOfImage,sizeimg
        mov [ecx].IMAGE_PE_HEADER32.OptionalHeader.SizeOfHeaders,sizehdr
        mov datadir,&[ecx].IMAGE_PE_HEADER32.OptionalHeader.DataDirectory
    .endif
endif

    ;; set export directory data dir value

    .if ( SymSearch( edataname ) )
        mov esi,[eax].dsym.seginfo
        mov edx,datadir
        mov [ecx][IMAGE_DIRECTORY_ENTRY_EXPORT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[eax].asym.max_offset
        mov [ecx][IMAGE_DIRECTORY_ENTRY_EXPORT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[esi].start_offset
    .endif

    ;; set import directory and IAT data dir value
    .if ( SymSearch( ".idata$" IMPDIRSUF ) )
       .new idata_null:ptr dsym
       .new idata_iat:ptr dsym
       .new size:uint_32
        mov edi,eax
        mov idata_null,SymSearch( ".idata$" IMPNDIRSUF ) ;; final NULL import directory entry
        mov idata_iat, SymSearch( ".idata$" IMPIATSUF )  ;; IAT entries

        mov ecx,idata_null
        mov esi,[ecx].dsym.seginfo
        mov eax,[esi].start_offset
        add eax,[ecx].asym.max_offset
        mov esi,[edi].dsym.seginfo
        sub eax,[esi].start_offset
        mov edx,datadir
        mov [edx][IMAGE_DIRECTORY_ENTRY_IMPORT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,eax
        mov [edx][IMAGE_DIRECTORY_ENTRY_IMPORT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[esi].start_offset

        mov ecx,idata_iat
        mov esi,[ecx].dsym.seginfo
        mov [edx][IMAGE_DIRECTORY_ENTRY_IAT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[esi].start_offset
        mov [edx][IMAGE_DIRECTORY_ENTRY_IAT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[ecx].asym.max_offset
    .endif

    ;; set resource directory data dir value
    .if ( SymSearch(".rsrc") )
        mov esi,[eax].dsym.seginfo
        mov edx,datadir
        mov [edx][IMAGE_DIRECTORY_ENTRY_RESOURCE*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[eax].asym.max_offset
        mov [edx][IMAGE_DIRECTORY_ENTRY_RESOURCE*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[esi].start_offset
    .endif

    ;; set relocation data dir value
    .if ( SymSearch(".reloc") )
        mov esi,[eax].dsym.seginfo
        mov edx,datadir
        mov [edx][IMAGE_DIRECTORY_ENTRY_BASERELOC*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[eax].asym.max_offset
        mov [edx][IMAGE_DIRECTORY_ENTRY_BASERELOC*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[esi].start_offset
    .endif

    ;; fixme: TLS entry is not written because there exists a segment .tls, but
    ;; because a _tls_used symbol is found ( type: IMAGE_THREAD_DIRECTORY )

    .if ( SymSearch(".tls") )
        mov esi,[eax].dsym.seginfo
        mov edx,datadir
        mov [edx][IMAGE_DIRECTORY_ENTRY_TLS*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[eax].asym.max_offset
        mov [edx][IMAGE_DIRECTORY_ENTRY_TLS*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[esi].start_offset
    .endif

ifndef __ASMC64__
    .if ( ModuleInfo.defOfssize == USE64 )
endif
        .if ( SymSearch( ".pdata" ) )
            mov esi,[eax].dsym.seginfo
            mov edx,datadir
            mov [edx][IMAGE_DIRECTORY_ENTRY_EXCEPTION*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[eax].asym.max_offset
            mov [edx][IMAGE_DIRECTORY_ENTRY_EXCEPTION*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[esi].start_offset
        .endif
        mov ecx,cp
        mov dword ptr [ecx].calc_param.imagebase64,GHF( OptionalHeader.ImageBase )
        mov dword ptr [ecx].calc_param.imagebase64[4],edx
ifndef __ASMC64__
    .else
        mov ecx,cp
        mov [ecx].calc_param.imagebase,GHF( OptionalHeader.ImageBase )
    .endif
endif
    ret
pe_set_values endp

;; v2.11: this function is called when the END directive has been found.
;; Previously the code was run inside EndDirective() directly.

pe_enddirhook proc modinfo:ptr module_info

    pe_create_MZ_header( modinfo )
    pe_emit_export_data()
    mov ecx,modinfo
    .if ( [ecx].module_info.DllQueue )
        pe_emit_import_data()
    .endif
    pe_create_section_table()
    .return( NOT_ERROR )

pe_enddirhook endp

;; write section contents
;; this is done after the last step only!

bin_write_module proc uses esi edi ebx modinfo:ptr module_info

    .new curr:ptr dsym
    .new size:uint_32
    .new sizetotal:uint_32
    .new i:int_t
    .new first:int_t
    .new sizeheap:uint_32
    .new pMZ:ptr IMAGE_DOS_HEADER
    .new reloccnt:uint_16
    .new sizemem:uint_32
    .new stackp:ptr dsym = NULL
    .new hdrbuf:ptr uint_8
    .new cp:calc_param = {0}

    mov cp.first,TRUE
    .for ( edi = SymTables[TAB_SEG*symbol_queue].head : edi : edi = [edi].dsym.next )
        mov esi,[edi].dsym.seginfo
        ;; reset the offset fields of segments
        ;; it was used to store the size in there
        mov [esi].start_offset,0
        ;; set STACK segment type
        .if ( [esi].combine == COMB_STACK )
            mov [esi].segtype,SEGTYPE_STACK
        .endif
    .endf

    ;; calculate size of header
    mov ebx,modinfo
    assume ebx:ptr module_info

    .if ( [ebx].sub_format == SFORMAT_MZ )
        mov reloccnt,GetSegRelocs( NULL )
        shl eax,2
        movzx edx,[ebx].mz_ofs_fixups
        add eax,edx
        movzx edx,[ebx].mz_alignment
        dec edx
        add eax,edx
        mov ecx,edx
        not ecx
        and eax,ecx
    .else
        xor eax,eax
    .endif
    mov cp.sizehdr,eax

    mov cp.fileoffset,eax
    .if ( eax )
        mov hdrbuf,LclAlloc( eax )
        memset( eax, 0, cp.sizehdr )
    .endif
    mov cp.entryoffset,-1

    ;; set starting offsets for all sections

    mov cp.rva,0
    .if ( [ebx].sub_format == SFORMAT_PE || [ebx].sub_format == SFORMAT_64BIT )
        .if ( ModuleInfo._model == MODEL_NONE )
            .return( asmerr( 2013 ) )
        .endif
        pe_set_values( &cp )
    .elseif ( [ebx].segorder == SEGORDER_DOSSEG )
        ;; for .DOSSEG, regroup segments (CODE, UNDEF, DATA, BSS)
        .for ( ebx = 0 : ebx < SIZE_DOSSEG : ebx++ )
            .for ( edi = SymTables[TAB_SEG*symbol_queue].head : edi : edi = [edi].dsym.next )
                mov esi,[edi].dsym.seginfo
                .continue .if ( [esi].segtype != dosseg_order[ebx*4] )
                CalcOffset( edi, &cp )
            .endf
        .endf
        SortSegments( 0 )
        mov ebx,modinfo
    .else ;; segment order .SEQ (default) and .ALPHA

        .if ( [ebx].segorder == SEGORDER_ALPHA )
            SortSegments( 1 )
        .endif
        .for ( edi = SymTables[TAB_SEG*symbol_queue].head : edi : edi = [edi].dsym.next )
            ;; ignore absolute segments
            CalcOffset( edi, &cp )
        .endf
    .endif
    ;; handle relocs
    .for ( edi = SymTables[TAB_SEG*symbol_queue].head : edi : edi = [edi].dsym.next )
        DoFixup( edi, &cp )
        mov esi,[edi].dsym.seginfo
        .if ( stackp == NULL && [esi].combine == COMB_STACK )
            mov stackp,edi
        .endif
    .endf
    ;; v2.04: return if any errors occured during fixup handling
    .return( ERROR ) .if ( [ebx].error_count )

    ;; for plain binaries make sure the start label is at
    ;; the beginning of the first segment
    .if ( [ebx].sub_format == SFORMAT_NONE )
        .if ( [ebx].start_label )
            mov eax,[ebx].start_label
            .if ( cp.entryoffset == -1 || cp.entryseg != [eax].asym.segm )
                .return( asmerr( 3003 ) )
            .endif
        .endif
    .endif

    mov sizetotal,GetImageSize( FALSE )

    ;; for MZ|PE format, initialize the header

    .if ( [ebx].sub_format == SFORMAT_MZ )

        ;; set fields in MZ header
        assume edi:ptr IMAGE_DOS_HEADER
        mov edi,hdrbuf
        mov [edi].e_magic,'M' + ('Z' shl 8)
        mov ecx,512
        mov eax,sizetotal
        cdq
        div ecx
        mov [edi].e_cblp,dx ;; bytes last page
        .if edx
            inc eax
        .endif
        mov [edi].e_cp,ax   ;; pages
        mov [edi].e_crlc,reloccnt
        mov eax,cp.sizehdr
        shr eax,4
        mov [edi].e_cparhdr,ax ;; size header in paras
        GetImageSize( TRUE )
        sub eax,sizetotal
        mov sizeheap,eax
        mov edx,eax
        shr eax,4
        and edx,0x0F
        .ifnz
            inc eax
        .endif
        mov [edi].e_minalloc,ax ;; heap min
        .if ( ax < [ebx].mz_heapmin )
            mov [edi].e_minalloc,[ebx].mz_heapmin
        .endif
        mov [edi].e_maxalloc,[ebx].mz_heapmax ;; heap max
        .if ( ax < [edi].e_minalloc )
            mov [edi].e_maxalloc,[edi].e_minalloc
        .endif

        ;; set stack if there's one defined

        .if ( stackp )
            mov ecx,stackp
            mov esi,[ecx].dsym.seginfo
            mov eax,[esi].start_offset
            .if ( [esi].sgroup )
                mov edx,[esi].sgroup
                add eax,[edx].asym.offs
            .endif
            xor edx,edx
            .if eax & 0x0F
                inc edx
            .endif
            shr eax,4
            add eax,edx
            mov [edi].e_ss,ax ;; SS
            ;; v2.11: changed sym.offset to sym.max_offset
            mov [edi].e_sp,[ecx].asym.max_offset ;; SP
        .else
            asmerr( 8010 )
        .endif
        mov [edi].e_csum,0 ;; checksum

        ;; set entry CS:IP if defined

        .if ( [ebx].start_label )

            mov ecx,[ebx].start_label
            mov edx,[ecx].asym.segm
            mov esi,[edx].dsym.seginfo
            .if ( [esi].sgroup )
                mov eax,[esi].sgroup
                mov eax,[eax].asym.offs
                mov edx,eax
                shr edx,4
                and eax,0x0F
                add eax,[esi].start_offset
                add eax,[ecx].asym.offs
                mov [edi].e_ip,ax
                mov [edi].e_cs,dx
            .else
                mov eax,[esi].start_offset
                mov edx,eax
                shr edx,4
                and eax,0x0F
                add eax,[ecx].asym.offs
                mov [edi].e_ip,ax
                mov [edi].e_cs,dx
            .endif
        .else
            asmerr( 8009 )
        .endif
        mov [edi].e_lfarlc,[ebx].mz_ofs_fixups
        add eax,hdrbuf
        GetSegRelocs( eax )
    .endif

    assume edi:nothing

    .if( CurrFile[LST*4] )
        ;; go to EOF
        fseek( CurrFile[LST*4], 0, SEEK_END )
        LstNL()
        LstNL()
        LstPrintf( szCaption )
        LstNL()
        LstNL()
        LstPrintf( szCaption2 )
        LstNL()
        LstPrintf( szSep )
        LstNL()
    .endif

    .if ( cp.sizehdr )
        .if ( fwrite( hdrbuf, 1, cp.sizehdr, CurrFile[OBJ*4] ) != cp.sizehdr )
            WriteError()
        .endif
        LstPrintf( szSegLine, szHeader, 0, 0, cp.sizehdr, 0 )
        LstNL()
    .endif

    ;; write sections

    .for ( edi = SymTables[TAB_SEG*symbol_queue].head, first = TRUE : edi : edi = [edi].dsym.next )

        mov esi,[edi].dsym.seginfo
        .continue .if ( [esi].segtype == SEGTYPE_ABS )

        .if ( ( ModuleInfo.sub_format == SFORMAT_PE || ModuleInfo.sub_format == SFORMAT_64BIT ) && \
            ( [esi].segtype == SEGTYPE_BSS || [esi].info ) )
            xor eax,eax
        .else
            mov eax,[edi].asym.max_offset
            sub eax,[esi].start_loc
        .endif
        mov size,eax
        .if first == 0
            mov eax,[edi].asym.max_offset
        .endif
        mov sizemem,eax
        ;; if no bytes have been written to the segment, check if there's
        ;; any further segments with bytes set. If no, skip write!
        .if ( [esi].bytes_written == 0 )
            .for ( edx = [edi].dsym.next: edx: edx = [edx].dsym.next )
                mov ecx,[edx].dsym.seginfo
                .break .if ( [ecx].seg_info.bytes_written )
            .endf
            .if ( !edx )
                mov size,edx
            .endif
        .endif
        mov ecx,[esi].start_offset
        .if first
            mov ecx,[esi].start_offset
            add ecx,[esi].start_loc
        .endif
        LstPrintf( szSegLine, [edi].asym.name, [esi].fileoffset, ecx, size, sizemem )
        LstNL()
        .if ( size && [esi].CodeBuffer )
            fseek( CurrFile[OBJ*4], [esi].fileoffset, SEEK_SET )
            .if ( fwrite( [esi].CodeBuffer, 1, size, CurrFile[OBJ*4] ) != size )
                WriteError()
            .endif
        .endif
        mov first,FALSE
    .endf
    .if ( [ebx].sub_format == SFORMAT_PE || ModuleInfo.sub_format == SFORMAT_64BIT )
        mov size,ftell( CurrFile[OBJ*4] )
        mov eax,cp.rawpagesize
        dec eax
        .if ( size & ( eax ) )
            lea ecx,[eax+1]
            and eax,size
            sub ecx,eax
            mov size,ecx
            memset( alloca(ecx), 0, size )
            fwrite( eax, 1, size, CurrFile[OBJ*4] )
        .endif
    .endif
    LstPrintf( szSep )
    LstNL()
    .if ( [ebx].sub_format == SFORMAT_MZ )
        mov eax,sizetotal
        sub eax,cp.sizehdr
        add sizeheap,eax
    .elseif ( [ebx].sub_format == SFORMAT_PE || ModuleInfo.sub_format == SFORMAT_64BIT )
        mov sizeheap,cp.rva
    .else
        mov sizeheap,GetImageSize( TRUE )
    .endif
    LstPrintf( szTotal, " ", sizetotal, sizeheap )
    LstNL()

    .return( NOT_ERROR )

bin_write_module endp

bin_check_external proc modinfo:ptr module_info

    .for ( edx = SymTables[TAB_EXT*symbol_queue].head : edx : edx = [edx].dsym.next )
        .if ( !( [edx].asym.sflags & S_WEAK ) || [edx].asym.flags & S_USED )
            .return( asmerr( 2014, [edx].asym.name ) )
        .endif
    .endf
    .return( NOT_ERROR )

bin_check_external endp

bin_init proc public uses esi edi ebx modinfo:ptr module_info

    mov ebx,modinfo
    mov [ebx].WriteModule,bin_write_module
    mov [ebx].Pass1Checks,bin_check_external
    mov al,[ebx].sub_format
    .switch al
ifndef __ASMC64__
    .case SFORMAT_MZ
        memcpy( &[ebx].mz_ofs_fixups, &mzdata, sizeof( MZDATA ) )
        .endc
endif
    .case SFORMAT_PE
    .case SFORMAT_64BIT
        mov [ebx].EndDirHook,pe_enddirhook ;; v2.11
        .endc
    .endsw
    ret

bin_init endp

    end
