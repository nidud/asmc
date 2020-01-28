; TWINPUTTITLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include twindow.inc

    .code

    assume rcx:window_t

TWindow::PutTitle proc string:string_t

    movzx   r9d,[rcx].rc.col
    mov     rdx,[rcx].Color
    movzx   eax,byte ptr [rdx+BG_TITLE]
    or      al,[rdx+FG_TITLE]
    shl     eax,16
    mov     al,' '

    [rcx].PutChar(0, 0, r9d, eax)

    movzx   r9d,[rcx].rc.col

    [rcx].PutCenter(0, 0, r9d, string)
    ret

TWindow::PutTitle endp

    end
