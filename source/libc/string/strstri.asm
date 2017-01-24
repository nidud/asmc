include string.inc

memstri PROTO :LPSTR, :SIZE_T, :LPSTR, :SIZE_T

	.code

strstri PROC dst:LPSTR, src:LPSTR
	strlen( dst )
	push	eax
	strlen( src )
	pop	ecx
	memstri( dst, ecx, src, eax )
	ret
strstri ENDP

	END
