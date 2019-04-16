; _STRTOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include quadmath.inc

    .data
    _real dt 0
    flt S_STRFLT <0,0,0,_real>

    .code

    option win64:nosave

_strtoflt proc string:LPSTR

  local q:REAL16

    atoquad(&q, rcx, &flt.string)
    mov flt.flags,edx
    mov flt.exponent,ecx
    quadtold(&_real, &q)
    lea rax,flt
    ret

_strtoflt endp

    end
