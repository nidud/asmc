; STRINGTOSYSTEMTIMEW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include stdlib.inc

    .code

    assume rbx:ptr SYSTEMTIME

StringToSystemTimeW proc uses rbx string:ptr wchar_t, lpSystemTime:ptr SYSTEMTIME

    ldr rcx,string
    ldr rbx,lpSystemTime
    mov rdx,rcx
    .repeat
        mov ax,[rdx]
        add rdx,2
    .until ( ax > '9' || ax < '0' )
    mov string,rdx
    _wtol(rcx)
    mov [rbx].wHour,ax
    _wtol(string)
    mov [rbx].wMinute,ax
    mov rcx,string
    .repeat
        mov ax,[rcx]
        add rcx,2
    .until ( ax > '9' || ax < '0' )
    _wtol(rcx)
    mov [rbx].wSecond,ax
    mov [rbx].wMilliseconds,0
    mov rax,rbx
    ret

StringToSystemTimeW endp

    end
