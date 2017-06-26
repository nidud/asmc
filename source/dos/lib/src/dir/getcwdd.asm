; GETCWDD.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include dos.inc
include conio.inc

	.code

getcwdd PROC _CType PUBLIC path:DWORD, disk:WORD
	push	si
	push	ds
  ifdef __LFN__
	mov	cx,console
	mov	al,_ifsmgr
	test	al,al
  endif
	lds	si,path
	mov	dx,disk ; drive number (DL, 0 = default)
	mov	ah,47h
  ifdef __LFN__
	jz	wgetcwd_21h
	test	cl,CON_NTCMD
	jz	wgetcwd_21h
	stc
	xchg	al,ah
    wgetcwd_21h:
  endif
	int	21h
	pop	ds
	jc	getcwdd_err
	lodm	path
    getcwdd_end:
	pop	si
	ret
    getcwdd_err:
	call	osmaperr
	inc	ax
	cwd
	jmp	getcwdd_end
getcwdd ENDP

	END
