; TOWLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc
include winnls.inc

    .code

towlower proc wc:wchar_t

ifdef _WIN64
    movzx eax,cx
else
    movzx eax,wc
endif

    .if ( eax < 'A' )
        .return
    .endif
    .if ( eax <= 'Z' )
        add eax,'a'-'A'
       .return
    .endif
    .if ( eax >= 'a' && eax <= 'z' )
        .return
    .endif

if WINVER GE 0x0600
    LCMapStringEx( LOCALE_NAME_USER_DEFAULT, LCMAP_LOWERCASE, &wc, 1, &wc, 1, 0, 0, 0 )
    movzx eax,wc
endif
    ret

towlower endp

    end

