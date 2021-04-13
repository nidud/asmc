; _WTOI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_wtoi64 proc uses esi edi ebx string:wstring_t

    mov ebx,string
    .repeat

        movzx eax,word ptr [ebx]
        add ebx,2
        .continue(0) .if eax == ' '
    .until 1

    push eax

    .if eax == '-' || eax == '+'

        mov ax,[ebx]
        add ebx,2
    .endif

    mov ecx,eax
    xor eax,eax
    xor edx,edx
    .while 1

        sub cx,'0'
        .break .ifc
        .break .if cx > 9

        mov esi,edx
        mov edi,eax
        shld edx,eax,3
        shl eax,3
        add eax,edi
        adc edx,esi
        add eax,edi
        adc edx,esi
        add eax,ecx
        adc edx,0
        mov cx,[ebx]
        add ebx,2
    .endw

    pop ecx
    .if ecx == '-'

        neg edx
        neg eax
        sbb edx,0
    .endif
    ret

_wtoi64 endp

    END
