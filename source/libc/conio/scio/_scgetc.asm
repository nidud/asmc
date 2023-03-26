; _SCGETC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scgetc proc x:BYTE, y:BYTE

   .new c:wchar_t
   .new count:int_t

    movzx ecx,y
    shl   ecx,16
    mov   cl,x

    .ifd ReadConsoleOutputCharacterW( _coninpfh, &c, 1, ecx, &count )

        movzx eax,c
    .endif
    ret

_scgetc endp

    end
