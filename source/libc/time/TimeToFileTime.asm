; TIMETOFILETIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

.code

TimeToFileTime proc Time:time_t, lpFileTime:ptr FILETIME
ifdef __UNIX__
    int 3
    ret
else
  local SystemTime:SYSTEMTIME

    SystemTimeToFileTime(TimeToSystemTime(Time, &SystemTime), lpFileTime)
    LocalFileTimeToFileTime(lpFileTime, lpFileTime)
   .return(lpFileTime)
endif

TimeToFileTime endp

    END
