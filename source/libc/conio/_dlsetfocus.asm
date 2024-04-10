; _DLSETFOCUS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc

    .code

    assume rbx:THWND
    assume rcx:THWND

_dlsetfocus proc uses rbx hwnd:THWND, index:BYTE

    ldr rcx,hwnd
    ldr dl,index

    test [rcx].flags,W_CHILD
    cmovnz rcx,[rcx].prev

    .for ( eax = 0, ebx = 0, dh = [rcx].index, rcx = [rcx].object : rcx : rcx = [rcx].next )

        .if ( dl == [rcx].index )

            .if ( ( [rcx].flags & O_STATE ) || !( [rcx].flags & W_WNDPROC ) || [rcx].type >= T_MOUSERECT )
                .break
            .endif
            mov rbx,rcx
        .endif
        .if ( dh == [rcx].index && [rcx].flags & W_WNDPROC )
            mov rax,rcx
        .endif
    .endf
    .if ( rbx )

        .if ( rax )

            mov rcx,rax
            [rcx].winproc(rcx, WM_KILLFOCUS, 0, 0)
        .endif
        [rbx].winproc(rbx, WM_SETFOCUS, 0, 0)
    .endif
    .return( 0 )

_dlsetfocus endp

    end
