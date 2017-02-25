include stdio.inc
IFDEF	_UNICODE
PRINTF	equ <wprintf>
OUTPUT	equ <_woutput>
ELSE
PRINTF	equ <printf>
OUTPUT	equ <_output>
ENDIF
	.code

PRINTF	PROC C format:LPTSTR, argptr:VARARG
	_stbuf( addr stdout )
	push	eax
	OUTPUT( addr stdout, format, addr argptr )
	pop	edx
	push	eax
	_ftbuf( edx, addr stdout )
	pop	eax
	ret
PRINTF	ENDP

	END
