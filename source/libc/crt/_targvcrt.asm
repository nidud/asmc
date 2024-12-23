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
    mov eax,_argvused
    ret
_initargv endp

    end
