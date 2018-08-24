include io.inc
include crtl.inc
include winbase.inc

public	hStdInput
public	hStdOutput
public	hStdError
public	OldErrorMode

	.data

_nfile		dd _NFILE_
_osfile		db FH_OPEN or FH_DEVICE or FH_TEXT
		db FH_OPEN or FH_DEVICE or FH_TEXT
		db FH_OPEN or FH_DEVICE or FH_TEXT
		db _NFILE_ - 3 dup(0)
_osfhnd		label HANDLE
hStdInput	HANDLE -1
hStdOutput	HANDLE -1
hStdError	HANDLE -1
		HANDLE _NFILE_ - 3 dup(-1)
OldErrorMode	dd 5

	.code

_ioinit:
	mov hStdInput,	GetStdHandle( STD_INPUT_HANDLE )
	mov hStdOutput, GetStdHandle( STD_OUTPUT_HANDLE )
	mov hStdError,	GetStdHandle( STD_ERROR_HANDLE )

	SetErrorMode( SEM_FAILCRITICALERRORS )
	mov OldErrorMode,eax
	ret

_ioexit:
	push	esi
	mov	esi,3
	.repeat
		.if _osfile[esi] & FH_OPEN

			_close( esi )
		.endif
		inc	esi
	.until	esi == _NFILE_
	pop	esi
	ret

.pragma(init(_ioinit, 1))
.pragma(exit(_ioexit, 2))

	END
