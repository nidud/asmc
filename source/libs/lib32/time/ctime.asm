; CTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

    .code

ctime proc timp:ptr time_t

    .if localtime(timp)
        asctime(eax)
    .endif
    ret

ctime endp

    end
