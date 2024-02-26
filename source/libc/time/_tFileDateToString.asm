; _TFILEDATETOSTRING.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include time.inc
include winbase.inc

    .code

FileDateToString proc string:LPTSTR, ft:ptr FILETIME

  local ftime:FILETIME, stime:SYSTEMTIME

ifndef __UNIX__
    FileTimeToLocalFileTime(ft, &ftime)
    FileTimeToSystemTime(&ftime, &stime)
    SystemDateToString(string, &stime)
endif
    ret

FileDateToString endp

    END
