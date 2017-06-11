include strlib.inc

	.code

	option stackbase:esp

strstart PROC string:LPSTR
	mov	eax,string
@@:
	add	eax,1
	cmp	byte ptr [eax-1],' '
	je	@B
	cmp	byte ptr [eax-1],9
	je	@B
	sub	eax,1
	ret
strstart ENDP

	END
