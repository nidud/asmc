; CLOCK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include sysinfoapi.inc

.data
 __stime uint_t 0

.code

clock proc
    GetTickCount()
    sub eax,__stime
    ret
    endp

__inittime proc
    GetTickCount()
    mov __stime,eax
    ret
    endp

.pragma init(__inittime, 20)

    end
