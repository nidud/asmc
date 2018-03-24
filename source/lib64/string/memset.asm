    .code

memset::

    push    rdi
    push    rcx
    mov     rdi,rcx
    mov     rax,rdx
    mov     rcx,r8
    rep     stosb
    pop     rax
    pop     rdi
    ret

    END
