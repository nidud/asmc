; _SET_ERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .code

_set_errno proc uses eax value:int_t

    mov eax,value
    mov errno,eax
    ret

_set_errno endp

    end
