; GETFTIME.ASM--
; Copyright (C) 2015 Doszip Developers
;
; int getftime(int handle, struct ftime *);
;
include dos.inc
include io.inc

	.code

getftime PROC _CType PUBLIC handle:size_t, ftime:PTR S_FTIME
	push	bx
	push	cx
	mov	bx,handle
	mov	ax,5700h
	int	21h
	jc	error
	mov	ax,cx
	les	bx,ftime
	stom	es:[bx]
	xor	ax,ax
    toend:
	pop	cx
	pop	bx
	ret
    error:
	call	osmaperr
	jmp	toend
getftime ENDP

	END
