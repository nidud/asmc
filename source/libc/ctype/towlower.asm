; TOWLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc
include winnls.inc

externdef _pclmap:string_t

    .code

towlower proc wc:wchar_t

    ldr cx,wc
    movzx ecx,cx

    .if ( ecx < 256 )

        mov rax,_pclmap
        movzx eax,byte ptr [rax+rcx]
       .return
    .endif
ifndef __UNIX__
if WINVER GE 0x0600
    LCMapStringEx( LOCALE_NAME_USER_DEFAULT, LCMAP_LOWERCASE, &wc, 1, &wc, 1, 0, 0, 0 )
endif
endif
    movzx eax,wc
    ret

towlower endp

    end

