include io.inc
include errno.inc

	.code

_chsize PROC USES edi esi handle:SINT, new_size

  local zbuf[512]:byte, offs, count

	_lseek( handle, 0, SEEK_CUR )
	mov	offs,eax	; save current offset
	cmp	eax,-1
	je	toend		; seek to end of file
	_lseek( handle, 0, SEEK_END )
	cmp	eax,-1
	je	toend
	cmp	eax,new_size
	ja	truncate
	jb	@F
	jmp	seekback	; All done..
@@:
	push	eax
	lea	edi,zbuf
	sub	eax,eax
	mov	ecx,512/4
	rep	stosd
	pop	eax
	mov	edi,new_size
	sub	edi,eax
write_loop:
	mov	count,512
	cmp	edi,count
	jae	write_chunk
	mov	count,edi
	test	edi,edi
	jz	seekback
write_chunk:
	sub	edi,count
	oswrite( handle, addr zbuf, count )
	cmp	eax,count
	je	write_loop
	mov	errno,ERROR_DISK_FULL
	mov	eax,-1
	jmp	toend
truncate:
	_lseek( handle, new_size, SEEK_SET )
	cmp	eax,-1
	je	toend
	;
	; Write zero byte at current file position
	;
	oswrite( handle, addr zbuf, 0 )
seekback:
	_lseek( handle, offs, SEEK_SET )
	cmp	eax,-1
	je	toend
	xor	eax,eax
toend:
	ret
_chsize ENDP

	END
