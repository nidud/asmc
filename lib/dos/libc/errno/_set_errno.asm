; _SET_ERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .code

_set_errno proc value:int_t

    mov ax,value
    mov errno,ax
    mov ax,-1
    ret

_set_errno endp

    end
