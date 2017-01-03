; WCUNZIP.ASM--
; Copyright (C) 2015 Doszip Developers
include conio.inc

rsunzipch PROTO
rsunzipat PROTO

	.code

wcunzip PROC _CType PUBLIC USES si di  dest:DWORD, src:DWORD, wcount:size_t
	push	ds
	les	di,dest
	inc	di
	lds	si,src
	cld?
	mov	ax,wcount
	and	wcount,07FFh
	and	ax,8000h
	mov	cx,wcount
	jz	wcunzip_00
	call	rsunzipat
	jmp	wcunzip_01
    wcunzip_00:
	call	rsunzipch
    wcunzip_01:
	mov	di,WORD PTR dest
	mov	cx,wcount
	call	rsunzipch
	pop	ds
	ret
wcunzip ENDP

	END
