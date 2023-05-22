; _DLSETFOCUS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc

    .code

    assume rbx:THWND

_dlsetfocus proc uses rbx hwnd:THWND, index:BYTE

    ldr rbx,hwnd
    .if _dlgetfocus(rbx)

        _sendmessage(rax, WM_KILLFOCUS, 0, 0)
    .endif

    test    [rbx].flags,W_CHILD
    cmovnz  rbx,[rbx].prev
    mov     [rbx].index,index
    movzx   eax,al

    .if _dlgetid(rbx, eax)

        _sendmessage(rax, WM_SETFOCUS, 0, 0)
    .endif
    ret

_dlsetfocus endp

    end
