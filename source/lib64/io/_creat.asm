; _CREAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include share.inc
include fcntl.inc

    .code

_creat proc path:LPSTR, pmode:UINT

    _sopen(rcx, O_CREAT or O_TRUNC or O_RDWR, SH_DENYNO, edx)
    ret

_creat endp

    END
