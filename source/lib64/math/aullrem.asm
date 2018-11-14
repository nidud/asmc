; AULLREM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;


    _aulldiv proto

    .code

_aullrem::
__umodti3::

    call    _aulldiv
    xchg    r9,rdx
    xchg    r8,rax
    ret

    END
