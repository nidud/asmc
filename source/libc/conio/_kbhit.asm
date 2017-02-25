include conio.inc

	.code

	ASSUME	ebx:PTR INPUT_RECORD

_kbhit	PROC USES ebx edi esi

  local Count:DWORD
  local Event[MAXINPUTRECORDS]:INPUT_RECORD

	xor edi,edi
	lea ebx,Event

	.if GetNumberOfConsoleInputEvents( hStdInput, addr Count )

		mov ecx,Count
		.if ecx > MAXINPUTRECORDS

			mov ecx,MAXINPUTRECORDS
		.endif

		PeekConsoleInput( hStdInput, ebx, ecx, addr Count )

		mov	esi,Count
		.while	esi

			.if [ebx].INPUT_RECORD.EventType == KEY_EVENT && \
			    [ebx].INPUT_RECORD.KeyEvent.bKeyDown

				movzx edi,[ebx].INPUT_RECORD.KeyEvent.AsciiChar
				.break .if edi
			.endif

			ReadConsoleInput( hStdInput, ebx, 1, addr Count )

			add ebx,SIZE INPUT_RECORD
			dec esi
		.endw
	.endif

	mov	eax,edi
	ret

_kbhit	ENDP

	END
