; __SUBQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__subq proc dest:ptr, src:ptr

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, dest)
    _fltunpack(&b, src)
    _fltsub(&a, &b)
    _fltpackfp(dest, &a)
    ret

__subq endp

    end
