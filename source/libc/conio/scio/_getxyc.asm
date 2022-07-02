; _GETXYC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_getxyc proc x:int_t, y:int_t

    movzx ecx,byte ptr y
    shl ecx,16
    mov cl,byte ptr x

    .ifd ReadConsoleOutputCharacter( hStdOutput, &x, 1, ecx, &y )

        mov eax,x
        and eax,0xFF
    .endif
    ret

_getxyc endp

    end
