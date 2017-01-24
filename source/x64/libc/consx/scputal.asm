include consx.inc
include string.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

scputal PROC USES rsi rdi rbx rax x, y, l, attrib:PVOID
local	pcx:DWORD,
	lbuf[TIMAXSCRLINE]:WORD

	movzx	ebx,r8b
	xor	eax,eax
	lea	rdi,lbuf
	mov	rsi,r9
@@:
	mov	al,[rsi]
	mov	[rdi],ax
	add	rdi,2
	inc	rsi
	dec	ebx
	jnz	@B

	movzx	eax,cl
	movzx	edi,dl
	cmp	edi,_scrrow
	ja	toend

	shl	edi,16
	add	edi,eax
	movzx	ebx,r8b
	add	eax,ebx
	cmp	eax,_scrcol
	jbe	@F
	sub	eax,ebx
	mov	ebx,_scrcol
	sub	ebx,eax
	jle	toend
@@:
	WriteConsoleOutputAttribute( hStdOutput, addr lbuf, ebx, edi, addr pcx )
toend:
	ret
scputal ENDP

	END
