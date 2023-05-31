; __MODTI3.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdlib.inc

    .code

ifdef _WIN64

__modti3 proc dividend:int128_t, divisor:int128_t

    call    __divti3
    xchg    r9,rdx
    xchg    r8,rax
    ret

__modti3 endp

else
    int     3
endif
    end
