; CEILF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

    option win64:rsp nosave noauto

ceilf proc x:float

    mov       r11d,-0.0
    movd      r10d,xmm0
    xor       r10d,r11d
    movd      xmm0,r10d
    shr       r10d,31
    cvttss2si eax,xmm0
    sub       eax,r10d
    neg       eax
    cvtsi2ss  xmm0,eax
    ret

ceilf endp

    end
