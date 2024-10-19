
.intel_syntax noprefix

.global _fltpackfp

.extern _fltround


.SECTION .text
	.ALIGN	16

_fltpackfp:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rcx, rdx
	call	_fltround@PLT
	mov	rax, qword ptr [rcx]
	mov	rdx, qword ptr [rcx+0x8]
	mov	cx, word ptr [rcx+0x10]
	shl	rax, 1
	rcl	rdx, 1
	shrd	rax, rdx, 16
	shrd	rdx, rcx, 16
	mov	rcx, qword ptr [rbp+0x10]
	mov	qword ptr [rcx], rax
	mov	qword ptr [rcx+0x8], rdx
	mov	rax, rcx
	leave
	ret

.att_syntax prefix
