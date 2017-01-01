include consx.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

rcmemsize PROC rc, dflag
	shr	ecx,16
	movzx	eax,ch
	movzx	r8d,cl
	mov	ecx,eax
	mul	r8b
	add	eax,eax
	.if	dl & _D_SHADE
		add ecx,r8d
		add ecx,r8d
		sub ecx,2
		add eax,ecx
	.endif
	ret
rcmemsize ENDP

	END
