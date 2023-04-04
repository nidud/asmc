; _DLCLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

    assume rbx:THWND

_dlclose proc uses rbx hwnd:THWND

    mov rbx,hwnd

    _dlhide(rbx)
    .if ( [rbx].flags & O_CURSOR )
        _setcursor(&[rbx].cursor)
    .endif
    _consunlink(rbx)
    free(rbx)
    ret

_dlclose endp

    end
