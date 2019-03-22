; _SET_DOSERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .code

    option win64:rsp nosave

_set_doserrno proc value:ulong_t

    __doserrno()
    mov [rax],ecx
    xor eax,eax
    ret

_set_doserrno endp

    end
