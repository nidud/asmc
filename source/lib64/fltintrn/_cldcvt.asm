; _CLDCVT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _cldcvt() - Converts long double to string
;
include fltintrn.inc
include quadmath.inc

    .code

_cldcvt proc ld:ptr real10, buffer:LPSTR, ch_type:SINT, precision:SINT, flags:SINT

  local q:REAL16

    mov rcx,__cvtld_q(&q, rcx)
    _cqcvt(rcx, buffer, ch_type, precision, flags)
    ret

_cldcvt endp

    end
