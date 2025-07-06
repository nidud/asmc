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
    mov ax,_argvused
    ret
_initargv endp

    end
