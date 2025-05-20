; _FINITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include float.inc

.code

_finite proc _x:double
ifdef _WIN64
   .new x:double = xmm0
else
    define x _x
endif
    mov edx,dword ptr x[4]
    xor eax,eax
    shr edx,32 - DBL_EXPBITS - 1
    and edx,DBL_EXPMASK
    cmp edx,DBL_EXPMASK
    setne al
    ret

_finite endp

    end
