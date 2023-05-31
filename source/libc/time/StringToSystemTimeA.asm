; STRINGTOSYSTEMTIMEA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include stdlib.inc

    .code

    assume rbx:ptr SYSTEMTIME

StringToSystemTimeA proc uses rbx string:ptr char_t, lpSystemTime:ptr SYSTEMTIME

    ldr rcx,string
    ldr rbx,lpSystemTime
    mov rdx,rcx
    .repeat
        mov al,[rdx]
        add rdx,1
    .until ( al > '9' || al < '0' )
    mov string,rdx
    atol(rcx)
    mov [rbx].wHour,ax
    atol(string)
    mov [rbx].wMinute,ax
    mov rcx,string
    .repeat
        mov al,[rcx]
        add rcx,1
    .until ( al > '9' || al < '0' )
    atol(rcx)
    mov [rbx].wSecond,ax
    mov [rbx].wMilliseconds,0
    mov rax,rbx
    ret

StringToSystemTimeA endp

    end
