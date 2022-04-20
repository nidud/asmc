; _DOSMAPERR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .code

_dosmaperr proc oserrno:ulong_t

    _set_errno(edi)
    mov rax,-1
    ret

_dosmaperr endp

    end
