
.intel_syntax noprefix

.global LdrDirective

.extern RunLineQueue
.extern AddLineQueueX
.extern LstWrite
.extern GetCurrOffset
.extern get_fasttype
.extern CurrProc
.extern asmerr
.extern ModuleInfo
.extern SymFind


.SECTION .text
	.ALIGN	16

$_001:	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 56
	mov	qword ptr [rbp-0x10], 0
	inc	dword ptr [rbp+0x18]
	imul	ebx, dword ptr [rbp+0x18], 24
	add	rbx, qword ptr [rbp+0x20]
	mov	rax, qword ptr [rbx+0x10]
	mov	qword ptr [rbp-0x18], rax
	mov	rcx, qword ptr [CurrProc+rip]
	movzx	edx, byte ptr [rcx+0x1A]
	movzx	ecx, byte ptr [rcx+0x1B]
	call	get_fasttype@PLT
	test	byte ptr [rax+0xF], 0x31
	je	$_017
	mov	eax, dword ptr [rbx+0x4]
	mov	dword ptr [rbp-0x4], eax
	cmp	byte ptr [rbx], 2
	jz	$_004
	cmp	byte ptr [rbx], 8
	jnz	$_002
	cmp	byte ptr [rbx+0x18], 44
	jz	$_003
$_002:	jmp	$_017

$_003:	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x10], rax
	mov	dword ptr [rbp-0x4], 0
$_004:	cmp	byte ptr [rbx], 44
	jz	$_005
	cmp	byte ptr [rbx], 0
	jz	$_005
	add	rbx, 24
	jmp	$_004

$_005:	cmp	byte ptr [rbx], 44
	jz	$_006
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_018

$_006:	add	rbx, 24
	cmp	byte ptr [rbx], 2
	jnz	$_009
	mov	ecx, dword ptr [rbx+0x4]
	cmp	dword ptr [rbp-0x4], 0
	jnz	$_007
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp-0x10]
	lea	rcx, [DS0000+rip]
	call	AddLineQueueX@PLT
	xor	eax, eax
	jmp	$_018

	jmp	$_008

$_007:	cmp	ecx, dword ptr [rbp-0x4]
	jnz	$_008
	xor	eax, eax
	jmp	$_018

$_008:	jmp	$_017

$_009:	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	test	rax, rax
	jnz	$_010
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_018

	jmp	$_017

$_010:	test	byte ptr [rax+0x17], 0x01
	jz	$_017
	movzx	ecx, byte ptr [rax+0x48]
	cmp	dword ptr [rbp-0x4], 0
	jnz	$_011
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp-0x10]
	lea	rcx, [DS0000+rip]
	call	AddLineQueueX@PLT
	jmp	$_016

$_011:	cmp	ecx, dword ptr [rbp-0x4]
	jz	$_016
	mov	ebx, 682
	test	byte ptr [rax+0x19], 0x20
	jz	$_015
	cmp	dword ptr [rax+0x50], 4
	ja	$_012
	mov	ebx, 1050
	jmp	$_015

$_012:	cmp	dword ptr [rax+0x50], 8
	jnz	$_013
	mov	ebx, 612
	jmp	$_015

$_013:	cmp	dword ptr [rax+0x50], 16
	jnz	$_014
	mov	ebx, 1030
	jmp	$_015

$_014:	mov	ebx, 1394
$_015:	mov	r9d, ecx
	mov	r8d, dword ptr [rbp-0x4]
	mov	edx, ebx
	lea	rcx, [DS0001+rip]
	call	AddLineQueueX@PLT
$_016:	xor	eax, eax
	jmp	$_018

$_017:	mov	rdx, qword ptr [rbp-0x18]
	lea	rcx, [DS0002+rip]
	call	AddLineQueueX@PLT
	xor	eax, eax
$_018:	leave
	pop	rbx
	ret

LdrDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	cmp	qword ptr [CurrProc+rip], 0
	jnz	$_019
	mov	ecx, 2012
	call	asmerr@PLT
	jmp	$_022

$_019:	mov	rdx, qword ptr [rbp+0x18]
	mov	ecx, dword ptr [rbp+0x10]
	call	$_001
	mov	dword ptr [rbp-0x4], eax
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_020
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_020:	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_021
	call	RunLineQueue@PLT
$_021:	mov	eax, dword ptr [rbp-0x4]
$_022:	leave
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x73, 0x2C
	.byte  0x20, 0x25, 0x72, 0x00

DS0001:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x25, 0x72, 0x00

DS0002:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x73, 0x00


.att_syntax prefix
