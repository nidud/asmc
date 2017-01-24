include io.inc

	.code

osfiletype PROC h:SINT
	mov	eax,h
	mov	eax,_osfhnd[eax*4]
	GetFileType( eax )
	ret
osfiletype ENDP

	END
