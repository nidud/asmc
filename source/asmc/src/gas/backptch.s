
.intel_syntax noprefix

.global BackPatch

.extern FreeFixup
.extern OutputByte
.extern asmerr
.extern ModuleInfo
.extern Parse_Pass


.SECTION .text
	.ALIGN	16

BackPatch:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rsi, rcx
	mov	rbx, qword ptr [rsi+0x60]
$_001:	test	rbx, rbx
	je	$_031
	mov	rax, qword ptr [rbx]
	mov	qword ptr [rbp-0x8], rax
	mov	rax, qword ptr [rsi+0x30]
	test	rax, rax
	je	$_030
	cmp	qword ptr [rbx+0x28], rax
	jne	$_030
	xor	edi, edi
	movzx	ecx, byte ptr [rbx+0x18]
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_005
	cmp	byte ptr [rsi+0x19], -126
	jnz	$_002
	cmp	byte ptr [rbx+0x19], 4
	jnz	$_002
	mov	byte ptr [ModuleInfo+0x1ED+rip], 1
	inc	dword ptr [rsi+0x28]
	xor	ecx, ecx
	call	OutputByte@PLT
	mov	rcx, rbx
	call	FreeFixup@PLT
	jmp	$_030

	jmp	$_005

$_002:	cmp	ecx, 3
	jz	$_003
	cmp	ecx, 2
	jnz	$_004
$_003:	mov	rcx, rbx
	call	FreeFixup@PLT
	jmp	$_030

$_004:	cmp	ecx, 4
	jnz	$_005
	cmp	byte ptr [rbx+0x19], 5
	jnz	$_005
	mov	edi, 1
	jmp	$_009

$_005:	jmp	$_029

$_006:	mov	edi, 2
$_007:	inc	edi
$_008:	inc	edi
	mov	rcx, qword ptr [rbx+0x30]
	mov	edx, dword ptr [rbx+0x10]
	add	edx, dword ptr [rcx+0x28]
	sub	edx, dword ptr [rbx+0x14]
	sub	edx, edi
	sub	edx, 1
	lea	ecx, [rdi*8-0x1]
	mov	eax, 1
	shl	eax, cl
	dec	eax
	mov	ecx, eax
	neg	ecx
	dec	ecx
	cmp	edx, eax
	jg	$_009
	cmp	edx, ecx
	jge	$_028
$_009:	mov	byte ptr [ModuleInfo+0x1ED+rip], 1
	jmp	$_027

$_010:	xor	edi, edi
	jmp	$_024

$_011:	jmp	$_030

$_012:	inc	edi
$_013:	inc	edi
$_014:	mov	rdx, qword ptr [rsi+0x30]
	mov	rdx, qword ptr [rdx+0x68]
	cmp	byte ptr [rdx+0x68], 0
	jz	$_015
	add	edi, 2
$_015:	inc	edi
	mov	eax, dword ptr [rbx+0x14]
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_017
	mov	rcx, qword ptr [rdx+0x28]
$_016:	test	rcx, rcx
	jz	$_017
	test	byte ptr [rcx+0x1B], 0x02
	jne	$_030
	cmp	dword ptr [rcx+0x14], eax
	jbe	$_017
	mov	rcx, qword ptr [rcx+0x8]
	jmp	$_016

$_017:	mov	rcx, qword ptr [rdx+0x20]
$_018:	test	rcx, rcx
	jz	$_019
	cmp	dword ptr [rcx+0x28], eax
	jle	$_019
	add	dword ptr [rcx+0x28], edi
	mov	rcx, qword ptr [rcx+0x70]
	jmp	$_018

$_019:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_022
	mov	rcx, qword ptr [rdx+0x28]
$_020:	test	rcx, rcx
	jz	$_022
	cmp	qword ptr [rcx+0x30], rsi
	jz	$_021
	cmp	dword ptr [rcx+0x14], eax
	jbe	$_022
	add	dword ptr [rcx+0x14], edi
$_021:	mov	rcx, qword ptr [rcx+0x8]
	jmp	$_020

$_022:	test	edi, edi
	jz	$_023
	mov	ecx, 204
	call	OutputByte@PLT
	dec	edi
	jmp	$_022

$_023:	jmp	$_025

$_024:	cmp	byte ptr [rbx+0x19], 1
	je	$_011
	cmp	byte ptr [rbx+0x19], 2
	je	$_012
	cmp	byte ptr [rbx+0x19], 3
	je	$_013
	jmp	$_014

$_025:	jmp	$_028

$_026:	sub	edx, eax
	mov	ecx, 2075
	call	asmerr@PLT
	jmp	$_028

$_027:	cmp	edi, 1
	je	$_010
	cmp	edi, 2
	jz	$_026
	cmp	edi, 4
	jz	$_026
$_028:	mov	rcx, rbx
	call	FreeFixup@PLT
	jmp	$_030

$_029:	cmp	ecx, 3
	je	$_006
	cmp	ecx, 2
	je	$_007
	cmp	ecx, 1
	je	$_008
$_030:	mov	rbx, qword ptr [rbp-0x8]
	jmp	$_001

$_031:
	xor	eax, eax
	mov	qword ptr [rsi+0x60], rax
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

.att_syntax prefix
