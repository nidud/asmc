; TWINPUTCHAR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include twindow.inc

    option win64:rsp noauto

    .code

    assume rcx:window_t

TWindow::PutChar proc uses rdi x:int_t, y:int_t, count:int_t, w:CHAR_INFO

    movzx   edi,[rcx].rc.col
    imul    edi,r8d
    add     edi,edx
    shl     edi,2
    add     rdi,[rcx].Window
    mov     eax,w
    xchg    rcx,r9

    .if ( ( eax & 0x00FF0000 ) && ( eax & 0x0000FFFF ) )

        rep stosd

    .else

        .if ( eax & 0x00FF0000 )

            add rdi,2
            shr eax,16
        .endif

        .repeat
            mov [rdi],ax
            add rdi,4
        .untilcxz
    .endif

    mov rcx,r9
    xor eax,eax
    ret

TWindow::PutChar endp

    end
