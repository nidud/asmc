; TRUNCF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
ifdef _WIN64
include intrin.inc
endif

.code

truncf proc x:float
ifdef _WIN64 ; SSE4.1
    _mm_round_ps(xmm0, _MM_FROUND_TO_ZERO or _MM_FROUND_NO_EXC)
else
   .new w:word
   .new n:word
    fld     x
    fstcw   w
    mov     ax,w
    or      ax,0xC00
    mov     n,ax
    fldcw   n
    frndint
    fldcw   w
endif
    ret
    endp

    end
