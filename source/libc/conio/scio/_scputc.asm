; _SCPUTC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputc proc x:int_t, y:int_t, l:int_t, char:char_t

  local NumberOfCharsWritten:int_t

    mov   eax,y
    movzx edx,char
    movzx ecx,al
    shl   ecx,16
    mov   cl,byte ptr x

    FillConsoleOutputCharacter( hStdOutput, edx, l, ecx, &NumberOfCharsWritten )
    ret

_scputc endp

    END
