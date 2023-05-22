; _DLGETFOCUS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    option dotname

    .code

    assume rax:THWND

_dlgetfocus proc watcall hwnd:THWND

    test    [rax].flags,W_CHILD
    cmovnz  rax,[rax].prev
    test    [rax].flags,O_CHILD
    jz      .3
    movzx   edx,word ptr [rax].rc
    mov     cl,[rax].index
    mov     rax,[rax].object
    test    cl,cl
    jz      .1
.0:
    test    rax,rax
    jz      .2
    mov     rax,[rax].next
    dec     cl
    jnz     .0
.1:
    add     edx,[rax].rc
.2:
    ret
.3:
    xor     eax,eax
    jmp     .2

_dlgetfocus endp

    end
