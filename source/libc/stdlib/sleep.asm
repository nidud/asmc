; SLEEP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

.code

_sleep proc milliseconds:uint_t
    Sleep( ldr(milliseconds) )
    ret
    endp

    end
