; WCSTOK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .data
     s0 wstring_t ?

    .code

wcstok proc uses rbx s1:wstring_t, s2:wstring_t

    ldr rbx,s1
    ldr rdx,s2

    .if ( rbx )
        mov s0,rbx
    .else
        mov rbx,s0
    .endif

    .while ( wchar_t ptr [rbx] )

        mov rcx,rdx
        mov ax,[rcx]

        .while ( ax )

            .break .if ( ax == [rbx] )

            add rcx,wchar_t
            mov ax,[rcx]
        .endw
        .break .if ( !ax )
        add rbx,wchar_t
    .endw

    .repeat

        xor eax,eax
        .break .if ( ax == [rbx] )

        push rbx
        .while ( wchar_t ptr [rbx] )

            mov rcx,rdx
            mov ax,[rcx]

            .while ( ax )

                .if ( ax == [rbx] )

                    mov wchar_t ptr [rbx],0
                    add rbx,wchar_t
                   .break( 1 )
                .endif
                add rcx,wchar_t
                mov ax,[rcx]
            .endw
            add rbx,wchar_t
        .endw
        pop rax
    .until 1
    mov s0,rbx
    ret

wcstok endp

    end
