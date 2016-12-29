include io.inc

	.code

_isatty PROC handle:SINT
	mov	eax,handle
	mov	al,_osfile[eax]
	and	eax,FH_DEVICE
	ret
_isatty ENDP

	END
