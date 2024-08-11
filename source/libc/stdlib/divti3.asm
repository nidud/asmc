; __DIVTI3.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

ifdef _WIN64

    option dotname

__divti3 proc dividend:int128_t, divisor:int128_t

    ;
    ; rdx:rax.r9:r8 = rdx::rcx / r9::r8
    ;
    test    rdx,rdx     ; hi word of dividend
    js      .1          ; signed ?
    test    r9,r9       ; hi word of divisor
    js      .0          ; signed ?
    call    __udivti3
    jmp     .3

.0:
    neg     r9
    neg     r8
    sbb     r9,0
    call    __udivti3
    neg     rdx
    neg     rax
    sbb     rdx,0
    jmp     .3

.1:
    neg     rdx
    neg     rcx
    sbb     rdx,0
    test    r9,r9
    jns     .2
    neg     r9
    neg     r8
    sbb     r9,0
    call    __udivti3
    neg     r9
    neg     r8
    sbb     r9,0
    jmp     .3
.2:
    call    __udivti3
    neg     r9
    neg     r8
    sbb     r9,0
    neg     rdx
    neg     rax
    sbb     rdx,0
.3:
    ret

__divti3 endp

else
    int     3
endif
    end
