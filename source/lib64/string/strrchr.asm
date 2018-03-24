    .code

strrchr::

    mov	  r8,rdi
    mov	  rdi,rcx
    xor	  rax,rax
    mov	  rcx,-1
    repne scasb
    not	  rcx
    dec	  rdi
    mov	  al,dl
    std
    repne scasb
    cld
    mov	  al,0
    .ifz
	lea rax,[rdi+1]
    .endif
    mov rdi,r8
    ret

    END
