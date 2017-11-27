; GETCWD.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include dos.inc
include conio.inc

	.code

getcwd	PROC _CType PUBLIC buffer:DWORD, maxlen:size_t
	push	si
	push	ds
    ifdef __LFN__
	mov	cx,console
	cmp	_ifsmgr,0
    endif
	lds	si,buffer
	mov	dx,0		; drive number (DL, 0 = default)
	mov	ah,47h
    ifdef __LFN__
	je	@F
	test	cl,CON_NTCMD	; only use LFN if NT Prompt
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
	jmp	getcwd_end
      @@:
	mov	dx,WORD PTR buffer+2
	mov	ax,si
    getcwd_end:
	pop	si
	ret
getcwd	ENDP

	END
