; DFREE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include malloc.inc

.code

    assume rbx:PDIRENT

_dfree proc uses rbx d:PDIRENT

    ldr rbx,d

    .while ( [rbx].count )

        dec [rbx].count
        mov ecx,[rbx].count
        mov rdx,[rbx].fcb
        free([rdx+rcx*size_t])
    .endw
    mov rcx,[rbx].fcb
    mov [rbx].fcb,NULL
    .if ( rcx )
        free(rcx)
    .endif
    ret

_dfree endp

    end
