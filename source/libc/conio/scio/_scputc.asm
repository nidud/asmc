; _SCPUTC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputc proc x:BYTE, y:BYTE, l:BYTE, char:wchar_t

  local NumberOfCharsWritten:int_t

    movzx edx,l
    movzx ecx,y
    shl   ecx,16
    mov   cl,x

    .if FillConsoleOutputCharacterW( _confh, char, edx, ecx, &NumberOfCharsWritten )

        mov eax,NumberOfCharsWritten
    .endif
    ret

_scputc endp

    end
