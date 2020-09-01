; _C_EXIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

doexit proto :int_t, :int_t, :int_t

    .code

_c_exit proc frame

    doexit(0, 1, 1) ; quick term, return to caller

_c_exit endp

    end
