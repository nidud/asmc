; _WTOL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_wtol proc string:LPWSTR

    ldr rcx,string
    .repeat
        movzx eax,word ptr [rcx]
        add rcx,2
        .continue(0) .if eax == ' '
    .until 1

ifdef _WIN64
    mov r8d,eax
else
    push eax
endif

    .if ( eax == '-' || eax == '+' )

        mov ax,[rcx]
        add rcx,2
    .endif

    mov edx,eax
    xor eax,eax

    .while 1

        sub edx,'0'

        .break .ifc
        .break .if ( edx > 9 )

        lea rdx,[rax*8+rdx]
        lea rax,[rax*2+rdx]

        movzx edx,word ptr [rcx]
        add rcx,2
    .endw

ifdef _WIN64
    .if ( r8d == '-' )
else
    pop ecx
    .if ( ecx == '-' )
endif
        neg rax
    .endif
    ret

_wtol endp

    end
