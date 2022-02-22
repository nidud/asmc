; TIMETOSYSTEMTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc

    .code

TimeToSystemTime proc Time:time_t, lpSystemTime:ptr SYSTEMTIME

    mov     [rdx].SYSTEMTIME.wDayOfWeek,0
    mov     [rdx].SYSTEMTIME.wMilliseconds,0
    mov     eax,ecx
    shr     eax,16
    shr     eax,9
    add     eax,DT_BASEYEAR
    mov     [rdx].SYSTEMTIME.wYear,ax
    mov     eax,ecx
    shr     eax,16
    shr     eax,5
    and     eax,1111B
    mov     [rdx].SYSTEMTIME.wMonth,ax
    mov     eax,ecx
    shr     eax,16
    and     eax,11111B
    mov     [rdx].SYSTEMTIME.wDay,ax
    movzx   eax,cx
    shr     eax,11
    mov     [rdx].SYSTEMTIME.wHour,ax
    movzx   eax,cx
    shr     eax,5
    and     ax,111111B
    mov     [rdx].SYSTEMTIME.wMinute,ax
    movzx   eax,cx
    and     eax,11111B
    shl     eax,1
    mov     [rdx].SYSTEMTIME.wSecond,ax
    mov     rax,rdx
    ret

TimeToSystemTime endp

    end
