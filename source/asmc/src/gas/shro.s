
.intel_syntax noprefix

.global __shro

.SECTION .text
	.ALIGN	16

__shro:
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
$_001:	xor	edx, edx
	xor	eax, eax
	jmp	$_007

$_002:	cmp	r8d, 128
	jnz	$_005
	jmp	$_004

$_003:	mov	rax, rdx
	xor	edx, edx
	sub	ecx, 64
$_004:	cmp	ecx, 64
	ja	$_003
	shrd	rax, rdx, cl
	shr	rdx, cl
	jmp	$_007

$_005:	cmp	eax, -1
	jnz	$_006
	cmp	r8d, 32
	jnz	$_006
	and	eax, eax
$_006:	shr	rax, cl
$_007:	mov	qword ptr [r10], rax
	mov	qword ptr [r10+0x8], rdx
	mov	rax, rbx
	leave
	pop	rbx
	ret

.att_syntax prefix
