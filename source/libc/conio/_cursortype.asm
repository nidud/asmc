; _CURSORTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_cursortype proc type:int_t

    .new cu:CONSOLE_CURSOR_INFO
    .ifd _getconsolecursorinfo(_confh, &cu)

        mov cu.dwSize,type
        _setconsolecursorinfo(_confh, &cu)
    .endif
    ret

_cursortype endp

    end
