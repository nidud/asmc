; TICMDFAILED.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

ticmdfailed proc
    mov eax,_TE_CMFAILED ; operation fail (end of line/buffer)
    ret
ticmdfailed endp

    END
