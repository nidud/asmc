include stdio.inc
IFDEF	_UNICODE
VFPRINTF equ <vfwprintf>
OUTPUT	 equ <_woutput>
ELSE
VFPRINTF equ <vfprintf>
OUTPUT	 equ <_output>
ENDIF
	.code

VFPRINTF PROC file:LPFILE, format:LPTSTR, args:PVOID
	_stbuf( file )
	push	eax
	OUTPUT( file, format, args )
	pop	ecx
	push	eax
	_ftbuf( ecx, file )
	pop	eax
	ret
VFPRINTF ENDP

	END
