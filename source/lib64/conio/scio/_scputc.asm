; _SCPUTC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    option win64:nosave

_scputc proc frame x:int_t, y:int_t, l:int_t, char:char_t

  local NumberOfCharsWritten:int_t

    mov   eax,edx
    movzx edx,r9b
    movzx r9d,al
    shl   r9d,16
    mov   r9b,cl

    FillConsoleOutputCharacter(_confh, edx, r8d, r9d, &NumberOfCharsWritten)
    ret

_scputc endp

    END
