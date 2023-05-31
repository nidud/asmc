; STRINGTOSYSTEMDATEW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include stdlib.inc

    .code

    assume rbx:ptr SYSTEMTIME

StringToSystemDateW proc uses rbx string:ptr wchar_t, lpSystemTime:ptr SYSTEMTIME

   .new v0:int_t
   .new v1:int_t
   .new wc:wchar_t
   .new yc:wchar_t

    ldr rbx,lpSystemTime
    ldr rcx,string
    mov ax,[rdx+4]
    mov yc,ax
    mov rdx,rcx
    .repeat
       mov ax,[rdx]
       add rdx,2
    .until ( ax > '9' || ax < '0' )
    mov wc,ax
    mov string,rdx
    mov v0,_wtol(rcx)
    mov v1,_wtol(string)
    mov rcx,string
    .repeat
       mov ax,[rcx]
       add rcx,2
    .until ( ax > '9' || ax < '0' )
    _wtol(rcx)
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

StringToSystemDateW endp

    end
