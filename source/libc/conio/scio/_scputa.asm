; SCPUTA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputa proc x:BYTE, y:BYTE, l:BYTE, a:WORD

  local NumberOfAttrsWritten:dword

    movzx edx,l
    movzx ecx,y
    shl   ecx,16
    mov   cl,x

    FillConsoleOutputAttribute( _confh, a, edx, ecx, &NumberOfAttrsWritten )
    ret

_scputa endp

    END
