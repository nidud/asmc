; char *strshr(char *string, char ch);
;
; shift string to the right and insert char in front of string
;
include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

strshr	PROC string:LPSTR, char:SIZE_T

	mov	r8,rcx
	mov	eax,[rcx]
	shl	eax,8
	mov	al,dl
@@:
	mov	edx,[rcx+3]
	mov	[rcx],eax
	test	eax,000000FFh
	jz	@F
	test	eax,0000FF00h
	jz	@F
	test	eax,00FF0000h
	jz	@F
	test	eax,0FF000000h
	jz	@F
	mov	eax,edx
	add	rcx,4
	jmp	@B
@@:
	mov	rax,r8
	ret

strshr	ENDP

	END
