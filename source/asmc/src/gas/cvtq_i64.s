
.intel_syntax noprefix

.global __cvtq_i64

.extern _flttoi64
.extern _fltunpack


.SECTION .text
	.ALIGN	16

__cvtq_i64:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 80
	mov	rdx, qword ptr [rbp+0x10]
	lea	rcx, [rbp-0x28]
	call	_fltunpack@PLT
	lea	rcx, [rbp-0x28]
	call	_flttoi64@PLT
	leave
	ret

.att_syntax prefix
