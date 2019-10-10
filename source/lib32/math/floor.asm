; FLOOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

.code

floor proc x:REAL8

  local w:word, n:word

    fld x
    fstcw w
    fclex
    mov n,0x0763
    fldcw n
    frndint
    fclex
    fldcw w
    ret

floor endp

    end
