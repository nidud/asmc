; _POSTQUITMESSAGE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_postquitmsg proc hwnd:THWND, retval:UINT

    ldr rax,hwnd
    ldr edx,retval

    test [rax].TDIALOG.flags,W_CHILD
    cmovnz rax,[rax].TDIALOG.prev
    _postmessage(rax, WM_QUIT, edx, 0)
    ret

_postquitmsg endp

    end
