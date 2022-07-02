; __CVTI64_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvti64_q() - __int64 to Quadruple float
;
include fltintrn.inc

    .code

__cvti64_q proc __ccall q:ptr qfloat_t, ll:int64_t

  local flt:STRFLT

    _i64toflt( &flt, ll )
    _fltpackfp( q, &flt )
    ret

__cvti64_q endp

    end

