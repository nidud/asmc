; DLHIDE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rbx:PDOBJ

dlhide proc uses rbx dobj:PDOBJ

    ldr rbx,dobj
    .if rchide([rbx].rc, [rbx].flag, [rbx].wp)

        and [rbx].flag,not W_VISIBLE
    .endif
    ret

dlhide endp

    end
