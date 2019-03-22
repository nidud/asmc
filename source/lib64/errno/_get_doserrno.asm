; _GET_DOSERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .code

    option win64:rsp nosave

_get_doserrno proc pValue:ptr ulong_t

    __doserrno()
    mov [rcx],eax
    xor eax,eax
    ret

_get_doserrno endp

    end
