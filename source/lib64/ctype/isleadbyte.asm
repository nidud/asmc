include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

isleadbyte PROC wc:SINT
	lea	rax,_ctype
	mov	ax,[rax+rcx*2+2]
	and	eax,_LEADBYTE
	ret
isleadbyte ENDP

	END

