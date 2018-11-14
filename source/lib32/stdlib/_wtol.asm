; _WTOL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

    option stackbase:esp

_wtol proc string:LPWSTR

    mov edx,string
    xor ecx,ecx
    .repeat

        movzx eax,word ptr [edx]
        add edx,2
        .continue(0) .if eax == ' '
    .until 1

    push eax

    .if eax == '-' || eax == '+'

        mov ax,[edx]
        add edx,2
    .endif

    mov ecx,eax
    xor eax,eax
    .while 1

        sub ecx,'0'
        .break .ifc
        .break .if ecx > 9
        lea ecx,[eax*8+ecx]
        lea eax,[eax*2+ecx]
        movzx ecx,word ptr [edx]
        add edx,2
    .endw

    pop ecx
    .if ecx == '-'

        neg eax
    .endif
    ret

_wtol endp

    END
