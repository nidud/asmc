; __CVTQ_I64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvtq_i64() - Quadruple float to long long
;
include fltintrn.inc

    .code

__cvtq_i64 proc __ccall q:ptr qfloat_t

  local flt:STRFLT

    _fltunpack( &flt, q )
    _flttoi64( &flt )
    ret

__cvtq_i64 endp

    end
