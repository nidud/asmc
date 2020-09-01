; _WREMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include winbase.inc

.code

_wremove proc file:LPWSTR

    .if DeleteFileW(file)

        xor eax,eax
    .else
        osmaperr()
    .endif
    ret

_wremove endp

    end
