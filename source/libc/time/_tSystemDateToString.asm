; _TSYSTEMDATETOSTRING.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include winnls.inc

    .code

SystemDateToString proc string:LPTSTR, date:ptr SYSTEMTIME

ifndef __UNIX__
ifdef _UNICODE
    GetDateFormatEx(NULL, DATE_SHORTDATE, date, NULL, string, 11, NULL)
else
   .new dateString[64]:wchar_t

    GetDateFormatEx(NULL, DATE_SHORTDATE, date, NULL, &dateString, lengthof(dateString), NULL)

    .for ( rdx = string, ecx = 0 : ecx < 10 : ecx++ )

        mov al,byte ptr dateString[rcx*2]
        mov [rdx+rcx],al
    .endf
    mov byte ptr [rdx+rcx],0
endif
endif
   .return( string )

SystemDateToString endp

    end
