; _WCSLWR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc
include winnls.inc

    .code

    option dotname

_wcslwr proc uses rbx string:ptr wchar_t

    ldr rbx,string
if ( WINVER GE 0x0600 ) and not defined(__UNIX__)

    mov ecx,wcslen( rbx )
    LCMapStringEx( LOCALE_NAME_USER_DEFAULT, LCMAP_LOWERCASE, rbx, ecx, rbx, ecx, 0, 0, 0 )
    mov rax,rbx

else
    mov     rax,rbx
.0:
    mov     dx,[rbx]
    test    dx,dx
    jz      .2
    cmp     dx,'A'
    jb      .1
    cmp     dx,'Z'
    ja      .1
    or      dl,0x20
.1:
    mov     [rbx],dx
    add     rbx,2
.2:
endif
    ret

_wcslwr endp

    end
