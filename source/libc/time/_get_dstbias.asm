; _GET_DSTBIAS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include errno.inc

.code

_get_dstbias proc pdstbias:ptr long_t

    ldr rcx,pdstbias

    mov eax,EINVAL
    .if ( rcx )

        mov eax,_dstbias
        mov [rcx],eax
        xor eax,eax
    .endif
    ret

_get_dstbias endp

    end
