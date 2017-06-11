include strlib.inc

	.code

	option stackbase:esp

strchri PROC uses esi string:LPSTR, char:SIZE_T

	mov	esi,string
	movzx	eax,byte ptr char

	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	cl,cl
	and	cl,'a'-'A'
	add	cl,al
	add	cl,'A'
@@:
	mov	al,[esi]
	test	eax,eax
	jz	toend
	add	esi,1
	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	ch,ch
	and	ch,'a'-'A'
	add	al,ch
	add	al,'A'
	cmp	al,cl
	jne	@B
	mov	eax,esi
	dec	eax
toend:
	ret

strchri ENDP

	END
