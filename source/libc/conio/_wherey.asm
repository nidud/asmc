; _WHEREY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_wherey proc
    .new ci:CONSOLE_SCREEN_BUFFER_INFO
    .ifd GetConsoleScreenBufferInfo(_confh, &ci)
        movzx eax,ci.dwCursorPosition.Y
    .endif
    ret
    endp

    end
