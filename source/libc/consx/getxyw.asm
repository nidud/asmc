include consx.inc

	.code

getxyw	PROC USES ebx x, y
	getxya( x, y )
	mov	ebx,eax
	getxyc( x, y )
	mov	ah,bl
	ret
getxyw	ENDP

	END
