; _TVSCANF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

.code

_vtscanf proc format:tstring_t, argptr:ptr

    _tinput(stdin, ldr(format), ldr(argptr))
    ret

_vtscanf endp

    end
