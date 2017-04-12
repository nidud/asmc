include io.inc
include winbase.inc

	.code

_filelength PROC handle:SINT

local	FileSize:QWORD

	lea rax,_osfhnd
	mov rcx,[rax+rcx*8]
	.if GetFileSizeEx(rcx, addr FileSize)

		mov rax,FileSize
	.else
		osmaperr()
		xor rax,rax
	.endif
	ret
_filelength ENDP

	END
