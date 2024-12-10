; _CURSOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

    assume rbx:PCURSOR

_setcursor proc uses rbx p:PCURSOR

   .new cu:CONSOLE_CURSOR_INFO

    ldr rbx,p

    _gotoxy([rbx].x, [rbx].y)
    movzx eax,[rbx].type
    movzx ecx,[rbx].visible
    mov cu.dwSize,eax
    mov cu.bVisible,ecx
    _setconsolecursorinfo(_confh, &cu)
    ret

_setcursor endp

    end
