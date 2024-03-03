; _TSCPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

.code

_sctprintf proc format:tstring_t, argptr:vararg

    _vsctprintf(format, &argptr)
    ret

_sctprintf endp

    end
