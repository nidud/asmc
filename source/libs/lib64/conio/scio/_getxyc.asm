; _GETXYC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_getxyc proc x:int_t, y:int_t

    movzx r9d,dl
    shl   r9d,16
    mov   r9b,cl

    .ifd ReadConsoleOutputCharacter(hStdOutput, &x, 1, r9d, &y)

        mov eax,x
        and eax,0xFF
    .endif
    ret

_getxyc endp

    END
