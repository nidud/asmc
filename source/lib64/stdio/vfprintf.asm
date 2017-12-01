include stdio.inc

    .code

vfprintf proc uses rsi file:LPFILE, format:LPSTR, args:PVOID
    _stbuf(rcx)
    mov rsi,rax
    _output(file, format, args)
    mov rcx,rsi
    mov rsi,rax
    _ftbuf(ecx, file)
    mov rax,rsi
    ret
vfprintf endp

    END
