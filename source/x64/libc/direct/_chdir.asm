include direct.inc
include io.inc
include stdlib.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

_chdir	PROC directory:LPSTR
local	abspath[_MAX_PATH]:BYTE,
	result:QWORD

	SetCurrentDirectory( rcx )
	test	eax,eax
	jz	error
	GetCurrentDirectory( _MAX_PATH, addr abspath )
	test	eax,eax
	jz	error
	mov	ecx,DWORD PTR abspath
	cmp	ch,':'
	jne	success
	mov	eax,003A003Dh
	mov	ah,cl
	cmp	ah,'a'
	jb	@F
	cmp	ah,'z'
	ja	@F
	sub	ah,'a' - 'A'
@@:
	lea	rcx,result
	lea	rdx,abspath
	SetEnvironmentVariable( rcx, rdx )
	test	eax,eax
	jz	error
success:
	xor	eax,eax
toend:
	ret
error:
	call	osmaperr
	jmp	toend
_chdir	ENDP

	END
