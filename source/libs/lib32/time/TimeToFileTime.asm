; TIMETOFILETIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

    .code

TimeToFileTime proc Time:time_t, lpFileTime:ptr FILETIME

  local SystemTime:SYSTEMTIME

    SystemTimeToFileTime(TimeToSystemTime(Time, &SystemTime), lpFileTime)
    LocalFileTimeToFileTime(lpFileTime, lpFileTime)
   .return(lpFileTime)

TimeToFileTime endp

    END
