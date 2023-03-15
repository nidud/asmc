; _SCMOVED.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc
include crtl.inc

    .code

_scmoved proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

   .new x:int_t
   .new l:int_t
   .new b:PCHAR_INFO
   .new ci:CONSOLE_SCREEN_BUFFER_INFO

    mov edi,25
    .if GetConsoleScreenBufferInfo(_confh, &ci)

        movzx edi,ci.dwSize.Y
    .endif

    movzx eax,rc.y
    movzx edx,rc.row
    mov esi,eax
    add eax,edx

    .if ( edi > eax )

        mov edi,eax
        mov al,rc.x
        mov x,eax
        mov al,rc.col
        mov l,eax
        mul rc.row
        shl eax,2

        .if malloc( eax )

            mov rbx,rax
            _scread(rc, rax)
            mov b,_screadl( x, edi, l )
            inc rc.y
            _scwrite( rc, rbx )
            free( rbx )

            mov ebx,l
            shl ebx,2
            memxchg( b, p, rbx )
            _scwritel( x, esi, l, rax )

            movzx esi,rc.row
            dec esi
            mov rdi,p
            .while esi

                memxchg( rdi, &[rdi+rbx], rbx )
                add rdi,rbx
                dec esi
            .endw
        .endif
    .endif
    .return( rc )

_scmoved endp

    end
