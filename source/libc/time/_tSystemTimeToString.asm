; _TSYSTEMTIMETOSTRING.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include time.inc
include winnls.inc

.code

SystemTimeToString proc uses rbx string:tstring_t, stime:ptr SYSTEMTIME
    ldr rbx,string
ifndef __UNIX__
ifdef _UNICODE
    GetTimeFormatEx( NULL, TIME_FORCE24HOURFORMAT, ldr(stime), NULL, rbx, 9 )
else
   .new timeString[64]:wchar_t
    GetTimeFormatEx(NULL, TIME_FORCE24HOURFORMAT, ldr(stime), NULL, &timeString, lengthof(timeString))
    .for ( ecx = 0 : ecx < 9 : ecx++ )
        mov al,byte ptr timeString[rcx*2]
        mov [rbx+rcx],al
    .endf
    mov byte ptr [rbx+rcx],0
endif
endif
    .return( rbx )
    endp

    end
