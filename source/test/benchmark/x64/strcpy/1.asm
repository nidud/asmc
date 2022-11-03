
    .code

    mov     r8,rcx
    mov     r9,rdi
    xor     eax,eax
    mov     rdi,rdx
    mov     ecx,-1
    repne   scasb
    not     ecx
    mov     rdi,r8
    xchg    rsi,rdx
    rep     movsb
    mov     rsi,rdx
    mov     rdi,r9
    mov     rax,r8
    ret

    end

