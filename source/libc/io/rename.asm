include io.inc
include winbase.inc
IFDEF	_UNICODE
RENAME	equ <_wrename>
ELSE
RENAME	equ <rename>
ENDIF
	.code

RENAME	PROC Oldname:LPTSTR, Newname:LPTSTR

	.if MoveFile( Oldname, Newname )

		xor eax,eax
ifdef __DZ__
		mov _diskflag,1
endif
	.else
		osmaperr()
	.endif
	ret

RENAME	ENDP

	END
