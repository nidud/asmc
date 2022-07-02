; __CVTI32_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include fltintrn.inc

    .code

__cvti32_q proc __ccall q:ptr qfloat_t, l:long_t

  local flt:STRFLT

    _itoflt( &flt, l )
    _fltpackfp( q, &flt )
    ret

__cvti32_q endp

    end

