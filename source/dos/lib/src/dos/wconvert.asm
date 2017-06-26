; WCONVERT.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include dir.inc
include string.inc

extrn	convbuf:BYTE

	.code

wlongname PROC _CType PUBLIC USES si path:DWORD, file:DWORD
	push	ds
	push	di
	call	convert
	mov	dx,ds
	mov	ax,di
	pop	di
	pop	ds
	ret
wlongname ENDP

wlongpath PROC _CType PUBLIC USES si path:DWORD, file:DWORD
	push	ds
	push	di
	call	convert
	mov	dx,ds
	mov	ax,si
	pop	di
	pop	ds
	ret
wlongpath ENDP

ifdef __l__
argfile equ [bp+6]
argpath equ [bp+6+4]
else
argfile equ [bp+4]
argpath equ [bp+4+4]
endif

convert:
	les	di,argfile
	mov	ax,WORD PTR argpath
	cmp	_ifsmgr,0
	jne	@F
	test	ax,ax
	jnz	@F
	cmp	BYTE PTR es:[di+1],':'
	je	@F
	invoke	fullpath,addr convbuf,0
	invoke	strfcat,addr convbuf,0,argfile
	jmp	done
@@:
	test	ax,ax
	jnz	@F
	test	di,di
	jz	@F
	invoke	strcpy,addr convbuf,argfile
	jmp	done
@@:
	push	ds
	push	offset convbuf
	pushm	argpath
	test	di,di
	jz	@F
	pushm	argfile
	call	strfcat
	jmp	done
@@:
	call	strcpy
done:
	mov	es,dx
	mov	si,ax
	mov	di,ax
ifdef __LFN__
	cmp	_ifsmgr,0
	je	@F
	mov	ax,7160h
	mov	cx,2
	int	21h
@@:
endif
	invoke	strfn,ds::di
	mov	di,ax
	ret

	END
