
.intel_syntax noprefix

.global __shlo

.SECTION .text
	.ALIGN	16

__shlo:
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rbx, rcx
	mov	r10, rcx
	mov	ecx, edx
	mov	rax, qword ptr [r10]
	mov	rdx, qword ptr [r10+0x8]
	cmp	ecx, 128
	jnc	$_001
	cmp	ecx, 64
	jc	$_002
	cmp	r8d, 128
	jnc	$_002
$_001:	xor	eax, eax
	xor	edx, edx
	jmp	$_006

$_002:	cmp	r8d, 128
	jnz	$_005
	jmp	$_004

$_003:	mov	rdx, rax
	xor	eax, eax
	sub	ecx, 64
$_004:	cmp	ecx, 64
	jnc	$_003
	shld	rdx, rax, cl
	shl	rax, cl
	jmp	$_006

$_005:	shl	rax, cl
$_006:	mov	qword ptr [r10], rax
	mov	qword ptr [r10+0x8], rdx
	mov	rax, rbx
	leave
	pop	rbx
	ret

.att_syntax prefix
