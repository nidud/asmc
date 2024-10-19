
.intel_syntax noprefix

.global _fptostr

.extern strcpy


.SECTION .text
	.ALIGN	16

_fptostr:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rbp
	mov	rbp, rsp
	mov	rdx, r8
	mov	byte ptr [rcx], 48
	inc	rcx
$_001:	cmp	dword ptr [rbp+0x18], 0
	jle	$_004
	mov	al, byte ptr [rdx]
	test	al, al
	jz	$_002
	inc	rdx
	jmp	$_003

$_002:	mov	al, 48
$_003:	mov	byte ptr [rcx], al
	dec	dword ptr [rbp+0x18]
	inc	rcx
	jmp	$_001

$_004:
	mov	byte ptr [rcx], 0
	mov	al, byte ptr [rdx]
	cmp	dword ptr [rbp+0x18], 0
	jl	$_007
	cmp	al, 53
	jc	$_007
	dec	rcx
	jmp	$_006

$_005:	mov	byte ptr [rcx], 48
	dec	rcx
$_006:	cmp	byte ptr [rcx], 57
	jz	$_005
	inc	byte ptr [rcx]
$_007:	mov	rcx, qword ptr [rbp+0x10]
	cmp	byte ptr [rcx], 49
	jnz	$_008
	mov	rdx, qword ptr [rbp+0x20]
	inc	dword ptr [rdx+0x1C]
	jmp	$_009

$_008:	lea	rsi, [rcx+0x1]
	mov	rdi, rcx
	call	strcpy@PLT
$_009:	leave
	ret

.att_syntax prefix
