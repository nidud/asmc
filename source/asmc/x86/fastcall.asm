; FASTCALL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc
include limits.inc
include malloc.inc
include stdio.inc

include asmc.inc
include proc.inc
include lqueue.inc
include parser.inc
include reswords.inc
include segment.inc
include operands.inc
include expreval.inc
include qfloat.inc
include memalloc.inc

public  fastcall_tab
public  elf64_regs

;
; tables for FASTCALL support
;
; v2.07: 16-bit MS FASTCALL registers are AX, DX, BX.
; And params on stack are in PASCAL order.
;
ifndef ASMC64
ms32_fcstart        proto __ccall private :dsym_t, :int_t, :int_t, :token_t, :ptr int_t
ms32_fcend          proto __ccall private :dsym_t, :int_t, :int_t
ms32_param          proto __ccall private :dsym_t, :int_t, :dsym_t, :int_t, :ptr expr, :string_t, :ptr byte
ms32_pcheck         proto __ccall private :dsym_t, :dsym_t, :ptr int_t
vc32_fcstart        proto __ccall private :dsym_t, :int_t, :int_t, :token_t, :ptr int_t
vc32_param          proto __ccall private :dsym_t, :int_t, :dsym_t, :int_t, :ptr expr, :string_t, :ptr byte
vc32_pcheck         proto __ccall private :dsym_t, :dsym_t, :ptr int_t
vc32_return         proto __ccall private :dsym_t, :string_t
endif

watc_fcstart        proto __ccall private :dsym_t, :int_t, :int_t, :token_t, :ptr int_t
watc_fcend          proto __ccall private :dsym_t, :int_t, :int_t
watc_param          proto __ccall private :dsym_t, :int_t, :dsym_t, :int_t, :ptr expr, :string_t, :ptr byte
watc_pcheck         proto __ccall private :dsym_t, :dsym_t, :ptr int_t
watc_return         proto __ccall private :dsym_t, :string_t

ms64_fcstart        proto __ccall private :dsym_t, :int_t, :int_t, :token_t, :ptr int_t
ms64_fcend          proto __ccall private :dsym_t, :int_t, :int_t
ms64_param          proto __ccall private :dsym_t, :int_t, :dsym_t, :int_t, :ptr expr, :string_t, :ptr byte
ms64_pcheck         proto __ccall private :dsym_t, :dsym_t, :ptr int_t
ms64_return         proto __ccall private :dsym_t, :string_t

elf64_fcstart       proto __ccall private :dsym_t, :int_t, :int_t, :token_t, :ptr int_t
elf64_fcend         proto __ccall private :dsym_t, :int_t, :int_t
elf64_param         proto __ccall private :dsym_t, :int_t, :dsym_t, :int_t, :ptr expr, :string_t, :ptr byte
elf64_pcheck        proto __ccall private :dsym_t, :dsym_t, :ptr int_t

get_register        proto __ccall private :int_t, :int_t
abs_param           proto __ccall private :dsym_t, :int_t, :dsym_t, :string_t
checkregoverwrite   proto __ccall private :expr_t, :ptr byte, :ptr dword, :ptr byte, :dword
GetPSize            proto __ccall private :int_t, :asym_t, :expr_t
CreateFloat         proto __ccall private :int_t, :expr_t, :string_t
CheckXMM            proto __ccall private :int_t, :string_t, :ptr byte, :dsym_t
GetAccumulator      proto __ccall private :uint_t, :ptr

.pragma warning(disable: 6004)

GetGroup        proto :asym_t

GetSegmentPart  proto :ptr expr, :string_t, :string_t
search_assume   proto :asym_t, :int_t, :int_t

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
externdef       size_vararg:int_t           ; size of :VARARG arguments

REGPAR_WIN64    equ 0x0306 ; regs 1, 2, 8 and 9
REGPAR_ELF64    equ 0x03C6 ; regs 1, 2, 6, 7, 8 and 9
REGPAR_WATC     equ 0x000F ; regs 0, 1, 3, 2

;
; table of fastcall types.
; must match order of enum fastcall_type!
; also see table in mangle.asm!
;

ifndef ASMC64

ms16_regs           db T_AX,  T_DX, T_BX
ms32_regs16         special_token T_AX, T_DX, T_BX
ms32_maxreg         uint_t lengthof(ms32_regs16), lengthof(ms32_regs32)

fastcall_tab fastcall_conv \
    { ms32_fcstart,  ms32_fcend,  ms32_param,  ms32_pcheck,  vc32_return }, ; FCT_MSC
    { watc_fcstart,  watc_fcend,  watc_param,  watc_pcheck,  watc_return }, ; FCT_WATCOMC
    { ms64_fcstart,  ms64_fcend , ms64_param,  ms64_pcheck,  ms64_return }, ; FCT_WIN64
    { elf64_fcstart, elf64_fcend, elf64_param, elf64_pcheck, ms64_return }, ; FCT_ELF64
    { vc32_fcstart,  ms32_fcend , vc32_param,  vc32_pcheck,  vc32_return }, ; FCT_VEC32
    { ms64_fcstart,  ms64_fcend , ms64_param,  ms64_pcheck,  ms64_return }  ; FCT_VEC64

else

fastcall_tab fastcall_conv \
    { 0,             0,           0,           0,            0           }, ; FCT_MSC
    { watc_fcstart,  watc_fcend,  watc_param,  watc_pcheck,  watc_return }, ; FCT_WATCOMC
    { ms64_fcstart,  ms64_fcend,  ms64_param,  ms64_pcheck,  ms64_return }, ; FCT_WIN64
    { elf64_fcstart, elf64_fcend, elf64_param, elf64_pcheck, ms64_return }, ; FCT_ELF64
    { 0,             0,           0,           0,            0           }, ; FCT_VEC32
    { ms64_fcstart,  ms64_fcend , ms64_param,  ms64_pcheck,  ms64_return }  ; FCT_VEC64

endif

watc_regs8          special_token T_AL, T_DL, T_BL, T_CL
watc_regs16         special_token T_AX, T_DX, T_BX, T_CX
watc_regs32         special_token T_EAX, T_EDX, T_EBX, T_ECX
watc_regs64         special_token T_RAX, T_RDX, T_RBX, T_RCX
watc_regs_qw        special_token T_AX, T_BX, T_CX, T_DX
watc_regname        char_t 64 dup(0)
watc_regist         char_t 32 dup(0)
watc_param_index    db 0, 2, 3, 1

ms32_regs           db T_ECX, T_EDX
ms32_regs32         special_token T_ECX, T_EDX

ms64_regs byte \
    T_CL,  T_DL,  T_R8B, T_R9B,
    T_CX,  T_DX,  T_R8W, T_R9W,
    T_ECX, T_EDX, T_R8D, T_R9D,
    T_RCX, T_RDX, T_R8,  T_R9

fcscratch int_t 0  ; exclusively to be used by FASTCALL helper functions
WordSize  int_t 0

elf64_valptr ptr int_t 0

elf64_regs byte \
    T_DIL, T_SIL, T_DL,  T_CL,  T_R8B, T_R9B,
    T_DI,  T_SI,  T_DX,  T_CX,  T_R8W, T_R9W,
    T_EDI, T_ESI, T_EDX, T_ECX, T_R8D, T_R9D,
    T_RDI, T_RSI, T_RDX, T_RCX, T_R8,  T_R9

elf64_param_index db 0, 3, 2, 0, 0, 0, 1, 0, 4, 5, 0, 0, 0, 0, 0, 0
                   ; AX CX DX BX SP BP SI DI R8 R9

    .code

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

fastcall_init proc
    mov fcscratch,0
    mov WordSize,ModuleInfo.wordsize
    ret
fastcall_init endp

; get segment part of an argument
; v2.05: extracted from PushInvokeParam(),
; so it could be used by watc_param() as well.

GetSegm macro x
    exitm<[x].asym.segm>
    endm

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

    .elseif eax && [eax].asym.segm

        mov ebx,[eax].asym.segm
        mov ecx,[ebx].dsym.seginfo

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

get_regname proc reg:int_t, size:int_t

    mov reg,get_register(reg, size)
    GetResWName(reg, LclAlloc(8))
    ret

get_regname endp

    option proc:private

;-------------------------------------------------------------------------------
; FCT_MSC - MS 16-/32-bit fastcall (ax,dx,cx / ecx,edx)
;-------------------------------------------------------------------------------

ifndef ASMC64

ms32_fcstart proc uses ebx pp:dsym_t, numparams:int_t, start:int_t,
    tokenarray:token_t, value:ptr int_t

    mov ebx,pp

    .return 0 .if GetSymOfssize(ebx) == USE16

    .for ecx=0,
         eax=[ebx].dsym.procinfo,
         eax=[eax].proc_info.paralist : eax : eax=[eax].dsym.nextparam, numparams--

        .if [eax].asym.state == SYM_TMACRO

            inc fcscratch
        .elseif [eax].asym.mem_type != MT_ABS
            add ecx,4
        .endif
    .endf
    mov eax,value
    mov [eax],ecx
    mov eax,1
    ret

ms32_fcstart endp

ms32_fcend proc pp:dsym_t, numparams:int_t, value:int_t

    mov eax,pp
    .if value && [eax].asym.flag2 & S_ISINLINE
        AddLineQueueX( " add esp, %u", value )
    .endif
    ret

ms32_fcend endp

ms32_param proc uses esi edi ebx pp:dsym_t, index:int_t, param:dsym_t, adr:int_t,
    opnd:ptr expr, paramvalue:string_t, r0used:ptr byte

  local z

    mov esi,param

    .if abs_param(pp, index, esi, paramvalue)

        .if [esi].asym.state == SYM_TMACRO

            dec fcscratch
        .endif
        .return
    .endif
    .return .if [esi].asym.state != SYM_TMACRO

    .if GetSymOfssize(pp) == USE16
        lea edi,ms16_regs
        add edi,fcscratch
        inc fcscratch
    .else
        dec fcscratch
        lea edi,ms32_regs
        add edi,index
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
                AddLineQueueX(
                    " mov %r, %s\n"
                    " mov %r, 0", &[edi+T_AL], paramvalue,  &[edi+T_AH])
            .endif
        .else
            mov eax,[edi].expr.base_reg
            .if [edi].expr.kind == EXPR_REG && !([edi].expr.flags & E_INDIRECT) && eax

                .return 1 .if [eax].asm_tok.tokval == ebx
            .endif
            mov eax,paramvalue
            .if ( word ptr [eax] == "0" )
                xor eax,eax
            .endif
            .if eax
                mov eax,z
                .if [edi].expr.kind == EXPR_ADDR && [edi].expr.mem_type != MT_EMPTY
                    SizeFromMemtype( [edi].expr.mem_type, [edi].expr.Ofssize, [edi].expr.type )
                .endif
                mov ecx,T_MOV
                .if eax < z
                    mov eax,ModuleInfo.curr_cpu
                    and eax,P_CPU_MASK
                    .if eax >= P_386
                        mov ecx,T_MOVSX
                        .if !( [edi].expr.mem_type & MT_SIGNED )
                            mov ecx,T_MOVZX
                        .endif
                    .endif
                .endif
                AddLineQueueX(" %r %r, %s", ecx, ebx, paramvalue)
            .else
                AddLineQueueX(" xor %r, %r", ebx, ebx)
            .endif
        .endif

        .if ebx == T_AX
            mov eax,r0used
            or byte ptr [eax],R0_USED
        .endif
    .endif
    mov eax,1
    ret

ms32_param endp

; the MS Win32 fastcall ABI is simple: register ecx and edx are used,
; if the parameter's value fits into the register.
; there is no space reserved on the stack for a register backup.
; The 16-bit ABI uses registers AX, DX and BX - additional registers
; are pushed in PASCAL order (i.o.w.: left to right).

ms32_pcheck proc private uses esi edi ebx p:ptr dsym, paranode:ptr dsym, used:ptr int_t

  local regname[32]:char_t

    mov esi,paranode
    mov ebx,SizeFromMemtype( [esi].asym.mem_type, [esi].asym.Ofssize, [esi].asym.type )

    ; v2.07: 16-bit has 3 register params (AX,DX,BX)

    mov     edi,used
    movzx   eax,ModuleInfo.Ofssize
    mov     ecx,ms32_maxreg[eax*4]
    movzx   edx,CurrWordSize

    .return( 0 ) .if ( ebx > edx || [edi] >= ecx )

    mov [esi].asym.state,SYM_TMACRO

    ; v2.10: for codeview debug info, store the register index in the symbol

    mov ecx,[edi]
    mov ebx,ms32_regs16[ecx*4]
    .if ( ModuleInfo.Ofssize )
        mov ebx,ms32_regs32[ecx*4]
    .endif
    mov [esi].asym.regist[0],bx

    GetResWName( ebx, &regname )
    mov [esi].asym.string_ptr,LclAlloc( &[strlen( &regname ) + 1] )
    strcpy( [esi].asym.string_ptr, &regname )
    inc dword ptr [edi]
   .return( 1 )

ms32_pcheck endp

endif

;-------------------------------------------------------------------------------
; FCT_WATCOMC
;-------------------------------------------------------------------------------

; the watcomm fastcall variant is somewhat peculiar:
; 16-bit:
; - for BYTE/WORD arguments, there are 4 registers: AX,DX,BX,CX
; - for DWORD arguments, there are 2 register pairs: DX::AX and CX::BX
; - there is a "usage" flag for each register. Thus the prototype:
;   sample proto :WORD, :DWORD, :WORD
;   will assign AX to the first param, CX::BX to the second, and DX to
;   the third!


watc_fcstart proc pp:dsym_t, numparams:int_t, start:int_t,
        tokenarray: token_t, value: ptr int_t

    mov edx,pp ; v2.33.25: add *this to fcscratch
    .if [edx].asym.flag2 & S_ISINLINE && [edx].asym.flag2 & S_ISSTATIC
        movzx eax,ModuleInfo.wordsize
        add fcscratch,eax
    .endif
    mov eax,1
    ret

watc_fcstart endp

watc_fcend proc pp:dsym_t, numparams:int_t, value:int_t

    mov eax,pp
    movzx edx,ModuleInfo.Ofssize
    mov ecx,stackreg[edx*4]
    mov edx,[eax].dsym.procinfo
    mov eax,[edx].proc_info.parasize
    .if [edx].proc_info.flags & PROC_HAS_VARARG
        add eax,size_vararg
        AddLineQueueX( " add %r, %u", ecx, eax )
    .elseif fcscratch < eax
        sub eax,fcscratch
        AddLineQueueX( " add %r, %u", ecx, eax )
    .endif
    ret

watc_fcend endp

watc_param proc uses esi edi ebx pp:dsym_t, index:int_t, param:dsym_t, adr:int_t,
        opnd:ptr expr, paramvalue:string_t, r0used:ptr byte

; get the register for parms 0 to 3,
; using the watcom register parm passing conventions ( A D B C )

  local regs[64]:byte, reg[4]:string_t, size:uint_t, psize:uint_t
  local buffer[128]:byte, reg_32:int_t

    mov ebx,param

    .if abs_param(pp, index, ebx, paramvalue)

        .if [ebx].asym.mem_type == MT_ABS

            movzx ecx,ModuleInfo.wordsize
            add fcscratch,ecx
        .endif
        .return
    .endif

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
    mov psize,SizeFromMemtype( [ebx].asym.mem_type, USE_EMPTY, [ebx].asym.type )
    mov eax,4
    mov ecx,opnd
    .if ( [ecx].expr.mem_type != MT_EMPTY )
        SizeFromMemtype( [ecx].expr.mem_type, USE_EMPTY, [ecx].expr.type )
    .endif
    mov size,eax

    .if strchr( edi, ':' )

        strcpy( &regs, edi )
        movzx eax,ModuleInfo.wordsize
        add fcscratch,eax

        .for ( ebx = &regs, edi = 0 : edi < 4 : edi++ )

            mov [esi+edi*4],ebx
            mov ebx,strchr( ebx, ':' )
            .break .if !ebx
            mov byte ptr [ebx],0
            add ebx,2
        .endf
    .endif

    mov edi,opnd
    .if adr
        mov edx,[edi].expr.sym
        mov esi,T_MOV
        mov ebx,T_OFFSET
        .if [edi].expr.kind == EXPR_REG || !edx || \
            [edx].asym.state == SYM_STACK || ModuleInfo.Ofssize == USE64
            mov esi,T_LEA
            mov ebx,T_NULL
        .endif

        ; v2.05: filling of segment part added

        xor eax,eax
        .if reg[1*4] != eax
            .if GetSegmentPart(opnd, &buffer, paramvalue)
                AddLineQueueX( " mov %s, %r", reg, eax)
            .else
                AddLineQueueX( " mov %s, %s", reg, &buffer)
            .endif
            mov eax,4
        .endif
        mov eax,reg[eax]
        AddLineQueueX( "%r %s, %r %s", esi, eax, ebx, paramvalue )
        .return 1
    .endif

    .fors ebx = 3: ebx >= 0: ebx--

        mov ecx,reg[ebx*4]

        .if ecx

            mov edx,[ecx]
            .if ( dl == 'e' || dl == 'r' )
                shr edx,8
            .endif
            mov eax,T_EAX
            .if ( dl == 'd' )
                mov eax,T_EDX
            .elseif ( dl == 'b' )
                mov eax,T_EBX
            .elseif ( dl == 'c' )
                mov eax,T_ECX
            .endif
            .if ( ModuleInfo.Ofssize == USE64 && psize > 4 )
                add eax,T_RAX - T_EAX
            .endif
            mov reg_32,eax

            mov edi,opnd
            .if [edi].expr.kind == EXPR_CONST

                mov eax,paramvalue
                .if ( word ptr [eax] == "0" )
                    xor eax,eax
                .endif

                mov edx,[edi].expr.value
                .ifs ebx > 0
                    mov esi,T_LOWWORD
                    .if ( ModuleInfo.Ofssize > USE16 )
                        mov esi,T_LOW32
                    .endif
                .elseif !ebx && reg[4]
                    mov esi,T_HIGHWORD
                    .if ( ModuleInfo.Ofssize > USE16 )
                        mov edx,[edi].expr.hvalue
                        mov esi,T_HIGH32
                    .endif
                .else
                    mov esi,T_NULL
                    .if ( ModuleInfo.Ofssize > USE16 )
                        or edx,[edi].expr.hvalue
                    .endif
                .endif
                .if ( eax == 0 || edx == 0 )
                    .if ( ModuleInfo.Ofssize )
                        mov eax,reg_32
                        .if ( ModuleInfo.Ofssize == USE64 && eax > T_EBX )
                            sub eax,T_RAX - T_EAX
                        .endif
                        AddLineQueueX( "xor %r, %r", eax, eax )
                    .else
                        AddLineQueueX( "xor %s, %s", ecx, ecx )
                    .endif
                .elseif esi != T_NULL
                    AddLineQueueX( "mov %s, %r (%s)", ecx, esi, eax )
                .else
                    .if ( ModuleInfo.Ofssize )
                        mov ecx,reg_32
                        .if ( ModuleInfo.Ofssize == USE64 && ecx > T_EBX )
                            sub ecx,T_RAX - T_EAX
                        .endif
                        AddLineQueueX( "mov %r, %s", ecx, eax )
                    .else
                        AddLineQueueX( "mov %s, %s", ecx, eax )
                    .endif
                .endif

            .elseif [edi].expr.kind == EXPR_REG && !( [edi].expr.flags & E_INDIRECT )

                mov edx,[edi].expr.base_reg
                mov edi,[edx].asm_tok.tokval
                mov eax,param
                movzx esi,[eax].asym.regist
                .if reg[ebx*4+4]
                    movzx esi,[eax].asym.regist[2]
                    mov edi,[edx-32].asm_tok.tokval
                .endif
                SizeFromRegister( edi )
                mov edx,psize
                .if ( edx < 4 && ModuleInfo.Ofssize )
                    mov esi,reg_32
                    mov edx,4
                .endif
                .if ( esi != edi )
                    .if ( ( eax < 4 || edx < 4 ) && ModuleInfo.Ofssize )
                        mov ecx,param
                        mov edx,T_MOVSX
                        .if !( [ecx].asym.mem_type & MT_SIGNED )
                            mov edx,T_MOVZX
                        .endif
                        AddLineQueueX( " %r %r, %r", edx, esi, edi )
                    .else
                        AddLineQueueX( " mov %r, %r", esi, edi )
                    .endif
                    movzx ecx,GetRegNo(edi)
                    mov eax,1
                    shl eax,cl
                    .if eax & REGPAR_WATC
                        mov ecx,r0used
                        .if [ecx] & al
                            asmerr(2133)
                        .endif
                    .endif
                .endif
            .else
                .if ebx == 0 && reg[4] == NULL
                    mov edi,param
                    mov eax,size
                    mov edx,psize
                    .if ( ( eax < edx || edx < 4 ) && ModuleInfo.Ofssize )
                        .if ( eax > edx )
                            mov eax,edx
                        .endif
                        mov ecx,T_BYTE
                        mov esi,reg_32
                        .if ( eax == 2 )
                            mov ecx,T_WORD
                        .endif
                         mov edx,T_MOVSX
                         .if !( [edi].asym.mem_type & MT_SIGNED )
                             mov edx,T_MOVZX
                         .endif
                         AddLineQueueX( " %r %r, %r ptr %s", edx, esi, ecx, paramvalue )
                    .else
                        AddLineQueueX( "mov %s, %s", ecx, paramvalue )
                    .endif
                .else
                    .if ModuleInfo.Ofssize == USE64
                        mov esi,T_QWORD
                    .elseif ModuleInfo.Ofssize == USE32
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
                    AddLineQueueX( "mov %s, %r ptr %s[%u]", edi, esi, paramvalue, ecx )
                .endif
            .endif
        .endif
    .endf
    mov ecx,index
    mov cl,watc_param_index[ecx]
    mov eax,1
    shl eax,cl
    mov ecx,r0used
    or [ecx],al
    mov eax,1
    ret

watc_param endp

; register usage for OW fastcall (register calling convention).
; registers are used for parameter size 1,2,4,8.
; if a parameter doesn't fit in a register, a register pair is used.
; however, valid register pairs are e/dx:e/ax and e/cx:e/bx only!
; if a parameter doesn't fit in a register pair, registers
; are used ax:bx:cx:dx!!!
; stack cleanup for OW fastcall: if the proc is VARARG, the caller
; will do the cleanup, else the called proc does it.
; in VARARG procs, all parameters are pushed onto the stack!

watc_pcheck proc private uses esi edi ebx p:ptr dsym, paranode:ptr dsym, used:ptr int_t

  .new newflg:int_t
  .new shift:int_t
  .new firstreg:int_t
  .new Ofssize:byte

    mov esi,paranode
    mov ebx,SizeFromMemtype( [esi].asym.mem_type, [esi].asym.Ofssize, [esi].asym.type )
    .if ( ebx == 0 && [esi].asym.mem_type == MT_ABS )
        mov ebx,4
    .endif

    mov edi,p
    mov Ofssize,GetSymOfssize( edi )
    mov edi,[edi].dsym.procinfo

    ; v2.05: VARARG procs don't have register params

    xor eax,eax
    .return .if ( [edi].proc_info.flags & PROC_HAS_VARARG )
    .return .if ( ebx != 1 && ebx != 2 && ebx != 4 && ebx != 8 )

    ; v2.05: rewritten. The old code didn't allow to "fill holes"

    .if ( ebx == 8 && Ofssize == USE32 )
        mov edx,15
        mov ecx,4
        .if Ofssize
            mov edx,3
            mov ecx,2
        .endif
    .elseif ( ebx == 4 && Ofssize == USE16 )
        mov edx,3
        mov ecx,2
    .else
        mov edx,1
        mov ecx,1
    .endif

    ; scan if there's a free register (pair/quadrupel)

    mov eax,used
    .for ( edi = 0 : edi < 4 && ( edx & [eax] ) : edx <<= cl, edi += ecx )
    .endf
    .return( 0 ) .if ( edi >= 4 ) ; exit if nothing is free

    mov newflg,edx
    shl edi,2
    mov [esi].asym.state,SYM_TMACRO
    .switch ebx
    .case 1
        mov [esi].asym.regist[0],watc_regs8[edi]
        .endc
    .case 2
        mov [esi].asym.regist[0],watc_regs16[edi]
        .endc
    .case 4
        .if ( Ofssize )
            mov [esi].asym.regist[0],watc_regs32[edi]
        .else
            mov [esi].asym.regist[0],watc_regs16[edi]
            mov [esi].asym.regist[2],watc_regs16[edi+1*4]
        .endif
        .endc
    .case 8
        .if ( Ofssize == USE32 )
            mov [esi].asym.regist[0],watc_regs32[edi]
            mov [esi].asym.regist[2],watc_regs32[edi+1*4]
        .elseif ( Ofssize == USE64 )
            mov [esi].asym.regist[0],watc_regs64[edi]
        .else

            ; the AX:BX:CX:DX sequence is for 16-bit only.
            ; fixme: no support for codeview debug info yet
            ; the S_REGISTER record supports max 2 registers only.

            .for ( edi = 0, watc_regname[0] = NULLC: edi < 4: edi++ )
                lea ecx,watc_regname[strlen( &watc_regname )]
                GetResWName( watc_regs_qw[edi*4], ecx )
                .if ( edi != 3 )
                    strcat( &watc_regname, "::" )
                .endif
            .endf
        .endif
    .endsw
    .if ( [esi].asym.regist[2] )
        mov ebx,GetResWName( [esi].asym.regist[0], NULL )
        tsprintf( &watc_regname, "%s::%s",
            GetResWName( [esi].asym.regist[2], &watc_regist ), ebx )
    .elseif ( [esi].asym.regist[0] )
        GetResWName( [esi].asym.regist[0], &watc_regname )
    .endif
    mov eax,newflg
    mov ecx,used
    or [ecx],eax
    mov [esi].asym.string_ptr,LclAlloc( &[strlen( &watc_regname ) + 1] )
    strcpy( [esi].asym.string_ptr, &watc_regname )
    .return( 1 )

watc_pcheck endp

watc_return proc p:ptr dsym, buffer:string_t

    ret

watc_return endp


;-------------------------------------------------------------------------------
; FCT_WIN64
;-------------------------------------------------------------------------------

ms64_fcstart proc uses esi edi ebx pp:dsym_t, numparams:int_t, start:int_t,
    tokenarray:token_t, value:ptr int_t

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
    .if [edx].asym.langtype == LANG_VECTORCALL
        mov esi,6
        mov edi,16
    .endif

    ; v2.04: VARARG didn't work

    mov edx,[edx].dsym.procinfo
    .if ( [edx].proc_info.flags & PROC_HAS_VARARG )

        .for ( ecx = start,
               ecx <<= 4,
               ecx += tokenarray,
               eax = 0 : [ecx].asm_tok.token != T_FINAL : ecx += 16 )

            .if ( [ecx].asm_tok.token == T_COMMA )

                inc eax
            .endif
        .endf

    .else ; v2.31.22: extend call stack to 6 * [32|64]

        .for ( edx = [edx].proc_info.paralist : edx : edx = [edx].dsym.prev )

            .if [edx].asym.total_size > edi

                .switch ( [edx].asym.mem_type )
                .case MT_REAL10
                .case MT_OWORD
                .case MT_REAL16
                    mov edi,16
                    .endc
                .case MT_YWORD
                    mov edi,32
                    .endc
                .case MT_ZWORD
                    mov edi,64
                    .endc
                .endsw
            .endif
        .endf
    .endif
    mov WordSize,edi

    .if eax < esi
        mov eax,esi
    .endif
    mov ecx,eax
    mul edi
    .if edi == 8 && ecx & 1
        add eax,edi
    .endif

    mov edx,pp ; v2.31.24: skip stack alloc if inline
    .if ecx == esi && [edx].asym.flag2 & S_ISINLINE
        xor eax,eax
    .endif
    mov edx,value
    mov [edx],eax

    .if ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP )

        mov edx,sym_ReservedStack
        .if eax > [edx].asym.value

            mov [edx].asym.value,eax
        .endif
    .elseif eax
        AddLineQueueX( " sub rsp, %d", eax )
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

ms64_fcend proc pp:dsym_t, numparams:int_t, value:int_t
    ;
    ; use <value>, which has been set by ms64_fcstart()
    ;
    .if !( ModuleInfo.win64_flags & W64F_AUTOSTACKSP )

        mov eax,value
        .if eax
            .if ( ModuleInfo.epilogueflags )
                AddLineQueueX( " lea rsp, [rsp+%d]", eax )
            .else
                AddLineQueueX( " add rsp, %d", eax )
            .endif
        .endif
    .endif
    ret
ms64_fcend endp

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
    mov reg,0

    mov edi,opnd
    mov eax,index
    mul WordSize
    mov arg_offset,eax

    mov ecx,pp
    .if [ecx].asym.langtype == LANG_VECTORCALL
        mov vector_call,TRUE
    .endif

    mov ebx,param
    .return .if abs_param(ecx, index, ebx, paramvalue)

    mov psize,GetPSize(address, ebx, edi)
    checkregoverwrite( edi, regs_used, &reg, &destroyed, REGPAR_WIN64 )

    .if destroyed

        asmerr(2133)
        mov ecx,regs_used
        mov byte ptr [ecx],0
    .endif

    .if ( [ebx].asym.mem_type == MT_TYPE )
        mov ebx,[ebx].asym.type
    .endif
    mov edx,ebx
    mov esi,index
    add esi,fcscratch
    mov eax,psize

    .if esi >= 4 && ( address || eax > 8 )

        .if eax == 4

            mov ebx,T_EAX
        .else
            .if eax < 8

                asmerr(2114, &[esi+1])

            .elseif vector_call && esi < 6 && ( \
                [ebx].asym.mem_type & MT_FLOAT || \
                [ebx].asym.mem_type == MT_YWORD || \
                [ebx].asym.mem_type == MT_OWORD )

                .return CheckXMM( reg, paramvalue, regs_used, ebx )
            .endif
            mov ebx,T_RAX
        .endif

        mov ecx,regs_used
        mov eax,R0_USED
        or [ecx],al

        ; v2.31.24 xmm to r64 -- vararg

        .if ( psize == 16 && ( GetValueSp(reg) & OP_XMM ) )
            AddLineQueueX( " movq %r, %r", ebx, reg )
        .else
            AddLineQueueX( " lea %r, %s", ebx, paramvalue )
        .endif
        AddLineQueueX( " mov [%r+%u], %r", T_RSP, arg_offset, ebx )
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

                AddLineQueueX(
                    " mov dword ptr [rsp+%u], low32(%s)\n"
                    " mov dword ptr [rsp+%u+4], high32(%s)", arg_offset, paramvalue, arg_offset, paramvalue )

            .else

                ; v2.11: no expansion if target type is a pointer and argument
                ; is an address part

                mov eax,[edi].expr.sym
                .if [ebx].asym.mem_type == MT_PTR && \
                    [edi].expr.kind == EXPR_ADDR && [eax].asym.state != SYM_UNDEFINED

                    asmerr(2114, &[esi+1])
                .endif
                mov eax,psize
                mov edx,paramvalue
                .switch ( eax )
                .case 1: mov ecx,T_BYTE : .endc
                .case 2: mov ecx,T_WORD : .endc
                .case 4
                    ;
                    ; added v2.33.57 for vararg
                    ; - this fails for NULL pointers as the upper value is not cleared
                    ; - the default size is 4
                    ;
                    .if ( [edi].expr.value || !( [ebx].asym.sflags & S_ISVARARG ) )
                        mov ecx,T_DWORD
                        .endc
                    .endif
                .default
                    mov ecx,T_QWORD
                    .endc
                .endsw
                AddLineQueueX( " mov %r ptr [rsp+%u], %s", ecx, arg_offset, edx )
            .endif

        .elseif ( [edi].expr.kind == EXPR_FLOAT )

            .if ( esi < 6 && vector_call &&
                ( [ebx].asym.mem_type & MT_FLOAT ||
                  [ebx].asym.mem_type == MT_YWORD ||
                  [ebx].asym.mem_type == MT_OWORD ) )
                .return CheckXMM(reg, paramvalue, regs_used, ebx)
            .endif

            .if ( [ebx].asym.mem_type != MT_REAL4 ) ; added v2.31
                AddLineQueueX(
                    " mov dword ptr [rsp+%u+0], low32(%s)\n"
                    " mov dword ptr [rsp+%u+4], high32(%s)", arg_offset, paramvalue, arg_offset, paramvalue)
            .else
                AddLineQueueX(" mov dword ptr [rsp+%u], %s", arg_offset, paramvalue)
            .endif

        .else ; it's a register or variable

            .if ( [edi].expr.kind == EXPR_REG && !( [edi].expr.flags & E_INDIRECT ) )

                .if ( vector_call && esi < 6 && ( [ebx].asym.mem_type & MT_FLOAT || \
                        [ebx].asym.mem_type == MT_YWORD || [ebx].asym.mem_type == MT_OWORD ) )

                    .return CheckXMM(reg, paramvalue, regs_used, ebx)
                .endif

                mov size,SizeFromRegister(reg)
                mov ecx,psize
                .if eax == ecx
                    mov eax,reg
                    ;.if ecx == 4 ; clear upper 32 ?
                    ;    get_register(reg, 8)
                    ;.endif
                .else
                    .if ( eax > ecx || (eax < ecx && [ebx].asym.mem_type == MT_PTR ) )
                        ; added in v2.31.25
                        .if ( eax > ecx && eax == 16 && [ebx].asym.mem_type & MT_FLOAT )
                            .if ecx == 4
                                AddLineQueueX( " movss [rsp+%u], %r", arg_offset, reg )
                            .else
                                AddLineQueueX( " movsd [rsp+%u], %r", arg_offset, reg )
                            .endif
                            .return 1
                        .endif
                        mov psize,eax
                        asmerr(2114, &[esi+1])
                    .endif
                    GetAccumulator( psize, regs_used )
                .endif
                mov i,eax

            .else
                .if ( [edi].expr.mem_type == MT_EMPTY )
                    mov eax,4
                    ; added v2.31.25
                    .if ( [edi].expr.inst == T_OFFSET || \
                         ( psize == 8 && [ebx].asym.mem_type == MT_PTR ) )
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
            .if ( eax > psize || (eax < psize && [ebx].asym.mem_type == MT_PTR ) )
                asmerr(2114, &[esi+1])
            .endif

            mov eax,size
            .if ( eax != psize )
                .if ( eax == 4 )
                    .if ( IS_SIGNED([edi].expr.mem_type ) )
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
            .elseif ( [edi].expr.kind != EXPR_REG || [edi].expr.flags & E_INDIRECT )
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
            AddLineQueueX(" mov [rsp+%u], %r", arg_offset, i)
        .endif
        .return 1
    .endif

    .if ( ( [ebx].asym.mem_type & MT_FLOAT ) ||
          ( [ebx].asym.mem_type == MT_YWORD ) ||
          ( [ebx].asym.mem_type == MT_OWORD &&
            ( vector_call || [ebx].asym.sflags & S_ISVECTOR ) ) )

        .return CheckXMM(reg, paramvalue, regs_used, ebx)
    .endif

    mov ecx,[edi].expr.kind
    xor ebx,ebx

    .if ( ecx == EXPR_REG && !( [edi].expr.flags & E_INDIRECT ) )

        mov eax,[edi].expr.base_reg
        .if ( [eax+16].asm_tok.token == T_DBL_COLON )

            ; case <reg>::<reg>

            mov ebx,[eax+32].asm_tok.tokval
            .if fcscratch
                dec fcscratch
            .endif
        .endif
    .endif

    mov reg_64,ebx
    mov eax,psize

    .if ( address || ( !ebx && eax > 8 ) ) ; psize > 8 shouldn't happen!

        .if eax >= 4
            .if eax > 4
                mov eax,4
            .else
                xor eax,eax
            .endif
            movzx ecx,ms64_regs[esi+eax+2*4]
            .if ( psize == 16 && ( GetValueSp(reg) & OP_XMM ) )
                .if ( [edx].asym.mem_type == MT_OWORD )
                    ; v2.33.07 :oword <-- xmm reg
                    lea ecx,[esi+T_XMM0]
                    .if ( ecx != reg )
                        AddLineQueueX( " movaps %r, %r", ecx, reg )
                    .endif
                    .return 1
                .else
                    ; v2.31.24 xmm to r64 -- vararg
                    AddLineQueueX( " movq %r, %r", ecx, reg )
                .endif
            .else
                AddLineQueueX( " lea %r, %s", ecx, paramvalue )
            .endif
        .else
            asmerr(2114, &[esi+1])
        .endif

    ret_regused:

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
            mov ecx,i32
            .return .if ( ebx == reg || ecx == reg )
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
                AddLineQueueX(
                    " mov %r, byte ptr %s[2]\n"
                    " shl %r, 16", ecx, eax, ebx)
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
                    AddLineQueueX(
                        " mov al, byte ptr %s[6]\n"
                        " shl eax,16\n"
                        " mov ax, word ptr %s[4]", paramvalue, paramvalue)
                .endif
                AddLineQueueX(
                    " shl rax,32\n"
                    " or  %r,rax", ebx)
            .endif
        .else

            mov edx,pp
            mov ecx,[edi].expr.sym
            .if ecx && \
                index == 0 && \
                [edi].expr.mbr && \
                [edi].expr.kind == EXPR_ADDR && \
                [edi].expr.flags == E_INDIRECT && \
                [ecx].asym.is_ptr && \
                [edx].asym.flag1 & S_METHOD

                mov ebx,ecx
                AddLineQueueX( " mov rax, %s", [ecx].asym.name )
                mov edx,[edi].expr.mbr
                mov ecx,[ebx].asym.target_type
                AddLineQueueX( " mov rcx, [rax].%s.%s", [ecx].asym.name, [edx].asym.name )

            .else
                mov edx,param
                .if [edi].expr.kind == EXPR_FLOAT && [edx].asym.sflags & S_ISVARARG
                    mov ebx,get_register(ebx, 8) ; added v2.31
                .endif
                AddLineQueueX( " mov %r, %s", ebx, paramvalue )
            .endif
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

; the MS Win64 fastcall ABI is strict: the first four parameters are
; passed in registers. If a parameter's value doesn't fit in a register,
; it's address is used instead. parameter 1 is stored in rcx/xmm0,
; then comes rdx/xmm1, r8/xmm2, r9/xmm3. The xmm regs are used if the
; param is a float/double (but not long double!).
; Additionally, there's space for the registers reserved by the caller on,
; the stack. On a function's entry it's located at [esp+8] for param 1,
; [esp+16] for param 2,... The parameter names refer to those stack
; locations, not to the register names.

ms64_pcheck proc p:ptr dsym, paranode:ptr dsym, used:ptr int_t

    ; since the parameter names refer the stack-backup locations,
    ; there's nothing to do here!
    ; That is, if a parameter's size is > 8, it has to be changed
    ; to a pointer. This is to be done yet.

    .return( 0 )

ms64_pcheck endp


ms64_return proc p:ptr dsym, buffer:string_t

    ; nothing to do, the caller cleans the stack

    ret

ms64_return endp

;-------------------------------------------------------------------------------
; FCT_ELF64
;-------------------------------------------------------------------------------

    assume esi:asym_t

elf64_pcheck proc public uses esi edi ebx pProc:dsym_t, paranode:dsym_t, used:ptr int_t

  local regname[32]:sbyte
  local reg:int_t

    mov ebx,used
    mov esi,paranode
    SizeFromMemtype([esi].mem_type, [esi].Ofssize, [esi].type)
    mov ecx,[ebx]
    mov dl,[esi].mem_type
    .if ( [esi].mem_type == MT_TYPE )
        mov edx,[esi].type
        mov dl,[edx].asym.mem_type
    .endif

    .switch
      .case ( [esi].sflags & S_ISVARARG )
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
    assume ebx:token_t

elf64_fcstart proc uses esi edi ebx pp:dsym_t, numparams:int_t, start:int_t,
    tokenarray:token_t, value:ptr int_t

    ; v2.28: xmm id to fcscratch

    mov edx,pp
    mov edx,[edx].dsym.procinfo
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
                    .if ( [eax].asym.mem_type == MT_TYPE )
                        mov eax,[eax].asym.type
                    .endif
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

        .for ( edi = [edx].proc_info.paralist : edi : edi = [edi].dsym.prev )
            mov dl,[edi].asym.mem_type
            .if ( dl == MT_TYPE )
                mov edx,[edi].asym.type
                mov dl,[edx].asym.mem_type
            .endif
            .if ( dl & MT_FLOAT || dl == MT_YWORD )
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

elf64_fcend proc pp:dsym_t, numparams:int_t, value:int_t

    ; use <value>, which has been set by elf64_fcstart()

    mov ecx,value
    .if ecx
        AddLineQueueX(" add rsp, %u*8", ecx)
    .endif
    ret

elf64_fcend endp

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

    .if ( [edx].sflags & S_ISVARARG )

        .if fcscratch && ( eax == 16 || [edi].mem_type & MT_FLOAT )
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

    mov ecx,pp
    .if ( [edx].asym.sflags & S_ISVARARG && \
          [ecx].asym.flag2 & S_ISINLINE )
        .return 1
    .endif
    .if [edx].asym.mem_type == MT_ABS
        mov esi,edx
        mov [esi].asym.name,LclAlloc(&[strlen(paramvalue)+1])
        strcpy(eax, paramvalue)
        .return 1
    .endif

    movzx eax,[edx].mem_type
    .if  ( eax == MT_EMPTY && ( [edx].sflags & S_ISVARARG ) && \
           [edi].kind == EXPR_ADDR && [edi].mem_type & MT_FLOAT )

        .if SymFind(paramvalue)
            mov edx,eax
        .else
            mov edx,param
        .endif
    .endif
    .if ( [edx].mem_type == MT_TYPE )
        mov edx,[edx].asym.type
    .endif
    movzx eax,[edx].mem_type

    .if ( !( eax & MT_FLOAT || eax == MT_YWORD ) && esi >= 6 )

        .return 0 .if !stack
        mov ebx,T_RAX
    .endif

    assume edx:nothing
    mov sym,edx

    .if ( eax & MT_FLOAT || eax == MT_YWORD )
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

                mov edx,param
                mov eax,T_RAX
                .if [edx].asym.mem_type == MT_REAL2
                    mov eax,T_AX
                .elseif [edx].asym.mem_type == MT_REAL4
                    mov eax,T_EAX
                .endif

                AddLineQueueX(
                    " mov %r, %s\n"
                    " push rax", eax, ecx)
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
            mov edx,param
            .if [edi].expr.kind == EXPR_FLOAT && [edx].asym.sflags & S_ISVARARG
                mov ebx,get_register( ebx, 8 ); added v2.31
            .endif
            AddLineQueueX( " mov %r, %s", ebx, paramvalue )
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
        AddLineQueueX(
            " mov %r, qword ptr %s\n"
            " mov %r, qword ptr %s[8]", eax, ecx, ebx, paramvalue)
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

    assume edx:nothing
    assume edi:nothing

;-------------------------------------------------------------------------------
; FCT_VEC32
;-------------------------------------------------------------------------------

vc32_fcstart proc pp:dsym_t, numparams:int_t, start:int_t,
    tokenarray:token_t, value:ptr int_t

    .for ecx=0, eax=pp, eax=[eax].dsym.procinfo,
         eax=[eax].proc_info.paralist: eax: eax=[eax].dsym.nextparam

        .if [eax].asym.state == SYM_TMACRO || \
            ( [eax].asym.state == SYM_STACK && [eax].asym.total_size <= 16 )

            inc fcscratch
        .else
            add ecx,4
        .endif
    .endf
    mov eax,value
    mov [eax],ecx
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
        .if edx < 2
            AddLineQueueX( " lea %r, %s", ebx, paramvalue )
        .else
            AddLineQueueX(
                " lea eax, %s\n"
                " push eax", paramvalue )
        .endif
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
                    AddLineQueueX(
                        " mov eax, %s\n"
                        " movd %r, eax", paramvalue, ebx )
                    .endc
                .case MT_REAL8
                    AddLineQueueX(
                        " pushd high32(%s)\n"
                        " pushd low32 (%s)\n"
                        " movq %r, [esp]\n"
                        " add esp, 8", paramvalue, paramvalue, ebx )
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
                    AddLineQueueX(
                        " pushd high32(0x%16lx)\n"
                        " pushd low32 (0x%16lx)\n"
                        " pushd high32(0x%16lx)\n"
                        " pushd low32 (0x%16lx)\n"
                        " movups %r, [esp]\n"
                        " add esp, 16",
                        [edi].expr.hlvalue, [edi].expr.hlvalue,
                        [edi].expr.llvalue, [edi].expr.llvalue, ebx )
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

; The vectorcall calling convention follows the fastcall convention for 32-bit
; integer type arguments, and takes advantage of the SSE vector registers for
; vector type and HVA arguments.
;
; The first two integer type arguments found in the parameter list from left to
; right are placed in ECX and EDX, respectively. A hidden this pointer is
; treated as the first integer type argument, and is passed in ECX. The first
; six vector type arguments are passed by value through SSE vector registers 0
; to 5, in the XMM or YMM registers, depending on argument size.

vc32_pcheck proc uses esi edi ebx p:ptr dsym, paranode:ptr dsym, used:ptr int_t

  local regname[32]:char_t

    mov esi,paranode
    mov ebx,SizeFromMemtype( [esi].asym.mem_type, [esi].asym.Ofssize, [esi].asym.type )

    .if ( [esi].asym.mem_type & MT_FLOAT )
        mov ebx,16
    .endif
    .if ( ebx < 4 )
        mov ebx,4
    .endif

    mov edi,used
    mov ecx,[edi]
   .return( 0 ) .if ( ebx != 4 && ebx != 16 )
   .return( 0 ) .if ( ( ebx == 4 && ecx > 1 ) || ( ebx == 16 && ecx > 5 ) )

    mov eax,ecx
    add ecx,T_XMM0
    .if ( ebx == 4 )
        mov ecx,ms32_regs32[eax*4]
    .endif
    mov [esi].asym.state,SYM_TMACRO
    mov [esi].asym.regist[0],cx

    GetResWName( ecx, &regname )
    mov [esi].asym.string_ptr,LclAlloc( &[strlen( &regname ) + 1] )
    strcpy( [esi].asym.string_ptr, &regname )
    inc dword ptr [edi]
   .return( 1 )

vc32_pcheck endp

vc32_return proc private uses edi ebx p:ptr dsym, buffer:string_t

    mov edx,p
    mov edx,[edx].dsym.procinfo
    xor ebx,ebx
    .for ( edi = [edx].proc_info.paralist: edi: edi = [edi].dsym.nextparam )
        .if ( [edi].asym.state != SYM_TMACRO ) ;; v2.34.35: used by ms32..
            add ebx,ROUND_UP( [edi].asym.total_size, CurrWordSize )
        .endif
    .endf
    .if ( ebx )
        add strlen(buffer),buffer
        mov ecx,'t'
        .if ( ModuleInfo.radix == 10 )
            xor ecx,ecx
        .endif
        tsprintf( eax, "%d%c", ebx, ecx )
    .endif
    ret

vc32_return endp

;--------------------------------------------

get_register proc uses ecx reg:int_t, size:int_t

    .if GetValueSp(reg) & OP_XMM
        mov size,16
    .endif
    movzx ecx,GetRegNo(reg)
    mov eax,reg

    .switch size
    .case 1
        .switch ecx
        .case 0,1,2,3
            .return(&[ecx+T_AL])
        .case 4,5,6,7,8,9,10,11,12,13,14,15
            .return(&[ecx+T_SPL-4])
        .endsw
        .endc
    .case 2
        .switch ecx
        .case 0,1,2,3,4,5,6,7
            .return(&[ecx+T_AX])
        .case 8,9,10,11,12,13,14,15
            .return(&[ecx+T_R8W-8])
        .endsw
        .endc
    .case 4
        .switch ecx
        .case 0,1,2,3,4,5,6,7
            .return(&[ecx+T_EAX])
        .case 8,9,10,11,12,13,14,15
            .return(&[ecx+T_R8D-8])
        .endsw
        .endc
    .case 8
        .switch ecx
        .case 0,1,2,3,4,5,6,7
            .return(&[ecx+T_RAX])
        .case 8,9,10,11,12,13,14,15
            .return(&[ecx+T_R8-8])
        .endsw
        .endc
    .endsw
    ret
get_register endp

    assume ebx:nothing
    assume ecx:nothing

abs_param proc uses ebx pp:dsym_t, index:int_t, param:dsym_t, paramvalue:string_t

    mov eax,1
    mov ecx,pp

    ; skip arg if :vararg and inline

    mov ebx,param
    .if ( [ebx].asym.sflags & S_ISVARARG && \
          [ecx].asym.flag2 & S_ISINLINE )

        .return
    .endif

    ; skip loading class pointer if :vararg and inline

    .if ( [ecx].asym.flag2 & S_ISINLINE && \
          [ecx].asym.flag1 & S_METHOD && !index )

        mov edx,[ecx].dsym.procinfo
        .if ( [edx].proc_info.flags & PROC_HAS_VARARG )

            .return
        .endif
    .endif

    ; skip arg if :abs

    .if ( [ebx].asym.mem_type == MT_ABS )

        mov [ebx].asym.name,LclAlloc(&[strlen(paramvalue)+1])
        strcpy(eax, paramvalue)

        .return 1
    .endif
    xor eax,eax
    ret

abs_param endp

; parameter for Win64 FASTCALL.
; the first 4 parameters are hold in registers: rcx, rdx, r8, r9 for non-float arguments,
; xmm0, xmm1, xmm2, xmm3 for float arguments. If parameter size is > 8, the address of
; the argument is used instead of the value.

checkregoverwrite proc uses esi edi ebx opnd:ptr expr,
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

checkregoverwrite endp

GetPSize proc uses edi address:int_t, param:asym_t, opnd:expr_t

    mov edx,param
    mov edi,opnd

    ; v2.11: default size is 32-bit, not 64-bit

    .if [edx].asym.sflags & S_ISVARARG

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
        .elseif [edi].expr.kind == EXPR_FLOAT && [edi].expr.mem_type == MT_REAL16

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

    .if ( [edi].expr.kind == EXPR_REG && !( [edi].expr.flags & E_INDIRECT ) )
        mov ecx,GetValueSp(reg)
        .if ( ecx & ( OP_XMM or OP_YMM or OP_ZMM ) )
            lea eax,[esi+T_XMM0]
            .if ( ecx & OP_YMM )
                lea eax,[esi+T_YMM0]
            .elseif ( ecx & OP_ZMM )
                lea eax,[esi+T_ZMM0]
            .endif
            .if ( eax != reg )
                mov edx,param
                .if ( reg < T_XMM16 && ecx & OP_XMM )
                    .if ( [edx].asym.mem_type == MT_REAL4 )
                        AddLineQueueX( " movss %r, %r", eax, reg )
                    .elseif ( [edx].asym.mem_type == MT_REAL8 )
                        AddLineQueueX( " movsd %r, %r", eax, reg )
                    .else
                        AddLineQueueX( " movaps %r, %r", eax, reg )
                    .endif
                .else
                    .if ( [edx].asym.mem_type == MT_REAL4 )
                        AddLineQueueX( " vmovss %r, %r, %r", eax, eax, reg )
                    .elseif ( [edx].asym.mem_type == MT_REAL8 )
                        AddLineQueueX( " vmovsd %r, %r, %r", eax, eax, reg )
                    .else
                        AddLineQueueX( " vmovaps %r, %r", eax, reg )
                    .endif
                .endif
            .endif
            .return 1
        .endif
    .endif

    mov edx,param
    lea ebx,[esi+T_XMM0]
    .if ( [edi].expr.kind == EXPR_FLOAT )

        mov eax,[edi]
        or  eax,[edi+4]
        or  eax,[edi+8]
        or  eax,[edi+12]
        .ifz
            AddLineQueueX( " xorps %r, %r", ebx, ebx )
            .return 1
        .endif

        .if ( [edx].asym.mem_type == MT_REAL10 || [edx].asym.mem_type == MT_REAL16 )
            mov esi,10
            .if ( [edx].asym.mem_type == MT_REAL16 )
                mov esi,16
            .endif
            CreateFloat( esi, edi, &buffer )
            lea eax,buffer
            .if ( esi == 10 )
                AddLineQueueX( " movaps %r, xmmword ptr %s", ebx, eax )
            .else
                AddLineQueueX( " movaps %r, %s", ebx, eax )
            .endif
            .return 1
        .endif
        .if ( [edx].asym.mem_type == MT_REAL2 )
            mov eax,regs_used
            or  byte ptr [eax],R0_USED
            AddLineQueueX( " mov %r, %s", T_AX, paramvalue )
            AddLineQueueX( " movd %r, eax", ebx )
        .elseif ( [edx].asym.mem_type == MT_REAL4 )
            AddLineQueueX( " movd %r, %s", ebx, paramvalue )
        .elseif ( [edx].asym.mem_type == MT_REAL8 )
            AddLineQueueX( " movq %r, %s", ebx, paramvalue )
        .endif
    .else
        .if ( [edx].asym.mem_type == MT_REAL2 )
            mov eax,regs_used
            or  byte ptr [eax],R0_USED
            AddLineQueueX(
                " movzx eax, word ptr %s\n"
                " movd %r, eax", paramvalue, ebx)
        .elseif ( [edx].asym.mem_type == MT_REAL4 )
            AddLineQueueX( " movd %r, %s", ebx, paramvalue )
        .elseif ( [edx].asym.mem_type == MT_REAL8 )
            AddLineQueueX( " movq %r, %s", ebx, paramvalue )
        .elseif ( [edx].asym.mem_type == MT_REAL10 )
            AddLineQueueX( " movaps %r, xmmword ptr %s", ebx, paramvalue )
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

    END
