include io.inc
include share.inc

.code

_wopen proc c path:LPWSTR, oflag:SINT, args:VARARG

    _wsopen(path, oflag, SH_DENYNO, &args)
    ret

_wopen endp

    end
