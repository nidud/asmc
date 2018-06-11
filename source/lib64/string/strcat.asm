    .code

strcat::

    push rcx
    xor eax,eax
    .while [rcx] != al
        inc rcx
    .endw
    .while [rdx] != ah
        mov al,[rdx]
        mov [rcx],al
        inc rcx
        inc rdx
    .endw
    mov [rcx],ah
    pop rax
    ret

    end
