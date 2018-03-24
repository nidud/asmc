    .code

_strupr::

    mov rax,rcx
    .while 1
        mov dl,[rcx]
        .break .if !dl
        sub dl,'a'
        cmp dl,'Z' - 'A' + 1
        sbb dl,dl
        and dl,'a' - 'A'
        xor [rcx],dl
        inc rcx
    .endw
    ret

    END
