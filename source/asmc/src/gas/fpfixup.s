
.intel_syntax noprefix

.global AddFloatingPointEmulationFixup

.extern omf_FlushCurrSeg
.extern MakeExtern
.extern store_fixup
.extern CreateFixup
.extern write_to_file
.extern Options
.extern ModuleInfo
.extern SymFind


.SECTION .text
	.ALIGN	16

AddFloatingPointEmulationFixup:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 88
	mov	dword ptr [rbp-0x1C], 1381982022
	mov	dword ptr [rbp-0x18], 20817
	cmp	word ptr [rcx+0xE], 910
	jnz	$_001
	mov	edi, 0
	jmp	$_003

$_001:	cmp	dword ptr [rcx+0x4], -2
	jnz	$_002
	mov	edi, 1
	jmp	$_003

$_002:	mov	edi, dword ptr [rcx+0x4]
	add	edi, 2
$_003:	xor	ebx, ebx
$_004:	cmp	ebx, 2
	jnc	$_007
	mov	qword ptr [rbp+rbx*8-0x10], 0
	lea	ecx, [rdi+rbx*8]
	mov	eax, 1
	shl	eax, cl
	test	eax, 0xF8FF
	jz	$_006
	lea	eax, [rbx+0x49]
	mov	byte ptr [rbp-0x1B], al
	lea	rcx, [patchchr2+rip]
	mov	al, byte ptr [rcx+rdi]
	mov	byte ptr [rbp-0x1A], al
	lea	rcx, [rbp-0x1C]
	call	SymFind@PLT
	mov	qword ptr [rbp+rbx*8-0x10], rax
	test	rax, rax
	jz	$_005
	cmp	byte ptr [rax+0x18], 0
	jnz	$_006
$_005:	mov	byte ptr [rsp+0x20], 0
	mov	r9, rax
	xor	r8d, r8d
	mov	edx, 130
	lea	rcx, [rbp-0x1C]
	call	MakeExtern@PLT
	mov	qword ptr [rbp+rbx*8-0x10], rax
	mov	byte ptr [rax+0x1A], 0
$_006:	inc	ebx
	jmp	$_004

$_007:
	cmp	dword ptr [write_to_file+rip], 0
	jz	$_011
	mov	rdi, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rdx, qword ptr [rdi+0x68]
	mov	eax, dword ptr [rdx+0xC]
	sub	eax, dword ptr [rdx+0x8]
	add	eax, 3
	cmp	dword ptr [Options+0xA4+rip], 1
	jnz	$_008
	cmp	eax, 1014
	jbe	$_008
	call	omf_FlushCurrSeg@PLT
$_008:	xor	ebx, ebx
$_009:	cmp	ebx, 2
	jnc	$_011
	mov	rax, qword ptr [rbp+rbx*8-0x10]
	test	rax, rax
	jz	$_010
	xor	r8d, r8d
	mov	edx, 5
	mov	rcx, rax
	call	CreateFixup@PLT
	mov	rsi, rax
	mov	byte ptr [rsi+0x20], 5
	add	dword ptr [rsi+0x14], ebx
	mov	dword ptr [rbp-0x14], 0
	lea	r8, [rbp-0x14]
	mov	rdx, rdi
	mov	rcx, rsi
	call	store_fixup@PLT
$_010:	inc	ebx
	jmp	$_009

$_011:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

patchchr2:
	.byte  0x57, 0x44, 0x45, 0x43, 0x53, 0x41, 0x46, 0x47


.att_syntax prefix
