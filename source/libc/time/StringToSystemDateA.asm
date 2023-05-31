; STRINGTOSYSTEMDATEA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include time.inc
include stdlib.inc

    .code

    assume rbx:ptr SYSTEMTIME

StringToSystemDateA proc uses rbx string:ptr char_t, lpSystemTime:ptr SYSTEMTIME

   .new v0:int_t
   .new v1:int_t
   .new wc:char_t
   .new yc:char_t

    ldr rbx,lpSystemTime
    ldr rcx,string
    mov al,[rdx+2]
    mov yc,al
    mov rdx,rcx
    .repeat
       mov al,[rdx]
       inc rdx
    .until ( al > '9' || al < '0' )
    mov wc,al
    mov string,rdx
    mov v0,atol(rcx)
    mov v1,atol(string)
    mov rcx,string
    .repeat
       mov al,[rcx]
       inc rcx
    .until ( al > '9' || al < '0' )
    atol(rcx)
    mov ecx,v0
    mov edx,v1

    .if ( yc <= '9' && yc >= '0' )  ; YMD
        mov [rbx].wYear,cx
        mov [rbx].wMonth,dx
        mov [rbx].wDay,ax
    .elseif ( wc == '/' )           ; MDY
        mov [rbx].wYear,ax
        mov [rbx].wMonth,cx
        mov [rbx].wDay,dx
    .else
        mov [rbx].wYear,ax          ; DMY
        mov [rbx].wMonth,dx
        mov [rbx].wDay,cx
    .endif
    mov [rbx].wDayOfWeek,0
    mov rax,rbx
    ret

StringToSystemDateA endp

    end
