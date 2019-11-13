
;; instruction encoding, scans opcode table and emits code.

include limits.inc
include asmc.inc
include fixup.inc
include parser.inc
include codegen.inc
include fpfixup.inc
include segment.inc
include reswords.inc
include token.inc
include operands.inc
include listing.inc
include input.inc
include proc.inc

public  szNull

extern  opnd_clstab:opnd_class
extern  ResWordTable:ReservedWord
extern  vex_flags:byte

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

    option procalign:4
    option proc:private
    assume esi:ptr code_info
    assume edi:instr_t

;; - determine what code should be output and their order.
;; - output prefix bytes:
;;    - LOCK, REPxx,
;;    - FWAIT (not a prefix, but handled like one)
;;    - address size prefix 0x67
;;    - operand size prefix 0x66
;;    - segment override prefix, branch hints
;; - output opcode (1-3), "mod r/m" and "s-i-b" bytes.
;;
;; Note that jwasm follows Masm strictly here, even if it
;; contradicts Intel docs. For example, Masm always emits
;; the F2/F3/66 byte before a segment prefix, even if the
;; F2/F3/66 byte is a "mantadory prefix".

output_opc proc uses edi ebx

  local vex     :byte
  local evex    :byte
  local fpfix   :byte
  local rflags  :byte
  local tuple   :byte
  local rmbyte  :byte

    mov     evex,0
    mov     fpfix,FALSE
    movzx   ecx,[esi].token
    mov     rflags,ResWordTable[ecx*8].flags
    and     al,RWF_MASK
    mov     tuple,al

    .if rflags & RWF_EVEX

        mov [esi].evex,1
    .endif

    ;; Output debug info - line numbers

    .if Options.line_numbers

        mov ebx,GetLineNumber()
        AddLinnumDataRef(get_curr_srcfile(), ebx)
    .endif

    ;; v2.02: if it's a FPU or MMX/SSE instr, reset opsiz!
    ;; [this code has been moved here from codegen()]

    mov edi,[esi].pinstr
    movzx ebx,[edi].cpu
    .if ebx & ( P_FPU_MASK or P_MMX or P_SSEALL )

        ;; there are 2 exceptions. how to avoid this ugly hack?

        movzx eax,[esi].token
        .if eax != T_CRC32 && eax != T_POPCNT
            mov [esi].opsiz,0
        .endif
    .endif

    ;; Check if CPU, FPU and extensions are within the limits

    mov edx,ModuleInfo.curr_cpu
    mov ecx,edx
    mov eax,ebx
    and ecx,P_CPU_MASK
    and eax,P_CPU_MASK
    .if eax <= ecx
        mov ecx,edx
        mov eax,ebx
        and ecx,P_FPU_MASK
        and eax,P_FPU_MASK
        .if eax <= ecx
            mov ecx,edx
            mov eax,ebx
            and ecx,P_EXT_MASK
            and eax,P_EXT_MASK
        .endif
    .endif

    .if eax > ecx

        ;; if instruction is valid for 16bit cpu, but operands aren't,
        ;; then display a more specific error message!

        movzx eax,[esi].token
        movzx eax,IndexFromToken(eax)
        mov ax,InstrTable[eax*8].cpu
        and eax,P_CPU_MASK
        mov ecx,2085
        .if ebx == P_386 && eax <= P_386
            mov ecx,2087
        .endif
        asmerr(ecx)
    .endif

    ;; Output FP fixup if required
    ;; the OPs with NOWAIT are the instructions beginning with
    ;; FN, except FNOP.
    ;; the OPs with WAIT are the instructions:
    ;; FCLEX, FDISI, FENI, FINIT, FSAVEx, FSTCW, FSTENVx, FSTSW

    mov al,[edi].flags
    and eax,II_ALLOWED_PREFIX
    .if ModuleInfo.emulator == TRUE && \
        [esi].Ofssize == USE16 && ( ebx & P_FPU_MASK ) && eax != AP_NO_FWAIT

        mov fpfix,TRUE

        ;; v2.04: no error is returned

        AddFloatingPointEmulationFixup(esi)
    .endif


    ;; Output EVEX instruction prefix

    .if [esi].evex

        mov evex,[edi].evex
        OutputByte(0x62)
    .endif


    ;; Output instruction prefix LOCK, REP or REP[N]E|Z

    .if [esi].inst != EMPTY

        mov     eax,[esi].inst
        movzx   edx,IndexFromToken(eax)
        mov     al,InstrTable[edx*8].flags
        and     eax,II_ALLOWED_PREFIX
        mov     cl,[edi].flags
        and     ecx,II_ALLOWED_PREFIX

        ;; instruction prefix must be ok. However, with -Zm, the plain REP
        ;; is also ok for instructions which expect REPxx.

        .if ModuleInfo.m510 == TRUE && eax == AP_REP && ecx == AP_REPxx
            mov eax,ecx
        .endif
        mov rmbyte,al
        .if ecx != eax
            asmerr(2068)
        .else
            OutputByte(InstrTable[edx*8].opcode)
        .endif
    .endif

    ;; Output FP FWAIT if required

    .if byte ptr [edi].cpu & P_FPU_MASK

        mov cl,[edi].flags
        and ecx,II_ALLOWED_PREFIX

        .if [esi].token == T_FWAIT

            ;; v2.04: Masm will always insert a NOP if emulation is active,
            ;; no matter what the current cpu is. The reason is simple: the
            ;; nop is needed because of the fixup which was inserted.

            .if fpfix
                OutputByte(OP_NOP)
            .endif

        .elseif fpfix || ecx == AP_FWAIT
            OutputByte(OP_WAIT)
        .elseif ecx != AP_NO_FWAIT

            ;; implicit FWAIT synchronization for 8087 (CPU 8086/80186)

            mov eax,ModuleInfo.curr_cpu
            and eax,P_CPU_MASK
            .if eax < P_286
               OutputByte(OP_WAIT)
            .endif
        .endif
    .endif

    ;; check if address/operand size prefix is to be set

    .switch [edi].byte1_info
    .case F_16
        .if [esi].Ofssize >= USE32
            mov [esi].opsiz,1
        .endif
        .endc
    .case F_32
        .if [esi].Ofssize == USE16
            mov [esi].opsiz,1
        .endif
        .endc
    .case F_16A ;; 16-bit JCXZ and LOOPcc

        ;; doesnt exist for IA32+

        .if [esi].Ofssize == USE32
            mov [esi].adrsiz,1
        .endif
        .endc
    .case F_32A ;; 32-bit JECXZ and LOOPcc

        ;; in IA32+, the 32bit version gets an 0x67 prefix

        .if [esi].Ofssize != USE32
            mov [esi].adrsiz,1
        .endif
        .endc
    .case F_0FNO66
        mov [esi].opsiz,0
        .endc
    .case F_48
    .case F_480F
        or [esi].rex,REX_W
        .endc
    .endsw

    .if !( rflags & RWF_VEX )
        .switch [edi].byte1_info
        .case F_660F
        .case F_660F38
        .case F_660F3A
            mov [esi].opsiz,1
            .endc
        .case F_F20F
        .case F_F20F38
            OutputByte(0xF2)
            .endc
        .case F_F3      ;; PAUSE instruction
        .case F_F30F
            OutputByte(0xF3)
        .endsw
    .endif

    ;; Output address and operand size prefixes.
    ;; These bytes are NOT compatible with FP emulation fixups,
    ;; which expect that the FWAIT/NOP first "prefix" byte is followed
    ;; by either a segment prefix or the opcode byte.
    ;; Neither Masm nor JWasm emit a warning, though.

    .if [esi].adrsiz && !( [esi].flags & CI_BASE_RIP ) && !( [edi].evex & VX_XMMI )
        OutputByte(ADRSIZ)
    .endif
    .if [esi].opsiz

        mov eax,ModuleInfo.curr_cpu
        and eax,P_CPU_MASK
        .if eax < P_386
            asmerr(2087)
        .endif
        OutputByte(OPSIZ)
    .endif

    ;; Output segment prefix

    .if [esi].RegOverride != EMPTY

        mov eax,[esi].RegOverride
        OutputByte(sr_prefix[eax])
    .endif

    .if [edi].flags & II_OPND_DIR

        mov al,[esi].rex
        mov ah,al
        mov dl,al
        and ah,0xFA
        and dl,REX_R
        shr dl,2
        and al,REX_B
        shl al,2
        or  al,dl
        or  al,ah
        mov [esi].rex,al

        ;; The reg and r/m fields are backwards

        mov al,[esi].rm_byte
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
        mov [esi].rm_byte,al
    .endif

    .if rflags & RWF_VEX

        movzx edx,[esi].token
        mov vex,vex_flags[edx-VEX_START]
        xor ebx,ebx         ; P1: R.X.B.R1.0.0.m1.m2
                            ; P2: W.v3.v2.v1.v0.1.p1.p0
        mov cl,[esi].evexP3 ; P3: z.L1.L0.b.V1.a2.a1.a0
        mov ch,[esi].vflags
        and al,VX_RW1
        .if evex == 0
            .if edx == T_VCVTSI2SD || edx == T_VMOVQ
                xor eax,eax
            .endif
        .endif
        mov bh,al ; P2 (vex & VX_RW1)

        mov al,[edi].byte1_info
        .switch al
        .case F_0F38
            mov bl,VX1_R
            .endc
        .case F_C5L
        .case F_C4M0L
            or bh,VX2_1
            .endc
        .case F_C5LP0
        .case F_C4M0P0L
            or bh,VX2_1
        .case F_C4M0P0
        .case F_660F
        .case F_660F38
        .case F_660F3A
            or bh,VX2_P0
            .endc
        .case F_F30F
        .case F_F30F38
            or bh,VX2_P1
            .endc
        .case F_F20F
        .case F_F20F38
            or bh,VX2_P0 or VX2_P1
            .endc
        .endsw

        .if ch & VX_OP1V
            or bh,VX2_1
        .endif
        .if cl & VX3_B || ( ( cl & VX3_A2 ) && !( ch & VX_ZMM ) && !( ch & VX_OP3 ) ) || \
            ( ( cl & VX3_A2 ) && ( ch == VX_OP3 ) )
            or cl,VX3_V
        .endif
        .if ( ( [esi].opnd[OPND1].type & ( OP_YMM or OP_ZMM ) ) || \
            ( [esi].opnd[OPNI2].type & ( OP_YMM or OP_ZMM or OP_M256 or OP_M512 ) ) || \
            ( [esi].opnd[OPND1].type == OP_NONE && vex & VX_L ) )

            ;; no operands? use VX_L flag from vex_flags[]

            or bh,VX2_1
            .if ch & VX_ZMM || [esi].opnd[OPNI2].type & OP_M512 || cl & VX3_B
                or  cl,VX3_L1 or VX3_V ;; ZMM
                mov al,evex
                and al,VX1_R1
                or  bl,al
            .else
                or cl,VX3_L0 ;; YMM
            .endif
        .endif

        .if [esi].vexregop

            mov dl,[esi].vexregop
            mov al,16
            and dl,0x3F
            sub al,dl
            shl al,3
            or  bh,al
            mov al,[esi].vexregop
            shr al,1
            and al,0x60
            or  cl,al

            .if cl & VX3_L1 ;; ZMM
                or cl,VX3_V
            .endif
            .if cl & VX3_B
                .if ch & VX_OP2V
                    and cl,not VX3_V
                .else
                    or cl,VX3_V
                .endif
            .endif

        .else

            or bh,VX2_V2 or VX2_V3
            .if !( [edi].evex & VX_XMMI )
                or bh,VX2_V1
            .endif

            or cl,VX3_V
            .if ( !( ( ch & VX_OP3 ) && ( evex & 0x04 ) && \
                ( [esi].opnd[OPNI2].type & ( OP_M128 or OP_M256 or OP_M512 ) ) ) )
                or bh,VX2_V0
            .endif
        .endif

        ;; emit 2 (0xC4) or 3 (0xC5) byte VEX prefix

        .if ( [edi].byte1_info >= F_0F38 || ( [esi].rex & ( REX_B or REX_X or REX_W ) ) )


            .if evex == 0
                push ecx
                OutputByte(0xC4)
                pop ecx
            .endif
            mov al,[edi].byte1_info
            .switch al
            .case F_F20F3A
                .if [esi].token == T_RORX
                    or ebx,0x0303
                .endif
                .endc
            .case F_0F38
            .case F_660F38
            .case F_F20F38
            .case F_F30F38
                or bl,VX1_M1
                .endc
            .case F_0F3A
            .case F_660F3A
                or bl,VX1_M1 or VX1_M2
                .endc
            .default
                .if [edi].byte1_info >= F_0F
                    or bl,VX1_M2
                .endif
            .endsw

            mov al,[esi].rex
            .if !( al & REX_B )
                or bl,VX1_B
            .endif
            .if !( al & REX_X )
                or bl,VX1_X
            .endif
            .if !( al & REX_R )
                or bl,VX1_R
            .endif
            .if al & REX_W
                or bh,VX2_W
            .endif

            mov ah,evex
            .if ah

                .if ch & VX_OP1V or VX_OP2V or VX_OP3V

                    ;; ?mm16..31

                    mov al,ch
                    and al,VX_OP1V or VX_OP2V or VX_OP3V or VX_OP3

                    .switch al
                    .case VX_OP3 or VX_OP2V or VX_OP3V  ;; 0, 1, 1
                        and cl,not VX3_V
                    .case VX_OP2V                       ;; 0, 1
                        mov al,bl
                        and al,0x6F
                        .if ax == 0x0862
                            or evex,0xE0
                            .endc
                        .endif
                        .if ah == 0x20
                            add edi,instr_item
                        .endif
                    .case VX_OP3 or VX_OP3V             ;; 0, 0, 1
                        .if !( ah & VX_W1 ) && ( tuple == RWF_T1S || tuple == RWF_QVM )
                            and bl,not VX1_R1
                        .else
                            and bl,not VX1_X
                            .if ( ch & VX_ZMM24 && ( [esi].opnd[OPND1].type == OP_ZMM ) ) || \
                                ( !( ch & VX_ZMM ) && !( [esi].sib & 0xC0 ) )
                                or bl,VX1_R1
                            .endif
                        .endif
                        .endc
                    .case VX_OP3 or VX_OP1V or VX_OP2V  ;; 1, 1, 0
                        .if !( ah & VX1_X ) && ( [esi].opnd[OPNI2].type & OP_I || [esi].opnd[OPNI3].type & OP_I )
                            and bl,not VX1_X
                            .if [esi].opnd[OPNI2].type & OP_I
                                or bl,VX1_R1
                                and cl,not VX3_V
                            .endif
                        .else
                            and cl,not VX3_V
                            and bl,not VX1_R1
                        .endif
                        .endc
                    .case VX_OP3 or VX_OP1V             ;; 1, 0, 0
                        .if ah == 0x10
                            or  bl,0x80
                            and bh,not 0x70
                            and cl,not 0x08
                            .endc
                        .endif
                    .case VX_OP1V                       ;; 1, 0
                        .if ah == 0x20 ;; VMOVQ
                            and bh,not 0x02
                            or  bh,0x01
                            add edi,instr_item
                            .if [edi].opcode != 0x6E
                                add edi,instr_item
                            .endif
                        .endif
                        and bl,not VX1_R1
                        .if !( ch & VX_ZMM ) && !( tuple == RWF_T1S && cl )
                            or cl,VX3_V
                        .endif
                        .endc
                    .case VX_OP3 or VX_OP1V or VX_OP2V or VX_OP3V ;; 1, 1, 1
                        and cl,not VX3_V
                    .case VX_OP3 or VX_OP1V or VX_OP3V   ;; 1, 0, 1
                    .case VX_OP1V or VX_OP2V             ;; 1, 1
                        and bl,not ( VX1_R1 or VX1_X )
                        .endc
                    .case VX_OP3 or VX_OP2V              ;; 0, 1, 0
                        mov al,ah
                        and al,0xFD
                        .if ( al != 0x80 && ( ( ch & VX_ZMM || [esi].sib & 0xC0 ) && \
                            !( !( vex & VX_RW1 ) && tuple == RWF_T1S ) ) )
                            and cl,not VX3_V
                            or  bl,VX1_R1
                        .else
                            and bl,not VX1_R1
                        .endif
                        .endc
                    .endsw

                .else

                    .switch bl
                    .case 0xC1
                        mov bl,0x91
                        .endc .if !( ch & VX_ZMM )
                        mov bl,0xB1
                        .endc .if !( ch & VX_ZMM8 )
                        mov bl,0xD1
                        .endc
                    .case 0xC5
                        mov bl,0xB1
                        .endc
                    .case 0xE2
                    .case 0xE3
                        .if !( cl & VX3_B ) || ( evex & 0x04 )
                            or bl,VX1_R1
                        .endif
                        or  cl,VX3_V
                        mov al,bl
                        and al,0x6F
                        .if evex == 0x08 && al == 0x62
                            mov al,bl
                            and al,0xF0
                            or evex,al
                        .endif
                        .endc
                    .default
                        mov al,bl
                        and al,0x0F
                        .if al == 1
                            or bl,VX1_R1
                        .elseif evex == 0x08 && al == 0x02
                            mov al,bl
                            and al,0xF0
                            or al,0x90
                            or evex,al
                        .endif
                        .endc
                    .endsw
                .endif
            .endif

        .else

            .if !( [esi].rex & REX_R )
                or bh,0x80
            .endif

            .if evex == 0

                mov bl,0xC5

            .else

                mov ah,evex
                mov al,ch
                and al,VX_OP1V or VX_OP2V or VX_OP3V or VX_OP3
                .switch al
                .case VX_OP3 or VX_OP2V or VX_OP3V       ;; 0, 1, 1
                    and cl,not VX3_V
                    .endc
                .case VX_OP3 or VX_OP1V or VX_OP2V       ;; 1, 1, 0
                    .if ah & VX1_X || [esi].opnd[OPNI3].type == OP_I8
                        and cl,not VX3_V
                    .endif
                    .endc
                .case VX_OP3 or VX_OP1V or VX_OP2V or VX_OP3V ;; 1, 1, 1
                    and cl,not VX3_V
                    .endc
                .case VX_OP3 or VX_OP2V                 ;; 0, 1, 0
                    .if ch & VX_ZMM
                        and cl,not VX3_V
                    .endif
                    .endc
                .case VX_OP2V                           ;; 0, 1
                .case VX_OP1V                           ;; 1, 0
                    .if ah == 0x20                      ;; VMOVQ
                        and bh,not 0x02
                        or  bh,0x01
                        add edi,instr_item              ;; 7E --> 6E
                    .elseif ah == 0xE0 && ( ch & VX_ZMM && \
                        [esi].opnd[OPND1].type == OP_ZMM && [esi].opnd[OPNI2].type == OP_ZMM )
                        mov ah,0xB0
                    .endif
                    .endc
                .case VX_OP3 or VX_OP1V                 ;; 1, 0, 0
                    .if ah == 0x10
                        and bh,not 0x70
                        and cl,not 0x08
                    .endif
                    .endc
                .endsw

                mov al,ah
                and al,0xF0
                or  al,0x01
                or  bl,al
                .if [esi].rex & REX_R
                    mov bl,0x61
                    .if [esi].opnd[OPND1].type == OP_R32 || ( ch & VX_ZMM8 )
                        or bl,0x10
                        .if ( ch & VX_OP1V or VX_OP2V or VX_OP3V )
                            and bl,not 0x40
                        .endif
                    .elseif evex == 0x10
                        or bl,0xF0
                    .elseif ( ch & VX_ZMM24 )
                        mov al,ch
                        and al,VX_OP1V or VX_OP2V or VX_OP3V
                        .if al == VX_OP1V or VX_OP2V && !( ch & VX_OP3 )
                            mov bl,0x21
                        .endif
                    .endif
                .elseif ch & VX_OP1V
                    mov bl,0xE1
                    .if ch & VX_OP2V
                        .if !( ch & VX_OP3 ) || ( ch & VX_OP3 && ch & VX_OP3V )
                            mov bl,0xA1
                        .endif
                    .elseif vex & VX_HALF && [esi].opnd[OPNI2].type & OP_I8
                        mov bl,0xF1
                    .else
                        or cl,VX3_V
                    .endif
                .elseif !( ch & VX_OP2V )
                    mov bl,0xF1
                    or  cl,VX3_V
                    .if evex == 0x10
                        and bh,not 0x08
                    .endif
                .elseif ch & VX_OP3
                    mov bl,0xF1
                .elseif ch & VX_OP2V && evex == 0x20
                    mov bl,0xE1
                .endif
            .endif
        .endif

        shl ecx,16
        or  ebx,ecx

        .if evex

            xor eax,eax
            xor edx,edx

            .if evex & VX_W1
                and vex,not VX_RW0
            .endif

            ;; Get index of memory address if any

            .if [esi].opnd[OPNI2].type & OP_M_ANY
                mov edx,OPNI2
            .endif
            .if [esi].opnd[edx].type & OP_M_ANY

                ;; EVEX-encoded instructions use a compressed displacement

                .if tuple == RWF_T1S

                    mov eax,MT_DWORD + 1
                    .if [esi].mem_type == MT_BYTE
                        mov eax,MT_BYTE + 1
                    .elseif [esi].mem_type == MT_WORD
                        mov eax,MT_WORD + 1
                    .elseif evex & VX_W1 || vex & VX_RW1
                        mov eax,MT_QWORD + 1
                    .endif

                .elseif [esi].evexP3 & VX3_B

                    ;; Embedded Broadcast {1tox} - EVEX.B=1

                    mov eax,MT_DWORD + 1 ;; Full Vector (FV) || Half Vector (HV) && EVEX.W0
                    .if evex & VX_W1 || ( vex & VX_RW1 && !( vex & VX_RW0 ) )
                        mov eax,MT_QWORD + 1;; FV && EVEX.W1
                    .endif
                .else

                    ;; Instructions Not Affected by Embedded Broadcast
                    ;;
                    ;; Type     ISize   EVEX.W  128     256     512     Comment
                    ;;
                    ;; FVM      N/A     N/A     16      32      64      Load/store or subDword full vector
                    ;; T1S      8bit    N/A     1       1       1       1 Tuple less than Full Vector
                    ;;          16bit   N/A     2       2       2
                    ;;          32bit   0       4       4       4
                    ;;          64bit   1       8       8       8
                    ;; T1F      32bit   N/A     4       4       4       1 Tuple memsize not affected by
                    ;;          64bit   N/A     8       8       8       EVEX.W
                    ;; T2       32bit   0       8       8       8       Broadcast (2 elements)
                    ;;          64bit   1       NA      16      16
                    ;; T4       32bit   0       NA      16      16      Broadcast (4 elements)
                    ;;          64bit   1       NA      NA      32
                    ;; T8       32bit   0       NA      NA      32      Broadcast (8 elements)
                    ;; HVM      N/A     N/A     8       16      32      SubQword Conversion
                    ;; QVM      N/A     N/A     4       8       16      SubDword Conversion
                    ;; OVM      N/A     N/A     2       4       8       SubWord Conversion
                    ;; M128     N/A     N/A     16      16      16      Shift count from memory
                    ;; MOVDDUP  N/A     N/A     8       32      64      VMOVDDUP

                    .switch [esi].mem_type
                    .case MT_OWORD
                    .case MT_YWORD
                    .case MT_ZWORD
                    .case MT_DWORD
                    .case MT_QWORD
                        mov al,[esi].mem_type
                        inc al
                        .endc
                    .default
                        .if [esi].opnd[edx].type & OP_M512
                            mov eax,MT_ZWORD + 1
                        .elseif [esi].opnd[edx].type & OP_M256
                            mov eax,MT_YWORD + 1
                        .elseif [esi].opnd[edx].type & OP_M128
                            mov eax,MT_OWORD + 1
                        .else
                            .endc
                        .endif

                        mov ecx,OPNI2
                        .if edx
                            xor ecx,ecx
                        .endif
                        .if [esi].opnd[ecx].type == OP_ZMM
                            mov eax,MT_ZWORD + 1
                        .elseif [esi].opnd[ecx].type == OP_YMM
                            mov eax,MT_YWORD + 1
                        .endif
                        .switch tuple
                        .case RWF_QVM
                            .if eax == MT_ZWORD + 1
                                mov eax,MT_OWORD + 1
                            .elseif eax == MT_YWORD + 1
                                mov eax,MT_QWORD + 1
                            .else
                                mov eax,MT_DWORD + 1
                            .endif
                            .endc
                        .case RWF_OVM
                            .if eax == MT_ZWORD + 1
                                mov eax,MT_QWORD + 1
                            .elseif eax == MT_YWORD + 1
                                mov eax,MT_DWORD + 1
                            .else
                                mov eax,MT_WORD + 1
                            .endif
                            .endc
                        .case RWF_HVM
                            .if eax == MT_ZWORD + 1
                                mov eax,MT_YWORD + 1
                            .elseif eax == MT_YWORD + 1
                                mov eax,MT_OWORD + 1
                            .else
                                mov eax,MT_QWORD + 1
                            .endif
                            .endc
                        .case RWF_T2
                            mov eax,MT_OWORD + 1
                            .endc .if vex & VX_RW1
                            mov eax,MT_QWORD + 1
                            .endc
                        .case RWF_T4
                            mov eax,MT_YWORD + 1
                            .endc .if vex & VX_RW1
                        .case RWF_M128
                            mov eax,MT_OWORD + 1
                            .endc
                        .endsw
                        .endc
                    .endsw
                .endif
            .endif

            .if eax && [esi].opnd[edx].data32l

                or  [esi].rm_byte,MOD_10
                and [esi].rm_byte,not MOD_01
                mov ecx,[esi].opnd[edx].data32l
                dec eax
                and ecx,eax

                .if !ecx

                    push edx
                    lea  ecx,[eax+1]
                    mov  eax,[esi].opnd[edx].data32l
                    cdq
                    idiv ecx
                    pop  edx

                    .ifs eax >= SCHAR_MIN && eax <= SCHAR_MAX

                        mov [esi].opnd[edx].data32l,eax
                        and [esi].rm_byte,not MOD_10
                        or  [esi].rm_byte,MOD_01
                    .endif
                .endif
            .endif

            .if evex & VX_XMMI

                or  bh,0x10
                mov cl,[esi].opc_or
                mov al,cl
                and ecx,0x1F
                and eax,0x40
                or  eax,0x01
                mov edx,ecx
                shr edx,1
                not edx
                and edx,0x08
                or  eax,edx
                .if al & 0x40 && [esi].opnd[OPNI2].type == OP_YMM
                    and al,not 0x40
                    or  al,0x20
                .endif

                shl eax,16
                and ebx,0xFF00FFFF
                or  ebx,eax
                shl ecx,3
                not ecx
                and ecx,0x40
                mov al,evex
                and eax,0xF0
                or  eax,0x02
                or  eax,ecx
                mov cl,[esi].sib
                and ecx,0xC0
                .if cl == 0x80
                    or al,0x20
                .endif
                mov bl,al
                mov [esi].opc_or,0
            .endif
        .endif

        OutputByte(bl)
        shr ebx,8

        .if evex
            or bl,VX2_W or VX2_1
            .if vex & VX_RW0 ;;  W0 and W1 may be set for VEX/EVEX encoding
                and bl,not VX2_W
            .endif
            OutputByte(bl)
            shr ebx,8
            .if bh & VX_SAE && !( [esi].evexP3 & VX3_L1 )
                and bl,not VX3_L1
            .endif
            OutputByte(bl)
        .else
            mov edx,edi
            mov edi,[esi].pinstr
            .if [edi].evex & VX_XMMI
                .if [edi].evex == 0x09 ;; VEX-Encoded GPR Instructions

                    mov al,rmbyte
                    not al
                    shl al,3
                    and al,0x38
                    and bl,0xC7
                    or  bl,al
                    .if [esi].rex & 0x04
                        and bl,0xBF
                    .endif
                    .if [esi].token == T_BLSMSK
                        and [esi].rm_byte,0xF7
                    .elseif [esi].token == T_BLSMSK
                        mov al,rmbyte
                        and al,0xC8
                        mov [esi].rm_byte,al
                    .else
                        and [esi].rm_byte,0xCF
                    .endif
                .else
                    mov al,[esi].opc_or
                    shl al,3
                    not al
                    and al,0x38
                    and bl,0xC7
                    or  bl,al
                    mov al,[esi].opc_or
                    shr al,4
                    or  bl,al
                    mov [esi].opc_or,0
                .endif
            .endif
            mov edi,edx
            OutputByte(bl)
        .endif
    .else

        ;; the REX prefix must be located after the other prefixes

        .if [esi].rex != 0
            .if [esi].Ofssize != USE64
                asmerr(2024)
            .endif
            movzx eax,[esi].rex
            or eax,0x40
            OutputByte(eax)
        .endif

        ;; Output extended opcode
        ;; special case for some 286 and 386 instructions
        ;; or 3DNow!, MMX and SSEx instructions

        .if [edi].byte1_info >= F_0F
            OutputByte(EXTENDED_OPCODE)
            .switch [edi].byte1_info
            .case F_0F0F: OutputByte(EXTENDED_OPCODE) : .endc
            .case F_0F38
            .case F_F20F38
            .case F_660F38: OutputByte(0x38) : .endc
            .case F_0F3A
            .case F_660F3A: OutputByte(0x3A) : .endc
            .endsw
        .endif
    .endif

    xor ecx,ecx
    .if [esi].flags & CI_ISWIDE
        inc ecx
    .endif

    mov al,[edi].flags
    and eax,II_RM_INFO
    shr eax,4

    .switch eax
    .case R_in_OP
        mov al,[esi].rm_byte
        and al,NOT_BIT_67
        or  al,[edi].opcode
        OutputByte(eax)
        .endc
    .case no_RM
        mov al,[edi].opcode
        or  al,cl
        OutputByte(eax)
        .endc
    .case no_WDS
        xor ecx,ecx
        ;; no break
    .default

        ;; opcode (with w d s bits), rm-byte
        ;; don't emit opcode for 3DNow! instructions

        .if [edi].byte1_info != F_0F0F
            mov al,[edi].opcode
            or  al,cl
            or  al,[esi].opc_or
            OutputByte(eax)
        .endif

        ;; emit ModRM byte; bits 7-6 = Mod, bits 5-3 = Reg, bits 2-0 = R/M

        mov bl,[edi].rm_byte
        or  bl,[esi].rm_byte
        .if [esi].flags & CI_BASE_RIP ;; @RIP
            and bl,not MOD_10
        .endif
        OutputByte(ebx)

        ;; no SIB for 16bit

        .return .if ( [esi].Ofssize == USE16 && ![esi].adrsiz ) || \
                    ( [esi].Ofssize == USE32 && [esi].adrsiz )

        and bl,NOT_BIT_345
        .switch bl
        .case 0x04 ;; mod = 00, r/m = 100, s-i-b is present
        .case 0x44 ;; mod = 01, r/m = 100, s-i-b is present
        .case 0x84 ;; mod = 10, r/m = 100, s-i-b is present

            ;; emit SIB byte; bits 7-6 = Scale, bits 5-3 = Index, bits 2-0 = Base

            OutputByte([esi].sib)
            .endc
        .endsw
        .endc
    .endsw
    ret

output_opc endp

output_data proc uses edi ebx determinant:int_t, index:int_t
;;
;; output address displacement and immediate data;
;;

    xor ebx,ebx
    mov edi,[esi].pinstr
    movzx eax,[esi].token
    .switch eax
    .case T_ANDN
    .case T_MULX
    .case T_PDEP
    .case T_PEXT
        .return .if ( ![esi].opnd[OPNI2].data32l || index == OPND3 )
        .endc
    .case T_BEXTR
    .case T_SARX
    .case T_SHLX
    .case T_SHRX
    .case T_BZHI
        .return .if ( ![esi].opnd[OPNI2].data32l || !index || index == OPND3 )
        .endc
    .case T_XLAT
    .case T_XLATB
        .return
    .endsw

    ;;
    ;; skip the memory operand for XLAT/XLATB and string instructions!
    ;;
    mov al,[edi].flags
    and eax,II_ALLOWED_PREFIX
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
        mov al,[esi].rm_byte
        and eax,BIT_67

        .switch eax
        .case MOD_01 ;; 8-bit displacement
            mov ebx,1
            .endc
        .case MOD_00 ;; direct; base and/or index with no disp
            .if( ( [esi].Ofssize == USE16 && ![esi].adrsiz ) || \
                 ( [esi].Ofssize == USE32 && [esi].adrsiz ) )

                mov al,[esi].rm_byte
                and al,BIT_012
                .if( al == RM_D16 )
                     mov ebx,2 ;; = size of displacement
                .endif
            .else
                ;;
                ;; v2.11: special case, 64-bit direct memory addressing, opcodes 0xA0 - 0xA3
                ;;
                mov al,[edi].opcode
                and al,0xFC
                .if( [esi].Ofssize == USE64 && al == 0xA0 && [edi].byte1_info == 0 )
                    mov ebx,8
                .else
                    mov al,[esi].rm_byte
                    and eax,BIT_012
                    .switch eax
                    .case RM_SIB ;; 0x04 (equals register # for ESP)
                        mov al,[esi].sib
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
                        mov eax,[esi].opnd[ecx].data32l
                        mov edx,[esi].opnd[ecx].data32h
                        xor ecx,ecx
                        .if edx || eax >= 0x80000000
                            inc ecx
                            .if !( edx < 0xffffffff || ( edx == 0xffffffff && eax < 0x80000000 ) )
                                xor ecx,ecx
                            .endif
                        .endif
                        .if ( [esi].Ofssize == USE64 && ecx )
                            asmerr( 2070 )
                        .endif
                    .endsw
                .endif
            .endif
            .endc
        .case MOD_10  ;; 16- or 32-bit displacement
            mov ebx,4
            .if( ( [esi].Ofssize == USE16 && ![esi].adrsiz ) || \
                 ( [esi].Ofssize == USE32 && [esi].adrsiz ) )
                mov ebx,2
            .endif
            .endc
        .endsw
    .endsw

    mov edi,ebx
    imul ebx,index,opnd_item

    .if ( edi )
        .if ( [esi].opnd[ebx].InsFixup )

            ;; v2.07: fixup type check moved here

            .if ( Parse_Pass > PASS_1 )

                mov eax,1
                mov edx,[esi].opnd[ebx].InsFixup
                mov cl,[edx].fixup.type
                shl eax,cl
                mov ecx,ModuleInfo.fmtopt
                movzx ecx,[ecx].format_options.invalid_fixup_type

                .if ( eax & ecx )

                    mov ecx,ModuleInfo.fmtopt
                    lea eax,[ecx].format_options.formatname
                    lea ecx,szNull
                    .if [edx].fixup.sym
                        mov ecx,[edx].fixup.sym
                        mov ecx,[ecx].asym.name
                    .endif
                    asmerr( 3001, eax, ecx )

                    ;; don't exit!

                .endif
            .endif
            .if ( write_to_file )

                GetCurrOffset()
                mov edx,[esi].opnd[ebx].InsFixup
                mov [edx].fixup.locofs,eax
                OutputBytes( &[esi].opnd[ebx].data32l, edi, edx )
                .return
            .endif
        .endif
        OutputBytes( &[esi].opnd[ebx].data32l, edi, NULL )
    .endif
    ret

output_data endp

check_3rd_operand proc uses edi ebx

    mov   edi,[esi].pinstr
    movzx eax,[edi].opclsidx
    imul  ebx,eax,opnd_class

    .if( ( opnd_clstab[ebx].opnd_type_3rd == OP3_NONE ) || \
         ( opnd_clstab[ebx].opnd_type_3rd == OP3_HID ) )
        .return( ERROR ) .if ( [esi].opnd[OPNI3].type != OP_NONE )
        .return( NOT_ERROR )
    .endif

    ;; current variant needs a 3rd operand

    movzx eax,opnd_clstab[ebx].opnd_type_3rd

    .switch eax

    .case OP3_CL
        .return( NOT_ERROR ) .if ( [esi].opnd[OPNI3].type == OP_CL )
        .endc

    .case OP3_I8_U ;; IMUL, SHxD, a few MMX/SSE

        ;; for IMUL, the operand is signed!

        .if ( ( [esi].opnd[OPNI3].type & OP_I ) && [esi].opnd[OPNI3].data32l >= -128 )
            .if ( ( [esi].token == T_IMUL && [esi].opnd[OPNI3].data32l < 128 ) || \
                ( [esi].token != T_IMUL && [esi].opnd[OPNI3].data32l < 256 ) )
                mov [esi].opnd[OPNI3].type,OP_I8
                .return( NOT_ERROR )
            .endif
        .endif
        .endc

    .case OP3_I ;; IMUL
        .endc .if !( [esi].opnd[OPNI3].type & OP_I )
        .return( NOT_ERROR )

    .case OP3_XMM0

        ;; for VEX encoding, XMM0 has the meaning: any XMM/YMM register

        .if ( [esi].token >= VEX_START )

            .return( NOT_ERROR ) .if ( [esi].opnd[OPNI3].type & ( OP_XMM or OP_YMM or OP_ZMM or OP_K ) )

            movzx eax,[esi].token
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
        .elseif ( [esi].opnd[OPNI3].type == OP_XMM && [esi].opnd[OPNI3].data32l == 0 )
            .return( NOT_ERROR )
        .endif
        .endc
    .endsw
    mov eax,ERROR
    ret

check_3rd_operand endp

output_3rd_operand proc uses edi ebx

    mov   edi,[esi].pinstr
    movzx eax,[edi].opclsidx
    imul  ebx,eax,opnd_class

    .if( opnd_clstab[ebx].opnd_type_3rd == OP3_I8_U )
        output_data( OP_I8, OPND3 )
    .elseif( opnd_clstab[ebx].opnd_type_3rd == OP3_I )
        output_data( [esi].opnd[OPNI3].type, OPND3 )
    .elseif( opnd_clstab[ebx].opnd_type_3rd == OP3_HID )
        movzx eax,[esi].token
        sub eax,T_CMPEQPD
        mov ecx,8
        xor edx,edx
        div ecx
        mov [esi].opnd[OPNI3].data32l,edx
        mov [esi].opnd[OPNI3].InsFixup,NULL
        output_data( OP_I8, OPND3 )
    .elseif( [esi].token >= VEX_START && opnd_clstab[ebx].opnd_type_3rd == OP3_XMM0 )
        mov eax,[esi].opnd[OPNI3].data32l
        shl eax,4
        mov [esi].opnd[OPNI3].data32l,eax
        output_data( OP_I8, OPND3 )
    .endif
    ret
output_3rd_operand endp

match_phase_3 proc uses edi ebx opnd1:int_t
;;
;; - this routine will look up the assembler opcode table and try to match
;;   the second operand with what we get;
;; - if second operand match then it will output code; if not, pass back to
;;   codegen() and continue to scan InstrTable;
;; - possible return codes: NOT_ERROR (=done), ERROR (=nothing found)
;;

  local determinant:int_t

    mov   edi,[esi].pinstr
    movzx eax,[edi].opclsidx
    imul  ebx,eax,opnd_class

    ;; remember first op type

    mov determinant,opnd_clstab[ebx].opnd_type[OPND1]
    mov ebx,[esi].opnd[OPNI2].type
    movzx eax,[esi].token
    sub eax,VEX_START

    .if ( [esi].token >= VEX_START && ( vex_flags[eax] & VX_L ) )

        .if ( [esi].opnd[OPND1].type & ( OP_K or OP_YMM or OP_ZMM or OP_M256 or OP_M512 ) )

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
            .elseif ( ( ebx & OP_XMM ) && !( vex_flags[eax] & VX_HALF ) )
                .return( asmerr( 2085 ) )
            .endif

        ;; may be necessary to cover the cases where the first operand is a memory operand
        ;; "without size" and the second operand is a ymm register
        ;;
        .elseif ( [esi].opnd[OPND1].type == OP_M )
            .if ( ebx & ( OP_YMM or OP_ZMM ) )
                or ebx,OP_XMM
            .endif
        .endif
    .elseif ( opnd1 == OP_XMM && ebx == OP_M64 )

        ;; v2.27: case xmm,m64 (real4 or 8)

        mov eax,CurrProc

        .if ( eax )
            .if ( [eax].asym.langtype == LANG_VECTORCALL )
                or ebx,OP_M128
            .endif
        .elseif ( ModuleInfo.langtype == LANG_VECTORCALL )
            or ebx,OP_M128
        .endif
    .endif

    .repeat

        mov     edi,[esi].pinstr
        movzx   eax,[edi].opclsidx
        imul    eax,eax,opnd_class
        mov     eax,opnd_clstab[eax].opnd_type[4] ; OPND2

        .switch eax

        .case OP_I ;; arith, MOV, IMUL, TEST

            .if ebx & eax

                ;; This branch exits with either ERROR or NOT_ERROR.
                ;; So it can modify the CodeInfo fields without harm.

                .if opnd1 & OP_R8

                    ;; 8-bit register, so output 8-bit data

                    mov [esi].opsiz,0
                    mov ebx,OP_I8
                    mov eax,[esi].opnd[OPNI2].InsFixup
                    .if eax != NULL

                        ;; v1.96: make sure FIX_HIBYTE isn't overwritten!

                        .if [eax].fixup.type != FIX_HIBYTE

                            mov [eax].fixup.type,FIX_OFF8
                        .endif
                    .endif

                .elseif opnd1 & OP_R16

                    ;; 16-bit register, so output 16-bit data

                    mov ebx,OP_I16

                .elseif opnd1 & ( OP_R32 or OP_R64 )

                    ;; 32- or 64-bit register, so output 32-bit data

                    mov [esi].opsiz,1
                    .if [esi].Ofssize
                        mov [esi].opsiz,0
                    .endif
                    mov ebx,OP_I32

                .elseif opnd1 & OP_M

                    ;; there is no reason this should be only for T_MOV

                    .switch OperandSize(opnd1, esi)
                    .case 1
                        mov ebx,OP_I8
                        mov [esi].opsiz,0
                        .endc
                    .case 2
                        mov ebx,OP_I16
                        mov [esi].opsiz,0
                        .if [esi].Ofssize
                            mov [esi].opsiz,1
                        .endif
                        .endc

                        ;; mov [mem], imm64 doesn't exist. It's ensured that
                        ;; immediate data is 32bit only

                    .case 8
                    .case 4
                        mov ebx,OP_I32
                        mov [esi].opsiz,1
                        .if [esi].Ofssize
                            mov [esi].opsiz,0
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
            .if ebx & eax

                .endc .if ( [esi].flags & CI_CONST_SIZE_FIXED ) && ebx != OP_I8

                ;; v2.03: lower bound wasn't checked
                ;; range of unsigned 8-bit is -128 - +255

                .if [esi].opnd[OPNI2].data32l <= UCHAR_MAX && [esi].opnd[OPNI2].data32l >= SCHAR_MIN

                    ;; v2.06: if there's an external, adjust the fixup if it is > 8-bit

                    mov eax,[esi].opnd[OPNI2].InsFixup
                    .if eax != NULL
                        .if [eax].fixup.type == FIX_OFF16 || [eax].fixup.type == FIX_OFF32

                            mov [eax].fixup.type,FIX_OFF8
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
            movzx eax,[esi].token
            .endc .if ModuleInfo.NoSignExtend && ( eax == T_AND || eax == T_OR || eax == T_XOR )

            mov eax,[esi].opnd[OPNI2].InsFixup
            .if eax
                mov ecx,[eax].fixup.sym
                .endc .if [ecx].asym.state != SYM_UNDEFINED ;; external? then skip
            .endif

            .if !( [esi].flags & CI_CONST_SIZE_FIXED )

                movsx eax,byte ptr [esi].opnd[OPNI2].data32l
                movsx ecx,word ptr [esi].opnd[OPNI2].data32l
                .if ( opnd1 & ( OP_R16 or OP_M16 ) ) && eax == ecx
                    or edx,OP_I16
                .elseif ( opnd1 & ( OP_RGT16 or OP_MGT16 ) ) && eax == [esi].opnd[OPNI2].data32l
                    or edx,OP_I32
                .endif
            .endif

            .if ebx & edx

                output_opc()
                output_data(opnd1, OPND1)
                output_data(OP_I8, OPND2)

                .return NOT_ERROR
            .endif
            .endc

        .case OP_I_1 ;; shift ops
            .if ebx & eax
               .if [esi].opnd[OPNI2].data32l == 1

                   output_opc()
                   output_data(opnd1, OPND1)

                   ;; the immediate is "implicite"

                   .return NOT_ERROR
               .endif
            .endif
            .endc
        .case OP_RGT16
            .switch [esi].token
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
            .if ebx & eax
                .endc .if check_3rd_operand() == ERROR
                output_opc()
                .if opnd1 & (OP_I_ANY or OP_M_ANY )
                    output_data(opnd1, OPND1)
                .endif
                .if ebx & (OP_I_ANY or OP_M_ANY )
                    output_data(ebx, OPND2)
                .endif

                movzx eax,[edi].opclsidx
                imul eax,eax,opnd_class
                .if opnd_clstab[eax].opnd_type_3rd != OP3_NONE && !( [edi].evex & VX_XMMI )
                    output_3rd_operand()
                .endif
                .if [edi].byte1_info == F_0F0F ;; output 3dNow opcode?
                    movzx eax,[edi].opcode
                    .if [esi].flags & CI_ISWIDE
                        or eax,1
                    .endif
                    OutputByte(eax)
                .endif
                .return NOT_ERROR
            .endif
            .endc
        .endsw

        add   [esi].pinstr,instr_item
        mov   edi,[esi].pinstr
        movzx eax,[edi].opclsidx
        imul  eax,eax,opnd_class
        mov   eax,opnd_clstab[eax].opnd_type[OPND1]

    .until !( eax == determinant && !( [edi].flags & II_FIRST ) )

    sub [esi].pinstr,instr_item ;; pointer will be increased in codegen()
    mov eax,ERROR
    ret

match_phase_3 endp

    assume edi:fixup_t

add_bytes proc uses edi index:int_t

    imul eax,index,opnd_item
    mov  edi,[esi].opnd[eax].InsFixup

    .if ( edi && [edi].type == FIX_RELOFF32 )

        GetCurrOffset()
        sub eax,[edi].locofs

        ;; v2.25 - added ->offset to ->addbytes
        ;; v2.28 - removed
        ;; if ( CodeInfo->opnd[index].InsFixup->sym && CodeInfo->opnd[index].InsFixup->sym->isarray )
        ;;      bytes += CodeInfo->opnd[index].InsFixup->offset;
        ;;

        mov [edi].addbytes,al
    .endif
    ret

add_bytes endp

    assume edi:instr_t

check_operand_2 proc uses edi ebx opnd1:int_t
;;
;; check if a second operand has been entered.
;; If yes, call match_phase_3();
;; else emit opcode and optional data.
;; possible return codes: ERROR (=nothing found), NOT_ERROR (=done)
;;
    .if [esi].opnd[OPNI2].type == OP_NONE

        mov     edi,[esi].pinstr
        movzx   eax,[edi].opclsidx
        imul    ecx,eax,opnd_class

        .return ERROR .if opnd_clstab[ecx].opnd_type[4] != OP_NONE


        ;; 1 opnd instruction found

        ;; v2.06: added check for unspecified size of mem op

        .if ( opnd1 == OP_M )

            add   edi,instr_item
            movzx eax,[edi].opclsidx
            imul  eax,eax,opnd_class

            .if ( ( opnd_clstab[eax].opnd_type[OPND1] & OP_M ) && !( [edi].flags & II_FIRST ) )

                ;; skip error if mem op is a forward reference

                xor ecx,ecx
                xor edx,edx
                mov eax,[esi].opnd[OPND1].InsFixup
                .if eax
                    mov edx,[eax].fixup.sym
                    .if edx
                        mov cl,[edx].asym.state
                    .endif
                .endif

                .if ( !( [esi].flags & CI_UNDEF_SYM ) && ( !eax || !edx || ecx != SYM_UNDEFINED ) )

                    asmerr(2023)
                .endif
            .endif
        .endif

        output_opc()
        output_data( opnd1, OPND1 )
        .if ( [esi].Ofssize == USE64 )

            add_bytes(OPND1)
        .endif
        .return NOT_ERROR
    .endif

    ;; check second operand

    .if match_phase_3(opnd1) == NOT_ERROR
        ;;
        ;; for rip-relative fixups, the instruction end is needed
        ;;
        .if ( [esi].Ofssize == USE64 )

            add_bytes(OPND1)
            add_bytes(OPND2)
        .endif
        .return NOT_ERROR
    .endif
    mov eax,ERROR
    ret

check_operand_2 endp

;; - codegen() will look up the assembler opcode table and try to find
;;   a matching first operand;
;; - if one is found then it will call check_operand_2() to determine
;;   if further operands also match; else, it must be error.

codegen proc public uses esi edi ebx CodeInfo:ptr code_info, oldofs:uint_t

  local evex:byte

    mov esi,CodeInfo
    mov evex,[esi].evex
    mov edi,[esi].pinstr
    ;;
    ;; privileged instructions ok?
    ;;
    mov ax,[edi].cpu
    and eax,P_PM
    mov ecx,ModuleInfo.curr_cpu
    and ecx,P_PM
    .return(asmerr(2085)) .if eax > ecx

    mov ebx,[esi].opnd[OPND1].type

    ;; if first operand is immediate data, set compatible flags

    .if( ebx & OP_I )
        .if( ebx == OP_I8 )
            mov ebx,OP_IGE8
        .elseif( ebx == OP_I16 )
            mov ebx,OP_IGE16
        .endif
    .endif

    movzx eax,[esi].token
    sub   eax,VEX_START

    .if ( [esi].token >= VEX_START && ( vex_flags[eax] & VX_L ) )

        .if ( ebx & ( OP_YMM or OP_M256 or OP_ZMM or OP_M512 ) )

            .return(asmerr(2070)) .if [esi].opnd[OPNI2].type & OP_XMM && !( vex_flags[eax] & VX_HALF )

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

        movzx eax,[edi].opclsidx
        imul  eax,eax,opnd_class
        mov   ecx,opnd_clstab[eax].opnd_type[OPND1]

        ;; v2.06: simplified

        .if ( ecx == OP_NONE && ebx == OP_NONE )

            output_opc()
            .if ( ModuleInfo.curr_file[LST*4] )
                LstWrite(LSTTYPE_CODE, oldofs, NULL)
            .endif
            .return NOT_ERROR
        .endif

        .if ebx & ecx

            ;; for immediate operands, the idata type has sometimes
            ;; to be modified in opnd_type[OPND1], to make output_data()
            ;; emit the correct number of bytes.

            mov eax,ERROR
            .switch ecx
            .case OP_I32 ;; CALL, JMP, PUSHD
            .case OP_I16 ;; CALL, JMP, RETx, ENTER, PUSHW
                check_operand_2(ecx)
                .endc
            .case OP_I8_U ;; INT xx; OUT xx, AL
                .if [esi].opnd[OPND1].data32l <= UCHAR_MAX && \
                    [esi].opnd[OPND1].data32l >= SCHAR_MIN
                    check_operand_2(OP_I8)
                .endif
                .endc
            .case OP_I_3 ;; INT 3
                .if [esi].opnd[OPND1].data32l == 3
                    check_operand_2(OP_NONE)
                .endif
                .endc
            .default
                .endc .if evex && [edi].evex == 0
                check_operand_2([esi].opnd[OPND1].type)
            .endsw
            .if eax == NOT_ERROR
                .if ModuleInfo.curr_file[LST*4]
                    LstWrite(LSTTYPE_CODE, oldofs, NULL)
                .endif
                .return NOT_ERROR
            .endif
        .endif
        add [esi].pinstr,instr_item
        mov edi,[esi].pinstr
    .until [edi].flags & II_FIRST
    asmerr(2070)
    ret
codegen endp

    end
