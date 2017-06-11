; char *strspace(char *) - search a string for the character SPACE and TAB
;
; If found the char is returned in CL and the pointer in EAX
; Else zero is returned and ECX points to the last char in the string
;
include strlib.inc

	.code

	option stackbase:esp

strspace PROC string:LPSTR
	mov	ecx,string
@@:
	mov	al,[ecx]
	inc	ecx
	cmp	al,' '
	je	found
	cmp	al,9
	je	found
	test	al,al
	jnz	@B
	dec	ecx
	xor	eax,eax
	jmp	toend
found:
	mov	eax,ecx
	dec	eax
	movzx	ecx,byte ptr [eax]
toend:
	ret
strspace ENDP

	END

