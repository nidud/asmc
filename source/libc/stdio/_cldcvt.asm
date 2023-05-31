; _CLDCVT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _cldcvt() - Converts long double to string
;
include fltintrn.inc

    .code

_cldcvt proc uses rbx ld:ptr real10, buffer:string_t, ch_type:int_t, precision:int_t, flags:int_t

   .new q:REAL16

    mov rbx,__cvtld_q( &q, ld )
    _cqcvt( rbx, buffer, ch_type, precision, flags )
    ret

_cldcvt endp

    end
