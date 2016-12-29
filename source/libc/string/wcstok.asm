include string.inc

	.data
	s0 dd ?

	.code

wcstok	PROC USES edx ebx s1:LPWSTR, s2:LPWSTR
	mov	eax,s1
	.if	eax
		mov	s0,eax
	.endif
	mov	ebx,s0
	.while	word ptr [ebx]
		mov	ecx,s2
		mov	ax,[ecx]
		.while	ax
			.break .if ax == [ebx]
			add	ecx,2
			mov	ax,[ecx]
		.endw
		.break .if !ax
		add	ebx,2
	.endw
	sub	eax,eax
	cmp	[ebx],ax
	je	toend
	mov	edx,ebx
	.while	word ptr [ebx]
		mov	ecx,s2
		mov	ax,[ecx]
		.while	ax
			.if	ax == [ebx]
				mov	word ptr [ebx],0
				add	ebx,2
				jmp	retok
			.endif
			add	ecx,2
			mov	ax,[ecx]
		.endw
		add	ebx,2
	.endw
retok:
	mov	eax,edx
toend:
	mov	s0,ebx
	ret
wcstok	ENDP

	END
