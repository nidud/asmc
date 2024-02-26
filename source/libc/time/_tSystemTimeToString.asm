; _TSYSTEMTIMETOSTRING.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include time.inc
include winnls.inc

    .code

SystemTimeToString proc string:LPTSTR, stime:ptr SYSTEMTIME
ifndef __UNIX__
ifdef _UNICODE
    GetTimeFormatEx( NULL, TIME_FORCE24HOURFORMAT, stime, NULL, string, 9 )
else
   .new timeString[64]:wchar_t

    GetTimeFormatEx(NULL, TIME_FORCE24HOURFORMAT, stime, NULL, &timeString, lengthof(timeString))

    .for ( rdx = string, ecx = 0 : ecx < 9 : ecx++ )
        mov al,byte ptr timeString[rcx*2]
        mov [rdx+rcx],al
    .endf
    mov byte ptr [rdx+rcx],0
endif
endif
   .return( string )
SystemTimeToString endp

    END
