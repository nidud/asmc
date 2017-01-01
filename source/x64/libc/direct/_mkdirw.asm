include io.inc
include direct.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_mkdirw proc directory:LPWSTR

	CreateDirectoryW( rcx, 0 )
	test	eax,eax
	jz	error
	xor	eax,eax
ifdef __DZ__
	mov	_diskflag,1
endif
toend:
	ret
error:
	call	osmaperr
	jmp	toend
_mkdirw endp

	END
