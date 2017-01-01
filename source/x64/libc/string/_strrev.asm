include string.inc

	.code

	OPTION	WIN64:0, STACKBASE:rsp

_strrev PROC USES rsi rdi string:LPSTR
	mov	rsi,rcx
	mov	r9,rcx
	mov	rdi,rsi
	xor	rax,rax
	mov	rcx,-1
	repnz	scasb
	cmp	rcx,-2
	je	toend
	sub	rdi,2
	xchg	rsi,rdi
	cmp	rdi,rsi
	jae	toend
@@:
	mov	al,[rdi]
	movsb
	mov	[rsi-1],al
	sub	rsi,2
	cmp	rdi,rsi
	jb	@B
toend:
	mov	rax,r9
	ret
_strrev ENDP

	END
