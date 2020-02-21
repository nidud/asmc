; _ALLOCA64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

_alloca64::

    pop rax ; return addres
    add ecx,16-1
    and cl,-16
    .while rcx > 0x1000
        sub  rsp,0x1000
        test [rsp],eax
        sub  rcx,0x1000
    .endw
    sub  rsp,rcx
    test [rsp],eax
    mov  rcx,rax
    lea  rax,[rsp+rdx]
    jmp  rcx

    end
