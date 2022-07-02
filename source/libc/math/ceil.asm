; CEIL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

ceil proc x:double
ifdef _AMD64_
    mov       rdx,-0.0
    movq      rcx,xmm0
    xor       rcx,rdx
    movq      xmm0,rcx
    shr       rcx,63
    cvttsd2si rax,xmm0
    sub       rax,rcx
    neg       rax
    cvtsi2sd  xmm0,rax
else
ifdef __SSE__
  local d:double, w:word, n:word
    movsd   d,xmm0
    fld     d
else
  local w:word, n:word
    fld     x
endif
    fstcw   w
    fclex               ; clear exceptions
    mov     n,0x0B63    ; set new rounding
    fldcw   n
    frndint             ; round to integer
    fclex
    fldcw   w
ifdef __SSE__
    fstp    d
    movsd   xmm0,d
endif
endif
    ret

ceil endp

    end
