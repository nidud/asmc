; _TTOI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

    .code

_ttoi64 proc string:LPTSTR
ifndef _WIN64
    push esi
    push edi
    push ebx
endif

    ldr rcx,string
    .repeat

        movzx eax,TCHAR ptr [rcx]
        add rcx,TCHAR
       .continue(0) .if eax == ' '
    .until 1

ifdef _WIN64
    mov r8d,eax
else
    push eax
endif
    .if ( eax == '-' || eax == '+' )

        movzx eax,TCHAR ptr [rcx]
        add rcx,TCHAR
    .endif

ifdef _WIN64
    mov edx,eax
else
    mov ebx,eax
    xor edx,edx
endif
    xor eax,eax

    .while 1

ifdef _WIN64

        sub edx,'0'

        .break .ifc
        .break .if ( edx > 9 )

        lea rdx,[rax*8+rdx]
        lea rax,[rax*2+rdx]
        movzx edx,TCHAR ptr [rcx]
else
        sub ebx,'0'

        .break .ifc
        .break .if ( ebx > 9 )

        mov esi,edx
        mov edi,eax
        shld edx,eax,3
        shl eax,3
        add eax,edi
        adc edx,esi
        add eax,edi
        adc edx,esi
        add eax,ebx
        adc edx,0
        movzx ebx,TCHAR ptr [rcx]
endif
        add rcx,TCHAR
    .endw

ifdef _WIN64
    .if ( r8d == '-' )
        neg rax
else
    pop ecx
    pop ebx
    pop edi
    pop esi
    .if ( ecx == '-' )
        neg edx
        neg eax
        sbb edx,0
endif
    .endif
    ret

_ttoi64 endp

    end
