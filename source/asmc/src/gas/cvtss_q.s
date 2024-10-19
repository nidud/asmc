
.intel_syntax noprefix

.global __cvtss_q

.extern qerrno


.SECTION .text
	.ALIGN	16

__cvtss_q:
	mov	rax, rcx
	mov	edx, dword ptr [rdx]
	mov	ecx, edx
	shl	edx, 8
	sar	ecx, 23
	xor	ch, ch
	test	cl, cl
	jz	$_003
	cmp	cl, -1
	jz	$_001
	add	cx, 16256
	jmp	$_002

$_001:	or	ch, 0xFFFFFFFF
	test	edx, 0x7FFFFFFF
	jnz	$_002
	or	edx, 0x40000000
	mov	dword ptr [qerrno+rip], 33
$_002:	jmp	$_005

$_003:	test	edx, edx
	jz	$_005
	or	cx, 0x3F81
$_004:	test	edx, edx
	js	$_005
	shl	edx, 1
	dec	cx
	jmp	$_004

$_005:
	add	ecx, ecx
	rcr	cx, 1
	mov	word ptr [rax+0xE], cx
	shl	edx, 1
	mov	dword ptr [rax+0xA], edx
	xor	edx, edx
	mov	dword ptr [rax], edx
	mov	dword ptr [rax+0x4], edx
	mov	word ptr [eax+0x8], dx
	ret

.att_syntax prefix
