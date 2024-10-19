
.intel_syntax noprefix

.global __cvtld_q


.SECTION .text
	.ALIGN	16

__cvtld_q:
	mov	rax, qword ptr [rdx]
	movzx	edx, word ptr [rdx+0x8]
	add	dx, dx
	rcr	dx, 1
	shl	rax, 1
	shld	rdx, rax, 48
	shl	rax, 48
	mov	qword ptr [rcx], rax
	mov	qword ptr [rcx+0x8], rdx
	mov	rax, rcx
	ret

.att_syntax prefix
