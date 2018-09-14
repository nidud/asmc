include string.inc
include limits.inc
include malloc.inc
include stdio.inc
include quadmath.inc
include asmc.inc
include token.inc

public  fastcall_tab

GetGroup        proto :ptr asym
ifndef __ASMC64__
GetSegmentPart  proto :ptr expr, :LPSTR, :LPSTR
endif
search_assume   proto :ptr asym, :SINT, :SINT

invoke_conv     struc
invokestart     dd ? ; dsym *, int, int, asm_tok *, int *
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

externdef       sym_ReservedStack:LPASYM    ; max stack space required by INVOKE
externdef       size_vararg:SINT        ; size of :VARARG arguments

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

stackreg label byte
    db T_SP, T_ESP, T_RSP

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
GetSegmentPart proc uses esi edi ebx opnd:ptr expr, buffer:LPSTR, fullparam:LPSTR

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
        mov ecx,[ebx].nsym.seginfo

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
                strcpy(buffer, [eax].asym._name)
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

ms32_fcstart proc pp:ptr nsym, numparams:SINT, start:SINT,
    tokenarray:ptr asm_tok, value:ptr SINT

    .repeat
        .if GetSymOfssize(pp) == USE16

            xor eax,eax
            .break
        .endif

        .for eax=pp, eax=[eax].nsym.procinfo,
             eax=[eax].proc_info.paralist: eax: eax=[eax].nsym.nextparam

            .if [eax].asym.state == SYM_TMACRO

                inc fcscratch
            .endif
        .endf
        mov eax,1
    .until 1
    ret

ms32_fcstart endp

ms32_param proc uses esi edi ebx pp:ptr nsym, index:SINT, param:ptr nsym, adr:SINT,
    opnd:ptr expr, paramvalue:LPSTR, r0used:ptr byte

    local z

    mov esi,param

    .repeat

        .if [esi].asym.state != SYM_TMACRO

            xor eax,eax
            .break
        .endif

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

            mov z,SizeFromMemtype([esi].asym.mem_type, USE_EMPTY, [esi].asym._type)
            mov edi,opnd

            .if [edi].expr.kind != EXPR_CONST && z < SizeFromRegister(ebx)

                mov eax,ModuleInfo.curr_cpu
                and eax,P_CPU_MASK
                .if eax >= P_386

                    mov eax,@CStr("movzx")
                    .if [esi].asym.mem_type & MT_SIGNED
                        mov eax,@CStr("movsx")
                    .endif
                    AddLineQueueX(" %s %r, %s", eax, ebx, paramvalue)
                .else
                    imul eax,ebx,sizeof(special_item)
                    movzx edi,SpecialTable[eax].bytval
                    AddLineQueueX(" mov %r, %s", &[edi+T_AL], paramvalue)
                    AddLineQueueX(" mov %r, 0",  &[edi+T_AH])
                .endif
            .else
                mov eax,[edi].expr.base_reg
                .if [edi].expr.kind == EXPR_REG && !([edi].expr.flags & EXF_INDIRECT) && eax
                    .if [eax].asm_tok.tokval == ebx
                        mov eax,1
                        .break
                    .endif
                .endif
                AddLineQueueX(" mov %r, %s", ebx, paramvalue)
            .endif
            .if ebx == T_AX
                mov eax,r0used
                or byte ptr [eax],R0_USED
            .endif
        .endif
        mov eax,1
    .until 1
    ret
ms32_param endp

ms32_fcend proc pp, numparams, value
    ret
ms32_fcend endp

;-------------------------------------------------------------------------------
; FCT_VEC32
;-------------------------------------------------------------------------------

vc32_fcstart proc pp:ptr nsym, numparams:SINT, start:SINT,
    tokenarray:ptr asm_tok, value:ptr SINT

    .repeat
        .for eax=pp, eax=[eax].nsym.procinfo,
             eax=[eax].proc_info.paralist: eax: eax=[eax].nsym.nextparam

            .if [eax].asym.state == SYM_TMACRO || \
                ( [eax].asym.state == SYM_STACK && [eax].asym.total_size <= 16 )

                inc fcscratch
            .endif
        .endf
        mov eax,1
    .until 1
    ret

vc32_fcstart endp

vc32_param proc uses esi edi ebx pp:ptr nsym, index:SINT, param:ptr nsym, adr:SINT,
    opnd:ptr expr, paramvalue:LPSTR, r0used:ptr byte

    local z

    mov esi,param
    xor eax,eax

    .repeat

        mov cl,[esi].asym.state
        .break .if !( cl == SYM_TMACRO || cl == SYM_STACK || !fcscratch )
        .break .if ( cl == SYM_STACK && [esi].asym.total_size > 16 )

        dec fcscratch
        mov edx,fcscratch
        .if cl == SYM_STACK || edx > 1 || [esi].asym.mem_type & MT_FLOAT
            .break .if edx > 5
            lea ebx,[edx+T_XMM0]
        .else
            .break .if edx > 1
            movzx ebx,ms32_regs[edx]
        .endif

        .if adr

            AddLineQueueX( " lea %r, %s", ebx, paramvalue )
        .else

            SizeFromMemtype([esi].asym.mem_type, USE_EMPTY, [esi].asym._type)
            mov edi,opnd

            .if ebx < T_XMM0 && [edi].expr.kind != EXPR_CONST && eax < 4

                mov ecx,[edi].expr.base_reg
                .if !eax && [edi].expr.kind == EXPR_REG && !( [edi].expr.flags & EXF_INDIRECT ) && ecx

                    .if [ecx].asm_tok.tokval == ebx

                        inc eax
                        .break
                    .endif

                    AddLineQueueX(" mov %r, %s", ebx, paramvalue)
                    mov eax,1
                    .break
                .endif

                mov eax,@CStr("movzx")
                .if [esi].asym.mem_type & MT_SIGNED
                    mov eax,@CStr("movsx")
                .endif
                AddLineQueueX(" %s %r, %s", eax, ebx, paramvalue)
            .else
                mov ecx,[edi].expr.base_reg
                .if [edi].expr.kind == EXPR_REG && !( [edi].expr.flags & EXF_INDIRECT ) && ecx

                    .if [ecx].asm_tok.tokval == ebx

                        inc eax
                        .break
                    .endif
                .endif

                .if [edi].expr.kind == EXPR_CONST

                    xor eax,eax
                    .break .if index > 1 || ebx >= T_XMM0

                    AddLineQueueX(" mov %r, %s", ebx, paramvalue)

                .elseif [edi].expr.kind == EXPR_FLOAT

                    mov edx,param
                    .if [edx].asym.mem_type == MT_REAL4
                        mov eax,r0used
                        or  byte ptr [eax],R0_USED
                        AddLineQueueX( " mov %r, %s", T_EAX, paramvalue )
                        AddLineQueueX( " movd %r, %r", ebx, T_EAX )
                    .elseif [edx].asym.mem_type == MT_REAL8
                        AddLineQueueX( " pushd %r (%s)", T_HIGH32, paramvalue )
                        AddLineQueueX( " pushd %r (%s)", T_LOW32, paramvalue )
                        AddLineQueueX( " movq %r, [esp]", ebx )
                        AddLineQueueX( " add esp, 8" )
                    .else
                        AddLineQueueX( " movaps %r, %s", ebx, paramvalue )
                    .endif
                .else
                    mov edx,param
                    .if [edx].asym.mem_type == MT_REAL4
                        AddLineQueueX(" movss %r, %s", ebx, paramvalue)
                    .elseif [edx].asym.mem_type == MT_REAL8
                        AddLineQueueX(" movsd %r, %s", ebx, paramvalue)
                    .elseif eax == 16
                        AddLineQueueX(" movaps %r, %s", ebx, paramvalue)
                    .else
                        xor eax,eax
                        .break
                    .endif
                .endif
            .endif
            .if ebx == T_AX
                mov eax,r0used
                or byte ptr [eax],R0_USED
            .endif
        .endif
        mov eax,1
    .until 1
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

watc_fcstart proc pp: ptr nsym, numparams:SINT, start:SINT,
        tokenarray: ptr asm_tok, value: ptr SINT
    mov eax,1
    ret
watc_fcstart endp

watc_param proc uses esi edi ebx pp, index, param, adr, opnd, paramvalue, r0used
;; get the register for parms 0 to 3,
;; using the watcom register parm passing conventions ( A D B C )
;;
    local opc, qual, i, regs[64]:byte, reg[4]:LPSTR, p:LPSTR, psize
    local buffer[128]:byte, sreg

    mov ebx,param
    mov psize,SizeFromMemtype([ebx].asym.mem_type, USE_EMPTY, [ebx].asym._type)

    xor eax,eax

    .repeat

        .break .if [ebx].asym.state != SYM_TMACRO


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
            ;
            ; v2.05: filling of segment part added
            ;
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
            mov eax,1
            .break
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
    .until 1
toend:
    ret
watc_param endp

watc_fcend proc pp, numparams, value

    mov eax,pp
    mov edx,[eax].nsym.procinfo
    mov eax,[edx].proc_info.parasize
    .if [edx].proc_info.flags & PINF_HAS_VARARG
        add eax,size_vararg
    .elseif fcscratch < eax
        sub eax,fcscratch
    .endif
    movzx edx,ModuleInfo.Ofssize
    movzx ecx,stackreg[edx]
    AddLineQueueX(" add %r, %u", ecx, eax)
    ret

watc_fcend endp
endif

;-------------------------------------------------------------------------------
; FCT_WIN64
;-------------------------------------------------------------------------------

ms64_fcstart proc uses esi edi pp:ptr nsym, numparams:SINT, start:SINT,
    tokenarray:ptr asm_tok, value:ptr SINT

    mov edx,pp
    mov eax,numparams
    mov esi,4
    mov edi,8
    .if [edx].nsym.sym.langtype == LANG_VECTORCALL

        mov esi,6
        mov edi,16
    .endif

    ; v2.04: VARARG didn't work

    mov edx,[edx].nsym.procinfo
    .if [edx].proc_info.flags & PINF_HAS_VARARG

        mov ecx,start
        shl ecx,4
        add ecx,tokenarray
        .for eax=0: [ecx].asm_tok.token != T_FINAL: ecx+=16
            .if [ecx].asm_tok.token == T_COMMA

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

    .if ModuleInfo.win64_flags & W64F_AUTOSTACKSP

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
    xor eax,eax
    ret
ms64_fcstart endp

;
; parameter for Win64 FASTCALL.
; the first 4 parameters are hold in registers: rcx, rdx, r8, r9 for non-float arguments,
; xmm0, xmm1, xmm2, xmm3 for float arguments. If parameter size is > 8, the address of
; the argument is used instead of the value.
;

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

    .if [edi].expr.idx_reg

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


GetPSize proc adr
    ;
    ; v2.11: default size is 32-bit, not 64-bit
    ;
    .if [edx].asym.sint_flag & SINT_ISVARARG

        xor eax,eax
        .if adr || [edi].expr._instr == T_OFFSET
            mov eax,8
        .elseif [edi].expr.kind == EXPR_REG
            .if !( [edi].expr.flags & EXF_INDIRECT )
                mov eax,[edi].expr.base_reg
                SizeFromRegister([eax].asm_tok.tokval)
            .else
                mov eax,8
            .endif
        .elseif [edi].expr.mem_type != MT_EMPTY
            SizeFromMemtype( [edi].expr.mem_type, USE64, [edi].expr._type )
        .endif
        .if eax < 4
            mov eax,4
        .endif
    .else
        SizeFromMemtype( [edx].asym.mem_type, USE64, [edx].asym._type )
    .endif
    ret
GetPSize endp

CheckXMM proc uses ebx reg:SINT, paramvalue:LPSTR, regs_used:ptr byte, param:ptr nsym

    local buffer[64]:sbyte, _sign:byte
    ;
    ; v2.04: check if argument is the correct XMM register already
    ;
    .repeat

        .if [edi].expr.kind == EXPR_REG && !( [edi].expr.flags & EXF_INDIRECT )

            .if GetValueSp( reg ) & OP_XMM

                lea eax,[esi+T_XMM0]
                .if eax != reg

                    mov edx,param
                    .if reg >= T_XMM0

                        .if [edx].asym.mem_type == MT_REAL4
                            AddLineQueueX(" movss %r, %r", eax, reg)
                        .elseif [edx].asym.mem_type == MT_REAL8
                            AddLineQueueX(" movsd %r, %r", eax, reg)
                        .else
                            AddLineQueueX(" movaps %r, %r", eax, reg)
                        .endif
                    .else
                        .if [edx].asym.mem_type == MT_REAL4
                            AddLineQueueX(" movd %r, %s", eax, paramvalue)
                        .elseif [edx].asym.mem_type == MT_REAL8
                            AddLineQueueX(" movq %r, %s", eax, paramvalue)
                        .else
                            AddLineQueueX(" movaps %r, %s", eax, paramvalue)
                        .endif
                    .endif
                .endif
                .break
            .endif
        .endif

        .if [edi].expr.kind == EXPR_FLOAT

            mov eax,regs_used
            or  byte ptr [eax],R0_USED
            mov edx,param
            .if [edx].asym.mem_type == MT_REAL4
                AddLineQueueX(" mov %r, %s", T_EAX, paramvalue)
                AddLineQueueX(" movd %r, %r", &[esi+T_XMM0], T_EAX)
            .elseif [edx].asym.mem_type == MT_REAL8
                AddLineQueueX(" mov %r, %r ptr %s", T_RAX, T_REAL8, paramvalue)
                AddLineQueueX(" movq %r, %r", &[esi+T_XMM0], T_RAX)
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
                atoquad(edi, edx, 0)
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
            .if [edx].asym.mem_type == MT_REAL4
                AddLineQueueX( " movd %r, %s", &[esi+T_XMM0], paramvalue )
            .elseif [edx].asym.mem_type == MT_REAL8
                AddLineQueueX( " movq %r, %s", &[esi+T_XMM0], paramvalue )
            .else
                AddLineQueueX( " movaps %r, %s", &[esi+T_XMM0], paramvalue )
            .endif

        .endif
    .until 1
    ret
CheckXMM endp

ms64_param proc uses esi edi ebx pp:ptr nsym, index:SINT, param:ptr nsym, adr:SINT,
    opnd:ptr expr, paramvalue:LPSTR, regs_used:ptr byte

    local z, psize, reg, i, i32, destroyed, arg_offset, vector_call:byte

    mov destroyed,FALSE
    mov vector_call,FALSE
    mov edx,param
    mov edi,opnd
    mov eax,index
    shl eax,3
    mov arg_offset,eax
    mov ecx,pp
    .if [ecx].nsym.sym.langtype == LANG_VECTORCALL
        mov vector_call,TRUE
        .if index < 6
            add eax,eax
            mov arg_offset,eax
        .endif
    .endif

    .repeat

        mov psize,GetPSize(adr)
        check_register_overwrite( edi, regs_used, &reg, &destroyed, REGPAR_WIN64 )

        .if destroyed

            asmerr(2133)
            mov ecx,regs_used
            mov byte ptr [ecx],0
        .endif

        mov edx,param
        mov esi,index

        .if esi >= 4

            mov eax,psize
            .if adr || eax > 8

                .if eax == 4

                    mov ebx,T_EAX
                .else
                    .if eax < 8

                        asmerr(2114, &[esi+1])
                    .else
                        .if vector_call && esi < 6 && \
                            ( [edx].asym.mem_type == MT_REAL16 || [edx].asym.mem_type == MT_OWORD )

                            jmp vector_0_5
                        .endif
                    .endif
                    mov ebx,T_RAX
                .endif
                mov ecx,regs_used
                mov eax,R0_USED
                or [ecx],al

                AddLineQueueX(" lea %r, %s", ebx, paramvalue)
                AddLineQueueX(" mov [%r+%u], %r", T_RSP, arg_offset, ebx)
                mov eax,1
                .break
            .endif

            mov eax,[edi].expr.kind
            .if eax == EXPR_CONST || \
              ( eax == EXPR_ADDR && !( [edi].expr.flags & EXF_INDIRECT ) && \
                [edi].expr.mem_type == MT_EMPTY && [edi].expr._instr != T_OFFSET )

                ;
                ; v2.06: support 64-bit constants for params > 4
                ;
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
                    ;
                    ; v2.11: no expansion if target type is a pointer and argument
                    ; is an address part
                    ;
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
                    AddLineQueueX(" mov %r ptr [%r+%u], %s", ecx, T_RSP, arg_offset, paramvalue)
                .endif
            .elseif [edi].expr.kind == EXPR_FLOAT

                mov edx,param
                .if [edx].asym.mem_type == MT_REAL8
                    AddLineQueueX(" mov %r ptr [%r+%u+0], %r (%s)", T_DWORD, T_RSP, arg_offset, T_LOW32, paramvalue)
                    AddLineQueueX(" mov %r ptr [%r+%u+4], %r (%s)", T_DWORD, T_RSP, arg_offset, T_HIGH32, paramvalue)
                .else
                    AddLineQueueX(" mov %r ptr [%r+%u], %s", T_DWORD, T_RSP, arg_offset, paramvalue)
                .endif

            .else ; it's a register or variable

                .if [edi].expr.kind == EXPR_REG && !( [edi].expr.flags & EXF_INDIRECT )

                    .if vector_call && esi < 6 && ( [edx].asym.mem_type & MT_FLOAT || \
                        [edx].asym.mem_type == MT_OWORD )

                        jmp vector_0_5
                    .endif

                    mov z,SizeFromRegister(reg)
                    mov ecx,psize
                    .if eax == ecx
                        mov eax,reg
                    .else
                        mov edx,param
                        .if eax > ecx || (eax < ecx && [edx].asym.mem_type == MT_PTR)
                            mov psize,eax
                            asmerr(2114, &[esi+1])
                        .endif
                        mov ecx,psize
                        shr ecx,1
                        lea eax,[ecx*8+T_AL]
                        cmp ecx,4
                        sbb ecx,ecx
                        and eax,ecx
                        not ecx
                        and ecx,T_RAX
                        or  eax,ecx
                        mov ecx,regs_used
                        or byte ptr [ecx],R0_USED
                    .endif
                    mov i,eax
                .else
                    .if [edi].expr.mem_type == MT_EMPTY
                        mov eax,4
                        .if [edi].expr._instr == T_OFFSET
                            mov eax,8
                        .endif
                    .else
                        SizeFromMemtype( [edi].expr.mem_type, USE64, [edi].expr._type )
                    .endif
                    mov z,eax
                    mov ecx,psize
                    shr ecx,1
                    lea eax,[ecx*8+T_AL]
                    cmp ecx,4
                    sbb ecx,ecx
                    and eax,ecx
                    not ecx
                    and ecx,T_RAX
                    or  eax,ecx
                    mov i,eax
                    mov ecx,regs_used
                    or byte ptr [ecx],R0_USED
                .endif
                ;
                ; v2.11: no expansion if target type is a pointer
                ;
                mov eax,i
                .if eax >= T_RAX && eax <= T_RDI
                    sub eax,T_RAX - T_EAX
                .elseif eax >= T_R8 && eax <= T_R15
                    sub eax,T_R8 - T_R8D
                .endif
                mov i32,eax

                mov eax,z
                mov edx,param
                .if eax > psize || (eax < psize && [edx].asym.mem_type == MT_PTR)
                    asmerr(2114, &[esi+1])
                .endif
                mov eax,z
                .if eax != psize
                    .if eax == 4
                        .if IS_SIGNED([edi].expr.mem_type)
                            AddLineQueueX( " movsxd %r, %s", i, paramvalue );
                        .else
                            AddLineQueueX( " mov %r, %s", i, paramvalue )
                        .endif
                    .else
                        .if IS_SIGNED([edi].expr.mem_type)
                            mov eax,@CStr("movsx")
                        .else
                            mov eax,@CStr("movzx")
                        .endif
                        AddLineQueueX(" %s %r, %s", eax, i, paramvalue)
                    .endif
                .elseif [edi].expr.kind != EXPR_REG || [edi].expr.flags & EXF_INDIRECT
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

        .elseif [edx].asym.mem_type == MT_REAL4 || \
                [edx].asym.mem_type == MT_REAL8 || \
                [edx].asym.mem_type == MT_REAL16 || \
                ( [edx].asym.mem_type == MT_OWORD && vector_call )

            vector_0_5:
            CheckXMM(reg, paramvalue, regs_used, param)
        .else

            mov eax,psize
            .if adr || eax > 8 ; psize > 8 shouldn't happen!
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
                mov eax,1
                .break
            .endif

            mov edx,[edi].expr.sym
            mov ecx,[edi].expr.kind

            .switch
            .case ecx == EXPR_REG
                ;
                ; register argument
                ;
                mov eax,8
                .endc .if ( [edi].expr.flags & EXF_INDIRECT )
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
                SizeFromMemtype([edi].expr.mem_type, USE64, [edi].expr._type)
                .endc
            .case ecx == EXPR_ADDR && ( !edx || [edx].asym.state == SYM_UNDEFINED )
                mov eax,psize
                .endc
            .default
                mov eax,4
                .endc .if [edi].expr._instr != T_OFFSET
                mov eax,8
            .endsw
            mov z,eax

            mov edx,param
            .if eax > psize || ( eax < psize && [edx].asym.mem_type == MT_PTR )
                asmerr( 2114, &[esi+1] )
            .endif

            mov eax,psize
            shr eax,1
            cmp eax,4
            cmc
            sbb eax,0
            movzx ebx,ms64_regs[esi+eax*4]

            mov eax,ebx
            .if eax >= T_RAX && eax <= T_RDI
                sub eax,T_RAX - T_EAX
            .elseif eax >= T_R8 && eax <= T_R15
                sub eax,T_R8 - T_R8D
            .endif
            mov i32,eax

            ;
            ; optimization if the register holds the value already
            ;
            .if [edi].expr.kind == EXPR_REG && !([edi].expr.flags & EXF_INDIRECT)

                .if GetValueSp(reg) & OP_R

                    .if ebx == reg
                        mov eax,1
                        .break
                    .endif

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
            ;
            ; v2.11: allow argument extension
            ;
            mov eax,z
            .if eax < psize
                .if eax == 4
                    .if IS_SIGNED([edi].expr.mem_type)
                        AddLineQueueX(" movsxd %r, %s", ebx, paramvalue)
                    .else
                        movzx eax,ms64_regs[esi+2*4]
                        AddLineQueueX(" mov %r, %s", eax, paramvalue)
                    .endif
                .else
                    .if IS_SIGNED([edi].expr.mem_type)
                        mov eax,@CStr("movsx")
                    .else
                        mov eax,@CStr("movzx")
                    .endif
                    AddLineQueueX(" %s %r, %s", eax, ebx, paramvalue)
                .endif
            .else
                mov eax,paramvalue
                .if ( word ptr [eax] == "0" || \
                    ( [edi].expr.kind == EXPR_CONST && [edi].expr.value == 0 ) )
                    AddLineQueueX(" xor %r, %r", i32, i32)
                .elseif [edi].expr.kind == EXPR_CONST && [edi].expr.hvalue == 0
                    mov ecx,i32
                    .if ecx >= T_AX && ecx <= T_DI
                        add ecx,T_EAX - T_AX
                    .elseif ecx >= T_R8W && ecx <= T_R15W
                        add ecx,T_R8D - T_R8W
                    .endif
                    AddLineQueueX(" mov %r, %s", ecx, eax)
                .else
                    AddLineQueueX(" mov %r, %s", ebx, eax)
                .endif
            .endif
            lea ecx,[esi+RPAR_START]
            mov eax,1
            shl eax,cl
            mov ecx,regs_used
            or [ecx],al
        .endif
        mov eax,1
    .until 1
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
            AddLineQueueX(" add %r, %d", T_RSP, eax)
        .endif
    .endif
    ret
ms64_fcend endp

;-------------------------------------------------------------------------------
; FCT_ELF64
;-------------------------------------------------------------------------------

.data

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

elf64_pcheck proc public uses esi edi ebx pProc:LPDSYM, paranode:LPDSYM, used:ptr SINT

  local regname[32]:sbyte
  local reg:SINT
  local psize:SINT

    mov ebx,used
    mov esi,paranode
    mov psize,SizeFromMemtype( [esi].asym.mem_type, [esi].asym.Ofssize, [esi].asym._type )
    mov ecx,[ebx]

    .repeat

        .if ( al > 16 || cl > 6 || ch > 8 || [esi].asym.sint_flag & SINT_ISVARARG )

            xor eax,eax
            mov [esi].asym.string_ptr,eax
            .break
        .endif

        mov dl,[esi].asym.mem_type
        .if ( al == 16 || dl == MT_REAL4 || dl == MT_REAL8 || dl == MT_REAL16 || dl == MT_OWORD )
            movzx ecx,ch
            inc byte ptr [ebx+1]
            lea eax,[ecx+T_XMM0]
        .else
            movzx ecx,cl
            shr eax,1
            cmp eax,4
            cmc
            sbb eax,0
            lea edi,[eax*2]
            lea eax,[edi+eax*4]
            movzx eax,elf64_regs[ecx+eax]
            inc byte ptr [ebx]
        .endif

        lea edi,regname
        mov [esi].asym.state,SYM_TMACRO
        mov [esi].asym.regist[0],ax
        mov [esi].asym.regist[2],cx
        GetResWName( eax, edi )
        mov [esi].asym.string_ptr,LclAlloc( &[strlen( edi ) + 1] )
        strcpy( eax, edi )
        mov eax,1
    .until 1
    ret

elf64_pcheck endp

elf64_fcstart proc uses ebx pp:ptr nsym, numparams:SINT, start:SINT,
    tokenarray:ptr asm_tok, value:ptr SINT

    ; v2.28: xmm id to fcscratch

    mov edx,pp
    mov edx,[edx].nsym.procinfo

    .if [edx].proc_info.flags & PINF_HAS_VARARG

        mov ebx,start
        shl ebx,4
        add ebx,tokenarray

        .for ( : [ebx].asm_tok.token != T_FINAL: ebx += 16 )

            .if [ebx].asm_tok.token == T_REG

                .if GetValueSp( [ebx].asm_tok.tokval ) & OP_XMM

                    inc fcscratch
                .endif

            .elseif [ebx].asm_tok.token == T_ID

                .if SymFind( [ebx].asm_tok.string_ptr )
                    .if [eax].asym.mem_type & MT_FLOAT

                        inc fcscratch
                    .endif
                .endif
            .endif
        .endf
        mov eax,fcscratch
    .else
        xor ebx,ebx
        .for ( edx = [edx].proc_info.paralist : edx : edx = [edx].nsym.prev )

            movzx eax,[edx].asym.regist[0]
            .if GetValueSp( eax ) & OP_XMM

                inc ebx
                .break
            .endif
        .endf
        mov eax,ebx
    .endif

    xor ecx,ecx
    mov edx,value
    mov [edx],ecx
    ret

elf64_fcstart endp

elf64_param proc uses esi edi ebx pp:ptr nsym, index:SINT, param:ptr nsym, adr:SINT,
    opnd:ptr expr, paramvalue:LPSTR, regs_used:ptr byte

    local z, psize, reg, i, i32, destroyed

    mov destroyed,FALSE
    mov edx,param
    mov edi,opnd

    .repeat

        mov eax,1
        mov ecx,paramvalue
        .break .if [ecx] == ah

        mov psize,GetPSize(adr)
        mov edx,param

        .if [edx].asym.sint_flag & SINT_ISVARARG
            .if eax == 16 || [edi].expr.mem_type & MT_FLOAT
                dec fcscratch
                mov esi,fcscratch
                lea ebx,[esi+T_XMM0]
            .else
                mov esi,index
                sub esi,fcscratch
                shr eax,1
                cmp eax,4
                cmc
                sbb eax,0
                lea ebx,[eax*2]
                lea eax,[ebx+eax*4]
                movzx ebx,elf64_regs[esi+eax]
            .endif
        .else
            movzx ebx,[edx].asym.regist[0]
            movzx esi,[edx].asym.regist[2]
        .endif

        movzx eax,[edx].asym.mem_type
        .if  eax == MT_EMPTY && [edx].asym.sint_flag & SINT_ISVARARG && \
            [edi].expr.kind == EXPR_ADDR && [edi].expr.mem_type & MT_FLOAT
            .if SymFind( paramvalue )
                mov edx,eax
            .else
                mov edx,param
            .endif
            movzx eax,[edx].asym.mem_type
        .endif

        .if eax == MT_REAL4 || eax == MT_REAL8 || eax == MT_REAL16

            mov eax,[edi].expr.base_reg
            .if eax
                mov eax,[eax].asm_tok.tokval
            .endif
            CheckXMM(eax, paramvalue, regs_used, edx)

        .else

            mov ecx,ebx
            .if ecx >= T_RAX && ecx <= T_RDI
                sub ecx,T_RAX - T_EAX
            .elseif ecx >= T_R8 && ecx <= T_R15
                sub ecx,T_R8 - T_R8D
            .endif
            mov i32,ecx

            .if adr
                .if SizeFromRegister( ebx ) == 8
                    AddLineQueueX(" lea %r, %s", ebx, paramvalue)
                .else
                    mov eax,index
                    inc eax
                    asmerr(2114, eax)
                .endif
                lea ecx,[esi+ELF64_START]
                mov eax,1
                shl eax,cl
                mov ecx,regs_used
                or [ecx],al
                mov eax,1
                .break
            .endif

            mov edx,[edi].expr.sym
            mov ecx,[edi].expr.kind

            .switch
            .case ecx == EXPR_REG
                ;
                ; register argument
                ;
                mov eax,8
                .endc .if ( [edi].expr.flags & EXF_INDIRECT )
                mov eax,[edi].expr.base_reg
                mov eax,[eax].asm_tok.tokval
                mov reg,eax
                SizeFromRegister(eax)
                .endc
            .case ecx == EXPR_CONST
                mov eax,[edi].expr.hvalue
                .if eax && eax != -1
                    mov psize,8 ; extend const value to 64
                .endif
                ; drop
            .case ecx == EXPR_FLOAT
                mov eax,psize
                .endc
            .case [edi].expr.mem_type != MT_EMPTY
                SizeFromMemtype([edi].expr.mem_type, USE64, [edi].expr._type)
                .endc
            .case ecx == EXPR_ADDR && [edx].asym.state == SYM_UNDEFINED
                mov eax,psize
                .endc
            .default
                mov eax,4
                .endc .if [edi].expr._instr != T_OFFSET
                mov eax,8
            .endsw
            mov z,eax

            mov edx,param
            .if eax > psize || (eax < psize && [edx].asym.mem_type == MT_PTR)

                mov eax,index
                inc eax
                asmerr( 2114, eax )
            .endif

            ;
            ; optimization if the register holds the value already
            ;
            .if [edi].expr.kind == EXPR_REG && !([edi].expr.flags & EXF_INDIRECT)

                .if GetValueSp(reg) & OP_XMM

                    mov eax,[edi].expr.base_reg
                    mov eax,[eax].asm_tok.tokval
                    CheckXMM(eax, paramvalue, regs_used, param)
                    mov eax,1
                    .break

                .elseif GetValueSp(reg) & OP_R

                    .if ebx == reg
                        mov eax,1
                        .break
                    .endif

                    .if [edi].expr.mem_type == MT_EMPTY

                        ; get type info (signed)
                        mov ecx,param
                        mov al,[ecx].asym.mem_type
                        mov [edi].expr.mem_type,al
                    .endif

                    movzx ecx,GetRegNo(reg)
                    mov eax,1
                    shl eax,cl
                    .if eax & REGPAR_ELF64
                        ;
                        ; convert register number to param number:
                        ;
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
            ;
            ; v2.11: allow argument extension
            ;
            mov eax,z
            .if eax < psize
                .if eax == 4
                    .if IS_SIGNED([edi].expr.mem_type)
                        AddLineQueueX(" movsxd %r, %s", ebx, paramvalue)
                    .else
                        movzx eax,elf64_regs[esi+2*6]
                        AddLineQueueX(" mov %r, %s", eax, paramvalue)
                    .endif
                .else
                    .if psize == 2
                        movzx ebx,elf64_regs[esi+2*6]
                    .endif
                    .if IS_SIGNED([edi].expr.mem_type)
                        mov eax,@CStr("movsx")
                    .else
                        mov eax,@CStr("movzx")
                    .endif
                    AddLineQueueX(" %s %r, %s", eax, ebx, paramvalue)
                .endif
            .else
                mov eax,paramvalue
                .if ( word ptr [eax] == "0" || \
                    ( [edi].expr.kind == EXPR_CONST && [edi].expr.value == 0 ) )
                    AddLineQueueX(" xor %r, %r", i32, i32)
                .elseif [edi].expr.kind == EXPR_CONST && [edi].expr.hvalue == 0
                    mov ecx,i32
                    .if ecx >= T_AX && ecx <= T_DI
                        add ecx,T_EAX - T_AX
                    .elseif ecx >= T_R8W && ecx <= T_R15W
                        add ecx,T_R8D - T_R8W
                    .endif
                    AddLineQueueX(" mov %r, %s", ecx, eax)
                .else
                    AddLineQueueX(" mov %r, %s", ebx, eax)
                .endif
            .endif
            lea ecx,[esi+ELF64_START]
            mov eax,1
            shl eax,cl
            mov ecx,regs_used
            or [ecx],al
        .endif
        mov eax,1
    .until 1
    ret

elf64_param endp

elf64_fcend proc pp, numparams, value
    ;
    ; use <value>, which has been set by elf64_fcstart()
    ;
    ret
elf64_fcend endp

    END
