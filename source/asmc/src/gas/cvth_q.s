
.intel_syntax noprefix

.global __cvth_q

.extern qerrno


.SECTION .text
	.ALIGN	16

__cvth_q:
	mov	rax, rcx
	movsx	edx, word ptr [rdx]
	mov	ecx, edx
	shl	edx, 21
	sar	ecx, 10
	and	cx, 0x1F
	test	cl, cl
	jz	$_004
	cmp	cl, 31
	jz	$_001
	add	cx, 16368
	jmp	$_003

$_001:
	or	cx, 0x7FE0
	test	edx, 0x7FFFFFFF
	jz	$_002
	mov	dword ptr [qerrno+rip], 33
	mov	ecx, 65535
	mov	edx, 1073741824
	jmp	$_003

$_002:	xor	edx, edx
$_003:	jmp	$_006

$_004:	test	edx, edx
	jz	$_006
	or	cx, 0x3FF1
$_005:	test	edx, edx
	js	$_006
	shl	edx, 1
	dec	cx
	jmp	$_005

$_006:
	shl	ecx, 1
	rcr	cx, 1
	mov	word ptr [rax+0xE], cx
	shl	edx, 1
	mov	dword ptr [rax+0xA], edx
	xor	edx, edx
	mov	qword ptr [rax], rdx
	mov	dword ptr [rax+0x8], edx
	ret

.att_syntax prefix
