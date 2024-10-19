
.intel_syntax noprefix

.global __saro


.SECTION .text
	.ALIGN	16

__saro:
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rsi, rcx
	mov	ecx, edx
	mov	eax, dword ptr [rsi]
	mov	edx, dword ptr [rsi+0x4]
	mov	ebx, dword ptr [rsi+0x8]
	mov	edi, dword ptr [rsi+0xC]
	cmp	ecx, 64
	jc	$_001
	cmp	dword ptr [rbp+0x38], 64
	jg	$_001
	xor	eax, eax
	xor	edx, edx
	xor	ebx, ebx
	xor	edi, edi
	jmp	$_009

$_001:	cmp	ecx, 128
	jc	$_002
	cmp	dword ptr [rbp+0x38], 128
	jnz	$_002
	sar	edi, 31
	mov	ebx, edi
	mov	edx, edi
	mov	eax, edi
	jmp	$_009

$_002:	cmp	dword ptr [rbp+0x38], 128
	jnz	$_005
	jmp	$_004

$_003:	mov	eax, edx
	mov	edx, ebx
	mov	ebx, edi
	sar	edi, 31
	sub	ecx, 32
$_004:	cmp	ecx, 32
	ja	$_003
	shrd	eax, edx, cl
	shrd	edx, ebx, cl
	shrd	ebx, edi, cl
	sar	edi, cl
	jmp	$_009

$_005:	cmp	eax, -1
	jnz	$_006
	cmp	dword ptr [rbp+0x38], 32
	jnz	$_006
	xor	edx, edx
$_006:	cmp	dword ptr [rbp+0x38], 32
	jnz	$_007
	sar	eax, cl
	jmp	$_009

$_007:	cmp	ecx, 32
	jnc	$_008
	shrd	eax, edx, cl
	sar	edx, cl
	jmp	$_009

$_008:	mov	eax, edx
	sar	edx, 31
	and	cl, 0x1F
	sar	eax, cl
$_009:	mov	dword ptr [rsi], eax
	mov	dword ptr [rsi+0x4], edx
	mov	dword ptr [rsi+0x8], ebx
	mov	dword ptr [rsi+0xC], edi
	mov	rax, rsi
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

.att_syntax prefix
