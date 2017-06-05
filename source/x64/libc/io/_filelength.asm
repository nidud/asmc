include io.inc
include winbase.inc

	.code

filelength PROC handle:SINT

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
filelength ENDP

	END
