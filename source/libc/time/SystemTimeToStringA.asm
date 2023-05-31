; SYSTEMTIMETOSTRINGA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include time.inc
include winnls.inc

    .code

SystemTimeToStringA proc string:ptr char_t, stime:ptr SYSTEMTIME
ifdef __UNIX__
    int 3
    ret
else
   .new timeString[64]:wchar_t

    GetTimeFormatEx(NULL, TIME_FORCE24HOURFORMAT, stime, NULL, &timeString, lengthof(timeString))

    .for ( rdx = string, ecx = 0 : ecx < 9 : ecx++ )
        mov al,byte ptr timeString[rcx*2]
        mov [rdx+rcx],al
    .endf
    mov byte ptr [rdx+rcx],0
   .return( string )
endif
SystemTimeToStringA endp

    END
