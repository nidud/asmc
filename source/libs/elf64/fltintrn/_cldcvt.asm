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

_cldcvt proc uses rbx r12 r13 r14 ld:ptr real10, buffer:string_t, ch_type:int_t, precision:int_t, flags:int_t

  local q:REAL16

    mov rbx,buffer
    mov r12d,ch_type
    mov r13d,precision
    mov r14d,flags
    _cqcvt(__cvtld_q(&q, ld), rbx, r12d, r13d, r14d)
    ret

_cldcvt endp

    end
