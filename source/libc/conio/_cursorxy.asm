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

   .new keys:CINPUT = {0}

    _cwrite(CSI "6n") ; get cursor

    xor ebx,ebx ; COORD
    .repeat
        ;
        ; ESC [ <r> ; <c> R
        ;

        mov keys.count,_read(_conin, &keys.b, 8)
        mov rcx,keys.q

        .break .if ( cl != VK_ESCAPE )
        .break .if ( eax == 0 )

         shr rcx,16
        .while ( cl >= '0' && cl <= '9' )

            imul    ebx,ebx,10
            movzx   eax,cl
            sub     eax,'0'
            add     ebx,eax
            shr     rcx,8
        .endw
         .if ( ebx )
           dec ebx
         .endif
         shl ebx,16
        .break .if ( cl != ';' )

         shr rcx,8
         xor eax,eax
        .while ( cl >= '0' && cl <= '9' )

            imul    eax,eax,10
            movzx   edx,cl
            sub     edx,'0'
            add     eax,edx
            shr     rcx,8
        .endw
         .if ( eax )
           dec eax
         .endif
        mov bx,ax
    .until 1
    .return( ebx )

_cursorxy endp

endif

    end
