; _Q_NAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .data

_Q_NAN label REAL16
    dd 0,0,0,0x7FFF4000

    end
