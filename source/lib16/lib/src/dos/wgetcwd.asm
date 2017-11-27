; WGETCWD.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

wgetcwd PROC _CType PUBLIC path:DWORD, drive:WORD
	push	si
	push	ds
ifdef __LFN__
	mov	al,_ifsmgr
	test	al,al
endif
	mov	dx,drive
	lds	si,path
	mov	ah,47h
ifdef __LFN__
	jz	wgetcwd_21h
	stc
	mov	ax,7147h
    wgetcwd_21h:
endif
	int	21h
	pop	ds
	jc	wgetcwd_fail
	mov	ax,WORD PTR path
	mov	dx,WORD PTR path+2
    wgetcwd_end:
	pop	si
	ret
    wgetcwd_fail:
	call	osmaperr
	inc	ax
	cwd
	jmp	wgetcwd_end
wgetcwd ENDP

	END
