include direct.inc
include errno.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_wrmdir proc directory:LPWSTR
	mov	eax,[esp+4]
	RemoveDirectoryW( eax )
	test	eax,eax
	jz	error
	xor	eax,eax
toend:
	ret	4
error:
	call	osmaperr
	jmp	toend
_wrmdir endp

	END
