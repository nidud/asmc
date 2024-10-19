
.intel_syntax noprefix

.global __cvti32_q

.extern _itoflt
.extern _fltpackfp


.SECTION .text
	.ALIGN	16

__cvti32_q:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 80
	mov	edx, dword ptr [rbp+0x18]
	lea	rcx, [rbp-0x28]
	call	_itoflt@PLT
	lea	rdx, [rbp-0x28]
	mov	rcx, qword ptr [rbp+0x10]
	call	_fltpackfp@PLT
	leave
	ret

.att_syntax prefix
