; GETXYS.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

getxys	PROC _CType PUBLIC x:size_t, y:size_t, b:DWORD, l:size_t, bsize:size_t
	mov	dh,1
	mov	dl,BYTE PTR l
	mov	ah,BYTE PTR y
	mov	al,BYTE PTR x
	invoke	dledit,b,dx::ax,bsize,0
	ret
getxys	ENDP

	END
