; _WHEREX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_wherex proc

    .new ci:CONSOLE_SCREEN_BUFFER_INFO

    .ifd _getconsolescreenbufferinfo(_confh, &ci)

        movzx eax,ci.dwCursorPosition.X
    .endif
    ret

_wherex endp

    end
