; _TFILETIMETOSTRING.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include time.inc
include winbase.inc

    .code

FileTimeToString proc string:tstring_t, ft:ptr FILETIME
  local ftime:FILETIME, stime:SYSTEMTIME
ifndef __UNIX__
    FileTimeToLocalFileTime(ft, &ftime)
    FileTimeToSystemTime(&ftime, &stime)
    SystemTimeToString(string, &stime)
endif
    ret
    endp

    END
