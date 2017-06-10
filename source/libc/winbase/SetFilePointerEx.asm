include io.inc
include crtl.inc
include winbase.inc

if (WINVER LT 0x0502)

	.data
	externdef kernel32_dll:BYTE
	SetFilePointerEx SetFilePointerEx_T dummy
	.code

dummy	proc WINAPI private \
		 hFile: HANDLE,
      liDistanceToMove: LARGE_INTEGER,
      lpNewFilePointer: PLARGE_INTEGER,
	  dwMoveMethod: DWORD

	mov eax,DWORD PTR liDistanceToMove
	mov edx,DWORD PTR liDistanceToMove[4]
	mov ecx,lpNewFilePointer
	add ecx,4
	mov [ecx],edx

	.if SetFilePointer(
		hFile,		;; handle of file
		eax,		;; number of bytes to move file pointer
		ecx,		;; pointer to high-order DWORD of distance to move
		dwMoveMethod ) != -1 ;; how to move

		mov edx,lpNewFilePointer
		mov [edx],eax
		mov eax,1
	.else
		dec eax
	.endif
	ret

dummy	endp

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
