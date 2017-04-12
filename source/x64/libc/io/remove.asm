include io.inc
include winbase.inc

	.code

remove	PROC file:LPSTR
	.if	DeleteFile( rcx )
ifdef __DZ__
		mov	eax,1
		mov	_diskflag,eax
		dec	rax
else
		xor	rax,rax
endif
	.else
		osmaperr()
	.endif
	ret
remove	ENDP

	END
