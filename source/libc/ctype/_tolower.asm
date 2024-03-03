; _TOLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc
ifdef _UNICODE
include winnls.inc
endif
include tchar.inc

    .code

_totlower proc c:int_t

    ldr     ecx,c
    movzx   ecx,_tcl

ifdef _UNICODE
    .if ( ecx < 256 )
endif

    mov     rax,_pclmap
    movzx   eax,byte ptr [rax+rcx]

ifdef _UNICODE
    .else
ifndef __UNIX__
if WINVER GE 0x0600
        LCMapStringEx( LOCALE_NAME_USER_DEFAULT, LCMAP_LOWERCASE, &c, 1, &c, 1, 0, 0, 0 )
        mov eax,c
    .endif
endif
endif
endif
    ret

_totlower endp

    end
