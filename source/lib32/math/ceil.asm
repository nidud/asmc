; CEIL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

.code

ceil proc __cdecl x:double

local w:word, n:word

    fld x
    fstcw w
    fclex           ; clear exceptions
    mov n,0x0B63    ; set new rounding
    fldcw n
    frndint         ; round to integer
    fclex
    fldcw w
    ret

ceil endp

    end
