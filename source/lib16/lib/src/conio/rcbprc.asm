; RCBPRC.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

rcbprc	PROC _CType PUBLIC USES bx rc:DWORD, wbuf:DWORD, cols:size_t
	mov	ax,cols
	add	ax,ax
	mov	bx,WORD PTR rc
	mul	bh
	mov	dl,bl
	mov	dh,0
	add	ax,dx
	add	ax,dx
	add	ax,WORD PTR wbuf
	mov	dx,WORD PTR wbuf+2
	ret
rcbprc	ENDP

	END
