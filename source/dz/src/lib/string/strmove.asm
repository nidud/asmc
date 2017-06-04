include string.inc

	.code

strmove PROC dst:LPSTR, src:LPSTR
	strlen( src )
	inc	eax
	memmove( dst, src, eax )
	ret
strmove ENDP

	END
