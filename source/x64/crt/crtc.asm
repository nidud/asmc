; CRTC.ASM--
;
; Startup module for C - main(argc, argv, environ)
;
include version.inc

externdef	_argc:DWORD
externdef	_argv:QWORD
externdef	_environ:QWORD

main		proto :dword, :qword, :qword
exit		proto :qword
__initialize	proto :qword, :qword

IFDEF DEBUG
includelib	libd.lib
ELSE
includelib	libc.lib
ENDIF
includelib	user32.lib
includelib	kernel32.lib

_INIT		SEGMENT PARA FLAT PUBLIC 'INIT'
InitStart	LABEL BYTE
_INIT		ENDS
_IEND		SEGMENT PARA FLAT PUBLIC 'INIT'
InitEnd		LABEL BYTE
_IEND		ENDS

	.code

	DD 495A440Ah
	DD 564A4A50h
	DB VERSSTR

	OPTION WIN64:2
	OPTION PROLOGUE:NONE, EPILOGUE:NONE

mainCRTStartup PROC

	sub	rsp,0x20

	lea	rcx,InitStart
	lea	rdx,InitEnd
	__initialize( rcx, rdx )

	exit( main( _argc, _argv, _environ ) )
	ret

mainCRTStartup ENDP

	END	mainCRTStartup
