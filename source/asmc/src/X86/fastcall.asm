include string.inc
include limits.inc
include malloc.inc
include stdio.inc
include quadmath.inc
include asmc.inc
include lqueue.inc
include parser.inc
include reswords.inc
include segment.inc
include operands.inc
include expreval.inc
include atofloat.inc
include memalloc.inc
include regno.inc

.pragma warning(disable: 6004)

public  fastcall_tab

GetGroup        proto :asym_t
ifndef __ASMC64__
GetSegmentPart  proto :ptr expr, :string_t, :string_t
endif
search_assume   proto :asym_t, :int_t, :int_t

invoke_conv     struc
invokestart     dd ? ; dsym *, int, int, asmtok *, int *
invokeend       dd ? ; dsym *, int, int
handleparam     dd ? ; dsym *, int, dsym *, bool, expr *, char *, byte *
invoke_conv     ends

R0_USED         equ 0x01 ; register contents of AX/EAX/RAX is destroyed
R0_H_CLEARED    equ 0x02 ; 16bit: high byte of R0 (=AH) has been set to 0
R0_X_CLEARED    equ 0x04 ; 16bit: register R0 (=AX) has been set to 0
R2_USED         equ 0x08 ; contents of DX is destroyed ( via CWD ); cpu < 80386 only
RDI_USED        equ 0x02 ; elf64: register contents of DIL/DI/EDI/RDI is destroyed
RSI_USED        equ 0x04 ; elf64: register contents of SIL/SI/ESI/RSI is destroyed
RCX_USED        equ 0x08 ; win64: register contents of CL/CX/ECX/RCX is destroyed
RDX_USED        equ 0x10 ; win64: register contents of DL/DX/EDX/RDX is destroyed
R8_USED         equ 0x20 ; win64: register contents of R8B/R8W/R8D/R8 is destroyed
R9_USED         equ 0x40 ; win64: register contents of R9B/R9W/R9D/R9 is destroyed
ROW_AX_USED     equ 0x08 ; watc: register contents of AL/AX/EAX is destroyed
ROW_DX_USED     equ 0x10 ; watc: register contents of DL/DX/EDX is destroyed
ROW_BX_USED     equ 0x20 ; watc: register contents of BL/BX/EBX is destroyed
ROW_CX_USED     equ 0x40 ; watc: register contents of CL/CX/ECX is destroyed

RPAR_START      equ 3 ; Win64: RCX first param start at bit 3
ROW_START       equ 3 ; watc: irst param start at bit 3
ELF64_START     equ 1 ; elf64: RDI first param start at bit 6

    .data

externdef       sym_ReservedStack:asym_t    ; max stack space required by INVOKE
externdef       size_vararg:int_t        ; size of :VARARG arguments

REGPAR_WIN64    equ 0x0306 ; regs 1, 2, 8 and 9
REGPAR_ELF64    equ 0x03C6 ; regs 1, 2, 6, 7, 8 and 9

fastcall_tab label invoke_conv
ifndef __ASMC64__
    dd ms32_fcstart, ms32_fcend , ms32_param ; FCT_MSC
    dd watc_fcstart, watc_fcend , watc_param ; FCT_WATCOMC
    dd ms64_fcstart, ms64_fcend , ms64_param ; FCT_WIN64
    dd elf64_fcstart,elf64_fcend,elf64_param ; FCT_ELF64
    dd vc32_fcstart, ms32_fcend , vc32_param ; FCT_VEC32
    dd ms64_fcstart, ms64_fcend , ms64_param ; FCT_VEC64

ms16_regs label byte
    db T_AX,  T_DX, T_BX

ms32_regs label byte
    db T_ECX, T_EDX
else
    dd 0, 0, 0 ; FCT_MSC
    dd 0, 0, 0 ; FCT_WATCOMC
    dd ms64_fcstart, ms64_fcend , ms64_param ; FCT_WIN64
    dd elf64_fcstart,elf64_fcend,elf64_param ; FCT_ELF64
    dd 0, 0, 0 ; FCT_VEC32
    dd ms64_fcstart, ms64_fcend , ms64_param ; FCT_VEC64
endif

ms64_regs label byte
    db T_CL,  T_DL,  T_R8B, T_R9B
    db T_CX,  T_DX,  T_R8W, T_R9W
    db T_ECX, T_EDX, T_R8D, T_R9D
    db T_RCX, T_RDX, T_R8,  T_R9

; segment register names, order must match ASSUME_ enum

;stackreg label byte
;    db T_SP, T_ESP, T_RSP

fcscratch dd 0  ; exclusively to be used by FASTCALL helper functions

.code

fastcall_init proc
    mov fcscratch,0
    ret
fastcall_init endp

;; get segment part of an argument
;; v2.05: extracted from PushInvokeParam(),
;; so it could be used by watc_param() as well.

GetSegm macro x
    exitm<[x].asym._segment>
    endm

ifndef __ASMC64__
GetSegmentPart proc uses esi edi ebx opnd:ptr expr, buffer:string_t, fullparam:string_t

    mov esi,T_NULL
    mov edi,opnd
    mov eax,[edi].expr.sym
    mov edx,[edi].expr.override

    .if edx

        .if [edx].asm_tok.token == T_REG
            mov esi,[edx].asm_tok.tokval
        .else
            strcpy( buffer, [edx].asm_tok.string_ptr )
        .endif

    .elseif eax && [eax].asym._segment

        mov ebx,[eax].asym._segment
        mov ecx,[ebx].esym.seginfo

        .if [ecx].seg_info.segtype == SEGTYPE_DATA || \
            [ecx].seg_info.segtype == SEGTYPE_BSS
            search_assume(ebx, ASSUME_DS, TRUE)
        .else
            search_assume(ebx, ASSUME_CS, TRUE)
        .endif
        .if eax != ASSUME_NOTHING

            lea esi,[eax+T_ES] ; v2.08: T_ES is first seg reg in special.h
        .else
            .if !GetGroup([edi].expr.sym)
                mov eax,ebx
            .endif
            .if eax
                strcpy(buffer, [eax].asym.name)
            .else
                strcpy(buffer, "seg ")
                strcat(buffer, fullparam)
            .endif
        .endif
    .elseif eax && [eax].asym.state == SYM_STACK
        mov esi,T_SS
    .else
        strcpy(buffer,"seg ")
        strcat(buffer, fullparam)
    .endif
    mov eax,esi
    ret

GetSegmentPart endp
endif

option proc:private


; macro to convert register number to param number:
; 1 -> 0 (rCX)
; 2 -> 1 (rDX)
; 8 -> 2 (r8)
; 9 -> 3 (r9)
;
GetParmIndex macro x
    mov eax,x
    dec eax
    .if eax >= 7
        sub eax,5
    .endif
    exitm<eax>
    endm

;-------------------------------------------------------------------------------
; FCT_MSC
;-------------------------------------------------------------------------------
ifndef __ASMC64__

ms32_fcstart proc pp:dsym_t, numparams:int_t, start:int_t,
    tokenarray:tok_t, value:ptr int_t

    .return 0 .if GetSymOfssize(pp) == USE16

    .for eax=pp, eax=[eax].esym.procinfo,
         eax=[eax].proc_info.paralist: eax: eax=[eax].esym.nextparam

        .if [eax].asym.state == SYM_TMACRO

            inc fcscratch
        .endif
    .endf
    mov eax,1
    ret

ms32_fcstart endp

ms32_param proc uses esi edi ebx pp:dsym_t, index:int_t, param:dsym_t, adr:int_t,
    opnd:ptr expr, paramvalue:string_t, r0used:ptr byte

  local z

    mov esi,param
    .return 0 .if [esi].asym.state != SYM_TMACRO

    .if GetSymOfssize(pp) == USE16
        lea edi,ms16_regs
        add edi,fcscratch
        inc fcscratch
    .else
        dec fcscratch
        lea edi,ms32_regs
        add edi,fcscratch
    .endif
    movzx ebx,byte ptr [edi]

    .if adr

        AddLineQueueX(" lea %r, %s", ebx, paramvalue)
    .else

        mov z,SizeFromMemtype([esi].asym.mem_type, USE_EMPTY, [esi].asym.type)
        mov edi,opnd

        .if [edi].expr.kind != EXPR_CONST && z < SizeFromRegister(ebx)

            mov eax,ModuleInfo.curr_cpu
            and eax,P_CPU_MASK
            .if eax >= P_386
                mov ecx,T_MOVSX
                .if !( [esi].asym.mem_type & MT_SIGNED )
                    mov ecx,T_MOVZX
                .endif
                AddLineQueueX(" %r %r, %s", ecx, ebx, paramvalue)
            .else
                imul eax,ebx,special_item
                movzx edi,SpecialTable[eax].bytval
                AddLineQueueX(" mov %r, %s", &[edi+T_AL], paramvalue)
                AddLineQueueX(" mov %r, 0",  &[edi+T_AH])
            .endif
        .else
            mov eax,[edi].expr.base_reg
            .if [edi].expr.kind == EXPR_REG && !([edi].expr.flags & E_INDIRECT) && eax

                .return 1 .if [eax].asm_tok.tokval == ebx
            .endif
            AddLineQueueX(" mov %r, %s", ebx, paramvalue)
        .endif

        .if ebx == T_AX
            mov eax,r0used
            or byte ptr [eax],R0_USED
        .endif
    .endif
    mov eax,1
    ret

ms32_param endp

ms32_fcend proc pp, numparams, value
    ret
ms32_fcend endp

;-------------------------------------------------------------------------------
; FCT_VEC32
;-------------------------------------------------------------------------------

vc32_fcstart proc pp:dsym_t, numparams:int_t, start:int_t,
    tokenarray:tok_t, value:ptr int_t

    .for eax=pp, eax=[eax].esym.procinfo,
         eax=[eax].proc_info.paralist: eax: eax=[eax].esym.nextparam

        .if [eax].asym.state == SYM_TMACRO || \
            ( [eax].asym.state == SYM_STACK && [eax].asym.total_size <= 16 )

            inc fcscratch
        .endif
    .endf
    mov eax,1
    ret

vc32_fcstart endp

vc32_param proc uses esi edi ebx pp:dsym_t, index:int_t, param:dsym_t, adr:int_t,
    opnd:ptr expr, paramvalue:string_t, r0used:ptr byte

    local z
    local value[64]:sbyte

    mov esi,param
    xor eax,eax

    mov cl,[esi].asym.state
    .return .if !( cl == SYM_TMACRO || cl == SYM_STACK || !fcscratch )
    .return .if ( cl == SYM_STACK && [esi].asym.total_size > 16 )

    dec fcscratch
    mov edx,fcscratch
    .if cl == SYM_STACK || edx > 1 || [esi].asym.mem_type & MT_FLOAT
        .return .if edx > 5
        lea ebx,[edx+T_XMM0]
    .else
        .return .if edx > 1
        movzx ebx,ms32_regs[edx]
    .endif

    .if adr

        AddLineQueueX( " lea %r, %s", ebx, paramvalue )
    .else

        SizeFromMemtype([esi].asym.mem_type, USE_EMPTY, [esi].asym.type)
        mov edi,opnd

        .if ebx < T_XMM0 && [edi].expr.kind != EXPR_CONST && eax < 4

            mov ecx,[edi].expr.base_reg
            .if !eax && [edi].expr.kind == EXPR_REG && !( [edi].expr.flags & E_INDIRECT ) && ecx

                .if [ecx].asm_tok.tokval == ebx

                    inc eax
                    .return
                .endif

                AddLineQueueX(" mov %r, %s", ebx, paramvalue)
                .return 1
            .endif
            mov ecx,T_MOVSX
            .if !( [esi].asym.mem_type & MT_SIGNED )
                mov ecx,T_MOVZX
            .endif
            AddLineQueueX(" %r %r, %s", ecx, ebx, paramvalue)
        .else
            mov ecx,[edi].expr.base_reg
            .if [edi].expr.kind == EXPR_REG && !( [edi].expr.flags & E_INDIRECT ) && ecx

                .if [ecx].asm_tok.tokval == ebx

                    inc eax
                    .return
                .endif
            .endif

            .if [edi].expr.kind == EXPR_CONST

                xor eax,eax
                .return .if index > 1 || ebx >= T_XMM0

                AddLineQueueX(" mov %r, %s", ebx, paramvalue)

            .elseif [edi].expr.kind == EXPR_FLOAT

                mov edx,param
                mov al,[edx].asym.mem_type

                .switch al
                .case MT_REAL4
                    mov eax,r0used
                    or  byte ptr [eax],R0_USED
                    AddLineQueueX( " mov %r, %s", T_EAX, paramvalue )
                    AddLineQueueX( " movd %r, %r", ebx, T_EAX )
                    .endc
                .case MT_REAL8
                    AddLineQueueX( " pushd %r (%s)", T_HIGH32, paramvalue )
                    AddLineQueueX( " pushd %r (%s)", T_LOW32, paramvalue )
                    AddLineQueueX( " movq %r, [esp]", ebx )
                    AddLineQueueX( " add esp, 8" )
                    .endc
                .case MT_REAL16
                    xor eax,eax
                    mov edx,paramvalue
                    .if ( [edi].expr.flags & E_NEGATIVE )
                        inc eax
                    .endif
                    mov ecx,[edi].expr.float_tok
                    .if ecx
                        mov edx,[ecx].asm_tok.string_ptr
                    .endif
                    atofloat( edi, edx, 16, eax, 0 )
                    lea esi,value
                    sprintf( esi, "0x%016I64X", [edi].expr.hlvalue )
                    AddLineQueueX( " pushd %r (%s)", T_HIGH32, esi )
                    AddLineQueueX( " pushd %r (%s)", T_LOW32, esi )
                    sprintf( esi, "0x%016I64X", [edi].expr.llvalue )
                    AddLineQueueX( " pushd %r (%s)", T_HIGH32, esi )
                    AddLineQueueX( " pushd %r (%s)", T_LOW32, esi )
                    AddLineQueueX( " movups %r, [esp]", ebx )
                    AddLineQueueX( " add esp, 16" )
                    .endc
                .default
                    AddLineQueueX( " movaps %r, %s", ebx, paramvalue )
                    .endc
                .endsw
            .else
                mov edx,param
                .if [edx].asym.mem_type == MT_REAL4
                    AddLineQueueX(" movss %r, %s", ebx, paramvalue)
                .elseif [edx].asym.mem_type == MT_REAL8
                    AddLineQueueX(" movsd %r, %s", ebx, paramvalue)
                .elseif eax == 16
                    AddLineQueueX(" movaps %r, %s", ebx, paramvalue)
                .else
                    .return 0
                .endif
            .endif
        .endif
        .if ebx == T_AX
            mov eax,r0used
            or byte ptr [eax],R0_USED
        .endif
    .endif
    mov eax,1
    ret

vc32_param endp

;-------------------------------------------------------------------------------
; FCT_WATCOMC
;-------------------------------------------------------------------------------

;; the watcomm fastcall variant is somewhat peculiar:
;; 16-bit:
;; - for BYTE/WORD arguments, there are 4 registers: AX,DX,BX,CX
;; - for DWORD arguments, there are 2 register pairs: DX::AX and CX::BX
;; - there is a "usage" flag for each register. Thus the prototype:
;;   sample proto :WORD, :DWORD, :WORD
;;   will assign AX to the first param, CX::BX to the second, and DX to
;;   the third!
;;

watc_fcstart proc pp: dsym_t, numparams:int_t, start:int_t,
        tokenarray: tok_t, value: ptr int_t
    mov eax,1
    ret

watc_fcstart endp


watc_param proc uses esi edi ebx pp, index, param, adr, opnd, paramvalue, r0used
;; get the register for parms 0 to 3,
;; using the watcom register parm passing conventions ( A D B C )

  local opc, qual, i, regs[64]:byte, reg[4]:string_t, p:string_t, psize
  local buffer[128]:byte, sreg

    mov ebx,param
    mov psize,SizeFromMemtype([ebx].asym.mem_type, USE_EMPTY, [ebx].asym.type)

    xor eax,eax
    .return .if [ebx].asym.state != SYM_TMACRO


    ;; the "name" might be a register pair

    lea esi,reg
    mov edi,[ebx].asym.string_ptr
    mov [esi],edi
    mov [esi+4],eax
    mov [esi+8],eax
    mov [esi+12],eax

    movzx eax,ModuleInfo.wordsize
    add fcscratch,eax

    .if strchr(edi, ':')

        strcpy(&regs, edi)
        movzx eax,ModuleInfo.wordsize
        add fcscratch,eax

        .for ebx=&regs, edi=0: edi < 4: edi++

            mov [esi+edi*4],ebx
            mov ebx,strchr(ebx, ':')
            .break .if !ebx
            mov byte ptr [ebx],0
            inc ebx
        .endf
    .endif

    mov edi,opnd
    .if adr
        mov edx,[edi].expr.sym
        mov esi,T_MOV
        mov ebx,T_OFFSET
        .if [edi].expr.kind == T_REG || [edx].asym.state == SYM_STACK
            mov esi,T_LEA
            mov ebx,T_NULL
        .endif

        ; v2.05: filling of segment part added

        xor eax,eax
        .if reg[1*4] != eax
            .if GetSegmentPart(opnd, &buffer, paramvalue)
                AddLineQueueX("%r %s, %r", T_MOV, reg, eax)
            .else
                AddLineQueueX("%r %s, %s", T_MOV, reg, &buffer)
            .endif
            mov eax,4
        .endif
        mov eax,reg[eax]
        AddLineQueueX("%r %s, %r %s", esi, eax, ebx, paramvalue)
        .return 1
    .endif

    .fors ebx = 3: ebx >= 0: ebx--

        mov ecx,reg[ebx*4]
        .if ecx

            .if [edi].expr.kind == EXPR_CONST
                .ifs ebx > 0
                    mov esi,T_LOWWORD
                .elseif !ebx && reg[4]
                    mov esi,T_HIGHWORD
                .else
                    mov esi,T_NULL
                .endif
                .if esi != T_NULL
                    AddLineQueueX("mov %s, %r (%s)", ecx, esi, paramvalue)
                .else
                    AddLineQueueX("mov %s, %s", ecx, paramvalue)
                .endif
            .elseif [edi].expr.kind == EXPR_REG
                AddLineQueueX("mov %s, %s", ecx, paramvalue)
            .else
                .if ebx == 0 && reg[4] == NULL
                    AddLineQueueX("mov %s, %s", ecx, paramvalue)
                .else
                    .if ModuleInfo.Ofssize
                        mov esi,T_DWORD
                    .else
                        mov esi,T_WORD
                    .endif
                    mov edi,ecx
                    mov cl,ModuleInfo.Ofssize
                    mov eax,2
                    shl eax,cl
                    lea ecx,[ebx+1]
                    mul ecx
                    mov ecx,psize
                    sub ecx,eax
                    AddLineQueueX("mov %s, %r %r %s[%u]", edi, esi, T_PTR, paramvalue, ecx)
                .endif
            .endif
        .endif
    .endf
    mov eax,1
    ret

watc_param endp

watc_fcend proc pp, numparams, value

    mov eax,pp
    mov edx,[eax].esym.procinfo
    mov eax,[edx].proc_info.parasize
    .if [edx].proc_info.flags & PROC_HAS_VARARG
        add eax,size_vararg
    .elseif fcscratch < eax
        sub eax,fcscratch
    .endif
    movzx edx,ModuleInfo.Ofssize
    mov ecx,stackreg[edx*4]
    AddLineQueueX(" add %r, %u", ecx, eax)
    ret

watc_fcend endp
endif

;-------------------------------------------------------------------------------
; FCT_WIN64
;-------------------------------------------------------------------------------

ms64_fcstart proc uses esi edi pp:dsym_t, numparams:int_t, start:int_t,
    tokenarray:tok_t, value:ptr int_t

    ; v2.29: reg::reg id to fcscratch

    mov edx,start
    shl edx,4
    add edx,tokenarray

    .for ( eax = 0 : [edx].asm_tok.token != T_FINAL : edx += 16 )

        .if ( [edx].asm_tok.token == T_REG && [edx+16].asm_tok.token == T_DBL_COLON )

            add edx,32
            inc eax
        .endif
    .endf

    .if eax

        dec eax
        mov fcscratch,eax
    .endif

    mov edx,pp
    mov eax,numparams
    mov esi,4
    mov edi,8
    .if [edx].esym.sym.langtype == LANG_VECTORCALL

        mov esi,6
        mov edi,16
    .endif

    ; v2.04: VARARG didn't work

    mov edx,[edx].esym.procinfo
    .if ( [edx].proc_info.flags & PROC_HAS_VARARG )

        .for ( ecx = start,
               ecx <<= 4,
               ecx += tokenarray,
               eax = 0 : [ecx].asm_tok.token != T_FINAL : ecx += 16 )

            .if ( [ecx].asm_tok.token == T_COMMA )

                inc eax
            .endif
        .endf
    .endif

    .if eax < esi
        mov eax,esi
    .elseif eax & 1
        inc eax
    .endif
    sub eax,esi
    shl eax,3
    xchg eax,edi
    mul esi
    add eax,edi
    mov edx,value
    mov [edx],eax

    .if ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP )

        mov edx,sym_ReservedStack
        .if eax > [edx].asym.value

            mov [edx].asym.value,eax
        .endif
    .else
        AddLineQueueX( " sub %r, %d", T_RSP, eax )
    .endif
    ;
    ; since Win64 fastcall doesn't push, it's a better/faster strategy to
    ; handle the arguments from left to right.
    ;
    ; v2.29 -- right to left
    ;
    xor eax,eax
    ret

ms64_fcstart endp


; parameter for Win64 FASTCALL.
; the first 4 parameters are hold in registers: rcx, rdx, r8, r9 for non-float arguments,
; xmm0, xmm1, xmm2, xmm3 for float arguments. If parameter size is > 8, the address of
; the argument is used instead of the value.

check_register_overwrite proc uses esi edi ebx opnd:ptr expr,
    regs_used:ptr byte, reg:ptr dword, destroyed:ptr byte, rmask:dword

    mov edi,opnd
    xor esi,esi

    .if [edi].expr.base_reg

        mov ebx,[edi].expr.base_reg
        mov ebx,[ebx].asm_tok.tokval
        mov eax,reg
        mov [eax],ebx

        .if GetValueSp(ebx) & OP_R

            movzx ecx,GetRegNo(ebx)
            mov eax,1
            shl eax,cl
            and eax,rmask
            .if eax

                lea ecx,[GetParmIndex(ecx)+RPAR_START]
                mov eax,1
                shl eax,cl
                mov ecx,regs_used
                .if [ecx] & al
                    mov esi,1
                .endif
            .else
                mov ecx,regs_used
                .if byte ptr [ecx] & R0_USED

                    .if GetValueSp(ebx) & OP_A || ebx == T_AH

                        mov esi,TRUE
                    .endif
                .endif
            .endif
        .endif
    .endif

    .if [edi].expr.kind == EXPR_ADDR && [edi].expr.idx_reg

        mov ebx,[edi].expr.idx_reg
        mov ebx,[ebx].asm_tok.tokval

        .if GetValueSp(ebx) & OP_R

            movzx ecx,GetRegNo(ebx)
            mov eax,1
            shl eax,cl
            and eax,rmask

            .if eax

                lea ecx,[GetParmIndex(ecx)+RPAR_START]
                mov eax,1
                shl eax,cl
                mov ecx,regs_used
                .if [ecx] & al

                    mov esi,TRUE
                .endif
            .else
                mov ecx,regs_used
                .if byte ptr [ecx] & R0_USED

                    .if GetValueSp(ebx) & OP_A || ebx == T_AH

                        mov esi,TRUE
                    .endif
                .endif
            .endif

        .endif
    .endif
    mov eax,destroyed
    mov [eax],esi
    ret

check_register_overwrite endp


GetPSize proc uses edi address:int_t, param:asym_t, opnd:expr_t

    mov edx,param
    mov edi,opnd

    ; v2.11: default size is 32-bit, not 64-bit

    .if [edx].asym.sint_flag & SINT_ISVARARG

        xor eax,eax
        .if address || [edi].expr.inst == T_OFFSET
            mov eax,8
        .elseif [edi].expr.kind == EXPR_REG
            .if !( [edi].expr.flags & E_INDIRECT )
                mov eax,[edi].expr.base_reg
                SizeFromRegister([eax].asm_tok.tokval)
            .else
                mov eax,8
            .endif
        .elseif [edi].expr.mem_type != MT_EMPTY
            SizeFromMemtype( [edi].expr.mem_type, USE64, [edi].expr.type )
        .endif
        .if eax < 4
            mov eax,4
        .endif
    .else
        SizeFromMemtype( [edx].asym.mem_type, USE64, [edx].asym.type )
    .endif
    ret

GetPSize endp


CheckXMM proc uses ebx reg:int_t, paramvalue:string_t, regs_used:ptr byte, param:dsym_t

  local buffer[64]:sbyte, _sign:byte

    ; v2.04: check if argument is the correct XMM register already

    .if [edi].expr.kind == EXPR_REG && !( [edi].expr.flags & E_INDIRECT )

        mov ecx,GetValueSp(reg)

        .if ecx & ( OP_XMM or OP_YMM or OP_ZMM )

            lea eax,[esi+T_XMM0]
            .if ecx & OP_YMM
                lea eax,[esi+T_YMM0]
            .elseif ecx & OP_ZMM
                lea eax,[esi+T_ZMM0]
            .endif

            .if eax != reg
                mov edx,param
                .if reg < T_XMM16 && ecx & OP_XMM
                    .if [edx].asym.mem_type == MT_REAL4
                        AddLineQueueX(" movss %r, %r", eax, reg)
                    .elseif [edx].asym.mem_type == MT_REAL8
                        AddLineQueueX(" movsd %r, %r", eax, reg)
                    .else
                        AddLineQueueX(" movaps %r, %r", eax, reg)
                    .endif
                .else
                    .if [edx].asym.mem_type == MT_REAL4
                        AddLineQueueX(" vmovss %r, %r, %r", eax, eax, reg)
                    .elseif [edx].asym.mem_type == MT_REAL8
                        AddLineQueueX(" vmovsd %r, %r, %r", eax, eax, reg)
                    .else
                        AddLineQueueX(" vmovaps %r, %r", eax, reg)
                    .endif
                .endif
            .endif
            .return 1
        .endif
    .endif

    lea ebx,[esi+T_XMM0]

    .if [edi].expr.kind == EXPR_FLOAT
        mov eax,regs_used
        or  byte ptr [eax],R0_USED
        mov edx,param
        .if [edx].asym.mem_type == MT_REAL2
            AddLineQueueX(" mov %r, %s", T_AX, paramvalue)
            AddLineQueueX(" movd %r, %r", ebx, T_EAX)
        .elseif [edx].asym.mem_type == MT_REAL4
            AddLineQueueX(" mov %r, %s", T_EAX, paramvalue)
            AddLineQueueX(" movd %r, %r", ebx, T_EAX)
        .elseif [edx].asym.mem_type == MT_REAL8
            AddLineQueueX(" mov %r, %r ptr %s", T_RAX, T_REAL8, paramvalue)
            AddLineQueueX(" movq %r, %r", ebx, T_RAX)
        .else
            xor ebx,ebx
            mov edx,paramvalue
            mov al,[edx]
            .if al == '+'
                inc edx
            .elseif al == '-'
                inc edx
                mov bl,0x80
            .endif
            __cvta_q(edi, edx, 0)
            or byte ptr [edi+15],bl
            .if dword ptr [edi].expr.llvalue[4]
                sprintf( &buffer, "0x%llX", [edi].expr.llvalue )
                AddLineQueueX( " mov rax, %s", &buffer )
                AddLineQueueX( " mov [rsp], rax" )
            .else
                AddLineQueueX( " mov qword ptr [rsp], 0x%x", dword ptr [edi].expr.llvalue )
            .endif
            .if dword ptr [edi].expr.hlvalue[4]
                sprintf( &buffer, "0x%llX", [edi].expr.hlvalue )
                AddLineQueueX( " mov rax, %s", &buffer )
                AddLineQueueX( " mov [rsp+8], rax" )
            .else
                AddLineQueueX( " mov qword ptr [rsp+8], 0x%x", dword ptr [edi].expr.hlvalue )
            .endif
            AddLineQueueX( " movaps %r, [rsp]", &[esi+T_XMM0] )
        .endif
    .else
        .if [edx].asym.mem_type == MT_REAL2
            mov eax,regs_used
            or  byte ptr [eax],R0_USED
            AddLineQueueX(" movzx %r, word ptr %s", T_EAX, paramvalue)
            AddLineQueueX(" movd %r, %r", ebx, T_EAX)
        .elseif [edx].asym.mem_type == MT_REAL4
            AddLineQueueX( " movd %r, %s", ebx, paramvalue )
        .elseif [edx].asym.mem_type == MT_REAL8
            AddLineQueueX( " movq %r, %s", ebx, paramvalue )
        .else
            AddLineQueueX( " movaps %r, %s", ebx, paramvalue )
        .endif
    .endif
    mov eax,1
    ret

CheckXMM endp


GetAccumulator proc psize:uint_t, regs:ptr

    mov ecx,psize
    shr ecx,1
    lea eax,[ecx*8+T_AL]
    cmp ecx,4
    sbb ecx,ecx
    and eax,ecx
    not ecx
    and ecx,T_RAX
    or  eax,ecx
    mov ecx,regs
    or  byte ptr [ecx],R0_USED
    ret

GetAccumulator endp

ms64_param proc uses esi edi ebx pp:dsym_t, index:int_t, param:dsym_t, address:int_t,
        opnd:ptr expr, paramvalue:string_t, regs_used:ptr byte

  local size        :uint_t,
        psize       :uint_t,
        reg         :int_t,
        reg_64      :int_t,
        i           :int_t,
        i32         :int_t,
        destroyed   :int_t,
        arg_offset  :uint_t,
        vector_call :byte

    mov destroyed,FALSE
    mov vector_call,FALSE
    mov edi,opnd

    mov eax,index
    shl eax,3
    mov arg_offset,eax

    mov ecx,pp
    .if [ecx].esym.sym.langtype == LANG_VECTORCALL

        mov vector_call,TRUE
        .if index < 6

            add eax,eax
            mov arg_offset,eax
        .endif
    .endif

    mov psize,GetPSize(address, param, edi)
    check_register_overwrite( edi, regs_used, &reg, &destroyed, REGPAR_WIN64 )

    .if destroyed

        asmerr(2133)
        mov ecx,regs_used
        mov byte ptr [ecx],0
    .endif

    mov edx,param
    mov esi,index
    add esi,fcscratch
    mov eax,psize

    .if esi >= 4 && ( address || eax > 8 )

        .if eax == 4

            mov ebx,T_EAX
        .else
            .if eax < 8

                asmerr(2114, &[esi+1])

            .elseif vector_call && esi < 6 && ( [edx].asym.mem_type & MT_FLOAT || \
                [edx].asym.mem_type == MT_YWORD || [edx].asym.mem_type == MT_OWORD )
                .return CheckXMM(reg, paramvalue, regs_used, param)
            .endif
            mov ebx,T_RAX
        .endif

        mov ecx,regs_used
        mov eax,R0_USED
        or [ecx],al

        AddLineQueueX(" lea %r, %s", ebx, paramvalue)
        AddLineQueueX(" mov [%r+%u], %r", T_RSP, arg_offset, ebx)
        .return 1
    .endif

    .if esi >= 4

        mov eax,[edi].expr.kind

        .if eax == EXPR_CONST || \
            ( eax == EXPR_ADDR && !( [edi].expr.flags & E_INDIRECT ) && \
            [edi].expr.mem_type == MT_EMPTY && [edi].expr.inst != T_OFFSET )


            ; v2.06: support 64-bit constants for params > 4

            xor ecx,ecx
            mov edx,dword ptr [edi].expr.value64[4]
            mov eax,dword ptr [edi].expr.value64
            .if edx == 0
                cmp eax,LONG_MAX
            .endif
            setg cl
            .if edx == -1
                cmp eax,LONG_MIN
            .endif
            setl ch

            .if psize == 8 && ( cl || ch )

                AddLineQueueX( " mov %r ptr [%r+%u], %r ( %s )",
                    T_DWORD, T_RSP, arg_offset, T_LOW32, paramvalue )
                AddLineQueueX( " mov %r ptr [%r+%u+4]], %r ( %s )",
                    T_DWORD, T_RSP, arg_offset, T_HIGH32, paramvalue )
            .else

                ; v2.11: no expansion if target type is a pointer and argument
                ; is an address part

                mov edx,param
                mov eax,[edi].expr.sym
                .if [edx].asym.mem_type == MT_PTR && \
                    [edi].expr.kind == EXPR_ADDR && [eax].asym.state != SYM_UNDEFINED

                    asmerr(2114, &[esi+1])
                .endif
                mov eax,psize
                .switch ( eax )
                .case 1: mov ecx,T_BYTE : .endc
                .case 2: mov ecx,T_WORD : .endc
                .case 4: mov ecx,T_DWORD: .endc
                .default
                    mov ecx,T_QWORD
                    .endc
                .endsw
                AddLineQueueX(" mov %r ptr [%r+%u], %s", ecx, T_RSP, arg_offset,
                        paramvalue)
            .endif

        .elseif [edi].expr.kind == EXPR_FLOAT

            mov edx,param
            .if [edx].asym.mem_type == MT_REAL8
                AddLineQueueX(" mov %r ptr [%r+%u+0], %r (%s)", T_DWORD, T_RSP,
                        arg_offset, T_LOW32, paramvalue)
                AddLineQueueX(" mov %r ptr [%r+%u+4], %r (%s)", T_DWORD, T_RSP,
                        arg_offset, T_HIGH32, paramvalue)
            .else
                AddLineQueueX(" mov %r ptr [%r+%u], %s", T_DWORD, T_RSP,
                        arg_offset, paramvalue)
            .endif

        .else ; it's a register or variable

            .if [edi].expr.kind == EXPR_REG && !( [edi].expr.flags & E_INDIRECT )

                .if vector_call && esi < 6 && ( [edx].asym.mem_type & MT_FLOAT || \
                        [edx].asym.mem_type == MT_YWORD || [edx].asym.mem_type == MT_OWORD )

                    .return CheckXMM(reg, paramvalue, regs_used, param)
                .endif

                mov size,SizeFromRegister(reg)
                mov ecx,psize

                .if eax == ecx

                    mov eax,reg
                .else

                    mov edx,param
                    .if eax > ecx || (eax < ecx && [edx].asym.mem_type == MT_PTR)

                        mov psize,eax
                        asmerr(2114, &[esi+1])
                    .endif

                    GetAccumulator( psize, regs_used )
                .endif
                mov i,eax

            .else

                .if [edi].expr.mem_type == MT_EMPTY

                    mov eax,4
                    .if [edi].expr.inst == T_OFFSET

                        mov eax,8
                    .endif
                .else
                    SizeFromMemtype( [edi].expr.mem_type, USE64, [edi].expr.type )
                .endif
                mov size,eax
                mov i,GetAccumulator( psize, regs_used )
            .endif

            ; v2.11: no expansion if target type is a pointer

            mov i32,get_register(i, 4)

            mov eax,size
            mov edx,param

            .if eax > psize || (eax < psize && [edx].asym.mem_type == MT_PTR)
                asmerr(2114, &[esi+1])
            .endif

            mov eax,size
            .if eax != psize

                .if eax == 4

                    .if IS_SIGNED([edi].expr.mem_type)
                        AddLineQueueX( " movsxd %r, %s", i, paramvalue )
                    .else
                        AddLineQueueX( " mov %r, %s", i, paramvalue )
                    .endif
                .else

                    mov ecx,T_MOVSX
                    .if !IS_SIGNED([edi].expr.mem_type)
                        mov ecx,T_MOVZX
                    .endif
                    AddLineQueueX(" %r %r, %s", ecx, i, paramvalue)
                .endif

            .elseif [edi].expr.kind != EXPR_REG || [edi].expr.flags & E_INDIRECT

                mov eax,paramvalue
                .if ( word ptr [eax] == "0" || \
                      ( [edi].expr.kind == EXPR_CONST && [edi].expr.value == 0 ) )

                    AddLineQueueX(" xor %r, %r", i32, i32)
                .elseif [edi].expr.kind == EXPR_CONST && [edi].expr.hvalue == 0

                    AddLineQueueX(" mov %r, %s", i32, eax)
                .else
                    AddLineQueueX(" mov %r, %s", i, eax)
                .endif
            .endif
            AddLineQueueX(" mov [%r+%u], %r", T_RSP, arg_offset, i)
        .endif
        .return 1
    .endif

    .if [edx].asym.mem_type & MT_FLOAT || [edx].asym.mem_type == MT_YWORD || \
        ( [edx].asym.mem_type == MT_OWORD && vector_call )

        .return CheckXMM(reg, paramvalue, regs_used, param)
    .endif

    mov ecx,[edi].expr.kind
    xor ebx,ebx

    .if ecx == EXPR_REG && !( [edi].expr.flags & E_INDIRECT )

        mov eax,[edi].expr.base_reg

        .if [eax+16].asm_tok.token == T_DBL_COLON

            ; case <reg>::<reg>

            mov ebx,[eax+32].asm_tok.tokval
            .if fcscratch
                dec fcscratch
            .endif
        .endif
    .endif

    mov reg_64,ebx
    mov eax,psize

    .if address || ( !ebx && eax > 8 ) ; psize > 8 shouldn't happen!

        .if eax >= 4
            .if eax > 4
                mov eax,4
            .else
                xor eax,eax
            .endif
            movzx eax,ms64_regs[esi+eax+2*4]
            AddLineQueueX(" lea %r, %s", eax, paramvalue)
        .else
            asmerr(2114, &[esi+1])
        .endif

        lea ecx,[esi+RPAR_START]
        mov eax,1
        shl eax,cl
        mov ecx,regs_used
        or [ecx],al
        .return 1
    .endif

    mov edx,[edi].expr.sym

    .switch
    .case ecx == EXPR_REG

        ; register argument

        mov eax,8
        .endc .if ( [edi].expr.flags & E_INDIRECT )
        mov eax,[edi].expr.base_reg
        mov eax,[eax].asm_tok.tokval
        mov reg,eax
        SizeFromRegister(eax)
        .endc
    .case ecx == EXPR_CONST
        .if [edi].expr.hvalue
            mov psize,8 ; extend const value to 64
        .endif
        ; drop
    .case ecx == EXPR_FLOAT
        mov eax,psize
        .endc
    .case [edi].expr.mem_type != MT_EMPTY
        SizeFromMemtype([edi].expr.mem_type, USE64, [edi].expr.type)
        .endc
    .case ecx == EXPR_ADDR && ( !edx || [edx].asym.state == SYM_UNDEFINED )
        mov eax,psize
        .endc
    .default
        mov eax,4
        .endc .if [edi].expr.inst != T_OFFSET
        mov eax,8
    .endsw
    mov size,eax

    mov edx,param
    mov ecx,paramvalue
    .if ( eax > psize && byte ptr [ecx] != '[' ) || \
        ( eax < psize && [edx].asym.mem_type == MT_PTR )

        asmerr( 2114, &[esi+1] )
    .endif

    xor ecx,ecx     ; added v2.29
    mov eax,psize
    .switch eax
    .case 1: xor eax,eax : .endc
    .case 2: mov eax,1   : .endc
    .case 3: inc ecx
    .case 4: mov eax,2   : .endc
    .case 5
    .case 6
    .case 7: inc ecx
    .default
        mov eax,3
        .endc
    .endsw
    movzx ebx,ms64_regs[esi+eax*4]
    mov i32,get_register(ebx, 4)

    ; optimization if the register holds the value already

    .if [edi].expr.kind == EXPR_REG && !([edi].expr.flags & E_INDIRECT)

        .if GetValueSp(reg) & OP_R

            ; case <reg>::<reg>

            .if reg_64
                .if ebx != reg_64
                    AddLineQueueX( " mov %r, %r", ebx, reg_64 )
                .endif
                movzx ebx,ms64_regs[esi+3*4+1]
                .if ebx != reg
                    AddLineQueueX( " mov %r, %r", ebx, reg )
                .endif
                .return 1
            .endif

            mov eax,1
            .return .if ebx == reg
            movzx ecx,GetRegNo(reg)
            mov eax,1
            shl eax,cl
            .if eax & REGPAR_WIN64
                lea ecx,[GetParmIndex(ecx)+RPAR_START]
                mov eax,1
                shl eax,cl
                mov ecx,regs_used
                .if [ecx] & al
                    asmerr(2133)
                .endif
            .endif
        .endif
    .endif

    ; v2.11: allow argument extension

    mov eax,size
    .if eax < psize
        .if eax == 4
            .if IS_SIGNED([edi].expr.mem_type)
                AddLineQueueX(" movsxd %r, %s", ebx, paramvalue)
            .else
                movzx eax,ms64_regs[esi+2*4]
                AddLineQueueX(" mov %r, %s", eax, paramvalue)
            .endif
        .else
            mov ecx,T_MOVSX
            .if !IS_SIGNED([edi].expr.mem_type)
                mov ecx,T_MOVZX
            .endif
            AddLineQueueX(" %r %r, %s", ecx, ebx, paramvalue)
        .endif
    .else

        mov eax,paramvalue

        .if ( word ptr [eax] == "0" || \
            ( [edi].expr.kind == EXPR_CONST && [edi].expr.value == 0 ) )

            AddLineQueueX(" xor %r, %r", i32, i32)

        .elseif [edi].expr.kind == EXPR_CONST && [edi].expr.hvalue == 0

            AddLineQueueX(" mov %r, %s", i32, eax)

        .elseif ecx && [edi].expr.kind == EXPR_ADDR ; added v2.29

            mov ecx,regs_used
            or  byte ptr [ecx],R0_USED

            .if size == 3

                mov ebx,i32
                lea ecx,[ebx-(T_R8D-T_R8B)]
                .if ebx >= T_EAX && ebx <= T_EDI
                    lea ecx,[ebx-(T_EAX-T_AL)]
                .endif
                AddLineQueueX(" mov %r, byte ptr %s[2]", ecx, eax)
                AddLineQueueX(" shl %r, 16", ebx)
                .if ebx >= T_EAX && ebx <= T_EDI
                    sub ebx,T_EAX-T_AX
                .else
                    sub ebx,T_R8D-T_R8W
                .endif
                AddLineQueueX(" mov %r, word ptr %s", ebx, paramvalue)
            .else
                AddLineQueueX(" mov %r, dword ptr %s", i32, eax)
                .if size == 5
                    AddLineQueueX(" mov al, byte ptr %s[4]", paramvalue)
                .elseif size == 6
                    AddLineQueueX(" mov ax, word ptr %s[4]", paramvalue)
                .else
                    AddLineQueueX(" mov al, byte ptr %s[6]", paramvalue)
                    AddLineQueueX(" shl eax,16")
                    AddLineQueueX(" mov ax, word ptr %s[4]", paramvalue)
                .endif
                AddLineQueueX(" shl rax,32")
                AddLineQueueX(" or  %r,rax", ebx)
            .endif
        .else
            AddLineQueueX(" mov %r, %s", ebx, eax)
        .endif
    .endif

    lea ecx,[esi+RPAR_START]
    mov eax,1
    shl eax,cl
    mov ecx,regs_used
    or [ecx],al
    mov eax,1
    ret

ms64_param endp

ms64_fcend proc pp, numparams, value
    ;
    ; use <value>, which has been set by ms64_fcstart()
    ;
    .if !( ModuleInfo.win64_flags & W64F_AUTOSTACKSP )

        mov eax,value
        .if ( ModuleInfo.epilogueflags )
            AddLineQueueX( " lea %r, [%r+%d]", T_RSP, T_RSP, eax )
        .else
            AddLineQueueX( " add %r, %d", T_RSP, eax )
        .endif
    .endif
    ret
ms64_fcend endp

;-------------------------------------------------------------------------------
; FCT_ELF64
;-------------------------------------------------------------------------------

.data

elf64_valptr dd 0

public elf64_regs
elf64_regs label byte
    db T_DIL, T_SIL, T_DL,  T_CL,  T_R8B, T_R9B
    db T_DI,  T_SI,  T_DX,  T_CX,  T_R8W, T_R9W
    db T_EDI, T_ESI, T_EDX, T_ECX, T_R8D, T_R9D
    db T_RDI, T_RSI, T_RDX, T_RCX, T_R8,  T_R9

elf64_param_index label byte
    ; AX CX DX BX SP BP SI DI R8 R9
    db 0, 3, 2, 0, 0, 0, 1, 0, 4, 5, 0, 0, 0, 0, 0, 0

.code

    assume esi:asym_t

elf64_pcheck proc public uses esi edi ebx pProc:dsym_t, paranode:dsym_t, used:ptr int_t

  local regname[32]:sbyte
  local reg:int_t

    mov ebx,used
    mov esi,paranode
    SizeFromMemtype([esi].mem_type, [esi].Ofssize, [esi].type)
    mov ecx,[ebx]
    mov dl,[esi].mem_type

    .switch
      .case ( [esi].sint_flag & SINT_ISVARARG )
        xor eax,eax
        mov [esi].string_ptr,eax
        .return

      .case ( dl & MT_FLOAT || dl == MT_YWORD )
        movzx ecx,ch
        inc byte ptr [ebx+1]
        .if ( ecx > 7 )
            mov [esi].regist[2],cx
            add ecx,(T_XMM8 - T_XMM7 - 1)
            mov [esi].regist[0],cx
            xor eax,eax
            mov [esi].string_ptr,eax
            .return
        .endif
        .if eax == 64
            lea eax,[ecx+T_ZMM0]
        .elseif eax == 32
            lea eax,[ecx+T_YMM0]
        .else
            lea eax,[ecx+T_XMM0]
        .endif
        .endc

      .case ( al > 16 )
        xor eax,eax
        mov [esi].string_ptr,eax
        .return

      .case ( al == 16 || dl == MT_OWORD )
        .if ( cl < 5 )
            movzx ecx,cl
            movzx eax,elf64_regs[ecx+3*6]
            add byte ptr [ebx],2
            .endc
        .endif

      .case ( cl > 5 )
        movzx ecx,cl
        mov [esi].regist[0],T_RAX
        mov [esi].regist[2],cx
        inc byte ptr [ebx]
        xor eax,eax
        mov [esi].string_ptr,eax
        .return

      .default
        movzx ecx,cl
        shr eax,1
        cmp eax,4
        cmc
        sbb eax,0
        lea edi,[eax*2]
        lea eax,[edi+eax*4]
        movzx eax,elf64_regs[ecx+eax]
        inc byte ptr [ebx]
        .endc
    .endsw

    lea edi,regname
    mov [esi].state,SYM_TMACRO
    mov [esi].regist[0],ax
    mov [esi].regist[2],cx
    GetResWName(eax, edi)
    mov [esi].string_ptr,LclAlloc(&[strlen(edi)+1])
    strcpy(eax, edi)
    mov eax,1
    ret

elf64_pcheck endp

    assume esi:nothing
    assume ebx:tok_t

elf64_fcstart proc uses esi edi ebx pp:dsym_t, numparams:int_t, start:int_t,
    tokenarray:tok_t, value:ptr int_t

    ; v2.28: xmm id to fcscratch

    mov edx,pp
    mov edx,[edx].esym.procinfo
    xor eax,eax
    xor esi,esi

    .if [edx].proc_info.flags & PROC_HAS_VARARG

        mov ebx,start
        shl ebx,4
        add ebx,tokenarray

        .for ( : [ebx].token != T_FINAL : ebx += 16 )

            .if [ebx].token == T_REG

                .if GetValueSp([ebx].tokval) & OP_XMM

                    inc fcscratch
                .endif

            .elseif [ebx].asm_tok.token == T_ID

                .if SymFind([ebx].string_ptr)

                    .if [eax].asym.mem_type & MT_FLOAT

                        inc fcscratch
                    .endif
                .endif
            .elseif [ebx].asm_tok.token == T_COMMA

                inc esi ; added v2.31
            .endif
        .endf
        mov eax,fcscratch
        sub esi,eax

    .else

        .for ( edi = [edx].proc_info.paralist : edi : edi = [edi].esym.prev )
            .if [edi].asym.mem_type & MT_FLOAT || [edi].asym.mem_type == MT_YWORD
                inc eax
            .else
                inc esi
            .endif
        .endf
    .endif

    mov edx,value
    xor ecx,ecx
    .if esi > 6
        lea ecx,[ecx+esi-6]
    .endif
    .if eax > 8
        lea ecx,[ecx+eax-8]
        mov eax,8
    .endif
    .if ecx & 1 && ModuleInfo.win64_flags & W64F_AUTOSTACKSP
        mov elf64_valptr,edx
    .endif
    mov [edx],ecx
    ret

elf64_fcstart endp

elf64_const proc reg:uint_t, pos:uint_t, val:qword, paramvalue:string_t, _negative:uint_t

    .if dword ptr val[4] == 0
        mov eax,get_register(reg, 4)
        .if dword ptr val == 0
            .if _negative
                AddLineQueueX(" mov %r, -1", reg)
            .else
                AddLineQueueX(" xor %r, %r", eax, eax)
            .endif
        .else
            AddLineQueueX(" mov %r, %s", eax, paramvalue)
        .endif
    .else
        AddLineQueueX(" mov %r, %r %s", reg, pos, paramvalue)
    .endif
    ret

elf64_const endp

; parameter for elf64 SYSCALL.
; the first 6 parameters are hold in registers: rdi, rsi, rdx, rcx, r8, r9
; for non-float arguments, xmm0..xmm31 for float arguments.

    assume edx:asym_t
    assume edi:expr_t

elf64_param proc uses esi edi ebx pp:dsym_t, index:int_t, param:dsym_t,
        address:int_t, opnd:ptr expr, paramvalue:string_t, regs_used:ptr byte

  local size        :uint_t,
        psize       :uint_t,
        reg         :int_t,
        i           :int_t,
        i32         :int_t,
        destroyed   :int_t,     ; added v2.31
        stack       :int_t,     ; added v2.31
        sym         :asym_t     ; added v2.31

    mov stack,FALSE
    mov destroyed,FALSE

    mov eax,TRUE
    mov ecx,paramvalue
    .return .if [ecx] == ah

    mov edi,opnd

    .if elf64_valptr ; if arg count is odd..

        ; last argument: align 16

        mov edx,elf64_valptr
        mov elf64_valptr,0
        inc dword ptr [edx] ; value++

        AddLineQueueX(" sub %r,8", T_RSP)
    .endif

    mov psize,GetPSize(address, param, edi)
    mov edx,param

    .if ( [edx].sint_flag & SINT_ISVARARG )

        .if ( eax == 16 || [edi].mem_type & MT_FLOAT )
            dec fcscratch
            mov esi,fcscratch
            lea ebx,[esi+T_XMM0]
        .else
            mov esi,index
            sub esi,fcscratch
            .if esi < 6
                shr eax,1
                cmp eax,4
                cmc
                sbb eax,0
                lea ebx,[eax*2]
                lea eax,[ebx+eax*4]
                movzx ebx,elf64_regs[esi+eax]
            .else
                inc stack
            .endif
        .endif
    .else
        movzx ebx,[edx].regist[0]
        movzx esi,[edx].regist[2]
    .endif

    movzx eax,[edx].mem_type
    .if  ( eax == MT_EMPTY && ( [edx].sint_flag & SINT_ISVARARG ) && \
           [edi].kind == EXPR_ADDR && [edi].mem_type & MT_FLOAT )

        .if SymFind(paramvalue)
            mov edx,eax
        .else
            mov edx,param
        .endif
        movzx eax,[edx].mem_type
    .endif

    .if ( !( eax & MT_FLOAT || eax == MT_YWORD ) && esi >= 6 )

        .return 0 .if !stack
        mov ebx,T_RAX
    .endif

    assume edx:nothing
    mov sym,edx

    .if eax & MT_FLOAT || eax == MT_YWORD
        mov eax,[edi].base_reg
        .if eax
            mov eax,[eax].asm_tok.tokval
        .endif
        .if esi < 8
            .return CheckXMM(eax, paramvalue, regs_used, edx)
        .else
            inc stack
        .endif
    .endif

    mov i32,get_register(ebx, 4)

    .repeat

        .if address

            .if SizeFromRegister(ebx) == 8

                AddLineQueueX( " lea %r, %s", ebx, paramvalue )
                .if stack

                    AddLineQueueX( " push %r", ebx )
                    mov ecx,regs_used
                    or  byte ptr [ecx],R0_USED
                    .return 1
                .endif
            .else
                mov eax,index
                inc eax
                asmerr(2114, eax)
            .endif
            .break
        .endif

        mov edx,[edi].sym
        mov ecx,[edi].kind

        .if ecx == EXPR_REG ; register argument

            mov eax,8
            .if !( [edi].flags & E_INDIRECT )
                mov eax,[edi].base_reg
                mov eax,[eax].asm_tok.tokval
                mov reg,eax
                SizeFromRegister(eax)
            .endif

        .elseif ecx == EXPR_CONST

            mov eax,[edi].hvalue
            .if eax && eax != -1
                mov psize,8 ; extend const value to 64
            .endif
            mov eax,psize

        .elseif ecx == EXPR_FLOAT

            mov eax,psize

        .elseif [edi].mem_type != MT_EMPTY

            SizeFromMemtype([edi].mem_type, USE64, [edi].type)

        .elseif ecx == EXPR_ADDR && [edx].asym.state == SYM_UNDEFINED

            mov eax,psize

        .else
            mov eax,4
            .if [edi].inst == T_OFFSET
                mov eax,8
            .endif
        .endif
        mov size,eax

        mov edx,param

        .if eax == 16 && stack && [edi].kind == EXPR_REG

            AddLineQueueX( " lea rsp,[rsp-8]" )
            .if reg < T_XMM16
                mov edx,param
                .if [edx].asym.mem_type == MT_REAL8
                    AddLineQueueX(" movsd [rsp], %s", paramvalue )
                .else
                    AddLineQueueX(" movss [rsp], %s", paramvalue )
                .endif
            .else
                AddLineQueueX( " vmovq [rsp], %s", paramvalue )
            .endif
            .return 1

        .elseif ( eax > psize || ( eax < psize && [edx].asym.mem_type == MT_PTR ) )

            mov eax,index
            inc eax
            asmerr(2114, eax)
        .endif

        ; optimization if the register holds the value already

        .if ( [edi].kind == EXPR_REG && !( [edi].flags & E_INDIRECT ) )

            .if GetValueSp(reg) & OP_XMM

                mov eax,[edi].base_reg
                mov eax,[eax].asm_tok.tokval
                .return CheckXMM(eax, paramvalue, regs_used, param)
            .endif

            .if GetValueSp(reg) & OP_R

                ; added v2.31.03

                movzx ecx,GetRegNo(reg)
                mov eax,1
                shl eax,cl
                and eax,REGPAR_ELF64 ; regs 1, 2, 6, 7, 8 and 9
                .if eax
                    movzx ecx,elf64_param_index[ecx]
                    lea ecx,[ecx+ELF64_START]
                    mov eax,1
                    shl eax,cl
                    mov ecx,regs_used
                    .if [ecx] & al
                        mov destroyed,TRUE
                    .endif
                .else
                    mov ecx,regs_used
                    .if byte ptr [ecx] & R0_USED
                        .if GetValueSp(reg) & OP_A || reg == T_AH
                            mov destroyed,TRUE
                        .endif
                    .endif
                .endif
                .if destroyed
                    asmerr(2133)
                    mov ecx,regs_used
                    mov byte ptr [ecx],0
                .endif

                mov eax,[edi].base_reg

                ; case <reg>::<reg>

                .if psize == 16 && size == 8 && [eax+16].asm_tok.token == T_DBL_COLON

                    mov ecx,[eax+32].asm_tok.tokval
                    .if ebx != ecx
                        AddLineQueueX(" mov %r, %r", ebx, ecx)
                    .endif
                    movzx ebx,elf64_regs[esi+3*6+1]
                    .if ebx != reg
                        AddLineQueueX(" mov %r, %r", ebx, reg)
                    .endif
                    .break
                .endif

                .if stack

                    AddLineQueueX(" push %r", get_register(reg, 8))
                    .return 1
                .endif

                .return 1 .if ebx == reg

                .if [edi].mem_type == MT_EMPTY

                    ; get type info (signed)

                    mov ecx,param
                    mov al,[ecx].asym.mem_type
                    mov [edi].mem_type,al
                .endif

                movzx ecx,GetRegNo(reg)
                mov eax,1
                shl eax,cl
                .if eax & REGPAR_ELF64

                    ; convert register number to param number:

                    and ecx,0xF
                    movzx eax,elf64_param_index[ecx]

                    lea ecx,[eax+ELF64_START]
                    mov eax,1
                    shl eax,cl
                    mov ecx,regs_used
                    .if [ecx] & al

                        asmerr(2133)
                    .endif
                .endif
            .endif
        .endif

        ; allow argument extension

        mov eax,size
        .if eax < psize

            .if eax == 4

                .if IS_SIGNED([edi].mem_type)

                    AddLineQueueX(" movsxd %r, %s", ebx, paramvalue)
                .else
                    AddLineQueueX(" mov %r, %s", i32, paramvalue)
                .endif
            .else
                mov ecx,T_MOVSX
                .if !( IS_SIGNED([edi].mem_type) )
                    mov ecx,T_MOVZX
                .endif
                AddLineQueueX(" %r %r, %s", ecx, i32, paramvalue)
            .endif

            .if stack

                AddLineQueueX(" push %r", ebx)
                mov ecx,regs_used
                or  byte ptr [ecx],R0_USED
                .return 1
            .endif
            .break
        .endif

        mov ecx,paramvalue
        .if stack
            .if [edi].expr.kind == EXPR_FLOAT
                mov eax,regs_used
                or  byte ptr [eax],R0_USED
                mov eax,T_RAX
                mov edx,param
                .if [edx].asym.mem_type == MT_REAL2
                    mov eax,T_AX
                .elseif [edx].asym.mem_type == MT_REAL4
                    mov eax,T_EAX
                .endif
                AddLineQueueX(" mov %r, %s", eax, ecx)
                AddLineQueueX(" push %r", T_RAX)
            .else
                AddLineQueueX(" push %s", ecx)
            .endif
            .return 1
        .endif

        .if ( word ptr [ecx] == "0" || ( [edi].kind == EXPR_CONST && [edi].value == 0 ) )

            AddLineQueueX(" xor %r, %r", i32, i32)
            .break .if size != 16

            mov ecx,dword ptr [edi].hlvalue
            or  ecx,dword ptr [edi].hlvalue[4]
            .ifz
                ; -0
                movzx ebx,elf64_regs[esi+2*6+1]
                AddLineQueueX(" xor %r, %r", ebx, ebx)
                .break
            .endif
            movzx ebx,elf64_regs[esi+3*6+1]
            movzx eax,[edi].flags
            and eax,E_NEGATIVE
            elf64_const(ebx, T_HIGH64, [edi].hlvalue, paramvalue, eax)
            .break
        .endif

        .if ( [edi].kind == EXPR_CONST && [edi].hvalue == 0 )

            AddLineQueueX(" mov %r, %s", i32, ecx)
            .break .if size != 16

            movzx ebx,elf64_regs[esi+3*6+1]
            movzx eax,[edi].flags
            and eax,E_NEGATIVE
            elf64_const(ebx, T_HIGH64, [edi].hlvalue, paramvalue, eax)
            .break
        .endif

        .if eax != 16

            AddLineQueueX(" mov %r, %s", ebx, ecx)
            .break
        .endif

        mov eax,ebx
        movzx ebx,elf64_regs[esi+3*6+1]

        .if [edi].kind == EXPR_CONST

            elf64_const(eax, T_LOW64, [edi].llvalue, paramvalue, 0)
            movzx eax,[edi].flags
            and eax,E_NEGATIVE
            elf64_const(ebx, T_HIGH64, [edi].hlvalue, paramvalue, eax)
            .break
        .endif

        AddLineQueueX(" mov %r, qword ptr %s", eax, ecx)
        AddLineQueueX(" mov %r, qword ptr %s[8]", ebx, paramvalue)
    .until 1

    .if esi < 6
        lea ecx,[esi+ELF64_START]
        mov eax,1
        shl eax,cl
        mov ecx,regs_used
        or [ecx],al
    .endif
    mov eax,1
    ret

elf64_param endp

elf64_fcend proc pp, numparams, value

    ; use <value>, which has been set by elf64_fcstart()

    mov ecx,value
    .if ecx
        AddLineQueueX(" add rsp, %u*8", ecx)
    .endif
    ret
elf64_fcend endp

    END
