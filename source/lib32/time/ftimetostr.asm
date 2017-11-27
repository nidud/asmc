include time.inc
include winbase.inc

    .code

ftimetostr proc uses ecx edx string:LPSTR, ft:LPFILETIME

local ftime:FILETIME, stime:SYSTEMTIME

    FileTimeToLocalFileTime(ft, &ftime)
    FileTimeToSystemTime(&ftime, &stime)
    SystemTimeToString(string, &stime)
    ret

ftimetostr endp

    END
