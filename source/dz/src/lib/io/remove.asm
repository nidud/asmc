include io.inc
include winbase.inc

IFDEF	_UNICODE
REMOVE	equ <_wremove>
ELSE
REMOVE	equ <remove>
ENDIF
	.code

REMOVE	PROC file:LPTSTR

	.if DeleteFile( file )

		mov	eax,1
		mov	_diskflag,eax
		dec	eax
	.else
		osmaperr()
	.endif
	ret

REMOVE	ENDP

	END
