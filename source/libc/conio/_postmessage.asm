; _MESSAGE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rbx:PMESSAGE

_postmessage proc uses rbx hwnd:THWND, uiMsg:uint_t, wParam:WPARAM, lParam:LPARAM

    mov rax,_console
    mov rbx,[rax].TCONSOLE.msgptr
    mov rbx,[rbx].next
    mov [rax].TCONSOLE.msgptr,rbx

    ldr rax,hwnd
    mov [rbx].hwnd,rax
    ldr eax,uiMsg
    mov [rbx].message,eax
    ldr rax,wParam
    mov [rbx].wParam,rax
    ldr rax,lParam
    mov [rbx].lParam,rax
    xor eax,eax
    ret

_postmessage endp

    end
