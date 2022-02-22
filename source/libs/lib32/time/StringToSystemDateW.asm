; STRINGTOSYSTEMDATEW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include stdlib.inc

    .code

    assume edi:ptr SYSTEMTIME

StringToSystemDateW proc uses esi edi ebx string:ptr wchar_t, lpSystemTime:ptr SYSTEMTIME

  local separator:word

    mov edi,lpSystemTime
    mov esi,string
    mov ecx,esi
    .repeat
        lodsw
    .until ax > '9' || ax < '0'
    mov separator,ax
    mov ebx,_wtol(ecx)
    mov ecx,_wtol(esi)
    .repeat
        lodsw
    .until ax > '9' || ax < '0'
    xchg ecx,esi
    mov ecx,_wtol(ecx)
    mov edx,string
    mov ax,[edx+4]
    .if ( ax <= '9' && ax >= '0' )  ; YMD
        mov [edi].wYear,bx
        mov [edi].wMonth,si
        mov [edi].wDay,cx
    .elseif ( separator == '/' )    ; MDY
        mov [edi].wYear,cx
        mov [edi].wMonth,bx
        mov [edi].wDay,si
    .else
        mov [edi].wYear,cx          ; DMY
        mov [edi].wMonth,si
        mov [edi].wDay,bx
    .endif
    mov [edi].wDayOfWeek,0
    mov eax,edi
    ret

StringToSystemDateW endp

    end
