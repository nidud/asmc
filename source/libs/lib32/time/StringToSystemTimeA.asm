; STRINGTOSYSTEMTIMEA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include stdlib.inc

    .code

    assume edi:ptr SYSTEMTIME

StringToSystemTimeA proc uses esi edi string:ptr char_t, lpSystemTime:ptr SYSTEMTIME

    mov esi,string
    mov ecx,esi
    mov edi,lpSystemTime
    .repeat
        lodsb
    .until al > '9' || al < '0'
    atol(ecx)
    mov [edi].wHour,ax
    atol(esi)
    mov [edi].wMinute,ax
    .repeat
        lodsb
    .until al > '9' || al < '0'
    atol(esi)
    mov [edi].wSecond,ax
    mov [edi].wMilliseconds,0
    mov eax,edi
    ret

StringToSystemTimeA endp

    end
