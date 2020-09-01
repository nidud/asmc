; FLOORF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

.code

floorf proc x:REAL4
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
    ret

floorf endp

    end
