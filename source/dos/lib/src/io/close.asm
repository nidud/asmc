; CLOSE.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc
include errno.inc

	.code

close	PROC _CType PUBLIC handle:size_t
	push	ax
	mov	ax,handle
	.if ax < 3 || ax > _nfile
	    mov errno,EBADF
	    mov doserrno,0
	    sub ax,ax
	.else
	    push bx
	    mov bx,ax
	    mov _osfile[bx],0
	    mov ah,3Eh
	    int 21h
	    pop bx
	    .if CARRY?
		call osmaperr
	    .else
		sub ax,ax
	    .endif
	.endif
	pop dx
	ret
close	ENDP

	END
