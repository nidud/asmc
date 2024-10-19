
.intel_syntax noprefix

.global __subo


.SECTION .text
	.ALIGN	16

__subo:
	mov	rax, qword ptr [rdx]
	sub	qword ptr [rcx], rax
	mov	rax, qword ptr [rdx+0x8]
	sbb	qword ptr [rcx+0x8], rax
	mov	rax, rcx
	ret

.att_syntax prefix
