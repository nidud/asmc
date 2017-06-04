include consx.inc

	.code

scputw	PROC USES eax x, y, l, w
	mov	eax,w
	.if	ah
		mov al,ah
		scputa( x, y, l, eax )
	.endif
	scputc( x, y, l, w )
	ret
scputw	ENDP

	END
