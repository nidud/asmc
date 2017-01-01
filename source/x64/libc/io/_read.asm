include io.inc
include errno.inc

ER_ACCESS_DENIED equ 5
ER_BROKEN_PIPE	 equ 109

	.data
	pipech	db _NFILE_ dup(10)
	peekchr db 0

	.code

	OPTION	WIN64:3, STACKBASE:rsp

_read	PROC USES rbx rsi rdi r12 r13 h:SINT, b:PVOID, count:SIZE_T
	xor	rsi,rsi			; nothing read yet
	mov	rdi,rdx
	mov	rbx,rcx

	xor	rax,rax			; nothing to read or at EOF
	cmp	rax,r8
	je	toend

	lea	r13,_osfile
	add	r13,rcx

	mov	cl,[r13]
	test	cl,FH_EOF
	jnz	toend

	mov	oserrno,eax

	.if	cl & FH_PIPE or FH_DEVICE
		lea	rcx,pipech
		mov	al,[rcx+rbx]
		.if	al != 10
			mov	[rdi],al
			mov	BYTE PTR [rcx+rbx],10
			inc	rdi
			inc	rsi
			dec	r8
		.endif
	.endif

	osread( ebx, rdi, r8 )
	test	rcx,rcx
	jz	error

	add	rsi,rax
	mov	rdi,b
	mov	al,[r13]

	.if	al & FH_TEXT
		and	al,not FH_CRLF
		.if	byte ptr [rdi] == 10
			or al,FH_CRLF
		.endif
		mov	[r13],al
		mov	r12,rdi
		.while	1
			mov	rax,b
			add	rax,rsi
			.break .if rdi >= rax

			mov	al,[rdi]
			.if	al == 26
				.break .if BYTE PTR[r13] & FH_DEVICE
				or	BYTE PTR [r13],FH_EOF
				.break
			.endif
			.if	al != 13
				mov	[r12],al
				inc	rdi
				inc	r12
				.continue
			.endif
			mov	rax,b
			lea	rax,[rax+rsi-1]
			.if	rdi < rax
				.if	byte ptr [rdi+1] == 10
					add	rdi,2
					mov	al,10
				.else
					mov	al,[rdi]
					inc	rdi
				.endif
				mov	[r12],al
				inc	r12
				.continue
			.endif

			inc	rdi
			mov	oserrno,0
			osread( ebx, addr peekchr, 1 )

			.if	!rax || oserrno
				mov	al,13
			.elseif BYTE PTR [r13] & FH_DEVICE or FH_PIPE
				mov	al,10
				.if	peekchr != al
					mov	al,peekchr
					lea	rcx,pipech
					mov	[rcx+rbx],al
					mov	al,13
				.endif
			.else
				mov	al,10
				.if	b != r12 || peekchr != al

					_lseek( ebx, -1, SEEK_CUR )
					mov	al,13
					.continue .if peekchr == 10
				.endif
			.endif
			mov	[r12],al
			inc	r12
		.endw
		mov	rax,r12
		sub	rax,b
	.else
		mov	rax,rsi
	.endif
toend:
	ret
error:
	xor	eax,eax
	mov	edx,oserrno
	cmp	edx,ER_BROKEN_PIPE
	je	toend
	dec	rax
	cmp	edx,ER_ACCESS_DENIED
	jne	toend
	mov	errno,EBADF
	jmp	toend
_read	ENDP

	END
