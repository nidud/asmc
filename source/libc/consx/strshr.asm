; char *strshr(char *string, char ch);
;
; shift string to the right and insert char in front of string
;
include consx.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

strshr	PROC string:LPSTR, char:UINT

	push	edx
	push	ecx

	mov	edx,8[esp+4]
	mov	eax,[edx]
	shl	eax,8
	mov	al,8[esp+8]
@@:
	mov	ecx,[edx+3]
	mov	[edx],eax
	test	eax,0x000000FF
	jz	@F
	test	eax,0x0000FF00
	jz	@F
	test	eax,0x00FF0000
	jz	@F
	test	eax,0xFF000000
	jz	@F
	mov	eax,ecx
	add	edx,4
	jmp	@B
@@:
	mov	eax,8[esp+4]

	pop	ecx
	pop	edx
	ret	8

strshr	ENDP

	END
