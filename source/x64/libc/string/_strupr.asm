include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

_strupr PROC string:LPSTR
	push	rcx
@@:
	mov	al,[rcx]
	test	al,al
	jz	@F
	sub	al,'a'
	cmp	al,'Z' - 'A' + 1
	sbb	al,al
	and	al,'a' - 'A'
	xor	[rcx],al
	inc	rcx
	jmp	@B
@@:
	pop	rax
	ret
_strupr ENDP

	END
