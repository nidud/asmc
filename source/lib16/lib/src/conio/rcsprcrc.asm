; RCSPRCRC.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

.code

rcsprcrc PROC _CType PUBLIC USES bx r1:DWORD, r2:DWORD
	mov	bx,WORD PTR r1
	add	bx,WORD PTR r2
	mov	al,_scrcol
	mul	bh
	add	ax,ax
	xor	dx,dx
	mov	dl,bl
	add	ax,dx
	add	ax,dx
	mov	dx,_scrseg
	ret
rcsprcrc ENDP

	END
