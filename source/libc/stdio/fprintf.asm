include stdio.inc

    .code

fprintf proc c uses esi file:LPFILE, format:LPSTR, argptr:VARARG

    mov  esi,_stbuf(file)
    xchg esi,_output(file, format, addr argptr)

    _ftbuf(eax, file)
    mov eax,esi
    ret

fprintf endp

    END
