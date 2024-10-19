
.intel_syntax noprefix

.global EndDirective

.extern idata_fixup
.extern ProcCheckOpen
.extern LstWriteSrcLine
.extern CurrStruct
.extern EvalOperand
.extern AddPublicData
.extern SegmentModuleExit
.extern optable_idx
.extern InstrTable
.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern CollectLinkObject


.SECTION .text
	.ALIGN	16

EndDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 256
	inc	dword ptr [rbp+0x20]
	call	LstWriteSrcLine@PLT
	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [rbp+0x20]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_001
	mov	rax, -1
	jmp	$_015

$_001:	imul	ebx, dword ptr [rbp+0x20], 24
	add	rbx, qword ptr [rbp+0x28]
	cmp	byte ptr [rbx], 0
	jz	$_002
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_015

$_002:	mov	rcx, qword ptr [CurrStruct+rip]
	test	rcx, rcx
	jz	$_005
	jmp	$_004

$_003:	mov	rcx, qword ptr [rcx+0x70]
$_004:	cmp	qword ptr [rcx+0x70], 0
	jnz	$_003
	mov	rdx, qword ptr [rcx+0x8]
	mov	ecx, 1010
	call	asmerr@PLT
$_005:	call	ProcCheckOpen@PLT
	mov	rsi, qword ptr [rbp-0x18]
	cmp	dword ptr [rbp-0x2C], 1
	jne	$_011
	test	byte ptr [rbp-0x25], 0x01
	jne	$_011
	cmp	byte ptr [rbp-0x28], -127
	jz	$_006
	cmp	byte ptr [rbp-0x28], -126
	jz	$_006
	cmp	byte ptr [rbp-0x28], -64
	jne	$_011
	cmp	dword ptr [rbp-0x30], 249
	jne	$_011
$_006:	test	rsi, rsi
	je	$_011
	cmp	byte ptr [rsi+0x18], 1
	jz	$_007
	cmp	byte ptr [rsi+0x18], 2
	jne	$_011
$_007:	cmp	dword ptr [Options+0xA4+rip], 1
	jnz	$_008
	mov	qword ptr [rbp-0xB8], 0
	mov	word ptr [rbp-0xC2], 720
	movzx	eax, word ptr [optable_idx+0x17A+rip]
	lea	rcx, [InstrTable+rip]
	lea	rax, [rcx+rax*8]
	mov	qword ptr [rbp-0x78], rax
	mov	byte ptr [rbp-0x6A], 0
	mov	byte ptr [rbp-0x70], -64
	lea	r8, [rbp-0x68]
	xor	edx, edx
	lea	rcx, [rbp-0xD0]
	call	idata_fixup@PLT
	mov	rax, qword ptr [rbp-0xB8]
	mov	qword ptr [ModuleInfo+0xE0+rip], rax
	mov	eax, dword ptr [rbp-0x68]
	mov	dword ptr [ModuleInfo+0xE8+rip], eax
	jmp	$_010

$_008:	cmp	byte ptr [rsi+0x18], 2
	jz	$_009
	test	dword ptr [rsi+0x14], 0x80
	jnz	$_009
	or	dword ptr [rsi+0x14], 0x80
	mov	rcx, rsi
	call	AddPublicData@PLT
$_009:	mov	qword ptr [ModuleInfo+0xE0+rip], rsi
$_010:	jmp	$_012

$_011:	cmp	dword ptr [rbp-0x2C], -2
	jz	$_012
	mov	ecx, 2094
	call	asmerr@PLT
	jmp	$_015

$_012:	call	SegmentModuleExit@PLT
	cmp	qword ptr [ModuleInfo+0x160+rip], 0
	jz	$_013
	lea	rcx, [ModuleInfo+rip]
	call	qword ptr [ModuleInfo+0x160+rip]
	jmp	$_014

$_013:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_014
	mov	rcx, qword ptr [ModuleInfo+0x98+rip]
	test	rcx, rcx
	jz	$_014
	call	CollectLinkObject@PLT
$_014:	mov	byte ptr [ModuleInfo+0x1E0+rip], 1
	xor	eax, eax
$_015:	leave
	pop	rbx
	pop	rsi
	ret

.att_syntax prefix
