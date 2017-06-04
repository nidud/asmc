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

		xor eax,eax
ifdef __DZ__
		mov _diskflag,1
endif
	.else
		osmaperr()
	.endif
	ret

REMOVE	ENDP

	END
