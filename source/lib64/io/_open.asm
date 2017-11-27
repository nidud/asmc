include io.inc
include share.inc

    .code

_open proc path:LPSTR, oflag:SINT, args:VARARG

    _sopen(rcx, edx, SH_DENYNO, args)
    ret

_open endp

    END
