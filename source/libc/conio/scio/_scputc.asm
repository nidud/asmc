; _SCPUTC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputc proc x:int_t, y:int_t, l:int_t, char:char_t

  local NumberOfCharsWritten:int_t

    movzx ecx,byte ptr y
    shl   ecx,16
    mov   cl,byte ptr x

    .if FillConsoleOutputCharacter( _confh, char, l, ecx, &NumberOfCharsWritten )

        mov eax,NumberOfCharsWritten
    .endif
    ret

_scputc endp

    END
