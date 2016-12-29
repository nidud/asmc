include consx.inc

	.code

rcbprcrc PROC USES ebx r1, r2, wbuf:PVOID, cols
	mov	eax,cols
	add	eax,eax
	mov	bx,WORD PTR r1
	add	bx,WORD PTR r2
	mul	bh
	movzx	ebx,bl
	add	eax,ebx
	add	eax,ebx
	add	eax,wbuf
	ret
rcbprcrc ENDP

	END
