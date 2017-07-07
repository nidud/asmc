include io.inc
include errno.inc
include winbase.inc

	.code

	option	win64:rsp nosave

oswrite PROC USES rbx h:SINT, b:PVOID, z:SIZE_T
local	lpNumberOfBytesWritten:dword

	mov ebx,r8d
	lea rax,_osfhnd
	mov rcx,[rax+rcx*8]
	.if WriteFile(rcx, rdx, r8d, &lpNumberOfBytesWritten, 0)

		mov eax,lpNumberOfBytesWritten
		.if eax != ebx
		    mov errno,ERROR_DISK_FULL
		    xor eax,eax
		.endif
	.else
	    osmaperr()
	    xor eax,eax
	.endif

	ret
oswrite ENDP

	END
