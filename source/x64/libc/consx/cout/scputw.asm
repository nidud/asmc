include consx.inc

	.code

scputw	PROC x, y, l, w
	mov	eax,r9d
	.if	ah
		mov al,ah
		scputa( ecx, edx, r8d, eax )
	.endif
	scputc( x, y, l, w )
	ret
scputw	ENDP

	END
