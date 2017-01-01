include consx.inc
include stdio.inc

	.code

_getch	PROC USES rbx rdi rsi

	local	Count:QWORD
	local	Event[MAXINPUTRECORDS]:INPUT_RECORD

	xor	edi,edi
	.while	!edi

		.if GetNumberOfConsoleInputEvents( hStdInput, addr Count )

			mov r8,Count
			.if r8 > MAXINPUTRECORDS
				mov r8,MAXINPUTRECORDS
			.endif

			lea	rbx,Event
			ReadConsoleInput( hStdInput, rbx, r8d, addr Count )

			mov	rsi,Count
			.while	esi

				.if [rbx].INPUT_RECORD.EventType == KEY_EVENT && \
				    [rbx].INPUT_RECORD.KeyEvent.bKeyDown

					movzx edi,[rbx].INPUT_RECORD.KeyEvent.Char
					.break .if edi
				.endif

				add	rbx,SIZE INPUT_RECORD
				dec	esi
			.endw
		.endif
	.endw
	mov	eax,edi
	ret
_getch	ENDP

	END
