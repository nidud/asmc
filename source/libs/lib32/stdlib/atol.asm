; ATOL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

atol proc string:LPSTR

    mov edx,string
    xor ecx,ecx

    .repeat

        movzx eax,byte ptr [edx]
        inc edx
        .continue(0) .if al == ' '

        push eax
        .if al == '-' || al == '+'

            mov al,[edx]
            inc edx
        .endif

        mov ecx,eax
        xor eax,eax

        .while 1

            sub ecx,'0'
            .break .ifc
            .break .if ecx > 9
            lea ecx,[eax*8+ecx]
            lea eax,[eax*2+ecx]
            movzx ecx,byte ptr [edx]
            inc edx
        .endw

        pop ecx
        .break .if cl != '-'
        neg eax
    .until 1
    ret

atol endp

    END
