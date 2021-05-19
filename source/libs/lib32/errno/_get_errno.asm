; _GET_ERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .code

_get_errno proc pValue:ptr int_t

    mov eax,errno
    mov ecx,pValue
    .if ecx
        mov [ecx],eax
    .endif
    ret

_get_errno endp

    end
