; char *strshr(char *string, char ch);
;
; shift string to the right and insert char in front of string
;
include string.inc

	.code

	option stackbase:esp

strshr	proc uses edx ecx string:LPSTR, char:UINT

	mov	edx,string
	mov	eax,[edx]
	shl	eax,8
	mov	al,byte ptr char
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
	mov	eax,string
	ret

strshr	ENDP

	END
