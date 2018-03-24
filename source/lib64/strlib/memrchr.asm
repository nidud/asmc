    .code

memrchr::

    xor eax,eax

    .if r8

        xchg  rcx,rdi
        xchg  rcx,r8
        mov   al,dl
        lea   rdi,[rdi+rcx-1]
        std
        repnz scasb
        cld
        xchg  rdi,r8
        setnz al
        inc   r8
        dec   rax
        and   rax,r8

    .endif
    ret

    end
