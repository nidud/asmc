; TWINWINDOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include twindow.inc

    option win64:rsp noauto

    .code

    assume rcx:window_t
    assume rbx:window_t

TWindow::Window proc uses rbx rdx

    mov     rbx,rcx
    test    [rcx].Flags,W_CHILD
    cmovnz  rbx,[rcx].Prev
    movzx   eax,[rcx].rc.y
    movzx   r8d,[rbx].rc.col
    mul     r8d
    movzx   edx,[rcx].rc.x
    add     eax,edx
    shl     eax,2
    add     rax,[rbx].Window
    ret

TWindow::Window endp

    end
