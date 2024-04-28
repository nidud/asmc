; _DLSHOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rbx:THWND

_dlshow proc uses rbx hwnd:THWND

    ldr rbx,hwnd

    movzx edx,[rbx].flags
    .if ( !( edx & W_ISOPEN ) )

        .return(0)
    .endif

    .if ( !( edx & W_VISIBLE ) )

        _rcxchg([rbx].rc, [rbx].window)
        .if ( [rbx].flags & W_SHADE )
            _rcshade([rbx].rc, [rbx].window, 1)
        .endif
        or [rbx].flags,W_VISIBLE
    .endif
    .return(1)

_dlshow endp

    end
