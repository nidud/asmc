include io.inc
include cfini.inc
include alloc.inc
include string.inc

	.code

__CFRead PROC USES esi edi ebx __ini:PCFINI, __file:LPSTR

local	i_fh, i_bp, i_i, i_c, o_bp, o_i, o_c

	.if	osopen( __file, _A_NORMAL, M_RDONLY, A_OPEN ) != -1

		mov	i_fh,eax
		mov	i_bp,alloca(_PAGESIZE_*2)
		add	eax,_PAGESIZE_
		mov	o_bp,eax
		xor	eax,eax
		mov	i_i,eax
		mov	i_c,eax
		mov	o_i,eax
		mov	o_c,eax

		.if	eax == __ini

			mov	__ini,__CFAlloc()
		.endif
		mov	ebx,__ini

		.while	1

			mov	eax,i_i
			.if	eax == i_c

				.break .if !osread( i_fh, i_bp, _PAGESIZE_ )

				mov	i_c,eax
				xor	eax,eax
				mov	i_i,eax
			.endif

			inc	i_i
			add	eax,i_bp
			movzx	eax,byte ptr [eax]

			mov	edx,o_i
			inc	o_i
			add	edx,o_bp
			mov	[edx],ax

			.if	eax == 10 || edx == _PAGESIZE_ - 2

				mov	o_i,0
				mov	edi,o_bp
				mov	al,[edi]

				.switch al

				  .case 10
				  .case 13
					.endc
				  .case '['
					inc	edi
					.if	strchr( edi, ']' )

						mov	byte ptr [eax],0

						.break .if !__CFAddSection(__ini, edi)

						mov	ebx,eax
					.endif
					.endc
				  .default
					CFAddEntry(ebx, edi)
				.endsw
			.endif
		.endw

		_close( i_fh )
		mov	eax,__ini
	.else

		xor	eax,eax
	.endif
	ret

__CFRead ENDP

	END
