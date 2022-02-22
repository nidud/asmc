; SYSTEMDATETOSTRINGW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winnls.inc

    .code

SystemDateToStringW proc string:ptr wchar_t, date:ptr SYSTEMTIME

    GetDateFormatEx(NULL, DATE_SHORTDATE, rdx, NULL, rcx, 11, NULL)
   .return( string )

SystemDateToStringW endp

    END
