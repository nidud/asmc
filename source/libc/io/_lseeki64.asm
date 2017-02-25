include io.inc
include crtl.inc
include winbase.inc

if (WINVER LT 0x0502)

	.data
	externdef kernel32_dll:BYTE
	SetFilePointerEx SetFilePointerEx_T dummy
	.code

dummy	proc _CType private \
		 hFile: HANDLE,
      liDistanceToMove: LARGE_INTEGER,
      lpNewFilePointer: PLARGE_INTEGER,
	  dwMoveMethod: DWORD

	.if SetFilePointer( hFile, DWORD PTR liDistanceToMove, lpNewFilePointer, dwMoveMethod )

		mov	edx,lpNewFilePointer
		mov	DWORD PTR [edx+4],0
	.endif
	ret
dummy	endp

else
	.code
endif

_lseeki64 PROC handle:SINT, offs:QWORD, pos:DWORD

local	lpNewFilePointer:QWORD

	.if	getosfhnd( handle ) != -1

		mov ecx,eax
		lea eax,lpNewFilePointer

		.if !SetFilePointerEx( ecx, offs, eax, pos )

			osmaperr()
			mov edx,eax
		.else
			mov eax,DWORD PTR lpNewFilePointer
			mov edx,DWORD PTR lpNewFilePointer[4]
		.endif
	.else
		mov edx,eax
	.endif
	ret
_lseeki64 ENDP

if (WINVER LT 0x0502)

Install:
	.if GetModuleHandle( addr kernel32_dll )

		.if GetProcAddress( eax, "SetFilePointerEx" )

			mov SetFilePointerEx,eax
		.endif
	.endif
	ret

pragma_init Install,7

endif
	END
