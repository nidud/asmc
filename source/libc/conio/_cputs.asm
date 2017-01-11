include consx.inc
include conio.inc
include string.inc

	.code

_cputs	proc uses ebx string:LPSTR

	local	num_written:ULONG
	;
	; write string to console file handle
	;
	mov	ebx,-1
	.if	hStdOutput != ebx

		mov	edx,strlen( string )
		.if	!WriteConsole(
				hStdOutput,
				string,
				edx,
				addr num_written,
				NULL )

			xor ebx,ebx
		.endif
	.endif

	mov	eax,ebx
	ret

_cputs	ENDP

	END
