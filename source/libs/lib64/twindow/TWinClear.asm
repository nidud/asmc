; TWINCLEAR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include twindow.inc

    .code

    assume rcx:window_t

TWindow::Clear proc at:CHAR_INFO

    movzx   eax,[rcx].rc.row
    mul     [rcx].rc.col

    [rcx].PutChar(0, 0, eax, edx)
    ret

TWindow::Clear endp

    end
