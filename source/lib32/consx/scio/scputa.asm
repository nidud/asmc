; SCPUTA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

scputa proc uses eax edx ecx x, y, l, a

  local NumberOfAttrsWritten

    movzx ecx,byte ptr a
    movzx eax,byte ptr x
    movzx edx,byte ptr y
    shl   edx,16
    mov   dx,ax

    FillConsoleOutputAttribute(
        hStdOutput,
        cx,
        l,
        edx,
        &NumberOfAttrsWritten)
    ret

scputa endp

    END
