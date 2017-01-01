include consx.inc
include stdio.inc

	.code

	ASSUME	rbx:PTR INPUT_RECORD

_kbhit	PROC USES rbx rdi rsi

  local Count:QWORD
  local Event[MAXINPUTRECORDS]:INPUT_RECORD

	xor edi,edi
	lea rbx,Event

	.if GetNumberOfConsoleInputEvents( hStdInput, addr Count )

		mov r8,Count
		.if r8 > MAXINPUTRECORDS
			mov r8,MAXINPUTRECORDS
		.endif

		PeekConsoleInput( hStdInput, rbx, r8d, addr Count )
		mov rsi,Count

		.while	esi

			.if [rbx].INPUT_RECORD.EventType == KEY_EVENT && \
			    [rbx].INPUT_RECORD.KeyEvent.bKeyDown

				movzx edi,[rbx].INPUT_RECORD.KeyEvent.Char
				.break .if edi
			.endif

			ReadConsoleInput( hStdInput, rbx, 1, addr Count )
			add rbx,SIZE INPUT_RECORD
			dec esi
		.endw
	.endif
	mov eax,edi
	ret
_kbhit	ENDP

	END
