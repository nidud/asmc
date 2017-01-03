; SCPUSH.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

scpush	PROC _CType PUBLIC lcount:size_t
	mov	ax,lcount
	mov	ah,80
	sub	dx,dx
	invoke	rcopen,dx::ax,0,0,0,0
	ret
scpush	ENDP

scpop	PROC _CType PUBLIC wp:DWORD, lc:size_t
	mov	ax,lc
	mov	ah,80
	sub	dx,dx
	invoke	rcclose,dx::ax,_D_DOPEN or _D_ONSCR,wp
	ret
scpop	ENDP

	END
