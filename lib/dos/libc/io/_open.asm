; _OPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include share.inc

.pragma warning(disable: 8022)

.code

_open proc path:string_t, oflag:int_t, args:vararg

    _sopen( path, oflag, SH_DENYNO, args )
    ret

_open endp

    end
