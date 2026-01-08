; DBGDW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; support for DWARF debugging info
; added for elf32/64 formats in v2.21
;

include asmc.inc
include memalloc.inc
include parser.inc
include fixup.inc
include segment.inc
include extern.inc
include elfspec.inc

if DWARF_SUPP

include linnum.inc
include dbgdw.inc

define DWLINE_OPCODE_BASE 13 ; max is 13
define DW_MIN_INSTR_LENGTH 1
define DWLINE_BASE (-1)
define DWLINE_RANGE 4

define NUM_DWSEGS 3

.enumt dwarf_sections : asym_t {
    DWINFO_IDX,
    DWABBREV_IDX,
    DWLINE_IDX
    }


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

.data

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

.data?
 dwarf_seg asym_t NUM_DWSEGS dup(?)

.code

    option proc:private

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

    lea rcx,dwarf_seg
    CreateFixup( [rcx+DWABBREV_IDX], FIX_OFF32, OPTJ_NONE )
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

    .for ( rcx = SymTables[TAB_SEG].head : rcx : rcx = [rcx].asym.next )

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
            lea rcx,dwarf_seg
            CreateFixup( [rcx+DWLINE_IDX], FIX_OFF32, OPTJ_NONE )
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
            lea rcx,dwarf_seg
            CreateFixup( [rcx+DWLINE_IDX], FIX_OFF32, OPTJ_NONE )
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

    .while 1

        mov eax,edx
        and eax,0x7F
        sar edx,7
        .break .if ( ZERO? && !( eax & 0x40 ) )
        .break .if ( edx == -1 && ( eax & 0x40 ) )
        or  al,0x80
        mov [rcx],al
        inc rcx
    .endw
    mov [rcx],al
    lea rax,[rcx+1]
    ret
    endp


dwarf_line_gen proc __ccall uses rsi rdi rbx line_incr:int_t, addr_incr:int_t, buf:ptr byte

   .new opcode:dword
   .new pend:ptr byte
   .new address:int_t

    ldr ecx,line_incr
    ldr ebx,addr_incr
    ldr rdi,buf
    xor esi,esi

    .ifs ( ecx < DWLINE_BASE || ecx > DWLINE_BASE + DWLINE_RANGE - 1 )

        ; line_incr is out of bounds... emit standard opcode

        mov byte ptr [rdi],DW_LNS_advance_line
        LEB128( &[rdi+1], ecx )
        sub rax,rdi
        mov esi,eax
        xor ecx,ecx
    .endif
    mov line_incr,ecx

    .ifs ( ebx < 0 )

        lea rcx,[rdi+rsi+1]
        mov eax,DW_LNS_advance_pc
        mov [rcx-1],al
        LEB128( rcx, ebx )
        sub rax,rdi
        mov esi,eax
        xor ebx,ebx
    .else
        mov eax,ebx
        xor edx,edx
        mov ecx,DW_MIN_INSTR_LENGTH
        div ecx
        mov ebx,eax
    .endif
    .if ( ebx == 0 && line_incr == 0 )

        mov eax,esi
        mov ecx,DW_LNS_copy
        mov [rdi+rax],cl
        inc eax
       .return
    .endif

    ; calculate the opcode with overflow checks

    sub line_incr,DWLINE_BASE
    imul eax,ebx,DWLINE_RANGE
    mov opcode,eax
    .ifs ( eax < ebx )
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

define MAX_ADDR_INCR ( ( 255 - DWLINE_OPCODE_BASE ) / DWLINE_RANGE )

    .ifs ( ebx < 2*MAX_ADDR_INCR )

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
        mov eax,ebx
        xor edx,edx
        mov ecx,MAX_ADDR_INCR - 1
        div ecx
        sub ebx,edx
        imul eax,edx,DWLINE_RANGE
        add eax,line_incr
        add eax,DWLINE_OPCODE_BASE
        mov opcode,eax
    .endif
    LEB128( &[rdi+rsi+1], ebx )
    mov ecx,opcode
    mov [rax],cl
    sub rax,rdi
    inc eax
    ret
    endp


dwarf_set_line proc __ccall uses rsi rdi rbx em:ptr elfmod, seg_linenum:asym_t

   .new curr:asym_t
   .new lni:ptr line_num_info

    ldr rbx,em
    ldr rsi,seg_linenum

    ; get linnum program size; currently we count the items and assume avg size is 2

    .for ( edx = 0, rcx = SymTables[TAB_SEG].head : rcx : rcx = [rcx].asym.next )

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

    .for ( rcx = SymTables[TAB_SEG].head : rcx : rcx = [rcx].asym.next )

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

dwarf_create_sections proc __ccall public uses rsi rdi rbx em:ptr elfmod

    ldr rbx,em
    .for ( rsi = &dwarf_segnames, edi = 0 : edi < NUM_DWSEGS : edi++ )
        CreateIntSegment( [rsi+rdi*string_t], "DWARF", 0, MODULE.Ofssize, FALSE )
        lea rcx,dwarf_seg
        mov [rcx+rdi*asym_t],rax
    .endf
    lea rsi,dwarf_seg
    dwarf_set_info( rbx, [rsi+DWINFO_IDX] )
    dwarf_set_abbrev( rbx, [rsi+DWABBREV_IDX] )
    dwarf_set_line( rbx, [rsi+DWLINE_IDX] )
    ret
    endp

endif

    end
