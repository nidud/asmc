; _FORCDECPT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include fltintrn.inc

    .code
    ;
    ; '#' and precision == 0 means force a decimal point
    ;
_forcdecpt proc uses rbx buffer:LPSTR

    mov rbx,rdi
    .if !strchr(rdi, '.')

        strcat(rbx, ".0")
    .endif
    ret

_forcdecpt endp

    END
