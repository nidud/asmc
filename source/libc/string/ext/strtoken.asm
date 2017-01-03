include string.inc
include ctype.inc

	.data
	token dd ?

	.code

strtoken PROC string:LPSTR
	mov	eax,string
	mov	ecx,token
	test	eax,eax
	jz	@F
	mov	ecx,eax
	xor	eax,eax
@@:
	mov	al,[ecx]
	inc	ecx
	test	[eax + __ctype + 1],_SPACE
	jnz	@B
	dec	ecx
	mov	token,ecx
	test	al,al
	jz	fail
@@:
	mov	al,[ecx]
	inc	ecx
	test	al,al
	jz	@F
	test	[eax + __ctype + 1],_SPACE
	jz	@B
	mov	[ecx-1],ah
	inc	ecx
@@:
	dec	ecx
	mov	eax,token
	mov	token,ecx
	jmp	toend
fail:
	xor	eax,eax
toend:
	ret
strtoken ENDP

	END
