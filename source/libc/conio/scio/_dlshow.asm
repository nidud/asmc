; _DLSHOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rbx:THWND

_dlshow proc uses rbx hwnd:THWND

    mov rbx,hwnd
    mov edx,.flags

    .if ( !( edx & W_ISOPEN ) )

        .return(0)
    .endif

    .if ( !( edx & W_VISIBLE ) )

        _rcxchg(.rc, .window)
        .if ( [rbx].flags & W_SHADE )
            _rcshade(.rc, .window, 1)
        .endif
        or .flags,W_VISIBLE
    .endif
    .return(1)

_dlshow endp

    end
