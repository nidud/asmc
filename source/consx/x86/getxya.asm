; GETXYA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

getxya proc uses ecx edx x, y

  local Attribute
  local NumberOfAttributesRead

    movzx ecx,byte ptr y
    shl   ecx,16
    mov   cl,byte ptr x   ; COORD

    .if ReadConsoleOutputAttribute(
        hStdOutput,
        &Attribute,
        1,
        ecx,
        &NumberOfAttributesRead)

        mov eax,Attribute
        and eax,0xFF
    .endif
    ret

getxya endp

    END
