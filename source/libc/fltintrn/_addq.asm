; _ADDQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include fltintrn.inc

    .code

__addq proc __ccall dest:ptr qfloat_t, src:ptr qfloat_t

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, dest)
    _fltunpack(&b, src)
    _fltadd(&a, &b)
    _fltpackfp(dest, &a)
    ret

__addq endp

    end
