; ERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .data
ifndef _WIN64
ifndef __UNIX__
     errno label errno_t
endif
endif
     ErrorNoMem errno_t ENOMEM

    .code

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
