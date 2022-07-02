; STRINGTOSYSTEMTIMEA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include stdlib.inc

    .code

    assume rdi:ptr SYSTEMTIME

StringToSystemTimeA proc uses rsi rdi string:ptr char_t, lpSystemTime:ptr SYSTEMTIME

ifndef _WIN64
    mov ecx,string
    mov edx,lpSystemTime
endif
    mov rsi,rcx
    mov rdi,rdx

    .repeat
        lodsb
    .until ( al > '9' || al < '0' )

    atol(rcx)
    mov [rdi].wHour,ax
    atol(rsi)
    mov [rdi].wMinute,ax

    .repeat
        lodsb
    .until ( al > '9' || al < '0' )

    atol(rsi)
    mov [rdi].wSecond,ax
    mov [rdi].wMilliseconds,0
    mov rax,rdi
    ret

StringToSystemTimeA endp

    end
