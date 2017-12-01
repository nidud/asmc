include stdio.inc

    .code

printf proc uses rbx format:LPSTR, argptr:VARARG
    _stbuf(addr stdout)
    mov rbx,rax
    _output(addr stdout, format, addr argptr)
    xchg rax,rbx
    _ftbuf(eax, addr stdout)
    ret
printf endp

    END
