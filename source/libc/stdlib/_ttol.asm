; _TTOL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

    .code

_ttol proc string:tstring_t

    ldr rcx,string

    .repeat

        movzx eax,tchar_t ptr [rcx]
        add rcx,tchar_t
       .continue(0) .if eax == ' '
    .until 1

ifdef _WIN64
    mov r8d,eax
else
    push eax
endif

    .if ( eax == '-' || eax == '+' )

        movzx eax,tchar_t ptr [rcx]
        add rcx,tchar_t
    .endif

    mov edx,eax
    xor eax,eax

    .while 1

        sub edx,'0'

        .break .ifc
        .break .if ( edx > 9 )

        lea edx,[rax*8+rdx]
        lea eax,[rax*2+rdx]
        movzx edx,tchar_t ptr [rcx]
        add rcx,tchar_t
    .endw

ifdef _WIN64
    .if ( r8d == '-' )
else
    pop ecx
    .if ( ecx == '-' )
endif
        neg eax
    .endif
    ret

_ttol endp

    end
