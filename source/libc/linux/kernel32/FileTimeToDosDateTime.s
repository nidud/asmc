; FILETIMETODOSDATETIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fileapi.inc
include timezoneapi.inc

.code

 FileTimeToDosDateTime proc WINAPI uses rbx lpFileTime:LPFILETIME, lpFatDate:LPWORD, lpFatTime:LPWORD
   .new s:SYSTEMTIME
    ldr rbx,lpFatDate
    .if ( !ldr(lpFileTime) || !rbx || !ldr(lpFatTime) )
        .return( FALSE )
    .endif
    .ifd !FileTimeToSystemTime(ldr(lpFileTime), &s)
        .return( FALSE )
    .endif
    movzx eax,s.wYear
    .if ( eax < 1980 || eax > 2107 )
        .return( FALSE )
    .endif
    sub     eax,1980
    shl     eax,9
    movzx   ecx,s.wMonth
    shl     ecx,5
    or      eax,ecx
    or      ax,s.wDay
    mov     [rbx],ax
    movzx   eax,s.wHour
    shl     eax,11
    movzx   ecx,s.wMinute
    shl     ecx,5
    or      eax,ecx
    movzx   ecx,s.wSecond
    shr     ecx,1
    or      eax,ecx
    mov     rbx,lpFatTime
    mov     [rbx],ax
    mov     eax,TRUE
    ret
    endp

    end
