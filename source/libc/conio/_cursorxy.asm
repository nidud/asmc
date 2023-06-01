; _CURSORXY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; COORD _cursorxy(void);
;
include io.inc
include conio.inc

    .code

ifndef __TTY__

_cursorxy proc

  local ci:CONSOLE_SCREEN_BUFFER_INFO

    .if GetConsoleScreenBufferInfo(_confh, &ci)

        movzx eax,ci.dwCursorPosition.Y
        shl eax,16
        mov ax,ci.dwCursorPosition.X
    .endif
    ret

_cursorxy endp

else

_cursorxy proc uses rbx

    .new val:int_t = 0

    xor ebx,ebx
    _cout(CSI "6n") ; get cursor

    .whiled _getch() != -1
        ;
        ; ESC [ <r> ; <c> R
        ;
        .switch
        .case eax == VK_ESCAPE
        .case eax == '['
            .continue
        .case eax == ';'
            mov val,ebx
            xor ebx,ebx
           .endc
        .case eax >= '0' && eax <= '9'
            imul ebx,ebx,10
            sub eax,'0'
            add ebx,eax
           .endc
        .default
            .break
        .endsw
    .endw
    mov eax,val
    .if eax
        dec eax
    .endif
    .if ebx
        dec ebx
    .endif
    shl eax,16
    mov ax,bx
    ret

_cursorxy endp

endif

    end
