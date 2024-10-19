
.intel_syntax noprefix

.global _fltround
.global _fltgetrounding
.global _fltsetrounding


.SECTION .text
	.ALIGN	16

_fltround:
	mov	rax, qword ptr [rcx]
	test	eax, 0x4000
	jz	$_002
	mov	rdx, qword ptr [rcx+0x8]
	add	rax, 16384
	adc	rdx, 0
	jnc	$_001
	rcr	rdx, 1
	rcr	rax, 1
	inc	word ptr [rcx+0x10]
	cmp	word ptr [rcx+0x10], 32767
	jnz	$_001
	mov	word ptr [rcx+0x10], 32767
	xor	eax, eax
	xor	edx, edx
$_001:	mov	qword ptr [rcx], rax
	mov	qword ptr [rcx+0x8], rdx
$_002:	mov	rax, rcx
	ret

_fltgetrounding:
	mov	eax, dword ptr [current_rounding_mode+rip]
	ret

_fltsetrounding:
	mov	eax, dword ptr [current_rounding_mode+rip]
	mov	dword ptr [current_rounding_mode+rip], ecx
	ret


.SECTION .data
	.ALIGN	16

current_rounding_mode:
	.int   0x00000000


.att_syntax prefix
