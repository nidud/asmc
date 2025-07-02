; _TSNPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

.code

_sntprintf proc string:tstring_t, count:size_t, format:tstring_t, args:vararg

    _vsntprintf(string, count, format, &args)
    ret

_sntprintf endp

    end
