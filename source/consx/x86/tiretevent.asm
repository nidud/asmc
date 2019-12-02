; TIRETEVENT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

tiretevent proc
    mov eax,_TE_RETEVENT ; return current event (keystroke)
    ret
tiretevent endp

    END
