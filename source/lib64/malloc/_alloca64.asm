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

    lea rax,[rsp+8] ; return addres

    add ecx,16-1    ; assume 16 aligned
    and cl,-16

    .while ecx > _PAGESIZE_

        sub  rax,_PAGESIZE_

        test edx,[rax] ; probe page
        ;
        ; RSP unchanged on stack overflow
        ;
        sub  ecx,_PAGESIZE_
    .endw

    sub  rax,rcx
    test edx,[rax]  ; probe page

    mov rcx,[rsp]   ; return addres
    mov rsp,rax     ; new stack
    mov [rax],rcx
    add rax,rdx     ; memory block
    ret

    end
