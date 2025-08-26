; _ARGVCRT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

.data
_argvcrt    string_t NULL
_environcrt string_t NULL

.code

_initargv proc private
    mov _argvcrt,__argv
    mov _environcrt,_environ
    ret
_initargv endp

.pragma init(_initargv, 10)

    end
