; CEILF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

    option win64:rsp nosave noauto

ceilf proc x:float

    movd      ecx,xmm0
    xor       ecx,-0.0
    movd      xmm0,ecx
    shr       ecx,31
    cvttss2si eax,xmm0
    sub       eax,ecx
    neg       eax
    cvtsi2ss  xmm0,eax
    ret

ceilf endp

    end
