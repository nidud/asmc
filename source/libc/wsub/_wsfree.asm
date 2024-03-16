; _WSFREE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include wsub.inc
include malloc.inc

.code

    assume rbx:PWSUB

_wsfree proc uses rbx wp:PWSUB

    ldr rbx,wp

    .while ( [rbx].count )

        dec [rbx].count
        mov ecx,[rbx].count
        mov rdx,[rbx].fcb
        free([rdx+rcx*size_t])
    .endw
    free([rbx].fcb)
    mov [rbx].fcb,NULL
    ret

_wsfree endp

    end
