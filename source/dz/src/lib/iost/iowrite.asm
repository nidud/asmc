include iost.inc

	.code

	ASSUME	ebx:PTR S_IOST

iowrite PROC USES esi edi ebx iost:PTR S_IOST, buf:PVOID, len
	mov	esi,buf
	mov	ebx,iost
lupe:
	mov	ecx,len
	mov	edi,[ebx].ios_i
	mov	eax,[ebx].ios_size
	sub	eax,edi
	add	edi,[ebx].ios_bp
	cmp	eax,ecx
	jb	tobig
	add	[ebx].ios_i,ecx
	rep	movsb
toend:
	mov	eax,esi
	ret
tobig:
	add	[ebx].ios_i,eax
	sub	len,eax
	mov	ecx,eax
	rep	movsb
	ioflush( ebx )
	jnz	lupe
	jmp	toend
iowrite ENDP

	END
