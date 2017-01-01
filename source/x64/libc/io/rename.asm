include io.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

rename	PROC Oldname:LPSTR, Newname:LPSTR
	.if	MoveFile( rcx, rdx )
ifdef __DZ__
		mov	eax,1
		mov	_diskflag,eax
		dec	eax
else
		xor	rax,rax
endif
	.else
		call	osmaperr
	.endif
	ret
rename	ENDP

	END
