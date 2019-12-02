; GETXYC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include io.inc

    .code

getxyc proc uses ecx edx x, y

  local Character
  local NumberOfCharsRead

    movzx ecx,byte ptr y
    shl   ecx,16
    mov   cl,byte ptr x

    .if ReadConsoleOutputCharacter(
        hStdOutput,
        &Character,
        1,
        ecx,
        &NumberOfCharsRead)

        mov eax,Character
        and eax,0xFF
    .endif
    ret

getxyc endp

    END
