; TOWUPPER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc
include winnls.inc

externdef _pcumap:string_t

    .code

towupper proc wc:wchar_t

    ldr cx,wc

    movzx ecx,cx
    .if ( ecx < 256 )

        mov rax,_pcumap
        movzx eax,byte ptr [rax+rcx]
       .return
    .endif
if WINVER GE 0x0600
    LCMapStringEx( LOCALE_NAME_USER_DEFAULT, LCMAP_UPPERCASE, &wc, 1, &wc, 1, 0, 0, 0 )
endif
    movzx eax,wc
    ret
towupper endp

    end

