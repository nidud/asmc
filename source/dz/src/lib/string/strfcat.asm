include string.inc

	.code

strfcat PROC USES esi edi ecx edx,
	buffer: LPSTR,			; "" or "[[C:]\]..."
	path:	LPSTR,			;  0 or "[[C:]\]..."
	file:	LPSTR			; "File or Directory name"


	mov	edx,buffer
	mov	esi,path

	xor	eax,eax
	lea	ecx,[eax-1]

	.if	esi
		mov	edi,esi		; overwrite buffer
		repne	scasb
		mov	edi,edx
		not	ecx
		rep	movsb
	.else
		mov	edi,edx		; length of buffer
		repne	scasb
	.endif

	dec	edi
	.if	edi != edx		; add slash if missing

		mov	al,[edi-1]
		.if	!( al == '\' || al == '/' )

			mov	al,'\'
			stosb
		.endif
	.endif

	mov	esi,file		; add file name
	.repeat
		lodsb
		stosb
	.until !eax

	mov	eax,edx
	ret
strfcat ENDP

	END
