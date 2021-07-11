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

    mov r10,wcslen(rcx)
    LCMapStringEx(LOCALE_NAME_USER_DEFAULT,
	LCMAP_LOWERCASE, string, r10d, string, r10d, 0, 0, 0)

    mov rax,string

else

    option win64:rsp nosave noauto

_wcslwr proc string:ptr wchar_t

    mov r10,rcx

    .while 1

	mov ax,[rcx]
	.break .if !ax
	sub ax,'A'
	cmp ax,'Z' - 'A' + 1
	sbb ax,ax
	and ax,'a' - 'A'
	xor [rcx],ax
	add rcx,2

    .endw

    mov rax,r10

endif
    ret

_wcslwr endp

    end
