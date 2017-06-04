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

		mov	eax,1
		mov	_diskflag,eax
		dec	eax
	.else
		osmaperr()
	.endif
	ret

RENAME	ENDP

	END
