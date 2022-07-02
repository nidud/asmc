; FLOORF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

    .code

floorf proc x:float
ifdef __SSE__
    movss       xmm1,1.0
    movss       xmm2,xmm0
    cvttps2dq   xmm0,xmm0
    cvtdq2ps    xmm0,xmm0
    cmpltps     xmm2,xmm0
    andps       xmm2,xmm1
    subss       xmm0,xmm2
else
  local     w:word, n:word
    fstcw   w           ; store fpu control word
    movzx   eax,w
    or      eax,0x0400  ; round towards -oo
    and     eax,0xF7FF
    mov     n,ax
    fldcw   n
    frndint             ; round
    fldcw   w           ; restore original control word
endif
    ret
floorf endp

    end
