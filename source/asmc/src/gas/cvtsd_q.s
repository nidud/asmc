
.intel_syntax noprefix

.global __cvtsd_q


.SECTION .text
	.ALIGN	16

__cvtsd_q:
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rbx, rcx
	mov	eax, dword ptr [rdx]
	mov	edx, dword ptr [rdx+0x4]
	mov	ecx, edx
	shld	edx, eax, 11
	shl	eax, 11
	sar	ecx, 20
	and	cx, 0x7FF
	jz	$_004
	cmp	cx, 2047
	jz	$_001
	add	cx, 15360
	jmp	$_003

$_001:	or	ch, 0x7F
	test	edx, 0x7FFFFFFF
	jnz	$_002
	test	eax, eax
	jz	$_003
$_002:	or	edx, 0x40000000
$_003:	or	edx, 0x80000000
	jmp	$_007

$_004:	test	edx, edx
	jnz	$_005
	test	eax, eax
	jz	$_007
$_005:	or	ecx, 0x3C01
	test	edx, edx
	jnz	$_006
	xchg	eax, edx
	sub	cx, 32
$_006:	test	edx, edx
	js	$_007
	shl	eax, 1
	rcl	edx, 1
	dec	rcx
	jnz	$_006
$_007:	add	ecx, ecx
	rcr	cx, 1
	shl	eax, 1
	rcl	edx, 1
	xchg	rax, rbx
	mov	dword ptr [rax+0x6], ebx
	mov	dword ptr [rax+0xA], edx
	mov	word ptr [rax+0xE], cx
	xor	ebx, ebx
	mov	dword ptr [rax], ebx
	mov	word ptr [rax+0x4], bx
	leave
	pop	rbx
	ret


.att_syntax prefix
