; _WTOL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

    option win64:rsp nosave noauto

_wtol proc string:LPWSTR

    mov rdx,rcx;string
    xor ecx,ecx
    .repeat

        movzx eax,word ptr [rdx]
        add rdx,2
        .continue(0) .if eax == ' '
    .until 1

    push rax

    .if eax == '-' || eax == '+'

        mov ax,[rdx]
        add rdx,2
    .endif

    mov ecx,eax
    xor eax,eax
    .while 1

        sub ecx,'0'
        .break .ifc
        .break .if ecx > 9
        lea rcx,[rax*8+rcx]
        lea rax,[rax*2+rcx]
        movzx ecx,word ptr [rdx]
        add rdx,2
    .endw

    pop rcx
    .if ecx == '-'

        neg rax
    .endif
    ret

_wtol endp

    END
