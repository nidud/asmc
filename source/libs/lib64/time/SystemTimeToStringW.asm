; SYSTEMTIMETOSTRINGW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include time.inc
include winnls.inc

    .code

SystemTimeToStringW proc string:ptr wchar_t, stime:ptr SYSTEMTIME

    GetTimeFormatEx(NULL, TIME_FORCE24HOURFORMAT, rdx, NULL, rcx, 9)
   .return( string )

SystemTimeToStringW endp

    END
