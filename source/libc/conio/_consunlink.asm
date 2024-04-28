; _CONSUNLINK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_consunlink proc hwnd:THWND

    ldr rax,hwnd
    mov rcx,[rax].TDIALOG.prev
    mov rdx,[rax].TDIALOG.next
    .if ( rcx )
        mov [rcx].TDIALOG.next,rdx
    .endif
    .if ( rdx )
        mov [rdx].TDIALOG.prev,rcx
    .endif
    ret

_consunlink endp

    end
