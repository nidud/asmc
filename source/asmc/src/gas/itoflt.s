
.intel_syntax noprefix

.global _itoflt


.SECTION .text
	.ALIGN	16

_itoflt:
	mov	eax, edx
	mov	rdx, rcx
	mov	r8d, 16383
	test	eax, eax
	jns	$_001
	neg	eax
	or	r8d, 0x8000
$_001:	xor	r9d, r9d
	test	eax, eax
	jz	$_002
	bsr	r9, rax
	mov	ecx, 63
	sub	ecx, r9d
	shl	rax, cl
	add	r9d, r8d
$_002:	xor	ecx, ecx
	mov	qword ptr [rdx], rcx
	mov	qword ptr [rdx+0x8], rax
	mov	word ptr [rdx+0x10], r9w
	mov	rax, rdx
	ret

.att_syntax prefix