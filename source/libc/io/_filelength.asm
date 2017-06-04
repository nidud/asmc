include io.inc
include errno.inc
include winbase.inc

	.code

filelength PROC handle:SINT
filelength ENDP

_filelength PROC handle:SINT

local	lpFileSize:qword

	mov eax,handle
	mov edx,_osfhnd[eax*4]

	.if !GetFileSizeEx( edx, addr lpFileSize )

		osmaperr()
	.else
		mov edx,dword ptr lpFileSize[4]
		mov eax,dword ptr lpFileSize
	.endif
	ret

_filelength ENDP

	END
