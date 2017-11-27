include io.inc
include share.inc
include fcntl.inc

    .code

    option win64:nosave

_creat proc path:LPSTR, pmode:UINT

    _sopen(rcx, O_CREAT or O_TRUNC or O_RDWR, SH_DENYNO, edx)
    ret

_creat endp

    END
