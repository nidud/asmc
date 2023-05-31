; _GOTOXY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_gotoxy proc x:uint_t, y:uint_t

    ldr ecx,x
    ldr eax,y

ifdef __TTY__
    inc ecx ; zero based..
    inc eax
    _cout("\e[%d;%dH", eax, ecx)
else
    shl eax,16
    mov ax,cx
    SetConsoleCursorPosition(_confh, eax)
endif
    ret

_gotoxy endp

    end
