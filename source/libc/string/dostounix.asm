include string.inc

	.code

dostounix PROC string:LPSTR
	mov	eax,string
@@:
	cmp	byte ptr [eax],0
	je	@F
	cmp	byte ptr [eax],'\'
	lea	eax,[eax+1]
	jne	@B
	mov	byte ptr [eax-1],'/'
	jmp	@B
@@:
	mov	eax,string
	ret
dostounix ENDP

	END
