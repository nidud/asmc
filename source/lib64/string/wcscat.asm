    .code

wcscat::

    mov rax,rcx
    xor r8d,r8d

    .while [rcx] != r8w

        add rcx,2
    .endw

    .repeat
        mov r8w,[rdx]
        mov [rcx],r8w
        add rcx,2
        add rdx,2
    .until !r8d
    ret

    end
