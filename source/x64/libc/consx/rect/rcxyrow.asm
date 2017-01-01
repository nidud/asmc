include consx.inc

	.code

	OPTION	WIN64:0, STACKBASE:rsp

rcxyrow PROC rc, x, y
	mov	al,r8b
	mov	ah,dl
	cmp	ah,cl
	jb	outside
	cmp	al,ch
	jb	outside
	mov	edx,ecx
	shr	edx,16
	add	cl,dl;rc.S_RECT.rc_col
	cmp	ah,cl
	jae	outside
	mov	ah,ch
	add	ch,dh;rc.S_RECT.rc_row
	cmp	al,ch
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
