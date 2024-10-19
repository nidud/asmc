
.intel_syntax noprefix

.global _flttoi64

.extern qerrno


.SECTION .text
	.ALIGN	16

_flttoi64:
	mov	dx, word ptr [rcx+0x10]
	mov	eax, edx
	and	eax, 0x7FFF
	cmp	eax, 16383
	jge	$_002
	xor	eax, eax
	test	dx, 0x8000
	jz	$_001
	dec	rax
$_001:	jmp	$_005

$_002:	cmp	eax, 16445
	jle	$_004
	mov	dword ptr [qerrno+rip], 34
	movabs	rax, 0x7FFFFFFFFFFFFFFF
	test	edx, 0x8000
	jz	$_003
	movabs	rax, 0x8000000000000000
$_003:	jmp	$_005

$_004:	mov	r10, qword ptr [rcx+0x8]
	mov	ecx, eax
	xor	eax, eax
	sub	ecx, 16383
	shl	r10, 1
	adc	eax, eax
	shld	rax, r10, cl
	test	edx, 0x8000
	jz	$_005
	neg	rax
$_005:	ret

.att_syntax prefix
