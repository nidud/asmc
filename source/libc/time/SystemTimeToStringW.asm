; SYSTEMTIMETOSTRINGW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include time.inc
include winnls.inc

    .code

SystemTimeToStringW proc string:ptr wchar_t, stime:ptr SYSTEMTIME
ifdef __UNIX__
    int 3
    ret
else
    GetTimeFormatEx( NULL, TIME_FORCE24HOURFORMAT, stime, NULL, string, 9 )
   .return( string )
endif
SystemTimeToStringW endp

    END
