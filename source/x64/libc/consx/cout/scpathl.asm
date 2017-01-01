include consx.inc
include string.inc

	.code

scpathl PROC USES rsi rdi rbx x, y, l, string:LPSTR
local	lbuf[TIMAXSCRLINE]:BYTE,
	pcx:DWORD

	movzx	rsi,r8b
	mov	al,' '
	lea	rdi,lbuf
	mov	rbx,rdi
	mov	rcx,rsi
	rep	stosb
	mov	rdi,r9

	strlen( rdi )
	cmp	rax,rsi
	jbe	lup

	mov	ecx,[rdi]
	add	rdi,rax
	sub	rdi,rsi
	add	rdi,4
	cmp	ch,':'
	jne	@F
	mov	[rbx],cl
	mov	[rbx+1],ch
	add	rdi,2
	add	rbx,2
@@:	mov	ax,'.\'
	mov	[rbx],al
	mov	[rbx+1],ah
	mov	[rbx+2],ah
	mov	[rbx+3],al
	add	rbx,4
	ALIGN	4
lup:
	mov	al,[rdi]
	test	al,al
	jz	done
	mov	[rbx],al
	inc	rdi
	inc	rbx
	jmp	lup
	ALIGN	4
done:
	movzx	eax,BYTE PTR x
	movzx	r9d,BYTE PTR y
	shl	r9d,16
	mov	r9w,ax
	WriteConsoleOutputCharacter( hStdOutput, addr lbuf, esi, r9d, addr pcx )
	mov	eax,pcx
	ret
scpathl ENDP

	END
