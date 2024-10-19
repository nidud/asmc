
.intel_syntax noprefix

.global SafeSEHDirective

.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern QAddItem
.extern SymFind
.extern SymCreate


.SECTION .text
	.ALIGN	16

SafeSEHDirective:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	imul	ebx, ecx, 24
	add	rbx, rdx
	cmp	dword ptr [Options+0xA4+rip], 2
	jz	$_002
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_001
	lea	rdx, [DS0000+rip]
	mov	ecx, 8015
	call	asmerr@PLT
$_001:	xor	eax, eax
	jmp	$_016

$_002:	cmp	byte ptr [Options+0xA3+rip], 0
	jnz	$_004
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_003
	lea	rdx, [DS0001+rip]
	mov	ecx, 8015
	call	asmerr@PLT
$_003:	xor	eax, eax
	jmp	$_016

$_004:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 8
	jz	$_005
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_016

$_005:	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	mov	rsi, rax
	test	rsi, rsi
	jz	$_006
	cmp	byte ptr [rsi+0x18], 0
	jnz	$_008
$_006:	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_007
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2006
	call	asmerr@PLT
	jmp	$_016

$_007:	jmp	$_009

$_008:	test	byte ptr [rsi+0x15], 0x08
	jnz	$_009
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 3017
	call	asmerr@PLT
	jmp	$_016

$_009:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_014
	test	rsi, rsi
	jz	$_012
	mov	rdi, qword ptr [ModuleInfo+0x30+rip]
$_010:	test	rdi, rdi
	jz	$_011
	cmp	qword ptr [rdi+0x8], rsi
	jz	$_011
	mov	rdi, qword ptr [rdi]
	jmp	$_010

$_011:	jmp	$_013

$_012:	mov	rcx, qword ptr [rbx+0x8]
	call	SymCreate@PLT
	mov	rsi, rax
	mov	edi, 0
$_013:	test	rdi, rdi
	jnz	$_014
	or	byte ptr [rsi+0x14], 0x01
	mov	rdx, rsi
	lea	rcx, [ModuleInfo+0x30+rip]
	call	QAddItem@PLT
$_014:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 0
	jz	$_015
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_016

$_015:	xor	eax, eax
$_016:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x63, 0x6F, 0x66, 0x66, 0x00

DS0001:
	.byte  0x73, 0x61, 0x66, 0x65, 0x73, 0x65, 0x68, 0x00


.att_syntax prefix
