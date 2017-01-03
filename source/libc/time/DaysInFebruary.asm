include time.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE, STACKBASE:ESP

DaysInFebruary PROC year

	mov	eax,year

	.while	1

		.break .if !eax

		.if  !( eax & 3 )

			mov	ecx,100
			xor	edx,edx
			div	ecx
			.break .if edx

			mov	eax,year
		.endif

		mov	ecx,400
		xor	edx,edx
		div	ecx
		.break .if !edx

		mov	eax,28
		jmp	toend
	.endw
	mov	eax,29
toend:
	ret	4

DaysInFebruary ENDP

	END
