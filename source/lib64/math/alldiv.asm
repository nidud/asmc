; ALLDIV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    _aulldiv proto

    .code

_alldiv::
__divti3::

    ;
    ; rdx:rax.r9:r8 = rdx::rcx / r9::r8
    ;
    test    rdx,rdx     ; hi word of dividend
    js      dividend    ; signed ?
    test    r9,r9       ; hi word of divisor
    js      divisor     ; signed ?
    jmp     _aulldiv

divisor:
    neg     r9
    neg     r8
    sbb     r9,0
    call    _aulldiv
    neg     rdx
    neg     rax
    sbb     rdx,0
    ret

dividend:
    neg     rdx
    neg     rcx
    sbb     rdx,0
    test    r9,r9
    jns     @F
    neg     r9
    neg     r8
    sbb     r9,0
    call    _aulldiv
    neg     r9
    neg     r8
    sbb     r9,0
    ret
@@:
    call    _aulldiv
    neg     r9
    neg     r8
    sbb     r9,0
    neg     rdx
    neg     rax
    sbb     rdx,0
    ret

    END
