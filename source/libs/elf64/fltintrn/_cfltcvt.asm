; _CFLTCVT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _cfltcvt() - Converts double to string
;
include fltintrn.inc

    .code

_cfltcvt proc uses rbx r12 r13 r14 d:ptr real8, buffer:string_t, ch_type:int_t, precision:int_t, flags:int_t

  local q:REAL16

    mov rbx,buffer
    mov r12d,ch_type
    mov r13d,precision
    mov r14d,flags
    _cqcvt(__cvtsd_q(&q, d), rbx, r12d, r13d, r14d)
    ret

_cfltcvt endp

    END
