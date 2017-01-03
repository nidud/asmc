; OSOPEN.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc
include dos.inc
include errno.inc
include conio.inc

	.code

osopen	PROC _CType PUBLIC fname:DWORD, attrib:size_t, mode:size_t, action:size_t
	push	si
	push	di
	push	ds
ifdef __LFN__
	stc
	cmp	_ifsmgr,0
	mov	ax,716Ch
endif
	lds	si,fname
	mov	bx,mode
	mov	cx,attrib
	mov	dx,action
ifdef __LFN__
	jnz	osopen_21h
endif
	mov	ax,6C00h	; DOS 4.0+ - EXTENDED OPEN/CREATE
	test	BYTE PTR ss:console,CON_DOSIO
	jz	osopen_21h
	mov	ah,3Dh		; DOS 2+ - OPEN EXISTING FILE
	mov	al,bl
	test	dl,A_TRUNC or A_CREATE
	xchg	dx,si
	jz	osopen_21h
	dec	ah		; DOS 2+ - CREATE OR TRUNCATE FILE
	test	si,A_TRUNC
	jnz	osopen_21h
	mov	ah,43h		; Create a new file - test if exist
	int	21h
	jnc	osopen_error_exist
	mov	ah,3Ch
	mov	cx,attrib
	cmp	al,2		; file not found
	je	osopen_21h
	mov	si,dx		; Windows for Workgroups bug
	mov	dx,action
	mov	ax,6C00h
    osopen_21h:
	int	21h
	pop	ds
	jc	osopen_error
	cmp	ax,_nfile
	jnb	osopen_error_ebadf
	mov	bx,ax
	or	BYTE PTR [bx+_osfile],FH_OPEN
    osopen_end:
	pop	di
	pop	si
	ret
    osopen_error_ebadf:
	push	ax
	sub	ax,ax
	mov	doserrno,ax	; no OS error
	mov	al,EBADF
	mov	errno,ax
	call	close
	jmp	osopen_user_error
    osopen_error_exist:
	pop	ds
	mov	ax,50h		; file exists
    osopen_error:
	call	osmaperr
    osopen_user_error:
	mov	ax,-1
	jmp	osopen_end
osopen	ENDP

	END
