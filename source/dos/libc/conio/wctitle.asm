; WCTITLE.ASM--
; Copyright (C) 2015 Doszip Developers
include conio.inc

	.code

wctitle PROC _CType PUBLIC p:DWORD, l:size_t, string:DWORD
	mov	al,' '
	mov	ah,at_background[B_Title]
	or	ah,at_foreground[F_Title]
	invoke	wcputw,p,l,ax
	invoke	wcenter,p,l,string
	ret
wctitle ENDP

	END
