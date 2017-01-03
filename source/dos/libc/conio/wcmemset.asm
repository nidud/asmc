; WCMEMSET.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

wcmemset PROC _CType PUBLIC USES di string:DWORD, val:size_t, count:size_t
	mov	cx,count
	les	di,string
	cld?
	mov	ax,val
	rep	stosw
	ret
wcmemset ENDP

	END
