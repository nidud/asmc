
.intel_syntax noprefix

.global __mulo


.SECTION .text
	.ALIGN	16

__mulo:
	mov	rax, qword ptr [rcx]
	mov	r10, qword ptr [rcx+0x8]
	mov	r9, qword ptr [rdx+0x8]
	test	r10, r10
	jnz	$_002
	test	r9, r9
	jnz	$_002
	test	r8, r8
	jz	$_001
	mov	qword ptr [r8], r9
	mov	qword ptr [r8+0x8], r9
$_001:	mul	qword ptr [rdx]
	jmp	$_004

$_002:	push	rcx
	mov	r11, qword ptr [rdx]
	mul	r11
	push	rax
	xchg	r11, rdx
	mov	rax, r10
	mul	rdx
	add	r11, rax
	xchg	rdx, rcx
	mov	rax, qword ptr [rdx]
	mul	r9
	add	r11, rax
	adc	rcx, rdx
	mov	edx, 0
	adc	edx, 0
	test	r8, r8
	jz	$_003
	xchg	r9, rdx
	mov	rax, r10
	mul	rdx
	add	rax, rcx
	adc	rdx, r9
	mov	qword ptr [r8], rax
	mov	qword ptr [r8+0x8], rdx
$_003:	pop	rax
	mov	rdx, r11
	pop	rcx
$_004:	mov	qword ptr [rcx], rax
	mov	qword ptr [rcx+0x8], rdx
	mov	rax, rcx
	ret

.att_syntax prefix
