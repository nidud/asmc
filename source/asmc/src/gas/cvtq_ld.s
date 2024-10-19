
.intel_syntax noprefix

.global __cvtq_ld


.SECTION .text
	.ALIGN	16

__cvtq_ld:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rax, rcx
	mov	rdi, rdx
	xor	ecx, ecx
	mov	ebx, dword ptr [rdi+0x6]
	mov	edx, dword ptr [rdi+0xA]
	mov	cx, word ptr [rdi+0xE]
	mov	esi, ecx
	and	esi, 0x7FFF
	neg	esi
	rcr	edx, 1
	rcr	ebx, 1
	jnc	$_002
	cmp	ebx, -1
	jnz	$_001
	cmp	edx, -1
	jnz	$_001
	xor	ebx, ebx
	mov	edx, 2147483648
	inc	cx
	jmp	$_002

$_001:	add	ebx, 1
	adc	edx, 0
$_002:	mov	dword ptr [rax], ebx
	mov	dword ptr [rax+0x4], edx
	cmp	rax, rdi
	jnz	$_003
	mov	dword ptr [rax+0x8], ecx
	mov	dword ptr [rax+0xC], 0
	jmp	$_004

$_003:	mov	word ptr [rax+0x8], cx
$_004:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

.att_syntax prefix
