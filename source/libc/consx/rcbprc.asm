include consx.inc

	.code

rcbprc	PROC USES ebx edx rc, wbuf:PVOID, cols
	mov	eax,cols
	add	eax,eax
	movzx	ebx,rc.S_RECT.rc_y
	mul	ebx
	movzx	ebx,rc.S_RECT.rc_x
	add	eax,ebx
	add	eax,ebx
	add	eax,wbuf
	ret
rcbprc	ENDP

	END
