
.intel_syntax noprefix

.global _fltmul


.SECTION .text
	.ALIGN	16

_fltmul:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	r10, rcx
	mov	rbx, qword ptr [rdx]
	mov	rdi, qword ptr [rdx+0x8]
	mov	si, word ptr [rdx+0x10]
	shl	esi, 16
	mov	rax, qword ptr [rcx]
	mov	rdx, qword ptr [rcx+0x8]
	mov	si, word ptr [rcx+0x10]
	add	si, 1
	jc	$_014
	jo	$_014
	add	esi, 65535
	jc	$_017
	jo	$_017
	sub	esi, 65536
	mov	rcx, rax
	or	rcx, rdx
	je	$_006
$_001:	mov	rcx, rbx
	or	rcx, rdi
	je	$_008
$_002:	mov	ecx, esi
	rol	ecx, 16
	sar	ecx, 16
	sar	esi, 16
	and	ecx, 0x80007FFF
	and	esi, 0x80007FFF
	add	esi, ecx
	sub	si, 16382
	jc	$_003
	cmp	si, 32767
	ja	$_010
$_003:	cmp	si, -65
	jl	$_012
	mov	rcx, rbx
	mov	r11, rdi
	mov	r8, rax
	mov	r9, rdi
	mov	rdi, rdx
	mul	rcx
	mov	rbx, rdx
	mov	rax, rdi
	mul	r11
	mov	r11, rdx
	xchg	rax, rcx
	mov	rdx, rdi
	mul	rdx
	add	rbx, rax
	adc	rcx, rdx
	adc	r11, 0
	mov	rax, r8
	mov	rdx, r9
	mul	rdx
	add	rbx, rax
	adc	rcx, rdx
	adc	r11, 0
	mov	rax, rcx
	mov	rdx, r11
	test	rdx, rdx
	js	$_004
	add	rbx, rbx
	adc	rax, rax
	adc	rdx, rdx
	dec	si
$_004:	add	rbx, rbx
	adc	rax, 0
	adc	rdx, 0
	test	si, si
	jle	$_012
	add	esi, esi
	rcr	si, 1
$_005:	mov	qword ptr [r10], rax
	mov	qword ptr [r10+0x8], rdx
	mov	word ptr [r10+0x10], si
	mov	rax, r10
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_006:	add	si, si
	jz	$_007
	rcr	si, 1
	jmp	$_001

$_007:	rcr	si, 1
	test	esi, 0x80008000
	jz	$_012
	mov	esi, 32768
	jmp	$_005

$_008:	test	esi, 0x7FFF0000
	jne	$_002
	test	esi, 0x80008000
	jz	$_012
	mov	esi, 2147483648
	jmp	$_013

$_009:	mov	esi, 65535
	mov	edx, 1
	rol	rdx, 1
	xor	eax, eax
	jmp	$_005

$_010:	mov	esi, 32767
$_011:	xor	eax, eax
	xor	edx, edx
	jmp	$_005

$_012:	xor	esi, esi
	jmp	$_011

$_013:	mov	rax, rbx
	mov	rdx, rdi
	shr	esi, 16
	jmp	$_005

$_014:	dec	si
	add	esi, 65536
	jc	$_015
	jo	$_015
	jns	$_005
	test	rax, rax
	jne	$_005
	test	rdx, rdx
	jne	$_005
	xor	esi, 0x8000
	jmp	$_005

$_015:	sub	esi, 65536
	mov	rcx, rax
	or	rcx, rdx
	or	rcx, rbx
	or	rcx, rdi
	jnz	$_016
	or	esi, 0xFFFFFFFF
	jmp	$_009

$_016:	cmp	rdx, rdi
	jc	$_013
	ja	$_005
	cmp	rax, rbx
	jbe	$_013
	jmp	$_005

$_017:
	sub	esi, 65536
	test	rbx, rbx
	jnz	$_013
	test	rdi, rdi
	jnz	$_013
	mov	ecx, esi
	shl	ecx, 16
	xor	esi, ecx
	and	esi, 0x80000000
	jmp	$_013

.att_syntax prefix
