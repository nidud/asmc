include ctype.inc

	.code

tiisword PROC
	movzx	eax,al
	mov	ah,byte ptr _ctype[eax*2+2]
	test	ah,_UPPER or _LOWER or _DIGIT
	jnz	toend
	cmp	al,'_'
	jne	@F
	test	al,al
	ret
@@:
	cmp	al,al
toend:
	ret
tiisword ENDP

	END
