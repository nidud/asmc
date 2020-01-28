; TWINCHILD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include twindow.inc

    .code

    assume rcx:window_t
    assume rbx:window_t

TWindow::Child proc uses rdi rbx rcx rc:TRect, id:uint_t, type:uint_t

    mov edi,r9d
    mov ebx,r8d

    .return .if ( [rcx].Open(edx, W_CHILD or W_WNDPROC) == NULL )

    mov [rax].TWindow.Index,ebx
    mov [rax].TWindow.Type,edi
    mov rbx,rax
    lea rax,TWindow_DefWindowProc
    mov [rbx].WndProc,rax
    .for ( rcx = [rbx].Prev : [rcx].Child : rcx = [rcx].Child )
    .endf
    mov [rcx].Child,rbx
    mov rax,rbx
    ret

TWindow::Child endp


    end
