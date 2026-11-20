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
   .new st_tz_local:SYSTEMTIME
   .new st_tz_utc:SYSTEMTIME
   .new tzi:TIME_ZONE_INFORMATION = { 0 }

    printf("=== 1. Live System & Local Time ===\n")
    GetSystemTime(&st_utc)
    GetLocalTime(&st_local)
    PrintSystemTime("  GetSystemTime (UTC)  ", &st_utc)
    PrintSystemTime("  GetLocalTime  (Local)", &st_local)

    printf("\n=== 2. SystemTimeToTzSpecificLocalTime (NULL = /etc/localtime) ===\n")
    SystemTimeToTzSpecificLocalTime(NULL, &st_utc, &st_tz_local)
    TzSpecificLocalTimeToSystemTime(NULL, &st_tz_local, &st_tz_utc)
    PrintSystemTime("  UTC -> Local         ", &st_tz_local)
    PrintSystemTime("  Local -> UTC         ", &st_tz_utc)

    printf("\n=== 3. Explicit TIME_ZONE_INFORMATION (EST, Bias = +300 min / UTC-5) ===\n")
    mov tzi.Bias,300
    SystemTimeToTzSpecificLocalTime(&tzi, &st_utc, &st_tz_local)
    TzSpecificLocalTimeToSystemTime(&tzi, &st_tz_local, &st_tz_utc)
    PrintSystemTime("  UTC -> EST (-5h)     ", &st_tz_local)
    PrintSystemTime("  EST -> UTC (+5h)     ", &st_tz_utc)
    .return( 0 )
    endp

    end
