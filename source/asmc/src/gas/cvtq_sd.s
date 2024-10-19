
.intel_syntax noprefix

.global __cvtq_sd

.extern qerrno


.SECTION .text
	.ALIGN	16

__cvtq_sd:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rax, rdx
	movzx	ecx, word ptr [rax+0xE]
	mov	edx, dword ptr [rax+0xA]
	mov	ebx, ecx
	and	ebx, 0x7FFF
	mov	edi, ebx
	neg	ebx
	mov	eax, dword ptr [rax+0x6]
	rcr	edx, 1
	rcr	eax, 1
	mov	esi, 4294965248
	mov	ebx, eax
	shl	ebx, 22
	jnc	$_002
	jnz	$_001
	shl	ebx, 1
$_001:	add	eax, 2048
	adc	edx, 0
	jnc	$_002
	mov	edx, 2147483648
	inc	cx
$_002:	and	eax, esi
	mov	ebx, ecx
	and	cx, 0x7FFF
	add	cx, -15360
	cmp	cx, 2047
	jnc	$_005
	test	cx, cx
	jnz	$_003
	shrd	eax, edx, 12
	shl	edx, 1
	shr	edx, 12
	jmp	$_004

$_003:	shrd	eax, edx, 11
	shl	edx, 1
	shrd	edx, ecx, 11
$_004:	shl	bx, 1
	rcr	edx, 1
	jmp	$_010

$_005:
	cmp	cx, -15360
	jc	$_009
	cmp	cx, -52
	jl	$_007
	sub	cx, 12
	neg	cx
	cmp	cl, 32
	jc	$_006
	sub	cl, 32
	mov	esi, eax
	mov	eax, edx
	xor	edx, edx
$_006:	shrd	esi, eax, cl
	shrd	eax, edx, cl
	shr	edx, cl
	add	esi, esi
	adc	eax, 0
	adc	edx, 0
	jmp	$_008

$_007:	xor	eax, eax
	xor	edx, edx
	shl	ebx, 17
	rcr	edx, 1
$_008:	jmp	$_010

$_009:	shrd	eax, edx, 11
	shl	edx, 1
	shr	edx, 11
	shl	bx, 1
	rcr	edx, 1
	or	edx, 0x7FF00000
$_010:	xor	ebx, ebx
	cmp	edi, 15308
	jnc	$_013
	mov	rcx, qword ptr [rbp+0x30]
	test	edi, edi
	jnz	$_011
	cmp	edi, dword ptr [rcx+0x6]
	jnz	$_011
	cmp	edi, dword ptr [rcx+0xA]
	jz	$_012
$_011:	xor	eax, eax
	xor	edx, edx
	mov	ebx, 34
$_012:	jmp	$_016

$_013:	cmp	edi, 15309
	jc	$_015
	mov	edi, edx
	and	edi, 0x7FF00000
	mov	ebx, 34
	jz	$_014
	cmp	edi, 2146435072
	jz	$_014
	xor	ebx, ebx
$_014:	jmp	$_016

$_015:	cmp	edi, 15308
	jc	$_016
	mov	edi, edx
	or	edi, eax
	mov	ebx, 34
	jz	$_016
	mov	edi, edx
	and	edi, 0x7FF00000
	jz	$_016
	xor	ebx, ebx
$_016:	mov	rdi, qword ptr [rbp+0x28]
	mov	dword ptr [rdi], eax
	mov	dword ptr [rdi+0x4], edx
	test	ebx, ebx
	jz	$_017
	mov	dword ptr [qerrno+rip], ebx
$_017:	cmp	rdi, qword ptr [rbp+0x30]
	jnz	$_018
	xor	eax, eax
	mov	dword ptr [rdi+0x8], eax
	mov	dword ptr [rdi+0xC], eax
$_018:	mov	rax, rdi
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

.att_syntax prefix
