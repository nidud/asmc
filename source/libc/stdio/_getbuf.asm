include stdio.inc
include alloc.inc

	.code

	ASSUME	EDX: LPFILE

_getbuf PROC fp:LPFILE
	malloc( _INTIOBUF )
	mov	edx,fp
	.if	!ZERO?
		or	[edx].iob_flag,_IOMYBUF
		mov	[edx].iob_bufsize,_INTIOBUF
	.else
		or	[edx].iob_flag,_IONBF
		mov	[edx].iob_bufsize,4
		lea	eax,[edx].iob_charbuf
	.endif
	mov	[edx].iob_ptr,eax
	mov	[edx].iob_base,eax
	mov	[edx].iob_cnt,0
	ret
_getbuf ENDP

	END
