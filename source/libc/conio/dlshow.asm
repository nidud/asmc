; DLSHOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rbx:PDOBJ

dlshow proc uses rbx dobj:PDOBJ

    ldr rbx,dobj
    .if rcshow([rbx].rc, [rbx].flags, [rbx].window)

        or [rbx].flags,W_VISIBLE
    .endif
    ret

dlshow endp

    end
