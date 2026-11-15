; SLEEP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include unistd.inc

.code

sleep proc seconds:uint_t
   .new req:timespec
   .new rem:timespec
    ldr eax,seconds
    mov req.tv_sec,rax
    mov req.tv_nsec,0
    .ifsd ( nanosleep(&req, &rem) < 0 )
        mov rax,rem.tv_sec
        .if ( rem.tv_nsec >= 500000000 )
            inc eax
        .endif
        .return
    .endif
    .return( 0 )
    endp

    end
