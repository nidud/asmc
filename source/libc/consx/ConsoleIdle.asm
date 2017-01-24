include consx.inc
include io.inc
include stdlib.inc

	.code

ConsoleIdle PROC

	.if console & CON_SLEEP

		Sleep( CON_SLEEP_TIME )

ifdef DEBUG
		mov eax,hCurrentWindow
else
		.if pGetForegroundWindow() != hCurrentWindow

			mov eax,keyshift
			and DWORD PTR [eax],not 0x00FF030F

			.while	pGetForegroundWindow() != hCurrentWindow

				Sleep( CON_SLEEP_TIME * 10 )
				.break .if tupdate()
			.endw
		.endif
endif
	.endif

	call tupdate
	test eax,eax
	ret

ConsoleIdle ENDP

	END
