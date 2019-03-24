; _CEXIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

doexit proto :int_t, :int_t, :int_t

    .code

_cexit proc frame

    doexit(0, 0, 1) ; full term, return to caller

_cexit endp

    end
