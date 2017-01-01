include io.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

_filelength PROC handle:SINT

	local	FileSize:QWORD

	lea	rax,_osfhnd
	mov	rcx,[rax+rcx*8]
	.if	GetFileSize( rcx, addr FileSize )
		mov	rax,FileSize
	.else
		call	osmaperr
		xor	rax,rax
	.endif
	ret
_filelength ENDP

	END
