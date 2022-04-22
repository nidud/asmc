; ATOLL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

atoll::
_atoi64::

    xor rax,rax
    xor rdx,rdx

    .repeat
        mov al,[rdi]
        inc rdi
    .until al != ' '

    mov r8b,al
    .if al == '-' || al == '+'

        mov al,[rdi]
        inc rdi
    .endif

    .while 1

        sub al,'0'
        .break .ifc
        .break .if al > 9

        mov rcx,rdx
        shl rdx,3
        add rdx,rcx
        add rdx,rcx
        add rdx,rax
        mov al,[rdi]
        inc rdi
    .endw

    .if r8b == '-'

        neg rdx
    .endif
    mov rax,rdx
    ret

    end
