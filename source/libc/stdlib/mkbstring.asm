include stdlib.inc
include string.inc
include stdio.inc

	.code

mkbstring PROC USES esi edi buf:LPSTR, qw:QWORD

	local	tmp[32]:BYTE

	sprintf( addr tmp, "%I64u", qw )
	_strrev( addr tmp )

	mov	esi,eax
	mov	edi,buf
	xor	edx,edx
	mov	ah,' '
	.repeat
		lodsb
		stosb
		.break .if !al
		inc	dl
		.if	dl == 3
			mov	al,ah
			stosb
			xor	dl,dl
		.endif
	.until	0
	.if	[edi-2] == ah
		mov	[edi-2],dh
	.endif
	_strrev( buf )
	mov	eax,DWORD PTR qw
	mov	ecx,DWORD PTR qw+4
	xor	edx,edx
	.while	ecx || eax > 1024*10
		shrd	eax,ecx,10
		shr	ecx,10
		inc	edx
	.endw
	ret
mkbstring ENDP

	END
