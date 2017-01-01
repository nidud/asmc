include consx.inc
include string.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

__wcpath PROC USES rsi rdi rbx b:PVOID, l:DWORD, p:LPSTR
	mov	rsi,rcx
	mov	rdi,rdx
	mov	rbx,r8
	strlen( r8 )
	mov	rcx,rax
	mov	rdx,rbx
	mov	rax,rsi
	cmp	ecx,edi
	jbe	toend
	mov	ebx,[rdx]
	add	rdx,rcx
	mov	ecx,edi
	sub	rdx,rcx
	add	rdx,4
	cmp	bh,':'
	jne	@F
	mov	[rax],bl
	mov	[rax+2],bh
	shr	ebx,8
	mov	bl,'.'
	add	rax,4
	add	rdx,2
	sub	rcx,2
	jmp	@set
@@:
	mov	bx,'/.'
@set:
	mov	[rax],bh
	mov	[rax+2],bl
	mov	[rax+4],bl
	mov	[rax+6],bh
	add	rax,8
	sub	rcx,4
toend:
	ret
__wcpath ENDP

	END
