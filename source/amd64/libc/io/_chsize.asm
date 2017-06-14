include io.inc
include errno.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

_chsize PROC USES rdi rsi rbx r12 r13 handle:SINT, new_size:QWORD

  local buf[512]:SBYTE

	mov	r12,rdx ; new_size
	mov	r13d,ecx ; handle
	lea	rsi,buf
	xor	rdx,rdx

	.if	_lseek( ecx, rdx, SEEK_CUR ) != -1

		mov	rbx,rax ; save current offset

		.if	_lseek( r13d, 0, SEEK_END ) != -1
			.if	rax > r12
				.if	_lseek( r13d, r12, SEEK_SET ) != -1
					;
					; Write zero byte at current file position
					;
					oswrite( r13d, rsi, 0 )
					jmp	seekback
				.endif
				jmp	toend
			.elseif ZERO?
				jmp	seekback	; All done..
			.else
				mov	r8,rax
				mov	rdi,rsi
				xor	rax,rax
				mov	rcx,512/4
				rep	stosd
				mov	rdi,r12
				sub	rdi,r8
				.repeat
					mov	r12,512
					.if	rdi < r12

						mov	r12,rdi
						test	rdi,rdi
						jz	seekback
					.endif
					sub	rdi,r12
					oswrite( r13d, rsi, r12 )
				.until	rax != r12

				mov	errno,ERROR_DISK_FULL
				mov	rax,-1
			.endif
		.endif
	.endif
toend:
	ret

seekback:
	_lseek( r13d, rbx, SEEK_SET )
	cmp	rax,-1
	je	toend
	xor	rax,rax
	jmp	toend
_chsize ENDP

	END
