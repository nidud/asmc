; SYSTEMDATETOSTRINGW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winnls.inc

    .code

SystemDateToStringW proc string:ptr wchar_t, date:ptr SYSTEMTIME
if (_WIN32_WINNT GE _WIN32_WINNT_VISTA)
    GetDateFormatEx(NULL, DATE_SHORTDATE, date, NULL, string, 11, NULL)
else
    mov ecx,GetUserDefaultLCID()
    GetDateFormatW(ecx, DATE_SHORTDATE, date, NULL, string, 11)
endif
    .return( string )

SystemDateToStringW endp

    END
