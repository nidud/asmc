include ctype.inc

	.code

	option stackbase:esp

isleadbyte PROC wc:SINT
	movzx	eax,BYTE PTR [esp+4]
	mov	ax,_ctype[eax*2+2]
	and	eax,_LEADBYTE
	ret
isleadbyte ENDP

	END

