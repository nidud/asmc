; _PUTWCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include wchar.inc

    .code

_putwch_nolock proc wc:UINT

  local cchWritten:DWORD

    .if ( _confh == -2 )

        __initconout()
    .endif

    .if ( _confh == -1 )

        mov eax,WEOF
    .else
        ;
        ; write character to console file handle
        ;
        .if WriteConsoleW( _confh, &wc, 1, &cchWritten, NULL )

            mov eax,wc
        .else
            mov eax,WEOF
        .endif
    .endif
    ret

_putwch_nolock endp

_putwch proc wc:UINT

    _putwch_nolock( wc )
    ret

_putwch endp

    end
