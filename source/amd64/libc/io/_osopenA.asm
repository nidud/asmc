include io.inc
include errno.inc
include conio.inc

	.code

_osopenA PROC USES rsi rdi rbx lpFileName:LPSTR, dwAccess:DWORD, dwShareMode:DWORD,
	lpSecurity:PVOID, dwCreation:DWORD, dwAttributes:DWORD
local	NameW[2048]:SBYTE

	xor eax,eax
	lea rsi,_osfile
	.while BYTE PTR [rsi+rax] & FH_OPEN
		inc eax
		.if eax == _nfile
			xor eax,eax
			mov oserrno,eax ; no OS error
			mov errno,EBADF
			dec rax
			jmp toend
		.endif
	.endw
	mov rbx,rax
	CreateFileA(lpFileName, dwAccess, dwShareMode, lpSecurity, dwCreation, dwAttributes, 0)
	mov rdx,rax
	inc rax
	jz  error
done:
	mov rax,rbx
	lea rsi,_osfile
	or  BYTE PTR [rsi+rax],FH_OPEN
	lea rsi,_osfhnd
	mov [rsi+rax*8],rdx
toend:
	ret
error:
	call osmaperr
	cmp edx,ERROR_FILENAME_EXCED_RANGE
	jne toend

	lea rdx,NameW
	mov rdi,rdx
	mov rsi,lpFileName
	mov ax,'\'
	stosw
	stosw
	mov al,'?'
	stosw
	mov al,'\'
	stosw
	.repeat
	    lodsb
	    stosw
	.until !al
	CreateFileW(rdx, dwAccess, dwShareMode, lpSecurity, dwCreation, dwAttributes, 0)
	mov rdx,rax
	inc rax
	jnz done
	call osmaperr
	jmp toend
_osopenA ENDP

	END
