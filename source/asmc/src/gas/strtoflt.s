
.intel_syntax noprefix

.global _strtoflt

.extern qerrno
.extern _fltscale
.extern _fltpackfp
.extern _destoflt
.extern _fltsetflags


.SECTION .text
	.ALIGN	16

_strtoflt:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 296
	xor	r8d, r8d
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [flt+rip]
	call	_fltsetflags@PLT
	test	eax, 0xE8
	jne	$_024
	lea	rdx, [rbp-0x100]
	lea	rcx, [flt+rip]
	call	_destoflt@PLT
	mov	dword ptr [rbp-0x104], eax
	test	eax, eax
	jnz	$_001
	or	byte ptr [flt+0x18+rip], 0x08
	jmp	$_024

$_001:	mov	byte ptr [rbp+rax-0x100], 0
	lea	rdx, [rbp-0x100]
	xor	eax, eax
	mov	al, byte ptr [rdx]
	mov	dword ptr [rbp-0x108], eax
	cmp	al, 43
	jz	$_002
	cmp	al, 45
	jnz	$_003
$_002:	inc	rdx
$_003:	mov	ebx, 16
	test	byte ptr [flt+0x18+rip], 0x10
	jnz	$_004
	mov	ebx, 10
$_004:	lea	rsi, [flt+rip]
$_005:	mov	al, byte ptr [rdx]
	test	al, al
	jz	$_007
	and	eax, 0xFFFFFFCF
	bt	eax, 6
	sbb	ecx, ecx
	and	ecx, 0x37
	sub	eax, ecx
	mov	ecx, 8
$_006:	movzx	edi, word ptr [rsi]
	imul	edi, ebx
	add	eax, edi
	mov	word ptr [rsi], ax
	add	rsi, 2
	shr	eax, 16
	dec	rcx
	jnz	$_006
	sub	rsi, 16
	inc	rdx
	jmp	$_005

$_007:	xor	ecx, ecx
	mov	rax, qword ptr [flt+rip]
	mov	rdx, qword ptr [flt+0x8+rip]
	test	rax, rax
	jnz	$_008
	test	rdx, rdx
	jz	$_013
$_008:	test	rdx, rdx
	jz	$_009
	bsr	rcx, rdx
	add	ecx, 64
	jmp	$_010

$_009:	bsr	rcx, rax
$_010:	mov	ch, cl
	mov	cl, 127
	sub	cl, ch
	cmp	cl, 64
	jc	$_011
	sub	cl, 64
	mov	rdx, rax
	xor	eax, eax
$_011:	shld	rdx, rax, cl
	shl	rax, cl
	mov	qword ptr [flt+rip], rax
	mov	qword ptr [flt+0x8+rip], rdx
	shr	ecx, 8
	add	ecx, 16383
	test	byte ptr [flt+0x18+rip], 0x10
	jz	$_012
	add	ecx, dword ptr [flt+0x1C+rip]
$_012:	jmp	$_014

$_013:	or	byte ptr [flt+0x18+rip], 0x08
$_014:	mov	edx, dword ptr [flt+0x18+rip]
	cmp	dword ptr [rbp-0x108], 45
	jz	$_015
	test	edx, 0x2
	jz	$_016
$_015:
	or	cx, 0x8000
$_016:	mov	ebx, ecx
	and	ebx, 0x7FFF
	jmp	$_019

$_017:	or	ecx, 0x7FFF
	xor	eax, eax
	mov	qword ptr [flt+rip], rax
	mov	qword ptr [flt+0x8+rip], rax
	test	edx, 0xA0
	jz	$_018
	or	ecx, 0x8000
	or	byte ptr [flt+0xF+rip], 0xFFFFFF80
$_018:	jmp	$_020

$_019:	test	edx, 0x3E0
	jnz	$_017
	cmp	ebx, 32767
	jnc	$_017
$_020:	mov	word ptr [flt+0x10+rip], cx
	and	ecx, 0x7FFF
	cmp	ecx, 32767
	jc	$_021
	mov	dword ptr [qerrno+rip], 34
	jmp	$_022

$_021:	cmp	dword ptr [flt+0x1C+rip], 0
	jz	$_022
	test	byte ptr [flt+0x18+rip], 0x10
	jnz	$_022
	lea	rcx, [flt+rip]
	call	_fltscale@PLT
$_022:	mov	eax, dword ptr [flt+0x1C+rip]
	add	eax, dword ptr [rbp-0x104]
	dec	eax
	cmp	eax, 4932
	jle	$_023
	or	byte ptr [flt+0x19+rip], 0x02
$_023:	cmp	eax, 4294962364
	jge	$_024
	or	byte ptr [flt+0x19+rip], 0x01
$_024:	lea	rdx, [flt+rip]
	lea	rcx, [flt+rip]
	call	_fltpackfp@PLT
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

flt:
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000


.att_syntax prefix
