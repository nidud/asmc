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

;
; pespec.inc contains MZ header declaration
;

include pespec.inc

SortSegments proto __ccall :int_t

.data

;
; if the structure changes, option.c, SetMZ() might need adjustment!
;

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
    SEGTYPE_CODE,
    SEGTYPE_CDATA,
    SEGTYPE_DATA,
    SEGTYPE_BSS,
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

    align size_t

ifndef ASMC64

;
; default 32-bit PE header
;

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

;
; default 64-bit PE header
;

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

    ;
    ; calculate starting offset of segments and groups
    ;

    assume rbx:ptr calc_param
    assume rdi:ptr seg_info

CalcOffset proc fastcall uses rsi rdi rbx curr:ptr dsym, cp:ptr calc_param

    mov rsi,rcx
    mov rbx,rdx
    mov rdi,[rsi].dsym.seginfo

    .if ( [rdi].segtype == SEGTYPE_ABS )

        mov eax,[rdi].abs_frame
        shl eax,4
        mov [rdi].start_offset,eax
       .return
    .elseif ( [rdi].info )
       .return
    .endif

    mov edx,1
    .if ( [rbx].alignment > [rdi].alignment )
        mov cl,[rbx].alignment
    .else
        mov cl,[rdi].alignment
    .endif
    shl edx,cl
   .new alignment:uint_t = edx

    mov ecx,edx
    neg ecx
    dec edx
    add edx,[rbx].fileoffset
    and edx,ecx
    sub edx,[rbx].fileoffset
    add [rbx].fileoffset,edx

   .new alignbytes:uint_t = edx
   .new grp:dsym_t = [rdi].sgroup
   .new offs:uint_t

    .if ( rax == NULL )

        mov eax,[rbx].fileoffset
        sub eax,[rbx].sizehdr
        mov offs,eax

    .else
        .if ( ModuleInfo.sub_format == SFORMAT_PE || ModuleInfo.sub_format == SFORMAT_64BIT )

            ;
            ; v2.24
            ;

            mov offs,[rbx].rva
        .else

            .if ( [rax].asym.total_size == 0 )

                mov ecx,[rbx].fileoffset
                sub ecx,[rbx].sizehdr
                mov [rax].asym.offs,ecx
                mov offs,0

            .else

                ;
                ; v2.12: the old way wasn't correct. if there's a segment between the
                ; segments of a group, it affects the offset as well ( if it
                ; occupies space in the file )! the value stored in grp->sym.total_size
                ; is no longer used (or, more exactly, used as a flag only).
                ;
                ; offset = ( cp->fileoffset - cp->sizehdr ) - grp->sym.offset;
                ;

                mov ecx,[rax].asym.total_size
                add ecx,alignbytes
                mov offs,ecx
            .endif
        .endif
    .endif

    ; v2.04: added
    ; v2.05: this addition did mess sample Win32_5.asm, because the
    ; "empty" alignment sections are now added to <fileoffset>.
    ; todo: VA in binary map is displayed wrong.

    .if ( [rbx].first == FALSE )

        ; v2.05: do the reset more carefully.
        ; Do reset start_loc only if
        ; - segment is in a group and
        ; - group isn't FLAT or segment's name contains '$'

        mov rax,grp
        .if ( rax )
            .if ( rax != ModuleInfo.flat_grp )
                mov [rdi].start_loc,0
            .elseif ( tstrchr( [rsi].asym.name, '$' ) )
                mov [rdi].start_loc,0
            .endif
        .endif
    .endif

    mov [rdi].fileoffset,[rbx].fileoffset
    mov [rdi].start_offset,offs

    .if ( ModuleInfo.sub_format == SFORMAT_NONE )

        mov eax,[rsi].asym.max_offset
        sub eax,[rdi].start_loc
        add [rbx].fileoffset,eax

        .if ( [rbx].first )

            mov [rbx].imagestart,[rdi].start_loc
        .endif

        ; there's no real entry address for BIN, therefore the
        ; start label must be at the very beginning of the file

        .if ( [rbx].entryoffset == -1 )

            mov [rbx].entryoffset,offs
            mov [rbx].entryseg,rsi
        .endif
    .else

        mov eax,[rsi].asym.max_offset
        sub eax,[rdi].start_loc
        add [rbx].rva,eax
        .if ( [rdi].segtype != SEGTYPE_BSS )
            add [rbx].fileoffset,eax
        .endif
    .endif

    add offs,[rsi].asym.max_offset
    mov rcx,grp
    .if rcx

        mov [rcx].asym.total_size,offs

        ; v2.07: for 16-bit groups, ensure that it fits in 64 kB

        .if ( [rcx].asym.total_size > 0x10000 && [rcx].asym.Ofssize == USE16 )

            asmerr( 8003, [rcx].asym.name )
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

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head : rsi : rsi = [rsi].dsym.next )

        mov rdi,[rsi].dsym.seginfo
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
                    .if ( rcx && [rcx].dsym.seginfo )

                        mov rax,[rcx].dsym.seginfo
                       .endc .if ( [rax].seg_info.segtype == SEGTYPE_ABS )
                    .endif
                .endif

                inc count

                .if ( pDst )

                    ; v2.04: fixed

                    mov eax,[rbx].locofs
                    mov ecx,[rdi].start_offset
                    and ecx,0xf
                    add ecx,eax

                    mov eax,[rdi].start_offset
                    shr eax,4

                    .if [rdi].sgroup

                        mov rdx,[rdi].sgroup
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

GetImageSize proc __ccall uses rsi rdi rbx memimage:int_t

    .new first:uint_32 = TRUE

    .for ( rsi = SymTables[TAB_SEG*symbol_queue].head,
           eax = 0, ebx = 0 : rsi : rsi = [rsi].dsym.next )

        mov rdi,[rsi].dsym.seginfo
        .if ( [rdi].segtype == SEGTYPE_ABS || [rdi].info )
            .continue
        .endif

        .if ( memimage == FALSE )

            .if ( [rdi].bytes_written == 0 )

                .for ( rcx = [rsi].dsym.next : rcx : rcx = [rcx].dsym.next )

                    mov rdx,[rcx].dsym.seginfo
                   .break .if ( [rdx].seg_info.bytes_written )
                .endf
                .break .if !rcx ; done, skip rest of segments!
            .endif
        .endif

        mov ecx,[rsi].asym.max_offset
        sub ecx,[rdi].start_loc
        add ecx,[rdi].fileoffset

        .if ( first == FALSE )
            add ebx,[rdi].start_loc
        .endif
        .if ( memimage )
            add ecx,ebx
        .endif
        .if ( eax < ecx )
            mov eax,ecx
        .endif
        mov first,FALSE
    .endf
    ret

GetImageSize endp


; micro-linker. resolve internal fixups.
;
; handle the fixups contained in a segment

DoFixup proc __ccall uses rsi rdi rbx curr:ptr dsym, cp:ptr calc_param

   .new value:uint_32
   .new value64:uint_64

    mov rsi,curr
    mov rdi,[rsi].dsym.seginfo

    .if ( [rdi].segtype == SEGTYPE_ABS )
        .return( NOT_ERROR )
    .endif

    .for ( rbx = [rdi].head : rbx : rbx = [rbx].nextrlc )

        mov eax,[rbx].locofs
        sub eax,[rdi].start_loc
        add rax,[rdi].CodeBuffer
        mov rcx,[rbx].sym

        .new codeptr:ptr = rax

        .if ( rcx && ( [rcx].asym.segm || [rcx].asym.flags & S_VARIABLE ) )

            ; assembly time variable (also $ symbol) in reloc?
            ; v2.07: moved inside if-block, using new local var "offset"

            .new offs:uint_32
            .if ( [rcx].asym.flags & S_VARIABLE )

                mov rsi,[rbx].segment_var
                mov offs,0

            .else
                mov rsi,[rcx].asym.segm
                mov offs,[rcx].asym.offs
            .endif
            .new segm:dsym_t = rsi

            mov rsi,[rsi].dsym.seginfo
            assume rsi:ptr seg_info

            ;
            ; the offset result consists of
            ; - the symbol's offset
            ; - the fixup's offset (usually the displacement )
            ; - the segment/group offset in the image
            ;

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

                ;
                ; check if symbol's segment name contains a '$'.
                ; If yes, search the segment without suffix.
                ;

                mov rcx,segm
                .if ( tstrchr( [rcx].asym.name, '$' ) )

                    mov rcx,segm
                    sub rax,[rcx].asym.name

                    .for ( rdx = SymTables[TAB_SEG*symbol_queue].head : rdx : rdx = [rdx].dsym.next )

                        .if ( [rdx].asym.name_size == eax )

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
                                mov rcx,[rdx].dsym.seginfo
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

                ;
                ; v1.96: special handling for "relative" fixups
                ; v2.28: removed fixup->offset..
                ;

                mov eax,[rsi].start_offset
                add eax,offs
                mov value,eax
               .endc

            .default

                .if ( [rsi].sgroup && [rbx].frame_type != FRAME_SEG )

                    mov rcx,[rsi].sgroup
                    mov eax,[rcx].asym.offs
                    and eax,0x0F
                    add eax,[rsi].start_offset
                    add eax,[rbx].offs
                    add eax,offs
                    mov value,eax

                    .if ( ModuleInfo.sub_format == SFORMAT_PE || ModuleInfo.sub_format == SFORMAT_64BIT )

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

                    mov eax,[rsi].start_offset
                    and eax,0xF
                    add eax,[rbx].offs
                    add eax,offs
                    mov value,eax
                .endif
                .endc
            .endsw
        .else
            mov segm,NULL
            mov value,0
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
        .case FIX_OFF32_IMGREL
        .case FIX_OFF32_SECREL
            mov [rcx],eax
           .endc
        .case FIX_OFF64
ifndef _WIN64
            xor edx,edx
endif
            .if ( ( ModuleInfo.sub_format == SFORMAT_PE && [rdi].Ofssize == USE64 ) ||
                  ModuleInfo.sub_format == SFORMAT_64BIT )
                .l8 value64
            .endif
            .s8 [rcx]
            .endc
        .case FIX_HIBYTE
            mov al,ah
            mov [rcx],al
           .endc
        .case FIX_SEG

            ; absolute segments are ok

            mov rax,[rbx].sym
            .if rax && [rax].asym.state == SYM_SEG
                mov rdx,[rax].dsym.seginfo
                .if [rdx].seg_info.segtype == SEGTYPE_ABS
                    mov edx,[rdx].seg_info.abs_frame
                    mov [rcx],dx
                   .endc
                .endif
            .endif

            .if ( ModuleInfo.sub_format == SFORMAT_MZ )

                .if ( [rax].asym.state == SYM_GRP )

                    mov segm,rax
                    mov rsi,[rax].dsym.seginfo
                    mov edx,[rax].asym.offs
                    shr edx,4
                    mov [rcx],dx

                .elseif ( [rax].asym.state == SYM_SEG )

                    mov segm,rax
                    mov rsi,[rax].dsym.seginfo
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
            ;
            ; v2.10: absolute segments are ok
            ;
            .if ( segm && [rsi].segtype == SEGTYPE_ABS )
                mov [rcx],ax
                mov eax,[rsi].abs_frame
                mov [rcx+2],ax
               .endc
            .endif
            .if ( ModuleInfo.sub_format == SFORMAT_MZ )
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
            ;
            ; v2.10: absolute segments are ok
            ;
            .if ( segm && [rsi].segtype == SEGTYPE_ABS )

                mov [rcx],eax
                mov eax,[rsi].abs_frame
                mov [rcx+4],ax
               .endc
            .endif

            .if ( ModuleInfo.sub_format == SFORMAT_MZ )

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
            mov rcx,ModuleInfo.fmtopt
            lea rdx,[rcx].format_options.formatname
            mov rcx,curr
            asmerr( 3019, rdx, [rbx].type, [rcx].asym.name, [rbx].locofs )
        .endsw
    .endf
    .return( NOT_ERROR )

DoFixup endp


    assume rsi:ptr module_info, rbx:nothing, rdi:nothing


pe_create_MZ_header proc fastcall uses rsi modinfo:ptr module_info

    mov rsi,rcx

    .if ( Parse_Pass == PASS_1 )

        .if ( SymSearch( hdrname "1" ) == NULL )
            or [rsi].pe_flags,PEF_MZHDR
        .endif
    .endif

    .if ( [rsi].pe_flags & PEF_MZHDR )

        AddLineQueueX(
            "option dotname\n"
            "%s1 segment USE16 word %s\n"
            "db 'MZ'\n"             ; e_magic
            "dw 68h,1,0,4\n"        ; e_cblp, e_cp, e_crlc, e_cparhdr
            "dw 0,-1,0,0B8h\n"      ; e_minalloc, e_maxalloc, e_ss, e_sp
            "dw 0,0,0,40h\n"        ; e_csum, e_ip, e_cs, e_sp, e_lfarlc
            "org 40h\n"             ; e_lfanew, will be set by program
            "push cs\n"
            "pop ds\n"
            "mov dx,@F-40h\n"
            "mov ah,9\n"
            "int 21h\n"
            "mov ax,4C01h\n"
            "int 21h\n"
            "@@:\n"
            "db 'This is a PE executable',0Dh,0Ah,'$'\n"
            "%s1 ends", hdrname, hdrattr, hdrname )

        RunLineQueue()

        .if SymSearch( hdrname "1" )

            .if ( [rax].asym.state == SYM_SEG )

                mov rcx,[rax].dsym.seginfo
                mov [rcx].seg_info.segtype,SEGTYPE_HDR
            .endif
        .endif
    .endif
    ret

pe_create_MZ_header endp


; get/set value of @pe_file_flags variable

set_file_flags proc __ccall sym:ptr asym, opnd:ptr expr

   .return .if !SymSearch( hdrname "2" )

    mov rcx,[rax].dsym.seginfo
    mov rdx,[rcx].seg_info.CodeBuffer
    movzx eax,[rdx].IMAGE_PE_HEADER32.FileHeader.Characteristics

    .if ( opnd ) ; set the value?

        mov rcx,opnd
        mov eax,[rcx].expr.value
        mov [rdx].IMAGE_PE_HEADER32.FileHeader.Characteristics,ax
    .endif
    mov rcx,sym
    mov [rcx].asym.value,eax
    ret

set_file_flags endp


    assume rsi:ptr seg_info

pe_create_PE_header proc public uses rsi rdi rbx

    .if ( Parse_Pass == PASS_1 )

        .if ( ModuleInfo._model != MODEL_FLAT )
            asmerr( 3002 )
        .endif

ifndef ASMC64
        .if ( ModuleInfo.defOfssize == USE64 )
endif
            mov ebx,IMAGE_PE_HEADER64
            lea rdi,pe64def
            mov pe64def.OptionalHeader.Subsystem,IMAGE_SUBSYSTEM_WINDOWS_CUI
            .if ( Options.pe_subsystem == 1 )
                mov pe64def.OptionalHeader.Subsystem,IMAGE_SUBSYSTEM_WINDOWS_GUI
            .endif


            mov eax,0x400000
ifndef _WIN64
            cdq
endif
            .if ( ModuleInfo.sub_format == SFORMAT_64BIT )

ifdef _WIN64
                mov rax,0x140000000
else
                mov eax,LOW32(0x140000000)
                mov edx,HIGH32(0x140000000)
endif
            .endif
            .s8 pe64def.OptionalHeader.ImageBase

ifndef ASMC64

        .else

            mov ebx,IMAGE_PE_HEADER32
            lea rdi,pe32def
            mov pe32def.OptionalHeader.Subsystem,IMAGE_SUBSYSTEM_WINDOWS_CUI
            .if ( Options.pe_subsystem == 1 )
                mov pe32def.OptionalHeader.Subsystem,IMAGE_SUBSYSTEM_WINDOWS_GUI
            .endif
        .endif
endif

        .if !SymSearch( hdrname "2" )

            CreateIntSegment( hdrname "2", "HDR", 2, ModuleInfo.defOfssize, TRUE )

            mov [rax].asym.max_offset,ebx
            mov rsi,[rax].dsym.seginfo
            mov rcx,ModuleInfo.flat_grp
            mov [rsi].sgroup,rcx
            mov [rsi].combine,COMB_ADDOFF  ; PUBLIC
            mov [rsi].characteristics,(IMAGE_SCN_MEM_READ shr 24)
            mov [rsi].readonly,1
            mov [rsi].bytes_written,ebx ; ensure that ORG won't set start_loc (assemble.c, SetCurrOffset)

        .else

            .if ( [rax].asym.max_offset < ebx )
                mov [rax].asym.max_offset,ebx
            .endif

            mov rsi,[rax].dsym.seginfo
            mov [rsi].internal,TRUE
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

            or [rax].asym.flags,S_PREDEFINED
            lea rcx,set_file_flags
            mov [rax].asym.sfunc_ptr,rcx
        .endif
    .endif
    ret

pe_create_PE_header endp


define CHAR_READONLY ( IMAGE_SCN_MEM_READ shr 24 )

pe_create_section_table proc __ccall uses rsi rdi rbx

   .new objtab:ptr dsym
   .new bCreated:int_t = FALSE

    .if ( Parse_Pass == PASS_1 )

        .if SymSearch( hdrname "3" )

            mov rdi,rax
            mov rsi,[rdi].dsym.seginfo
        .else

            mov bCreated,TRUE
            mov rdi,CreateIntSegment( hdrname "3", "HDR", 2, ModuleInfo.defOfssize, TRUE )
            mov rsi,[rdi].dsym.seginfo
            mov [rsi].sgroup,ModuleInfo.flat_grp
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

        .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].dsym.next )

            mov rsi,[rdi].dsym.seginfo
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

        ;
        ; count objects ( without header types )
        ;

        .for ( ebx = 1, esi = 0 : ebx < SIZE_PEFLAT : ebx++ )

            lea rcx,flat_order
            .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].dsym.next )

                mov rdx,[rdi].dsym.seginfo
                .if ( [rdx].seg_info.segtype == [rcx+rbx*4] )
                    .if ( [rdi].asym.max_offset )

                        inc esi
                       .break
                    .endif
                .endif
            .endf
        .endf

        .if ( esi )

            mov rdi,objtab
            imul ebx,esi,IMAGE_SECTION_HEADER
            mov [rdi].asym.max_offset,ebx

            ; alloc space for 1 more section (.reloc)

            mov rsi,[rdi].dsym.seginfo
            mov [rsi].CodeBuffer,LclAlloc( &[rbx+IMAGE_SECTION_HEADER] )
        .endif
    .endif
    ret

pe_create_section_table endp


expitem struct
name    string_t ?
idx     dd ?
expitem ends

compare_exp proc __ccall p1:ptr expitem, p2:ptr expitem
    .return( tstrcmp( [rcx].expitem.name, [rdx].expitem.name ) )
compare_exp endp


pe_emit_export_data proc __ccall uses rsi rdi rbx

  local timedate:int_32
  local cnt:int_t
  local name:string_t
  local pitems:ptr expitem

    .for ( rdi = SymTables[TAB_PROC*symbol_queue].head, ebx = 0 : rdi : rdi = [rdi].dsym.nextproc )
        mov rdx,[rdi].dsym.procinfo
        .if ( [rdx].proc_info.flags & PROC_ISEXPORT )
            inc ebx
        .endif
    .endf
    .return .if ( ebx == 0 )

    time( &timedate )
    lea rsi,ModuleInfo.name

    ; create .edata segment

    AddLineQueueX(
        "option dotname\n"
        "%s segment dword %s\n"
        "DD 0, 0%xh, 0, imagerel @%s_name, %u, %u, %u, imagerel @%s_func, imagerel @%s_names, imagerel @%s_nameord",
        edataname, edataattr, timedate, rsi, 1, ebx, ebx, rsi, rsi, rsi )

    mov name,rsi
    mov cnt,ebx

    ; the name pointer table must be in ascending order!
    ; so we have to fill an array of exports and sort it.

    imul ecx,ebx,expitem
    mov pitems,alloca(ecx)

    assume rsi:ptr expitem
    .for ( rdi = SymTables[TAB_PROC*symbol_queue].head,
           rsi = rax, ebx = 0 : rdi : rdi = [rdi].dsym.nextproc )

        mov rdx,[rdi].dsym.procinfo
        .if ( [rdx].proc_info.flags & PROC_ISEXPORT )

            mov [rsi].name,[rdi].asym.name
            mov [rsi].idx,ebx
            inc ebx
            add rsi,expitem
        .endif
    .endf
    tqsort( pitems, cnt, sizeof( expitem ), &compare_exp )

    ;
    ; emit export address table.
    ; would be possible to just use the array of sorted names,
    ; but we want to emit the EAT being sorted by address.
    ;

    AddLineQueueX( "@%s_func label dword", name )

    .for ( rdi = SymTables[TAB_PROC*symbol_queue].head : rdi : rdi = [rdi].dsym.nextproc )

        mov rdx,[rdi].dsym.procinfo
        .if ( [rdx].proc_info.flags & PROC_ISEXPORT )

            AddLineQueueX( "dd imagerel %s", [rdi].asym.name )
        .endif
    .endf

    ;
    ; emit the name pointer table
    ;
    AddLineQueueX( "@%s_names label dword", name )

    .for ( rsi = pitems, ebx = 0: ebx < cnt: ebx++, rsi += expitem )
        AddLineQueueX( "dd imagerel @%s", [rsi].name )
    .endf

    ;
    ; ordinal table. each ordinal is an index into the export address table
    ;
    AddLineQueueX( "@%s_nameord label word", name )

    .for ( rsi = pitems, ebx = 0: ebx < cnt: ebx++, rsi += expitem )
        AddLineQueueX( "dw %u", [rsi].idx )
    .endf

    ;
    ; v2.10: name+ext of dll
    ;
    .for ( rbx = CurrFName[OBJ*string_t], rbx += tstrlen( rbx ): rbx > CurrFName[OBJ*string_t]: rbx-- )
        .break .if ( B[rbx] == '/' || B[rbx] == '\' || B[rbx] == ':' )
    .endf
    AddLineQueueX( "@%s_name db '%s',0", name, rbx )

    .for ( rdi = SymTables[TAB_PROC*symbol_queue].head : rdi : rdi = [rdi].dsym.nextproc )

        mov rdx,[rdi].dsym.procinfo
        .if ( [rdx].proc_info.flags & PROC_ISEXPORT )

            Mangle( rdi, StringBufferEnd )
            mov rcx,StringBufferEnd
            .if Options.no_export_decoration
                mov rcx,[rdi].asym.name
            .endif
            AddLineQueueX( "@%s db '%s',0", [rdi].asym.name, rcx )
        .endif
    .endf

    ;
    ; exit .edata segment
    ;
    AddLineQueueX( "%s ends", edataname )
    RunLineQueue()
    ret

pe_emit_export_data endp


;
; write import data.
; convention:
; .idata$2: import directory
; .idata$3: final import directory NULL entry
; .idata$4: ILT entry
; .idata$5: IAT entry
; .idata$6: strings
;

pe_emit_import_data proc __ccall uses rsi rdi rbx

    .new type:int_t = 0
    .new ptrtype:int_t = T_QWORD
    .new cpalign:string_t = "ALIGN(8)"

ifndef ASMC64
    .if ( ModuleInfo.defOfssize != USE64 )
        mov ptrtype,T_DWORD
        mov cpalign,&@CStr("ALIGN(4)")
    .endif
endif

    assume rbx:ptr dll_desc

    .for ( rbx = ModuleInfo.DllQueue: rbx: rbx = [rbx].next )

        .if ( [rbx].cnt )

            .if ( !type )

                mov type,1
                AddLineQueueX(
                    "@LPPROC typedef ptr proc\n"
                    "option dotname" )
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
            AddLineQueueX(
                "%s" IMPDIRSUF " segment dword %s\n"
                "dd imagerel @%s_ilt, 0, 0, imagerel @%s_name, imagerel @%s_iat\n"
                "%s" IMPDIRSUF " ends\n"
                "%s" IMPILTSUF " segment %s %s\n"
                "@%s_ilt label %r",
                rcx, rdx, rsi, rsi, rsi, rcx, rcx, cpalign, rdx, rsi, ptrtype )

            .for ( rdi = SymTables[TAB_EXT*symbol_queue].head : rdi : rdi = [rdi].dsym.next )
                .if ( [rdi].asym.flags & S_IAT_USED && [rdi].asym.dll == rbx )
                    AddLineQueueX( "@LPPROC imagerel @%s_name", [rdi].asym.name )
                .endif
            .endf

            ; ILT termination entry + IAT

            AddLineQueueX(
                "@LPPROC 0\n"
                "%s" IMPILTSUF " ends\n"
                "%s" IMPIATSUF " segment %s %s\n"
                "@%s_iat label %r", idataname, idataname, cpalign, idataattr, rsi, ptrtype )

            .for ( rdi = SymTables[TAB_EXT*symbol_queue].head : rdi : rdi = [rdi].dsym.next )
                .if ( [rdi].asym.flags & S_IAT_USED && [rdi].asym.dll == rbx )
                    Mangle( rdi, StringBufferEnd )
                    AddLineQueueX( "%s%s @LPPROC imagerel @%s_name",
                        ModuleInfo.imp_prefix, StringBufferEnd, [rdi].asym.name )
                .endif
            .endf

            ; IAT termination entry + name table

            AddLineQueueX(
                "@LPPROC 0\n"
                "%s" IMPIATSUF " ends\n"
                "%s" IMPSTRSUF " segment word %s", idataname, idataname, idataattr )

            .for ( rdi = SymTables[TAB_EXT*symbol_queue].head : rdi : rdi = [rdi].dsym.next )
                .if ( [rdi].asym.flags & S_IAT_USED && [rdi].asym.dll == rbx )
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
                "%s" IMPSTRSUF " ends", rsi, &[rbx].name, idataname )

        .endif
    .endf
    .if ( is_linequeue_populated() )

        ; import directory NULL entry

        AddLineQueueX(
            "%s" IMPNDIRSUF " segment dword %s\n"
            "DD 0, 0, 0, 0, 0\n"
            "%s" IMPNDIRSUF " ends", idataname, idataattr, idataname )
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

    mov rcx,[rcx].dsym.seginfo
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
    assume rsi:ptr seg_info

pe_set_base_relocs proc __ccall uses rsi rdi rbx reloc:ptr dsym

  .new cnt1:int_t = 0
  .new cnt2:int_t = 0
  .new ftype:int_t
  .new currpage:uint_32 = -1
  .new currloc:uint_32
  .new curr:ptr dsym
  .new fixp:ptr fixup
  .new baserel:ptr IMAGE_BASE_RELOCATION
  .new prel:ptr uint_16

    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].dsym.next )

        mov rsi,[rdi].dsym.seginfo
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
    mov rsi,[rdi].dsym.seginfo
    mov [rdi].asym.max_offset,ecx
    mov [rsi].CodeBuffer,LclAlloc( ecx )
    mov baserel,rax
    mov [rax].IMAGE_BASE_RELOCATION.VirtualAddress,-1
    add rax,IMAGE_BASE_RELOCATION
    mov prel,rax

    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].dsym.next )

        mov rsi,[rdi].dsym.seginfo
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
                        ;
                        ; address of relocation header must be DWORD aligned
                        ;
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
ifndef ASMC64
 .if ( ModuleInfo.defOfssize == USE64 )
endif
    mov rax,ph64
  if sizeof(IMAGE_PE_HEADER64.x) lt 4
    movzx eax,[rax].IMAGE_PE_HEADER64.x
  elseif sizeof(IMAGE_PE_HEADER64.x) eq 4
    mov eax,[rax].IMAGE_PE_HEADER64.x
  else
    .l8 [rax].IMAGE_PE_HEADER64.x
   endif
ifndef ASMC64
 .else
    mov rax,ph32
  if sizeof(IMAGE_PE_HEADER32.x) lt 4
    movzx eax,[rax].IMAGE_PE_HEADER32.x
  else
    mov eax,[rax].IMAGE_PE_HEADER32.x
  endif
 .endif
endif
    }

;
; set values in PE header
; including data directories:
; special section names:
; .edata - IMAGE_DIRECTORY_ENTRY_EXPORT
; .idata - IMAGE_DIRECTORY_ENTRY_IMPORT, IMAGE_DIRECTORY_ENTRY_IAT
; .rsrc  - IMAGE_DIRECTORY_ENTRY_RESOURCE
; .pdata - IMAGE_DIRECTORY_ENTRY_EXCEPTION (64-bit only)
; .reloc - IMAGE_DIRECTORY_ENTRY_BASERELOC
; .tls   - IMAGE_DIRECTORY_ENTRY_TLS
;

    assume rbx:nothing

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
    .new mzhdr:ptr dsym
    .new pehdr:ptr dsym
    .new objtab:ptr dsym
    .new reloc:ptr dsym = NULL
ifndef ASMC64
    .new ph32:ptr IMAGE_PE_HEADER32
endif
    .new ph64:ptr IMAGE_PE_HEADER64
    .new fh:ptr IMAGE_FILE_HEADER
    .new section:ptr IMAGE_SECTION_HEADER
    .new datadir:ptr IMAGE_DATA_DIRECTORY
    .new secname:string_t
    .new buffer[MAX_ID_LEN+1]:char_t

    mov mzhdr,  SymSearch( hdrname "1" )
    mov rsi,    [rax].dsym.seginfo
    mov pehdr,  SymSearch( hdrname "2" )
    mov objtab, SymSearch( hdrname "3" )

    ;; make sure all header objects are in FLAT group
    mov [rsi].sgroup,ModuleInfo.flat_grp

    mov rax,pehdr
    mov rsi,[rax].dsym.seginfo
    mov rcx,[rsi].CodeBuffer
ifndef ASMC64
    .if ( ModuleInfo.defOfssize == USE64 )
endif
        mov ph64,rcx
        mov ff,[rcx].IMAGE_PE_HEADER64.FileHeader.Characteristics
ifndef ASMC64
    .else
        mov ph32,rcx
        mov ff,[rcx].IMAGE_PE_HEADER32.FileHeader.Characteristics
    .endif
endif
    .if ( !( eax & IMAGE_FILE_RELOCS_STRIPPED ) )

        mov reloc,CreateIntSegment( ".reloc", "RELOC", 2, ModuleInfo.defOfssize, TRUE )

        .if ( rax )

            mov rsi,[rax].dsym.seginfo

            ; make sure the section isn't empty ( true size will be calculated later )

            mov [rax].asym.max_offset,sizeof( IMAGE_BASE_RELOCATION )
            mov [rsi].sgroup,ModuleInfo.flat_grp
            mov [rsi].combine,COMB_ADDOFF
            mov [rsi].segtype,SEGTYPE_RELOC
            mov [rsi].characteristics,((IMAGE_SCN_MEM_DISCARDABLE or IMAGE_SCN_MEM_READ) shr 24 )
            mov [rsi].bytes_written,sizeof( IMAGE_BASE_RELOCATION )

            ; clear the additionally allocated entry in object table

            mov rdx,objtab
            mov rsi,[rdx].dsym.seginfo
            mov edi,[rdx].asym.max_offset
            add [rdx].asym.max_offset,sizeof( IMAGE_SECTION_HEADER )
            add rdi,[rsi].CodeBuffer
            mov ecx,sizeof( IMAGE_SECTION_HEADER )
            xor eax,eax
            rep stosb
        .endif
    .endif

    ; sort: header, executable, readable, read-write segments, resources, relocs

    lea rcx,flat_order
    .for ( ebx = 0: ebx < SIZE_PEFLAT: ebx++ )
        .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].dsym.next )
            mov rsi,[rdi].dsym.seginfo
            .if ( [rsi].segtype == [rcx+rbx*4] )
                mov [rsi].lname_idx,ebx
            .endif
        .endf
    .endf
    SortSegments( 2 )

    mov falign,get_bit( GHF( OptionalHeader.FileAlignment ) )
    mov malign,GHF( OptionalHeader.SectionAlignment )

    ; assign RVAs to sections

    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head, ebx = -1 : rdi : rdi = [rdi].dsym.next )

        mov rsi,[rdi].dsym.seginfo
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
    .if ( reloc )

        pe_set_base_relocs( reloc )

        mov rcx,reloc
        mov rsi,[rcx].dsym.seginfo
        mov eax,[rcx].asym.max_offset
        add eax,[rsi].start_offset
        mov [rbx].calc_param.rva,eax
    .endif

    mov sizeimg,[rbx].calc_param.rva

    ; set e_lfanew of dosstub to start of PE header

    mov rax,mzhdr
    mov rcx,pehdr

    .if ( [rax].asym.max_offset >= 0x40 )

        mov rsi,[rax].dsym.seginfo
        mov rdx,[rsi].CodeBuffer
        mov rsi,[rcx].dsym.seginfo
        mov eax,[rsi].fileoffset
        mov [rdx].IMAGE_DOS_HEADER.e_lfanew,eax
    .endif

    ; set number of sections in PE file header (doesn't matter if it's 32- or 64-bit)

    mov rsi,[rcx].dsym.seginfo
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

    mov rsi,[rdi].dsym.seginfo
    mov section,[rsi].CodeBuffer

    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head, ebx = -1 : rdi : rdi = [rdi].dsym.next )

        mov rsi,[rdi].dsym.seginfo

        .continue .if ( [rsi].segtype == SEGTYPE_HDR )
        .continue .if ( [rdi].asym.max_offset == 0 ) ;; ignore empty sections

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

        mov rdx,[rdi].dsym.next
        .if rdx
            mov rdx,[rdx].dsym.seginfo
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


    .if ( ModuleInfo.start_label )

        mov rax,ModuleInfo.start_label
        mov rdx,[rax].asym.segm
        mov rsi,[rdx].dsym.seginfo
        mov ecx,[rsi].start_offset
        add ecx,[rax].asym.offs

ifndef ASMC64
        .if ( ModuleInfo.defOfssize == USE64 )
endif
            mov rax,ph64
            mov [rax].IMAGE_PE_HEADER64.OptionalHeader.AddressOfEntryPoint,ecx
ifndef ASMC64
        .else
            mov rax,ph32
            mov [rax].IMAGE_PE_HEADER32.OptionalHeader.AddressOfEntryPoint,ecx
        .endif
endif
    .else
        asmerr( 8009 )
    .endif

ifndef ASMC64
    .if ( ModuleInfo.defOfssize == USE64 )
endif
        mov rcx,ph64
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
        mov rcx,ph32
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

    .if ( SymSearch( edataname ) )

        mov rsi,[rax].dsym.seginfo
        mov rdx,datadir
        mov [rcx][IMAGE_DIRECTORY_ENTRY_EXPORT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[rax].asym.max_offset
        mov [rcx][IMAGE_DIRECTORY_ENTRY_EXPORT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[rsi].start_offset
    .endif

    ; set import directory and IAT data dir value

    .if ( SymSearch( ".idata$" IMPDIRSUF ) )

       .new idata_null:ptr dsym
       .new idata_iat:ptr dsym
       .new size:uint_32

        mov rdi,rax
        mov idata_null,SymSearch( ".idata$" IMPNDIRSUF ) ; final NULL import directory entry
        mov idata_iat, SymSearch( ".idata$" IMPIATSUF )  ; IAT entries

        mov rcx,idata_null
        mov rsi,[rcx].dsym.seginfo
        mov eax,[rsi].start_offset
        add eax,[rcx].asym.max_offset
        mov rsi,[rdi].dsym.seginfo
        sub eax,[rsi].start_offset
        mov rdx,datadir
        mov [rdx][IMAGE_DIRECTORY_ENTRY_IMPORT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,eax
        mov [rdx][IMAGE_DIRECTORY_ENTRY_IMPORT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[rsi].start_offset

        mov rcx,idata_iat
        mov rsi,[rcx].dsym.seginfo
        mov [rdx][IMAGE_DIRECTORY_ENTRY_IAT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[rsi].start_offset
        mov [rdx][IMAGE_DIRECTORY_ENTRY_IAT*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[rcx].asym.max_offset
    .endif

    ; set resource directory data dir value

    .if ( SymSearch( ".rsrc" ) )

        mov rsi,[rax].dsym.seginfo
        mov rdx,datadir
        mov [rdx][IMAGE_DIRECTORY_ENTRY_RESOURCE*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[rax].asym.max_offset
        mov [rdx][IMAGE_DIRECTORY_ENTRY_RESOURCE*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[rsi].start_offset
    .endif

    ; set relocation data dir value

    .if ( SymSearch( ".reloc" ) )

        mov rsi,[rax].dsym.seginfo
        mov rdx,datadir
        mov [rdx][IMAGE_DIRECTORY_ENTRY_BASERELOC*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[rax].asym.max_offset
        mov [rdx][IMAGE_DIRECTORY_ENTRY_BASERELOC*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[rsi].start_offset
    .endif

    ; fixme: TLS entry is not written because there exists a segment .tls, but
    ; because a _tls_used symbol is found ( type: IMAGE_THREAD_DIRECTORY )

    .if ( SymSearch(".tls") )

        mov rsi,[rax].dsym.seginfo
        mov rdx,datadir
        mov [rdx][IMAGE_DIRECTORY_ENTRY_TLS*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[rax].asym.max_offset
        mov [rdx][IMAGE_DIRECTORY_ENTRY_TLS*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[rsi].start_offset
    .endif

ifndef ASMC64
    .if ( ModuleInfo.defOfssize == USE64 )
endif
        .if ( SymSearch( ".pdata" ) )

            mov rsi,[rax].dsym.seginfo
            mov rdx,datadir
            mov [rdx][IMAGE_DIRECTORY_ENTRY_EXCEPTION*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.Size,[rax].asym.max_offset
            mov [rdx][IMAGE_DIRECTORY_ENTRY_EXCEPTION*IMAGE_DATA_DIRECTORY].IMAGE_DATA_DIRECTORY.VirtualAddress,[rsi].start_offset
        .endif
        mov rcx,cp
        GHF( OptionalHeader.ImageBase )
        .s8 [rcx].calc_param.imagebase64
ifndef ASMC64
    .else
        mov rcx,cp
        mov [rcx].calc_param.imagebase,GHF( OptionalHeader.ImageBase )
    .endif
endif
    ret

pe_set_values endp


; v2.11: this function is called when the END directive has been found.
; Previously the code was run inside EndDirective() directly.

pe_enddirhook proc fastcall modinfo:ptr module_info

    pe_create_MZ_header( rcx )
    pe_emit_export_data()

    mov rcx,modinfo
    .if ( [rcx].module_info.DllQueue )
        pe_emit_import_data()
    .endif

    pe_create_section_table()
   .return( NOT_ERROR )

pe_enddirhook endp


; write section contents
; this is done after the last step only!

bin_write_module proc __ccall uses rsi rdi rbx modinfo:ptr module_info

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
    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].dsym.next )

        mov rsi,[rdi].dsym.seginfo

        ; reset the offset fields of segments
        ; it was used to store the size in there

        mov [rsi].start_offset,0

        ; set STACK segment type

        .if ( [rsi].combine == COMB_STACK )
            mov [rsi].segtype,SEGTYPE_STACK
        .endif
    .endf

    ; calculate size of header

    mov rbx,modinfo
    assume rbx:ptr module_info

    .if ( [rbx].sub_format == SFORMAT_MZ )

        mov reloccnt,GetSegRelocs( NULL )
        shl eax,2
        movzx edx,[rbx].mz_ofs_fixups
        add eax,edx
        movzx edx,[rbx].mz_alignment
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
        ;tmemset( rax, 0, cp.sizehdr ) -- zero alloc...
    .endif
    mov cp.entryoffset,-1

    ; set starting offsets for all sections

    mov cp.rva,0
    .if ( [rbx].sub_format == SFORMAT_PE || [rbx].sub_format == SFORMAT_64BIT )

        .if ( ModuleInfo._model == MODEL_NONE )
            .return( asmerr( 2013 ) )
        .endif
        pe_set_values( &cp )

    .elseif ( [rbx].segorder == SEGORDER_DOSSEG )

        ; for .DOSSEG, regroup segments (CODE, UNDEF, DATA, BSS)

        .for ( ebx = 0 : ebx < SIZE_DOSSEG : ebx++ )
            .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].dsym.next )
                mov rsi,[rdi].dsym.seginfo
                lea rcx,dosseg_order
                .continue .if ( [rsi].segtype != [rcx+rbx*4] )
                CalcOffset( rdi, &cp )
            .endf
        .endf
        SortSegments( 0 )
        mov rbx,modinfo

    .else ; segment order .SEQ (default) and .ALPHA

        .if ( [rbx].segorder == SEGORDER_ALPHA )
            SortSegments( 1 )
        .endif

        .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].dsym.next )

            ; ignore absolute segments
            CalcOffset( rdi, &cp )
        .endf
    .endif

    ; handle relocs

    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head : rdi : rdi = [rdi].dsym.next )

        DoFixup( rdi, &cp )
        mov rsi,[rdi].dsym.seginfo
        .if ( stackp == NULL && [rsi].combine == COMB_STACK )
            mov stackp,rdi
        .endif
    .endf

    ; v2.04: return if any errors occured during fixup handling

    .if ( [rbx].error_count )
        .return( ERROR )
    .endif

    ; for plain binaries make sure the start label is at
    ; the beginning of the first segment

    .if ( [rbx].sub_format == SFORMAT_NONE )
        .if ( [rbx].start_label )
            mov rax,[rbx].start_label
            .if ( cp.entryoffset == -1 || cp.entryseg != [rax].asym.segm )
                .return( asmerr( 3003 ) )
            .endif
        .endif
    .endif

    mov sizetotal,GetImageSize( FALSE )

    ; for MZ|PE format, initialize the header

    .if ( [rbx].sub_format == SFORMAT_MZ )

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
        .if ( ax < [rbx].mz_heapmin )
            mov [rdi].e_minalloc,[rbx].mz_heapmin
        .endif
        mov [rdi].e_maxalloc,[rbx].mz_heapmax ;; heap max
        .if ( ax < [rdi].e_minalloc )
            mov [rdi].e_maxalloc,[rdi].e_minalloc
        .endif

        ; set stack if there's one defined

        .if ( stackp )
            mov rcx,stackp
            mov rsi,[rcx].dsym.seginfo
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

        .if ( [rbx].start_label )

            mov rcx,[rbx].start_label
            mov rdx,[rcx].asym.segm
            mov rsi,[rdx].dsym.seginfo

            .if ( [rsi].sgroup )

                mov rax,[rsi].sgroup
                mov eax,[rax].asym.offs
                mov edx,eax
                shr edx,4
                and eax,0x0F
                add eax,[rsi].start_offset
                add eax,[rcx].asym.offs
                mov [rdi].e_ip,ax
                mov [rdi].e_cs,dx

            .else

                mov eax,[rsi].start_offset
                mov edx,eax
                shr edx,4
                and eax,0x0F
                add eax,[rcx].asym.offs
                mov [rdi].e_ip,ax
                mov [rdi].e_cs,dx
            .endif
        .else
            asmerr( 8009 )
        .endif

        mov [rdi].e_lfarlc,[rbx].mz_ofs_fixups
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

    .for ( rdi = SymTables[TAB_SEG*symbol_queue].head, first = TRUE : rdi : rdi = [rdi].dsym.next )

        mov rsi,[rdi].dsym.seginfo
        .continue .if ( [rsi].segtype == SEGTYPE_ABS )

        .if ( ( ModuleInfo.sub_format == SFORMAT_PE || ModuleInfo.sub_format == SFORMAT_64BIT ) &&
              ( [rsi].segtype == SEGTYPE_BSS || [rsi].info ) )
            xor eax,eax
        .else
            mov eax,[rdi].asym.max_offset
            sub eax,[rsi].start_loc
        .endif
        mov size,eax
        .if first == 0
            mov eax,[rdi].asym.max_offset
        .endif
        mov sizemem,eax

        ; if no bytes have been written to the segment, check if there's
        ; any further segments with bytes set. If no, skip write!

        .if ( [rsi].bytes_written == 0 )
            .for ( rdx = [rdi].dsym.next: rdx: rdx = [rdx].dsym.next )
                mov rcx,[rdx].dsym.seginfo
                .break .if ( [rcx].seg_info.bytes_written )
            .endf
            .if ( !rdx )
                mov size,edx
            .endif
        .endif

        mov ecx,[rsi].start_offset
        .if first
            add ecx,[rsi].start_loc
        .endif
        LstPrintf( szSegLine, [rdi].asym.name, [rsi].fileoffset, ecx, size, sizemem )
        LstNL()

        .if ( size && [rsi].CodeBuffer )
ifdef _LIN64
            .new _rdi:ptr = rdi
            .new _rsi:ptr = rsi
endif
            fseek( CurrFile[OBJ*string_t], [rsi].fileoffset, SEEK_SET )
ifdef _LIN64
            mov rdi,_rsi
            fwrite( [rdi].seg_info.CodeBuffer, 1, size, CurrFile[OBJ*string_t] )
            mov rsi,_rsi
            mov rdi,_rdi
else
            fwrite( [rsi].seg_info.CodeBuffer, 1, size, CurrFile[OBJ*string_t] )
endif
            .if ( eax != size )
                WriteError()
            .endif
        .endif
        mov first,FALSE
    .endf

    .if ( [rbx].sub_format == SFORMAT_PE || ModuleInfo.sub_format == SFORMAT_64BIT )

        mov size,ftell( CurrFile[OBJ*string_t] )
        mov eax,cp.rawpagesize
        dec eax
        .if ( size & eax )
            lea ecx,[rax+1]
            and eax,size
            sub ecx,eax
            mov size,ecx
            tmemset( alloca(ecx), 0, size )
            fwrite( rax, 1, size, CurrFile[OBJ*string_t] )
        .endif
    .endif
    LstPrintf( szSep )
    LstNL()

    .if ( [rbx].sub_format == SFORMAT_MZ )

        mov eax,sizetotal
        sub eax,cp.sizehdr
        add sizeheap,eax
    .elseif ( [rbx].sub_format == SFORMAT_PE || ModuleInfo.sub_format == SFORMAT_64BIT )
        mov sizeheap,cp.rva
    .else
        mov sizeheap,GetImageSize( TRUE )
    .endif

    LstPrintf( szTotal, " ", sizetotal, sizeheap )
    LstNL()
   .return( NOT_ERROR )

bin_write_module endp


bin_check_external proc fastcall modinfo:ptr module_info

    .for ( rdx = SymTables[TAB_EXT*symbol_queue].head : rdx : rdx = [rdx].dsym.next )
        .if ( !( [rdx].asym.sflags & S_WEAK ) || [rdx].asym.flags & S_USED )
            .if ( !( [rdx].asym.flag2 & S_ISINLINE ) )
                .return( asmerr( 2014, [rdx].asym.name ) )
            .endif
        .endif
    .endf
    .return( NOT_ERROR )

bin_check_external endp


bin_init proc fastcall public uses rsi rdi rbx modinfo:ptr module_info

    mov rbx,rcx
    mov [rbx].WriteModule,&bin_write_module
    mov [rbx].Pass1Checks,&bin_check_external
    mov al,[rbx].sub_format
    .switch al
ifndef ASMC64
    .case SFORMAT_MZ
        lea rdi,[rbx].mz_ofs_fixups
        lea rsi,mzdata
        mov ecx,sizeof( MZDATA )
        rep movsb
       .endc
endif
    .case SFORMAT_PE
    .case SFORMAT_64BIT
        mov [rbx].EndDirHook,&pe_enddirhook ;; v2.11
       .endc
    .endsw
    ret

bin_init endp

    end
