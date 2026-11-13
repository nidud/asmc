; GETLOCALTIME.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include sysinfoapi.inc
include timezoneapi.inc
include fileapi.inc

.code

 GetLocalTime proc WINAPI lpSystemTime:LPSYSTEMTIME
    .new ft_utc:FILETIME
    .new ft_local:FILETIME
    .if ( ldr(lpSystemTime) )
        GetSystemTimeAsFileTime(&ft_utc)
        FileTimeToLocalFileTime(&ft_utc, &ft_local)
        FileTimeToSystemTime(&ft_local, lpSystemTime)
    .endif
    ret
    endp

    end
