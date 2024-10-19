
.intel_syntax noprefix

.global _destoflt


.SECTION .text
	.ALIGN	16

_destoflt:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	dword ptr [rbp-0x4], 0
	mov	dword ptr [rbp-0x8], 0
	mov	rbx, rcx
	mov	rdi, rdx
	mov	rsi, qword ptr [rbx+0x20]
	mov	ecx, dword ptr [rbx+0x18]
	xor	eax, eax
	xor	edx, edx
$_001:	lodsb
	test	al, al
	jz	$_009
	cmp	al, 46
	jnz	$_002
	test	ecx, 0x800
	jnz	$_009
	or	ecx, 0x800
	jmp	$_008

$_002:	test	ecx, 0x10
	jz	$_004
	or	al, 0x20
	cmp	al, 48
	jc	$_009
	cmp	al, 102
	ja	$_009
	cmp	al, 57
	jbe	$_003
	cmp	al, 97
	jc	$_009
$_003:	jmp	$_005

$_004:	cmp	al, 48
	jc	$_009
	cmp	al, 57
	ja	$_009
$_005:	test	ecx, 0x800
	jz	$_006
	inc	dword ptr [rbp-0x8]
$_006:	or	ecx, 0x400
	or	edx, eax
	cmp	edx, 48
	jz	$_001
	cmp	dword ptr [rbp-0x4], 49
	jge	$_007
	stosb
$_007:	inc	dword ptr [rbp-0x4]
$_008:	jmp	$_001

$_009:
	mov	byte ptr [rdi], 0
	xor	edx, edx
	test	ecx, 0x400
	je	$_026
	xor	edi, edi
	test	ecx, 0x10
	jz	$_010
	cmp	al, 112
	jz	$_011
	cmp	al, 80
	jz	$_011
$_010:	cmp	al, 101
	jz	$_011
	cmp	al, 69
	jnz	$_019
$_011:	mov	al, byte ptr [rsi]
	lea	rdx, [rsi-0x1]
	cmp	al, 43
	jnz	$_012
	inc	rsi
$_012:	cmp	al, 45
	jnz	$_013
	inc	rsi
	or	ecx, 0x04
$_013:	and	ecx, 0xFFFFFBFF
$_014:	movzx	eax, byte ptr [rsi]
	cmp	al, 48
	jc	$_016
	cmp	al, 57
	ja	$_016
	cmp	edi, 100000000
	jnc	$_015
	imul	edi, edi, 10
	lea	edi, [rdi+rax-0x30]
$_015:	or	ecx, 0x400
	inc	rsi
	jmp	$_014

$_016:	test	ecx, 0x4
	jz	$_017
	neg	edi
$_017:	test	ecx, 0x400
	jnz	$_018
	mov	rsi, rdx
$_018:	jmp	$_020

$_019:	dec	rsi
$_020:	mov	edx, edi
	mov	eax, dword ptr [rbp-0x8]
	mov	edi, 38
	test	ecx, 0x10
	jz	$_021
	mov	edi, 32
	shl	eax, 2
$_021:	sub	edx, eax
	mov	eax, 1
	test	ecx, 0x10
	jz	$_022
	mov	eax, 4
$_022:	cmp	dword ptr [rbp-0x4], edi
	jle	$_024
	add	edx, dword ptr [rbp-0x4]
	mov	dword ptr [rbp-0x4], edi
	test	ecx, 0x10
	jz	$_023
	shl	edi, 2
$_023:	sub	edx, edi
$_024:	cmp	dword ptr [rbp-0x4], 0
	jle	$_025
	mov	edi, dword ptr [rbp-0x4]
	add	rdi, qword ptr [rbp+0x30]
	cmp	byte ptr [rdi-0x1], 48
	jnz	$_025
	add	edx, eax
	dec	dword ptr [rbp-0x4]
	jmp	$_024

$_025:	jmp	$_027

$_026:	mov	rsi, qword ptr [rbx+0x20]
$_027:	mov	dword ptr [rbx+0x18], ecx
	mov	qword ptr [rbx+0x20], rsi
	mov	dword ptr [rbx+0x1C], edx
	mov	eax, dword ptr [rbp-0x4]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

.att_syntax prefix
