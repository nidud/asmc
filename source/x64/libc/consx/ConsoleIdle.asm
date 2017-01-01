include consx.inc
include io.inc
include stdlib.inc

	.code

ConsoleIdle PROC

	.if	console & CON_SLEEP

		Sleep( CON_SLEEP_TIME )

ifdef DEBUG
		mov	rax,hCurrentWindow
else
		.if	GetForegroundWindow() != hCurrentWindow

			mov	rax,keyshift
			and	DWORD PTR [rax],not 0x00FF030F
			.while	GetForegroundWindow() != hCurrentWindow

				Sleep( CON_SLEEP_TIME * 10 )
				.break .if tupdate()
			.endw
		.endif
endif
	.endif

	call	tupdate
	test	eax,eax
	ret
ConsoleIdle ENDP

	END
