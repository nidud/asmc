; _WCSLWR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc
include winnls.inc

    .code

if WINVER GE 0x0600

_wcslwr proc string:ptr wchar_t

    mov ecx,wcslen( string )
    LCMapStringEx( LOCALE_NAME_USER_DEFAULT, LCMAP_LOWERCASE, string, ecx, string, ecx, 0, 0, 0 )
    mov rax,string

else

    option dotname

_wcslwr proc string:ptr wchar_t

ifndef _WIN64
    mov     ecx,string
endif
    mov     rax,rcx
.0:
    mov     dx,[rcx]
    test    dx,dx
    jz      .2
    cmp     dx,'A'
    jb      .1
    cmp     dx,'Z'
    ja      .1
    or      dl,0x20
.1:
    mov     [rcx],dx
    add     rcx,2
.2:

endif
    ret

_wcslwr endp

    end
