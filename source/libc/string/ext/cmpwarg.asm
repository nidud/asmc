include string.inc

	.code

cmpwarg PROC USES esi edi cpFile:LPSTR, cpMask:LPSTR

	mov	esi,cpFile
	mov	edi,cpMask
	xor	eax,eax

	continue:

		lodsb
		mov	ah,[edi]
		inc	edi

		.if ah == '*'

		     @@:
			mov	ah,[edi]
			test	ah,ah
			jz	return_1
			inc	edi
			cmp	ah,'.'
			jne	@B
			xor	edx,edx
			.while	al
				.if al == ah
					mov edx,esi
				.endif
				lodsb
			.endw
			test	edx,edx
			mov	esi,edx
			jnz	continue
			mov	ah,[edi]
			inc	edi
			cmp	ah,'*'
			je	@B

			test	eax,eax
			jz	return_1
			jmp	return_0
		.endif

		.if !al
			test	eax,eax
			jnz	return_0
			jmp	return_1
		.endif
		test	ah,ah
		jz	return_0
		cmp	ah,'?'
		je	continue

		.if ah == '.'
			cmp	al,'.'
			je	continue
			jmp	return_0
		.endif
		cmp	al,'.'
		je	return_0
		or	eax,2020h
		cmp	al,ah
		je	continue
return_0:
	xor	eax,eax
toend:
	test	eax,eax
	ret
return_1:
	mov	eax,1
	jmp	toend
cmpwarg ENDP

cmpwargs PROC USES edi filep:LPSTR, maskp:LPSTR
	mov	edi,maskp
	.repeat
		.if strchr( edi, ' ' )
			mov	edi,eax
			mov	byte ptr [edi],0
			cmpwarg( filep, eax )
			mov	byte ptr [edi],' '
			inc	edi
		.else
			cmpwarg( filep, edi )
			.break
		.endif
	.until	eax
	ret
cmpwargs ENDP

	END
