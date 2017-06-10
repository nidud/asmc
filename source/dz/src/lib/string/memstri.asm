include string.inc

	.code

	option stackbase:esp

memstri PROC uses esi edi ebx edx s1:LPSTR, l1:SIZE_T, s2:LPSTR, l2:SIZE_T

	mov	edi,s1
	mov	ecx,l1
	mov	esi,s2

	mov	al,[esi]
	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	bl,bl
	and	bl,'a'-'A'
	add	bl,al
	add	bl,'A'
scan:
	test	ecx,ecx
	jz	nomatch
	dec	ecx
	mov	al,[edi]
	add	edi,1
	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	bh,bh
	and	bh,'a'-'A'
	add	al,bh
	add	al,'A'
	cmp	al,bl
	jne	scan
	mov	edx,l2
	dec	edx
	jz	match
	cmp	ecx,edx
	jl	nomatch
compare:
	dec	edx
	jl	match
	mov	al,[esi+edx+1]
	cmp	al,[edi+edx]
	je	compare
	mov	ah,[edi+edx]
	sub	ax,'AA'
	cmp	al,'Z'-'A' + 1
	sbb	bh,bh
	and	bh,'a'-'A'
	add	al,bh
	cmp	ah,'Z'-'A' + 1
	sbb	bh,bh
	and	bh,'a'-'A'
	add	ah,bh
	add	ax,'AA'
	cmp	al,ah
	je	compare
	jmp	scan
nomatch:
	xor	eax,eax
	jmp	toend
match:
	mov	eax,edi
	dec	eax
toend:
	ret

memstri ENDP

	END
