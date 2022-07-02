; TOUPPER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc
include winnls.inc

    .code

toupper proc c:int_t

ifdef _WIN64
    mov eax,ecx
else
    mov eax,c
endif

    .return .if ( al <= 'Z' )

    .if ( al >= 'a' && al <= 'z' )

        sub al,'a'-'A'
       .return
    .endif

if WINVER GE 0x0600
    LCMapStringEx( LOCALE_NAME_USER_DEFAULT, LCMAP_UPPERCASE, &c, 1, &c, 1, 0, 0, 0 )
    mov eax,c
endif
    ret

toupper endp

    end

