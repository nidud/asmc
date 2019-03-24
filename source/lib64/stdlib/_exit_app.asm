; _EXIT_APP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

doexit proto :int_t, :int_t, :int_t

    .code

_exit_app proc frame

    doexit(0, 0, 0) ; full term, return to caller

_exit_app endp

    end
