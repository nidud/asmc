; _TSTRTOK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tmacro.inc

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
        mov __a,[rcx]

        .while ( __a )

            .break .if ( __a == [rbx] )

            add rcx,TCHAR
            mov __a,[rcx]
        .endw
        .break .if ( !__a )
        add rbx,TCHAR
    .endw

    .repeat

        xor eax,eax
        .break .if ( __a == [rbx] )

        mov p,rbx
        .while ( TCHAR ptr [rbx] )

            mov rcx,rdx
            mov __a,[rcx]

            .while ( __a )

                .if ( __a == [rbx] )

                    mov TCHAR ptr [rbx],0
                    add rbx,TCHAR
                   .break( 1 )
                .endif

                add rcx,TCHAR
                mov __a,[rcx]
            .endw
            add rbx,TCHAR
        .endw
        mov rax,p
    .until 1
    mov s0,rbx
    ret

_tcstok endp

    end
