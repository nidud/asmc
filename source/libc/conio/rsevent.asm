; RSEVENT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

rsevent proc uses rbx robj:PIDD, dobj:PDOBJ

    ldr rbx,dobj

    dlevent(rbx)
    mov edx,[rbx].DOBJ.rc
    mov rcx,robj
    mov [rcx].RIDD.rc,edx
    ret

rsevent endp

    end
