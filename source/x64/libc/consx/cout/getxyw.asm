include consx.inc

	.code

getxyw	PROC USES rbx x, y
	getxya( ecx, edx )
	mov	ebx,eax
	getxyc( x, y )
	mov	ah,bl
	ret
getxyw	ENDP

	END
