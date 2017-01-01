include consx.inc
include alloc.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

rcreadc PROC USES rbx rsi rdi buf:PVOID, bsize, rect:PVOID
	local	bz:COORD
	local	rc:SMALL_RECT

	mov	rdi,rcx
	mov	bz,edx
	mov	rax,[r8]
	mov	QWORD PTR rc,rax

	.if	!ReadConsoleOutput( hStdOutput, rdi, bz, 0, addr rc )

		mov	ax,rc.Top
		mov	rc.Bottom,ax
		movzx	ebx,bz.y
		mov	bz.y,1
		movzx	esi,bz.x
		shl	esi,2

		.repeat
			.break .if !ReadConsoleOutput( hStdOutput, rdi, bz, 0, addr rc )
			inc	rc.Bottom
			inc	rc.Top
			add	rdi,rsi
			dec	ebx
		.until !ebx
		xor	eax,eax
		.if	!ebx
			inc eax
		.endif
	.endif
	ret
rcreadc ENDP

rcread	PROC USES rbx rsi rdi rbp rc, wc:PVOID

	local	bz:COORD
	local	rect:SMALL_RECT

	mov	rdi,rdx
	mov	eax,ecx
	shr	eax,16
	movzx	ebp,al
	mov	bz.x,bp
	movzx	eax,ah
	mov	bz.y,ax
	mov	ebx,eax
	mov	al,ch
	mov	rect.Top,ax
	mov	al,cl
	mov	rect.Left,ax
	mov	eax,ebx
	add	ax,rect.Top
	dec	eax
	mov	rect.Bottom,ax
	mov	eax,ebp
	add	ax,rect.Left
	dec	eax
	mov	rect.Right,ax
	mov	eax,ebx
	mul	ebp
	shl	eax,2
	malloc( rax )
	mov	rsi,rax

	.if	rax
		.if	rcreadc( rsi, bz, addr rect )
			.repeat
				mov ecx,ebp
				.repeat
					lodsw
					stosb
					lodsw
					stosb
				.untilcxz
				dec	ebx
			.until !ebx
			inc	ebx
			mov	eax,ebx
		.endif
		free(rsi)
	.endif
	ret

rcread	ENDP

	END
