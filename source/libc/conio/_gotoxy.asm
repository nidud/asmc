; _GOTOXY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_gotoxy proc x:int_t, y:int_t

ifndef _WIN64
    mov ecx,x
    mov edx,y
endif
    and edx,0xFF
    shl edx,16
    mov dl,cl
    SetConsoleCursorPosition( _confh, edx )
    ret

_gotoxy endp

    end
