include io.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

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
		call	osmaperr
	.endif
	ret
remove	ENDP

	END
