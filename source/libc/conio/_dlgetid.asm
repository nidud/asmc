; _DLGETID.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    option dotname

    .code

    assume rax:THWND

_dlgetid proc watcall hwnd:THWND, id:UINT

    test    [rax].flags,W_CHILD
    cmovnz  rax,[rax].prev
    test    [rax].flags,O_CHILD
    jz      .2
    mov     rax,[rax].object
    test    edx,edx
    jz      .1
.0:
    test    rax,rax
    jz      .1
    mov     rax,[rax].next
    dec     edx
    jnz     .0
.1:
    ret
.2:
    xor     eax,eax
    jmp     .1

_dlgetid endp

    end
