    .code

strncmp::

    xor eax,eax
    .repeat
        .break .if !r8
        .while 1
            mov al,[rcx]
            cmp al,[rdx]
            lea rdx,[rdx+1]
            lea rcx,[rcx+1]
            .break .ifnz
            .break(1) .if !al
            dec r8
            .continue(0) .ifnz
            xor eax,eax
            .break(1)
        .endw
        sbb al,al
        sbb al,-1
        movsx rax,al
    .until 1
    ret

    END
