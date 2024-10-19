
.intel_syntax noprefix

.global __cvtq_ss

.extern qerrno


.SECTION .text
	.ALIGN	16

__cvtq_ss:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rbx, rdx
	mov	edx, 4294967040
	mov	eax, dword ptr [rbx+0xA]
	mov	cx, word ptr [rbx+0xE]
	and	ecx, 0x7FFF
	neg	ecx
	rcr	eax, 1
	mov	ecx, eax
	shl	ecx, 25
	mov	cx, word ptr [rbx+0xE]
	jnc	$_002
	jnz	$_001
	cmp	dword ptr [rbx+0x6], 0
	jnz	$_001
	shl	edx, 1
$_001:	add	eax, 256
	jnc	$_002
	mov	eax, 2147483648
	inc	cx
$_002:	and	eax, edx
	mov	ebx, ecx
	and	cx, 0x7FFF
	jz	$_006
	cmp	cx, 32767
	jnz	$_003
	shl	eax, 1
	shr	eax, 8
	or	eax, 0xFF000000
	shl	bx, 1
	rcr	eax, 1
	jmp	$_006

$_003:
	add	cx, -16256
	jns	$_004
	mov	dword ptr [qerrno+rip], 34
	xor	eax, eax
	jmp	$_006

$_004:
	cmp	cx, 255
	jl	$_005
	mov	dword ptr [qerrno+rip], 34
	mov	eax, 4278190080
	shl	bx, 1
	rcr	eax, 1
	jmp	$_006

$_005:	shl	eax, 1
	shrd	eax, ecx, 8
	shl	bx, 1
	rcr	eax, 1
	test	cx, cx
	jnz	$_006
	cmp	eax, 8388608
	jge	$_006
	mov	ebx, eax
	mov	dword ptr [qerrno+rip], 34
	mov	eax, ebx
$_006:	mov	ecx, eax
	mov	rax, qword ptr [rbp+0x18]
	mov	dword ptr [rax], ecx
	cmp	rax, qword ptr [rbp+0x20]
	jnz	$_007
	xor	ecx, ecx
	mov	dword ptr [rax+0x4], ecx
	mov	dword ptr [rax+0x8], ecx
	mov	dword ptr [rax+0xC], ecx
$_007:	leave
	pop	rbx
	ret

.att_syntax prefix
