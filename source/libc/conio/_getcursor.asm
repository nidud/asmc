; _GETCURSOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc

.code

_getcursor proc uses rbx p:PCURSOR

   .new cu:CONSOLE_CURSOR_INFO
ifdef __TTY__
   .new a:CINPUT
else
   .new ci:CONSOLE_SCREEN_BUFFER_INFO
endif

    ldr rbx,p

ifdef __TTY__
    _write(_confd, CSI "6n", 4) ; get cursor
    .ifd ( _readansi( &a ) && a.count == 2 )

        mov eax,a.n
        mov ecx,a.n[4]
        .if ( eax )
            dec eax
        .endif
        .if ( ecx )
            dec ecx
        .endif
        mov [rbx].CURSOR.y,al
        mov [rbx].CURSOR.x,cl
else
    .ifd _getconsolescreenbufferinfo(_confh, &ci)

        mov [rbx].CURSOR.x,ci.dwCursorPosition.X
        mov [rbx].CURSOR.y,ci.dwCursorPosition.Y
endif
    .endif

    .ifd _getconsolecursorinfo(_confh, &cu)

        mov [rbx].CURSOR.type,cu.dwSize
        mov [rbx].CURSOR.visible,cu.bVisible
    .endif
    ret

_getcursor endp

    end
