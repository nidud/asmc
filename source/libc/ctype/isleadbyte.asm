include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isleadbyte PROC wc:SINT
	movzx	eax,BYTE PTR [esp+4]
	mov	ax,_ctype[eax*2+2]
	and	eax,_LEADBYTE
	ret	4
isleadbyte ENDP

	END

