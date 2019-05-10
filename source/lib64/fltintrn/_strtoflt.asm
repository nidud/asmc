; _STRTOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include quadmath.inc

    .data
    _real dt 0
    align 8
    flt S_STRFLT <0,0,0,_real>

    .code

    option win64:nosave

_strtoflt proc string:LPSTR

    cvta_q(rcx, &flt.string)
    mov flt.flags,edx
    mov flt.exponent,ecx
    cvtq_ld(xmm0)
    mov qword ptr _real,rax
    mov word ptr _real[8],cx
    lea rax,flt
    ret

_strtoflt endp

    end
