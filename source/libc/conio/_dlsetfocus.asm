; _DLSETFOCUS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc

    .code

    assume rbx:THWND
    assume rcx:THWND

_dlsetfocus proc uses rsi rbx hwnd:THWND, index:BYTE

    ldr rcx,hwnd
    ldr dl,index

    test [rcx].flags,W_CHILD
    cmovnz rcx,[rcx].prev

    .for ( eax = 0, ebx = 0, dh = [rcx].index, rcx = [rcx].object : rcx : rcx = [rcx].next )

        .if ( dl == [rcx].oindex )

             movzx esi,[rcx].flags
            .break .if ( ( esi & O_STATE or O_NOFOCUS ) || !( esi & W_WNDPROC ) )
             mov rbx,rcx
        .endif

        .if ( dh == [rcx].oindex && [rcx].flags & W_WNDPROC )
            mov rax,rcx
        .endif
    .endf
    .if ( rbx )

        .if ( rax )

            mov rcx,rax
            [rcx].winproc(rcx, WM_KILLFOCUS, 0, 0)
        .endif
        mov rcx,[rbx].prev
        mov [rcx].index,[rbx].oindex
        [rbx].winproc(rbx, WM_SETFOCUS, 0, 0)
    .endif
    .return( 0 )

_dlsetfocus endp

    end
