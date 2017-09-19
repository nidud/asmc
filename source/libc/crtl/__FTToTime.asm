include time.inc
include winbase.inc

    .code

__FTToTime proc uses ecx edx ft:LPFILETIME

  local ftime:FILETIME
  local stime:SYSTEMTIME

    FileTimeToLocalFileTime(ft, &ftime)
    FileTimeToSystemTime(&ftime, &stime)
    __STToTime(&stime)
    ret

__FTToTime endp

    END
