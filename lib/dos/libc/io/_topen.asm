; _TOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include share.inc
include tchar.inc

.pragma warning(disable: 8022)

.code

_topen proc path:LPTSTR, oflag:SINT, args:VARARG

    _tsopen( path, oflag, SH_DENYNO, args )
    ret

_topen endp

    end
