include conio.inc
include stdio.inc

	.code

_getch	PROC USES ebx edi esi

local	Count:DWORD
local	Event[MAXINPUTRECORDS]:INPUT_RECORD

	xor edi,edi

	.while !edi

		.if GetNumberOfConsoleInputEvents( hStdInput, addr Count )

			lea ebx,Event
			mov ecx,Count
			.if ecx > MAXINPUTRECORDS

				mov ecx,MAXINPUTRECORDS
			.endif
			ReadConsoleInput( hStdInput, ebx, ecx, addr Count )
			mov esi,Count

			.while esi

				.if [ebx].INPUT_RECORD.EventType == KEY_EVENT && \
				    [ebx].INPUT_RECORD.KeyEvent.bKeyDown

					movzx edi,[ebx].INPUT_RECORD.KeyEvent.Char
					.break .if edi
				.endif

				add ebx,SIZE INPUT_RECORD
				dec esi
			.endw
		.endif
	.endw

	mov eax,edi
	ret

_getch	ENDP

	END
