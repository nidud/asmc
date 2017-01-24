include stdlib.inc
include string.inc

	.code

qsort	PROC USES esi edi ebx p:PVOID, n:SIZE_T, w:SIZE_T, compare:PVOID

local	q

	mov	eax,n
	.if	eax > 1

		dec	eax
		mul	w
		mov	esi,p
		lea	edi,[esi+eax]
		mov	q,0

		.while	1

			mov	ecx,w
			lea	eax,[edi+ecx]	; middle from (hi - lo) / 2
			sub	eax,esi

			.if	!ZERO?

				sub	edx,edx
				div	ecx
				shr	eax,1
				mul	ecx
			.endif

			lea	ebx,[esi+eax]
			push	ebx
			push	esi
			call	compare
			.if	SDWORD PTR eax > 0

				memxchg( ebx, esi, w )
			.endif

			push	edi
			push	esi
			call	compare
			.if	SDWORD PTR eax > 0

				memxchg( edi, esi, w )
			.endif

			push	edi
			push	ebx
			call	compare
			.if	SDWORD PTR eax > 0

				memxchg( ebx, edi, w )
			.endif

			mov	p,esi
			mov	n,edi

			.while	1

				mov	eax,w
				add	p,eax
				.if	p < edi

					push	ebx
					push	p
					call	compare
					.continue .if SDWORD PTR eax <= 0
				.endif

				.while	1

					mov	eax,w
					sub	n,eax

					.break .if n <= ebx
					push	ebx
					push	n
					call	compare
					.break .if SDWORD PTR eax <= 0
				.endw

				mov	edx,n
				mov	eax,p
				.break .if edx < eax

				memxchg( edx, eax, w )

				.if	ebx == n

					mov	ebx,p
				.endif
			.endw

			mov	eax,w
			add	n,eax

			.while	1

				mov	eax,w
				sub	n,eax

				.break .if n <= esi

				push	ebx
				push	n
				call	compare
				.break .if eax
			.endw

			mov	edx,p
			mov	eax,n
			sub	eax,esi
			mov	ecx,edi
			sub	ecx,edx

			.if	SDWORD PTR eax < ecx

				mov	ecx,n

				.if	edx < edi

					push	edx
					push	edi
					inc	q
				.endif

				.if	esi < ecx

					mov	edi,ecx
					.continue
				.endif
			.else
				mov	ecx,n

				.if	esi < ecx

					push	esi
					push	ecx
					inc	q
				.endif

				.if	edx < edi

					mov	esi,edx
					.continue
				.endif
			.endif

			.break .if !q
			dec	q
			pop	edi
			pop	esi
		.endw
	.endif
	ret

qsort	ENDP

	END
