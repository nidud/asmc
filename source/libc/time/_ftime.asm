; _FTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include winbase.inc
include time.inc
include sys/timeb.inc

    .code

    assume rdi:ptr _timeb

_ftime proc uses rdi tp:ptr _timeb

  local t:tm
  local d:SYSTEMTIME

    _tzset()

    mov rdi,tp
    mov ecx,60
    mov eax,_timezone
    xor edx,edx
    div ecx
    mov [rdi].timezone,ax

    GetLocalTime(&d)

    mov [rdi].millitm,d.wMilliseconds
    movzx eax,d.wYear
    sub eax,1900
    mov t.tm_year,eax
    movzx eax,d.wDay
    mov t.tm_mday,eax
    movzx eax,d.wMonth
    dec eax
    mov t.tm_mon,eax
    movzx eax,d.wHour
    mov t.tm_hour,eax
    movzx eax,d.wMinute
    mov t.tm_min,eax
    movzx eax,d.wSecond
    mov t.tm_sec,eax
    mov t.tm_isdst,-1

    ;
    ; Call mktime() to compute time_t value and Daylight Savings Time flag.
    ;
    mov [rdi].time,mktime(&t)
    mov eax,t.tm_isdst
    mov [rdi].dstflag,ax
    ret

_ftime endp

    end
