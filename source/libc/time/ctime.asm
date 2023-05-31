; CTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

    .code

ctime proc timp:ptr time_t

    ldr rcx,timp
    .if localtime(rcx)
        asctime(rax)
    .endif
    ret

ctime endp

    end
