; _ALLOCA64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; void *_alloca64(UINT dwSize, UINT ReservedStack)
;
; alloca macro dwSize:req, ReservedStack:=<@ReservedStack>
;     exitm<_alloca64( dwSize, ReservedStack )>
;     endm
;
; Allocates memory on the stack. This function is deprecated
; because a more secure version is available; see _malloca.
;

_PAGESIZE_ equ 0x1000 ; one page

    .code

_alloca64::
    mov rax,rsp
    lea rsp,[rsp+8]
    add ecx,16-1    ; assume 16 aligned
    and ecx,-16
    .while ecx > _PAGESIZE_
        sub  rsp,_PAGESIZE_
        test edx,[rsp]
        sub  ecx,_PAGESIZE_
    .endw
    sub rsp,rcx
    mov rcx,[rax]       ; return addres
    lea rax,[rsp+rdx]   ; memory block
    jmp rcx

    end
