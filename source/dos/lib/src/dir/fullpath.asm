; FULLPATH.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include dos.inc
include conio.inc

	.code

fullpath PROC _CType PUBLIC buffer:DWORD, disk:size_t
	push	si
	push	ds
    ifdef __LFNx__
	mov	cx,console
	cmp	_ifsmgr,0
    endif
	lds	si,buffer
	add	si,3
	mov	dx,disk		; drive number (DL, 0 = default)
	mov	ah,47h
    ifdef __LFNx__
	je	@F
	test	cl,CON_NTCMD
	jz	@F
	stc
	mov	ax,7147h
      @@:
    endif
	int	21h
	pop	ds
	jnc	@F
	call	osmaperr
	inc	ax
	cwd
	jmp	fullpath_end
      @@:
	mov	ax,disk
	test	ax,ax
	jz	fullpath_get
	add	al,'@'
	jmp	fullpath_drv
    fullpath_get:
	call	getdrv
	add	al,'A'
    fullpath_drv:
	les	si,buffer
	mov	ah,':'
	mov	es:[si],ax
	mov	al,'\'
	mov	es:[si+2],al
	mov	dx,es
	mov	ax,si
    fullpath_end:
	pop	si
	ret
fullpath ENDP

	END

