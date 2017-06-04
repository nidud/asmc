include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

strstart PROC string:LPSTR
	mov	eax,[esp+4]
@@:
	add	eax,1
	cmp	byte ptr [eax-1],' '
	je	@B
	cmp	byte ptr [eax-1],9
	je	@B
	sub	eax,1
	ret	4
strstart ENDP

	END
