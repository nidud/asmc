; TOWUPPER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc
include winnls.inc

    .code

towupper proc wc:wchar_t

ifdef _WIN64
    movzx eax,cx
else
    movzx eax,wc
endif

    .if ( ax <= 'Z' )
        .return
    .endif
    .if ( ax >= 'a' && ax <= 'z' )

        sub ax,'a'-'A'
       .return
    .endif

if WINVER GE 0x0600
    LCMapStringEx( LOCALE_NAME_USER_DEFAULT, LCMAP_UPPERCASE, &wc, 1, &wc, 1, 0, 0, 0 )
    movzx eax,wc
endif
    ret

towupper endp

    end

