; _DLGETFOCUS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rcx:THWND

_dlgetfocus proc hwnd:THWND

    ldr     rcx,hwnd
    test    [rcx].flags,W_CHILD
    cmovnz  rcx,[rcx].prev
    mov     al,[rcx].index
    movzx   edx,word ptr [rcx].rc

    .for ( rcx = [rcx].object : rcx : rcx = [rcx].next )

        .if ( al == [rcx].oindex )

            add edx,[rcx].rc
            .return( rcx )
        .endif
    .endf
    .return( 0 )

_dlgetfocus endp

    end
