; _GETXYA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc
include errno.inc

    .code

_getxya proc x:int_t, y:int_t

    movzx ecx,byte ptr y
    shl ecx,16
    mov cl,byte ptr x

    .ifd ReadConsoleOutputAttribute( _confh, &x, 1, ecx, &y )

        mov eax,x
        and eax,0xFF
    .endif
    ret

_getxya endp

    end
