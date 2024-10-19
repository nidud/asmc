
.intel_syntax noprefix

.global _flttoi

.extern qerrno


.SECTION .text
	.ALIGN	16

_flttoi:
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rbx, rcx
	mov	cx, word ptr [rbx+0x10]
	mov	eax, ecx
	and	eax, 0x7FFF
	cmp	eax, 16383
	jge	$_001
	xor	eax, eax
	jmp	$_004

$_001:	cmp	eax, 16415
	jle	$_003
	mov	dword ptr [qerrno+rip], 34
	mov	eax, 2147483647
	test	cx, 0x8000
	jz	$_002
	mov	eax, 2147483648
$_002:	jmp	$_004

$_003:	mov	ecx, eax
	sub	ecx, 16383
	xor	eax, eax
	mov	edx, dword ptr [rbx+0xC]
	shl	edx, 1
	adc	eax, eax
	shld	eax, edx, cl
	test	byte ptr [rbx+0x11], 0xFFFFFF80
	jz	$_004
	neg	eax
$_004:	leave
	pop	rbx
	ret

.att_syntax prefix
