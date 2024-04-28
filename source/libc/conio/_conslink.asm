; _CONSLINK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_conslink proc hwnd:THWND

    ldr rax,hwnd
    mov rcx,_console
    .if ( rcx )
        .while ( [rcx].TDIALOG.next )
            mov rcx,[rcx].TDIALOG.next
        .endw
        mov [rax].TDIALOG.prev,rcx
        mov [rcx].TDIALOG.next,rax
    .endif
    ret

_conslink endp

    end
