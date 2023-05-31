; FILETIMETOSTRINGA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include time.inc
include winbase.inc

    .code

FileTimeToStringA proc string:ptr char_t, ft:ptr FILETIME
ifdef __UNIX__
    int 3
else
  local ftime:FILETIME, stime:SYSTEMTIME

    FileTimeToLocalFileTime(ft, &ftime)
    FileTimeToSystemTime(&ftime, &stime)
    SystemTimeToStringA(string, &stime)
endif
    ret

FileTimeToStringA endp

    END
