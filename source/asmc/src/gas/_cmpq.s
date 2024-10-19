
.intel_syntax noprefix

.global __cmpq


.SECTION .text
	.ALIGN	16

__cmpq:
	mov	rax, qword ptr [rdx]
	cmp	qword ptr [rcx], rax
	jnz	$_001
	mov	rax, qword ptr [rdx+0x8]
	cmp	qword ptr [rcx+0x8], rax
	jnz	$_001
	xor	eax, eax
	jmp	$_007

$_001:	cmp	byte ptr [rcx+0xF], 0
	jl	$_002
	cmp	byte ptr [rdx+0xF], 0
	jge	$_002
	mov	eax, 1
	jmp	$_007

$_002:	cmp	byte ptr [rcx+0xF], 0
	jge	$_003
	cmp	byte ptr [rdx+0xF], 0
	jl	$_003
	mov	rax, -1
	jmp	$_007

$_003:	cmp	byte ptr [rcx+0xF], 0
	jge	$_005
	cmp	byte ptr [rdx+0xF], 0
	jge	$_005
	mov	rax, qword ptr [rcx+0x8]
	cmp	qword ptr [rdx+0x8], rax
	jnz	$_004
	mov	rax, qword ptr [rcx]
	cmp	qword ptr [rdx], rax
$_004:	jmp	$_006

$_005:	mov	rax, qword ptr [rdx+0x8]
	cmp	qword ptr [rcx+0x8], rax
	jnz	$_006
	mov	rax, qword ptr [rdx]
	cmp	qword ptr [rcx], rax
$_006:	sbb	eax, eax
	sbb	eax, -1
$_007:	ret

.att_syntax prefix
