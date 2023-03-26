; _SCGETA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc
include errno.inc

    .code

_scgeta proc x:BYTE, y:BYTE

   .new at:WORD
   .new count:DWORD

    movzx ecx,y
    shl   ecx,16
    mov   cl,x

    .ifd ReadConsoleOutputAttribute( _confh, &at, 1, ecx, &count )

        movzx eax,at
    .endif
    ret

_scgeta endp

    end
