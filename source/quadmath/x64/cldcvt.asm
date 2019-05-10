; CLDCVT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

cldcvt proc vectorcall ld:real10, buffer:string_t, ch_type:int_t, precision:int_t, flags:int_t

    cqfcvt(cvtld_q(xmm0), buffer, ch_type, precision, flags)
    ret

cldcvt endp

    end
