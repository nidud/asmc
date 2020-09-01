; FLOORF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

    option win64:rsp nosave noauto

floorf proc x:float

    movd      r10d,xmm0
    shr       r10d,63
    cvttss2si eax,xmm0
    sub       eax,r10d
    cvtsi2ss  xmm0,eax
    ret

floorf endp

    end
