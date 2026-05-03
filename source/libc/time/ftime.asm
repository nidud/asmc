; FTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

ifndef __UNIX__
include winbase.inc
endif
include time.inc
include sys/timeb.inc

    .code

    assume rbx:ptr _timeb

_ftime proc uses rbx tp:ptr _timeb

    ldr rbx,tp

ifdef __UNIX__
   .new tv:timeval
   .new tz:timezone
else
   .new t:tm
   .new d:SYSTEMTIME
endif
    _tzset()

    mov     ecx,60
    mov     eax,_timezone
    cdq
    idiv    ecx
    mov     [rbx].timezone,ax

ifdef __UNIX__

    .ifsd ( gettimeofday( &tv, &tz ) >= 0 )

        mov [rbx].time,tv.tv_sec
        mov rax,tv.tv_usec
        xor edx,edx
        mov rcx,1000
        div rcx
        mov [rbx].millitm,ax
    .endif
    mov eax,_daylight

else

    GetLocalTime(&d)

    mov     [rbx].millitm,d.wMilliseconds
    movzx   eax,d.wYear
    sub     eax,1900
    mov     t.tm_year,eax
    movzx   eax,d.wDay
    mov     t.tm_mday,eax
    movzx   eax,d.wMonth
    dec     eax
    mov     t.tm_mon,eax
    movzx   eax,d.wHour
    mov     t.tm_hour,eax
    movzx   eax,d.wMinute
    mov     t.tm_min,eax
    movzx   eax,d.wSecond
    mov     t.tm_sec,eax
    mov     t.tm_isdst,-1
    mov     [rbx].time,mktime(&t)
    mov     eax,t.tm_isdst
endif
    mov     [rbx].dstflag,ax
    xor     eax,eax
    ret
    endp

    end
