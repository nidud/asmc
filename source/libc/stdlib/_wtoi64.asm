; _WTOI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

ifdef _WIN64

_wtoi64 proc string:wstring_t

    ldr rcx,string

    .repeat
        movzx eax,word ptr [rcx]
        add rcx,2
        .continue(0) .if eax == ' '
    .until 1

    mov r8d,eax
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

        lea rcx,[rax*8+rcx]
        lea rax,[rax*2+rcx]

        movzx edx,word ptr [rcx]
        add rcx,2
    .endw

    .if ( r8d == '-' )
        neg rax
    .endif

else

_wtoi64 proc uses esi edi ebx string:wstring_t

    mov ecx,string

    .repeat
        movzx eax,word ptr [rcx]
        add rcx,2
        .continue(0) .if eax == ' '
    .until 1

    push eax

    .if ( eax == '-' || eax == '+' )

        mov ax,[rcx]
        add rcx,2
    .endif

    mov ebx,eax
    xor eax,eax
    xor edx,edx

    .while 1

        sub ebx,'0'
        .break .ifc
        .break .if ebx > 9

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

        movzx ebx,word ptr [rcx]
        add rcx,2
    .endw

    pop ecx
    .if ( ecx == '-' )
        neg edx
        neg eax
        sbb edx,0
    .endif
endif
    ret

_wtoi64 endp

    end
