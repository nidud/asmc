; _IFSMGR.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
ifdef __LFN__

	PUBLIC	_ifsmgr

	.data

_ifsmgr db ?	; 71h
	db ?

	.code

Install PROC PRIVATE
	push	di
	sub	sp,32
	mov	di,sp
	mov	ax,ss
	mov	es,ax
	mov	ah,19h
	int	21h
	add	al,'A'
	mov	ah,':'
	mov	[di],ax
	mov	ax,'\'
	mov	[di+2],ax
	mov	dx,di
	mov	cx,32
	mov	ax,71A0h
	stc
	int	21h
	jc	Install_02
	and	bh,40h
	jz	Install_02
	mov	_ifsmgr,71h
	mov	_ifsmgr+1,bh
    Install_02:
	add	sp,32
	pop	di
	ret
Install ENDP

pragma_init Install, 4
endif

	END
