; WCSTOK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .data
     s0 wstring_t ?

    .code

wcstok proc uses rsi rdi s1:wstring_t, s2:wstring_t

ifdef _WIN64
    mov rsi,rcx
    mov rdi,rdx
else
    mov rsi,s1
    mov rdi,s2
endif

    .if ( rsi )
        mov s0,rsi
    .else
        mov rsi,s0
    .endif

    .while ( wchar_t ptr [rsi] )

        mov rcx,rdi
        mov ax,[rcx]

        .while ( ax )

            .break .if ( ax == [rsi] )

            add rcx,wchar_t
            mov ax,[rcx]
        .endw
        .break .if ( !ax )
        add rsi,wchar_t
    .endw

    .repeat

        xor eax,eax
        .break .if ( ax == [rsi] )

        mov rdx,rsi
        .while ( wchar_t ptr [rsi] )

            mov rcx,rdi
            mov ax,[rcx]

            .while ( ax )

                .if ( ax == [rsi] )

                    mov wchar_t ptr [rsi],0
                    add rsi,wchar_t
                   .break( 1 )
                .endif
                add rcx,wchar_t
                mov ax,[rcx]
            .endw
            add rsi,wchar_t
        .endw
        mov rax,rdx
    .until 1
    mov s0,rsi
    ret

wcstok endp

    end
