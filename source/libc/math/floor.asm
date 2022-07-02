; FLOOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

    .code

floor proc x:double
ifdef _WIN64
    movq      rcx,xmm0
    shr       rcx,63
    cvttsd2si rax,xmm0
    sub       rax,rcx
    cvtsi2sd  xmm0,rax
else
ifdef __SSE__
  local     w:word, n:word
  local     d:double
    movsd   d,xmm0
    fld     d
else
  local     w:word, n:word
    fld     x
endif
    fstcw   w
    fclex
    mov     n,0x0763
    fldcw   n
    frndint
    fclex
    fldcw   w
ifdef __SSE__
    fstp    d
    movsd   xmm0,d
endif
endif
    ret
floor endp

    end
