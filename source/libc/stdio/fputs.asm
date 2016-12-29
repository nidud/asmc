include stdio.inc
include string.inc

	.code

fputs	PROC string:LPSTR, fp:LPFILE
	_stbuf( fp )
	push	eax
	fwrite( string, 1, strlen( string ), fp )
	pop	edx
	push	eax
	_ftbuf( edx, fp )
	strlen( string )
	pop	edx
	cmp	eax,edx
	mov	eax,0
	je	@F
	dec	eax
@@:
	ret
fputs	ENDP

	END
