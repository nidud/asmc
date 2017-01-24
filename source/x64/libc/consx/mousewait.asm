include consx.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

mousewait PROC USES rsi rdi rbx x, y, l
	mov	esi,ecx
	mov	edi,edx
	mov	ebx,ecx
	add	ebx,r8d
	.while	mousep()
		.break .if mousey() != rdi
		.break .if mousex() < rsi
		.break .if eax > ebx
	.endw
	ret
mousewait ENDP

	END
