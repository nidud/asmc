; _SET_DOSERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .code

_set_doserrno proc value:uint_t

    ldr ecx,value
    mov _doserrno,ecx
    ret

_set_doserrno endp

    end
