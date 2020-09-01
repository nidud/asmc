; ALLREM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    _alldiv proto

    .code

_allrem::
__modti3::

    call    _alldiv
    xchg    r9,rdx
    xchg    r8,rax
    ret

    END
