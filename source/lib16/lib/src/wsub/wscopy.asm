; WSCOPY.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include io.inc
include iost.inc
include wsub.inc
include errno.inc

extrn	copy_jump:WORD

	.code

wscopy_remove PROC _CType PUBLIC ; AX: offset of file to remove
	push	ds
	push	ax
	invoke	oclose,addr STDO
	call	remove
	mov	ax,-1
	ret
wscopy_remove ENDP

wscopy_open PROC _CType PUBLIC USES si di
	mov	si,ax		; AX: offset srcfile
	mov	di,dx		; DX: offset outfile
	mov	errno,0
	invoke	oopen,ds::dx,M_WRONLY
	cmp	ax,-1		; -1 == error
	je	wscopy_open_end
	test	ax,ax		;  0 == jump
	jz	wscopy_open_jmp
	invoke	oopen,ds::si,M_RDONLY
	cmp	ax,-1
	je	wscopy_open_error
    wscopy_open_end:
	ret
    wscopy_open_jmp:
	mov	copy_jump,1
	jmp	wscopy_open_end
    wscopy_open_error:
	invoke	eropen,ds::si
	mov	ax,di
	call	wscopy_remove
	jmp	wscopy_open_end
wscopy_open ENDP

	END
