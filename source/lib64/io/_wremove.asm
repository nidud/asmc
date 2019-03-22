; _WREMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include winbase.inc

.code

_wremove proc file:LPWSTR

    .if DeleteFileW(rcx)

        xor eax,eax
    .else
        _dosmaperr(GetLastError())
    .endif
    ret

_wremove endp

    end
