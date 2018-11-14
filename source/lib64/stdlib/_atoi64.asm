; _ATOI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

_atoi64::

    xor rax,rax
    xor rdx,rdx

    .repeat
        mov al,[rcx]
        inc rcx
    .until al != ' '

    mov r8b,al
    .if al == '-' || al == '+'

        mov al,[rcx]
        inc rcx
    .endif

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

    .if r8b == '-'

        neg rdx
    .endif
    mov rax,rdx
    ret

    end
