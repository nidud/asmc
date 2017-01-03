; RCPUSH.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

rcpush	PROC _CType PUBLIC lines:size_t
	mov	ah,BYTE PTR lines
	mov	al,_scrcol
	mov	dx,ax
	sub	ax,ax
	invoke	rcopen,dx::ax,0,0,0,0
	ret
rcpush	ENDP

	END
