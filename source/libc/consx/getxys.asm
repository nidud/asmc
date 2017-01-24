include consx.inc

	.code

getxys	PROC x, y, b:LPSTR, l, bsize
	mov	ah,1
	mov	al,BYTE PTR l
	shl	eax,16
	mov	ah,BYTE PTR y
	mov	al,BYTE PTR x
	dledit( b, eax, bsize, 0 )
	ret
getxys	ENDP

	END
