; WCPUTW.ASM--
; Copyright (C) 2015 Doszip Developers
include conio.inc

	.code

wcputw	PROC _CType PUBLIC USES ax cx di b:DWORD, l:size_t, w:size_t
	cld?
	push	es
	mov	ax,w
	mov	cx,l
	les	di,b
	.if ah
	    rep stosw
	.else
	    .repeat
		stosb
		inc di
	    .untilcxz
	.endif
	pop	es
	ret
wcputw	ENDP

	END
