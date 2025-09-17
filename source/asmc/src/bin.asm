; BIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

include asmc.inc
include memalloc.inc
include parser.inc
include fixup.inc
include omfspec.inc
include listing.inc
include coffspec.inc
include input.inc
include segment.inc
include expreval.inc
include pespec.inc
include qfloat.inc
include lqueue.inc

define ADD_MANIFESTFILE ; Add .pragma comment(linker, "/manifestdependency: ..."

define RAWSIZE_ROUND 1 ;; SectionHeader.SizeOfRawData is multiple FileAlign. Required by MS COFF spec
define IMGSIZE_ROUND 1 ;; OptionalHeader.SizeOfImage is multiple ObjectAlign. Required by MS COFF spec

IMPDIRSUF  equ <"2"> ;; import directory segment suffix
IMPNDIRSUF equ <"3"> ;; import data null directory entry segment suffix
IMPILTSUF  equ <"4"> ;; ILT segment suffix
IMPIATSUF  equ <"5"> ;; IAT segment suffix
IMPSTRSUF  equ <"6"> ;; import strings segment suffix

; pespec.inc contains MZ header declaration

include pespec.inc

SortSegments proto __ccall :int_t

.data

; if the structure changes, option.c, SetMZ() might need adjustment!

MZDATA      struct
ofs_fixups  dw ?    ; offset start fixups
alignment   dw ?    ; header alignment: 16,32,64,128,256,512
heapmin     dw ?
heapmax     dw ?
MZDATA      ends

; default values for OPTION MZ
ifndef ASMC64
mzdata MZDATA { 0x1E, 0x10, 0, 0xFFFF }
endif

; these strings are to be moved to ltext.inc

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
    start_loc       uint_32 ?
calc_param          ends

dosseg_order seg_type \ ; reorder segments for DOSSEG:
    SEGTYPE_CODE,       ; 1. code
    SEGTYPE_UNDEF,      ; 2. unknown
    SEGTYPE_DATA,       ; 3. initialized data
    SEGTYPE_BSS,        ; 4. uninitialized data
    SEGTYPE_STACK,      ; 5. stack
    SEGTYPE_ABS

flat_order seg_type \
    SEGTYPE_HDR,
    SEGTYPE_UNDEF,
    SEGTYPE_CODE,
    SEGTYPE_CODE16,
    SEGTYPE_CDATA,
    SEGTYPE_DATA,
    SEGTYPE_BSS,
    SEGTYPE_STACK,
    SEGTYPE_RSRC,
    SEGTYPE_RELOC

SIZE_DOSSEG equ ( sizeof( dosseg_order ) / sizeof( seg_type ) )
SIZE_PEFLAT equ ( sizeof( flat_order ) / sizeof( seg_type ) )

.enum pe_flags_values {
    PEF_MZHDR = 0x01,  ; 1=create mz header
    }

hdrname     equ <".hdr$">
hdrattr     equ <"read public 'HDR'">
edataname   equ <".edata">
edataattr   equ <"FLAT read public alias('.rdata') 'DATA'">

idataname   equ <".idata$">
idataattr   equ <"FLAT read public alias('.rdata') 'DATA'">

define PE_UNDEF_BASE 0xffffffff
define PE32_DEF_BASE_EXE 0x400000
define PE32_DEF_BASE_DLL 0x10000000
define PE64_DEF_BASE_EXE 0x140000000
define PE64_DEF_BASE_DLL 0x180000000

    align size_t

ifndef ASMC64

; default 32-bit PE header

pe32def IMAGE_PE_HEADER32 {
    'EP',
    { IMAGE_FILE_MACHINE_I386, 0, 0, 0, 0, sizeof( IMAGE_OPTIONAL_HEADER32 ),
      IMAGE_FILE_RELOCS_STRIPPED or IMAGE_FILE_EXECUTABLE_IMAGE or \
      IMAGE_FILE_LINE_NUMS_STRIPPED or IMAGE_FILE_LOCAL_SYMS_STRIPPED or \
      IMAGE_FILE_32BIT_MACHINE },
    { IMAGE_NT_OPTIONAL_HDR32_MAGIC,
      5,1,0,0,0,0,0,0,  ;; linkervers maj/min, sizeof code/init/uninit, entrypoint, base code/data
      PE_UNDEF_BASE,    ;; image base
      0x1000, 0x200,    ;; SectionAlignment, FileAlignment
      4,0,0,0,4,0,      ;; OSversion maj/min, Imagevers maj/min, Subsystemvers maj/min
      0,0,0,0,          ;; Win32vers, sizeofimage, sizeofheaders, checksum
      IMAGE_SUBSYSTEM_WINDOWS_CUI,0,  ;; subsystem, dllcharacteristics
      0x100000,0x1000,  ;; sizeofstack reserve/commit
      0x100000,0x1000,  ;; sizeofheap reserve/commit
      0, IMAGE_NUMBEROF_DIRECTORY_ENTRIES, ;; loaderflags, numberofRVAandSizes
    }}
endif

; default 64-bit PE header

pe64def IMAGE_PE_HEADER64 {
    'EP',
    { IMAGE_FILE_MACHINE_AMD64, 0, 0, 0, 0, sizeof( IMAGE_OPTIONAL_HEADER64 ),
      IMAGE_FILE_RELOCS_STRIPPED or IMAGE_FILE_EXECUTABLE_IMAGE or \
      IMAGE_FILE_LINE_NUMS_STRIPPED or IMAGE_FILE_LOCAL_SYMS_STRIPPED or \
      IMAGE_FILE_LARGE_ADDRESS_AWARE or IMAGE_FILE_32BIT_MACHINE },
    { IMAGE_NT_OPTIONAL_HDR64_MAGIC,
      5,1,0,0,0,0,0,    ;; linkervers maj/min, sizeof code/init data/uninit data, entrypoint, base code RVA
      PE_UNDEF_BASE,    ;; image base
      0x1000, 0x200,    ;; SectionAlignment, FileAlignment
      4,0,0,0,4,0,      ;; OSversion maj/min, Imagevers maj/min, Subsystemvers maj/min
      0,0,0,0,          ;; Win32vers, sizeofimage, sizeofheaders, checksum
      IMAGE_SUBSYSTEM_WINDOWS_CUI,0,  ;; subsystem, dllcharacteristics
      0x100000,0x1000,  ;; sizeofstack reserve/commit
      0x100000,0x1000,  ;; sizeofheap reserve/commit
      0, IMAGE_NUMBEROF_DIRECTORY_ENTRIES, ;; loaderflags, numberofRVAandSizes
    } }

    .code

    B equ <byte ptr>
    W equ <word ptr>

    option proc:private

    ; calculate starting offset of segments and groups

    assume rbx:ptr calc_param
    assume rdi:segment_t

CalcOffset proc fastcall uses rsi rdi rbx curr:asym_t, cp:ptr calc_param

    mov rsi,rcx
    mov rbx,rdx
    mov rdi,[rsi].asym.seginfo

    .if ( [rdi].segtype == SEGTYPE_ABS )

        imul eax,[rdi].abs_frame,16
        mov [rdi].start_offset,eax
       .return
    .elseif ( [rdi].information )
       .return
    .endif

    ; v2.19: mz format and org in first segment (org1.asm).

    .if ( [rbx].first && MODULE.sub_format != SFORMAT_NONE )
        mov [rbx].start_loc,[rdi].start_loc
    .elseif ( [rbx].first == FALSE && [rbx].start_loc )
        add [rbx].fileoffset,[rbx].start_loc
        mov [rbx].start_loc,0
    .endif

    mov eax,1
    mov cl,[rbx].alignment
    .if ( cl < [rdi].alignment )
        mov cl,[rdi].alignment
    .endif
    shl eax,cl
    mov ecx,eax
    neg ecx
    dec eax
    add eax,[rbx].fileoffset
    and eax,ecx
    sub eax,[rbx].fileoffset

    ; v2.19, format -bin: don't align fileoffset for segments with RVA alignment [ALIGN(x,v)]

    .if ( !( [rdi].align_rva ) )

        add [rbx].fileoffset,eax
    .endif

    mov rdx,[rdi].sgroup

    .if ( MODULE.sub_format == SFORMAT_PE || MODULE.sub_format == SFORMAT_64BIT )

        ; v2.24

        mov ecx,[rbx].rva
        add [rbx].rva,[rsi].asym.max_offset

    .elseif ( rdx == NULL )

        mov ecx,[rbx].fileoffset
        sub ecx,[rbx].sizehdr

    .elseif ( [rdx].asym.total_size == 0 )

        mov ecx,[rbx].fileoffset
        sub ecx,[rbx].sizehdr
        mov [rdx].asym.offs,ecx
        mov [rdx].asym.included,1
        xor ecx,ecx

    .else

        ; v2.12: the old way wasn't correct. if there's a segment between the
        ; segments of a group, it affects the offset as well ( if it
        ; occupies space in the file )! the value stored in grp->sym.total_size
        ; is no longer used (or, more exactly, used as a flag only).

        mov ecx,[rdx].asym.total_size
        add ecx,eax
    .endif
    mov [rdi].start_offset,ecx

    ; v2.04: added
    ; v2.05: this addition did mess sample Win32_5.asm, because the
    ; "empty" alignment sections are now added to <fileoffset>.
    ; todo: VA in binary map is displayed wrong.

    .if ( [rbx].first == FALSE )

        ; v2.05: do the reset more carefully.
        ; Do reset start_loc only if
        ; - segment is in a group and
        ; - group isn't FLAT or segment's name contains '$'

        .if ( rdx && rdx != MODULE.flat_grp )
            mov [rdi].start_loc,0
        .endif
    .endif

    mov [rdi].fileoffset,[rbx].fileoffset
    mov eax,[rsi].asym.max_offset
    sub eax,[rdi].start_loc

    .if ( MODULE.sub_format == SFORMAT_NONE )

        add [rbx].fileoffset,eax
        .if ( [rbx].first )
            mov [rbx].imagestart,[rdi].start_loc
        .endif

        ; there's no real entry address for BIN, therefore the
        ; start label must be at the very beginning of the file

        .if ( [rbx].entryoffset == -1 )

            mov [rbx].entryoffset,ecx
            mov [rbx].entryseg,rsi
        .endif

    .elseif ( [rdi].segtype != SEGTYPE_BSS )
        add [rbx].fileoffset,eax
    .endif

    .if rdx

        add ecx,[rsi].asym.max_offset
        mov [rdx].asym.total_size,ecx

        ; v2.07: for 16-bit groups, ensure that it fits in 64 kB

        .if ( ecx > 0x10000 && [rdx].asym.Ofssize == USE16 )
            asmerr( 8003, [rdx].asym.name )
        .endif
    .endif
    mov [rbx].first,FALSE
    ret

CalcOffset endp


; if pDst==NULL: count the number of segment related fixups
; if pDst!=NULL: write segment related fixups

    assume rbx:ptr fixup

GetSegRelocs proc __ccall uses rsi rdi rbx pDst:ptr uint_16

    .new count:int_t = 0

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].asym.next )

        mov rdi,[rsi].asym.seginfo
        .if ( [rdi].segtype == SEGTYPE_ABS )
            .continue
        .endif

        .for ( rbx = [rdi].head : rbx : rbx = [rbx].nextrlc )

            .switch [rbx].type
            .case FIX_PTR32
            .case FIX_PTR16
            .case FIX_SEG

                ; ignore fixups for absolute segments

                mov rcx,[rbx].sym
                .if ( rcx )

                    mov rcx,[rcx].asym.segm
                    .if ( rcx && [rcx].asym.seginfo )

                        mov rax,[rcx].asym.seginfo
                       .endc .if ( [rax].seg_info.segtype == SEGTYPE_ABS )
                    .endif
                .endif

                inc count

                .if ( pDst )

                    ; v2.04: fixed

                    mov ecx,[rdi].start_offset
                    mov eax,ecx
                    and ecx,0xf
                    add ecx,[rbx].locofs
                    shr eax,4
                    mov rdx,[rdi].sgroup
                    .if rdx
                        mov edx,[rdx].asym.offs
                        and edx,0xf
                        add ecx,edx
                        mov rdx,[rdi].sgroup
                        mov edx,[rdx].asym.offs
                        shr edx,4
                        add eax,edx
                    .endif

                    .if [rbx].type == FIX_PTR16
                        add ecx,2
                    .elseif [rbx].type == FIX_PTR32
                        add ecx,4
                    .endif

                    ; offset may be > 64 kB

                    .while ecx >= 0x10000

                        sub ecx,16
                        inc eax
                    .endw

                    mov rdx,pDst
                    mov [rdx],cx
                    mov [rdx+2],ax
                    add pDst,4
                .endif
                .endc
            .endsw
        .endf
    .endf
    .return( count )

GetSegRelocs endp


; get image size.
; memimage=FALSE: get size without uninitialized segments (BSS and STACK)
; memimage=TRUE: get full size

GetImageSize proc __ccall uses rsi rdi memimage:int_t

    .new first:uint_32 = TRUE

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head, eax = 0 : rsi : rsi = [rsi].asym.next )

        mov rdi,[rsi].asym.seginfo
        .if ( [rdi].segtype == SEGTYPE_ABS || [rdi].information )
            .continue
        .endif

        .if ( memimage == FALSE )

            .if ( [rdi].bytes_written == 0 )

                .for ( rcx = [rsi].asym.next : rcx : rcx = [rcx].asym.next )

                    mov rdx,[rcx].asym.seginfo
                   .break .if ( [rdx].seg_info.bytes_written )
                .endf
                .break .if !rcx ; done, skip rest of segments!
            .endif
        .endif

        mov eax,[rsi].asym.max_offset
        add eax,[rdi].fileoffset

        ; for format -bin, skip the first start_loc

        .if ( first && MODULE.sub_format == SFORMAT_NONE )
            sub eax,[rdi].start_loc
        .endif
        mov first,FALSE
    .endf
    ret

GetImageSize endp


; micro-linker. resolve internal fixups.
;
; handle the fixups contained in a segment

DoFixup proc __ccall uses rsi rdi rbx curr:asym_t, cp:ptr calc_param

   .new value:uint_32
   .new value64:uint_64
   .new offs:uint_32

    ldr rsi,curr
    mov rdi,[rsi].asym.seginfo

    .if ( [rdi].segtype == SEGTYPE_ABS )
        .return( NOT_ERROR )
    .endif

    .for ( rbx = [rdi].head : rbx : rbx = [rbx].nextrlc )

        mov eax,[rbx].locofs
        sub eax,[rdi].start_loc
        add rax,[rdi].CodeBuffer
        mov rcx,[rbx].sym

        .new codeptr:ptr = rax

        .if ( rcx && ( [rcx].asym.segm || [rcx].asym.isvariable ) )

            ; assembly time variable (also $ symbol) in reloc?
            ; v2.07: moved inside if-block, using new local var "offset"

            .if ( [rcx].asym.isvariable )

                mov rsi,[rbx].segment_var
                mov offs,0

            .else
                mov rsi,[rcx].asym.segm
                mov offs,[rcx].asym.offs
            .endif
            .new segm:asym_t = rsi

            mov rsi,[rsi].asym.seginfo
            assume rsi:segment_t

            ; the offset result consists of
            ; - the symbol's offset
            ; - the fixup's offset (usually the displacement )
            ; - the segment/group offset in the image

            mov al,[rbx].type
            .switch al

            .case FIX_OFF32_IMGREL

                mov eax,[rbx].offs
                add eax,offs
                add eax,[rsi].start_offset
                mov rdx,cp
                sub eax,[rdx].calc_param.imagestart
                mov value,eax
               .endc

            .case FIX_OFF32_SECREL

                mov eax,[rbx].offs
                add eax,offs
                sub eax,[rsi].start_loc
                mov value,eax

                ; check if symbol's segment name contains a '$'.
                ; If yes, search the segment without suffix.

                mov rcx,segm
                .if ( tstrchr( [rcx].asym.name, '$' ) )

                    mov rcx,segm
                    sub rax,[rcx].asym.name

                    .for ( rdx = SymTables[TAB_SEG*symbol_queue].head : rdx : rdx = [rdx].asym.next )

                        .if ( eax == [rdx].asym.name_size )

                            push    rsi
                            push    rdi
                            mov     rcx,segm
                            mov     rdi,[rdx].asym.name
                            mov     rsi,[rcx].asym.name
                            mov     ecx,eax
                            repz    cmpsb
                            pop     rdi
                            pop     rsi
                            .ifz
                                mov eax,[rbx].offs
                                add eax,offs
                                add eax,[rsi].start_offset
                                mov rcx,[rdx].asym.seginfo
                                sub eax,[rcx].seg_info.start_offset
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

                ; v1.96: special handling for "relative" fixups
                ; v2.28: removed fixup->offset..

                mov eax,[rsi].start_offset
                add eax,offs
                mov value,eax
               .endc

            .default

                ; v2.19: ensure that all DIR32 offsets have image base added ( even if segment is 16-bit )
                ; Actually, this "moves" the segment to FLAT - and shows up accordingly in the listing.
                ; Perhaps there's a better fix possible?

                .if ( MODULE.sub_format == SFORMAT_PE )
                    .if ( [rsi].sgroup == NULL )
                        mov [rsi].sgroup,MODULE.flat_grp
                    .endif
                    .if ( [rsi].sgroup == MODULE.flat_grp && [rbx].frame_type == FRAME_SEG )
                        mov [rbx].frame_type,FRAME_GRP
                    .endif
                .endif

                mov rcx,[rsi].sgroup
                .if ( rcx && [rbx].frame_type != FRAME_SEG )

                    mov eax,[rcx].asym.offs
                    and eax,0x0F
                    add eax,[rsi].start_offset
                    add eax,[rbx].offs
                    add eax,offs
                    mov value,eax

                    .if ( MODULE.sub_format == SFORMAT_PE || MODULE.sub_format == SFORMAT_64BIT )

                        mov rcx,cp
                        .if ( [rdi].Ofssize == USE64 )
ifdef _WIN64
                            mov eax,value
                            add rax,[rcx].calc_param.imagebase64
                            mov value64,rax
else
                            mov eax,dword ptr [rcx].calc_param.imagebase64
                            mov edx,dword ptr [rcx].calc_param.imagebase64[4]
                            add eax,value
                            adc edx,0
                            mov dword ptr value64,eax
                            mov dword ptr value64[4],edx
endif
                        .endif
                        add value,[rcx].calc_param.imagebase
                    .endif

                .else

                    ; v2.13: if frametype == FRAME_GRP, add full segment offset (see fixup5a.asm)

                    mov eax,[rbx].offs
                    add eax,offs
                    .if ( [rbx].frame_type == FRAME_GRP )

                        add eax,[rsi].start_offset

                    .else ; v2.13: use lower 4 bits of group offset

                        xor edx,edx
                        .if ( rcx )
                            mov edx,[rcx].asym.offs
                            and edx,0xF
                        .endif
                        mov ecx,[rsi].start_offset
                        and ecx,0xF
                        add eax,edx
                        add eax,ecx
                    .endif
                    mov value,eax
                .endif
                .endc
            .endsw

        .else

            mov segm,NULL
            mov value,0

            ; v2.14: use fixup->offset; see flatgrp2.asm. todo: check if this should be done generally

            .if ( [rbx].sym == NULL )
                mov value,[rbx].offs
            .endif

            ; v2.14: if a segment is given, find it - we just have the segment index

            .if ( [rbx].frame_type == FRAME_SEG )

                .for ( rcx = SymTables[TAB_SEG*symbol_queue].head : rcx : rcx = [rcx].asym.next )

                    mov rdx,[rcx].asym.seginfo

                    .if ( [rdx].seg_info.seg_idx == [rbx].frame_datum )

                        ; if the segment is in a group, add the segment's start offset

                        .if ( [rdx].seg_info.sgroup )

                            add value,[rdx].seg_info.start_offset

                            ; v2.15: add imagebase. see lea3.asm

                            .if ( MODULE.sub_format == SFORMAT_PE )

                                mov rcx,cp
                                .if ( [rdi].Ofssize == USE64 )
ifdef _WIN64
                                    mov eax,value
                                    add rax,[rcx].calc_param.imagebase64
                                    mov value64,rax
else
                                    mov eax,dword ptr [rcx].calc_param.imagebase64
                                    mov edx,dword ptr [rcx].calc_param.imagebase64[4]
                                    add eax,value
                                    adc edx,0
                                    mov dword ptr value64,eax
                                    mov dword ptr value64[4],edx
endif
                                .endif
                                add value,[rcx].calc_param.imagebase
                            .endif
                        .endif
                        .break
                    .endif
                .endf
            .endif
        .endif

        mov   rcx,codeptr
        mov   eax,value
        movzx edx,[rbx].type

        .switch edx
        .case FIX_RELOFF8
            sub eax,[rbx].locofs
            sub eax,[rdi].start_offset
            dec eax
            add [rcx],al
           .endc
        .case FIX_RELOFF16
            sub eax,[rbx].locofs
            sub eax,[rdi].start_offset
            sub eax,2
            add [rcx],ax
           .endc
        .case FIX_RELOFF32

            ; adjust the location for EIP-related offsets if USE64

            .if ( [rdi].Ofssize == USE64 )
                movzx edx,[rbx].addbytes
                sub edx,4
                add [rbx].locofs,edx
            .endif

            ; changed in v1.95

            sub eax,[rbx].locofs
            sub eax,[rdi].start_offset
            sub eax,4
            add [rcx],eax
           .endc
        .case FIX_OFF8
            mov [rcx],al
           .endc
        .case FIX_OFF16
            mov [rcx],ax
           .endc
        .case FIX_OFF32
if 0
            .if ( rdi && [rdi].Ofssize == USE64 )
                mov edx,dword ptr value64[4]
                .ifs ( edx > 0 || eax < 0 )
                    mov [rcx],eax
                    asmerr( 2024 )
                   .endc
                .endif
            .endif
endif
        .case FIX_OFF32_IMGREL
        .case FIX_OFF32_SECREL
            mov [rcx],eax
           .endc
        .case FIX_OFF64
ifndef _WIN64
            xor edx,edx
endif
            .if ( ( MODULE.sub_format == SFORMAT_PE && [rdi].Ofssize == USE64 ) ||
                  MODULE.sub_format == SFORMAT_64BIT )
ifdef _WIN64
                mov rax,value64
else
                mov eax,dword ptr value64
                mov edx,dword ptr value64[4]
endif
            .endif
            mov [rcx],rax
ifndef _WIN64
            mov [ecx+4],edx
endif
            .endc
        .case FIX_HIBYTE
            mov al,ah
            mov [rcx],al
           .endc
        .case FIX_SEG

            ; absolute segments are ok

            mov rax,[rbx].sym
            .if rax && [rax].asym.state == SYM_SEG
                mov rdx,[rax].asym.seginfo
                .if [rdx].seg_info.segtype == SEGTYPE_ABS
                    mov edx,[rdx].seg_info.abs_frame
                    mov [rcx],dx
                   .endc
                .endif
            .endif

            .if ( MODULE.sub_format == SFORMAT_MZ )

                .if ( [rax].asym.state == SYM_GRP )

                    mov segm,rax
                    mov rsi,[rax].asym.seginfo
                    mov edx,[rax].asym.offs
                    shr edx,4
                    mov [rcx],dx

                .elseif ( [rax].asym.state == SYM_SEG )

                    mov segm,rax
                    mov rsi,[rax].asym.seginfo
                    mov edx,[rsi].start_offset
                    .if [rsi].sgroup
                        mov rax,[rsi].sgroup
                        add edx,[rax].asym.offs
                    .endif
                    shr edx,4
                    mov [rcx],dx

                .elseif ( [rbx].frame_type == FRAME_GRP )

                    mov rax,[rsi].sgroup
                    mov eax,[rax].asym.offs
                    shr eax,4
                    mov [rcx],ax
                .else
                    mov eax,[rsi].start_offset
                    shr eax,4
                    mov [rcx],ax
                .endif
                .endc
            .endif
            mov eax,value

        .case FIX_PTR16

            ; v2.10: absolute segments are ok

            .if ( segm && [rsi].segtype == SEGTYPE_ABS )
                mov [rcx],ax
                mov eax,[rsi].abs_frame
                mov [rcx+2],ax
               .endc
            .endif
            .if ( MODULE.sub_format == SFORMAT_MZ )
                mov [rcx],ax
                add rcx,2
                .if ( [rbx].frame_type == FRAME_GRP )
                    mov rax,[rsi].sgroup
                    mov eax,[rax].asym.offs
                    shr eax,4
                    mov [rcx],ax
                .else
                    mov eax,[rsi].start_offset
                    .if [rsi].sgroup
                        mov rdx,[rsi].sgroup
                        add eax,[rdx].asym.offs
                    .endif
                    shr eax,4
                    mov [rcx],ax
                .endif
                .endc
            .endif
            mov eax,value
        .case FIX_PTR32

            ; v2.10: absolute segments are ok

            .if ( segm && [rsi].segtype == SEGTYPE_ABS )

                mov [rcx],eax
                mov eax,[rsi].abs_frame
                mov [rcx+4],ax
               .endc
            .endif

            .if ( MODULE.sub_format == SFORMAT_MZ )

                mov [rcx],eax
                .if ( [rbx].frame_type == FRAME_GRP )

                    mov rax,[rsi].sgroup
                    mov eax,[rax].asym.offs
                    shr eax,4
                    mov [rcx+4],ax
                .else

                    mov eax,[rsi].start_offset
                    .if ( [rsi].sgroup)

                        mov rdx,[rsi].sgroup
                        add eax,[rdx].asym.offs
                    .endif
                    shr eax,4
                    mov [rcx+4],ax
                .endif
                .endc
            .endif
        .default
            mov rcx,MODULE.fmtopt
            lea rdx,[rcx].format_options.formatname
            mov rcx,curr
            asmerr( 3019, rdx, [rbx].type, [rcx].asym.name, [rbx].locofs )
        .endsw
    .endf
    .return( NOT_ERROR )

DoFixup endp


    assume rbx:nothing, rdi:nothing, rsi:nothing

pe_create_MZ_header proc

    .if ( Parse_Pass == PASS_1 )

        .if ( SymFind( hdrname "1" ) == NULL )
            or MODULE.pe_flags,PEF_MZHDR
        .endif
    .endif

    .if ( MODULE.pe_flags & PEF_MZHDR )

        AddLineQueueX(
            "option dotname\n"
            "IMAGE_DOS_HEADER STRUC\n"
            "e_magic dw ?\n"
            "e_cblp dw ?\n"
            "e_cp dw ?\n"
            "e_crlc dw ?\n"
            "e_cparhdr dw ?\n"
            "e_minalloc dw ?\n"
            "e_maxalloc dw ?\n"
            "e_ss dw ?\n"
            "e_sp dw ?\n"
            "e_csum dw ?\n"
            "e_ip dw ?\n"
            "e_cs dw ?\n"
            "e_lfarlc dw ?\n"
            "e_ovno dw ?\n"
            "e_res dw 4 dup(?)\n"
            "e_oemid dw ?\n"
            "e_oeminfo dw ?\n"
            "e_res2 dw 10 dup(?)\n"
            "e_lfanew dd ?\n"
            "IMAGE_DOS_HEADER ENDS\n"
            "%s1 segment USE16 word %s\n"
            "IMAGE_DOS_HEADER {0x5A4D,0x68,1,0,4,0,-1,0,0xB8,0,0,0,0x40}\n"
            "push cs\n"
            "pop ds\n"
            "mov dx,@F-40h\n"
            "mov ah,9\n"
            "int 21h\n"
            "mov ax,4C01h\n"
            "int 21h\n"
            "@@:\n"
            "db 'This is a PE executable',13,10,'$'\n"
            "%s1 ends", hdrname, hdrattr, hdrname )

        RunLineQueue()

        .if SymFind( hdrname "1" )

            .if ( [rax].asym.state == SYM_SEG )

                mov rcx,[rax].asym.seginfo
                mov [rcx].seg_info.segtype,SEGTYPE_HDR
            .endif
        .endif
    .endif
    ret

pe_create_MZ_header endp


; get/set value of @pe_file_flags variable

set_file_flags proc fastcall uses rsi rdi sym:asym_t, opnd:ptr expr

    mov rsi,rcx
    mov rdi,rdx

    .if SymFind( hdrname "2" )

        mov rcx,[rax].asym.seginfo
        mov rdx,[rcx].seg_info.CodeBuffer
        movzx eax,[rdx].IMAGE_PE_HEADER32.FileHeader.Characteristics

        .if ( rdi ) ; set the value?

            mov eax,[rdi].expr.value
            mov [rdx].IMAGE_PE_HEADER32.FileHeader.Characteristics,ax
        .endif
        mov [rsi].asym.value,eax
    .endif
    ret

set_file_flags endp


    assume rsi:segment_t

pe_create_PE_header proc public uses rsi rdi rbx

    .if ( Parse_Pass == PASS_1 )

        .if ( MODULE._model != MODEL_FLAT )
            asmerr( 3002 )
        .endif

        movzx eax,Options.pe_subsystem
ifndef ASMC64
        .if ( MODULE.defOfssize == USE64 )
endif
            mov ebx,IMAGE_PE_HEADER64
            lea rdi,pe64def
            mov [rdi].IMAGE_PE_HEADER64.OptionalHeader.Subsystem,ax
ifndef ASMC64
        .else
            mov ebx,IMAGE_PE_HEADER32
            lea rdi,pe32def
            mov [rdi].IMAGE_PE_HEADER32.OptionalHeader.Subsystem,ax
        .endif
endif
        .if ( Options.pe_dll )
            or [rdi].IMAGE_PE_HEADER32.FileHeader.Characteristics,IMAGE_FILE_DLL
        .endif

        .if !SymFind( hdrname "2" )

            CreateIntSegment( hdrname "2", "HDR", 2, MODULE.defOfssize, TRUE )

            mov [rax].asym.max_offset,ebx
            mov rsi,[rax].asym.seginfo
            mov rcx,MODULE.flat_grp
            mov [rsi].sgroup,rcx
            mov [rsi].combine,COMB_ADDOFF  ; PUBLIC
            mov [rsi].characteristics,(IMAGE_SCN_MEM_READ shr 24)
            mov [rsi].readonly,1
            mov [rsi].bytes_written,ebx ; ensure that ORG won't set start_loc (assemble.c, SetCurrOffset)

        .else

            .if ( [rax].asym.max_offset < ebx )
                mov [rax].asym.max_offset,ebx
            .endif

            mov rsi,[rax].asym.seginfo
            mov [rsi].internal,1
            mov [rsi].start_loc,0
        .endif

        mov [rsi].segtype,SEGTYPE_HDR
        mov [rsi].CodeBuffer,LclAlloc( ebx )
        mov rbx,tmemcpy( rax, rdi, ebx )
        lea rcx,[rbx].IMAGE_PE_HEADER32.FileHeader.TimeDateStamp
        movzx ebx,[rdi].IMAGE_PE_HEADER32.FileHeader.Characteristics

        time( rcx )
        CreateVariable( "@pe_file_flags", ebx )

        .if ( rax )

            mov [rax].asym.predefined,1
            lea rcx,set_file_flags
            mov [rax].asym.sfunc_ptr,rcx
        .endif
    .endif
    ret

pe_create_PE_header endp


define CHAR_READONLY ( IMAGE_SCN_MEM_READ shr 24 )

IsStdCodeName proc fastcall segm:string_t

    ; if segment name starts with _TEXT$ or .text$, assume it should be "mixed"

    xor eax,eax
    .if ( byte ptr [rcx] == '_' || byte ptr [rcx] == '.' )

        .if ( byte ptr [rcx+5] == '$' )

            mov  ecx,[rcx+1]
            or   ecx,0x20202020
            cmp  ecx,'txet'
            setz al
        .endif
    .endif
    ret

IsStdCodeName endp

pe_create_section_table proc __ccall uses rsi rdi rbx

   .new objtab:asym_t
   .new bCreated:int_t = FALSE

    .if ( Parse_Pass == PASS_1 )

        .if SymFind( hdrname "3" )

            mov rdi,rax
            mov rsi,[rdi].asym.seginfo
        .else

            mov bCreated,TRUE
            mov rdi,CreateIntSegment( hdrname "3", "HDR", 2, MODULE.defOfssize, TRUE )
            mov rsi,[rdi].asym.seginfo
            mov [rsi].sgroup,MODULE.flat_grp
            mov [rsi].combine,COMB_ADDOFF ;; PUBLIC
        .endif
        mov [rsi].segtype,SEGTYPE_HDR

        .if ( !bCreated )
            .return
        .endif
        mov objtab,rdi

        ; before objects can be counted, the segment types
        ; SEGTYPE_CDATA ( for readonly segments ) &
        ; SEGTYPE_RSRC ( for resource segments )
        ; SEGTYPE_RELOC ( for relocations )
        ; must be set  - also, init lname_idx field

        .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].asym.next )

            mov rsi,[rdi].asym.seginfo
            mov [rsi].lname_idx,SEGTYPE_ERROR ; use the highest index possible

            .if ( [rsi].segtype == SEGTYPE_DATA )

                .if ( [rsi].readonly || [rsi].characteristics == CHAR_READONLY )

                    mov [rsi].segtype,SEGTYPE_CDATA

                .elseif ( [rsi].clsym )

                    mov rcx,[rsi].clsym
                    .ifd ( tstrcmp( [rcx].asym.name, "CONST" ) == 0 )
                        mov [rsi].segtype,SEGTYPE_CDATA
                    .endif
                .endif

            .elseif ( [rsi].segtype == SEGTYPE_UNDEF )

                mov rbx,[rdi].asym.name
                .ifd ( tmemcmp( rbx, ".rsrc", 5 ) == 0 )

                    .if ( B[rbx+5] == 0 || B[rbx+5] == '$' )
                        mov [rsi].segtype,SEGTYPE_RSRC
                    .endif

                .elseifd ( tstrcmp( rbx, ".reloc" ) == 0 )

                    mov [rsi].segtype,SEGTYPE_RELOC
                .endif
            .endif
        .endf

        ; count objects ( without header types )

        .for ( ebx = 1, esi = 0 : ebx < SIZE_PEFLAT : ebx++ )

            .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].asym.next )

                mov rdx,[rdi].asym.seginfo

                ; v2.19: skip info sections

                .continue .if ( [rdx].seg_info.information )

                ; v2.12: don't mix 32-bit and 16-bit code segments
                ; v2.19: use SEGTYPE_CODE16 instead of SEGTYPE_UNDEF so it's behind the .text section;
                ;        if segment name contains a '$', allow mixing!

                IsStdCodeName( [rdi].asym.name )

                lea rcx,flat_order
                mov ecx,[rcx+rbx*4]
                mov ah,ModuleInfo.defOfssize

                .if ( ecx == SEGTYPE_CODE16 && [rdx].seg_info.segtype == SEGTYPE_CODE &&
                      [rdx].seg_info.Ofssize != ah && !al )
                    ;nop
                .elseif ( ecx == [rdx].seg_info.segtype && [rdi].asym.max_offset )
                    inc esi
                   .break
                .endif
            .endf
        .endf

        .if ( esi )

            mov rdi,objtab
            imul ebx,esi,IMAGE_SECTION_HEADER
            mov [rdi].asym.max_offset,ebx

            ; alloc space for 1 more section (.reloc)

            mov rsi,[rdi].asym.seginfo
            mov [rsi].CodeBuffer,LclAlloc( &[rbx+IMAGE_SECTION_HEADER] )
        .endif
    .endif
    ret

pe_create_section_table endp


expitem struct
name    string_t ?
idx     dd ?
expitem ends

compare_exp proc fastcall p1:ptr expitem, p2:ptr expitem

    tstrcmp( [rcx].expitem.name, [rdx].expitem.name )
    ret

compare_exp endp


pe_emit_export_data proc __ccall uses rsi rdi rbx

  local timedate:int_32
  local cnt:int_t
  local name:string_t
  local pitems:ptr expitem

    ; v2.19: scan the public queue instead of just PROCs.
    ; In v2.19, the PUBLIC directive has been extended to allow to export data items;
    ; masm has the restriction that only PROCs can have the "export" attribute.

    .for ( rdi = MODULE.PubQueue.head, ebx = 0 : rdi : rdi = [rdi].qnode.next )
        mov rdx,[rdi].qnode.sym
        .if ( [rdx].asym.isexport )
            inc ebx
        .endif
    .endf
    .return .if ( ebx == 0 )

    time( &timedate )
    lea rsi,MODULE.name

    ; create .edata segment

    mov ecx,T_IMAGEREL
    AddLineQueueX(
        "%r DOTNAME\n"
        "%s %r %r %s\n"
        "DD 0, 0%xh, 0, %r @%s_name, 1, %u, %u, %r @%s_func, %r @%s_names, %r @%s_nameord",
        T_OPTION, edataname, T_SEGMENT, T_DWORD, edataattr, timedate, ecx, rsi, ebx, ebx, ecx, rsi, ecx, rsi, ecx, rsi )

    mov name,rsi
    mov cnt,ebx

    ; the name pointer table must be in ascending order!
    ; so we have to fill an array of exports and sort it.

    imul ecx,ebx,expitem
    mov pitems,alloca(ecx)

    assume rsi:ptr expitem

    .for ( rsi = rax, rdi = MODULE.PubQueue.head, ebx = 0 : rdi : rdi = [rdi].qnode.next )

        mov rdx,[rdi].qnode.sym
        .if ( [rdx].asym.isexport )

            mov [rsi].name,[rdx].asym.name
            mov [rsi].idx,ebx
            inc ebx
            add rsi,expitem
        .endif
    .endf
    tqsort( pitems, cnt, sizeof( expitem ), &compare_exp )

    ; emit export address table.
    ; would be possible to just use the array of sorted names,
    ; but we want to emit the EAT being sorted by address.

    AddLineQueueX( "@%s_func %r %r", name, T_LABEL, T_DWORD )

    .for ( rdi = MODULE.PubQueue.head : rdi : rdi = [rdi].qnode.next )

        mov rdx,[rdi].qnode.sym
        .if ( [rdx].asym.isexport )
            AddLineQueueX( "dd %r %s", T_IMAGEREL, [rdi].asym.name )
        .endif
    .endf

    ; emit the name pointer table

    AddLineQueueX( "@%s_names %r %r", name, T_LABEL, T_DWORD )

    .for ( rsi = pitems, ebx = 0: ebx < cnt: ebx++, rsi += expitem )
        AddLineQueueX( "dd %r @%s", T_IMAGEREL, [rsi].name )
    .endf

    ; ordinal table. each ordinal is an index into the export address table

    AddLineQueueX( "@%s_nameord %r %r", name, T_LABEL, T_WORD )

    .for ( rsi = pitems, ebx = 0: ebx < cnt: ebx++, rsi += expitem )
        AddLineQueueX( "dw %u", [rsi].idx )
    .endf

    assume rsi:nothing

    ; v2.10: name+ext of dll

    .for ( rbx = CurrFName[OBJ*string_t], rbx += tstrlen( rbx ): rbx > CurrFName[OBJ*string_t]: rbx-- )
        .break .if ( B[rbx] == '/' || B[rbx] == '\' || B[rbx] == ':' )
    .endf
    AddLineQueueX( "@%s_name db '%s',0", name, rbx )

    .for ( rsi = MODULE.PubQueue.head : rsi : rsi = [rsi].qnode.next )

        mov rdi,[rsi].qnode.sym
        .if ( [rdi].asym.isexport )

            Mangle( rdi, StringBufferEnd )
            mov rcx,StringBufferEnd
            .if Options.no_export_decoration
                mov rcx,[rdi].asym.name
            .endif
            AddLineQueueX( "@%s db '%s',0", [rdi].asym.name, rcx )
        .endif
    .endf

    ; exit .edata segment

    AddLineQueueX( "%s %r", edataname, T_ENDS )
    RunLineQueue()
    ret

pe_emit_export_data endp


; write import data.
; convention:
; .idata$2: import directory
; .idata$3: final import directory NULL entry
; .idata$4: ILT entry
; .idata$5: IAT entry
; .idata$6: strings

pe_emit_import_data proc __ccall uses rsi rdi rbx

    .new type:int_t = 0
    .new ptrtype:int_t = T_QWORD
    .new cpalign:string_t = "ALIGN(8)"

ifndef ASMC64
    .if ( MODULE.defOfssize != USE64 )
        mov ptrtype,T_DWORD
        mov cpalign,&@CStr("ALIGN(4)")
    .endif
endif

    assume rbx:ptr dll_desc

    .for ( rbx = MODULE.DllQueue: rbx: rbx = [rbx].next )

        .if ( [rbx].cnt )

            .if ( !type )

                mov type,1
                AddLineQueueX(
                    "@LPPROC %r %r %r\n"
                    "%r dotname", T_TYPEDEF, T_PTR, T_PROC, T_OPTION )
            .endif

           .new name[256]:char_t
            mov rsi,tstrcpy(&name, &[rbx].name)

            ; avoid '.' and '-' in IDs

            .while ( tstrchr( rsi, '.' ) )
                mov B[rax],'_'
            .endw
            .while ( tstrchr( rsi, '-' ) )
                mov B[rax],'_'
            .endw

            ; import directory entry

            lea rcx,@CStr(idataname)
            lea rdx,@CStr(idataattr)
            mov edi,T_IMAGEREL
            AddLineQueueX(
                "%s" IMPDIRSUF " %r %r %s\n"
                "dd %r @%s_ilt, 0, 0, %r @%s_name, %r @%s_iat\n"
                "%s" IMPDIRSUF " %r\n"
                "%s" IMPILTSUF " %r %s %s\n"
                "@%s_ilt %r %r",
                rcx, T_SEGMENT, T_DWORD, rdx, edi, rsi, edi, rsi, edi, rsi, rcx, T_ENDS,
                rcx, T_SEGMENT, cpalign, rdx, rsi, T_LABEL, ptrtype )

            .for ( rdi = SymTables[TAB_EXT*symbol_queue].head : rdi : rdi = [rdi].asym.next )
                .if ( [rdi].asym.iat_used && [rdi].asym.dll == rbx )
                    AddLineQueueX( "@LPPROC %r @%s_name", T_IMAGEREL, [rdi].asym.name )
                .endif
            .endf

            ; ILT termination entry + IAT

            AddLineQueueX(
                "@LPPROC 0\n"
                "%s" IMPILTSUF " %r\n"
                "%s" IMPIATSUF " %r %s %s\n"
                "@%s_iat %r %r", idataname, T_ENDS, idataname, T_SEGMENT, cpalign, idataattr, rsi, T_LABEL, ptrtype )

            .for ( rdi = SymTables[TAB_EXT*symbol_queue].head : rdi : rdi = [rdi].asym.next )
                .if ( [rdi].asym.iat_used && [rdi].asym.dll == rbx )
                    Mangle( rdi, StringBufferEnd )
                    AddLineQueueX( "%s%s @LPPROC %r @%s_name",
                        MODULE.imp_prefix, StringBufferEnd, T_IMAGEREL, [rdi].asym.name )
                .endif
            .endf

            ; IAT termination entry + name table

            AddLineQueueX(
                "@LPPROC 0\n"
                "%s" IMPIATSUF " %r\n"
                "%s" IMPSTRSUF " %r %r %s", idataname, T_ENDS, idataname, T_SEGMENT, T_WORD, idataattr )

            .for ( rdi = SymTables[TAB_EXT*symbol_queue].head : rdi : rdi = [rdi].asym.next )
                .if ( [rdi].asym.iat_used && [rdi].asym.dll == rbx )
                    AddLineQueueX(
                        "@%s_name dw 0\n"
                        "db '%s',0\n"
                        "even", [rdi].asym.name, [rdi].asym.name )
                .endif
            .endf

            ; dll name table entry

            AddLineQueueX(
                "@%s_name db '%s',0\n"
                "even\n"
                "%s" IMPSTRSUF " %r", rsi, &[rbx].name, idataname, T_ENDS )

        .endif
    .endf
    .if ( is_linequeue_populated() )

        ; import directory NULL entry

        AddLineQueueX(
            "%s" IMPNDIRSUF " %r %r %s\n"
            "DD 0, 0, 0, 0, 0\n"
            "%s" IMPNDIRSUF " %r", idataname, T_SEGMENT, T_DWORD, idataattr, idataname, T_ENDS )
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


pe_get_characteristics proc fastcall segp:asym_t

    mov rcx,[rcx].asym.seginfo
    mov eax,IMAGE_SCN_CNT_INITIALIZED_DATA or IMAGE_SCN_MEM_READ or IMAGE_SCN_MEM_WRITE

    .switch
    .case ( [rcx].seg_info.segtype == SEGTYPE_CODE )
        mov eax,IMAGE_SCN_CNT_CODE or IMAGE_SCN_MEM_EXECUTE or IMAGE_SCN_MEM_READ
        .endc
    .case ( [rcx].seg_info.segtype == SEGTYPE_BSS )
        mov eax,IMAGE_SCN_CNT_UNINITIALIZED_DATA or IMAGE_SCN_MEM_READ or IMAGE_SCN_MEM_WRITE
        .endc
    .case ( [rcx].seg_info.combine == COMB_STACK && [rcx].seg_info.bytes_written == 0 )
        mov eax,IMAGE_SCN_CNT_UNINITIALIZED_DATA or IMAGE_SCN_MEM_READ or IMAGE_SCN_MEM_WRITE
        .endc
    .case ( [rcx].seg_info.readonly )
        mov eax,IMAGE_SCN_CNT_INITIALIZED_DATA or IMAGE_SCN_MEM_READ
        .endc
    .case ( [rcx].seg_info.clsym )
        mov rdx,[rcx].seg_info.clsym
        mov rdx,[rdx].asym.name
        .if dword ptr [rdx] == 'SNOC' && word ptr [rdx+4] == 'T'
            mov eax,IMAGE_SCN_CNT_INITIALIZED_DATA or IMAGE_SCN_MEM_READ
        .endif
    .endsw

    ; manual characteristics set?

    .if ( [rcx].seg_info.characteristics )

        and eax,0x1FFFFFF ;; clear the IMAGE_SCN_MEM flags
        mov dl,[rcx].seg_info.characteristics
        and edx,0xFE
        shl edx,24
        or  eax,edx
    .endif
    ret

pe_get_characteristics endp


; set base relocations

    assume rbx:ptr fixup
    assume rsi:segment_t

pe_set_base_relocs proc __ccall uses rsi rdi rbx reloc:asym_t

  .new cnt1:int_t = 0
  .new cnt2:int_t = 0
  .new ftype:int_t
  .new currpage:uint_32 = -1
  .new currloc:uint_32
  .new curr:asym_t
  .new fixp:ptr fixup
  .new baserel:ptr IMAGE_BASE_RELOCATION
  .new prel:ptr uint_16

    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].asym.next )

        mov rsi,[rdi].asym.seginfo
        .continue .if ( [rsi].segtype == SEGTYPE_HDR )

        .for ( rbx = [rsi].head: rbx: rbx = [rbx].nextrlc )

            .switch ( [rbx].type )
            .case FIX_OFF16
            .case FIX_OFF32
            .case FIX_OFF64
                mov eax,[rbx].locofs
                and eax,0xFFFFF000
                add eax,[rsi].start_offset
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
    mov rdi,reloc
    mov rsi,[rdi].asym.seginfo
    mov [rdi].asym.max_offset,ecx
    mov [rsi].CodeBuffer,LclAlloc( ecx )
    mov baserel,rax
    mov [rax].IMAGE_BASE_RELOCATION.VirtualAddress,-1
    add rax,IMAGE_BASE_RELOCATION
    mov prel,rax

    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].asym.next )

        mov rsi,[rdi].asym.seginfo
        .continue .if ( [rsi].segtype == SEGTYPE_HDR )

        .for ( rbx = [rsi].head: rbx: rbx = [rbx].nextrlc )

            xor ecx,ecx
            mov al,[rbx].type
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
                mov eax,[rbx].locofs
                and eax,0xFFFFF000
                add eax,[rsi].start_offset
                mov rdx,baserel
                mov rcx,prel

                assume rdx:ptr IMAGE_BASE_RELOCATION

                .if ( eax != [rdx].VirtualAddress )
                    .if ( [rdx].VirtualAddress != -1 )

                        ; address of relocation header must be DWORD aligned

                        .if ( [rdx].SizeOfBlock & 2 )
                            mov W[rcx],0
                            add rcx,2
                            add [rdx].SizeOfBlock,sizeof( uint_16 )
                        .endif
                        mov rdx,rcx
                        add rcx,sizeof( IMAGE_BASE_RELOCATION )
                    .endif
                    mov [rdx].VirtualAddress,eax
                    mov [rdx].SizeOfBlock,sizeof( IMAGE_BASE_RELOCATION )
                .endif

                add [rdx].SizeOfBlock,sizeof( uint_16 )
                mov baserel,rdx

                mov eax,[rbx].locofs
                and eax,0xfff
                mov edx,ftype
                shl edx,12
                or  eax,edx
                mov [rcx],ax
                add rcx,2
                mov prel,rcx

                assume rdx:nothing
            .endif
        .endf
    .endf
    ret

pe_set_base_relocs endp


GHF proto watcall x:abs {
    mov rax,pe
ifndef ASMC64
    .if ( MODULE.defOfssize == USE64 )
endif
if sizeof(IMAGE_PE_HEADER64.x) lt 4
        movzx eax,[rax].IMAGE_PE_HEADER64.x
elseif sizeof(IMAGE_PE_HEADER64.x) eq 4
        mov eax,[rax].IMAGE_PE_HEADER64.x
elseifdef _WIN64
        mov rax,[rax].IMAGE_PE_HEADER64.x
else
        mov edx,dword ptr [rax].IMAGE_PE_HEADER64.x[4]
        mov eax,dword ptr [rax].IMAGE_PE_HEADER64.x
endif
ifndef ASMC64
    .else
if sizeof(IMAGE_PE_HEADER32.x) lt 4
        movzx eax,[rax].IMAGE_PE_HEADER32.x
else
        mov eax,[rax].IMAGE_PE_HEADER32.x
endif
    .endif
endif
    }

; set values in PE header
; including data directories:
; special section names:
; .edata - IMAGE_DIRECTORY_ENTRY_EXPORT
; .idata - IMAGE_DIRECTORY_ENTRY_IMPORT, IMAGE_DIRECTORY_ENTRY_IAT
; .rsrc  - IMAGE_DIRECTORY_ENTRY_RESOURCE
; .pdata - IMAGE_DIRECTORY_ENTRY_EXCEPTION (64-bit only)
; .reloc - IMAGE_DIRECTORY_ENTRY_BASERELOC
; .tls   - IMAGE_DIRECTORY_ENTRY_TLS

    assume rbx:nothing
    assume rsi:nothing

ifdef ADD_MANIFESTFILE ; v2.36.26 - add manifest file

AddManifestdependency proc __ccall uses rsi rdi rbx dependency:string_t

   .new cp:string_t
   .new fp:LPFILE
   .new file[256]:char_t

    ldr rbx,dependency
    add rbx,16

    .if tstrrchr( tstrcpy( &file, GetFNamePart( MODULE.curr_fname[ASM*string_t] ) ), '.' )
        mov byte ptr [rax],0
    .endif

    .if ( fopen( tstrcat( &file, ".exe.manifest" ), "w" ) != NULL )

        mov fp,rax
        mov cp,tstrrchr( rbx, '"' )
        .if ( rax )
            mov byte ptr [rax],0
        .endif

        tfprintf( fp,
            "<?xml version='1.0' encoding='UTF-8' standalone='yes'?>\n"
            "<assembly xmlns='urn:schemas-microsoft-com:asm.v1' manifestVersion='1.0'>\n"
            "  <trustInfo xmlns=\"urn:schemas-microsoft-com:asm.v3\">\n"
            "    <security>\n"
            "      <requestedPrivileges>\n"
            "        <requestedExecutionLevel level='asInvoker' uiAccess='false' />\n"
            "      </requestedPrivileges>\n"
            "    </security>\n"
            "  </trustInfo>\n"
            "  <dependency>\n"
            "    <dependentAssembly>\n"
            "      <assemblyIdentity %s />\n"
            "    </dependentAssembly>\n"
            "  </dependency>\n"
            "</assembly>\n", rbx )

        mov rax,cp
        .if ( rax )

            mov byte ptr [rax],'"'
            lea rbx,[rax+1]
        .endif
        fclose(fp)
    .endif
    mov rax,rbx
    ret

AddManifestdependency endp
endif

pe_scan_linker_directives proc __ccall uses rsi rdi rbx pe:ptr, cmd:string_t, size:int_t

   .new num[4]:dword
   .new entry[128]:char_t

    ldr rbx,pe
    ldr rsi,cmd

    .while ( size > 3 )

        lodsb
        dec size
        .if ( al == '-' || al == '/' )

            lodsd
            sub size,4
            or eax,0x20202020
            .switch eax
            .case 'esab'
                lodsb
                dec size
                .if ( al == ':' )
                    mov eax,[rsi]
                    mov ecx,10
                    .if ( al == '0' && ah == 'x' )
                        lodsw
                        sub size,2
                        mov ecx,16
                    .endif
                    _atoow( rsi, &num, ecx, size )
                    mov eax,num  ; base != 0, fits in 64-bits, page aligned?
                    mov ecx,eax
                    or  ecx,num[4]
                    mov edx,num[8]
                    or  edx,num[12]
                    .if ( ecx && !edx && !( eax & 0x0FFF ) )
                        mov edx,num[4]
                        .if ( MODULE.defOfssize == USE64 )
                            mov dword ptr [rbx].IMAGE_PE_HEADER64.OptionalHeader.ImageBase,eax
                            mov dword ptr [rbx].IMAGE_PE_HEADER64.OptionalHeader.ImageBase[4],edx
                        .elseif ( !edx && eax <= 0xfffff000 )
                            mov [rbx].IMAGE_PE_HEADER32.OptionalHeader.ImageBase,eax
                        .endif
                    .endif
                .endif
                .endc
            .case 'rtne'
                lodsw
                dec size
                or al,0x20
                .if ( al == 'y' && ah == ':' )
                    .for ( rdi = &entry : size > 0 : size-- )
                        lodsb
                        .break .if ( al == 0 || al == ' ' )
                        stosb
                    .endf
                    xor eax,eax
                    stosb
                    .if SymFind( &entry )
                        mov MODULE.start_label,rax
                    .endif
                .endif
                .endc
            .case 'exif'
                lodsb
                dec size
                or al,0x20
                .if ( al == 'd' )
                    lodsb
                    dec size
                    .if ( al == ':' )
                        and [rbx].IMAGE_PE_HEADER32.FileHeader.Characteristics,not IMAGE_FILE_RELOCS_STRIPPED
                    .else
                        or  [rbx].IMAGE_PE_HEADER32.FileHeader.Characteristics,IMAGE_FILE_RELOCS_STRIPPED
                    .endif
                .endif
                .endc
            .case 'gral'
                .ifd !tmemicmp( rsi, "eaddressaware", 13 )
                    sub size,13
                    add rsi,13
                    .ifd !tmemicmp( rsi, ":no", 3 )
                        sub size,3
                        add rsi,3
                        and [rbx].IMAGE_PE_HEADER32.FileHeader.Characteristics,not IMAGE_FILE_LARGE_ADDRESS_AWARE
                    .else
                        or  [rbx].IMAGE_PE_HEADER32.FileHeader.Characteristics,IMAGE_FILE_LARGE_ADDRESS_AWARE
                    .endif
                .endif
                .endc
            .case 'sbus'
                .new subsystem:int_t = IMAGE_SUBSYSTEM_UNKNOWN
                .ifd !tmemicmp( rsi, "ystem:", 6 )
                    sub size,6
                    add rsi,6
                    .ifd !tmemicmp( rsi, "windows", 7 )
                        sub size,7
                        add rsi,7
                        mov subsystem,IMAGE_SUBSYSTEM_WINDOWS_GUI
                    .elseifd !tmemicmp( rsi, "console", 7 )
                        sub size,7
                        add rsi,7
                        mov subsystem,IMAGE_SUBSYSTEM_WINDOWS_CUI
                    .elseifd !tmemicmp( rsi, "native", 6 )
                        sub size,6
                        add rsi,6
                        mov subsystem,IMAGE_SUBSYSTEM_NATIVE
                    .endif
                .endif
                .if ( subsystem != IMAGE_SUBSYSTEM_UNKNOWN )
                    mov eax,subsystem
                    .if ( MODULE.defOfssize == USE64 )
                        mov [rbx].IMAGE_PE_HEADER64.OptionalHeader.Subsystem,ax
                    .else
                        mov [rbx].IMAGE_PE_HEADER32.OptionalHeader.Subsystem,ax
                    .endif
                .endif
                .endc
ifdef ADD_MANIFESTFILE
            .case 'inam'
                sub AddManifestdependency(rsi),rsi
                sub size,eax
                add rsi,rax
               .endc
endif
            .default
                and eax,0x00FFFFFF
                .if eax == 'lld'
                    or [rbx].IMAGE_PE_HEADER32.FileHeader.Characteristics,IMAGE_FILE_DLL
                .else
                    asmerr( 8000, &[rsi-5] ) ; pe8.asm
                .endif
            .endsw
        .endif
    .endw
    ret

pe_scan_linker_directives endp


    assume rsi:segment_t

pe_set_values proc __ccall uses rsi rdi rbx cp:ptr calc_param

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
    .new mzhdr:asym_t
    .new pehdr:asym_t
    .new objtab:asym_t
    .new reloc:asym_t = NULL
    .new pe:ptr IMAGE_PE_HEADER64
    .new fh:ptr IMAGE_FILE_HEADER
    .new section:ptr IMAGE_SECTION_HEADER
    .new datadir:ptr IMAGE_DATA_DIRECTORY
    .new secname:string_t
    .new buffer[MAX_ID_LEN+1]:char_t

    mov mzhdr,  SymFind( hdrname "1" )
    mov rsi,    [rax].asym.seginfo
    mov pehdr,  SymFind( hdrname "2" )
    mov objtab, SymFind( hdrname "3" )

    ;; make sure all header objects are in FLAT group
    mov [rsi].sgroup,MODULE.flat_grp

    mov rax,pehdr
    mov rsi,[rax].asym.seginfo
    mov rcx,[rsi].CodeBuffer
    mov pe,rcx
ifndef ASMC64
    .if ( MODULE.defOfssize == USE64 )
endif
        mov ff,[rcx].IMAGE_PE_HEADER64.FileHeader.Characteristics
ifndef ASMC64
    .else
        mov ff,[rcx].IMAGE_PE_HEADER32.FileHeader.Characteristics
    .endif
endif

    ; .pragma comment(linker, "/..")

    .for ( rdi = MODULE.LinkQueue.head: rdi: rdi = [rdi].qitem.next )

        tstrlen( &[rdi].qitem.value )
        pe_scan_linker_directives( pe, &[rdi].qitem.value, eax )
    .endf

    ; v2.19: first, handle ".drectve" info sections

    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].asym.next )

        mov rsi,[rdi].asym.seginfo
        .if ( [rsi].information )
            .if ( !tstrcmp( [rdi].asym.name, ".drectve" ) )
                pe_scan_linker_directives( pe, [rsi].CodeBuffer, [rsi].bytes_written )
            .endif
        .endif
    .endf

    .if ( !( eax & IMAGE_FILE_RELOCS_STRIPPED ) )

        mov reloc,CreateIntSegment( ".reloc", "RELOC", 2, MODULE.defOfssize, TRUE )

        .if ( rax )

            mov rsi,[rax].asym.seginfo

            ; make sure the section isn't empty ( true size will be calculated later )

            mov [rax].asym.max_offset,sizeof( IMAGE_BASE_RELOCATION )
            mov [rsi].sgroup,MODULE.flat_grp
            mov [rsi].combine,COMB_ADDOFF
            mov [rsi].segtype,SEGTYPE_RELOC
            mov [rsi].characteristics,((IMAGE_SCN_MEM_DISCARDABLE or IMAGE_SCN_MEM_READ) shr 24 )
            mov [rsi].bytes_written,sizeof( IMAGE_BASE_RELOCATION )

            ; clear the additionally allocated entry in object table

            mov rdx,objtab
            mov rsi,[rdx].asym.seginfo
            mov edi,[rdx].asym.max_offset
            add [rdx].asym.max_offset,sizeof( IMAGE_SECTION_HEADER )
            add rdi,[rsi].CodeBuffer
            mov ecx,sizeof( IMAGE_SECTION_HEADER )
            xor eax,eax
            rep stosb
        .endif
    .endif

    ; sort: header, executable, readable, read-write segments, resources, relocs

    .for ( rdx = &flat_order, ebx = 0 : ebx < SIZE_PEFLAT : ebx++ )
        .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].asym.next )
            mov rsi,[rdi].asym.seginfo
            .if ( [rsi].segtype == [rdx+rbx*4] )
if 1
                ; v2.12: added to avoid mixing 16-/32-bit code segments;
                ;        also see code in pe_create_section_table!
                ;        jwlink DOES mix 16- and 32-bit code segments! MS link does NOT.
                ; v2.19: allow mixing if 16-bit code segment's name starts with _TEXT$ or .text$.

                IsStdCodeName( [rdi].asym.name )
                mov ecx,ebx
                mov ah,ModuleInfo.defOfssize

                .if ( [rsi].segtype == SEGTYPE_CODE && [rsi].Ofssize != ah && !al )

                    ; v2.19: use newly introduced SEGTYPE_CODE16 (so 16-bit code is behind .text

                    inc ecx ; i+1 = SEGTYPE_CODE16
                .endif
                mov [rsi].lname_idx,ecx
else
                mov [rsi].lname_idx,ebx
endif
            .endif
        .endf
    .endf
    SortSegments( 2 )

    mov falign,get_bit( GHF( OptionalHeader.FileAlignment ) )
    mov malign,GHF( OptionalHeader.SectionAlignment )

    ; assign RVAs to sections

    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head, ebx = -1 : rdi : rdi = [rdi].asym.next )

        mov rsi,[rdi].asym.seginfo
        mov rdx,cp

        .if ( [rsi].lname_idx == SEGTYPE_ERROR || [rsi].lname_idx != ebx )

            mov ebx,[rsi].lname_idx
            mov [rdx].calc_param.alignment,falign
            mov eax,malign

        .else
            mov eax,1
            mov cl,[rsi].alignment
            shl eax,cl
            mov [rdx].calc_param.alignment,0
        .endif
        dec eax
        mov ecx,eax
        not ecx
        add eax,[rdx].calc_param.rva
        and eax,ecx
        mov [rdx].calc_param.rva,eax
        CalcOffset( rdi, rdx )
    .endf

    mov rbx,cp
    mov rcx,reloc

    .if ( rcx )

        pe_set_base_relocs( rcx )

        ; v2.13: if no relocs exist, remove the .reloc section that was just created.
        ; v2.16: this didn't work because reloc->sym.max_offset was initialized
        ;        with size of IMAGE_BASE_RELOCATION

        mov rcx,reloc
        mov eax,[rcx].asym.max_offset
        .ifs ( eax > IMAGE_BASE_RELOCATION )

            mov rsi,[rcx].asym.seginfo
            add eax,[rsi].start_offset
            mov [rbx].calc_param.rva,eax
        .else
            mov rdx,objtab
            sub [rdx].asym.max_offset,IMAGE_SECTION_HEADER
            sub [rbx].calc_param.rva,IMAGE_BASE_RELOCATION ; v2.16: added
        .endif
    .endif

    mov sizeimg,[rbx].calc_param.rva

    ; set e_lfanew of dosstub to start of PE header

    mov rax,mzhdr
    mov rcx,pehdr

    .if ( [rax].asym.max_offset >= 0x40 )

        mov rsi,[rax].asym.seginfo
        mov rdx,[rsi].CodeBuffer
        mov rsi,[rcx].asym.seginfo
        mov eax,[rsi].fileoffset
        .if ( [rdx].IMAGE_DOS_HEADER.e_magic == 0x5a4d && [rdx].IMAGE_DOS_HEADER.e_cparhdr >= 4 )
            mov [rdx].IMAGE_DOS_HEADER.e_lfanew,eax
        .endif
    .endif

    ; set number of sections in PE file header (doesn't matter if it's 32- or 64-bit)

    mov rsi,[rcx].asym.seginfo
    mov rdx,[rsi].CodeBuffer
    lea rcx,[rdx].IMAGE_PE_HEADER32.FileHeader
    mov fh,rcx
    mov rdi,objtab
    mov eax,[rdi].asym.max_offset
    mov ecx,sizeof( IMAGE_SECTION_HEADER )
    cdq
    div ecx
    mov rcx,fh
    mov [rcx].IMAGE_FILE_HEADER.NumberOfSections,ax

if RAWSIZE_ROUND
    mov [rbx].calc_param.rawpagesize,GHF(OptionalHeader.FileAlignment)
endif

    ; fill object table values

    mov rsi,[rdi].asym.seginfo
    mov section,[rsi].CodeBuffer

    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head, ebx = -1 : rdi : rdi = [rdi].asym.next )

        mov rsi,[rdi].asym.seginfo

        .continue .if ( [rsi].segtype == SEGTYPE_HDR )
        .continue .if ( [rdi].asym.max_offset == 0 ) ;; ignore empty sections

if 1    ; v2.34.61 - jwasm

        ; v2.16: linker directive sections are ignored. Would be good to scan
        ; them for export directives, since masm/jwasm has the restriction that only PROCs can
        ; be exported. The problem is that it's far too late here, function pe_emit_export_data() has
        ; been called just after step 1 - and worse, inside pe_emit_export_data() it cannot be done
        ; either since at that time there are no section contents available yet!

        .if ( [rsi].information ) ; v2.13: ignore 'info' sections (linker directives)

            ;asmerr( 8017, [rdi].asym.name ) ; v2.15: emit warning
           .continue
        .endif
endif
        assume rcx:ptr IMAGE_SECTION_HEADER

        .if ( [rsi].lname_idx != ebx )

            mov ebx,[rsi].lname_idx
            mov rax,[rsi].aliasname
            .if rax == NULL
                ConvertSectionName( rdi, NULL, &buffer )
            .endif
            mov secname,rax
            mov rcx,section
            tstrncpy( &[rcx].Name, secname, sizeof ( IMAGE_SECTION_HEADER.Name ) )

            mov rcx,section
            .if ( [rsi].segtype != SEGTYPE_BSS )
                mov [rcx].PointerToRawData,[rsi].fileoffset
            .endif
            mov [rcx].VirtualAddress,[rsi].start_offset

            ; file offset of first section in object table defines SizeOfHeader

            .if ( sizehdr == 0 )
                mov sizehdr,[rsi].fileoffset
            .endif
        .endif

        pe_get_characteristics( rdi )

        mov rcx,section
        or  [rcx].Characteristics,eax
        mov eax,[rdi].asym.max_offset
        .if ( [rsi].segtype != SEGTYPE_BSS )
            add [rcx].SizeOfRawData,eax
        .endif
        mov edx,[rsi].start_offset
        sub edx,[rcx].VirtualAddress
        add eax,edx
        mov [rcx].Misc.VirtualSize,eax

        mov rdx,[rdi].asym.next
        .if rdx
            mov rdx,[rdx].asym.seginfo
        .endif

        .if ( rdx == NULL || [rdx].seg_info.lname_idx != ebx )

if RAWSIZE_ROUND ; AntiVir TR/Crypt.XPACK Gen
            mov rax,cp
            mov eax,[rax].calc_param.rawpagesize
            dec eax
            add [rcx].SizeOfRawData,eax
            not eax
            and [rcx].SizeOfRawData,eax
endif
            .if ( [rcx].Characteristics & IMAGE_SCN_MEM_EXECUTE )
                .if ( codebase == 0 )
                    mov codebase,[rcx].VirtualAddress
                .endif
                add codesize,[rcx].SizeOfRawData
            .endif
            .if ( [rcx].Characteristics & IMAGE_SCN_CNT_INITIALIZED_DATA )
                .if ( database == 0 )
                    mov database,[rcx].VirtualAddress
                .endif
                add datasize,[rcx].SizeOfRawData
            .endif
        .endif
        .if ( rdx && [rdx].seg_info.lname_idx != ebx )
            add section,IMAGE_SECTION_HEADER
        .endif
    .endf

    assume rcx:nothing


    .if ( MODULE.start_label )

        mov rax,MODULE.start_label
        mov rdx,[rax].asym.segm
        mov rsi,[rdx].asym.seginfo
        mov ecx,[rsi].start_offset
        add ecx,[rax].asym.offs
        mov rax,pe
ifndef ASMC64
        .if ( MODULE.defOfssize == USE64 )
endif
            mov [rax].IMAGE_PE_HEADER64.OptionalHeader.AddressOfEntryPoint,ecx
ifndef ASMC64
        .else
            mov [rax].IMAGE_PE_HEADER32.OptionalHeader.AddressOfEntryPoint,ecx
        .endif
endif
    .else
        asmerr( 8009 )
    .endif

    mov rcx,pe
ifndef ASMC64
    .if ( MODULE.defOfssize == USE64 )
endif
if IMGSIZE_ROUND
        ;; round up the SizeOfImage field to page boundary
        mov eax,[rcx].IMAGE_PE_HEADER64.OptionalHeader.SectionAlignment
        dec eax
        mov edx,eax
        not edx
        add eax,sizeimg
        and eax,edx
        mov sizeimg,eax
endif
        mov [rcx].IMAGE_PE_HEADER64.OptionalHeader.SizeOfCode,codesize
        mov [rcx].IMAGE_PE_HEADER64.OptionalHeader.BaseOfCode,codebase
        mov [rcx].IMAGE_PE_HEADER64.OptionalHeader.SizeOfImage,sizeimg
        mov [rcx].IMAGE_PE_HEADER64.OptionalHeader.SizeOfHeaders,sizehdr
        mov datadir,&[rcx].IMAGE_PE_HEADER64.OptionalHeader.DataDirectory
ifndef ASMC64
    .else
if IMGSIZE_ROUND
        ;
        ; round up the SizeOfImage field to page boundary
        ;
        mov eax,[rcx].IMAGE_PE_HEADER32.OptionalHeader.SectionAlignment
        dec eax
        mov edx,eax
        not edx
        add eax,sizeimg
        and eax,edx
        mov sizeimg,eax
endif
        mov [rcx].IMAGE_PE_HEADER32.OptionalHeader.SizeOfCode,codesize
        mov [rcx].IMAGE_PE_HEADER32.OptionalHeader.SizeOfInitializedData,datasize
        mov [rcx].IMAGE_PE_HEADER32.OptionalHeader.BaseOfCode,codebase
        mov [rcx].IMAGE_PE_HEADER32.OptionalHeader.BaseOfData,database
        mov [rcx].IMAGE_PE_HEADER32.OptionalHeader.SizeOfImage,sizeimg
        mov [rcx].IMAGE_PE_HEADER32.OptionalHeader.SizeOfHeaders,sizehdr
        mov datadir,&[rcx].IMAGE_PE_HEADER32.OptionalHeader.DataDirectory
    .endif
endif

    ; set export directory data dir value

    .if ( SymFind( edataname ) )

        mov rsi,[rax].asym.seginfo
        mov rcx,datadir
        mov [rcx][IMAGE_DIRECTORY_ENTRY_EXPORT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[rax].asym.max_offset
        mov [rcx][IMAGE_DIRECTORY_ENTRY_EXPORT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[rsi].start_offset
    .endif

    ; set import directory and IAT data dir value

    .if ( SymFind( ".idata$" IMPDIRSUF ) )

       .new idata_null:asym_t
       .new idata_iat:asym_t
       .new size:uint_32

        mov rdi,rax
        mov idata_null,SymFind( ".idata$" IMPNDIRSUF ) ; final NULL import directory entry
        mov idata_iat, SymFind( ".idata$" IMPIATSUF )  ; IAT entries

        mov rcx,idata_null
        mov rsi,[rcx].asym.seginfo
        mov eax,[rsi].start_offset
        add eax,[rcx].asym.max_offset
        mov rsi,[rdi].asym.seginfo
        sub eax,[rsi].start_offset
        mov rdx,datadir
        mov [rdx][IMAGE_DIRECTORY_ENTRY_IMPORT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,eax
        mov [rdx][IMAGE_DIRECTORY_ENTRY_IMPORT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[rsi].start_offset

        mov rcx,idata_iat
        mov rsi,[rcx].asym.seginfo
        mov [rdx][IMAGE_DIRECTORY_ENTRY_IAT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[rsi].start_offset
        mov [rdx][IMAGE_DIRECTORY_ENTRY_IAT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[rcx].asym.max_offset
    .endif

    ; set resource directory data dir value

    .if ( SymFind( ".rsrc" ) )

        mov rsi,[rax].asym.seginfo
        mov rdx,datadir
        mov [rdx][IMAGE_DIRECTORY_ENTRY_RESOURCE*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[rax].asym.max_offset
        mov [rdx][IMAGE_DIRECTORY_ENTRY_RESOURCE*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[rsi].start_offset
    .endif

    ; set relocation data dir value

    .if ( SymFind( ".reloc" ) )

        mov rsi,[rax].asym.seginfo
        mov rdx,datadir
        mov [rdx][IMAGE_DIRECTORY_ENTRY_BASERELOC*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[rax].asym.max_offset
        mov [rdx][IMAGE_DIRECTORY_ENTRY_BASERELOC*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[rsi].start_offset
    .endif

    ; fixme: TLS entry is not written because there exists a segment .tls, but
    ; because a _tls_used symbol is found ( type: IMAGE_THREAD_DIRECTORY )

    .if ( SymFind(".tls") )

        mov rsi,[rax].asym.seginfo
        mov rdx,datadir
        mov [rdx][IMAGE_DIRECTORY_ENTRY_TLS*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[rax].asym.max_offset
        mov [rdx][IMAGE_DIRECTORY_ENTRY_TLS*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[rsi].start_offset
    .endif

ifndef ASMC64
    .if ( MODULE.defOfssize == USE64 )
endif
        .if ( SymFind( ".pdata" ) )

            mov rsi,[rax].asym.seginfo
            mov rdx,datadir
            mov [rdx][IMAGE_DIRECTORY_ENTRY_EXCEPTION*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[rax].asym.max_offset
            mov [rdx][IMAGE_DIRECTORY_ENTRY_EXCEPTION*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[rsi].start_offset
        .endif
        mov rcx,pe
ifdef _WIN64
        mov rax,[rcx].IMAGE_PE_HEADER64.OptionalHeader.ImageBase
        .if ( eax == PE_UNDEF_BASE )
            mov rax,PE64_DEF_BASE_EXE
            .if ( ff & IMAGE_FILE_DLL )
                mov rax,PE64_DEF_BASE_DLL
            .elseif !( [rcx].IMAGE_PE_HEADER32.FileHeader.Characteristics & IMAGE_FILE_LARGE_ADDRESS_AWARE )
                mov eax,PE32_DEF_BASE_EXE
            .endif
            mov [rcx].IMAGE_PE_HEADER64.OptionalHeader.ImageBase,rax
        .endif
        mov rcx,cp
        mov [rcx].calc_param.imagebase64,rax
else
        mov eax,dword ptr [rcx].IMAGE_PE_HEADER64.OptionalHeader.ImageBase
        mov edx,dword ptr [rcx].IMAGE_PE_HEADER64.OptionalHeader.ImageBase[4]
        .if ( eax == PE_UNDEF_BASE )
            mov eax,LOW32(PE64_DEF_BASE_EXE)
            mov edx,HIGH32(PE64_DEF_BASE_EXE)
            .if ( ff & IMAGE_FILE_DLL )
                mov eax,LOW32(PE64_DEF_BASE_DLL)
                mov edx,HIGH32(PE64_DEF_BASE_DLL)
            .endif
            mov dword ptr [rcx].IMAGE_PE_HEADER64.OptionalHeader.ImageBase,eax
            mov dword ptr [rcx].IMAGE_PE_HEADER64.OptionalHeader.ImageBase[4],edx
        .endif
        mov rcx,cp
        mov dword ptr [rcx].calc_param.imagebase64,eax
        mov dword ptr [rcx].calc_param.imagebase64[4],edx
endif
ifndef ASMC64
    .else
        ; v2.16: set default base for dll/exe
        mov rcx,pe
        .if ( [rcx].IMAGE_PE_HEADER32.OptionalHeader.ImageBase == PE_UNDEF_BASE )
            mov eax,PE32_DEF_BASE_EXE
            .if ( ff & IMAGE_FILE_DLL )
                mov eax,PE32_DEF_BASE_DLL
            .endif
            mov [rcx].IMAGE_PE_HEADER32.OptionalHeader.ImageBase,eax
        .endif
        mov rcx,cp
        mov [rcx].calc_param.imagebase,GHF( OptionalHeader.ImageBase )
    .endif
endif
    ret

pe_set_values endp


; v2.11: this function is called when the END directive has been found.
; Previously the code was run inside EndDirective() directly.

pe_enddirhook proc

    pe_create_MZ_header()
    pe_emit_export_data()

    .if ( MODULE.DllQueue )
        pe_emit_import_data()
    .endif

    pe_create_section_table()
   .return( NOT_ERROR )

pe_enddirhook endp


; write section contents
; this is done after the last step only!

bin_write_module proc uses rsi rdi rbx

    .new curr:asym_t
    .new size:uint_32
    .new sizetotal:uint_32
    .new i:int_t
    .new first:int_t
    .new sizeheap:uint_32
    .new pMZ:ptr IMAGE_DOS_HEADER
    .new reloccnt:uint_16
    .new sizemem:uint_32
    .new stackp:asym_t = NULL
    .new hdrbuf:ptr uint_8
    .new cp:calc_param = {0}
ifdef _LIN64
    .new _rdi:ptr
    .new _rsi:ptr
endif
    .new nullbyt:char_t = 0

    mov cp.first,TRUE
    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].asym.next )

        mov rsi,[rdi].asym.seginfo

        ; reset the offset fields of segments
        ; it was used to store the size in there

        mov [rsi].start_offset,0

        ; set STACK segment type

        .if ( [rsi].combine == COMB_STACK )
            mov [rsi].segtype,SEGTYPE_STACK
        .endif
    .endf

    ; calculate size of header

    xor eax,eax
    .if ( MODULE.sub_format == SFORMAT_MZ )

        mov     reloccnt,GetSegRelocs( NULL )
        shl     eax,2
        movzx   edx,MODULE.mz_ofs_fixups
        add     eax,edx
        movzx   edx,MODULE.mz_alignment
        dec     edx
        add     eax,edx
        not     edx
        and     eax,edx
    .endif
    mov cp.sizehdr,eax

    mov cp.fileoffset,eax
    .if ( eax )
        mov hdrbuf,LclAlloc( eax )
        ;tmemset( rax, 0, cp.sizehdr ) -- zero alloc...
    .endif
    mov cp.entryoffset,-1

    ; set starting offsets for all sections

    mov cp.rva,0
    .if ( MODULE.sub_format == SFORMAT_PE || MODULE.sub_format == SFORMAT_64BIT )

        .if ( MODULE._model == MODEL_NONE )
            .return( asmerr( 2013 ) )
        .endif
        pe_set_values( &cp )

    .elseif ( MODULE.segorder == SEGORDER_DOSSEG )

        ; for .DOSSEG, regroup segments (CODE, UNDEF, DATA, BSS)

        .for ( ebx = 0 : ebx < SIZE_DOSSEG : ebx++ )

            .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].asym.next )

                mov rsi,[rdi].asym.seginfo
                lea rcx,dosseg_order
                .continue .if ( [rsi].segtype != [rcx+rbx*4] )
                CalcOffset( rdi, &cp )
            .endf
        .endf
        SortSegments( 0 )

    .else ; segment order .SEQ (default) and .ALPHA

        .if ( MODULE.segorder == SEGORDER_ALPHA )
            SortSegments( 1 )
        .endif

        .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].asym.next )

            ; ignore absolute segments
            CalcOffset( rdi, &cp )
        .endf
    .endif

    ; handle relocs

    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].asym.next )

        DoFixup( rdi, &cp )
        mov rsi,[rdi].asym.seginfo
        .if ( stackp == NULL && [rsi].combine == COMB_STACK )
            mov stackp,rdi
        .endif
    .endf

    ; v2.04: return if any errors occured during fixup handling

    .if ( MODULE.error_count )
        .return( ERROR )
    .endif

    ; for plain binaries make sure the start label is at
    ; the beginning of the first segment

    .if ( MODULE.sub_format == SFORMAT_NONE )
        .if ( MODULE.start_label )
            mov rax,MODULE.start_label
            .if ( cp.entryoffset == -1 || cp.entryseg != [rax].asym.segm )
                .return( asmerr( 3003 ) )
            .endif
        .endif
    .endif

    mov sizetotal,GetImageSize( FALSE )

    ; for MZ|PE format, initialize the header

    .if ( MODULE.sub_format == SFORMAT_MZ )

        ; set fields in MZ header

        assume rdi:ptr IMAGE_DOS_HEADER
        mov rdi,hdrbuf
        mov [rdi].e_magic,'M' + ('Z' shl 8)
        mov ecx,512
        mov eax,sizetotal
        cdq
        div ecx
        mov [rdi].e_cblp,dx ;; bytes last page
        .if edx
            inc eax
        .endif
        mov [rdi].e_cp,ax   ;; pages
        mov [rdi].e_crlc,reloccnt
        mov eax,cp.sizehdr
        shr eax,4
        mov [rdi].e_cparhdr,ax ;; size header in paras
        GetImageSize( TRUE )
        sub eax,sizetotal
        mov sizeheap,eax
        mov edx,eax
        shr eax,4
        and edx,0x0F
        .ifnz
            inc eax
        .endif
        mov [rdi].e_minalloc,ax ;; heap min
        .if ( ax < MODULE.mz_heapmin )
            mov [rdi].e_minalloc,MODULE.mz_heapmin
        .endif
        mov [rdi].e_maxalloc,MODULE.mz_heapmax ;; heap max
        .if ( ax < [rdi].e_minalloc )
            mov [rdi].e_maxalloc,[rdi].e_minalloc
        .endif

        ; set stack if there's one defined

        .if ( stackp )
            mov rcx,stackp
            mov rsi,[rcx].asym.seginfo
            mov eax,[rsi].start_offset
            .if ( [rsi].sgroup )
                mov rdx,[rsi].sgroup
                add eax,[rdx].asym.offs
            .endif
            xor edx,edx
            .if eax & 0x0F
                inc edx
            .endif
            shr eax,4
            add eax,edx
            mov [rdi].e_ss,ax ;; SS

            ; v2.11: changed sym.offset to sym.max_offset

            mov [rdi].e_sp,[rcx].asym.max_offset ; SP
        .else
            asmerr( 8010 )
        .endif
        mov [rdi].e_csum,0 ; checksum

        ; set entry CS:IP if defined

        .if ( MODULE.start_label )

            mov rcx,MODULE.start_label
            mov rdx,[rcx].asym.segm
            mov rsi,[rdx].asym.seginfo

            .if ( [rsi].sgroup )

                mov rax,[rsi].sgroup
                mov eax,[rax].asym.offs
                mov ebx,eax
                mov edx,eax
                shr edx,4
                and eax,0x0F
                add eax,[rsi].start_offset
                add eax,[rcx].asym.offs
                mov [rdi].e_ip,ax
                mov [rdi].e_cs,dx

            .else

                mov eax,[rsi].start_offset
                mov ebx,eax
                mov edx,eax
                shr edx,4
                and eax,0x0F
                add eax,[rcx].asym.offs
                mov [rdi].e_ip,ax
                mov [rdi].e_cs,dx
            .endif
            ; v2.19: error if CS:IP doesn't fit in 20-bit
            .if ( ebx >= 0x100000 || [rcx].asym.offs >= 0x10000 )
                .return( asmerr( 3003 ) )
            .endif
            ; v2.12: warn if entry point is in a 32-/64-bit segment
            .if ( [rsi].Ofssize > USE16 )
                asmerr( 7009 )
            .endif
        .else
            asmerr( 8009 )
        .endif

        mov [rdi].e_lfarlc,MODULE.mz_ofs_fixups
        add rax,hdrbuf
        GetSegRelocs( rax )
    .endif

    assume rdi:nothing

    .if ( CurrFile[LST*string_t] )

        ; go to EOF

        fseek( CurrFile[LST*string_t], 0, SEEK_END )
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

        fwrite( hdrbuf, 1, cp.sizehdr, CurrFile[OBJ*string_t] )
        .if ( eax  != cp.sizehdr )
            WriteError()
        .endif
        LstPrintf( szSegLine, szHeader, 0, 0, cp.sizehdr, 0 )
        LstNL()
    .endif

    ; write sections

    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head, first = TRUE : rdi : rdi = [rdi].asym.next )

        mov rsi,[rdi].asym.seginfo
        .continue .if ( [rsi].segtype == SEGTYPE_ABS )

        .if ( ( MODULE.sub_format == SFORMAT_PE || MODULE.sub_format == SFORMAT_64BIT ) &&
              ( [rsi].segtype == SEGTYPE_BSS || [rsi].information ) )
            xor eax,eax
            .if ( [rsi].information )
                .continue ; v2.19: info sections shouldn't appear in binary map
            .endif
        .else
            ; v2.19: subtract start_loc only if -bin AND first segment
            mov eax,[rdi].asym.max_offset
            .if ( first && MODULE.sub_format == SFORMAT_NONE )
                sub eax,[rsi].start_loc
            .endif
        .endif
        mov size,eax
        .if first == 0
            mov eax,[rdi].asym.max_offset
        .endif
        mov sizemem,eax

        ; if no bytes have been written to the segment, check if there's
        ; any further segments with bytes set. If no, skip write!

        .if ( [rsi].bytes_written == 0 )
            .for ( rdx = [rdi].asym.next: rdx: rdx = [rdx].asym.next )
                mov rcx,[rdx].asym.seginfo
                .break .if ( [rcx].seg_info.bytes_written )
            .endf
            .if ( !rdx )
                mov size,edx
                mov [rsi].fileoffset,edx
            .endif
        .endif

        mov ecx,[rsi].start_offset
        .if first
            add ecx,[rsi].start_loc
        .endif
        LstPrintf( szSegLine, [rdi].asym.name, [rsi].fileoffset, ecx, size, sizemem )
        LstNL()

        .if ( size ) ; v2.13: write in any case, even if bss segment
ifdef _LIN64
            mov _rdi,rdi
            mov _rsi,rsi
endif
            fseek( CurrFile[OBJ*string_t], [rsi].fileoffset, SEEK_SET )
ifdef _LIN64
            mov rsi,_rsi
endif
            .if ( [rsi].CodeBuffer )

                ; v2.19 write null bytes if start_loc != 0

                .if ( first && MODULE.sub_format == SFORMAT_NONE )
                    ;
                .elseif ( [rsi].start_loc )

                    .for ( ebx = [rsi].start_loc : ebx : ebx-- )
                        fwrite( &nullbyt, 1, 1, CurrFile[OBJ*string_t] )
                    .endf
ifdef _LIN64
                    mov rsi,_rsi
endif
                    sub size,[rsi].start_loc
                .endif
ifdef _LIN64
                mov rdi,rsi
                fwrite( [rdi].seg_info.CodeBuffer, 1, size, CurrFile[OBJ*string_t] )
else
                fwrite( [rsi].CodeBuffer, 1, size, CurrFile[OBJ*string_t] )
endif
                .if ( eax != size )
                    WriteError()
                .endif
            .else
                .for ( : size : size-- )
                    fwrite( &nullbyt, 1, 1, CurrFile[OBJ*string_t] )
                .endf
            .endif
ifdef _LIN64
            mov rsi,_rsi
            mov rdi,_rdi
endif
        .endif
        mov first,FALSE
    .endf

    .if ( MODULE.sub_format == SFORMAT_PE || MODULE.sub_format == SFORMAT_64BIT )

        mov ecx,ftell( CurrFile[OBJ*string_t] )
        mov eax,cp.rawpagesize
        dec eax
        .if ( ecx & eax )
            lea ebx,[rax+1]
            and eax,ecx
            sub ebx,eax
if 1
            .for ( : ebx : ebx-- )
                fwrite( &nullbyt, 1, 1, CurrFile[OBJ*string_t] )
            .endf
else
            tmemset( alloca(ebx), 0, size )
            fwrite( rax, 1, ebx, CurrFile[OBJ*string_t] )
endif
        .endif
    .endif
    LstPrintf( szSep )
    LstNL()

    .if ( MODULE.sub_format == SFORMAT_MZ )

        mov eax,sizetotal
        sub eax,cp.sizehdr
        add sizeheap,eax
    .elseif ( MODULE.sub_format == SFORMAT_PE || MODULE.sub_format == SFORMAT_64BIT )
        mov sizeheap,cp.rva
    .else
        mov sizeheap,GetImageSize( TRUE )
    .endif

    LstPrintf( szTotal, " ", sizetotal, sizeheap )
    LstNL()
   .return( NOT_ERROR )

bin_write_module endp


bin_check_external proc

    .for ( rdx = SymTables[TAB_EXT*symbol_queue].head : rdx : rdx = [rdx].asym.next )
        .if ( !( [rdx].asym.weak ) || [rdx].asym.used )
            .if ( !( [rdx].asym.isinline ) )
                .return( asmerr( 2014, [rdx].asym.name ) )
            .endif
        .endif
    .endf
    .return( NOT_ERROR )

bin_check_external endp


bin_init proc public uses rsi rdi rbx

    mov MODULE.WriteModule,&bin_write_module
    mov MODULE.Pass1Checks,&bin_check_external
    mov al,MODULE.sub_format
    .switch al
ifndef ASMC64
    .case SFORMAT_MZ
        lea rdi,MODULE.mz_ofs_fixups
        lea rsi,mzdata
        mov ecx,sizeof( MZDATA )
        rep movsb
       .endc
endif
    .case SFORMAT_PE
    .case SFORMAT_64BIT
        mov MODULE.EndDirHook,&pe_enddirhook ;; v2.11
       .endc
    .endsw
    ret

bin_init endp

    end
