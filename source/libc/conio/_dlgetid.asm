; _DLGETID.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rcx:THWND

_dlgetid proc hwnd:THWND, index:int_t

    ldr rcx,hwnd
    ldr edx,index

    .for ( rcx = [rcx].object : rcx : rcx = [rcx].next, edx-- )

        .if ( dl == 0 )

            .break
        .endif
    .endf
    mov rax,rcx
    ret

_dlgetid endp

    end
