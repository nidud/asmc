include string.inc

	.code

wcspbrk PROC USES esi edi ecx s1:LPWSTR, s2:LPWSTR
	mov	esi,s1
	mov	cx,[esi]
	.while	cx
		mov	edi,s2
		mov	ax,[edi]
		.while	ax
			.if	ax == cx
				mov	eax,esi
				jmp	toend
			.endif
			add	edi,2
			mov	ax,[edi]
		.endw
		add	esi,2
		mov	cx,[esi]
	.endw
	xor	eax,eax
  toend:
	ret
wcspbrk ENDP

	END
