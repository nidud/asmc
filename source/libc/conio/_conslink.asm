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
        .while ( [rcx].TCLASS.next )
            mov rcx,[rcx].TCLASS.next
        .endw
        mov [rax].TCLASS.prev,rcx
        mov [rcx].TCLASS.next,rax
    .endif
    ret

_conslink endp

    end
