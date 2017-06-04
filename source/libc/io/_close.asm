include io.inc
include errno.inc
include winbase.inc

	.code

close	PROC handle:SINT
close	ENDP

_close	PROC handle:SINT
	push	eax
	mov	eax,handle
	cmp	eax,3
	jb	argerr
	cmp	eax,_nfile
	jae	argerr
	test	_osfile[eax],FH_OPEN
	jz	argerr
	mov	_osfile[eax],0
	mov	eax,_osfhnd[eax*4]
	CloseHandle( eax )
	test	eax,eax
	jz	error
	xor	eax,eax
toend:
	pop	edx
	ret
error:
	call	osmaperr
	jmp	toend
argerr:
	mov	errno,EBADF
	mov	oserrno,0
	xor	eax,eax
	jmp	toend
_close	ENDP

	END
