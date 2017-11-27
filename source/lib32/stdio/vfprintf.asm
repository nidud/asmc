include stdio.inc

    .code

vfprintf proc uses esi file:LPFILE, format:LPSTR, args:PVOID

    mov  esi,_stbuf(file)
    xchg esi,_output(file, format, args)
    _ftbuf(eax, file)
    mov eax,esi
    ret

vfprintf endp

    END
