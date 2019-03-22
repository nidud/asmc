; _ERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .data
    ErrnoNoMem int_t ENOMEM

    .code

_errno proc

    lea rax,ErrnoNoMem
    ret

_errno endp

    end
