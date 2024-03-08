    .code

    mov         rdx,rdi
    mov         rdi,rcx
    mov         rcx,-1
    xor         eax,eax
    repnz       scasw
    mov         rax,rcx
    mov         rdi,rdx
    not         rax
    dec         rax
    ret

    end
