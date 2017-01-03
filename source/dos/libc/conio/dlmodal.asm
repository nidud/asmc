; DLMODAL.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

dlmodal PROC _CType PUBLIC dobj:DWORD
	invoke	dlevent,dobj
	invoke	dlclose,dobj
	mov	ax,dx
	test	ax,ax
	ret
dlmodal ENDP

	END
