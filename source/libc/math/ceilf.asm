; CEILF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

ceilf proc x:float
ifdef __SSE__
    movd      ecx,xmm0
    xor       ecx,-0.0
    movd      xmm0,ecx
    shr       ecx,31
    cvttss2si eax,xmm0
    sub       eax,ecx
    neg       eax
    cvtsi2ss  xmm0,eax
else
  local w:word, n:word
    fld     x
    fstcw   w
    fclex               ; clear exceptions
    mov     n,0x0B63    ; set new rounding
    fldcw   n
    frndint             ; round to integer
    fclex
    fldcw   w
endif
    ret
ceilf endp

    end
