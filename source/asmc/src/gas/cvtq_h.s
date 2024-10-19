
.intel_syntax noprefix

.global __cvtq_h

.extern qerrno


.SECTION .text
	.ALIGN	16

__cvtq_h:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rsi, rdx
	mov	rdi, rcx
	mov	eax, dword ptr [rsi+0xA]
	mov	cx, word ptr [rsi+0xE]
	shr	eax, 1
	test	ecx, 0x7FFF
	jz	$_001
	or	eax, 0x80000000
$_001:	mov	edx, eax
	shl	edx, 12
	mov	edx, 4292870144
	jnc	$_003
	jnz	$_002
	cmp	dword ptr [rsi+0x6], 0
	jnz	$_002
	shl	edx, 1
$_002:	add	eax, 2097152
	jnc	$_003
	mov	eax, 2147483648
	inc	cx
$_003:	mov	ebx, ecx
	and	cx, 0x7FFF
	je	$_009
	cmp	cx, 32767
	jnz	$_005
	test	eax, 0x7FFFFFFF
	jz	$_004
	mov	eax, 4294967295
	jmp	$_010

$_004:	mov	eax, 4160749568
	shl	bx, 1
	rcr	eax, 1
	jmp	$_010

$_005:
	add	cx, -16368
	jns	$_006
	mov	dword ptr [qerrno+rip], 34
	mov	eax, 65536
	jmp	$_010

$_006:	cmp	cx, 31
	jnc	$_007
	cmp	cx, 30
	jnz	$_008
	cmp	eax, edx
	jbe	$_008
$_007:	mov	dword ptr [qerrno+rip], 34
	mov	eax, 4160618496
	shl	bx, 1
	rcr	eax, 1
	jmp	$_010

$_008:	and	eax, edx
	shl	eax, 1
	shrd	eax, ecx, 5
	shl	bx, 1
	rcr	eax, 1
	test	cx, cx
	jnz	$_010
	cmp	eax, 1
	jge	$_010
	mov	ebx, eax
	mov	dword ptr [qerrno+rip], 34
	mov	eax, ebx
	jmp	$_010

$_009:	and	eax, edx
$_010:	shr	eax, 16
	mov	ecx, eax
	mov	rax, rdi
	mov	word ptr [rax], cx
	cmp	rax, rsi
	jnz	$_011
	xor	ecx, ecx
	mov	word ptr [rax+0x2], cx
	mov	dword ptr [rax+0x4], ecx
	mov	dword ptr [rax+0x8], ecx
	mov	dword ptr [rax+0xC], ecx
$_011:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

.att_syntax prefix
