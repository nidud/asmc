; __MULQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__mulq proc uses rbx r12 dest:ptr, src:ptr

  local a:STRFLT
  local b:STRFLT

    mov rbx,dest
    mov r12,src

    _fltunpack(&a, rbx)
    _fltunpack(&b, r12)
    _fltmul(&a, &b)
    _fltpackfp(rbx, &a)
    ret

__mulq endp

    end
