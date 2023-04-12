; _CURSOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_cursorxy proc uses rbx

    _cout(CSI "6n") ; get cursor

    xor ebx,ebx ; COORD
    .repeat
        ;
        ; ESC [ <r> ; <c> R
        ;
        .break .if ( _getch() != VK_ESCAPE )
        .break .if ( _kbflush() == 0 )

         shr rcx,8
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

    end
