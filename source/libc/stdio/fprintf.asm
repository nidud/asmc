include stdio.inc
IFDEF	_UNICODE
FPRINTF equ <fwprintf>
OUTPUT	equ <_woutput>
ELSE
FPRINTF equ <fprintf>
OUTPUT	equ <_output>
ENDIF
	.code

FPRINTF PROC C file:LPFILE, format:LPTSTR, argptr:VARARG
	_stbuf( file )
	push	eax
	OUTPUT( file, format, addr argptr )
	pop	edx
	push	eax
	_ftbuf( edx, file )
	pop	eax
	ret
FPRINTF ENDP

	END
