; _WHEREY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_wherey proc

    _cursorxy()
    shr eax,16
    ret

_wherey endp

    end
