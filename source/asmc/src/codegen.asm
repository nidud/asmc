; CODEGEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; instruction encoding, scans opcode table and emits code.
;

include asmc.inc
include fixup.inc
include parser.inc
include codegen.inc
include segment.inc
include reswords.inc
include operands.inc
include listing.inc
include input.inc
include proc.inc

AddFloatingPointEmulationFixup proto __ccall :ptr code_info

public  szNull

externdef opnd_clstab:opnd_class
externdef vex_flags:byte

;; segment order must match the one in special.inc

PREFIX_ES       equ 0x26
PREFIX_CS       equ 0x2E
PREFIX_SS       equ 0x36
PREFIX_DS       equ 0x3E
PREFIX_FS       equ 0x64
PREFIX_GS       equ 0x65

    .data
    szNull      char_t "<NULL>",0
    sr_prefix   char_t PREFIX_ES, PREFIX_CS, PREFIX_SS, PREFIX_DS, PREFIX_FS, PREFIX_GS

    .code

    assume proc:private, rsi:ptr code_info, rdi:instr_t

; - determine what code should be output and their order.
; - output prefix bytes:
;    - LOCK, REPxx,
;    - FWAIT (not a prefix, but handled like one)
;    - address size prefix 0x67
;    - operand size prefix 0x66
;    - segment override prefix, branch hints
; - output opcode (1-3), "mod r/m" and "s-i-b" bytes.
;
; Note that jwasm follows Masm strictly here, even if it
; contradicts Intel docs. For example, Masm always emits
; the F2/F3/66 byte before a segment prefix, even if the
; F2/F3/66 byte is a "mantadory prefix".

output_opc proc __ccall uses rdi rbx

   .new m_opid:dword
   .new m_type:dword
   .new v_type:dword
   .new m_size:byte
   .new v_size:byte
   .new w_size:byte
   .new brccnt:byte
   .new fpfix:byte = FALSE
   .new rmbyte:byte
   .new do_swap:byte ; short version for VMOV*

    mov rdi,[rsi].pinstr

    ;; Output debug info - line numbers

    .if ( Options.line_numbers )

        mov ebx,GetLineNumber()
        AddLinnumDataRef(get_curr_srcfile(), ebx)
    .endif

    ;; v2.02: if it's a FPU or MMX/SSE instr, reset opsiz!
    ;; [this code has been moved here from codegen()]

    mov bl,GetCpu([rdi].cpu)
    mov bh,GetCpuExtensions([rdi].cpu)

    .if ( [rdi].cpu.Fpu || bh == P_MMX || bh >= P_SSE1 )

        ;; there are 2 exceptions. how to avoid this ugly hack?

        mov eax,[rsi].token
        .if ( eax != T_CRC32 && eax != T_POPCNT )
            mov [rsi].Prefix.Osize,0
        .endif
    .endif

    ;; Check if CPU, FPU and extensions are within the limits

    mov cl,GetCurrCpu()
    mov ch,GetCpuExtensions(CurrCpu)

    .if ( bl > cl || ( [rdi].cpu.Fpu && !CurrCpu.Fpu ) || bh > ch )

        ;; if instruction is valid for 16bit cpu, but operands aren't,
        ;; then display a more specific error message!

        GetInstrTable([rsi].token)
        GetCpu([rax].Instruction.cpu)
        mov ecx,2085
        .if ( bl == P_386 && al <= P_386 )
            mov ecx,2087
        .endif
        asmerr( ecx )
    .endif

    ;; Output FP fixup if required
    ;; the OPs with NOWAIT are the instructions beginning with
    ;; FN, except FNOP.
    ;; the OPs with WAIT are the instructions:
    ;; FCLEX, FDISI, FENI, FINIT, FSAVEx, FSTCW, FSTENVx, FSTSW

    mov eax,[rdi].prefix
    .if ( MODULE.emulator == TRUE &&
          [rsi].Ofssize == USE16 && [rdi].cpu.Fpu && eax != AP_NO_FWAIT )

        mov fpfix,TRUE

        ;; v2.04: no error is returned

        AddFloatingPointEmulationFixup(rsi)
    .elseif ( eax == AP_REX_W )
        mov [rsi].Rex.W,1 ; XSAVE64/..
    .endif

    ; Output instruction prefix

    .if ( [rsi].HLE )
        OutputByte( [rsi].HLE ) ; Hardware Lock Elision Prefix Hints
    .endif

    ; Output instruction prefix LOCK, REP, or REP[N]E|Z

    .if ( [rsi].inst != EMPTY )

        mov rdx,GetInstrTable([rsi].inst)
        mov eax,[rdx].Instruction.prefix
        mov ecx,[rdi].prefix

        ; instruction prefix must be ok. However, with -Zm, the plain REP
        ; is also ok for instructions which expect REPxx.

        .if ( MODULE.m510 == TRUE && eax == AP_REP && ecx == AP_REPxx )
            mov eax,ecx
        .endif
        mov rmbyte,al
        .if ( ecx != eax )
            .if !( [rsi].HLE == 0xF3 && [rsi].token == T_MOV )
                asmerr( 2068 )
            .endif
        .else
            OutputByte( [rdx].instr_item.opcode )
        .endif
    .endif

    ;; Output FP FWAIT if required

    .if ( [rdi].cpu.Fpu )

        mov ecx,[rdi].prefix
        .if ( [rsi].token == T_FWAIT )

            ;; v2.04: Masm will always insert a NOP if emulation is active,
            ;; no matter what the current cpu is. The reason is simple: the
            ;; nop is needed because of the fixup which was inserted.

            .if fpfix
                OutputByte(OP_NOP)
            .endif

        .elseif ( fpfix || ecx == AP_FWAIT )

            OutputByte(OP_WAIT)

        .elseif ( ecx != AP_NO_FWAIT )

            ;; implicit FWAIT synchronization for 8087 (CPU 8086/80186)

            .ifd ( GetCurrCpu() < P_286 )
               OutputByte(OP_WAIT)
            .endif
        .endif
    .endif

    ;; check if address/operand size prefix is to be set

    mov al,[rdi].byte1_info
    .switch al
    .case F_16
        .if [rsi].Ofssize >= USE32
            mov [rsi].Prefix.Osize,1
        .endif
        .endc
    .case F_32
        .if [rsi].Ofssize == USE16
            mov [rsi].Prefix.Osize,1
        .endif
        .endc
    .case F_16A ;; 16-bit JCXZ and LOOPcc

        ;; doesnt exist for IA32+

        .if [rsi].Ofssize == USE32
            mov [rsi].Prefix.Asize,1
        .endif
        .endc
    .case F_32A ;; 32-bit JECXZ and LOOPcc

        ;; in IA32+, the 32bit version gets an 0x67 prefix

        .if [rsi].Ofssize != USE32
            mov [rsi].Prefix.Asize,1
        .endif
        .endc
    .case F_0FNO66
        mov [rsi].Prefix.Osize,0
       .endc
    .case F_48
    .case F_480F
        mov [rsi].Rex.W,1
       .endc
    .endsw

    .if !( [rsi].ResW & RWF_VEX or RWF_EVEX )
        .switch al ; [rdi].byte1_info
        .case F_660F
        .case F_660F38
        .case F_660F3A
            mov [rsi].Prefix.Osize,1
           .endc
        .case F_F20F
        .case F_F20F38
            OutputByte(0xF2)
           .endc
        .case F_F30F
            .if ( [rsi].token == T_UMONITOR )
                .if ( MODULE.Ofssize == USE64 )
                    mov [rsi].Rex,0
                    .if ( [rsi].opnd.type & OP_R32 )
                        mov [rsi].Prefix.Asize,1
                    .elseif ( [rsi].opnd.type & OP_R16 )
                        asmerr( 2024 )
                    .endif
                .elseif ( [rsi].Prefix.Osize )
                    mov [rsi].Prefix.Osize,0
                    mov [rsi].Prefix.Asize,1
                .endif
            .endif
        .case F_F3      ; PAUSE instruction
        .case F_F30F38
        .case F_F30F3A  ; HRESET instruction
            OutputByte(0xF3)
        .endsw
    .endif

    ;; Output address and operand size prefixes.
    ;; These bytes are NOT compatible with FP emulation fixups,
    ;; which expect that the FWAIT/NOP first "prefix" byte is followed
    ;; by either a segment prefix or the opcode byte.
    ;; Neither Masm nor JWasm emit a warning, though.

    .if ( [rsi].Prefix.Asize && ![rsi].Flags.B_RIP && ![rdi].Evex.vsib )
        OutputByte(ADRSIZ)
    .endif
    .if ( [rsi].Prefix.Osize )
        .ifd ( GetCurrCpu() < P_386 )
            asmerr(2087)
        .endif
        OutputByte(OPSIZ)
    .endif

    ;; Output segment prefix

    .if ( [rsi].RegOverride != EMPTY )

        mov eax,[rsi].RegOverride
        lea rcx,sr_prefix
        OutputByte( [rcx+rax] )
    .endif

    .if ( [rdi].opnd_dir )

        ;; The reg and r/m fields are backwards

        mov al,[rsi].rm_byte
        mov rmbyte,al
        mov ah,al
        mov dl,al
        and ah,0xc0
        shr dl,3
        and dl,7
        shl al,3
        and al,0x38
        or  al,dl
        or  al,ah
        mov [rsi].rm_byte,al

        mov al,[rsi].Rex2
        mov cl,al
        mov dl,al
        and cl,0x20
        and dl,0x40
        and al,0x10
        shr dl,2
        shl al,2
        or  al,dl
        or  al,cl
        mov [rsi].Rex2,al

        mov al,[rsi].Rex
        mov cl,al
        mov dl,al
        and cl,0xFA
        and dl,REX_R
        shr dl,2
        and al,REX_B
        shl al,2
        or  al,dl
        or  al,cl
        mov [rsi].Rex,al
    .endif

    .if ( [rsi].ResW & RWF_VEX or RWF_EVEX )

        mov do_swap,0
        .if ( [rsi].Prefix.Swap )
            mov al,[rsi].rm_byte
            and al,0xC0
            .if ( al == 0xC0 && [rdi].opnd_dir && ![rdi+instr_item].opnd_dir )
                add rdi,instr_item
                mov [rsi].pinstr,rdi
                mov [rsi].rm_byte,rmbyte
                inc do_swap
            .else
                asmerr( 2008, "{swap} not supported" )
            .endif
        .endif

        .if ( [rsi].Prefix.Evex )
            OutputByte(0x62)
        .elseif ( [rsi].ResW.SWAP && !do_swap )
            mov al,[rsi].Rex
            mov ah,[rsi].rm_byte
            and eax,0xC00B
            .if ( eax == 0xC001 )
                add rdi,instr_item
                mov [rsi].pinstr,rdi
                mov [rsi].rm_byte,rmbyte
                inc do_swap
            .endif
        .endif

        movzx ebx,[rsi].Vex
        and bl,0x80
        shl ebx,8
        mov al,[rdi].byte1_info
        .switch al
        .case F_0F
        .case F_660F
        .case F_F20F
        .case F_F30F
        .case F_F2660F
        .case F_L10FW1
        .case F_L166W1
        .case F_L00FW1
        .case F_L066W1
            or bl,0x01
           .endc
        .case F_0F38
            or bl,0x80
        .case F_660F38
        .case F_F20F38
        .case F_F30F38
            or bl,0x02
           .endc
        .case F_0F3A
        .case F_660F3A
        .case F_F20F3A
        .case F_F30F3A
            or bl,0x03
           .endc
        .case F_66MAP5 ; map 5 -- AVX512-FP16 instructions
        .case F_F2MAP5
        .case F_F3MAP5
        .case F_NPMAP5
            or bl,0x05
           .endc
        .case F_66MAP6 ; map 6 -- AVX512-FP16 instructions
        .case F_F2MAP6
        .case F_F3MAP6
        .case F_NPMAP6
            or bl,0x06
        .endsw

        .switch al
        .case F_660F
        .case F_660F38
        .case F_660F3A
        .case F_66MAP6
        .case F_66MAP5
        .case F_L066W1
            or bh,0x01
           .endc
        .case F_F30F
        .case F_F30F38
        .case F_F30F3A
        .case F_F3MAP5
        .case F_F3MAP6
            or bh,0x02
           .endc
        .case F_F20F
        .case F_F20F38
        .case F_F20F3A
        .case F_F2MAP6
        .case F_F2MAP5
            or bh,0x03
           .endc
        .case F_L10FW0
        .case F_L10FW1
            or bh,0x04
           .endc
        .case F_L166W0
        .case F_L166W1
            or bh,0x05
        .endsw

        .if ( [rsi].vexregop )

            mov dl,[rsi].vexregop
            mov al,16
            sub al,dl
            shl al,3
            mov dl,al
            and dl,0x80
            shr dl,5
            or  al,dl
            shl dl,3    ; REX2.R4
            or  bh,al
            or  [rsi].Rex2,dl

        .elseif ( [rsi].rrm_ib )

            ;
            ; inst r, r/m, imm
            ;
            ; - source moved to rrm_ib
            ; - REX.B/B4=0
            ;

            or  bh,0x78     ; VEX.vvvv = 1111
            mov al,[rsi].rrm_ib
            dec al
            mov cl,al
            mov dl,al
            and al,0x07     ; r/m
            and cl,0x08     ; REX
            and dl,0x10     ; REX2
            mov ah,[rsi].rm_byte
            and ah,0xC7
            .switch ah
            .case 0x04      ; mod = 00, r/m = 100, s-i-b is present
            .case 0x44      ; mod = 01, r/m = 100, s-i-b is present
            .case 0x84      ; mod = 10, r/m = 100, s-i-b is present
                or  [rsi].rm_byte,0x04
                or  al,cl
                shl al,3
                xor bh,al   ; VEX.vvvv = op1 reg
                xor cl,cl   ; REX.
                shl dl,1
               .endc
            .default
                or  al,cl
                shl al,3
                xor bh,al   ; VEX.vvvv = op1 reg
                xor cl,cl   ; REX.
                shl dl,1
            .endsw
            or [rsi].Rex,cl
            or [rsi].Rex2,dl
        .else
            or  bh,0x68     ; VEX.vvvv = 1101
            .if ( [rdi].Evex.vsib == 0 )
                or bh,0x10  ; VEX.vvvv = 1111
            .endif
        .endif

        ;; emit 2 (0xC4) or 3 (0xC5) byte VEX prefix

        mov al,[rsi].Rex

        .if ( do_swap )

            .if ( [rsi].Prefix.Evex == 0 )
                mov bl,0xC5
            .else
                mov al,[rsi].Rex
                not al
                and al,7
                shl al,5
                or  bl,al
            .endif
            and bh,0x7F

        .elseif ( [rdi].byte1_info >= F_0F38 || al & 0x0B )

            .if ( [rsi].Prefix.Evex == 0 )
                OutputByte( 0xC4 )
            .endif
            mov al,[rsi].Rex
            mov ah,al
            not al
            and al,7
            shl al,5    ; P0.RXB
            and ah,0x08 ; P1.W
            shl ah,4
            or  bx,ax
        .else
            mov al,[rsi].Rex
            not al
            and al,7
            shl al,5
            or  bl,al   ; P0.RXB
            .if ( ![rsi].Rex.R )
                or bh,0x80
            .endif
            .if ( [rsi].Prefix.Evex == 0 )
                mov bl,0xC5
            .endif
        .endif

        .if ( [rsi].Prefix.Evex )

            or  bh,0x04
            and bh,0x7F
            .if ( [rsi].Rex2.R4 == 0 )
                or bl,0x10 ; EVEX.R4 High-16 register
            .endif

            ; avxins() set W in ResW.EVEX_W

            mov al,4
            .if ( [rsi].ResW.EVEX_W || [rdi].Evex.W )
                or  bh,0x80
                add al,al
            .endif
            mov w_size,al

            .if ( [rsi].Rex2.X4 == 0 )
                mov [rsi].Evex.P2.V,1 ; EVEX.V High-16 NDS register
            .endif


            mov al,[rsi].rm_byte
            and al,MOD_11
            .if ( al == MOD_11 )

                .if ( [rsi].Rex2.B4 )
                    and bl,not 0x40 ; EVEX.X = High-16 register
                .endif

                ; EVEX.L Vector length

                .if ( [rsi].Modifier.Rounding == 0 )
                    mov eax,[rsi].opnd[OPND1].type
                    .if ( eax & OP_K || [rsi].opnd[OPNI2].type & OP_V )
                        or eax,[rsi].opnd[OPNI2].type
                    .endif
                    .if ( [rsi].VReg.R_ZMM )
                        or eax,OP_ZMM
                    .elseif ( [rsi].VReg.R_YMM )
                        or eax,OP_YMM
                    .endif
                    .switch
                    .case eax & OP_ZMM ;or OP_K
                        mov [rsi].Evex.P2.L1,1
                       .endc
                    .case eax & OP_YMM
                        mov [rsi].Evex.P2.L0,1
                       .endc
                    .endsw
                .endif

            .else

                .if ( [rsi].Rex2.B4 )

                    ; - Prefix.Rex2 is set if EGPR used
                    ; - EVEX.P0.B4 is not inverted

                    or bl,0x08 ; EVEX.P0.B4
                .endif

                ; figure out the vector size
                ;
                ; vcvtpd2dq(XMM, XMM_M128_M64)
                ; - xmm0,[rax]{1to2}      : 128
                ; - xmm0,[rax]{1to4}      : 256
                ; - ymm0,[rax]{1to4}      : 512
                ; - xmm0,qword bcst [rax] : 128
                ; - ymm0,qword bcst [rax] : 512
                ;

                xor eax,eax
                xor edx,edx
                xor ecx,ecx
                .if ( [rsi].opnd[OPNI2].type & OP_M_ANY )
                    mov edx,OPNI2
                    mov ecx,4
                .endif
                mov m_opid,edx

                movzx eax,[rdi].opclsidx
                imul eax,eax,opnd_class
                lea rdx,opnd_clstab
                add rdx,rax
                mov eax,[rdx].opnd_class.opnd_type[rcx]
                .if ( [rsi].Vex.HALF && ecx )
                    or eax,[rdx].opnd_class.opnd_type[0]
                .endif
                mov edx,m_opid
                or  eax,[rsi].opnd[rdx].type
                .if ( [rsi].Vex.L )
                    .if ( edx )
                        or eax,[rsi].opnd.type
                    .else
                        or eax,[rsi].opnd[OPNI2].type
                    .endif
                .endif
                .if ( [rsi].VReg.R_ZMM )
                    or eax,OP_ZMM
                .elseif ( [rsi].VReg.R_YMM )
                    or eax,OP_YMM
                .endif
                mov m_type,eax

                xor eax,eax
                .if ( [rsi].Modifier.Broadcast )
                    mov cl,[rsi].Modifier.BCShift
                    .if ( cl )
                        mov al,2
                        shl al,cl ; {1to<al>}
                    .endif
                .endif
                mov brccnt,al

                xor eax,eax ; get memory size
                mov cl,[rsi].mem_type
                .if ( cl == MT_ZWORD )
                    mov al,64
                .elseif !( cl & MT_SPECIAL )
                    and cl,MT_SIZE_MASK
                    inc cl
                    mov al,cl
                .endif
                mov m_size,al
                .if ( al == 64 )
                    or m_type,OP_M512
                .elseif ( al == 32 )
                    or m_type,OP_M256
                .endif

                mov al,16
                .if ( m_type & OP_ZMM or OP_M512 )
                    mov al,64
                .elseif ( m_type & OP_YMM or OP_M256 )
                    mov al,32
                .endif
                mov v_size,al

                .if ( !m_size )
                    .if ( ![rsi].Modifier.Broadcast )
                        mov m_size,al
                    .else
                        mov m_size,w_size
                        .if ( brccnt )
                            ;mov al,w_size
                            mul brccnt
                            mov v_size,al
                            .if ( al > 64 || al < 16 )
                                asmerr( 2008, "mismatch in the number of broadcasting elements" )
                            .endif
                        .endif
                    .endif
                .elseif ( brccnt ) ; ...
                    mov al,m_size
                    mul brccnt
                    mov v_size,al
                    .if ( al > 64 || al < 16 )
                        asmerr( 2008, "mismatch in the number of broadcasting elements" )
                    .endif
                .endif

                xor eax,eax
                mov ecx,[rdi].Evex.Tuple
                .switch ecx
                .case FV512
                    .if ( [rsi].Evex.P2.b && v_size == 32 && !brccnt )
                        mov v_size,64
                    .endif
                .case FV
                    .if ( [rsi].Evex.P2.b )
                        movzx eax,w_size
                        .if ( m_size == 2 )
                            mov eax,2
                        .endif
                        .endc
                    .endif
                .case FVM
                    movzx eax,v_size
                   .endc
                .case HV
                    .if ( [rsi].Evex.P2.b )
                        mov eax,4
                        .if ( m_size == 2 )
                            mov eax,2
                        .endif
                    .else
                        movzx eax,v_size
                        shr eax,1
                    .endif
                    .endc
                .case T1S   ; Tuple1 Scalar
                    mov cl,m_size
                    ;
                    ; issue: m_size = vector size
                    ;
                    mov edx,[rsi].token
                    .switch edx
                    .case T_VPEXPANDB
                    .case T_VPCOMPRESSB
                        mov cl,1
                       .endc
                    .case T_VPEXPANDW
                    .case T_VPCOMPRESSW
                        mov cl,2
                    .endsw

                    mov al,w_size
                    .if ( cl == 1 || cl == 2 )
                        mov al,cl
                    .endif
                    .endc
                .case T1F       ; Tuple1 Fixed 4/8 not affected by EVEX.W
                    movzx eax,w_size
                    movzx ecx,m_size
                    .if ( ecx == 4 || ecx == 8 )
                        mov eax,ecx
                    .endif
                    .endc
                .case T2        ;  8  8  8 Broadcast (2 elements)
                    mov eax,8   ;  - 16 16
                    .if ( w_size == 8 )
                        add eax,eax
                    .endif
                    .endc
                .case T4        ;  - 16 16 Broadcast (4 elements)
                    mov eax,16  ;  - -  32
                    .if ( w_size == 8 )
                        add eax,eax
                    .endif
                    .endc
                .case T8        ;  - -  32 Broadcast (8 elements)
                    movzx eax,m_size ; ?
                   .endc
                .case OVM       ;  2  4  8 Octal Mem
                    movzx eax,v_size
                    shr eax,3
                   .endc
                .case QVM       ;  4  8 16 Quarter Mem
                    movzx eax,v_size
                    shr eax,2
                    .if ( m_size == 2 )
                        mov eax,2
                    .endif
                   .endc
                .case HVM       ;  8 16 32 Half Mem
                    movzx eax,v_size
                    shr eax,1
                   .endc
                .case T14X      ; Tuple1_4X
                .case M128      ; 16 16 16 Mem 128
                    mov eax,16
                   .endc
                .case DDUP      ;  8 32 64 VMOVDDUP
                    movzx eax,v_size
                    .if ( eax == 16 )
                        mov eax,8
                    .endif
                    .endc
                .default
                    xor eax,eax
                .endsw
                .if ( [rsi].Modifier.Rounding == 0 )
                    .if ( v_size == 64 || [rsi].VReg.X_ZMM )
                        mov [rsi].Evex.P2.L1,1
                    .elseif ( v_size == 32 || [rsi].VReg.X_YMM )
                        mov [rsi].Evex.P2.L0,1
                    .endif
                .endif
                mov edx,m_opid

                ; the displacement in disp8 will be scaled in MOD_01

                .if ( eax && [rsi].opnd[rdx].data32l )

                    or  [rsi].rm_byte,MOD_10 ; [reg+disp32]
                    and [rsi].rm_byte,not MOD_01
                    mov ecx,[rsi].opnd[rdx].data32l
                    dec eax
                    and ecx,eax
                    .ifz
                        lea ecx,[rax+1]
                        mov eax,[rsi].opnd[rdx].data32l
                        cdq
                        idiv ecx
                        mov edx,m_opid
                        .ifs ( eax >= SCHAR_MIN && eax <= SCHAR_MAX )
                            mov [rsi].opnd[rdx].data32l,eax
                            and [rsi].rm_byte,not MOD_10
                            or  [rsi].rm_byte,MOD_01 ; [reg+disp8]
                        .endif
                    .endif
                .endif

                .if ( [rdi].Evex.vsib )

                    mov cl,[rsi].opc_or
                    or  ebx,0x7840
                    mov [rsi].Evex.P2.V,1
                    mov al,cl
                    and al,0x08
                    and cl,0x10
                    shl al,3
                    shr cl,1
                    xor bl,al
                    xor [rsi].Evex.P2,cl
                    mov [rsi].opc_or,0
                .endif
            .endif
            OutputByte(ebx)
            shr ebx,8

            ; WIgnored is also used as a "dummy" flag..

            .if ( [rdi].Evex.WIgnored && ![rsi].ResW.EVEX_W )
                and bl,not 0x80 ; ?
            .endif
            OutputByte(ebx)

            mov bl,[rsi].Evex.P2
            .if ( [rdi].Evex.LIgnored && [rsi].Modifier.Rounding == 0 )
                and bl,not 0x60 ; ?
            .elseif ( [rsi].Modifier.Suppress && bl & 0x40 )
                and bl,not 0x40 ; ?
            .endif
            OutputByte(ebx)

            .if ( [rsi].Evex.P2.Mask && [rdi].Evex.Mask == 0 )
                asmerr( 2152 )
            .endif
            .if ( [rsi].Evex.P2.z && [rdi].Evex.Zeroing == 0 )
                asmerr( 2152 )
            .endif

            .if ( [rsi].Modifier.Broadcast && [rdi].Evex.Broadcast == 0 )
                asmerr( 2152 )
            .endif
            .if ( [rsi].Modifier.Suppress )
                .if ( ( ![rdi].Evex.SuppressZ && ![rdi].Evex.Suppress ) ||
                      ( [rdi].Evex.SuppressZ && ![rsi].Modifier.ZMMUsed ) )
                    asmerr( 2024 )
                .endif
            .endif
            .if ( [rsi].Modifier.Rounding )
                .if ( ( ![rdi].Evex.RoundingZ && ![rdi].Evex.Rounding ) ||
                      ( [rdi].Evex.RoundingZ && ![rsi].Modifier.ZMMUsed ) )
                    asmerr( 2024 )
                .endif
            .endif

        .else

            mov eax,[rsi].opnd[OPND1].type
            .if ( eax & OP_YMM || ( [rsi].opnd[OPNI2].type & OP_YMM or OP_M256 ) ||
                ( eax == OP_NONE && [rsi].Vex.L ) ) ; no operands? use VX_L flag from vex_flags[]
                or bh,0x04
            .endif
            .if ( [rsi].Evex.P2.b )
                asmerr( 2152 )
            .endif
            OutputByte(ebx)
            shr ebx,8

            .if ( [rdi].Evex.vgpr || [rdi].Evex.vsib )

                mov ecx,[rsi].token
                .if ( [rdi].Evex.vsib )
                    mov ecx,T_BEXTR
                .endif

                ; VEX-Encoded GPR Instructions

                .switch ecx
                .case T_BLSI
                .case T_BLSR
                .case T_BLSMSK
                    mov al,rmbyte
                    not al
                    shl al,3
                    and al,0x38
                    and bl,0xC7
                    or  bl,al
                    .if ( [rsi].Rex.R )
                        and bl,0xBF
                    .endif
                    .if ( ecx == T_BLSMSK )
                        and [rsi].rm_byte,0xF7
                    .else
                        and [rsi].rm_byte,0xCF
                    .endif
                    .endc
                .case T_BEXTR
                .case T_SARX
                .case T_SHLX
                .case T_SHRX
                .case T_BZHI
                    mov al,[rsi].opc_or
                    shl al,3
                    not al
                    and al,0x38
                    and bl,0xC7
                    or  bl,al
                    mov al,[rsi].opc_or
                    shr al,4
                    or  bl,al
                    mov [rsi].opc_or,0
                .endsw
            .endif
            OutputByte(ebx)
        .endif

    .else

        ; REX2 must be the last prefix

        .if ( [rsi].Prefix.Rex2 )

            OutputByte(0xD5)
            mov cl,[rsi].Rex
            and cl,0xF
            or  cl,[rsi].Rex2
            mov [rsi].Rex,0
            OutputByte(ecx)
        .endif

        ;; the REX prefix must be located after the other prefixes

        .if ( [rsi].Rex )

            mov eax,[rsi].token
            .switch eax
            .case T_RDPID
            .case T_SENDUIPI
                .endc
            .case T_INVEPT
            .case T_INVVPID
                and [rsi].Rex,REX_R
               .endc .ifz
            .default
                .if ( [rsi].Ofssize != USE64 )
                    asmerr(2024)
                .endif
                mov cl,[rsi].Rex
                or  cl,0x40
                OutputByte(ecx)
            .endsw
        .endif

        ;; Output extended opcode
        ;; special case for some 286 and 386 instructions
        ;; or 3DNow!, MMX and SSEx instructions

        .if ( [rdi].byte1_info >= F_0F )

            OutputByte(EXTENDED_OPCODE)
            mov al,[rdi].byte1_info
            .switch al
            .case F_0F0F: OutputByte(EXTENDED_OPCODE) : .endc
            .case F_0F38
            .case F_F20F38
            .case F_F30F38
            .case F_660F38: OutputByte(0x38) : .endc
            .case F_0F3A
            .case F_F30F3A
            .case F_660F3A: OutputByte(0x3A) : .endc
            .endsw
        .endif
    .endif

    xor ecx,ecx
    .if ( [rsi].Flags.IsWide )
        inc ecx
    .endif

    mov eax,[rdi].rm_info
    .switch eax
    .case R_in_OP
        mov al,[rsi].rm_byte
        and al,NOT_BIT_67
        or  al,[rdi].opcode
        OutputByte(eax)
       .endc
    .case no_RM
        mov al,[rdi].opcode
        or  al,cl
        OutputByte(eax)
       .endc
    .case no_WDS
        xor ecx,ecx
        ;; no break
    .default

        ;; opcode (with w d s bits), rm-byte
        ;; don't emit opcode for 3DNow! instructions

        .if ( [rdi].byte1_info != F_0F0F )

            mov al,[rdi].opcode
            or  al,cl
            or  al,[rsi].opc_or
            OutputByte(eax)
        .endif

        ;; emit ModRM byte; bits 7-6 = Mod, bits 5-3 = Reg, bits 2-0 = R/M

        mov bl,[rdi].rm_byte
        or  bl,[rsi].rm_byte
        .if ( [rsi].Flags.B_RIP ) ;; @RIP

            and bl,not MOD_10
        .endif

        mov eax,[rsi].token
        .switch eax
        .case T_RDPID
            mov bl,NOT_BIT_012
            or bl,[rsi].rm_byte
            .endc
        .case T_ADOX
            OutputByte(0xF6)
            .endc
        .endsw
        OutputByte(ebx)

        ;; no SIB for 16bit

        .return .if ( ( [rsi].Ofssize == USE16 && ![rsi].Prefix.Asize ) ||
                      ( [rsi].Ofssize == USE32 && [rsi].Prefix.Asize ) )

        and bl,NOT_BIT_345
        .switch bl
        .case 0x04 ;; mod = 00, r/m = 100, s-i-b is present
        .case 0x44 ;; mod = 01, r/m = 100, s-i-b is present
        .case 0x84 ;; mod = 10, r/m = 100, s-i-b is present

            ;; emit SIB byte; bits 7-6 = Scale, bits 5-3 = Index, bits 2-0 = Base

            OutputByte([rsi].sib)
        .endsw
    .endsw
    ret
    endp

output_data proc __ccall uses rdi rbx determinant:int_t, index:int_t

; output address displacement and immediate data;

    xor ebx,ebx
    mov rdi,[rsi].pinstr
    mov eax,[rsi].token
    .switch eax
    .case T_ANDN
    .case T_MULX
    .case T_PDEP
    .case T_PEXT
        .return .if ( ![rsi].opnd[OPNI2].data32l || index == OPND3 )
        .endc
    .case T_BEXTR
    .case T_SARX
    .case T_SHLX
    .case T_SHRX
    .case T_BZHI
        .return .if ( ![rsi].opnd[OPNI2].data32l || !index || index == OPND3 )
        .endc
    .case T_XLAT
    .case T_XLATB
        .return
    .endsw

    ;;
    ;; skip the memory operand for XLAT/XLATB and string instructions!
    ;;
    mov eax,[rdi].prefix
    .return .if ( eax == AP_REP || eax == AP_REPxx )

    ;; determine size

    mov eax,determinant
    .switch
    .case eax & OP_I8
        mov ebx,1
        .endc
    .case eax & OP_I16
        mov ebx,2
        .endc
    .case eax & OP_I32
        mov ebx,4
        .endc
    .case eax & OP_I48
        mov ebx,6
        .endc
    .case eax & OP_I64
        mov ebx,8
        .endc
    .case eax & OP_M_ANY
        ;;
        ;; switch on the mode ( the leftmost 2 bits )
        ;;
        mov al,[rsi].rm_byte
        and eax,BIT_67

        .switch eax
        .case MOD_01 ;; 8-bit displacement
            mov ebx,1
            .endc
        .case MOD_00 ;; direct; base and/or index with no disp
            .if ( ( [rsi].Ofssize == USE16 && ![rsi].Prefix.Asize ) ||
                  ( [rsi].Ofssize == USE32 && [rsi].Prefix.Asize ) )

                mov al,[rsi].rm_byte
                and al,BIT_012
                .if ( al == RM_D16 )
                     mov ebx,2 ;; = size of displacement
                .endif
            .else
                ;;
                ;; v2.11: special case, 64-bit direct memory addressing, opcodes 0xA0 - 0xA3
                ;;
                mov al,[rdi].opcode
                and al,0xFC
                .if ( [rsi].Ofssize == USE64 && al == 0xA0 && [rdi].byte1_info == 0 )
                    mov ebx,8
                .else
                    mov al,[rsi].rm_byte
                    and eax,BIT_012
                    .switch eax
                    .case RM_SIB ;; 0x04 (equals register # for ESP)
                        mov al,[rsi].sib
                        and al,BIT_012
                        .endc .if( al != RM_D32 ) ;; size = 0
                        ;;
                        ;; no break
                        ;;
                    .case RM_D32  ;; 0x05 (equals register # for EBP)
                        mov ebx,4 ;; = size of displacement
                        ;;
                        ;; v2.11: overflow check for 64-bit added
                        ;;
                        imul ecx,index,opnd_item
                        mov eax,[rsi].opnd[rcx].data32l
                        mov edx,[rsi].opnd[rcx].data32h
                        xor ecx,ecx
                        .if edx || eax >= 0x80000000
                            inc ecx
                            .if !( edx < 0xffffffff || ( edx == 0xffffffff && eax < 0x80000000 ) )
                                xor ecx,ecx
                            .endif
                        .endif
                        .if ( [rsi].Ofssize == USE64 && ecx )
                            asmerr( 2070 )
                        .endif
                    .endsw
                .endif
            .endif
            .endc
        .case MOD_10  ;; 16- or 32-bit displacement
            mov ebx,4
            .if ( ( [rsi].Ofssize == USE16 && ![rsi].Prefix.Asize ) ||
                  ( [rsi].Ofssize == USE32 && [rsi].Prefix.Asize ) )

                mov ebx,2
            .endif
            .endc
        .endsw
    .endsw

    mov edi,ebx
    imul ebx,index,opnd_item

    .if ( edi )
        .if ( [rsi].opnd[rbx].InsFixup )

            ; v2.07: fixup type check moved here

            .if ( Parse_Pass > PASS_1 )

                mov eax,1
                mov rdx,[rsi].opnd[rbx].InsFixup
                mov cl,[rdx].fixup.type
                shl eax,cl
                mov rcx,MODULE.fmtopt
                movzx ecx,[rcx].format_options.invalid_fixup_type

                .if ( eax & ecx )

                    mov rcx,MODULE.fmtopt
                    lea rax,[rcx].format_options.formatname
                    lea rcx,szNull
                    .if [rdx].fixup.sym
                        mov rcx,[rdx].fixup.sym
                        mov rcx,[rcx].asym.name
                    .endif
                    asmerr( 3001, rax, rcx )

                    ; don't exit!
                .endif
            .endif

            .if ( write_to_file )

                GetCurrOffset()
                mov rdx,[rsi].opnd[rbx].InsFixup
                mov [rdx].fixup.locofs,eax
                OutputBytes( &[rsi].opnd[rbx].data32l, edi, rdx )
               .return
            .endif
        .endif
        OutputBytes( &[rsi].opnd[rbx].data32l, edi, NULL )
    .endif
    ret
    endp


check_3rd_operand proc __ccall uses rdi rbx

    mov   rdi,[rsi].pinstr
    movzx eax,[rdi].opclsidx
    imul  ebx,eax,opnd_class
    lea   rcx,opnd_clstab
    movzx eax,[rcx+rbx].opnd_class.opnd_type_3rd

    .if ( eax == OP3_NONE || eax == OP3_HID )
        .return( ERROR ) .if ( [rsi].opnd[OPNI3].type != OP_NONE )
        .return( NOT_ERROR )
    .endif

    ;; current variant needs a 3rd operand

    .switch eax

    .case OP3_CL
        .return( NOT_ERROR ) .if ( [rsi].opnd[OPNI3].type == OP_CL )
        .endc

    .case OP3_I8_U ;; IMUL, SHxD, a few MMX/SSE

        ;; for IMUL, the operand is signed!

        .if ( ( [rsi].opnd[OPNI3].type & OP_I ) && [rsi].opnd[OPNI3].data32l >= -128 )
            .if ( ( [rsi].token == T_IMUL && [rsi].opnd[OPNI3].data32l < 128 ) ||
                ( [rsi].token != T_IMUL && [rsi].opnd[OPNI3].data32l < 256 ) )
                mov [rsi].opnd[OPNI3].type,OP_I8
                .return( NOT_ERROR )
            .endif
        .endif
        .endc

    .case OP3_I ;; IMUL
        .endc .if !( [rsi].opnd[OPNI3].type & OP_I )
        .return( NOT_ERROR )

    .case OP3_XMM0

        ;; for VEX encoding, XMM0 has the meaning: any XMM/YMM register

        .if ( [rsi].token >= VEX_START )

            .return( NOT_ERROR ) .if ( [rsi].opnd[OPNI3].type & ( OP_V or OP_K ) )

            mov eax,[rsi].token
            .switch eax
            .case T_ANDN
            .case T_MULX
            .case T_PDEP
            .case T_PEXT
            .case T_BEXTR
            .case T_SARX
            .case T_SHLX
            .case T_SHRX
            .case T_BZHI
            .case T_RORX
                .return( NOT_ERROR )
            .endsw
        .elseif ( [rsi].opnd[OPNI3].type == OP_XMM && [rsi].opnd[OPNI3].data32l == 0 )
            .return( NOT_ERROR )
        .endif
        .endc
    .endsw
    .return( ERROR )
    endp


output_3rd_operand proc __ccall uses rdi rbx

    mov   rdi,[rsi].pinstr
    movzx eax,[rdi].opclsidx
    imul  ebx,eax,opnd_class
    lea   rcx,opnd_clstab
    add   rbx,rcx

    movzx eax,[rbx].opnd_class.opnd_type_3rd
    .switch pascal eax
    .case OP3_I8_U
        output_data( OP_I8, OPND3 )
    .case OP3_I
        output_data( [rsi].opnd[OPNI3].type, OPND3 )
    .case OP3_HID
        mov eax,[rsi].token
        xor edx,edx
        .switch eax
        .case T_PCLMULLQLQDQ
        .case T_VPCLMULLQLQDQ
           .endc
        .case T_PCLMULHQLQDQ
        .case T_VPCLMULHQLQDQ
            inc edx
           .endc
        .case T_PCLMULLQHQDQ
        .case T_VPCLMULLQHQDQ
            mov edx,16
           .endc
        .case T_PCLMULHQHQDQ
        .case T_VPCLMULHQHQDQ
            mov edx,17
           .endc
        .default
            .if ( eax < T_VCMPEQPS )
                sub eax,T_CMPEQPD
                mov ecx,8
                div ecx
            .elseif ( eax < T_VPCMPEQB )
                sub eax,T_VCMPEQPS
                mov ecx,32
                div ecx
            .else
                sub eax,T_VPCMPEQB
                mov ecx,6
                div ecx
                .if ( edx >= 3 )
                    inc edx ; 0, 1, 2, [] 4, 5, 6
                .endif
            .endif
        .endsw
        mov [rsi].opnd[OPNI3].data32l,edx
        mov [rsi].opnd[OPNI3].InsFixup,NULL
        output_data( OP_I8, OPND3 )
    .case OP3_XMM0
        .if ( [rsi].token >= VEX_START )
            mov eax,[rsi].opnd[OPNI3].data32l
            shl eax,4
            mov [rsi].opnd[OPNI3].data32l,eax
            output_data( OP_I8, OPND3 )
        .endif
    .endsw
    ret
    endp


match_phase_3 proc __ccall uses rdi rbx opnd1:int_t

;; - this routine will look up the assembler opcode table and try to match
;;   the second operand with what we get;
;; - if second operand match then it will output code; if not, pass back to
;;   codegen() and continue to scan InstrTable;
;; - possible return codes: NOT_ERROR (=done), ERROR (=nothing found)

  local determinant:int_t

    mov rdi,[rsi].pinstr
    movzx eax,[rdi].opclsidx
    imul ebx,eax,opnd_class
    lea rcx,opnd_clstab

    ;; remember first op type

    mov determinant,[rbx+rcx].opnd_class.opnd_type[OPND1]
    mov ebx,[rsi].opnd[OPNI2].type

    .if ( [rsi].token >= VEX_START && [rsi].Vex.L )

        mov eax,[rsi].opnd[OPND1].type
        .if ( eax & ( OP_YMM or OP_M256 or OP_K or OP_ZMM or OP_M512 ) )

            .if ( ebx & OP_ZMM )
                or ebx,OP_YMM
            .elseif ( ebx & OP_M512 )
                or ebx,OP_M256
            .endif
            .if ( ebx & OP_YMM )
                or ebx,OP_XMM
            .elseif ( ebx & OP_M256 )
                or ebx,OP_M128
            .elseif ( ebx & OP_M128 )
                or ebx,OP_M64
            .elseif ( ebx & OP_XMM && ![rsi].Vex.HALF && eax != OP_K )
                .return( asmerr( 2085 ) )
            .endif

            ;; may be necessary to cover the cases where the first operand is a memory operand
            ;; "without size" and the second operand is a ymm register

        .elseif ( eax == OP_M )
            .if ( ebx & OP_YMM or OP_ZMM )
                or ebx,OP_XMM
            .endif
        .endif
    .elseif ( opnd1 == OP_XMM && ebx == OP_M64 )

        ;; v2.27: case xmm,m64 (real4 or 8)

        mov rax,CurrProc
        .if ( rax )
            .if ( [rax].asym.langtype == LANG_VECTORCALL )
                or ebx,OP_M128
            .endif
        .elseif ( MODULE.langtype == LANG_VECTORCALL )
            or ebx,OP_M128
        .endif
    .endif

    .repeat

        mov   rdi,[rsi].pinstr
        movzx eax,[rdi].opclsidx
        imul  eax,eax,opnd_class
        lea   rcx,opnd_clstab
        mov   eax,[rcx+rax].opnd_class.opnd_type[4] ; OPND2

        .if ( [rsi].Vex.L && eax == OP_XMM && ( ebx == OP_ZMM || ebx == OP_YMM ) )

            ; inst m[32|64],[z|y]mm -- VPSCATTER

            or eax,ebx
        .endif

        .if ( [rsi].Prefix.Evex && [rdi].Evex.Broadcast && ( eax & OP_MGT8 || ebx & OP_MGT8 ) )

            ; Vector, QWORD BCST mem

            or eax,ebx
        .endif

        .switch eax

        .case OP_I ;; arith, MOV, IMUL, TEST

            .if ebx & eax

                ;; This branch exits with either ERROR or NOT_ERROR.
                ;; So it can modify the CodeInfo fields without harm.

                .if opnd1 & OP_R8

                    ;; 8-bit register, so output 8-bit data

                    mov [rsi].Prefix.Osize,0
                    mov ebx,OP_I8
                    mov rax,[rsi].opnd[OPNI2].InsFixup
                    .if rax != NULL

                        ;; v1.96: make sure FIX_HIBYTE isn't overwritten!

                        .if [rax].fixup.type != FIX_HIBYTE

                            mov [rax].fixup.type,FIX_OFF8
                        .endif
                    .endif

                .elseif opnd1 & OP_R16

                    ;; 16-bit register, so output 16-bit data

                    mov ebx,OP_I16

                .elseif opnd1 & ( OP_R32 or OP_R64 )

                    ;; 32- or 64-bit register, so output 32-bit data

                    mov [rsi].Prefix.Osize,1
                    .if [rsi].Ofssize
                        mov [rsi].Prefix.Osize,0
                    .endif
                    mov ebx,OP_I32

                .elseif opnd1 & OP_M

                    ;; there is no reason this should be only for T_MOV

                    .switch OperandSize(opnd1, rsi)
                    .case 1
                        mov ebx,OP_I8
                        mov [rsi].Prefix.Osize,0
                       .endc
                    .case 2
                        mov ebx,OP_I16
                        mov [rsi].Prefix.Osize,0
                        .if [rsi].Ofssize
                            mov [rsi].Prefix.Osize,1
                        .endif
                        .endc

                        ;; mov [mem], imm64 doesn't exist. It's ensured that
                        ;; immediate data is 32bit only

                    .case 8
                    .case 4
                        mov ebx,OP_I32
                        mov [rsi].Prefix.Osize,1
                        .if [rsi].Ofssize
                            mov [rsi].Prefix.Osize,0
                        .endif
                        .endc
                    .default
                        asmerr(2070)
                    .endsw
                .endif
                output_opc()
                output_data(opnd1, OPND1)
                output_data(ebx, OPND2)
               .return(NOT_ERROR)
            .endif
            .endc

        .case OP_I8_U ;; shift+rotate, ENTER, BTx, IN, PSxx[D|Q|W]

            .if ( ebx & eax )

                .endc .if ( [rsi].Flags.ConstFixed ) && ebx != OP_I8

                ;; v2.03: lower bound wasn't checked
                ;; range of unsigned 8-bit is -128 - +255

                .if ( [rsi].opnd[OPNI2].data32l <= UCHAR_MAX && [rsi].opnd[OPNI2].data32l >= SCHAR_MIN )

                    ;; v2.06: if there's an external, adjust the fixup if it is > 8-bit

                    mov rax,[rsi].opnd[OPNI2].InsFixup
                    .if ( rax != NULL )
                        .if ( [rax].fixup.type == FIX_OFF16 || [rax].fixup.type == FIX_OFF32 )

                            mov [rax].fixup.type,FIX_OFF8
                        .endif
                    .endif

                    ;; the SSE4A EXTRQ instruction will need this!

                    output_opc()
                    output_data(opnd1, OPND1)
                    output_data(OP_I8, OPND2)
                   .return NOT_ERROR
                .endif
            .endif
            .endc

        .case OP_I8 ;; arith, IMUL

            mov edx,eax
            mov eax,[rsi].token
            .endc .if MODULE.NoSignExtend && ( eax == T_AND || eax == T_OR || eax == T_XOR )

            mov rax,[rsi].opnd[OPNI2].InsFixup
            .if rax
                mov rcx,[rax].fixup.sym
               .endc .if ( rcx && [rcx].asym.state != SYM_UNDEFINED ) ;; external? then skip
            .endif

            .if !( [rsi].Flags.ConstFixed )

                movsx eax,byte ptr [rsi].opnd[OPNI2].data32l
                movsx ecx,word ptr [rsi].opnd[OPNI2].data32l
                .if ( opnd1 & ( OP_R16 or OP_M16 ) ) && eax == ecx
                    or edx,OP_I16
                .elseif ( opnd1 & ( OP_RGT16 or OP_MGT16 ) ) && eax == [rsi].opnd[OPNI2].data32l
                    or edx,OP_I32
                .endif
            .endif

            .if ( ebx & edx )

                output_opc()
                output_data(opnd1, OPND1)
                output_data(OP_I8, OPND2)
               .return NOT_ERROR
            .endif
            .endc

        .case OP_I_1 ;; shift ops

            .if ( ebx & eax )
               .if ( [rsi].opnd[OPNI2].data32l == 1 )

                   output_opc()
                   output_data(opnd1, OPND1)

                   ;; the immediate is "implicite"

                   .return NOT_ERROR
               .endif
            .endif
            .endc
        .case OP_RGT16
            .switch [rsi].token
            .case T_ANDN
            .case T_MULX
            .case T_PDEP
            .case T_PEXT
                .if !( ebx & ( OP_R32 or OP_R64 ) )
                    or ebx,OP_RGT16
                .endif
                .endc
            .case T_RORX
                output_opc()
                output_data(OP_I8_U, OPND3)
                .return NOT_ERROR
            .endsw
            ;; drop
        .default

            .if ( ebx & eax )

                .endc .ifd check_3rd_operand() == ERROR
                output_opc()
                .if opnd1 & (OP_I_ANY or OP_M_ANY )
                    output_data(opnd1, OPND1)
                .endif
                .if ( ebx & ( OP_I_ANY or OP_M_ANY ) )
                    output_data(ebx, OPND2)
                .endif

                movzx eax,[rdi].opclsidx
                imul eax,eax,opnd_class
                lea rcx,opnd_clstab
                .if ( [rcx+rax].opnd_class.opnd_type_3rd != OP3_NONE && ![rdi].Evex.vsib )
                    output_3rd_operand()
                .endif
                .if [rdi].byte1_info == F_0F0F ;; output 3dNow opcode?
                    movzx eax,[rdi].opcode
                    .if [rsi].Flags.IsWide
                        or eax,1
                    .endif
                    OutputByte(eax)
                .endif
                .return NOT_ERROR
            .endif
            .endc
        .endsw

        add rdi,instr_item
        .while ( [rsi].Prefix.Evex && [rdi].Evex == 0 && ![rdi].first )
            add rdi,instr_item
        .endw
        mov   [rsi].pinstr,rdi
        movzx eax,[rdi].opclsidx
        imul  eax,eax,opnd_class
        lea   rcx,opnd_clstab
        mov   eax,[rcx+rax].opnd_class.opnd_type[OPND1]

    .until !( eax == determinant && ![rdi].first )

    sub [rsi].pinstr,instr_item ;; pointer will be increased in codegen()
   .return( ERROR )
    endp


    assume rdi:fixup_t

add_bytes proc __ccall uses rdi index:int_t

    imul eax,index,opnd_item
    mov rdi,[rsi].opnd[rax].InsFixup

    .if ( rdi && [rdi].type == FIX_RELOFF32 )

        GetCurrOffset()
        sub eax,[rdi].locofs

        ;; v2.25 - added ->offset to ->addbytes
        ;; v2.28 - removed
        ;; if ( CodeInfo->opnd[index].InsFixup->sym && CodeInfo->opnd[index].InsFixup->sym->isarray )
        ;;      bytes += CodeInfo->opnd[index].InsFixup->offset;
        ;;

        mov [rdi].addbytes,al
    .endif
    ret
    endp


    assume rdi:instr_t

check_operand_2 proc __ccall uses rdi rbx opnd1:int_t
;
; check if a second operand has been entered.
; If yes, call match_phase_3();
; else emit opcode and optional data.
; possible return codes: ERROR (=nothing found), NOT_ERROR (=done)
;
    .if ( [rsi].opnd[OPNI2].type == OP_NONE )

        mov     rdi,[rsi].pinstr
        movzx   eax,[rdi].opclsidx
        imul    ecx,eax,opnd_class
        lea     rdx,opnd_clstab

        .return ERROR .if [rdx+rcx].opnd_class.opnd_type[4] != OP_NONE


        ;; 1 opnd instruction found

        ;; v2.06: added check for unspecified size of mem op

        .if ( opnd1 == OP_M )

            add   rdi,instr_item
            movzx eax,[rdi].opclsidx
            imul  eax,eax,opnd_class

            .if ( ( [rdx+rax].opnd_class.opnd_type[OPND1] & OP_M ) && ![rdi].first )

                ;; skip error if mem op is a forward reference

                xor ecx,ecx
                xor edx,edx
                mov rax,[rsi].opnd[OPND1].InsFixup
                .if rax
                    mov rdx,[rax].fixup.sym
                    .if rdx
                        mov cl,[rdx].asym.state
                    .endif
                .endif
                .if ( !( [rsi].Flags.SymUndef ) && ( !eax || !rdx || ecx != SYM_UNDEFINED ) )
                    asmerr(2023)
                .endif
            .endif
        .endif
        output_opc()
        output_data( opnd1, OPND1 )
        .if ( [rsi].Ofssize == USE64 )
            add_bytes(OPND1)
        .endif
        .return NOT_ERROR
    .endif

    ;; check second operand

    .ifd match_phase_3(opnd1) == NOT_ERROR
        ;;
        ;; for rip-relative fixups, the instruction end is needed
        ;;
        .if ( [rsi].Ofssize == USE64 )

            add_bytes(OPND1)
            add_bytes(OPND2)
        .endif
        .return NOT_ERROR
    .endif
    .return( ERROR )
    endp


;; - codegen() will look up the assembler opcode table and try to find
;;   a matching first operand;
;; - if one is found then it will call check_operand_2() to determine
;;   if further operands also match; else, it must be error.

codegen proc __ccall public uses rsi rdi rbx CodeInfo:ptr code_info, oldofs:uint_t

    ldr rsi,CodeInfo

    mov rdi,[rsi].pinstr

    ;; privileged instructions ok?

    .if ( [rdi].cpu.Pm && !CurrCpu.Pm )
        .return( asmerr( 2085 ) )
    .endif

    ; if no [E]VEX[2|3] or {evex} prefix set test avxencoding flags

    .if !( [rsi].Prefix & VEX_PREFIX )

        ; handle EVEX only instructions

        .if ( [rsi].ResW.EVEX )
            .if ( ![rsi].ResW.VEX || !( MODULE.avxencoding & PREFER_VEX or PREFER_VEX3 or NO_EVEX ) )
                mov [rsi].Prefix.Evex,1
            .endif
        .elseif ( [rsi].ResW.VEX && MODULE.avxencoding == PREFER_EVEX )
            mov [rsi].Prefix.Evex,1
        .endif
    .endif

    .if ( [rsi].Prefix.Evex )

        ; get the first EVEX-Encoded entry

        .while ( ![rdi].Evex && ![rdi+instr_item].first )
            add rdi,instr_item
            mov [rsi].pinstr,rdi
        .endw
    .endif

    mov ebx,[rsi].opnd[OPND1].type

    ;; if first operand is immediate data, set compatible flags

    .if ( ebx & OP_I )
        .if ( ebx == OP_I8 )
            mov ebx,OP_IGE8
        .elseif ( ebx == OP_I16 )
            mov ebx,OP_IGE16
        .endif
    .endif

    .if ( [rsi].ResW & 0x18 )

        ; set the VEX flags

        lea rdx,vex_flags
        mov ecx,[rsi].token
        mov al,[rcx+rdx-VEX_START]
        mov [rsi].Vex,al

        .if ( al & VX_L && ebx & ( OP_YMM or OP_M256 or OP_ZMM or OP_M512 ) )

            .if ( [rsi].opnd[OPNI2].type & OP_XMM && !( al & VX_HALF ) )
                .return( asmerr( 2070 ) )
            .endif
            .if ( ebx & OP_ZMM )
                or ebx,OP_YMM
            .elseif ( ebx & OP_M512 )
                or ebx,OP_M256
            .endif
            .if ( ebx & OP_YMM )
                or ebx,OP_XMM
            .else
                or ebx,OP_M128
            .endif
        .endif
    .endif

    ;; scan the instruction table for a matching first operand

    .repeat

        movzx eax,[rdi].opclsidx
        imul eax,eax,opnd_class
        lea rcx,opnd_clstab
        mov ecx,[rcx+rax].opnd_class.opnd_type[OPND1]

        ;; v2.06: simplified

        .if ( ecx == OP_NONE && ebx == OP_NONE )
            output_opc()
            .if ( MODULE.curr_file[TLST] )
                LstWrite(LSTTYPE_CODE, oldofs, NULL)
            .endif
            .return NOT_ERROR
        .endif

        .if ( ebx & ecx )

            ;; for immediate operands, the idata type has sometimes
            ;; to be modified in opnd_type[OPND1], to make output_data()
            ;; emit the correct number of bytes.

            mov eax,ERROR
            .switch ecx
            .case OP_I32 ;; CALL, JMP, PUSHD
            .case OP_I16 ;; CALL, JMP, RETx, ENTER, PUSHW
                check_operand_2( ecx )
               .endc
            .case OP_I8_U ;; INT xx; OUT xx, AL
                .if ( [rsi].opnd[OPND1].data32l <= UCHAR_MAX &&
                      [rsi].opnd[OPND1].data32l >= SCHAR_MIN )
                    check_operand_2( OP_I8 )
                .endif
                .endc
            .case OP_I_3 ;; INT 3
                .if ( [rsi].opnd[OPND1].data32l == 3 )
                    check_operand_2( OP_NONE )
                .endif
                .endc
            .default
                .endc .if ( [rsi].Prefix.Evex && [rdi].Evex == 0 )
                check_operand_2( [rsi].opnd[OPND1].type )
            .endsw
            .if ( eax == NOT_ERROR )
                .if ( MODULE.curr_file[TLST] )
                    LstWrite( LSTTYPE_CODE, oldofs, NULL )
                .endif
                .return NOT_ERROR
            .endif
        .endif
        add rdi,instr_item
        mov [rsi].pinstr,rdi
    .until ( [rdi].first )
    .return asmerr( 2070 )
    endp

    end
