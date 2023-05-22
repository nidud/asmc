; _ERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .data
ifndef _WIN64
     errno label errno_t
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
    ret

_set_errno endp

_get_errno proc pValue:ptr int_t

    ldr rcx,pValue
    mov eax,ErrorNoMem
    .if rcx
        mov [rcx],eax
    .endif
    ret

_get_errno endp

    end
