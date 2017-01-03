; WVOLINFO.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc

	.code

wvolinfo PROC _CType PUBLIC path:PTR BYTE, buffer:PTR BYTE
	push	ds
	push	di
	stc
	mov	ax,71A0h
	mov	cx,32
	les	di,buffer	; 32 byte 'FAT32','CDFS',...
	lds	dx,path		; 'C:\*.*'
	int	21h
	jc	@F
	xor	ax,ax		; return 0
@@:
	pop	di
	pop	ds
	ret
wvolinfo ENDP

	END
