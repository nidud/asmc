; _GETDRIVES.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include winbase.inc

    .code

_getdrives proc
    GetLogicalDrives()
    ret
_getdrives endp

    END
