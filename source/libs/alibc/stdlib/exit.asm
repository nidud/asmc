; EXIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

; worker routine prototype
doexit proto :int_t, :int_t, :int_t

    .code

exit proc retval:int_t

    doexit(edi, 0, 0) ; full term, kill process
    ret

exit endp

    end
