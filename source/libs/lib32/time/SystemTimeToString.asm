; SYSTEMTIMETOSTRING.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include stdio.inc

    .code

SystemTimeToString proc uses ecx edx string:LPSTR, t:LPSYSTEMTIME
    mov   eax,t
    movzx ecx,[eax].SYSTEMTIME.wSecond
    movzx edx,[eax].SYSTEMTIME.wMinute
    movzx eax,[eax].SYSTEMTIME.wHour
    sprintf(string, "%02d:%02d:%02d", eax, edx, ecx)
    mov eax,string
    ret
SystemTimeToString endp

    END
