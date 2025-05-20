; CEIL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

ceil proc _x:double
ifdef _WIN64
   .new x:double = xmm0
else
    define x _x
endif
   .new w:word
   .new n:word
    fld     x
    fstcw   w
    fclex               ; clear exceptions
    mov     n,0x0B63    ; set new rounding
    fldcw   n
    frndint             ; round to integer
    fclex
    fldcw   w
ifdef _WIN64
    fstp    x
    movsd   xmm0,x
endif
    ret

ceil endp

    end
