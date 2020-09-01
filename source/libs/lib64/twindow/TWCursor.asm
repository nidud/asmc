; TWCURSOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include twindow.inc

    .code

    assume rcx:window_t

TWindow::CursorGet proc

    mov rax,[rcx].Cursor

    .if ( rax == NULL )

        mov rax,[rcx].Class

        .new TCursor()

        mov rcx,this
        mov [rcx].Cursor,rax
    .endif
    ret

TWindow::CursorGet endp

TWindow::CursorSet proc

    mov rax,[rcx].Cursor

    .if ( rax != NULL )

        [rax].TCursor.Release()

        mov rcx,this
        xor eax,eax
        mov [rcx].Cursor,rax
    .endif
    ret

TWindow::CursorSet endp

TWindow::CursorOn proc

    .if [rcx].CursorGet()

        [rax].TCursor.Show()
        mov rcx,this
    .endif
    ret

TWindow::CursorOn endp

TWindow::CursorOff proc

    .if [rcx].CursorGet()

        [rax].TCursor.Hide()
        mov rcx,this
    .endif
    ret

TWindow::CursorOff endp

TWindow::CursorMove proc x:int_t, y:int_t

    .if [rcx].CursorGet()

        [rax].TCursor.Move(x, y)
        mov rcx,this
    .endif
    ret

TWindow::CursorMove endp

    end
