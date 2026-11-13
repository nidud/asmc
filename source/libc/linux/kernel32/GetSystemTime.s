; GETSYSTEMTIME.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include sysinfoapi.inc
include timezoneapi.inc

.code

 GetSystemTime proc WINAPI lpSystemTime:LPSYSTEMTIME
    .new ft:FILETIME
    .if ( ldr(lpSystemTime) )
        GetSystemTimeAsFileTime(&ft)
        FileTimeToSystemTime(&ft, lpSystemTime)
    .endif
    ret
    endp

    end
