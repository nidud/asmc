; _ARGVUSED.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

.data
_argvused int_t 1

.code

_initargv proc private
    mov _argvcrt,__argv
    mov _environcrt,_environ
    ret
_initargv endp

.pragma init(_initargv, 10)

    end
