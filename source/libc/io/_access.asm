include io.inc
include crtl.inc
include errno.inc

    .code

_access proc file:LPSTR, amode

    .if getfattr(file) == -1

        osmaperr()

    .elseif amode & 2 && eax & _A_RDONLY

        mov errno,EACCES
        mov eax,-1
    .else
        xor eax,eax
    .endif
    ret

_access endp

    END