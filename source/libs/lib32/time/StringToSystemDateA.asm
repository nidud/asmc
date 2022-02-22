; STRINGTOSYSTEMDATEA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include time.inc
include stdlib.inc

    .code

    assume edi:ptr SYSTEMTIME

StringToSystemDateA proc uses esi edi ebx string:ptr char_t, lpSystemTime:ptr SYSTEMTIME

  local separator:byte

    mov edi,lpSystemTime
    mov esi,string
    mov ecx,esi
    .repeat
        lodsb
    .until al > '9' || al < '0'
    mov separator,al
    mov ebx,atol(ecx)
    mov ecx,atol(esi)
    .repeat
        lodsb
    .until al > '9' || al < '0'
    xchg ecx,esi
    mov ecx,atol(ecx)
    mov edx,string
    mov al,[edx+2]
    .if ( al <= '9' && al >= '0' )  ; YMD
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

StringToSystemDateA endp

    end
