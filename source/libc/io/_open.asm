; _OPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include share.inc

    .code

_open proc path:LPSTR, oflag:SINT, args:VARARG

    _sopen( path, oflag, SH_DENYNO, args )
    ret

_open endp

    end
