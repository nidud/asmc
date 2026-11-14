;
; Test case for Linux WinAPI wrappers
;

include stdio.inc
include sysinfoapi.inc
include timezoneapi.inc

.code

 PrintSystemTime proc uses rbx text:LPSTR, lpST:LPSYSTEMTIME
    ldr rbx,lpST
    printf("%s: %04d-%02d-%02d %02d:%02d:%02d.%03d (DOW=%d)\n",
           text,
           [rbx].SYSTEMTIME.wYear,
           [rbx].SYSTEMTIME.wMonth,
           [rbx].SYSTEMTIME.wDay,
           [rbx].SYSTEMTIME.wHour,
           [rbx].SYSTEMTIME.wMinute,
           [rbx].SYSTEMTIME.wSecond,
           [rbx].SYSTEMTIME.wMilliseconds,
           [rbx].SYSTEMTIME.wDayOfWeek)
    ret
    endp

 main proc
   .new st_utc:SYSTEMTIME
   .new st_local:SYSTEMTIME
    GetSystemTime(&st_utc)
    GetLocalTime(&st_local)
    PrintSystemTime("GetSystemTime (UTC)  ", &st_utc)
    PrintSystemTime("GetLocalTime  (Local)", &st_local)
    .return( 0 )
    endp

    end
