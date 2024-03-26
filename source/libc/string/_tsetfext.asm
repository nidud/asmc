; _TSETFEXT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

.code

_tsetfext proc path:LPTSTR, ext:LPTSTR

    .if _tstrext(path)

        mov TCHAR ptr [rax],0
    .endif
    _tcscat(path, ext)
    ret

_tsetfext endp

    end
