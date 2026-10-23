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

ifdef __UNIX__
ifdef _WIN64
ALIAS <__get_errno_ptr>=<_errno>
else
ALIAS <__errno_location>=<_errno>
endif
else
ALIAS <__get_errno_ptr>=<_errno>
ALIAS <__errno_location>=<_errno>
endif

_errno proc
    lea rax,ErrorNoMem
    ret
    endp

_set_errno proc value:int_t
    ldr ecx,value
    mov ErrorNoMem,ecx
    mov rax,-1
    ret
    endp

    end
