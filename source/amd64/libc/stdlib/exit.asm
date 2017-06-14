include crtl.inc
include stdlib.inc
include winbase.inc

_EXIT	segment para flat PUBLIC 'EXIT'
ExitStart LABEL BYTE
_EXIT	ENDS
_EEND	segment para flat PUBLIC 'EXIT'
ExitEnd LABEL BYTE
_EEND	ENDS

	.code

exit	PROC erlevel
	lea	rcx,ExitStart
	lea	rdx,ExitEnd
	__initialize( rcx, rdx )
	ExitProcess( erlevel )
exit	ENDP

	END
