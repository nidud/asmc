; _ATOI128.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

_atoi128::

    mov r10,rcx
    xor ecx,ecx
    .repeat

        mov al,[r10]
        inc r10
    .until al != ' '

    mov r11b,al
    .if al == '-' || al == '+'
        mov al,[r10]
        inc r10
    .endif

    mov cl,al
    xor eax,eax
    xor edx,edx

    .while 1
        sub cl,'0'
        .break .ifc
        .break .if cl > 9
        mov r9,rdx
        mov r8,rax
        shld rdx,rax,3
        shl rax,3
        add rax,r8
        adc rdx,r9
        add rax,r8
        adc rdx,r9
        add rax,rcx
        adc rdx,0
        mov cl,[r10]
        inc r10
    .endw
    .if r11b == '-'

        neg rdx
        neg rax
        sbb rdx,0
    .endif
    ret

    END
