; _DISPATCHMSG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rdx:PCONSOLE
    assume rcx:PMESSAGE

_dispatchmsg proc msg:PMESSAGE

    ldr rcx,msg
    mov rcx,[rcx].next
    xor eax,eax
    mov [rcx].hwnd,rax
    mov [rcx].message,eax
    mov [rcx].wParam,rax
    mov [rcx].lParam,rax
    mov rdx,_console

    .if ( rcx == [rdx].msgptr )

        mov rcx,[rcx].prev
        mov [rdx].msgptr,rcx
    .endif
    ret

_dispatchmsg endp

    end
