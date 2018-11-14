; FDATETOSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

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
