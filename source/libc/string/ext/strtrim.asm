include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

strtrim PROC string:LPSTR
	mov	eax,[esp+4]
	strlen( eax )
	jz	toend
	mov	ecx,eax
	add	ecx,[esp+4]
@@:
	dec	ecx
	cmp	byte ptr [ecx],' '
	ja	toend
	mov	byte ptr [ecx],0
	dec	eax
	jnz	@B
toend:
	ret	4
strtrim ENDP

	END
