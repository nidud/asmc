; _TSCANF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

.code

_tscanf proc format:tstring_t, argptr:vararg

    _vtscanf(format, &argptr)
    ret

_tscanf endp

    end
