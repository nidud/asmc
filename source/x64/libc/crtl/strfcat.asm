include string.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

strfcat PROC USES rsi rdi,
	buffer: LPSTR,			; "" or "[[C:]\]..."
	path:	LPSTR,			;  0 or "[[C:]\]..."
	file:	LPSTR			; "File or Directory name"


	mov	rsi,rdx
	mov	rdx,rcx

	xor	rax,rax
	lea	rcx,[rax-1]

	.if	rsi
		mov	rdi,rsi		; overwrite buffer
		repne	scasb
		mov	rdi,rdx
		not	rcx
		rep	movsb
	.else
		mov	rdi,rdx		; length of buffer
		repne	scasb
	.endif

	dec	rdi
	.if	rdi != rdx		; add slash if missing

		mov	al,[rdi-1]
		.if	!( al == '\' || al == '/' )

			mov	al,'\'
			stosb
		.endif
	.endif

	mov	rsi,r8			; add file name
	.repeat
		lodsb
		stosb
	.until !eax

	mov	rax,rdx
	ret
strfcat ENDP

	END
