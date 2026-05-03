; GET_DAYLIGHT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include errno.inc

.code

_get_daylight proc pdaylight:ptr int_t
    ldr rcx,pdaylight
    mov eax,EINVAL
    .if ( rcx )
        mov eax,_daylight
        mov [rcx],eax
        xor eax,eax
    .endif
    ret
    endp

    end
