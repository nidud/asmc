; RCXYROW.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

rcxyrow PROC _CType PUBLIC rc:DWORD, x:size_t, y:size_t
	push	dx
	mov	al,BYTE PTR y
	mov	ah,BYTE PTR x
	mov	dl,rc.S_RECT.rc_x
	mov	dh,rc.S_RECT.rc_y
	cmp	ah,dl
	jb	rcxyrow_01
	cmp	al,dh
	jb	rcxyrow_01
	add	dl,rc.S_RECT.rc_col
	cmp	ah,dl
	jae	rcxyrow_01
	mov	ah,dh
	add	dh,rc.S_RECT.rc_row
	cmp	al,dh
	jae	rcxyrow_01
	sub	al,ah
	inc	al
	mov	ah,0
    rcxyrow_00:
	pop	dx
	ret
    rcxyrow_01:
	sub	ax,ax
	jmp	rcxyrow_00
rcxyrow ENDP

	END
