; STRINGTOSYSTEMTIMEW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include stdlib.inc

    .code

    assume rdi:ptr SYSTEMTIME

StringToSystemTimeW proc uses rsi rdi string:ptr wchar_t, lpSystemTime:ptr SYSTEMTIME

ifndef _WIN64
    mov ecx,string
    mov edx,lpSystemTime
endif
    mov rsi,rcx
    mov rdi,rdx

    .repeat
        lodsw
    .until ( ax > '9' || ax < '0' )

    _wtol(rcx)
    mov [rdi].wHour,ax
    _wtol(rsi)
    mov [rdi].wMinute,ax

    .repeat
        lodsw
    .until ( ax > '9' || ax < '0' )

    _wtol(rsi)
    mov [rdi].wSecond,ax
    mov [rdi].wMilliseconds,0
    mov rax,rdi
    ret

StringToSystemTimeW endp

    end
