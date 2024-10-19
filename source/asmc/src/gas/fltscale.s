
.intel_syntax noprefix

.global _fltscale

.extern _fltpowtable
.extern _fltmul


.SECTION .text
	.ALIGN	16

_fltscale:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	mov	edi, dword ptr [rbx+0x1C]
	lea	rsi, [_fltpowtable+rip]
	cmp	edi, 0
	jge	$_001
	neg	edi
	add	rsi, 312
$_001:	test	edi, edi
	jz	$_005
	xor	ebx, ebx
$_002:	test	edi, edi
	jz	$_004
	cmp	ebx, 13
	jnc	$_004
	test	edi, 0x1
	jz	$_003
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp+0x28]
	call	_fltmul@PLT
$_003:	inc	ebx
	shr	edi, 1
	add	rsi, 24
	jmp	$_002

$_004:	test	edi, edi
	jz	$_005
	xor	eax, eax
	mov	rbx, qword ptr [rbp+0x28]
	mov	qword ptr [rbx], rax
	mov	qword ptr [rbx+0x8], rax
	mov	word ptr [rbx+0x10], 32767
$_005:	mov	rax, qword ptr [rbp+0x28]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

.att_syntax prefix
