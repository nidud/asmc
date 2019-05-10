; CFLTCVT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; cfltcvt() - Converts double to string
;

include quadmath.inc

.code

cfltcvt proc d:ptr, buffer:string_t, ch_type:int_t, precision:int_t, flags:int_t

  local q:REAL16

    cqfcvt(cvtsd_q(&q, d), buffer, ch_type, precision, flags)
    ret

cfltcvt endp

    end
