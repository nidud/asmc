include stdlib.inc
include string.inc

	.code

qsort	PROC USES rsi rdi rbx p:PVOID, n:SIZE_T, w:SIZE_T, compare:LPQSORTCMD

local	stack_level

	mov	rax,n
	.if	rax > 1

		dec	rax
		mul	w
		mov	rsi,p
		lea	rdi,[rsi+rax]
		mov	stack_level,0

		.while	1

			mov	rcx,w
			lea	rax,[rdi+rcx]	; middle from (hi - lo) / 2
			sub	rax,rsi
			.ifnz
				xor	rdx,rdx
				div	rcx
				shr	rax,1
				mul	rcx
			.endif

			lea	rbx,[rsi+rax]
			.ifs	compare( rsi, rbx ) > 0

				memxchg( rsi, rbx, w )
			.endif
			.ifs	compare( rsi, rdi ) > 0

				memxchg( rsi, rdi, w )
			.endif
			.ifs	compare( rbx, rdi ) > 0

				memxchg( rbx, rdi, w )
			.endif

			mov	p,rsi
			mov	n,rdi

			.while	1

				mov	rax,w
				add	p,rax
				.if	p < rdi

					.continue .ifs compare( p, rbx ) <= 0
				.endif

				.while	1

					mov	rax,w
					sub	n,rax

					.break .if n <= rbx
					.break .ifs compare( n, rbx ) <= 0
				.endw

				mov	rdx,n
				mov	rax,p
				.break .if rdx < rax

				memxchg( rdx, rax, w )

				.if	rbx == n

					mov	rbx,p
				.endif
			.endw

			mov	rax,w
			add	n,rax

			.while	1

				mov	rax,w
				sub	n,rax

				.break .if n <= rsi
				.break .if compare( n, rbx )
			.endw

			mov	rdx,p
			mov	rax,n
			sub	rax,rsi
			mov	rcx,rdi
			sub	rcx,rdx

			.ifs	rax < rcx

				mov	rcx,n

				.if	rdx < rdi

					push	rdx
					push	rdi
					inc	stack_level
				.endif

				.if	rsi < rcx

					mov	rdi,rcx
					.continue
				.endif
			.else
				mov	rcx,n

				.if	rsi < rcx

					push	rsi
					push	rcx
					inc	stack_level
				.endif

				.if	rdx < rdi

					mov	rsi,rdx
					.continue
				.endif
			.endif

			.break .if !stack_level

			dec	stack_level
			pop	rdi
			pop	rsi
		.endw
	.endif
	ret

qsort	ENDP

	END
