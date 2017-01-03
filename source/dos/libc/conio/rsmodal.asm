; RSMODAL.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

rsmodal PROC _CType PUBLIC robj:DWORD
	invoke	rsopen,robj
	jz	@F
	push	dx
	push	ax
	invoke	rsevent,robj,dx::ax
	call	dlclose
	mov	ax,dx
	test	ax,ax
      @@:
	ret
rsmodal ENDP

	END
