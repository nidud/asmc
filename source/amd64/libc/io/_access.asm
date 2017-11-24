include io.inc

.code

_access proc fname:LPSTR, amode:UINT

    .if getfattr(rcx) != -1
        .if amode == 2 && eax & _A_RDONLY
            mov eax,-1
        .else
            xor eax,eax
        .endif
    .endif
    ret

_access endp

    END