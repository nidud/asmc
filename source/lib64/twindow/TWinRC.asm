; TWINRC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include twindow.inc

    .code

    assume rcx:window_t

TWindow::Read proc rect:trect_t, pc:PCHAR_INFO

    mov rax,[rcx].Class
    mov rcx,rdx

    TRect_Read(rcx, [rax].TClass.StdOut, r8)
    mov rcx,this
    ret

TWindow::Read endp

TWindow::Write proc rect:trect_t, pc:PCHAR_INFO

    mov rax,[rcx].Class
    mov rcx,rdx

    TRect_Write(rcx, [rax].TClass.StdOut, r8)
    mov rcx,this
    ret

TWindow::Write endp

TWindow::Exchange proc rc:trect_t, pc:PCHAR_INFO

    mov rax,[rcx].Class
    mov rcx,rdx

    TRect_Exchange(rcx, [rax].TClass.StdOut, r8)
    mov rcx,this
    ret

TWindow::Exchange endp

    end
