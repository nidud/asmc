; RCCLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include malloc.inc

    .code

rcclose proc rect:S_RECT, fl:UINT, wp:PVOID

    mov eax,fl
    .if eax & _D_DOPEN

        .if eax & _D_ONSCR

            rchide(rect, fl, wp)
            mov eax,fl
        .endif

        .if !(eax & _D_MYBUF)

            free(wp)
        .endif
    .endif

    mov eax,fl
    and eax,_D_DOPEN
    ret

rcclose endp

    END
