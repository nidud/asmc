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

    .ifd rchide([rbx].rc, [rbx].flags, [rbx].window)

        and [rbx].flags,not W_VISIBLE
    .endif
    ret

dlhide endp

    end
