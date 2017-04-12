include io.inc
include direct.inc
include winbase.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_rmdirw proc directory:LPWSTR

	RemoveDirectoryW( rcx )
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
_rmdirw endp

	END
