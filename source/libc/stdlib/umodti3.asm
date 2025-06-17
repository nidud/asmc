; __UMODTI3.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdlib.inc

    .code

ifdef _WIN64

__umodti3 proc dividend:uint128_t, divisor:uint128_t

    call    __udivti3
    xchg    r9,rdx
    xchg    r8,rax
    ret

__umodti3 endp

else
    int     3
endif
    end
