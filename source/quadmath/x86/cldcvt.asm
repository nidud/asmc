; CLDCVT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; cldcvt() - Converts long double to string
;

include quadmath.inc

.code

cldcvt proc ld:ptr, buffer:string_t, ch_type:int_t, precision:int_t, flags:int_t

  local q:REAL16

    cqfcvt(cvtld_q(&q, ld), buffer, ch_type, precision, flags)
    ret

cldcvt endp

    end
