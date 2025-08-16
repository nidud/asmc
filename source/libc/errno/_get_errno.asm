; _GET_ERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .code

_get_errno proc pValue:ptr int_t

    ldr rcx,pValue

    mov eax,errno
    .if rcx
        mov [rcx],eax
    .endif
    ret

_get_errno endp

    end
