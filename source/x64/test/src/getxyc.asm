include consx.inc

	.code

main	PROC
	mov	rsi,getxyc( 0, 0 )
	scputc( 0, 0, 1, 'x' )
	mov	rdi,getxyc( 0, 0 )
	scputc( 0, 0, 1, esi )
	getxyc( 0, 0 )
	.assert edi == 'x'
	.assert eax == esi
	xor	eax,eax
	ret
main	ENDP

	END
