; _GETCSI2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_getcsi2 proc uses rsi rbx h:ptr int_t, l:ptr int_t

    mov rbx,h
    mov rsi,l
    xor eax,eax
    mov [rbx],eax
    mov [rsi],eax

    .repeat

        .break .if ( _getch() != 27 )
        .break .if ( _getch() != '[' )

        _getch()
        .while ( eax >= '0' && eax <= '9' )

            imul ecx,[rbx],10
            sub eax,'0'
            add eax,ecx
            mov [rbx],eax
            _getch()
        .endw
        .break .if ( eax != ';' )

        _getch()
        .while ( eax >= '0' && eax <= '9' )

            imul ecx,[rsi],10
            sub eax,'0'
            add eax,ecx
            mov [rsi],eax
            _getch()
        .endw
    .until 1
    ret

_getcsi2 endp

    end
