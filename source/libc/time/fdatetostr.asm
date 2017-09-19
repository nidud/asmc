include time.inc
include stdio.inc
include winbase.inc

    .code

fdatetostr proc uses ecx edx string:LPSTR, ft:LPFILETIME

local ftime:FILETIME, stime:SYSTEMTIME

    FileTimeToLocalFileTime(ft, &ftime)
    FileTimeToSystemTime(&ftime, &stime)
    SystemDateToString(string, &stime)
    ret

fdatetostr endp

    END
