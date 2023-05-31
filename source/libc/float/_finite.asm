; _FINITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include float.inc

.code

_finite proc d:double
ifdef __SSE__
    local x:double
    movsd x,xmm0
    mov edx,dword ptr x[4]
else
    mov edx,dword ptr d[4]
endif
    xor eax,eax
    shr edx,32 - DBL_EXPBITS - 1
    and edx,DBL_EXPMASK
    cmp edx,DBL_EXPMASK
    setne al
    ret

_finite endp

    end
