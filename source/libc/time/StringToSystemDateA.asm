; STRINGTOSYSTEMDATEA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include time.inc
include stdlib.inc

    .code

    assume rdi:ptr SYSTEMTIME

StringToSystemDateA proc uses rsi rdi rbx string:ptr char_t, lpSystemTime:ptr SYSTEMTIME

  local separator:byte

    mov rdi,lpSystemTime
    mov rsi,string
    mov rcx,rsi

    .repeat
        lodsb
    .until ( al > '9' || al < '0' )

    mov separator,al
    mov ebx,atol(rcx)
    mov ecx,atol(rsi)

    .repeat
        lodsb
    .until ( al > '9' || al < '0' )

    xchg rcx,rsi
    mov ecx,atol(rcx)
    mov rdx,string
    mov al,[rdx+2]

    .if ( al <= '9' && al >= '0' )  ; YMD

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

StringToSystemDateA endp

    end
