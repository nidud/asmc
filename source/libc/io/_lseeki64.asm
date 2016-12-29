include io.inc
include errno.inc
include stdlib.inc
include crtl.inc

ifndef __WINXP__

	.data

externdef kernel32_dll:BYTE
pSetFilePointerEx dd 0

endif
	.code

_lseeki64 PROC handle:SINT, offs:QWORD, pos:DWORD

	local	lpNewFilePointer:QWORD

	.if	getosfhnd( handle ) != -1

		mov	ecx,eax
		lea	eax,lpNewFilePointer
ifdef __WINXP__
		.if	!SetFilePointerEx( ecx, offs, eax, pos )
else
		.if	pSetFilePointerEx
			push	pos
			push	eax
			push	DWORD PTR offs[4]
			push	DWORD PTR offs
			push	ecx
			call	pSetFilePointerEx
		.else
			SetFilePointer( ecx, DWORD PTR offs, eax, pos )
			mov	DWORD PTR lpNewFilePointer[4],0
		.endif
		.if	!eax
endif
			call	osmaperr
			mov	edx,eax
		.else
			mov	eax,DWORD PTR lpNewFilePointer
			mov	edx,DWORD PTR lpNewFilePointer[4]
		.endif
	.else
		mov	edx,eax
	.endif
	ret
_lseeki64 ENDP

ifndef __WINXP__

Install:
	.if	GetModuleHandle( addr kernel32_dll )
		.if	GetProcAddress( eax, "SetFilePointerEx" )
			mov pSetFilePointerEx,eax
		.endif
	.endif
	ret

pragma_init Install,7

endif
	END
