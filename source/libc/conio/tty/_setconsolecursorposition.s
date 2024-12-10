; _SETCONSOLECURSORPOSITION.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include consoleapi.inc

.code

_setconsolecursorposition proc WINAPI fh:HANDLE, pos:COORD

    ldr     edx,pos
    mov     ecx,edx
    shr     ecx,16
    movzx   edx,dx
    inc     ecx
    inc     edx

    _cout(CSI "%d;%dH", ecx, edx)
    ret

_setconsolecursorposition endp

    end
