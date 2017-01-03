; RCBPRCRC.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

rcbprcrc PROC _CType PUBLIC USES bx r1:DWORD, r2:DWORD, wbuf:DWORD, cols:size_t
	mov	ax,cols
	add	ax,ax
	mov	bx,WORD PTR r1
	add	bx,WORD PTR r2
	mul	bh
	mov	dl,bl
	mov	dh,0
	add	ax,dx
	add	ax,dx
	add	ax,WORD PTR wbuf
	mov	dx,WORD PTR wbuf+2
	ret
rcbprcrc ENDP

	END
