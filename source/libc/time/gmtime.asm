; GMTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

    .data
     tb tm <>

    .code

gmtime proc tp:ptr time_t

    _gmtime(ldr(tp), &tb)
    ret

gmtime endp

    end
