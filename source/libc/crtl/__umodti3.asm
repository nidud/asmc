; __UMODTI3.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include crtl.inc

    .code

ifdef _WIN64

__umodti3 proc dividend:int128_t, divisor:int128_t

    call    __udivti3
    xchg    r9,rdx
    xchg    r8,rax
    ret

__umodti3 endp

else
    int     3
endif
    end
