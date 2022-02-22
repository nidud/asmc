; STRINGTOSYSTEMTIMEW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include stdlib.inc

    .code

    assume edi:ptr SYSTEMTIME

StringToSystemTimeW proc uses esi edi string:ptr wchar_t, lpSystemTime:ptr SYSTEMTIME

    mov esi,string
    mov ecx,esi
    mov edi,lpSystemTime
    .repeat
        lodsw
    .until ax > '9' || ax < '0'
    _wtol(ecx)
    mov [edi].wHour,ax
    _wtol(esi)
    mov [edi].wMinute,ax
    .repeat
        lodsw
    .until ax > '9' || ax < '0'
    _wtol(esi)
    mov [edi].wSecond,ax
    mov [edi].wMilliseconds,0
    mov eax,edi
    ret

StringToSystemTimeW endp

    end
