include stdio.inc
include alloc.inc

	.code

	ASSUME	EDX: LPFILE

_getbuf PROC fp:LPFILE
	malloc( _INTIOBUF )
	mov	edx,fp
	.if	!ZERO?
		or	[edx]._flag,_IOMYBUF
		mov	[edx]._bufsiz,_INTIOBUF
	.else
		or	[edx]._flag,_IONBF
		mov	[edx]._bufsiz,4
		lea	eax,[edx]._charbuf
	.endif
	mov	[edx]._ptr,eax
	mov	[edx]._base,eax
	mov	[edx]._cnt,0
	ret
_getbuf ENDP

	END
