; __CVTQ_I32.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvtq_i32() - Quadruple float to long
;
include fltintrn.inc

    .code

__cvtq_i32 proc __ccall q:ptr qfloat_t

  local flt:STRFLT

    _fltunpack( &flt, q )
    _flttoi( &flt )
    ret

__cvtq_i32 endp

    end
