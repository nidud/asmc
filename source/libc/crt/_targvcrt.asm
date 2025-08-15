; _TARGVCRT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

.data
_targvcrt    tstring_t NULL
_tenvironcrt tstring_t NULL

.code

_initargv proc private
    mov _targvcrt,__targv
    mov _tenvironcrt,_tenviron
    ret
_initargv endp

.pragma init(_initargv, 10)

    end
