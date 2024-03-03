; _TSTRTOK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .data
     s0 LPTSTR ?

    .code

_tcstok proc uses rbx s1:LPTSTR, s2:LPTSTR

   .new p:ptr

    ldr rbx,s1
    ldr rdx,s2

    .if ( rbx )
        mov s0,rbx
    .else
        mov rbx,s0
    .endif

    .while ( TCHAR ptr [rbx] )

        mov rcx,rdx
        mov _tal,[rcx]

        .while ( _tal )

            .break .if ( _tal == [rbx] )

            add rcx,TCHAR
            mov _tal,[rcx]
        .endw
        .break .if ( !_tal )
        add rbx,TCHAR
    .endw

    .repeat

        xor eax,eax
        .break .if ( _tal == [rbx] )

        mov p,rbx
        .while ( TCHAR ptr [rbx] )

            mov rcx,rdx
            mov _tal,[rcx]

            .while ( _tal )

                .if ( _tal == [rbx] )

                    mov TCHAR ptr [rbx],0
                    add rbx,TCHAR
                   .break( 1 )
                .endif

                add rcx,TCHAR
                mov _tal,[rcx]
            .endw
            add rbx,TCHAR
        .endw
        mov rax,p
    .until 1
    mov s0,rbx
    ret

_tcstok endp

    end
