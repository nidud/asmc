include strlib.inc

	.code

unixtodos PROC string:LPSTR
	mov	eax,string
@@:
	cmp	byte ptr [eax],0
	je	@F
	cmp	byte ptr [eax],'/'
	lea	eax,[eax+1]
	jne	@B
	mov	byte ptr [eax-1],'\'
	jmp	@B
@@:
	mov	eax,string
	ret
unixtodos ENDP

	END
