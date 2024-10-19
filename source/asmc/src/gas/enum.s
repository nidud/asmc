
.intel_syntax noprefix

.global EnumDirective
.global CurrEnum

.extern Tokenize
.extern RunLineQueue
.extern AddLineQueueX
.extern LstWrite
.extern GetCurrOffset
.extern EvalOperand
.extern LclAlloc
.extern asmerr
.extern ModuleInfo
.extern Parse_Pass
.extern NameSpace_


.SECTION .text
	.ALIGN	16

EnumDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 312
	cmp	dword ptr [Parse_Pass+rip], 0
	jbe	$_001
	xor	eax, eax
	jmp	$_043

$_001:	mov	dword ptr [rbp-0x74], 0
	mov	rbx, rdx
	mov	rsi, qword ptr [CurrEnum+rip]
	mov	eax, dword ptr [rbx+0x4]
	jmp	$_019

$_002:	mov	rdi, rsi
	mov	ecx, 104
	call	LclAlloc@PLT
	mov	rsi, rax
	mov	qword ptr [CurrEnum+rip], rax
	mov	qword ptr [rsi], rdi
	mov	qword ptr [rsi+0x8], 0
	mov	dword ptr [rsi+0x28], 0
	mov	dword ptr [rsi+0x50], 4
	mov	byte ptr [rsi+0x19], 67
	mov	dword ptr [rsi+0x58], 0
	cmp	dword ptr [rbx+0x4], 412
	jnz	$_003
	inc	dword ptr [rsi+0x58]
$_003:	add	rbx, 24
	inc	dword ptr [rbp+0x28]
	cmp	byte ptr [rbx], 0
	je	$_017
	cmp	byte ptr [rbx], 9
	jnz	$_005
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rsi+0x8], rax
	mov	rax, qword ptr [rbx+0x10]
	add	rbx, 24
	inc	dword ptr [rbp+0x28]
	cmp	byte ptr [rax], 123
	jnz	$_004
	cmp	byte ptr [rax+0x1], 0
	jz	$_004
	inc	rax
	xor	r9d, r9d
	mov	r8, rbx
	xor	edx, edx
	mov	rcx, rax
	call	Tokenize@PLT
	add	dword ptr [ModuleInfo+0x220+rip], eax
$_004:	jmp	$_016

$_005:	mov	dword ptr [rbp-0x7C], 211
	mov	rdx, qword ptr [rbx+0x8]
	mov	rax, qword ptr [rbx+0x8]
	call	NameSpace_@PLT
	mov	qword ptr [rbp-0x8], rax
	add	rbx, 24
	inc	dword ptr [rbp+0x28]
	cmp	byte ptr [rbx], 58
	jne	$_015
	add	rbx, 24
	inc	dword ptr [rbp+0x28]
	mov	ecx, dword ptr [rbp+0x28]
	inc	ecx
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x70]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	mov	dword ptr [rbp-0x74], eax
	cmp	eax, -1
	jz	$_015
	mov	eax, dword ptr [rbp-0x70]
	mov	dword ptr [rsi+0x50], eax
	add	rbx, 24
	cmp	dword ptr [rsi+0x58], 0
	jnz	$_015
	test	byte ptr [rbp-0x30], 0x40
	jz	$_010
	jmp	$_008

$_006:	mov	dword ptr [rbp-0x7C], 208
	mov	byte ptr [rsi+0x19], 65
	jmp	$_009

$_007:	mov	dword ptr [rbp-0x7C], 206
	mov	byte ptr [rsi+0x19], 64
	jmp	$_009

$_008:	cmp	eax, 2
	jz	$_006
	cmp	eax, 1
	jz	$_007
$_009:	jmp	$_015

$_010:	jmp	$_014

$_011:	mov	dword ptr [rbp-0x7C], 210
	mov	byte ptr [rsi+0x19], 3
	jmp	$_015

$_012:	mov	dword ptr [rbp-0x7C], 207
	mov	byte ptr [rsi+0x19], 1
	jmp	$_015

$_013:	mov	dword ptr [rbp-0x7C], 205
	mov	byte ptr [rsi+0x19], 0
	jmp	$_015

$_014:	cmp	eax, 4
	jz	$_011
	cmp	eax, 2
	jz	$_012
	cmp	eax, 1
	jz	$_013
$_015:	mov	r8d, dword ptr [rbp-0x7C]
	mov	rdx, qword ptr [rbp-0x8]
	lea	rcx, [DS0000+rip]
	call	AddLineQueueX@PLT
$_016:	cmp	byte ptr [rbx], 9
	jnz	$_017
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rsi+0x8], rax
	mov	rax, qword ptr [rbx+0x10]
	add	rbx, 24
	inc	dword ptr [rbp+0x28]
	cmp	byte ptr [rax], 123
	jnz	$_017
	cmp	byte ptr [rax+0x1], 0
	jz	$_017
	inc	rax
	xor	r9d, r9d
	mov	r8, rbx
	xor	edx, edx
	mov	rcx, rax
	call	Tokenize@PLT
	add	dword ptr [ModuleInfo+0x220+rip], eax
$_017:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_018
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_018:	jmp	$_020

$_019:	cmp	eax, 411
	je	$_002
	cmp	eax, 412
	je	$_002
$_020:	jmp	$_039

$_021:	mov	rcx, qword ptr [rbx+0x8]
	add	rbx, 24
	cmp	byte ptr [rbx-0x18], 9
	jnz	$_022
	cmp	word ptr [rcx], 125
	jnz	$_022
	mov	rax, qword ptr [rsi]
	mov	qword ptr [CurrEnum+rip], rax
	jmp	$_040

$_022:	mov	qword ptr [rbp-0x8], rcx
	inc	dword ptr [rbp+0x28]
	mov	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rbp-0x70], eax
	add	dword ptr [rsi+0x28], 1
	mov	edi, 1
	cmp	byte ptr [rbx], 3
	jne	$_033
	cmp	dword ptr [rbx+0x4], 523
	jne	$_033
	add	rbx, 24
	inc	dword ptr [rbp+0x28]
	mov	ecx, dword ptr [rbp+0x28]
	mov	rdx, rbx
$_023:	cmp	ecx, dword ptr [ModuleInfo+0x220+rip]
	jge	$_025
	cmp	byte ptr [rdx], 44
	jz	$_025
	cmp	byte ptr [rdx], 0
	jz	$_025
	cmp	byte ptr [rdx], 9
	jnz	$_024
	mov	rax, qword ptr [rdx+0x8]
	cmp	word ptr [rax], 125
	jz	$_025
$_024:	inc	ecx
	add	rdx, 24
	jmp	$_023

$_025:	cmp	rdx, rbx
	je	$_040
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x70]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	mov	dword ptr [rbp-0x74], eax
	cmp	eax, -1
	je	$_040
	cmp	dword ptr [rbp-0x34], 0
	jz	$_026
	mov	ecx, 2026
	call	asmerr@PLT
	mov	dword ptr [rbp-0x74], eax
	jmp	$_040

$_026:	cmp	byte ptr [rbx], 45
	jnz	$_027
	cmp	byte ptr [rbx+0x18], 10
	jnz	$_027
	cmp	byte ptr [rbx+0x19], 10
	jnz	$_027
	xor	edi, edi
$_027:	mov	ecx, 1
	mov	eax, dword ptr [rbp-0x70]
	test	eax, 0xFFFF0000
	jz	$_028
	mov	ecx, 4
	jmp	$_029

$_028:	test	eax, 0xFF00
	jz	$_029
	mov	ecx, 2
$_029:	mov	edx, dword ptr [rbp-0x6C]
	test	edx, edx
	jnz	$_030
	cmp	ecx, dword ptr [rsi+0x50]
	jbe	$_032
$_030:	cmp	edx, -1
	jnz	$_031
	or	byte ptr [rbp-0x6D], 0xFFFFFF80
	jmp	$_032

$_031:	mov	ecx, 2071
	call	asmerr@PLT
	mov	dword ptr [rbp-0x74], eax
	jmp	$_040

$_032:	add	eax, 1
	mov	dword ptr [rsi+0x28], eax
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
$_033:	cmp	byte ptr [rbx], 44
	jnz	$_034
	add	rbx, 24
	inc	dword ptr [rbp+0x28]
	jmp	$_035

$_034:	cmp	byte ptr [rbx], 0
	jnz	$_035
	cmp	qword ptr [rsi+0x8], 0
	jnz	$_035
	mov	rax, qword ptr [rsi]
	mov	qword ptr [CurrEnum+rip], rax
$_035:	mov	eax, dword ptr [rbp-0x70]
	cmp	dword ptr [rsi+0x58], 0
	jz	$_036
	mul	dword ptr [rsi+0x50]
$_036:	test	edi, edi
	jz	$_037
	lea	rcx, [DS0001+rip]
	jmp	$_038

$_037:	lea	rcx, [DS0002+rip]
$_038:	mov	r8d, eax
	mov	rdx, qword ptr [rbp-0x8]
	call	AddLineQueueX@PLT
$_039:	cmp	byte ptr [rbx], 0
	jne	$_021
$_040:	cmp	byte ptr [rbx], 0
	jz	$_041
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_043

$_041:	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_042
	mov	rsi, qword ptr [CurrEnum+rip]
	mov	qword ptr [CurrEnum+rip], 0
	call	RunLineQueue@PLT
	mov	qword ptr [CurrEnum+rip], rsi
$_042:	mov	eax, dword ptr [rbp-0x74]
$_043:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

CurrEnum:
	.quad  0x0000000000000000

DS0000:
	.byte  0x25, 0x73, 0x20, 0x74, 0x79, 0x70, 0x65, 0x64
	.byte  0x65, 0x66, 0x20, 0x25, 0x72, 0x00

DS0001:
	.byte  0x25, 0x73, 0x20, 0x65, 0x71, 0x75, 0x20, 0x30
	.byte  0x78, 0x25, 0x78, 0x00

DS0002:
	.byte  0x25, 0x73, 0x20, 0x65, 0x71, 0x75, 0x20, 0x25
	.byte  0x64, 0x00


.att_syntax prefix
