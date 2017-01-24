include consx.inc

	.code

ticmdfailed PROC
	mov	eax,_TE_CMFAILED ; operation fail (end of line/buffer)
	ret
ticmdfailed ENDP

	END
