include time.inc
include stdio.inc

    .code

SystemDateToString proc uses ecx edx string:ptr sbyte, t:ptr SYSTEMTIME

    mov   eax,t
    movzx ecx,[eax].SYSTEMTIME.wDay
    movzx edx,[eax].SYSTEMTIME.wMonth
    movzx eax,[eax].SYSTEMTIME.wYear
    sprintf(string, "%02d.%02d.%d", ecx, edx, eax)
    mov eax,string
    ret

SystemDateToString endp

    END
