include stdio.inc
include string.inc

    .code

    option win64:rsp nosave

fputs proc uses rsi rdi rbx string:LPSTR, fp:LPFILE

    mov rsi,rdx
    mov rdi,rcx

    _stbuf(rdx)
    mov rbx,rax
    strlen(rdi)
    fwrite(rdi, 1, eax, rsi)
    xchg    rbx,rax
    _ftbuf(eax, rsi)
    strlen(rdi)
    cmp rax,rbx
    mov rax,0
    je	@F
    dec rax
@@:
    ret
fputs endp

    END
