include consx.inc

	.code

rcxyrow PROC USES edx rc, x, y
	mov	al,BYTE PTR y
	mov	ah,BYTE PTR x
	mov	dl,rc.S_RECT.rc_x
	mov	dh,rc.S_RECT.rc_y
	cmp	ah,dl
	jb	outside
	cmp	al,dh
	jb	outside
	add	dl,rc.S_RECT.rc_col
	cmp	ah,dl
	jae	outside
	mov	ah,dh
	add	dh,rc.S_RECT.rc_row
	cmp	al,dh
	jae	outside
	sub	al,ah
	inc	al
	movzx	eax,al
toend:
	ret
outside:
	xor	eax,eax
	jmp	toend
rcxyrow ENDP

	END
