    .code

memcpy::

    xchg rdx,rsi
    xchg rcx,rdi
    xchg rcx,r8
    mov  rax,rdi
    rep  movsb
    mov  rdi,r8
    mov  rsi,rdx
    ret

    end
