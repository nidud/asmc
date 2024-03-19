; _DCLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include malloc.inc

    .code

    assume rbx:PDIRENT

_dclose proc uses rbx d:PDIRENT

    ldr rbx,d

    _dfree(rbx)
    .if ( [rbx].flags & _D_MALLOC )

        free(rbx)
    .else
        free([rbx].path)
        mov [rbx].path,NULL
    .endif
    xor eax,eax
    ret

_dclose endp

    end
