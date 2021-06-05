; __SUBQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__subq proc A:ptr, B:ptr

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, A)
    _fltunpack(&b, B)
    _fltsub(&a, &b)
    _fltpackfp(A, &a)
    ret

__subq endp

    end
