; _SET_ERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

_errno proto __cdecl

    .code

_set_errno proc frame value:int_t

    _errno()
    mov [rax],ecx
    ret

_set_errno endp

    end
