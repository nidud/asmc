include crtl.inc
include stdlib.inc

_EXIT	segment para flat PUBLIC 'EXIT'
ExitStart LABEL BYTE
_EXIT	ENDS
_EEND	segment para flat PUBLIC 'EXIT'
ExitEnd LABEL BYTE
_EEND	ENDS

	.code

	OPTION	WIN64:2, STACKBASE:rsp

exit	PROC erlevel
	lea	rcx,ExitStart
	lea	rdx,ExitEnd
	__initialize( rcx, rdx )
	ExitProcess( erlevel )
exit	ENDP

	END
