include io.inc
include crtl.inc

public	hStdInput
public	hStdOutput
public	hStdError

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

	OPTION	WIN64:3, STACKBASE:rsp

_ioinit proc
	GetStdHandle( STD_INPUT_HANDLE )
	mov	hStdInput,rax
	GetStdHandle( STD_OUTPUT_HANDLE )
	mov	hStdOutput,rax
	GetStdHandle( STD_ERROR_HANDLE )
	mov	hStdError,rax
	SetErrorMode( SEM_FAILCRITICALERRORS )
	mov	OldErrorMode,eax
	ret
_ioinit endp

_ioexit proc uses rsi rdi
	mov	esi,3
	lea	rdi,_osfile
	.while	esi < _NFILE_
		.if	BYTE PTR [rdi+rsi] & FH_OPEN
			_close( esi )
		.endif
		inc	esi
	.endw
	ret
_ioexit endp

pragma_init _ioinit, 1
pragma_exit _ioexit, 2

	END
