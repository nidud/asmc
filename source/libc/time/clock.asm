; CLOCK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
ifndef __UNIX__
include winbase.inc
endif

.data
 __stime uint_t 0

.code

clock proc
ifdef __UNIX__
    times(NULL)
else
    GetTickCount()
endif
    sub eax,__stime
    ret
    endp

__inittime proc
ifdef __UNIX__
    times(NULL)
else
    GetTickCount()
endif
    mov __stime,eax
    ret
    endp

.pragma init(__inittime, 20)

    end
