
.intel_syntax noprefix

.global _fltunpack


.SECTION .text
	.ALIGN	16

_fltunpack:
	mov	rax, qword ptr [rdx]
	mov	r8, qword ptr [rdx+0x8]
	shld	r9, r8, 16
	shld	r8, rax, 16
	shl	rax, 16
	mov	word ptr [rcx+0x10], r9w
	and	r9d, 0x7FFF
	neg	r9d
	rcr	r8, 1
	rcr	rax, 1
	mov	qword ptr [rcx], rax
	mov	qword ptr [rcx+0x8], r8
	mov	rax, rcx
	ret

.att_syntax prefix
