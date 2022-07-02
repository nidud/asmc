; _WCREAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include share.inc
include fcntl.inc

    .code

_wcreat proc path:LPWSTR, pmode:SINT

    _wsopen( path, O_CREAT or O_TRUNC or O_RDWR, SH_DENYNO, pmode )
    ret

_wcreat endp

    end
