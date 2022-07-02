; _SCMOVEU.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc
include crtl.inc

    .code

_scmoveu proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

   .new x:int_t
   .new l:int_t
   .new z:int_t
   .new b:PCHAR_INFO

    movzx eax,rc.y
    .if ( eax > 1 )

        movzx esi,rc.row
        dec eax
        add esi,eax
        mov edi,eax
        mov al,rc.x
        mov x,eax
        mov al,rc.col
        mov l,eax
        mul rc.row
        shl eax,2

        .if malloc( eax )

            mov rbx,rax
            _scread( rc, rax )
            mov b,_screadl( x, edi, l )
            dec rc.y
            _scwrite( rc, rbx )
            free( rbx )

            mov ebx,l
            shl ebx,2
            movzx eax,rc.row
            dec eax
            mov z,eax
            mul ebx
            mov rdi,p
            add rdi,rax

            memxchg( b, rdi, rbx )
            _scwritel( x, esi, l, b )

            mov b,rdi
            sub b,rbx
            mov esi,z

            .while esi

                memxchg( b, rdi, rbx )
                sub rdi,rbx
                sub b,rbx
                dec esi
            .endw
        .endif
    .endif
    .return( rc )

_scmoveu endp

    end
