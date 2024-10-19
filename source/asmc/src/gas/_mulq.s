
.intel_syntax noprefix

.global __mulq

.extern _fltmul
.extern _fltpackfp
.extern _fltunpack


.SECTION .text
	.ALIGN	16

__mulq:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 112
	mov	rdx, qword ptr [rbp+0x10]
	lea	rcx, [rbp-0x28]
	call	_fltunpack@PLT
	mov	rdx, qword ptr [rbp+0x18]
	lea	rcx, [rbp-0x50]
	call	_fltunpack@PLT
	lea	rdx, [rbp-0x50]
	lea	rcx, [rbp-0x28]
	call	_fltmul@PLT
	lea	rdx, [rbp-0x28]
	mov	rcx, qword ptr [rbp+0x10]
	call	_fltpackfp@PLT
	leave
	ret

.att_syntax prefix
