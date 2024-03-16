; _WSCLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include wsub.inc
include malloc.inc

.code

    assume rbx:PWSUB

_wsclose proc uses rbx wp:PWSUB

    ldr rbx,wp

    _wsfree(rbx)
    .if ( [rbx].flags & _W_MALLOC )

        free(rbx)
    .else
        free([rbx].path)
        mov [rbx].path,NULL
    .endif
    xor eax,eax
    ret

_wsclose endp

    end
