include string.inc

	.code

memcmp	PROC USES esi edi s1:LPSTR, s2:LPSTR, len:SIZE_T
	mov	edi,s1
	mov	esi,s2
	mov	ecx,len
	xor	eax,eax
	repe	cmpsb
	je	@F
	sbb	eax,eax
	sbb	eax,-1
@@:
	ret
memcmp	ENDP

	END
