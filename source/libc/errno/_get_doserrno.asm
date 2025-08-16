; _GET_DOSERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .code

_get_doserrno proc pValue:ptr uint_t

    ldr rcx,pValue

    mov eax,_doserrno
    .if rcx
        mov [rcx],eax
    .endif
    ret

_get_doserrno endp

    end
