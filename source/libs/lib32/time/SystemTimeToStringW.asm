; SYSTEMTIMETOSTRINGW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include time.inc
include winnls.inc

    .code

SystemTimeToStringW proc string:ptr wchar_t, stime:ptr SYSTEMTIME
if (_WIN32_WINNT GE _WIN32_WINNT_VISTA)
    GetTimeFormatEx(NULL, TIME_FORCE24HOURFORMAT, stime, NULL, string, 9)
else
    mov ecx,GetUserDefaultLCID()
    GetTimeFormatW(ecx, TIME_FORCE24HOURFORMAT, stime, NULL, string, 9)
endif
    .return( string )

SystemTimeToStringW endp

    END
