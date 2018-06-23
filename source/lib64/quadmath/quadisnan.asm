
    .code

ifdef _LINUX
quad equ <rdi>
else
quad equ <rcx>
endif
quadisnan::

    xor eax,eax
    .repeat

        movzx r10d,word ptr [quad+14]
        .break .if r10d != 0x7FFF

        inc eax
        mov r10,[quad]
        or  r10,[quad+6]
        .break .ifnz

        dec eax
    .until 1
    ret

    end
