; CFLTCVT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

cfltcvt proc vectorcall d:real8, buffer:string_t, ch_type:int_t, precision:int_t, flags:int_t

    cqfcvt(cvtsd_q(xmm0), buffer, ch_type, precision, flags)
    ret

cfltcvt endp

    end
