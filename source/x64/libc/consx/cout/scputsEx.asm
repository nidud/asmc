include consx.inc

	.code

scputsEx PROC USES rsi rdi rbx r12 x, y, a, l, string:LPSTR
	mov	rdi,string
	mov	esi,x
	mov	ebx,l
	mov	ah,BYTE PTR a
	.repeat
		mov	al,BYTE PTR [rdi]
		inc	rdi
		.switch al
		  .case 9
			add	esi,16
			and	esi,0FFF0h
			.endc
		  .case 10
			mov	esi,x
			inc	y
			.endc
		  .case 0
			mov	bl,al
			.endc
		  .case '&'
			.if	bh
				mov	al,bh
				mov	r12d,ecx
				lea	rcx,[rsi-1]
				scputa( ecx, y, 1, eax )
				mov	ecx,r12d
				.endc
			.endif
		  .default
			scputw( esi, y, 1, eax )
			inc	esi
			dec	bl
		.endsw
	.until	!bl
	mov	rax,rdi
	sub	rax,string
	dec	rax
	ret
scputsEx ENDP

	END
