
.intel_syntax noprefix

.global __divo


.SECTION .text
	.ALIGN	16

__divo:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x18], r8
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rbx, qword ptr [rcx]
	mov	rcx, qword ptr [rcx+0x8]
	mov	r10, qword ptr [rdx]
	mov	r11, qword ptr [rdx+0x8]
	xor	eax, eax
	xor	edx, edx
	test	r10, r10
	jnz	$_001
	test	r11, r11
	jnz	$_001
	xor	rbx, rbx
	xor	rcx, rcx
	jmp	$_009

$_001:	cmp	r11, rcx
	jnz	$_002
	cmp	r10, rbx
$_002:	ja	$_009
	jnz	$_003
	xor	rbx, rbx
	xor	rcx, rcx
	inc	eax
	jmp	$_009

$_003:	mov	r8d, 4294967295
$_004:	inc	r8d
	shl	r10, 1
	rcl	r11, 1
	jc	$_005
	cmp	r11, rcx
	ja	$_005
	jc	$_004
	cmp	r10, rbx
	jc	$_004
	jz	$_004
$_005:	rcr	r11, 1
	rcr	r10, 1
	sub	rbx, r10
	sbb	rcx, r11
	cmc
	jc	$_008
$_006:	add	rax, rax
	adc	rdx, rdx
	dec	r8d
	jns	$_007
	add	rbx, r10
	adc	rcx, r11
	jmp	$_009

$_007:	shr	r11, 1
	rcr	r10, 1
	add	rbx, r10
	adc	rcx, r11
	jnc	$_006
$_008:	adc	rax, rax
	adc	rdx, rdx
	dec	r8d
	jns	$_005
$_009:	mov	r10, qword ptr [rbp+0x28]
	test	r10, r10
	jz	$_010
	mov	qword ptr [r10], rbx
	mov	qword ptr [r10+0x8], rcx
$_010:	mov	r10, rax
	mov	rax, qword ptr [rbp+0x18]
	mov	qword ptr [rax], r10
	mov	qword ptr [rax+0x8], rdx
	leave
	pop	rbx
	ret

.att_syntax prefix
