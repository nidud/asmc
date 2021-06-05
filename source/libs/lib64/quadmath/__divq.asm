; __DIVQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__divq proc dest:ptr, src:ptr

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, dest)
    _fltunpack(&b, src)
    _fltdiv(&a, &b)
    _fltpackfp(dest, &a)
    ret

__divq endp

    end
