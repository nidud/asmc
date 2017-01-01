include consx.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

rcbprc	PROC rc, wbuf:PVOID, cols
	mov	eax,r8d;cols
	add	eax,eax
	mov	r8,rdx
	movzx	edx,ch;rc.S_RECT.rc_y
	mul	edx
	movzx	edx,cl;rc.S_RECT.rc_x
	add	eax,edx
	add	eax,edx
	add	rax,r8;wbuf
	ret
rcbprc	ENDP

	END
