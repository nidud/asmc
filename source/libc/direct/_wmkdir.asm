include direct.inc
include errno.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_wmkdir proc directory:LPWSTR
	mov	eax,[esp+4]
	CreateDirectoryW( eax, 0 )
	test	eax,eax
	jz	error
	xor	eax,eax
toend:
	ret	4
error:
	call	osmaperr
	jmp	toend
_wmkdir endp

	END
