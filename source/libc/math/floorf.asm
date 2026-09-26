; FLOORF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc
include intrin.inc

    .code

floorf proc x:float
ifdef _WIN64
    _mm_floor_ps(xmm0)
else
  local w:word, n:word
    fld     x
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
    endp

    end
