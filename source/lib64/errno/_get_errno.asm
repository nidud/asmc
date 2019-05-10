; _GET_ERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .code

    option win64:rsp nosave

_get_errno proc frame pValue:ptr int_t

    mov eax,[_errno()]
    mov [rcx],eax
    xor eax,eax
    ret

_get_errno endp

    end
