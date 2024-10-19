
.intel_syntax noprefix

.global __addo


.SECTION .text
	.ALIGN	16

__addo:
	mov	rax, qword ptr [rdx]
	add	qword ptr [rcx], rax
	mov	rax, qword ptr [rdx+0x8]
	adc	qword ptr [rcx+0x8], rax
	mov	rax, rcx
	ret

.att_syntax prefix
