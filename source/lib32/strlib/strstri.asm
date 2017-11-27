include string.inc
include strlib.inc

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
