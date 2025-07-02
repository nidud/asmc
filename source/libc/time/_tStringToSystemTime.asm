; _TSTRINGTOSYSTEMTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include stdlib.inc
include tchar.inc

    .code

    assume rbx:ptr SYSTEMTIME

StringToSystemTime proc uses rbx string:tstring_t, lpSystemTime:ptr SYSTEMTIME

    ldr rcx,string
    ldr rbx,lpSystemTime
    mov rdx,rcx
    .repeat
        movzx eax,tchar_t ptr [rdx]
        add rdx,tchar_t
    .until ( eax > '9' || eax < '0' )
    mov string,rdx
    _tstol(rcx)
    mov [rbx].wHour,ax
    _tstol(string)
    mov [rbx].wMinute,ax
    mov rcx,string
    .repeat
        movzx eax,tchar_t ptr [rcx]
        add rcx,tchar_t
    .until ( eax > '9' || eax < '0' )
    _tstol(rcx)
    mov [rbx].wSecond,ax
    mov [rbx].wMilliseconds,0
    mov rax,rbx
    ret

StringToSystemTime endp

    end
