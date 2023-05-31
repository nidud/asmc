; FILETIMETOTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

    .code

FileTimeToTime proc ft:LPFILETIME
ifdef __UNIX__
    int 3
else
  local ftime:FILETIME
  local stime:SYSTEMTIME

    FileTimeToLocalFileTime(ft, &ftime)
    FileTimeToSystemTime(&ftime, &stime)
    SystemTimeToTime(&stime)
endif
    ret

FileTimeToTime endp

    END
