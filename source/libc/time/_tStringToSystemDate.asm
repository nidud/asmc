; _TSTRINGTOSYSTEMDATE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include stdlib.inc
include tchar.inc

    .code

    assume rbx:ptr SYSTEMTIME

StringToSystemDate proc uses rbx string:tstring_t, lpSystemTime:ptr SYSTEMTIME

   .new v0:int_t,v1,wc,yc
    ldr rbx,lpSystemTime
    ldr rcx,string
    movzx eax,tchar_t ptr [rdx+tchar_t*2]
    mov yc,eax
    mov rdx,rcx
    .repeat
       movzx eax,tchar_t ptr [rdx]
       add rdx,tchar_t
    .until ( eax > '9' || eax < '0' )
    mov wc,eax
    mov string,rdx
    mov v0,_tstol(rcx)
    mov v1,_tstol(string)
    mov rcx,string
    .repeat
       movzx eax,tchar_t ptr [rcx]
       add rcx,tchar_t
    .until ( eax > '9' || eax < '0' )
    _tstol(rcx)
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
    endp

    end
