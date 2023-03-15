; SCPUTA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputa proc x:int_t, y:int_t, l:int_t, a:uchar_t

  local NumberOfAttrsWritten:dword

    mov   eax,y
    movzx edx,a
    movzx ecx,al
    shl   ecx,16
    mov   cl,byte ptr x

    FillConsoleOutputAttribute( _confh, dx, l, ecx, &NumberOfAttrsWritten )
    ret

_scputa endp

    END
