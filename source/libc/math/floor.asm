; FLOOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
include intrin.inc

.code

floor proc x:double
ifdef _WIN64
    _mm_floor_pd(xmm0)
else
  local w:word, n:word
    fld     x
    fstcw   w
    fclex
    mov     n,0x0763
    fldcw   n
    frndint
    fclex
    fldcw   w
endif
    ret
    endp

    end
