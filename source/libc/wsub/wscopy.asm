include io.inc
include iost.inc
include errno.inc
include wsub.inc

extrn	copy_jump:DWORD

	.code

wscopy_remove PROC		; EAX: file to remove
	ioclose( addr STDO )
	remove( eax )
	mov	eax,-1
	ret
wscopy_remove ENDP

wscopy_open PROC USES esi edi
	mov	esi,eax		; AX: srcfile
	mov	edi,edx		; DX: outfile
	mov	errno,0
	ioopen( addr STDO, edx, M_WRONLY, OO_MEM64K )
	cmp	eax,-1		; -1 == error
	je	toend
	test	eax,eax		;  0 == jump
	jz	skip
	ioopen( addr STDI, esi, M_RDONLY, OO_MEM64K )
	or	STDI.S_IOST.ios_flag,IO_USECRC
	cmp	eax,-1
	je	error
toend:
	ret
skip:
	mov	copy_jump,1
	jmp	toend
error:
	eropen( esi )
	mov	eax,edi
	call	wscopy_remove
	jmp	toend
wscopy_open ENDP

	END
