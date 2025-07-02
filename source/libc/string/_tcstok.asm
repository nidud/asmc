; _TCSTOK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .data
     s0 tstring_t ?

    .code

_tcstok proc uses rbx s1:tstring_t, s2:tstring_t

   .new p:ptr

    ldr rbx,s1
    ldr rdx,s2

    .if ( rbx )
        mov s0,rbx
    .else
        mov rbx,s0
    .endif

    .while ( tchar_t ptr [rbx] )

        mov rcx,rdx
        mov _tal,[rcx]

        .while ( _tal )

            .break .if ( _tal == [rbx] )

            add rcx,tchar_t
            mov _tal,[rcx]
        .endw
        .break .if ( !_tal )
        add rbx,tchar_t
    .endw

    .repeat

        xor eax,eax
        .break .if ( _tal == [rbx] )

        mov p,rbx
        .while ( tchar_t ptr [rbx] )

            mov rcx,rdx
            mov _tal,[rcx]

            .while ( _tal )

                .if ( _tal == [rbx] )

                    mov tchar_t ptr [rbx],0
                    add rbx,tchar_t
                   .break( 1 )
                .endif

                add rcx,tchar_t
                mov _tal,[rcx]
            .endw
            add rbx,tchar_t
        .endw
        mov rax,p
    .until 1
    mov s0,rbx
    ret

_tcstok endp

    end
