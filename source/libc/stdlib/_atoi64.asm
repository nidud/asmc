; ATOLL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_atoi64 proc string:string_t

ifndef _WIN64
    mov ecx,string
endif
    xor eax,eax
    xor edx,edx

    .repeat
        mov al,[rcx]
        inc rcx
    .until al != ' '

ifdef _WIN64
    mov r8b,al
else
    push eax
endif

    .if ( al == '-' || al == '+' )

        mov al,[rcx]
        inc rcx
    .endif

ifdef _WIN64

    .while 1

        sub al,'0'

        .break .ifc
        .break .if al > 9

        mov r9,rdx
        shl rdx,3
        add rdx,r9
        add rdx,r9
        add rdx,rax
        mov al,[rcx]
        inc rcx
    .endw

    .if ( r8b == '-' )

        neg rdx
    .endif
    mov rax,rdx

else

    push esi
    push edi
    push ebx

    mov ebx,ecx
    mov ecx,eax
    xor eax,eax
    xor edx,edx

    .while 1

        sub cl,'0'

        .break .ifc
        .break .if ( cl > 9 )

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

    pop ebx
    pop edi
    pop esi
    pop ecx

    .if ( cl == '-' )

        neg edx
        neg eax
        sbb edx,0
    .endif
endif
    ret

_atoi64 endp

    end
