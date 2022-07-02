; _CFLTCVT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _cfltcvt() - Converts double to string
;
include fltintrn.inc

    .code

_cfltcvt proc d:ptr real8, buffer:string_t, ch_type:int_t, precision:int_t, flags:int_t

   .new q:REAL16

    mov rcx,__cvtsd_q( &q, d )
    _cqcvt( rcx, buffer, ch_type, precision, flags )
    ret

_cfltcvt endp

    end
