; _GET_TIMEZONE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include errno.inc

.code

_get_timezone proc ptimezone:ptr long_t

    ldr rcx,ptimezone

    mov eax,EINVAL
    .if ( rcx )

        mov eax,_timezone
        mov [rcx],eax
        xor eax,eax
    .endif
    ret

_get_timezone endp

    end
