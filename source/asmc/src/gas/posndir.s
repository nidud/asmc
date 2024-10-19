
.intel_syntax noprefix

.global OrgDirective
.global AlignCurrOffset
.global AlignDirective

.extern StoreLine
.extern StoreState
.extern LstWrite
.extern AlignInStruct
.extern SetStructCurrentOffset
.extern CurrStruct
.extern EvalOperand
.extern GetCurrSegAlign
.extern SetCurrOffset
.extern GetCurrOffset
.extern FillDataBytes
.extern OutputByte
.extern asmerr
.extern Options
.extern ModuleInfo
.extern Parse_Pass


.SECTION .text
	.ALIGN	16

OrgDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 160
	inc	dword ptr [rbp+0x10]
	xor	ecx, ecx
	cmp	byte ptr [Options+0xC6+rip], 0
	jz	$_001
	mov	ecx, 2
$_001:	mov	byte ptr [rsp+0x20], cl
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x18]
	lea	rcx, [rbp+0x10]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_010
	imul	ecx, dword ptr [rbp+0x10], 24
	add	rcx, qword ptr [rbp+0x18]
	cmp	byte ptr [rcx], 0
	jz	$_002
	mov	rdx, qword ptr [rcx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_010

$_002:	cmp	qword ptr [CurrStruct+rip], 0
	jz	$_004
	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_003
	mov	ecx, dword ptr [rbp-0x68]
	call	SetStructCurrentOffset@PLT
	jmp	$_010

$_003:	jmp	$_009

$_004:	cmp	qword ptr [ModuleInfo+0x1F8+rip], 0
	jnz	$_005
	mov	ecx, 2034
	call	asmerr@PLT
	jmp	$_010

$_005:	cmp	dword ptr [StoreState+rip], 0
	jnz	$_006
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_006
	xor	r8d, r8d
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
$_006:	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rcx, qword ptr [rcx+0x68]
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_007
	cmp	qword ptr [rcx+0x28], 0
	jz	$_007
	mov	rdx, qword ptr [rcx+0x28]
	or	byte ptr [rdx+0x1B], 0x02
$_007:	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_008
	xor	r9d, r9d
	xor	r8d, r8d
	mov	edx, dword ptr [rbp-0x68]
	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	call	SetCurrOffset@PLT
	jmp	$_010

	jmp	$_009

$_008:	cmp	dword ptr [rbp-0x2C], 1
	jnz	$_009
	test	byte ptr [rbp-0x25], 0x01
	jnz	$_009
	mov	rcx, qword ptr [rbp-0x18]
	mov	edx, dword ptr [rcx+0x28]
	add	edx, dword ptr [rbp-0x68]
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	call	SetCurrOffset@PLT
	jmp	$_010

$_009:	mov	ecx, 2132
	call	asmerr@PLT
$_010:	leave
	ret

$_011:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rdi, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rsi, qword ptr [rdi+0x68]
	cmp	byte ptr [rsi+0x70], 0
	jnz	$_012
	mov	r9d, 1
	mov	r8d, 1
	mov	edx, dword ptr [rbp+0x28]
	mov	rcx, rdi
	call	SetCurrOffset@PLT
	jmp	$_020

$_012:	cmp	dword ptr [rsi+0x48], 1
	jz	$_013
	mov	edx, dword ptr [rbp+0x28]
	xor	ecx, ecx
	call	FillDataBytes@PLT
	jmp	$_020

$_013:	movzx	ebx, byte ptr [ModuleInfo+0x1CC+rip]
	lea	rcx, [NopLists+rip]
	mov	rsi, qword ptr [rcx+rbx*8]
	movzx	ebx, byte ptr [rsi]
	jmp	$_017

$_014:	mov	edi, 1
$_015:	cmp	edi, ebx
	ja	$_016
	mov	ecx, dword ptr [rsi+rdi]
	call	OutputByte@PLT
	inc	edi
	jmp	$_015

$_016:	sub	dword ptr [rbp+0x28], ebx
$_017:	cmp	dword ptr [rbp+0x28], ebx
	ja	$_014
	cmp	dword ptr [rbp+0x28], 0
	jz	$_020
	inc	rsi
	mov	edi, ebx
$_018:	cmp	edi, dword ptr [rbp+0x28]
	jle	$_019
	add	rsi, rdi
	dec	edi
	jmp	$_018

$_019:	cmp	edi, 0
	jle	$_020
	mov	ecx, dword ptr [rsi]
	call	OutputByte@PLT
	dec	edi
	inc	rsi
	jmp	$_019

$_020:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

AlignCurrOffset:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	call	GetCurrOffset@PLT
	mov	ecx, dword ptr [rbp+0x10]
	mov	edx, 1
	shl	edx, cl
	mov	ecx, edx
	cdq
	div	ecx
	test	edx, edx
	jz	$_021
	sub	ecx, edx
	call	$_011
$_021:	leave
	ret

AlignDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 160
	imul	ecx, dword ptr [rbp+0x10], 24
	add	rcx, qword ptr [rbp+0x18]
	jmp	$_033

$_022:	inc	dword ptr [rbp+0x10]
	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x68]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x18]
	lea	rcx, [rbp+0x10]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_023
	jmp	$_043

$_023:	cmp	dword ptr [rbp-0x2C], 0
	jnz	$_027
	mov	ecx, 1
$_024:	cmp	ecx, dword ptr [rbp-0x68]
	jge	$_025
	shl	ecx, 1
	jmp	$_024

$_025:	cmp	ecx, dword ptr [rbp-0x68]
	jz	$_026
	mov	edx, dword ptr [rbp-0x68]
	mov	ecx, 2063
	call	asmerr@PLT
	jmp	$_043

$_026:	jmp	$_031

$_027:	cmp	dword ptr [rbp-0x2C], -2
	jnz	$_030
	cmp	qword ptr [CurrStruct+rip], 0
	jz	$_028
	mov	rcx, qword ptr [CurrStruct+rip]
	mov	rcx, qword ptr [rcx+0x68]
	movzx	eax, byte ptr [rcx+0x10]
	mov	dword ptr [rbp-0x68], eax
	jmp	$_029

$_028:	call	GetCurrSegAlign@PLT
	mov	dword ptr [rbp-0x68], eax
$_029:	jmp	$_031

$_030:	mov	ecx, 2026
	call	asmerr@PLT
	jmp	$_043

$_031:	jmp	$_034

$_032:	mov	dword ptr [rbp-0x68], 2
	inc	dword ptr [rbp+0x10]
	jmp	$_034

$_033:	cmp	dword ptr [rcx+0x4], 514
	je	$_022
	cmp	dword ptr [rcx+0x4], 515
	jz	$_032
$_034:	imul	ecx, dword ptr [rbp+0x10], 24
	add	rcx, qword ptr [rbp+0x18]
	cmp	byte ptr [rcx], 0
	jz	$_035
	mov	rdx, qword ptr [rcx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_043

$_035:	cmp	qword ptr [CurrStruct+rip], 0
	jz	$_036
	mov	ecx, dword ptr [rbp-0x68]
	call	AlignInStruct@PLT
	jmp	$_043

$_036:	cmp	dword ptr [StoreState+rip], 0
	jnz	$_037
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_037
	xor	r8d, r8d
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
$_037:	call	GetCurrSegAlign@PLT
	cmp	eax, 0
	jg	$_038
	mov	ecx, 2034
	call	asmerr@PLT
	jmp	$_043

$_038:	cmp	dword ptr [rbp-0x68], eax
	jle	$_039
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_039
	mov	edx, dword ptr [rbp-0x68]
	mov	ecx, 2189
	call	asmerr@PLT
$_039:	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_040
	cmp	qword ptr [ModuleInfo+0x1F8+rip], 0
	jz	$_040
	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	mov	rcx, qword ptr [rcx+0x68]
	mov	rcx, qword ptr [rcx+0x28]
	test	rcx, rcx
	jz	$_040
	or	byte ptr [rcx+0x1B], 0x02
$_040:	call	GetCurrOffset@PLT
	mov	dword ptr [rbp-0x6C], eax
	cdq
	div	dword ptr [rbp-0x68]
	test	edx, edx
	jz	$_041
	sub	dword ptr [rbp-0x68], edx
	mov	ecx, dword ptr [rbp-0x68]
	call	$_011
$_041:	cmp	qword ptr [ModuleInfo+0x80+rip], 0
	jz	$_042
	xor	r8d, r8d
	mov	edx, dword ptr [rbp-0x6C]
	xor	ecx, ecx
	call	LstWrite@PLT
$_042:	xor	eax, eax
$_043:	leave
	ret


.SECTION .data
	.ALIGN	16

NopList16:
	.byte  0x03, 0x2E, 0x8B, 0xC0, 0x8B, 0xC0, 0x90

NopList32:
	.byte  0x07, 0x8D, 0xA4, 0x24, 0x00, 0x00, 0x00, 0x00
	.byte  0x8D, 0x80, 0x00, 0x00, 0x00, 0x00, 0x2E, 0x8D
	.byte  0x44, 0x20, 0x00, 0x8D, 0x44, 0x20, 0x00, 0x8D
	.byte  0x40, 0x00, 0x8B, 0xFF, 0x90

NopList64:
	.byte  0x07, 0x0F, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00
	.byte  0x66, 0x0F, 0x1F, 0x44, 0x00, 0x00, 0x0F, 0x1F
	.byte  0x44, 0x00, 0x00, 0x0F, 0x1F, 0x40, 0x00, 0x0F
	.byte  0x1F, 0x00, 0x66, 0x90, 0x90

NopLists:
	.quad  NopList16
	.quad  NopList32
	.quad  NopList64


.att_syntax prefix
