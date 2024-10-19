
.intel_syntax noprefix

.global __sqrtq

.extern __subq
.extern __divq
.extern __mulq
.extern __cvtld_q
.extern __cvtq_ld


.SECTION .text
	.ALIGN	16

__sqrtq:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 80
	mov	rax, qword ptr [rcx]
	or	eax, dword ptr [rcx+0x8]
	or	ax, word ptr [rcx+0xC]
	mov	dx, word ptr [rcx+0xE]
	and	edx, 0x7FFF
	cmp	edx, 32767
	jnz	$_001
	test	eax, eax
	je	$_004
$_001:	test	edx, edx
	jnz	$_002
	test	eax, eax
	je	$_004
$_002:	test	byte ptr [rcx+0xF], 0xFFFFFF80
	jz	$_003
	mov	rdx, rcx
	call	__subq@PLT
	mov	rdx, rax
	mov	rcx, rax
	call	__divq@PLT
	jmp	$_004

$_003:	mov	rax, qword ptr [rcx]
	mov	qword ptr [rbp-0x10], rax
	mov	rax, qword ptr [rcx+0x8]
	mov	qword ptr [rbp-0x8], rax
	mov	rdx, rcx
	call	__cvtq_ld@PLT
	mov	rcx, qword ptr [rbp+0x10]
	fld	tbyte ptr [rcx]
	fsqrt
	fstp	tbyte ptr [rcx]
	mov	rdx, rcx
	call	__cvtld_q@PLT
	mov	rdx, qword ptr [rbp+0x10]
	mov	rax, qword ptr [rdx]
	mov	qword ptr [rbp-0x20], rax
	mov	rax, qword ptr [rdx+0x8]
	mov	qword ptr [rbp-0x18], rax
	lea	rcx, [rbp-0x10]
	call	__divq@PLT
	mov	rdx, rax
	lea	rcx, [rbp-0x20]
	call	__subq@PLT
	mov	qword ptr [rbp-0x10], 0
	mov	dword ptr [rbp-0x8], 0
	mov	dword ptr [rbp-0x4], 1073610752
	lea	rdx, [rbp-0x10]
	lea	rcx, [rbp-0x20]
	call	__mulq@PLT
	lea	rdx, [rbp-0x20]
	mov	rcx, qword ptr [rbp+0x10]
	call	__subq@PLT
$_004:	leave
	ret

.att_syntax prefix
