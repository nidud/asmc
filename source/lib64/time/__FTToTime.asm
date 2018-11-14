; __FTTOTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winbase.inc

    .code

__FTToTime proc ft:LPFILETIME

  local ftime:FILETIME
  local stime:SYSTEMTIME

    FileTimeToLocalFileTime( rcx, &ftime )
    FileTimeToSystemTime( &ftime, &stime )
    __STToTime( &stime )
    ret

__FTToTime endp

    end
