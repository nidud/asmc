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
    mov edx,[rbx+4]
    mov rcx,robj
    mov [rcx+6],edx
    ret

rsevent endp

    end
