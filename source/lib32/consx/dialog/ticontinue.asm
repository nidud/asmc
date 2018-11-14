; TICONTINUE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

ticontinue proc
    xor eax,eax ; _TI_CONTINUE - continue edit
    ret
ticontinue endp

    END
