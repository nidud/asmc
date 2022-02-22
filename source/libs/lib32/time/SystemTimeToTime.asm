; SYSTEMTIMETOTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; unsigned SystemTimeToTime(SYSTEMTIME *lpSystemTime);
;
; Return:
;
;    edx - <date> yyyyyyymmmmddddd
;    ecx - <time> hhhhhmmmmmmsssss
;    eax - <date>:<time>
;
include time.inc

    .code

SystemTimeToTime proc uses edi lpSystemTime:ptr SYSTEMTIME

    mov     ecx,lpSystemTime
    movzx   eax,[ecx].SYSTEMTIME.wYear
    sub     eax,DT_BASEYEAR
    shl     eax,9
    movzx   edx,[ecx].SYSTEMTIME.wMonth
    shl     edx,5
    or      eax,edx
    or      ax,[ecx].SYSTEMTIME.wDay
    shl     eax,16
    mov     edi,eax
    movzx   eax,[ecx].SYSTEMTIME.wSecond
    shr     eax,1
    mov     edx,eax ; second/2
    mov     al,byte ptr [ecx].SYSTEMTIME.wHour
    movzx   ecx,byte ptr [ecx].SYSTEMTIME.wMinute
    shl     ecx,5
    shl     eax,11
    or      eax,ecx
    or      eax,edx
    mov     edx,edi ; <date> yyyyyyymmmmddddd
    mov     ecx,eax ; <time> hhhhhmmmmmmsssss
    or      eax,edx ; <date>:<time>
    shr     edx,16
    ret

SystemTimeToTime endp

    END
