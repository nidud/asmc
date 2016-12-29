include crtl.inc
include stdlib.inc

_EXIT	SEGMENT DWORD FLAT PUBLIC 'EXIT'
_EXIT	ENDS
_EEND	SEGMENT DWORD FLAT PUBLIC 'EXIT'
_EEND	ENDS

	.code

exit	PROC erlevel:SIZE_T
	mov	edx,offset _EXIT
	mov	eax,offset _EEND
	__initialize( edx, eax )
	ExitProcess( erlevel )
exit	ENDP

	END
