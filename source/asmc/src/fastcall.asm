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
include assume.inc

public  fastcall_tab
public  elf64_regs

extern  size_vararg:int_t        ; size of :VARARG arguments

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
elf64_const         proto __ccall private :uint_t, :uint_t, :qword, :string_t, :uint_t

abs_param           proto __ccall private :dsym_t, :int_t, :dsym_t, :string_t
checkregoverwrite   proto __ccall private :expr_t, :ptr byte, :ptr dword, :ptr byte, :dword
GetPSize            proto __ccall private :int_t, :asym_t, :expr_t
CreateFloat         proto __ccall private :int_t, :expr_t, :string_t
CheckXMM            proto __ccall private :int_t, :string_t, :ptr byte, :dsym_t, :ptr expr, :int_t
GetAccumulator      proto fastcall private :uint_t, :ptr

.pragma warning(disable: 6004)

R0_USED             equ 0x01 ; register contents of AX/EAX/RAX is destroyed
R0_H_CLEARED        equ 0x02 ; 16bit: high byte of R0 (=AH) has been set to 0
R0_X_CLEARED        equ 0x04 ; 16bit: register R0 (=AX) has been set to 0
R2_USED             equ 0x08 ; contents of DX is destroyed ( via CWD ); cpu < 80386 only
RDI_USED            equ 0x02 ; elf64: register contents of DIL/DI/EDI/RDI is destroyed
RSI_USED            equ 0x04 ; elf64: register contents of SIL/SI/ESI/RSI is destroyed
RCX_USED            equ 0x08 ; win64: register contents of CL/CX/ECX/RCX is destroyed
RDX_USED            equ 0x10 ; win64: register contents of DL/DX/EDX/RDX is destroyed
R8_USED             equ 0x20 ; win64: register contents of R8B/R8W/R8D/R8 is destroyed
R9_USED             equ 0x40 ; win64: register contents of R9B/R9W/R9D/R9 is destroyed
ROW_AX_USED         equ 0x08 ; watc: register contents of AL/AX/EAX is destroyed
ROW_DX_USED         equ 0x10 ; watc: register contents of DL/DX/EDX is destroyed
ROW_BX_USED         equ 0x20 ; watc: register contents of BL/BX/EBX is destroyed
ROW_CX_USED         equ 0x40 ; watc: register contents of CL/CX/ECX is destroyed

RPAR_START          equ 3 ; Win64: RCX first param start at bit 3
ROW_START           equ 3 ; watc: irst param start at bit 3
ELF64_START         equ 1 ; elf64: RDI first param start at bit 6

REGPAR_WIN64        equ 0x0306 ; regs 1, 2, 8 and 9
REGPAR_ELF64        equ 0x03C6 ; regs 1, 2, 6, 7, 8 and 9
REGPAR_WATC         equ 0x000F ; regs 0, 1, 3, 2


.data

;
; table of fastcall types.
; must match order of enum fastcall_type!
; also see table in mangle.asm!
;

watc_regs byte      T_AL,  T_DL,  T_BL,  T_CL,
                    T_AX,  T_DX,  T_BX,  T_CX,
                    T_EAX, T_EDX, T_EBX, T_ECX,
                    T_RAX, T_RDX, T_RBX, T_RCX

watc_regname        char_t 64 dup(0)
watc_regist         char_t 32 dup(0)
watc_param_index    db 0, 2, 3, 1

ms64_regs byte      T_CL,  T_DL,  T_R8B, T_R9B,
                    T_CX,  T_DX,  T_R8W, T_R9W,
                    T_ECX, T_EDX, T_R8D, T_R9D,
                    T_RCX, T_RDX, T_R8,  T_R9

ms32_regs           db T_ECX, T_EDX
ms16_regs           db T_AX, T_DX, T_BX
ms32_maxreg         db lengthof(ms16_regs), lengthof(ms32_regs)

align size_t
ifndef ASMC64
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
GetParmIndex proto watcall index:int_t {
    dec eax
    .if ( eax >= 7 )
        sub eax,5
    .endif
    }

fastcall_init proc __ccall

    mov fcscratch,0
    mov WordSize,ModuleInfo.wordsize
    ret

fastcall_init endp


; get segment part of an argument
; v2.05: extracted from PushInvokeParam(),
; so it could be used by watc_param() as well.

GetSegmentPart proc __ccall uses rsi rdi rbx opnd:ptr expr, buffer:string_t, fullparam:string_t

    mov esi,T_NULL
    mov rdi,opnd
    mov rax,[rdi].expr.sym
    mov rdx,[rdi].expr.override

    .if ( rdx )

        .if ( [rdx].asm_tok.token == T_REG )
            mov esi,[rdx].asm_tok.tokval
        .else
            tstrcpy( rdi, [rdx].asm_tok.string_ptr )
        .endif

    .elseif ( rax && [rax].asym.segm )

        mov rbx,[rax].asym.segm
        mov rcx,[rbx].dsym.seginfo

        .if ( [rcx].seg_info.segtype == SEGTYPE_DATA ||
              [rcx].seg_info.segtype == SEGTYPE_BSS )
            search_assume( rbx, ASSUME_DS, TRUE )
        .else
            search_assume( rbx, ASSUME_CS, TRUE )
        .endif
        .if ( eax != ASSUME_NOTHING )

            lea rsi,[rax+T_ES] ; v2.08: T_ES is first seg reg in special.h
        .else
            .if !GetGroup([rdi].expr.sym)
                mov rax,rbx
            .endif
            .if rax
                tstrcpy( buffer, [rax].asym.name )
            .else
                tstrcat( tstrcpy( buffer, "seg " ), fullparam )
            .endif
        .endif
    .elseif ( rax && [rax].asym.state == SYM_STACK )
        mov esi,T_SS
    .else
        tstrcat( tstrcpy( buffer, "seg " ), fullparam )
    .endif
    .return( rsi )

GetSegmentPart endp


get_regname proc __ccall reg:int_t, size:int_t

    mov reg,get_register( reg, size )
    GetResWName( reg, LclAlloc(8) )
    ret

get_regname endp


;-------------------------------------------------------------------------------
; FCT_MSC
;-------------------------------------------------------------------------------

ifndef ASMC64

ms32_fcstart proc __ccall private uses rbx pp:dsym_t, numparams:int_t, start:int_t,
    tokenarray:token_t, value:ptr int_t

    mov rbx,pp

    .if ( GetSymOfssize( rbx ) == USE16 )
        .return 0
    .endif

    .for ( ecx = 0, rax = [rbx].dsym.procinfo,
           rax = [rax].proc_info.paralist : rax : rax=[rax].dsym.nextparam, numparams-- )

        .if ( [rax].asym.state == SYM_TMACRO )

            inc fcscratch
        .elseif ( [rax].asym.mem_type != MT_ABS )
            add ecx,4
        .endif
    .endf
    mov rax,value
    mov [rax],ecx
    .return( 1 )

ms32_fcstart endp


ms32_fcend proc __ccall private pp:dsym_t, numparams:int_t, value:int_t

    mov rcx,pp
    .if ( value && [rcx].asym.flag2 & S_ISINLINE )
        AddLineQueueX( " add esp, %u", value )
    .endif
    ret

ms32_fcend endp


ms32_param proc __ccall private uses rsi rdi rbx pp:dsym_t, index:int_t, param:dsym_t, address:int_t,
    opnd:ptr expr, paramvalue:string_t, r0used:ptr byte

  local size:int_t

    mov rsi,param

    .if abs_param( pp, index, rsi, paramvalue )

        .if ( [rsi].asym.state == SYM_TMACRO )

            dec fcscratch
        .endif
        .return
    .endif
    .return .if ( [rsi].asym.state != SYM_TMACRO )

    .if ( GetSymOfssize( pp ) == USE16 )

        lea rdi,ms16_regs
        mov eax,fcscratch
        add rdi,rax
        inc fcscratch
    .else

        dec fcscratch
        lea rdi,ms32_regs
        mov eax,fcscratch
        add rdi,rax
    .endif

    movzx ebx,byte ptr [rdi]
    .if ( address )

        AddLineQueueX( " lea %r, %s", ebx, paramvalue )
    .else

        mov size,SizeFromMemtype( [rsi].asym.mem_type, USE_EMPTY, [rsi].asym.type )
        mov rdi,opnd
        SizeFromRegister( ebx )

        .if ( [rdi].expr.kind != EXPR_CONST && size < eax )

            mov eax,ModuleInfo.curr_cpu
            and eax,P_CPU_MASK

            .if ( eax >= P_386 )

                mov ecx,T_MOVSX
                .if ( !( [rsi].asym.mem_type & MT_SIGNED ) )
                    mov ecx,T_MOVZX
                .endif
                AddLineQueueX( " %r %r, %s", ecx, ebx, paramvalue )

            .else

                imul  eax,ebx,special_item
                lea   rdx,SpecialTable
                movzx edi,[rdx+rax].special_item.bytval

                AddLineQueueX( " mov %r, %s", &[rdi+T_AL], paramvalue )
                AddLineQueueX( " mov %r, 0",  &[rdi+T_AH] )
            .endif

        .else

            mov rax,[rdi].expr.base_reg
            .if ( [rdi].expr.kind == EXPR_REG && !( [rdi].expr.flags & E_INDIRECT ) && rax )

                .if ( [rax].asm_tok.tokval == ebx )
                    .return 1
                .endif
            .endif

            mov rax,paramvalue
            .if ( word ptr [rax] == "0" )

                AddLineQueueX( " xor %r, %r", ebx, ebx )

            .else

                mov eax,size
                .if ( [rdi].expr.kind == EXPR_ADDR && [rdi].expr.mem_type != MT_EMPTY )
                    SizeFromMemtype( [rdi].expr.mem_type, [rdi].expr.Ofssize, [rdi].expr.type )
                .endif
                mov ecx,T_MOV
                .if ( eax < size )

                    mov eax,ModuleInfo.curr_cpu
                    and eax,P_CPU_MASK

                    .if ( eax >= P_386 )
                        mov ecx,T_MOVSX
                        .if !( [rdi].expr.mem_type & MT_SIGNED )
                            mov ecx,T_MOVZX
                        .endif
                    .endif
                .endif
                AddLineQueueX( " %r %r, %s", ecx, ebx, paramvalue )
            .endif
        .endif

        .if ( ebx == T_AX )
            mov rax,r0used
            or byte ptr [rax],R0_USED
        .endif
    .endif
    .return( 1 )

ms32_param endp


; the MS Win32 fastcall ABI is simple: register ecx and edx are used,
; if the parameter's value fits into the register.
; there is no space reserved on the stack for a register backup.
; The 16-bit ABI uses registers AX, DX and BX - additional registers
; are pushed in PASCAL order (i.o.w.: left to right).

ms32_pcheck proc __ccall private uses rsi rdi rbx p:ptr dsym, paranode:ptr dsym, used:ptr int_t

  local regname[32]:char_t

    mov rsi,paranode
    mov rdi,used
    mov ebx,SizeFromMemtype( [rsi].asym.mem_type, [rsi].asym.Ofssize, [rsi].asym.type )

    ; v2.07: 16-bit has 3 register params (AX,DX,BX)

    movzx   eax,ModuleInfo.Ofssize
    lea     rdx,ms32_maxreg
    movzx   ecx,byte ptr [rdx+rax]
    movzx   edx,CurrWordSize

    .if ( ebx > edx || [rdi] >= ecx )
        .return( 0 )
    .endif

    mov [rsi].asym.state,SYM_TMACRO

    ; v2.10: for codeview debug info, store the register index in the symbol

    mov   ecx,[rdi]
    lea   rdx,ms16_regs
    movzx ebx,byte ptr [rdx+rcx]

    .if ( ModuleInfo.Ofssize )

        lea rdx,ms32_regs
        movzx ebx,byte ptr [rdx+rcx]
    .endif

    mov [rsi].asym.regist[0],bx
    mov [rsi].asym.string_ptr,LclDup( GetResWName( ebx, &regname ) )
    inc dword ptr [rdi]
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
;

watc_fcstart proc __ccall private pp: dsym_t, numparams:int_t, start:int_t,
        tokenarray: token_t, value: ptr int_t

    mov rcx,pp

    ; v2.33.25: add *this to fcscratch

    .if ( [rcx].asym.flag2 & S_ISINLINE && [rcx].asym.flag2 & S_ISSTATIC )

        movzx eax,ModuleInfo.wordsize
        add fcscratch,eax
    .endif
    .return( 1 )

watc_fcstart endp


watc_fcend proc __ccall private pp:dsym_t, numparams:int_t, value:int_t

    mov     rax,pp
    movzx   edx,ModuleInfo.Ofssize
    lea     rcx,stackreg
    mov     ecx,[rcx+rdx*4]
    mov     rdx,[rax].dsym.procinfo
    mov     eax,[rdx].proc_info.parasize

    .if ( [rdx].proc_info.flags & PROC_HAS_VARARG )
        add eax,size_vararg
        AddLineQueueX( " add %r, %u", ecx, eax )
    .elseif ( fcscratch < eax )
        sub eax,fcscratch
        AddLineQueueX( " add %r, %u", ecx, eax )
    .endif
    ret

watc_fcend endp


watc_param proc __ccall private uses rsi rdi rbx pp:dsym_t, index:int_t, param:dsym_t, adr:int_t,
        opnd:ptr expr, paramvalue:string_t, r0used:ptr byte

    ; get the register for parms 0 to 3,
    ; using the watcom register parm passing conventions ( A D B C )

    mov rbx,param

    .if abs_param( pp, index, rbx, paramvalue )

        .if [rbx].asym.mem_type == MT_ABS

            movzx ecx,ModuleInfo.wordsize
            add fcscratch,ecx
        .endif
        .return
    .endif

    .if ( [rbx].asym.state != SYM_TMACRO )
        .return
    .endif

    ; the "name" might be a register pair

   .new reg[4]:string_t = {0}
   .new psize:uint_t = SizeFromMemtype( [rbx].asym.mem_type, USE_EMPTY, [rbx].asym.type )

    lea rsi,reg
    mov rdi,[rbx].asym.string_ptr
    mov [rsi],rdi

    movzx eax,ModuleInfo.wordsize
    add fcscratch,eax

    mov eax,4
    mov rcx,opnd
    .if ( [rcx].expr.mem_type != MT_EMPTY )
        SizeFromMemtype( [rcx].expr.mem_type, USE_EMPTY, [rcx].expr.type )
    .endif
   .new size:uint_t = eax
   .new regs[64]:char_t

    .if tstrchr( rdi, ':' )

        tstrcpy( &regs, rdi )
        movzx eax,ModuleInfo.wordsize
        add fcscratch,eax

        .for ( rbx = &regs, edi = 0 : edi < 4 : edi++ )

            mov [rsi+rdi*string_t],rbx
            mov rbx,tstrchr( rbx, ':' )
            .break .if !rbx
            mov byte ptr [rbx],0
            add rbx,2
        .endf
    .endif

    mov rdi,opnd
    .if ( adr )
        mov rdx,[rdi].expr.sym
        mov esi,T_MOV
        mov ebx,T_OFFSET
        .if ( [rdi].expr.kind == EXPR_REG || !rdx ||
              [rdx].asym.state == SYM_STACK || ModuleInfo.Ofssize == USE64 )

            mov esi,T_LEA
            mov ebx,T_NULL
        .endif

        ; v2.05: filling of segment part added

        xor eax,eax
        .if ( reg[string_t] != rax )

            .new buffer[128]:char_t
            .if GetSegmentPart( opnd, &buffer, paramvalue )
                AddLineQueueX( " mov %s, %r", reg, eax )
            .else
                AddLineQueueX( " mov %s, %s", reg, &buffer )
            .endif
            mov eax,string_t
        .endif
        mov rcx,reg[rax]
        AddLineQueueX( "%r %s, %r %s", esi, rcx, ebx, paramvalue )
       .return 1
    .endif

    .fors ( ebx = 3: ebx >= 0: ebx-- )

        mov rcx,reg[rbx*string_t]

        .if rcx

            mov edx,[rcx]
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
            .new reg_32:int_t = eax

            mov rdi,opnd

            .if ( [rdi].expr.kind == EXPR_CONST )

                mov rax,paramvalue
                .if ( word ptr [rax] == "0" )
                    xor eax,eax
                .endif

                mov edx,[rdi].expr.value
                .ifs ( ebx > 0 )
                    mov esi,T_LOWWORD
                    .if ( ModuleInfo.Ofssize > USE16 )
                        mov esi,T_LOW32
                    .endif
                .elseif ( !ebx && reg[string_t] )
                    mov esi,T_HIGHWORD
                    .if ( ModuleInfo.Ofssize > USE16 )
                        mov edx,[rdi].expr.hvalue
                        mov esi,T_HIGH32
                    .endif
                .else
                    mov esi,T_NULL
                    .if ( ModuleInfo.Ofssize > USE16 )
                        or edx,[rdi].expr.hvalue
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
                        AddLineQueueX( "xor %s, %s", rcx, rcx )
                    .endif

                .elseif ( esi != T_NULL )

                    AddLineQueueX( "mov %s, %r (%s)", rcx, esi, rax )

                .else
                    .if ( ModuleInfo.Ofssize )
                        mov ecx,reg_32
                        .if ( ModuleInfo.Ofssize == USE64 &&
                              ecx > T_EBX && [rdi].expr.hvalue == 0 )
                            sub ecx,T_RAX - T_EAX
                        .endif
                        AddLineQueueX( "mov %r, %s", ecx, rax )
                    .else
                        AddLineQueueX( "mov %s, %s", ecx, rax )
                    .endif
                .endif

            .elseif ( [rdi].expr.kind == EXPR_REG && !( [rdi].expr.flags & E_INDIRECT ) )

                mov     rdx,[rdi].expr.base_reg
                mov     edi,[rdx].asm_tok.tokval
                mov     rax,param
                movzx   esi,[rax].asym.regist

                .if ( reg[rbx*string_t+string_t] )
                    movzx esi,[rax].asym.regist[2]
                    mov   edi,[rdx-asm_tok*2].asm_tok.tokval
                .endif
                SizeFromRegister( edi )

                mov edx,psize
                .if ( edx < 4 && ModuleInfo.Ofssize )
                    mov esi,reg_32
                    mov edx,4
                .endif

                .if ( esi != edi )
                    .if ( ( eax < 4 || edx < 4 ) && ModuleInfo.Ofssize )

                        mov rcx,param
                        mov edx,T_MOVSX
                        .if !( [rcx].asym.mem_type & MT_SIGNED )
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
                        mov rcx,r0used
                        .if ( [rcx] & al )
                            asmerr( 2133 )
                        .endif
                    .endif
                .endif

            .else

                .if ( ebx == 0 && reg[string_t] == NULL )

                    mov rdi,param
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
                         .if !( [rdi].asym.mem_type & MT_SIGNED )
                             mov edx,T_MOVZX
                         .endif
                         AddLineQueueX( " %r %r, %r ptr %s", edx, esi, ecx, paramvalue )
                    .else
                        AddLineQueueX( "mov %s, %s", rcx, paramvalue )
                    .endif

                .else

                    .if ( ModuleInfo.Ofssize == USE64 )
                        mov esi,T_QWORD
                    .elseif ( ModuleInfo.Ofssize == USE32 )
                        mov esi,T_DWORD
                    .else
                        mov esi,T_WORD
                    .endif

                    mov rdi,rcx
                    mov cl,ModuleInfo.Ofssize
                    mov eax,2
                    shl eax,cl
                    lea ecx,[rbx+1]
                    mul ecx
                    mov ecx,psize
                    sub ecx,eax

                    AddLineQueueX( "mov %s, %r ptr %s[%u]", rdi, esi, paramvalue, ecx )
                .endif
            .endif
        .endif
    .endf

    mov ecx,index
    lea rax,watc_param_index
    mov cl,[rax+rcx]
    mov eax,1
    shl eax,cl
    mov rcx,r0used
    or [rcx],al
   .return TRUE

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

watc_pcheck proc __ccall private uses rsi rdi rbx p:ptr dsym, paranode:ptr dsym, used:ptr int_t

  .new newflg:int_t
  .new shift:int_t
  .new firstreg:int_t
  .new Ofssize:byte

    mov rdi,p
    mov rsi,paranode
    mov ebx,SizeFromMemtype( [rsi].asym.mem_type, [rsi].asym.Ofssize, [rsi].asym.type )
    .if ( ebx == 0 && [rsi].asym.mem_type == MT_ABS )
        mov ebx,4
    .endif

    mov Ofssize,GetSymOfssize( rdi )
    mov rdi,[rdi].dsym.procinfo

    ; v2.05: VARARG procs don't have register params

    xor eax,eax
    .return .if ( [rdi].proc_info.flags & PROC_HAS_VARARG )
    .if ( ebx != 1 && ebx != 2 && ebx != 4 && ebx != 8 )
        .if ( ebx != 16 || Ofssize != USE64 || [rsi].asym.mem_type != MT_OWORD )
            .return
        .endif
    .endif

    ; v2.05: rewritten. The old code didn't allow to "fill holes"
    ; v2.34: added 64-bit handling

    mov al,Ofssize
    .if ( ebx == 16 && al == USE64 )
        mov edx,3
        mov ecx,2
    .elseif ( ebx == 8 && al < USE64 )
        .if ( al == USE16 )
            mov edx,15
            mov ecx,4
        .elseif ( al == USE32 )
            mov edx,3
            mov ecx,2
        .endif
    .elseif ( ebx == 4 && al == USE16 )
        mov edx,3
        mov ecx,2
    .else
        mov edx,1
        mov ecx,1
    .endif

    ; scan if there's a free register (pair/quadrupel)

    mov rax,used
    .for ( edi = 0 : edi < 4 && ( edx & [rax] ) : edx <<= cl, edi += ecx )
    .endf
    .return( 0 ) .if ( edi >= 4 ) ; exit if nothing is free

    mov newflg,edx
    lea rcx,watc_regs
    xor eax,eax
    add rcx,rdi
    mov [rsi].asym.state,SYM_TMACRO
    .switch ebx
    .case 1
        mov al,[rcx]
        mov [rsi].asym.regist[0],ax
        .endc
    .case 2
        mov al,[rcx+4]
        mov [rsi].asym.regist[0],ax
        .endc
    .case 4
        .if ( Ofssize )
            mov al,[rcx+8]
            mov [rsi].asym.regist[0],ax
        .else
            mov al,[rcx+4]
            mov [rsi].asym.regist[0],ax
            mov al,[rcx+5]
            mov [rsi].asym.regist[2],ax
        .endif
        .endc
    .case 8
        .if ( Ofssize == USE32 )
            mov al,[rcx+8]
            mov [rsi].asym.regist[0],ax
            mov al,[rcx+9]
            mov [rsi].asym.regist[2],ax
        .elseif ( Ofssize == USE64 )
            mov al,[rcx+12]
            mov [rsi].asym.regist[0],ax
        .else

            ; the AX:BX:CX:DX sequence is for 16-bit only.
            ; fixme: no support for codeview debug info yet
            ; the S_REGISTER record supports max 2 registers only.

            .for ( edi = 0, watc_regname[0] = NULLC: edi < 4: edi++ )
                tstrlen( &watc_regname )
                lea rcx,watc_regname
                lea rdx,[rcx+rax]
                lea rcx,watc_regs
                movzx ecx,byte ptr [rcx+rdi+4]
                GetResWName( ecx, rdx )
                .if ( edi != 3 )
                    tstrcat( &watc_regname, "::" )
                .endif
            .endf
        .endif
        .endc
    .case 16
        .if ( Ofssize == USE64 && [rsi].asym.mem_type == MT_OWORD )
            mov al,[rcx+12]
            mov [rsi].asym.regist[0],ax
            mov al,[rcx+13]
            mov [rsi].asym.regist[2],ax
        .endif
    .endsw
    .if ( [rsi].asym.regist[2] )
        mov rbx,GetResWName( [rsi].asym.regist[0], NULL )
        tsprintf( &watc_regname, "%s::%s",
            GetResWName( [rsi].asym.regist[2], &watc_regist ), rbx )
    .elseif ( [rsi].asym.regist[0] )
        GetResWName( [rsi].asym.regist[0], &watc_regname )
    .endif
    mov eax,newflg
    mov rcx,used
    or [rcx],eax
    mov [rsi].asym.string_ptr,LclDup( &watc_regname )
   .return( 1 )

watc_pcheck endp


watc_return proc __ccall private p:ptr dsym, buffer:string_t
    ret
watc_return endp


;-------------------------------------------------------------------------------
; FCT_WIN64
;-------------------------------------------------------------------------------

ms64_fcstart proc __ccall private uses rsi rdi rbx pp:dsym_t, numparams:int_t, start:int_t,
    tokenarray:token_t, value:ptr int_t

    ; v2.29: reg::reg id to fcscratch
    ; v2.34: changed to paralist

    mov rbx,pp
    mov eax,numparams
    mov esi,4
    mov edi,8
    .if ( [rbx].asym.langtype == LANG_VECTORCALL )
        mov esi,6
        mov edi,16
    .endif

    ; v2.04: VARARG didn't work

    mov rdx,[rbx].dsym.procinfo
    .if ( [rdx].proc_info.flags & PROC_HAS_VARARG )

        imul ecx,start,asm_tok
        add rcx,tokenarray

        .for ( eax = 0 : [rcx].asm_tok.token != T_FINAL : rcx += asm_tok )

            .if ( [rcx].asm_tok.token == T_COMMA )

                inc eax
            .endif
        .endf

    .else ; v2.31.22: extend call stack to 6 * [32|64]

        .for ( ecx = eax, rdx = [rdx].proc_info.paralist : rdx : ecx--, rdx = [rdx].dsym.prev )

            .if ( [rdx].asym.mem_type == MT_OWORD && !( [rdx].asym.sflags & S_ISVECTOR ) )

                ; __int128 register index++
                ;
                ; - rdx::rcx, r9::r8 -- +2 (0, 1)
                ; - rcx, r8::rdx, r9 -- +1 (1)
                ; - rcx, rdx, r9::r8 -- +1 (2)

                .if ( ecx < 4 && esi == 4 )
                    inc fcscratch
                .endif
            .endif

            .if ( [rdx].asym.total_size > edi )

                .switch ( [rdx].asym.mem_type )
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
    .if ( eax < esi )
        mov eax,esi
    .endif
    mov ecx,eax
    mul edi
    .if ( edi == 8 && ecx & 1 )
        add eax,edi
    .endif

    ; v2.31.24: skip stack alloc if inline
    .if ( ecx == esi && [rbx].asym.flag2 & S_ISINLINE )
        xor eax,eax
    .endif
    mov rdx,value
    mov [rdx],eax

    .if ( ModuleInfo.win64_flags & W64F_AUTOSTACKSP )

        mov rdx,CurrProc
        .if ( rdx )
            or [rdx].asym.sflags,S_STKUSED
        .endif
        mov rdx,sym_ReservedStack
        .if ( eax > [rdx].asym.value )
            mov [rdx].asym.value,eax
        .endif
    .elseif ( eax )
        AddLineQueueX( " sub rsp, %d", eax )
    .endif
    ;
    ; since Win64 fastcall doesn't push, it's a better/faster strategy to
    ; handle the arguments from left to right.
    ;
    ; v2.29 -- right to left
    ;
   .return FALSE

ms64_fcstart endp


ms64_fcend proc __ccall private pp:dsym_t, numparams:int_t, value:int_t

    ; use <value>, which has been set by ms64_fcstart()

    .if !( ModuleInfo.win64_flags & W64F_AUTOSTACKSP )

        .if value
            .if ( ModuleInfo.epilogueflags )
                AddLineQueueX( " lea rsp, [rsp+%d]", value )
            .else
                AddLineQueueX( " add rsp, %d", value )
            .endif
        .endif
    .endif
    ret
ms64_fcend endp


ms64_param proc __ccall private uses rsi rdi rbx pp:dsym_t, index:int_t, param:dsym_t, address:int_t,
        opnd:ptr expr, paramvalue:string_t, regs_used:ptr byte

   .new size:uint_t
   .new psize:uint_t
   .new reg:int_t = 0
   .new reg_64:int_t
   .new i:int_t
   .new i32:int_t
   .new destroyed:int_t = FALSE
   .new arg_offset:uint_t
   .new vector_call:byte = FALSE
   .new int128_arg:byte = FALSE

    mov rdi,opnd
    mov eax,index
    mul WordSize
    mov arg_offset,eax
    mov rsi,pp

    .if ( [rsi].asym.langtype == LANG_VECTORCALL )
        mov vector_call,TRUE
    .endif

    mov rbx,param
    .if abs_param( rsi, index, rbx, paramvalue )
        .return
    .endif

    mov psize,GetPSize(address, rbx, rdi)
    checkregoverwrite( rdi, regs_used, &reg, &destroyed, REGPAR_WIN64 )

    .if ( destroyed )

        asmerr( 2133 )
        mov rcx,regs_used
        mov byte ptr [rcx],0
    .endif

    .if ( [rbx].asym.mem_type == MT_TYPE )
        mov rbx,[rbx].asym.type
    .endif
    mov rdx,rbx
    mov esi,index
    .if ( !esi && fcscratch )
        dec fcscratch
    .endif
    add esi,fcscratch
    mov eax,psize

    .if ( esi >= 4 && ( address || eax > 8 ) )

        .if ( eax == 4 )
            mov ebx,T_EAX
        .else
            .if ( eax < 8 )

                asmerr( 2114, &[rsi+1] )

            .elseif ( vector_call && esi < 6 && ( [rbx].asym.mem_type & MT_FLOAT ||
                      [rbx].asym.mem_type == MT_YWORD || [rbx].asym.mem_type == MT_OWORD ) )

                .return CheckXMM( reg, paramvalue, regs_used, rbx, rdi, index )
            .endif
            mov ebx,T_RAX
        .endif
        mov rax,regs_used
        or byte ptr [rax],R0_USED

        ; v2.31.24 xmm to r64 -- vararg

        mov rdx,param
        .if ( psize == 16 && ( GetValueSp(reg) & OP_XMM ) )

          AddLineQueueX( " movq %r, %r", ebx, reg )

        ; v2.34.03 split register args for OWORD

        .elseif ( psize == 16 && [rdx].asym.mem_type == MT_OWORD && !vector_call )

            .if ( [rdi].expr.kind == EXPR_REG && !( [rdi].expr.flags & E_INDIRECT ) )

                mov rbx,[rdi].expr.base_reg
                mov ecx,[rbx].asm_tok.tokval
                .if ( [rbx-asm_tok].asm_tok.token == T_DBL_COLON )
                    mov edx,[rbx-asm_tok*2].asm_tok.tokval
                    AddLineQueueX(
                        " mov [rsp+%u], %r\n"
                        " mov [rsp+%u+8], %r", arg_offset, ecx, arg_offset, edx )
                .else
                    AddLineQueueX(
                        " mov [rsp+%u], %r\n"
                        " mov qword ptr [rsp+%u+8], 0", arg_offset, ecx, arg_offset )
                .endif
            .else
                AddLineQueueX(
                    " mov %r, qword ptr %s\n"
                    " mov [rsp+%u], %r\n"
                    " mov %r, qword ptr %s[8]\n"
                    " mov [rsp+%u+8], %r",
                    ebx, paramvalue, arg_offset, ebx, ebx, paramvalue, arg_offset, ebx )
            .endif
            .return( 1 )
        .else
            AddLineQueueX( " lea %r, %s", ebx, paramvalue )
        .endif
        AddLineQueueX( " mov [rsp+%u], %r", arg_offset, ebx )
       .return( 1 )
    .endif

    .if ( esi >= 4 )

        mov esi,index
        mov eax,[rdi].expr.kind
        .if ( eax == EXPR_CONST || ( eax == EXPR_ADDR && !( [rdi].expr.flags & E_INDIRECT ) &&
              [rdi].expr.mem_type == MT_EMPTY && [rdi].expr.inst != T_OFFSET ) )

            ; v2.06: support 64-bit constants for params > 4

            xor ecx,ecx
            .l8 [rdi].expr.value64
ifdef _WIN64
            .ifs ( rax > LONG_MAX || rax < LONG_MIN )
else
            .ifs ( ( !edx && eax > LONG_MAX ) || ( edx < 0 && eax < LONG_MIN ) )
endif
                inc ecx
            .endif
            .if ( psize == 8 && ecx )

                AddLineQueueX(
                    " mov dword ptr [rsp+%u], low32(%s)\n"
                    " mov dword ptr [rsp+%u+4], high32(%s)",
                    arg_offset, paramvalue, arg_offset, paramvalue )

            .else

                ; v2.11: no expansion if target type is a pointer and argument
                ; is an address part

                mov rax,[rdi].expr.sym
                .if ( [rbx].asym.mem_type == MT_PTR && [rdi].expr.kind == EXPR_ADDR &&
                      [rax].asym.state != SYM_UNDEFINED )

                    asmerr( 2114, &[rsi+1] )
                .endif
                mov eax,psize
                .switch ( eax )
                .case 1: mov ecx,T_BYTE : .endc
                .case 2: mov ecx,T_WORD : .endc
                .case 4
                    ;
                    ; added v2.33.57 for vararg
                    ; - this fails for NULL pointers as the upper value is not cleared
                    ; - the default size is 4
                    ;
                    .if ( [rdi].expr.value || !( [rbx].asym.sflags & S_ISVARARG ) )
                        mov ecx,T_DWORD
                        .endc
                    .endif
                .default
                    mov ecx,T_QWORD
                    .endc
                .endsw
                AddLineQueueX( " mov %r ptr [rsp+%u], %s", ecx, arg_offset, paramvalue )
            .endif

        .elseif ( [rdi].expr.kind == EXPR_FLOAT )

            .if ( esi < 6 && vector_call &&
                  ( [rbx].asym.mem_type & MT_FLOAT ||
                    [rbx].asym.mem_type == MT_YWORD ||
                    [rbx].asym.mem_type == MT_OWORD ) )

                .return CheckXMM( reg, paramvalue, regs_used, rbx, rdi, esi )
            .endif

            .if ( [rbx].asym.mem_type != MT_REAL4 ) ; added v2.31
                AddLineQueueX(
                    " mov dword ptr [rsp+%u+0], low32(%s)\n"
                    " mov dword ptr [rsp+%u+4], high32(%s)", arg_offset, paramvalue, arg_offset, paramvalue )
            .else
                AddLineQueueX( " mov dword ptr [rsp+%u], %s", arg_offset, paramvalue )
            .endif

        .else ; it's a register or variable

            .if ( [rdi].expr.kind == EXPR_REG && !( [rdi].expr.flags & E_INDIRECT ) )

                .if ( vector_call && esi < 6 && ( [rbx].asym.mem_type & MT_FLOAT ||
                        [rbx].asym.mem_type == MT_YWORD || [rbx].asym.mem_type == MT_OWORD ) )

                    .return CheckXMM( reg, paramvalue, regs_used, rbx, rdi, esi )
                .endif

                mov size,SizeFromRegister(reg)
                mov ecx,psize
                .if eax == ecx
                    mov eax,reg
                .else
                    .if ( eax > ecx || (eax < ecx && [rbx].asym.mem_type == MT_PTR ) )
                        ; added in v2.31.25
                        .if ( eax > ecx && eax == 16 && [rbx].asym.mem_type & MT_FLOAT )
                            .if ecx == 4
                                AddLineQueueX( " movss [rsp+%u], %r", arg_offset, reg )
                            .else
                                AddLineQueueX( " movsd [rsp+%u], %r", arg_offset, reg )
                            .endif
                            .return 1
                        .endif
                        mov psize,eax
                        asmerr( 2114, &[rsi+1] )
                    .endif
                    GetAccumulator( psize, regs_used )
                .endif
                mov i,eax

            .else
                .if ( [rdi].expr.mem_type == MT_EMPTY )
                    mov eax,4
                    ; added v2.31.25
                    .if ( [rdi].expr.inst == T_OFFSET ||
                         ( psize == 8 && [rbx].asym.mem_type == MT_PTR ) )
                        mov eax,8
                    .endif
                .else
                    SizeFromMemtype( [rdi].expr.mem_type, USE64, [rdi].expr.type )
                .endif
                mov size,eax
                mov i,GetAccumulator( psize, regs_used )
            .endif

            ; v2.11: no expansion if target type is a pointer

            mov i32,get_register( i, 4 )

            mov eax,size
            .if ( eax > psize || (eax < psize && [rbx].asym.mem_type == MT_PTR ) )
                asmerr( 2114, &[rsi+1] )
            .endif

            mov eax,size
            .if ( eax != psize )
                .if ( eax == 4 )
                    .if ( IS_SIGNED([rdi].expr.mem_type ) )
                        AddLineQueueX( " movsxd %r, %s", i, paramvalue )
                    .else
                        AddLineQueueX( " mov %r, %s", i, paramvalue )
                    .endif
                .else
                    mov ecx,T_MOVSX
                    .if !IS_SIGNED([rdi].expr.mem_type)
                        mov ecx,T_MOVZX
                    .endif
                    AddLineQueueX( " %r %r, %s", ecx, i, paramvalue )
                .endif
            .elseif ( [rdi].expr.kind != EXPR_REG || [rdi].expr.flags & E_INDIRECT )
                mov rcx,paramvalue
                .if ( word ptr [rcx] == "0" ||
                      ( [rdi].expr.kind == EXPR_CONST && [rdi].expr.value == 0 ) )
                    AddLineQueueX( " xor %r, %r", i32, i32 )
                .elseif [rdi].expr.kind == EXPR_CONST && [rdi].expr.hvalue == 0
                    AddLineQueueX( " mov %r, %s", i32, rcx )
                .else
                    AddLineQueueX( " mov %r, %s", i, rcx )
                .endif
            .endif
            AddLineQueueX( " mov [rsp+%u], %r", arg_offset, i )
        .endif
        .return 1
    .endif

    .if ( ( [rbx].asym.mem_type & MT_FLOAT ) || ( [rbx].asym.mem_type == MT_YWORD ) ||
          ( [rbx].asym.mem_type == MT_OWORD && ( vector_call || [rbx].asym.sflags & S_ISVECTOR ) ) )

        mov esi,index
        .return CheckXMM( reg, paramvalue, regs_used, rbx, rdi, esi )

    .elseif ( psize == 16 && [rbx].asym.mem_type == MT_OWORD &&
              !vector_call && !( [rbx].asym.sflags & S_ISVECTOR ) )

        mov int128_arg,TRUE
        .if fcscratch
            dec fcscratch
            dec esi
        .endif
    .endif

    mov ecx,[rdi].expr.kind
    xor ebx,ebx

    .if ( ecx == EXPR_REG && !( [rdi].expr.flags & E_INDIRECT ) )

        mov rax,[rdi].expr.base_reg
        .if ( [rax-asm_tok].asm_tok.token == T_DBL_COLON )

            ; case <reg>::<reg>

            mov ebx,[rax-asm_tok*2].asm_tok.tokval
        .endif
    .endif

    mov reg_64,ebx
    mov eax,psize

    .if ( !int128_arg && ( address || ( !ebx && eax > 8 ) ) ) ; psize > 8 shouldn't happen!

        .if ( eax >= 4 )

            .if ( eax > 4 )
                mov eax,4
            .else
                xor eax,eax
            .endif

            lea rcx,ms64_regs
            add rax,rcx
            movzx ecx,byte ptr [rsi+rax+2*4]

            .if ( psize == 16 && ( GetValueSp(reg) & OP_XMM ) )

                .if ( [rdx].asym.mem_type == MT_OWORD )

                    ; v2.33.07 :oword <-- xmm reg

                    lea ecx,[rsi+T_XMM0]
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
            asmerr( 2114, &[rsi+1] )
        .endif

    ret_regused:

        lea ecx,[rsi+RPAR_START]
        mov eax,1
        shl eax,cl
        mov rdx,regs_used
        or [rdx],al
       .return 1
    .endif

    mov rdx,[rdi].expr.sym
    .switch
    .case ( ecx == EXPR_REG ) ; register argument
        mov eax,8
        .if !( [rdi].expr.flags & E_INDIRECT )
            mov rax,[rdi].expr.base_reg
            mov eax,[rax].asm_tok.tokval
            mov reg,eax
            SizeFromRegister(eax)
        .elseif ( int128_arg )
            add eax,8
        .endif
        .endc
    .case ( ecx == EXPR_CONST )
        .if ( [rdi].expr.hvalue )
            mov psize,8 ; extend const value to 64
        .endif
        ; drop
    .case ( ecx == EXPR_FLOAT )
        mov eax,psize
       .endc
    .case ( [rdi].expr.mem_type != MT_EMPTY )
        SizeFromMemtype( [rdi].expr.mem_type, USE64, [rdi].expr.type )
       .endc
    .case ( ecx == EXPR_ADDR && ( !rdx || [rdx].asym.state == SYM_UNDEFINED ) )
        mov eax,psize
       .endc
    .default
        mov eax,4
        .if ( [rdi].expr.inst == T_OFFSET )
            mov eax,8
        .endif
    .endsw
    mov size,eax

    mov rdx,param
    mov rcx,paramvalue
    .if ( ( eax > psize && byte ptr [rcx] != '[' ) ||
          ( eax < psize && [rdx].asym.mem_type == MT_PTR ) )
        asmerr( 2114, &[rsi+1] )
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
    lea rbx,ms64_regs
    add rbx,rsi
    movzx ebx,byte ptr [rbx+rax*4]
    mov i32,ecx
    get_register( ebx, 4 )
    mov ecx,i32
    mov i32,eax

    ; optimization if the register holds the value already

    .if ( [rdi].expr.kind == EXPR_REG && !( [rdi].expr.flags & E_INDIRECT ) )

        .if ( GetValueSp(reg) & OP_R )

            ; case <reg>::<reg>

            .if ( reg_64 )

                .if ( ebx != reg )
                    AddLineQueueX( " mov %r, %r", ebx, reg )
                .endif

                lea rcx,ms64_regs
                movzx ebx,byte ptr [rcx+rsi+3*4+1]
                .if ( ebx != reg_64 )
                    AddLineQueueX( " mov %r, %r", ebx, reg_64 )
                .endif
                .return 1
            .endif

            mov eax,1
            mov ecx,i32
            .if ( ebx == reg || ecx == reg )
                .return
            .endif

            movzx ecx,GetRegNo( reg )
            mov eax,1
            shl eax,cl

            .if ( eax & REGPAR_WIN64 )

                lea ecx,[GetParmIndex(ecx)+RPAR_START]
                mov eax,1
                shl eax,cl
                mov rdx,regs_used

                .if ( [rdx] & al )
                    asmerr( 2133 )
                .endif
            .endif
        .endif
    .endif

    ; v2.11: allow argument extension

    mov eax,size
    .if ( eax < psize )

        .if ( eax == 4 )

            .if IS_SIGNED([rdi].expr.mem_type)
                AddLineQueueX( " movsxd %r, %s", ebx, paramvalue )
            .else
                lea rcx,ms64_regs
                movzx eax,byte ptr [rcx+rsi+2*4]
                AddLineQueueX( " mov %r, %s", eax, paramvalue )
            .endif
        .else
            mov ecx,T_MOVSX
            .if !IS_SIGNED( [rdi].expr.mem_type )
                mov ecx,T_MOVZX
            .endif
            AddLineQueueX( " %r %r, %s", ecx, ebx, paramvalue )
        .endif

    .else

        mov rdx,paramvalue
        .if ( word ptr [rdx] == "0" ||
              ( [rdi].expr.kind == EXPR_CONST && [rdi].expr.value == 0 ) )

            AddLineQueueX( " xor %r, %r", i32, i32 )

            .if ( int128_arg )

                lea rcx,ms64_regs
                .if ( [rdi].expr.h64_l == 0 && [rdi].expr.h64_h == 0 )

                    movzx ecx,byte ptr [rcx+rsi+2*4+1]
                    AddLineQueueX( " xor %r, %r", ecx, ecx )

                .else

                    movzx ecx,byte ptr [rcx+rsi+3*4+1]
                    movzx eax,[rdi].expr.flags
                    and   eax,E_NEGATIVE
                    elf64_const( ecx, T_HIGH64, [rdi].expr.hlvalue, paramvalue, eax )
                .endif
            .endif

        .elseif ( [rdi].expr.kind == EXPR_CONST && [rdi].expr.hvalue == 0 )

            AddLineQueueX( " mov %r, %s", i32, rdx )

            .if ( int128_arg )

                lea   rcx,ms64_regs
                movzx ecx,byte ptr [rcx+rsi+3*4+1]
                movzx eax,[rdi].expr.flags
                and   eax,E_NEGATIVE
                elf64_const( ecx, T_HIGH64, [rdi].expr.hlvalue, paramvalue, eax )
            .endif

        .elseif ( ecx && [rdi].expr.kind == EXPR_ADDR ) ; added v2.29

            mov rax,regs_used
            or  byte ptr [rax],R0_USED

            .if ( size == 3 )

                mov ebx,i32
                lea ecx,[rbx-(T_R8D-T_R8B)]
                .if ebx >= T_EAX && ebx <= T_EDI
                    lea ecx,[rbx-(T_EAX-T_AL)]
                .endif
                AddLineQueueX(
                    " mov %r, byte ptr %s[2]\n"
                    " shl %r, 16", ecx, rdx, ebx )

                .if ( ebx >= T_EAX && ebx <= T_EDI )
                    sub ebx,T_EAX-T_AX
                .else
                    sub ebx,T_R8D-T_R8W
                .endif
                AddLineQueueX( " mov %r, word ptr %s", ebx, paramvalue )

            .else

                AddLineQueueX( " mov %r, dword ptr %s", i32, rdx )
                .if ( size == 5 )
                    AddLineQueueX(" mov al, byte ptr %s[4]", paramvalue )
                .elseif ( size == 6 )
                    AddLineQueueX(" mov ax, word ptr %s[4]", paramvalue )
                .else
                    AddLineQueueX(
                        " mov al, byte ptr %s[6]\n"
                        " shl eax,16\n"
                        " mov ax, word ptr %s[4]", paramvalue, paramvalue )
                .endif
                AddLineQueueX(
                    " shl rax,32\n"
                    " or  %r,rax", rbx )
            .endif

        .elseif ( int128_arg && ( [rdi].expr.kind == EXPR_ADDR || ; added v2.34
                ( [rdi].expr.kind == EXPR_REG && ( [rdi].expr.flags & E_INDIRECT ) ) ) )

            lea   rcx,ms64_regs
            movzx ecx,byte ptr [rcx+rsi+3*4+1]
            AddLineQueueX(
                " mov %r, qword ptr %s\n"
                " mov %r, qword ptr %s[8]",
                ebx, paramvalue, ecx, paramvalue )

        .else

            mov rdx,pp
            mov rcx,[rdi].expr.sym

            .if ( rcx && index == 0 && [rdi].expr.mbr && [rdi].expr.kind == EXPR_ADDR &&
                  [rdi].expr.flags == E_INDIRECT && [rcx].asym.is_ptr && [rdx].asym.flag1 & S_METHOD )

                mov rbx,rcx
                AddLineQueueX( " mov rax, %s", [rcx].asym.name )
                mov rdx,[rdi].expr.mbr
                mov rcx,[rbx].asym.target_type
                AddLineQueueX( " mov rcx, [rax].%s.%s", [rcx].asym.name, [rdx].asym.name )

            .else
                mov rdx,param
                .if ( [rdi].expr.kind == EXPR_FLOAT && [rdx].asym.sflags & S_ISVARARG )
                    mov ebx,get_register( ebx, 8 ) ; added v2.31
                .endif
                AddLineQueueX( " mov %r, %s", ebx, paramvalue )
            .endif
        .endif
    .endif

    lea ecx,[rsi+RPAR_START]
    mov eax,1
    shl eax,cl
    mov rdx,regs_used
    or [rdx],al

   .return TRUE

ms64_param endp


; the MS Win64 fastcall ABI is strict: the first four parameters are
; passed in registers. If a parameter's value doesn't fit in a register,
; it's address is used instead. parameter 1 is stored in rcx/xmm0,
; then comes rdx/xmm1, r8/xmm2, r9/xmm3. The xmm regs are used if the
; param is a float/double (but not long double!).
; Additionally, there's space for the registers reserved by the caller on,
; the stack. On a function's entry it's located at [rsp+8] for param 1,
; [rsp+16] for param 2,... The parameter names refer to those stack
; locations, not to the register names.

ms64_pcheck proc __ccall private p:ptr dsym, paranode:ptr dsym, used:ptr int_t

    ; since the parameter names refer the stack-backup locations,
    ; there's nothing to do here!
    ; That is, if a parameter's size is > 8, it has to be changed
    ; to a pointer. This is to be done yet.

    .return( 0 )
ms64_pcheck endp


ms64_return proc __ccall private p:ptr dsym, buffer:string_t

    ; nothing to do, the caller cleans the stack
    ret

ms64_return endp

;-------------------------------------------------------------------------------
; FCT_ELF64
;-------------------------------------------------------------------------------

    assume rbx:token_t

elf64_fcstart proc __ccall private uses rsi rdi rbx pp:dsym_t, numparams:int_t, start:int_t,
    tokenarray:token_t, value:ptr int_t

    ; v2.28: xmm id to fcscratch

    mov rdi,pp
    mov rdx,[rdi].dsym.procinfo
    xor eax,eax
    xor esi,esi

    .if ( [rdx].proc_info.flags & PROC_HAS_VARARG )

        imul ebx,start,asm_tok
        add rbx,tokenarray

        .for ( : [rbx].token != T_FINAL : rbx += asm_tok )

            .if [rbx].token == T_REG

                .if GetValueSp([rbx].tokval) & OP_XMM

                    inc fcscratch
                .endif

            .elseif [rbx].asm_tok.token == T_ID

                .if SymFind([rbx].string_ptr)
                    .if ( [rax].asym.mem_type == MT_TYPE )
                        mov rax,[rax].asym.type
                    .endif
                    .if [rax].asym.mem_type & MT_FLOAT

                        inc fcscratch
                    .endif
                .endif
            .elseif [rbx].asm_tok.token == T_COMMA

                inc esi ; added v2.31
            .endif
        .endf
        mov eax,fcscratch
        sub esi,eax

    .else

        .for ( rdi = [rdx].proc_info.paralist : rdi : rdi = [rdi].dsym.prev )
            mov dl,[rdi].asym.mem_type
            .if ( dl == MT_TYPE )
                mov rdx,[rdi].asym.type
                mov dl,[rdx].asym.mem_type
            .endif
            .if ( dl & MT_FLOAT || dl == MT_YWORD )
                inc eax
            .else
                inc esi
            .endif
        .endf
    .endif

    mov rdx,value
    xor ecx,ecx
    .if esi > 6
        lea ecx,[rcx+rsi-6]
    .endif
    .if eax > 8
        lea ecx,[rcx+rax-8]
        mov eax,8
    .endif
    .if ( ecx & 1 && ModuleInfo.win64_flags & W64F_AUTOSTACKSP )
        mov elf64_valptr,rdx
    .endif
    mov [rdx],ecx
    ret

elf64_fcstart endp


elf64_fcend proc __ccall private pp:dsym_t, numparams:int_t, value:int_t

    ; use <value>, which has been set by elf64_fcstart()

    .if value
        AddLineQueueX( " add rsp, %u*8", value )
    .endif
    ret
elf64_fcend endp


elf64_const proc __ccall private reg:uint_t, pos:uint_t, val:qword, paramvalue:string_t, negative:uint_t

    .if ( dword ptr val[4] == 0 )
        mov eax,get_register( reg, 4 )
        .if ( dword ptr val == 0 )
            .if ( negative )
                AddLineQueueX( " mov %r, -1", reg )
            .else
                AddLineQueueX( " xor %r, %r", eax, eax )
            .endif
        .else
            AddLineQueueX( " mov %r, %s", eax, paramvalue )
        .endif
    .else
        AddLineQueueX( " mov %r, %r %s", reg, pos, paramvalue )
    .endif
    ret

elf64_const endp


; parameter for elf64 SYSCALL.
; the first 6 parameters are hold in registers: rdi, rsi, rdx, rcx, r8, r9
; for non-float arguments, xmm0..xmm31 for float arguments.

    assume rdx:asym_t
    assume rdi:expr_t

elf64_param proc __ccall private uses rsi rdi rbx pp:dsym_t, index:int_t, param:dsym_t,
        address:int_t, opnd:ptr expr, paramvalue:string_t, regs_used:ptr byte

   .new size:uint_t
   .new psize:uint_t
   .new reg:int_t
   .new i:int_t
   .new i32:int_t
   .new destroyed:int_t = FALSE ; added v2.31
   .new stack:int_t = FALSE     ; added v2.31

    mov rdi,opnd
    mov rcx,paramvalue

    .if ( byte ptr [rcx] == 0 )
        .return TRUE
    .endif

    mov rax,elf64_valptr
    .if ( rax != NULL ) ; if arg count is odd..

        ; last argument: align 16

        mov elf64_valptr,0
        inc dword ptr [rax] ; value++
        AddLineQueue( " sub rsp,8" )
    .endif

    mov psize,GetPSize( address, param, rdi )
    mov rdx,param

    .if ( [rdx].sflags & S_ISVARARG )

        .if ( fcscratch && ( eax == 16 || [rdi].mem_type & MT_FLOAT ) )

            dec fcscratch
            mov esi,fcscratch
            lea ebx,[rsi+T_XMM0]
        .else

            mov esi,index
            sub esi,fcscratch
            .if esi < 6
                shr eax,1
                cmp eax,4
                cmc
                sbb eax,0
                imul eax,eax,6
                lea rcx,elf64_regs
                add rcx,rax
                movzx ebx,byte ptr [rsi+rcx]
            .else
                inc stack
            .endif
        .endif
    .else
        movzx ebx,[rdx].regist[0]
        movzx esi,[rdx].regist[2]
    .endif

    mov rcx,pp
    .if ( [rdx].sflags & S_ISVARARG && [rcx].asym.flag2 & S_ISINLINE )
        .return 1
    .endif

    .if ( [rdx].mem_type == MT_ABS )

        LclDup( paramvalue )
        mov rdx,param
        mov [rdx].name,rax
       .return 1
    .endif

    movzx eax,[rdx].mem_type
    .if  ( eax == MT_EMPTY && ( [rdx].sflags & S_ISVARARG ) &&
           [rdi].kind == EXPR_ADDR && [rdi].mem_type & MT_FLOAT )

        .if SymFind( paramvalue )
            mov rdx,rax
        .else
            mov rdx,param
        .endif
    .endif

    .if ( [rdx].asym.mem_type == MT_TYPE )
        mov rdx,[rdx].asym.type
    .endif
    movzx eax,[rdx].asym.mem_type

    .if ( !( eax & MT_FLOAT || eax == MT_YWORD ) && esi >= 6 )

        .return 0 .if !stack
        mov ebx,T_RAX
    .endif

    assume rdx:nothing
    .new sym:asym_t = rdx

    .if ( eax & MT_FLOAT || eax == MT_YWORD )

        xor ecx,ecx
        mov rax,[rdi].base_reg
        .if rax
            mov ecx,[rax].asm_tok.tokval
        .endif
        .if ( esi < 8 )
            .return CheckXMM( ecx, paramvalue, regs_used, rdx, rdi, esi )
        .else
            inc stack
        .endif
    .endif
    mov i32,get_register( ebx, 4 )

    .repeat

        .if ( address )

            .if ( SizeFromRegister( ebx ) == 8 )

                AddLineQueueX( " lea %r, %s", ebx, paramvalue )
                .if stack

                    AddLineQueueX( " push %r", ebx )
                    mov rcx,regs_used
                    or byte ptr [rcx],R0_USED
                   .return 1
                .endif
            .else
                mov eax,index
                inc eax
                asmerr( 2114, eax )
            .endif
            .break
        .endif

        mov rdx,[rdi].sym
        mov ecx,[rdi].kind

        .if ( ecx == EXPR_REG ) ; register argument

            mov eax,8
            .if !( [rdi].flags & E_INDIRECT )

                mov rax,[rdi].base_reg
                mov ecx,[rax].asm_tok.tokval
                mov reg,ecx
                SizeFromRegister( ecx )
            .endif

        .elseif ( ecx == EXPR_CONST )

            mov eax,[rdi].hvalue
            .if eax && eax != -1
                mov psize,8 ; extend const value to 64
            .endif
            mov eax,psize

        .elseif ( ecx == EXPR_FLOAT )

            mov eax,psize

        .elseif ( [rdi].mem_type != MT_EMPTY )

            SizeFromMemtype( [rdi].mem_type, USE64, [rdi].type )

        .elseif ( ecx == EXPR_ADDR && [rdx].asym.state == SYM_UNDEFINED )

            mov eax,psize

        .else
            mov eax,4
            .if ( [rdi].inst == T_OFFSET )
                mov eax,8
            .endif
        .endif
        mov size,eax

        mov rdx,param
        .if ( eax == 16 && stack && [rdi].kind == EXPR_REG )

            AddLineQueue( " lea rsp,[rsp-8]" )
            .if ( reg < T_XMM16 )
                mov rdx,param
                .if [rdx].asym.mem_type == MT_REAL8
                    AddLineQueueX(" movsd [rsp], %s", paramvalue )
                .else
                    AddLineQueueX(" movss [rsp], %s", paramvalue )
                .endif
            .else
                AddLineQueueX( " vmovq [rsp], %s", paramvalue )
            .endif
            .return 1

        .elseif ( eax > psize || ( eax < psize && [rdx].asym.mem_type == MT_PTR ) )

            mov eax,index
            inc eax
            asmerr( 2114, eax )
        .endif

        ; optimization if the register holds the value already

        .if ( [rdi].kind == EXPR_REG && !( [rdi].flags & E_INDIRECT ) )

            .if GetValueSp(reg) & OP_XMM

                mov rax,[rdi].base_reg
                mov ecx,[rax].asm_tok.tokval
               .return CheckXMM( ecx, paramvalue, regs_used, param, rdi, esi )
            .endif

            .if GetValueSp(reg) & OP_R

                ; added v2.31.03

                movzx ecx,GetRegNo(reg)
                mov eax,1
                shl eax,cl
                and eax,REGPAR_ELF64 ; regs 1, 2, 6, 7, 8 and 9
                mov rdx,regs_used

                .if eax

                    lea     rax,elf64_param_index
                    movzx   ecx,byte ptr [rax+rcx]
                    lea     ecx,[rcx+ELF64_START]
                    mov     eax,1
                    shl     eax,cl

                    .if ( [rdx] & al )
                        mov destroyed,TRUE
                    .endif
                .else
                    .if ( byte ptr [rdx] & R0_USED )
                        .if ( GetValueSp(reg) & OP_A || reg == T_AH )
                            mov destroyed,TRUE
                        .endif
                    .endif
                .endif

                .if destroyed

                    asmerr( 2133 )
                    mov rdx,regs_used
                    mov byte ptr [rdx],0
                .endif

                mov rax,[rdi].base_reg

                ; case <reg>::<reg>

                .if ( psize == 16 && size == 8 && [rax-asm_tok].asm_tok.token == T_DBL_COLON )

                    mov ecx,[rax].asm_tok.tokval
                    mov reg,[rax-asm_tok*2].asm_tok.tokval
                    .if ( ebx != ecx )
                        AddLineQueueX( " mov %r, %r", ebx, ecx )
                    .endif
                    lea rcx,elf64_regs
                    movzx ebx,byte ptr [rcx+rsi+3*6+1]
                    .if ( ebx != reg )
                        AddLineQueueX( " mov %r, %r", ebx, reg )
                    .endif
                    .break
                .endif

                .if stack

                    AddLineQueueX( " push %r", get_register( reg, 8 ) )
                   .return 1
                .endif

                .return 1 .if ( ebx == reg )

                .if ( [rdi].mem_type == MT_EMPTY )

                    ; get type info (signed)

                    mov rcx,param
                    mov [rdi].mem_type,[rcx].asym.mem_type
                .endif

                movzx ecx,GetRegNo(reg)
                mov eax,1
                shl eax,cl

                .if ( eax & REGPAR_ELF64 )

                    ; convert register number to param number:

                    and ecx,0xF
                    lea rax,elf64_param_index
                    movzx eax,byte ptr [rax+rcx]

                    lea ecx,[rax+ELF64_START]
                    mov eax,1
                    shl eax,cl
                    mov rcx,regs_used
                    .if ( [rcx] & al )
                        asmerr( 2133 )
                    .endif
                .endif
            .endif
        .endif

        ; allow argument extension

        mov eax,size
        .if ( eax < psize )

            .if ( eax == 4 )

                .if IS_SIGNED( [rdi].mem_type )

                    AddLineQueueX( " movsxd %r, %s", ebx, paramvalue )
                .else
                    AddLineQueueX( " mov %r, %s", i32, paramvalue )
                .endif
            .else
                mov ecx,T_MOVSX
                .if !( IS_SIGNED( [rdi].mem_type ) )
                    mov ecx,T_MOVZX
                .endif
                AddLineQueueX( " %r %r, %s", ecx, i32, paramvalue )
            .endif

            .if ( stack )

                AddLineQueueX( " push %r", ebx )
                mov rcx,regs_used
                or  byte ptr [rcx],R0_USED
               .return 1
            .endif
            .break
        .endif

        mov rcx,paramvalue
        .if ( stack )

            .if ( [rdi].expr.kind == EXPR_FLOAT )

                mov rax,regs_used
                or  byte ptr [rax],R0_USED
                mov rdx,param
                mov eax,T_RAX
                .if ( [rdx].asym.mem_type == MT_REAL2 )
                    mov eax,T_AX
                .elseif ( [rdx].asym.mem_type == MT_REAL4 )
                    mov eax,T_EAX
                .endif
                AddLineQueueX(
                    " mov %r, %s\n"
                    " push rax", eax, rcx )
            .else
                AddLineQueueX(" push %s", rcx )
            .endif
            .return 1
        .endif

        .if ( word ptr [rcx] == "0" ||
              ( [rdi].kind == EXPR_CONST && [rdi].l64_l == 0 && [rdi].l64_h == 0 ) )

            AddLineQueueX( " xor %r, %r", i32, i32 )
            .break .if ( size != 16 )

            lea rcx,elf64_regs
            .if ( [rdi].h64_l == 0 && [rdi].h64_h == 0 )
                ; -0
                movzx ebx,byte ptr [rcx+rsi+2*6+1]
                AddLineQueueX( " xor %r, %r", ebx, ebx )
               .break
            .endif
            movzx ebx,byte ptr [rcx+rsi+3*6+1]
            movzx eax,[rdi].flags
            and eax,E_NEGATIVE
            elf64_const( ebx, T_HIGH64, [rdi].hlvalue, paramvalue, eax )
           .break
        .endif

        .if ( [rdi].kind == EXPR_CONST && [rdi].hvalue == 0 )

            AddLineQueueX( " mov %r, %s", i32, paramvalue )

            .break .if ( size != 16 )

            lea rcx,elf64_regs
            movzx ebx,byte ptr [rcx+rsi+3*6+1]
            movzx eax,[rdi].flags
            and eax,E_NEGATIVE
            elf64_const( ebx, T_HIGH64, [rdi].hlvalue, paramvalue, eax )
           .break
        .endif

        .if ( eax != 16 )

            mov rdx,param
            .if ( [rdi].expr.kind == EXPR_FLOAT && [rdx].asym.sflags & S_ISVARARG )
                mov ebx,get_register( ebx, 8 ); added v2.31
            .endif
            AddLineQueueX( " mov %r, %s", ebx, paramvalue )
           .break
        .endif

        mov edx,ebx
        lea rcx,elf64_regs
        movzx ebx,byte ptr [rcx+rsi+3*6+1]

        .if ( [rdi].kind == EXPR_CONST  )

            mov eax,edx
            elf64_const( eax, T_LOW64, [rdi].llvalue, paramvalue, 0 )
            movzx eax,[rdi].flags
            and eax,E_NEGATIVE
            elf64_const( ebx, T_HIGH64, [rdi].hlvalue, paramvalue, eax )
           .break
        .endif
        AddLineQueueX(
            " mov %r, qword ptr %s\n"
            " mov %r, qword ptr %s[8]", edx, paramvalue, ebx, paramvalue )
    .until 1

    .if ( esi < 6 )

        lea ecx,[rsi+ELF64_START]
        mov eax,1
        shl eax,cl
        mov rcx,regs_used
        or [rcx],al
    .endif
    .return TRUE

elf64_param endp


    assume rsi:asym_t

elf64_pcheck proc __ccall private uses rsi rdi rbx pProc:dsym_t, paranode:dsym_t, used:ptr int_t

  local regname[32]:sbyte
  local reg:int_t

    mov rbx,used
    mov rsi,paranode
    SizeFromMemtype( [rsi].mem_type, [rsi].Ofssize, [rsi].type )
    mov ecx,[rbx]
    mov dl,[rsi].mem_type
    .if ( [rsi].mem_type == MT_TYPE )
        mov rdx,[rsi].type
        mov dl,[rdx].asym.mem_type
    .endif

    .switch
      .case ( [rsi].sflags & S_ISVARARG )
        xor eax,eax
        mov [rsi].string_ptr,rax
       .return

      .case ( dl & MT_FLOAT || dl == MT_YWORD )
        movzx ecx,ch
        inc byte ptr [rbx+1]
        .if ( ecx > 7 )
            mov [rsi].regist[2],cx
            add ecx,(T_XMM8 - T_XMM7 - 1)
            mov [rsi].regist[0],cx
            xor eax,eax
            mov [rsi].string_ptr,rax
            .return
        .endif
        .if eax == 64
            lea eax,[rcx+T_ZMM0]
        .elseif eax == 32
            lea eax,[rcx+T_YMM0]
        .else
            lea eax,[rcx+T_XMM0]
        .endif
        .endc

      .case ( al > 16 )
        xor eax,eax
        mov [rsi].string_ptr,rax
       .return

      .case ( al == 16 || dl == MT_OWORD )
        .if ( cl < 5 )
            movzx ecx,cl
            lea rdx,elf64_regs
            movzx eax,byte ptr [rdx+rcx+3*6]
            add byte ptr [rbx],2
           .endc
        .endif

      .case ( cl > 5 )
        movzx ecx,cl
        mov [rsi].regist[0],T_RAX
        mov [rsi].regist[2],cx
        inc byte ptr [rbx]
        xor eax,eax
        mov [rsi].string_ptr,rax
       .return

      .default
        movzx ecx,cl
        shr eax,1
        cmp eax,4
        cmc
        sbb eax,0
        imul eax,eax,6
        lea rdx,elf64_regs
        add rdx,rax
        movzx eax,byte ptr [rcx+rdx]
        inc byte ptr [rbx]
       .endc
    .endsw

    lea rdi,regname
    mov [rsi].state,SYM_TMACRO
    mov [rsi].regist[0],ax
    mov [rsi].regist[2],cx
    mov [rsi].string_ptr,LclDup( GetResWName(eax, rdi) )
   .return TRUE

elf64_pcheck endp

    assume rsi:nothing


;-------------------------------------------------------------------------------
; FCT_VEC32
;-------------------------------------------------------------------------------

vc32_fcstart proc __ccall private pp:dsym_t, numparams:int_t, start:int_t,
    tokenarray:token_t, value:ptr int_t

    mov rcx,pp
    .for ( edx = 0, rax = [rcx].dsym.procinfo,
           rax = [rax].proc_info.paralist : rax : rax = [rax].dsym.nextparam )

        .if ( [rax].asym.state == SYM_TMACRO ||
              ( [rax].asym.state == SYM_STACK && [rax].asym.total_size <= 16 ) )

            inc fcscratch
        .else
            add edx,4
        .endif
    .endf
    mov rax,value
    mov [rax],edx
   .return TRUE

vc32_fcstart endp


vc32_param proc __ccall private uses rsi rdi rbx pp:dsym_t, index:int_t, param:dsym_t, address:int_t,
    opnd:ptr expr, paramvalue:string_t, r0used:ptr byte

   .new size:int_t
   .new value[64]:char_t

    mov rsi,param
    xor eax,eax

    mov cl,[rsi].asym.state
    .if ( !( cl == SYM_TMACRO || cl == SYM_STACK || !fcscratch ) ||
           ( cl == SYM_STACK && [rsi].asym.total_size > 16 ) )
        .return
    .endif

    dec fcscratch
    mov edx,fcscratch
    .if ( cl == SYM_STACK || edx > 1 || [rsi].asym.mem_type & MT_FLOAT )
        .return .if ( edx > 5 )
        lea ebx,[rdx+T_XMM0]
    .else
        .return .if ( edx > 1 )
        lea rcx,ms32_regs
        movzx ebx,byte ptr [rcx+rdx]
    .endif

    .if ( address )
        .if edx < 2
            AddLineQueueX( " lea %r, %s", ebx, paramvalue )
        .else
            AddLineQueueX(
                " lea eax, %s\n"
                " push eax", paramvalue )
        .endif
    .else

        SizeFromMemtype( [rsi].asym.mem_type, USE_EMPTY, [rsi].asym.type )
        mov rdi,opnd

        .if ( ebx < T_XMM0 && [rdi].expr.kind != EXPR_CONST && eax < 4 )

            mov rcx,[rdi].expr.base_reg
            .if ( !eax && [rdi].expr.kind == EXPR_REG && !( [rdi].expr.flags & E_INDIRECT ) && rcx )

                .if ( [rcx].asm_tok.tokval == ebx )

                    inc eax
                    .return
                .endif

                AddLineQueueX( " mov %r, %s", ebx, paramvalue )
               .return 1
            .endif
            mov ecx,T_MOVSX
            .if !( [rsi].asym.mem_type & MT_SIGNED )
                mov ecx,T_MOVZX
            .endif
            AddLineQueueX( " %r %r, %s", ecx, ebx, paramvalue )
        .else

            mov rcx,[rdi].expr.base_reg
            .if ( [rdi].expr.kind == EXPR_REG && !( [rdi].expr.flags & E_INDIRECT ) && rcx )

                .if ( [rcx].asm_tok.tokval == ebx )

                    inc eax
                    .return
                .endif
            .endif

            .if ( [rdi].expr.kind == EXPR_CONST )

                .if ( index > 1 || ebx >= T_XMM0 )
                    .return 0
                .endif
                AddLineQueueX( " mov %r, %s", ebx, paramvalue )

            .elseif ( [rdi].expr.kind == EXPR_FLOAT )

                mov rdx,param
                mov al,[rdx].asym.mem_type

                .switch al
                .case MT_REAL4
                    mov rax,r0used
                    or  byte ptr [rax],R0_USED
                    AddLineQueueX(
                        " mov eax, %s\n"
                        " movd %r, eax", paramvalue, ebx )
                    .endc
                .case MT_REAL8
                    AddLineQueueX(
                        " pushd high32(%s)\n"
                        " pushd low32 (%s)\n"
                        " movq %r, [rsp]\n"
                        " add esp, 8", paramvalue, paramvalue, ebx )
                    .endc
                .case MT_REAL16
                    xor eax,eax
                    mov rdx,paramvalue
                    .if ( [rdi].expr.flags & E_NEGATIVE )
                        inc eax
                    .endif
                    mov rcx,[rdi].expr.float_tok
                    .if rcx
                        mov rdx,[rcx].asm_tok.string_ptr
                    .endif
                    atofloat( rdi, rdx, 16, eax, 0 )
                    AddLineQueueX(
                        " pushd high32(0x%16lx)\n"
                        " pushd low32 (0x%16lx)\n"
                        " pushd high32(0x%16lx)\n"
                        " pushd low32 (0x%16lx)\n"
                        " movups %r, [rsp]\n"
                        " add esp, 16",
                        [rdi].expr.hlvalue, [rdi].expr.hlvalue,
                        [rdi].expr.llvalue, [rdi].expr.llvalue, ebx )
                    .endc
                .default
                    AddLineQueueX( " movaps %r, %s", ebx, paramvalue )
                    .endc
                .endsw
            .else
                mov rdx,param
                .if [rdx].asym.mem_type == MT_REAL4
                    AddLineQueueX( " movss %r, %s", ebx, paramvalue )
                .elseif [rdx].asym.mem_type == MT_REAL8
                    AddLineQueueX( " movsd %r, %s", ebx, paramvalue )
                .elseif eax == 16
                    AddLineQueueX( " movaps %r, %s", ebx, paramvalue )
                .else
                    .return 0
                .endif
            .endif
        .endif
        .if ( ebx == T_AX )
            mov rax,r0used
            or byte ptr [rax],R0_USED
        .endif
    .endif
    .return( 1 )

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

vc32_pcheck proc __ccall private uses rsi rdi rbx p:ptr dsym, paranode:ptr dsym, used:ptr int_t

   .new regname[32]:char_t

    mov rdi,used
    mov rsi,paranode
    mov ebx,SizeFromMemtype( [rsi].asym.mem_type, [rsi].asym.Ofssize, [rsi].asym.type )

    .if ( [rsi].asym.mem_type & MT_FLOAT )
        mov ebx,16
    .endif
    .if ( ebx < 4 )
        mov ebx,4
    .endif

    mov ecx,[rdi]
    .if ( ( ebx != 4 && ebx != 16 ) ||
          ( ( ebx == 4 && ecx > 1 ) || ( ebx == 16 && ecx > 5 ) ) )
        .return( 0 )
    .endif

    mov eax,ecx
    add ecx,T_XMM0
    .if ( ebx == 4 )
        lea rdx,ms32_regs
        movzx ecx,byte ptr [rdx+rax]
    .endif
    mov [rsi].asym.state,SYM_TMACRO
    mov [rsi].asym.regist[0],cx
    mov [rsi].asym.string_ptr,LclDup( GetResWName( ecx, &regname ) )
    inc dword ptr [rdi]
   .return( 1 )

vc32_pcheck endp


    assume rdi:nothing
    assume rbx:nothing

vc32_return proc __ccall private uses rdi rbx p:ptr dsym, buffer:string_t

    mov rcx,p
    mov rdx,[rcx].dsym.procinfo
    xor ebx,ebx
    .for ( rdi = [rdx].proc_info.paralist: rdi: rdi = [rdi].dsym.nextparam )
        .if ( [rdi].asym.state != SYM_TMACRO ) ;; v2.34.35: used by ms32..
            add ebx,ROUND_UP( [rdi].asym.total_size, CurrWordSize )
        .endif
    .endf
    .if ( ebx )
        add tstrlen(buffer),buffer
        mov ecx,'t'
        .if ( ModuleInfo.radix == 10 )
            xor ecx,ecx
        .endif
        tsprintf( rax, "%d%c", ebx, ecx )
    .endif
    ret

vc32_return endp


;-------------------------------------------------------------


abs_param proc __ccall private uses rbx pp:dsym_t, index:int_t, param:dsym_t, paramvalue:string_t

    ; skip arg if :vararg and inline

    mov rcx,pp
    mov rbx,param
    .if ( [rbx].asym.sflags & S_ISVARARG && [rcx].asym.flag2 & S_ISINLINE )
        .return( 1 )
    .endif

    ; skip loading class pointer if :vararg and inline

    .if ( [rcx].asym.flag2 & S_ISINLINE && [rcx].asym.flag1 & S_METHOD && !index )
        mov rdx,[rcx].dsym.procinfo
        .if ( [rdx].proc_info.flags & PROC_HAS_VARARG )
            .return( 1 )
        .endif
    .endif

    ; skip arg if :abs

    .if ( [rbx].asym.mem_type == MT_ABS )
        mov [rbx].asym.name,LclDup( paramvalue )
       .return( 1 )
    .endif
    .return( 0 )

abs_param endp


; parameter for Win64 FASTCALL.
; the first 4 parameters are hold in registers: rcx, rdx, r8, r9 for non-float arguments,
; xmm0, xmm1, xmm2, xmm3 for float arguments. If parameter size is > 8, the address of
; the argument is used instead of the value.

checkregoverwrite proc __ccall private uses rsi rdi rbx opnd:ptr expr,
        regs_used:ptr byte, reg:ptr dword, destroyed:ptr byte, rmask:dword

    mov rdi,opnd
    xor esi,esi

    .if ( [rdi].expr.base_reg )

        mov rbx,[rdi].expr.base_reg
        mov ebx,[rbx].asm_tok.tokval
        mov rax,reg
        mov [rax],ebx

        .if ( GetValueSp(ebx) & OP_R )

            movzx ecx,GetRegNo(ebx)
            mov eax,1
            shl eax,cl
            and eax,rmask

            .if ( eax )

                lea ecx,[GetParmIndex(ecx)+RPAR_START]
                mov eax,1
                shl eax,cl
                mov rcx,regs_used
                .if [rcx] & al
                    mov esi,1
                .endif
            .else
                mov rcx,regs_used
                .if ( byte ptr [rcx] & R0_USED )
                    .if ( GetValueSp(ebx) & OP_A || ebx == T_AH )
                        mov esi,TRUE
                    .endif
                .endif
            .endif
        .endif
    .endif

    .if ( [rdi].expr.kind == EXPR_ADDR && [rdi].expr.idx_reg )

        mov rbx,[rdi].expr.idx_reg
        mov ebx,[rbx].asm_tok.tokval

        .if ( GetValueSp(ebx) & OP_R )

            movzx ecx,GetRegNo(ebx)
            mov eax,1
            shl eax,cl
            and eax,rmask

            .if ( eax )

                lea ecx,[GetParmIndex(ecx)+RPAR_START]
                mov eax,1
                shl eax,cl
                mov rcx,regs_used

                .if ( [rcx] & al )
                    mov esi,TRUE
                .endif
            .else
                mov rcx,regs_used
                .if ( byte ptr [rcx] & R0_USED )
                    .if ( GetValueSp(ebx) & OP_A || ebx == T_AH )
                        mov esi,TRUE
                    .endif
                .endif
            .endif
        .endif
    .endif
    mov rax,destroyed
    mov [rax],esi
    ret

checkregoverwrite endp


GetPSize proc __ccall private uses rdi address:int_t, param:asym_t, opnd:expr_t

    mov rdx,param
    mov rdi,opnd

    ; v2.11: default size is 32-bit, not 64-bit

    .if ( [rdx].asym.sflags & S_ISVARARG )

        xor eax,eax
        .if ( address || [rdi].expr.inst == T_OFFSET )
            mov eax,8
        .elseif ( [rdi].expr.kind == EXPR_REG )
            .if !( [rdi].expr.flags & E_INDIRECT )
                mov rax,[rdi].expr.base_reg
                SizeFromRegister([rax].asm_tok.tokval)
            .else
                mov eax,8
            .endif
        .elseif ( [rdi].expr.kind == EXPR_FLOAT && [rdi].expr.mem_type == MT_REAL16 )

        .elseif ( [rdi].expr.mem_type != MT_EMPTY )
            SizeFromMemtype( [rdi].expr.mem_type, USE64, [rdi].expr.type )
        .endif
        .if eax < 4
            mov eax,4
        .endif
    .else
        mov rcx,rdx
        SizeFromMemtype( [rcx].asym.mem_type, USE64, [rcx].asym.type )
    .endif
    ret

GetPSize endp


CheckXMM proc __ccall private uses rsi rdi rbx reg:int_t, paramvalue:string_t,
        regs_used:ptr byte, param:dsym_t, opnd:ptr expr, index:int_t

   .new buffer[64]:char_t
   .new sign:byte

    ; v2.04: check if argument is the correct XMM register already

    mov rdi,opnd
    mov esi,index

    .if ( [rdi].expr.kind == EXPR_REG && !( [rdi].expr.flags & E_INDIRECT ) )

        mov ecx,GetValueSp( reg )

        .if ( ecx & ( OP_XMM or OP_YMM or OP_ZMM ) )

            lea eax,[rsi+T_XMM0]
            .if ( ecx & OP_YMM )
                lea eax,[rsi+T_YMM0]
            .elseif ( ecx & OP_ZMM )
                lea eax,[rsi+T_ZMM0]
            .endif

            .if ( eax != reg )

                mov rdx,param
                .if ( reg < T_XMM16 && ecx & OP_XMM )
                    .if ( [rdx].asym.mem_type == MT_REAL4 )
                        AddLineQueueX( " movss %r, %r", eax, reg )
                    .elseif ( [rdx].asym.mem_type == MT_REAL8 )
                        AddLineQueueX( " movsd %r, %r", eax, reg )
                    .else
                        AddLineQueueX( " movaps %r, %r", eax, reg )
                    .endif
                .else
                    .if ( [rdx].asym.mem_type == MT_REAL4 )
                        AddLineQueueX( " vmovss %r, %r, %r", eax, eax, reg )
                    .elseif ( [rdx].asym.mem_type == MT_REAL8 )
                        AddLineQueueX( " vmovsd %r, %r, %r", eax, eax, reg )
                    .else
                        AddLineQueueX( " vmovaps %r, %r", eax, reg )
                    .endif
                .endif
            .endif
            .return TRUE
        .endif
    .endif

    mov rdx,param
    lea ebx,[rsi+T_XMM0]
    .if ( [rdi].expr.kind == EXPR_FLOAT )

        mov rax,[rdi]
        or  rax,[rdi+8]
ifndef _WIN64
        or  eax,[rdi+4]
        or  eax,[rdi+12]
endif
        .switch pascal
        .case ZERO?
            AddLineQueueX( " xorps %r, %r", ebx, ebx )
        .case ( [rdx].asym.mem_type == MT_REAL10 || [rdx].asym.mem_type == MT_REAL16 )
            mov esi,10
            .if ( [rdx].asym.mem_type == MT_REAL16 )
                mov esi,16
            .endif
            CreateFloat( esi, rdi, &buffer )
            .if ( esi == 10 )
                AddLineQueueX( " movaps %r, xmmword ptr %s", ebx, &buffer )
            .else
                AddLineQueueX( " movaps %r, %s", ebx, &buffer )
            .endif
        .case ( [rdx].asym.mem_type == MT_REAL2 )
            mov rax,regs_used
            or  byte ptr [rax],R0_USED
            AddLineQueueX(
                " mov ax, %s\n"
                " movd %r, eax", paramvalue, ebx )
        .case ( [rdx].asym.mem_type == MT_REAL4 )
            AddLineQueueX( " movd %r, %s", ebx, paramvalue )
        .case ( [rdx].asym.mem_type == MT_REAL8 )
            AddLineQueueX( " movq %r, %s", ebx, paramvalue )
        .endsw

    .else
        .switch pascal
        .case ( [rdx].asym.mem_type == MT_REAL2 )
            mov rax,regs_used
            or  byte ptr [rax],R0_USED
            AddLineQueueX(
                " movzx eax, word ptr %s\n"
                " movd %r, eax", paramvalue, ebx )
        .case ( [rdx].asym.mem_type == MT_REAL4 )
            AddLineQueueX( " movd %r, %s", ebx, paramvalue )
        .case ( [rdx].asym.mem_type == MT_REAL8 )
            AddLineQueueX( " movq %r, %s", ebx, paramvalue )
        .case ( [rdx].asym.mem_type == MT_REAL10 )
            AddLineQueueX( " movaps %r, xmmword ptr %s", ebx, paramvalue )
        .default
            AddLineQueueX( " movaps %r, %s", ebx, paramvalue )
        .endsw
    .endif
    .return TRUE

CheckXMM endp


get_register proc __ccall reg:int_t, size:int_t

    lea  rcx,SpecialTable
    imul eax,reg,special_item
    mov  edx,size
    .if ( [rcx+rax].special_item.value & OP_XMM )
        mov edx,16
    .endif
    movzx ecx,[rcx+rax].special_item.bytval
    mov eax,reg

    .return .if ( ecx > 15 )
    .switch rdx
    .case 1
        .if ( ecx < 4 )
            .return( &[rcx+T_AL] )
        .endif
        .return( &[rcx+T_SPL-4] )
    .case 2
        .if ( ecx < 8 )
            .return( &[rcx+T_AX] )
        .endif
        .return( &[rcx+T_R8W-8] )
    .case 4
        .if ( ecx < 8 )
            .return( &[rcx+T_EAX] )
        .endif
        .return( &[rcx+T_R8D-8] )
    .case 8
        .if ( ecx < 8 )
            .return( &[rcx+T_RAX] )
        .endif
        .return( &[rcx+T_R8-8] )
    .endsw
    ret
get_register endp


GetAccumulator proc fastcall private psize:uint_t, regs:ptr

    shr ecx,1
    lea eax,[rcx*8+T_AL]
    cmp ecx,4
    sbb ecx,ecx
    and eax,ecx
    not ecx
    and ecx,T_RAX
    or  eax,ecx
    or  byte ptr [rdx],R0_USED
    ret

GetAccumulator endp

    END
