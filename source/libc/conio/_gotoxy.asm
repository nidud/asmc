; _GOTOXY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_gotoxy proc x:uint_t, y:uint_t

    ldr ecx,x
    ldr edx,y

    shl edx,16
    mov dx,cx
    _setconsolecursorposition(_confh, edx)
    ret

_gotoxy endp

    end
