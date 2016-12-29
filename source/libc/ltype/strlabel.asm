include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

strlabel PROC string:LPSTR, usedot:UINT
	mov	ecx,[esp+4]
	movzx	eax,BYTE PTR [ecx]
	test	__ctype[eax+1],_UPPER or _LOWER
	jnz	@F
	cmp	eax,'_'
	je	@F
	cmp	eax,'@'
	je	@F
	cmp	eax,'$'
	je	@F
	cmp	eax,'?'
	je	@F
	cmp	eax,'.'
	jne	nolabel
	cmp	DWORD PTR [esp+8],0
	je	nolabel
@@:
	add	ecx,1
	movzx	eax,BYTE PTR [ecx]
	test	__ctype[eax+1],_UPPER or _LOWER or _DIGIT
	jnz	@B
	test	eax,eax
	jz	done
	cmp	eax,'_'
	je	@B
	cmp	eax,'@'
	je	@B
	cmp	eax,'$'
	je	@B
	cmp	eax,'?'
	je	@B
nolabel:
	xor	eax,eax
toend:
	ret	8
done:
	cmp	BYTE PTR [ecx-1],'.'
	je	nolabel
	mov	eax,[esp+4]
	jmp	toend
strlabel ENDP

	END

