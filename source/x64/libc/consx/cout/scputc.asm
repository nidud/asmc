include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

scputc	PROC uses rcx rdx r8 r9 x, y, l, char

	local	NumberOfCharsWritten

	movzx	eax,dl
	shl	eax,16
	mov	al,cl
	movzx	edx,r9b
	mov	r9d,eax

	FillConsoleOutputCharacter(
		hStdOutput,
		edx,
		r8d,
		r9d,
		addr NumberOfCharsWritten )
	ret

scputc	ENDP

	END
