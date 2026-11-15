; GETTICKCOUNT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include sysinfoapi.inc

.code

GetTickCount proc WINAPI
    GetTickCount64()
    ret
    endp

    end
