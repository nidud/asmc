; _TCSMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

.code

_tcsmove proc dst:LPTSTR, src:LPTSTR

    _tcslen(src)
    inc eax
ifdef _UNICODE
    add eax,eax
endif
    memmove(dst, src, eax)
    ret

_tcsmove endp

    end
