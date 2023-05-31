; _PUTWCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include conio.inc
include stdlib.inc

    .code

_putwch proc wc:wchar_t

    .if ( _confd == -1 )

        mov rax,WEOF
    .else
        ;
        ; write character to console file handle
        ;
ifdef __UNIX__
        .new c:int_t = _wtoutf(wc)
        .if _write( _confd, &c, ecx )
else
        .new cchWritten:uint_t
        .if WriteConsoleW( _confh, &wc, 1, &cchWritten, NULL )
endif
            movzx eax,wc
        .else
            mov rax,WEOF
        .endif
    .endif
    ret

_putwch endp

    end
