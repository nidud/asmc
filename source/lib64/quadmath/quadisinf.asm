
    .code

ifdef _LINUX
quad equ <rdi>
else
quad equ <rcx>
endif

quadisinf::

    xor eax,eax
    .repeat

        mov r10,[quad]
        or  r10,[quad+6]
        .break .ifnz

        movzx r10d,word ptr [quad+14]
        and r10d,0x7FFF
        .break .if r10d != 0x7FFF

        inc eax
    .until 1
    ret

    end
