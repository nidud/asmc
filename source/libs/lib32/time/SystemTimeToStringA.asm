; SYSTEMTIMETOSTRINGA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include time.inc
include winnls.inc

    .code

SystemTimeToStringA proc string:ptr char_t, stime:ptr SYSTEMTIME
if (_WIN32_WINNT GE _WIN32_WINNT_VISTA)
   .new timeString[64]:wchar_t
    GetTimeFormatEx(NULL, TIME_FORCE24HOURFORMAT, stime, NULL, &timeString, lengthof(timeString))
    .for ( edx = string, ecx = 0 : ecx < 9 : ecx++ )
        mov al,byte ptr timeString[ecx*2]
        mov [edx+ecx],al
    .endf
    mov byte ptr [edx+ecx],0
else
    mov ecx,GetUserDefaultLCID()
    GetTimeFormatA(ecx, TIME_FORCE24HOURFORMAT, stime, NULL, string, 9)
endif
    .return( string )

SystemTimeToStringA endp

    END
