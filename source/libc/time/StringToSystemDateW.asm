; STRINGTOSYSTEMDATEW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include stdlib.inc

    .code

    assume rdi:ptr SYSTEMTIME

StringToSystemDateW proc uses rsi rdi rbx string:ptr wchar_t, lpSystemTime:ptr SYSTEMTIME

  local separator:word

    mov rdi,lpSystemTime
    mov rsi,string
    mov rcx,rsi

    .repeat
        lodsw
    .until ( ax > '9' || ax < '0' )

    mov separator,ax
    mov ebx,_wtol(rcx)
    mov ecx,_wtol(rsi)

    .repeat
        lodsw
    .until ( ax > '9' || ax < '0' )

    xchg rcx,rsi
    mov ecx,_wtol(rcx)
    mov rdx,string
    mov ax,[rdx+4]

    .if ( ax <= '9' && ax >= '0' )  ; YMD

        mov [rdi].wYear,bx
        mov [rdi].wMonth,si
        mov [rdi].wDay,cx

    .elseif ( separator == '/' )    ; MDY

        mov [rdi].wYear,cx
        mov [rdi].wMonth,bx
        mov [rdi].wDay,si
    .else

        mov [rdi].wYear,cx          ; DMY
        mov [rdi].wMonth,si
        mov [rdi].wDay,bx
    .endif
    mov [rdi].wDayOfWeek,0
    mov rax,rdi
    ret

StringToSystemDateW endp

    end
