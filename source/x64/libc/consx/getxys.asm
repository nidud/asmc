include consx.inc

	.code

getxys	PROC x, y, b:LPSTR, l, bsize
	mov	ah,1
	mov	al,r9b
	shl	eax,16
	mov	ah,dl
	mov	al,cl
	dledit( r8, eax, bsize, 0 )
	ret
getxys	ENDP

	END
