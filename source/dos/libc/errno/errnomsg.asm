; ERRNOMSG.ASM--
; Copyright (C) 2015 Doszip Developers

include errno.inc

	.code

errnomsg PROC _CType PUBLIC etitle:DWORD, format:DWORD, file:DWORD
	mov	cx,errno
	shl	cx,2
	mov	ax,offset sys_errlist
	add	ax,cx
	xchg	bx,ax
	mov	bx,[bx]
	xchg	bx,ax
	mov	dx,ds
	invoke	ermsg,etitle,format,file,dx::ax
	dec	ax
	ret
errnomsg ENDP

	END
