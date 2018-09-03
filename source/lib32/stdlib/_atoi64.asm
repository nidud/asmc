include stdlib.inc

    .code

_atoi64 proc uses esi edi ebx string:LPSTR

    mov ebx,string
    xor ecx,ecx
    .repeat

        mov al,[ebx]
        inc ebx
    .until al != ' '

    push eax
    .if al == '-' || al == '+'
        mov al,[ebx]
        inc ebx
    .endif

    mov cl,al
    xor eax,eax
    xor edx,edx

    .while 1
        sub cl,'0'
        .break .ifc
        .break .if cl > 9
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
        mov cl,[ebx]
        inc ebx
    .endw
    pop ecx
    .if cl == '-'

        neg edx
        neg eax
        sbb edx,0
    .endif
    ret

_atoi64 endp

    END
