
.intel_syntax noprefix

.global _fltdiv


.SECTION .text
	.ALIGN	16

_fltdiv:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	r12
	push	r13
	push	rbp
	mov	rbp, rsp
	mov	rbx, qword ptr [rdx]
	mov	rdi, qword ptr [rdx+0x8]
	mov	si, word ptr [rdx+0x10]
	shl	esi, 16
	mov	rax, qword ptr [rcx]
	mov	rdx, qword ptr [rcx+0x8]
	mov	si, word ptr [rcx+0x10]
	add	si, 1
	jc	$_023
	jo	$_023
	add	esi, 65535
	jc	$_025
	jo	$_025
	sub	esi, 65536
	mov	rcx, rbx
	or	rcx, rdi
	je	$_016
$_001:	mov	rcx, rax
	or	rcx, rdx
	je	$_014
$_002:	mov	ecx, esi
	rol	ecx, 16
	sar	ecx, 16
	sar	esi, 16
	and	ecx, 0x80007FFF
	and	esi, 0x80007FFF
	rol	ecx, 16
	rol	esi, 16
	add	cx, si
	rol	ecx, 16
	rol	esi, 16
	test	cx, cx
	je	$_012
$_003:	test	si, si
	je	$_013
$_004:	sub	cx, si
	add	cx, 16383
	js	$_005
	cmp	cx, 32767
	ja	$_019
$_005:	cmp	cx, -65
	jl	$_018
	mov	r13, rcx
	mov	r12, rbp
	shrd	rax, rdx, 14
	shr	rdx, 14
	shrd	rbx, rdi, 14
	shr	rdi, 14
	mov	ecx, 115
	mov	rbp, rdi
	mov	r10, rax
	mov	r11, rdx
	xor	eax, eax
	xor	edx, edx
	xor	r8d, r8d
	xor	r9d, r9d
	xor	edi, edi
	xor	esi, esi
	add	rbx, rbx
	adc	rbp, rbp
$_006:	shr	rbp, 1
	rcr	rbx, 1
	rcr	r9, 1
	rcr	r8, 1
	sub	rdi, r8
	sbb	rsi, r9
	sbb	r10, rbx
	sbb	r11, rbp
	cmc
	jc	$_008
$_007:	add	rax, rax
	adc	rdx, rdx
	dec	ecx
	jz	$_009
	shr	rbp, 1
	rcr	rbx, 1
	rcr	r9, 1
	rcr	r8, 1
	add	rdi, r8
	adc	rsi, r9
	adc	r10, rbx
	adc	r11, rbp
	jnc	$_007
$_008:	adc	rax, rax
	adc	rdx, rdx
	dec	ecx
	jnz	$_006
$_009:	mov	rsi, r13
	mov	rbp, r12
	dec	si
	bt	rax, 0
	adc	rax, 0
	adc	rdx, 0
	bt	rdx, 50
	jnc	$_010
	rcr	rdx, 1
	rcr	rax, 1
	add	esi, 1
$_010:	shld	rdx, rax, 14
	shl	rax, 14
	test	si, si
	jle	$_021
	add	esi, esi
	rcr	si, 1
$_011:	mov	rcx, qword ptr [rbp+0x38]
	mov	qword ptr [rcx], rax
	mov	qword ptr [rcx+0x8], rdx
	mov	word ptr [rcx+0x10], si
	mov	rax, rcx
	leave
	pop	r13
	pop	r12
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_012:	dec	cx
	add	rax, rax
	adc	rdx, rdx
	jnc	$_012
	jmp	$_003

$_013:	dec	si
	add	rbx, rbx
	adc	rdi, rdi
	jnc	$_013
	jmp	$_004

$_014:	add	si, si
	jz	$_015
	rcr	si, 1
	jmp	$_002

$_015:	rcr	si, 1
	test	esi, 0x80008000
	jz	$_021
	mov	esi, 32768
	jmp	$_011

$_016:	test	esi, 0x7FFF0000
	jne	$_001
	mov	rcx, rax
	or	rcx, rdx
	jnz	$_019
	mov	ecx, esi
	add	cx, cx
	jnz	$_019
$_017:	mov	esi, 65535
	movabs	rdx, 0x4000000000000000
	xor	eax, eax
	jmp	$_011

$_018:
	and	cx, 0x7FFF
	cmp	cx, 16383
	jnc	$_021
$_019:	mov	esi, 32767
$_020:	xor	eax, eax
	xor	edx, edx
	jmp	$_011

$_021:	xor	esi, esi
	jmp	$_020

$_022:	mov	rax, rbx
	mov	rdx, rdi
	shr	esi, 16
	jmp	$_011

$_023:	dec	si
	add	esi, 65536
	jc	$_024
	jo	$_024
	jns	$_011
	mov	rcx, rax
	or	rcx, rdx
	jne	$_011
	xor	esi, 0x8000
	jmp	$_011

$_024:	sub	esi, 65536
	mov	rcx, rax
	or	rcx, rdx
	or	rcx, rbx
	or	rcx, rdi
	jz	$_017
	cmp	rdx, rdi
	jc	$_022
	ja	$_011
	cmp	rax, rbx
	jbe	$_022
	jmp	$_011

$_025:
	sub	esi, 65536
	mov	rcx, rbx
	or	rcx, rdi
	jnz	$_022
	mov	ecx, esi
	shl	ecx, 16
	xor	esi, ecx
	and	esi, 0x80000000
	jmp	$_022

.att_syntax prefix
