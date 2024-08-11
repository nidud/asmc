; FORCDECPT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include fltintrn.inc

    .code

    ; '#' and precision == 0 means force a decimal point

_forcdecpt proc uses rbx buffer:string_t

    ldr rbx,buffer
    .if !strchr( rbx, '.' )
        strcat( rbx, ".0" )
    .endif
    ret

_forcdecpt endp

    end
