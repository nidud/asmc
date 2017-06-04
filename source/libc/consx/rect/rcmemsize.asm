include consx.inc

	.code

rcmemsize PROC USES ecx edx rc, dflag
	movzx eax,BYTE PTR rc+2
	movzx edx,BYTE PTR rc+3
	mov ecx,eax
	mul dl
	add eax,eax
	.if BYTE PTR dflag & _D_SHADE
		add ecx,edx
		add ecx,edx
		sub ecx,2
		add eax,ecx
	.endif
	ret
rcmemsize ENDP

	END
