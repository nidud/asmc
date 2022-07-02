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

_set_errno proc value:int_t
ifndef _WIN64
    mov ecx,value
endif
    mov ErrnoNoMem,ecx
    ret

_set_errno endp

_get_errno proc pValue:ptr int_t
ifndef _WIN64
    mov ecx,pValue
endif
    mov eax,ErrnoNoMem
    .if rcx
        mov [rcx],eax
    .endif
    ret

_get_errno endp

    end
