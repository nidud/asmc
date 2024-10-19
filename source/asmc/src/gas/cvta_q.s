
.intel_syntax noprefix

.global __cvta_q

.extern _strtoflt


.SECTION .text
	.ALIGN	16

__cvta_q:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rcx, qword ptr [rbp+0x18]
	call	_strtoflt@PLT
	mov	rcx, qword ptr [rbp+0x20]
	test	rcx, rcx
	jz	$_001
	mov	rdx, qword ptr [rax+0x20]
	mov	qword ptr [rcx], rdx
$_001:	mov	rcx, qword ptr [rbp+0x10]
	mov	rdx, rax
	mov	rax, qword ptr [rdx]
	mov	qword ptr [rcx], rax
	mov	rax, qword ptr [rdx+0x8]
	mov	qword ptr [rcx+0x8], rax
	mov	rax, rcx
	leave
	ret

.att_syntax prefix
