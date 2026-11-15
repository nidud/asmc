; DOSDATETIMETOFILETIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fileapi.inc
include timezoneapi.inc

.code

 DosDateTimeToFileTime proc WINAPI uses rbx wFatDate:WORD, wFatTime:WORD, lpFileTime:LPFILETIME
   .new s:SYSTEMTIME
    ldr rbx,lpFileTime
    .if ( !rbx )
        .return( FALSE )
    .endif
    mov     s.wDayOfWeek,0
    mov     s.wMilliseconds,0
    movzx   eax,wFatDate
    mov     ecx,eax
    shr     ecx,9
    add     ecx,1980
    mov     s.wYear,cx
    mov     ecx,eax
    shr     ecx,5
    and     ecx,1111B
    mov     s.wMonth,cx
    and     eax,11111B
    mov     s.wDay,ax
    movzx   eax,wFatTime
    mov     ecx,eax
    shr     ecx,11
    mov     s.wHour,cx
    mov     ecx,eax
    shr     ecx,5
    and     ecx,111111B
    mov     s.wMinute,cx
    and     eax,11111B
    shl     eax,1
    mov     s.wSecond,ax
    .return SystemTimeToFileTime(&s, rbx)
    endp

    end
