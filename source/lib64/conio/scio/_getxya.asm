; _GETXYA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc

    .code

    option win64:nosave

_getxya proc frame x:int_t, y:int_t

    movzx r9d,dl
    shl   r9d,16
    mov   r9b,cl

    .ifd ReadConsoleOutputAttribute(_confh, &x, 1, r9d, &y)

        mov eax,x
        and eax,0xFF
    .endif
    ret

_getxya endp

    END
