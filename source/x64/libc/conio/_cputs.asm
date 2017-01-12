include conio.inc
include string.inc

	.code

_cputs	proc uses rbx string:LPSTR

	local	num_written:ULONG
	;
	; write string to console file handle
	;
	mov	rbx,-1
	.if	hStdOutput != rbx

		mov	r9,strlen( string )
		.if	!WriteConsole(
				hStdOutput,
				string,
				r9d,
				addr num_written,
				NULL )

			xor rbx,rbx
		.endif
	.endif

	mov	rax,rbx
	ret

_cputs	ENDP

	END
