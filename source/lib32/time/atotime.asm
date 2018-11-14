; ATOTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; clock_t atotime(char *string);
;
; hh:mm:ss
;
; return: hhhhhmmmmmmsssss
;
include time.inc
include stdlib.inc

    .code

atotime proc uses edi ebx ecx edx string:LPSTR

    xor eax,eax
    mov ebx,string
    .repeat
        mov al,[ebx]
        inc ebx
    .until al > '9' || al < '0'
    .if al
        atol(string)
        push eax
        atol(ebx)
        mov edi,eax
        xor eax,eax
        .repeat
            mov al,[ebx]
            inc ebx
        .until al > '9' || al < '0'
        pop ecx
        .if al
            xchg ecx,ebx
            atol(ecx)
            shr eax,1
            shl edi,5
            shl ebx,11
            or  eax,ebx
            or  eax,edi
        .endif
    .endif
    ret

atotime endp

    END
