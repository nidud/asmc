; _WCSLWR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc
include winnls.inc

    .code

    option dotname

_wcslwr proc string:ptr wchar_t

if ( WINVER GE 0x0600 ) and not defined(__UNIX__)

    mov ecx,wcslen( string )
    LCMapStringEx( LOCALE_NAME_USER_DEFAULT, LCMAP_LOWERCASE, string, ecx, string, ecx, 0, 0, 0 )
    mov rax,string

else
    ldr     rcx,string
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
