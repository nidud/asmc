; __DIVQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__divq proc uses rbx r12 dest:ptr, src:ptr

  local a:STRFLT
  local b:STRFLT

    mov rbx,dest
    mov r12,src
    _fltunpack(&a, rbx)
    _fltunpack(&b, r12)
    _fltdiv(&a, &b)
    _fltpackfp(rbx, &a)
    ret

__divq endp

    end
