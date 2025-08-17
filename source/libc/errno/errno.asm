; ERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .data
if not defined(_WIN64) and not defined(__UNIX__)
     errno label errno_t
endif
     ErrorNoMem errno_t ENOMEM

    .code

__errno_location::
ifndef _WIN64
__get_errno_ptr::
endif
_errno proc

    lea rax,ErrorNoMem
    ret

_errno endp

_set_errno proc value:int_t

    ldr ecx,value

    mov ErrorNoMem,ecx
    mov rax,-1
    ret

_set_errno endp

    end
