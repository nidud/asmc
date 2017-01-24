include io.inc
include alloc.inc
include direct.inc
include string.inc

	.code

wlongpath proc path, file

local	convbuf, lpFilePart

	mov	convbuf, alloca( _PAGESIZE_ )

	.if	file

		strfcat( eax, path, file )
	.else

		strcpy( eax, path )
	.endif

	lea	edx,lpFilePart
	.if	GetFullPathName( eax, _PAGESIZE_, eax, edx )

		mov	edx,lpFilePart
	.else

		xor	edx,edx
	.endif
	mov	eax,convbuf
	ret

wlongpath endp

wlongname proc path, file

	strfn( wlongpath( path, file ) )
	ret

wlongname endp

	END
