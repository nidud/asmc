
.intel_syntax noprefix

.global ReturnDirective

.extern CreateFloat
.extern HllContinueIf
.extern ExpandHllProc
.extern ExpandCStrings
.extern GetLabelStr
.extern RunLineQueue
.extern AddLineQueueX
.extern AddLineQueue
.extern LstWrite
.extern GetCurrOffset
.extern EvalOperand
.extern SizeFromRegister
.extern SizeFromMemtype
.extern SpecialTable
.extern LclAlloc
.extern CurrProc
.extern tstrcpy
.extern tstrlen
.extern asmerr
.extern ModuleInfo


.SECTION .text
	.ALIGN	16

$_001:	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	imul	ebx, dword ptr [rcx], 24
	add	rbx, rdx
	mov	rcx, r8
	xor	esi, esi
	xor	edi, edi
	xor	edx, edx
	mov	qword ptr [rcx], rdx
	mov	al, byte ptr [rbx]
	test	al, al
	jz	$_012
	cmp	al, 6
	jnz	$_002
	cmp	byte ptr [rbx+0x18], 40
	jnz	$_002
	mov	al, 40
	mov	qword ptr [rcx], rbx
	add	rbx, 24
	mov	rcx, qword ptr [rbp+0x28]
	inc	dword ptr [rcx]
$_002:	cmp	al, 3
	jnz	$_003
	inc	esi
	jmp	$_012

$_003:	mov	rdi, rbx
	inc	edx
	add	rbx, 24
	cmp	al, 40
	jnz	$_009
	mov	ecx, 1
	mov	al, byte ptr [rbx]
$_004:	test	al, al
	jz	$_007
	cmp	al, 40
	jnz	$_005
	inc	ecx
	jmp	$_006

$_005:	cmp	al, 41
	jnz	$_006
	dec	ecx
	jz	$_007
$_006:	add	rbx, 24
	mov	al, byte ptr [rbx]
	inc	edx
	jmp	$_004

$_007:	cmp	al, 41
	jnz	$_008
	inc	edx
	add	rbx, 24
$_008:	jmp	$_011

$_009:	mov	al, byte ptr [rbx]
$_010:	test	al, al
	jz	$_011
	cmp	al, 3
	jz	$_011
	add	rbx, 24
	mov	al, byte ptr [rbx]
	inc	edx
	jmp	$_010

$_011:	mov	al, byte ptr [rbx]
	cmp	al, 3
	jnz	$_012
	inc	esi
$_012:	mov	rax, qword ptr [rbp+0x40]
	mov	dword ptr [rax], edx
	mov	rax, rbx
	mov	rbx, qword ptr [rbp+0x48]
	mov	dword ptr [rbx], esi
	mov	rbx, qword ptr [rbp+0x50]
	mov	dword ptr [rbx], edi
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_013:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 440
	mov	rsi, rcx
	imul	ebx, dword ptr [rsi], 24
	add	rbx, rdx
	lea	rdi, [rbp-0x178]
	mov	eax, dword ptr [ModuleInfo+0x340+rip]
	mov	dword ptr [rbp-0x6C], eax
	mov	dword ptr [rbp-0x70], 682
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rsi]
	mov	rcx, rdi
	call	ExpandHllProc@PLT
	cmp	eax, -1
	jz	$_014
	cmp	byte ptr [rdi], 0
	jz	$_014
	mov	rcx, rdi
	call	AddLineQueue@PLT
	lea	rax, [rbp-0x74]
	mov	qword ptr [rsp+0x28], rax
	lea	rax, [rbp-0x78]
	mov	qword ptr [rsp+0x20], rax
	lea	r9, [rbp+0x40]
	lea	r8, [rbp+0x38]
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, rsi
	call	$_001
$_014:	cmp	dword ptr [rbp+0x40], 0
	jz	$_015
	imul	eax, dword ptr [rbp+0x40], 24
	mov	rcx, qword ptr [rbx+rax+0x10]
	sub	rcx, qword ptr [rbx+0x10]
	mov	rdx, rsi
	mov	rsi, qword ptr [rbx+0x10]
	mov	rax, rdi
	rep movsb
	mov	byte ptr [rdi], 0
	mov	rdi, rax
	mov	rsi, rdx
	jmp	$_016

$_015:	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rdi
	call	tstrcpy@PLT
$_016:	mov	byte ptr [rbp-0x179], 0
	mov	ecx, dword ptr [rsi]
	add	ecx, dword ptr [rbp+0x40]
	cmp	byte ptr [rbx], 40
	jnz	$_024
	cmp	byte ptr [rbx+0x18], 38
	jnz	$_024
	jmp	$_018

$_017:	inc	rdi
$_018:	cmp	byte ptr [rdi], 38
	jnz	$_017
	inc	rdi
	mov	rdx, rdi
$_019:	cmp	byte ptr [rdx], 0
	jz	$_020
	inc	rdx
	jmp	$_019

$_020:	jmp	$_022

$_021:	mov	byte ptr [rdx-0x1], 0
	dec	rdx
$_022:	cmp	byte ptr [rdx-0x1], 32
	jbe	$_021
	cmp	byte ptr [rdx-0x1], 41
	jnz	$_023
	mov	byte ptr [rdx-0x1], 0
$_023:	inc	byte ptr [rbp-0x179]
	add	dword ptr [rsi], 2
	jmp	$_025

$_024:	cmp	byte ptr [rdi], 38
	jnz	$_025
	inc	rdi
	inc	byte ptr [rbp-0x179]
	inc	dword ptr [rsi]
$_025:	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x68]
	mov	r8d, ecx
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, rsi
	call	EvalOperand@PLT
	test	eax, eax
	jne	$_075
	mov	esi, 1
	cmp	byte ptr [rbp-0x179], 0
	jz	$_026
	mov	dword ptr [rbp-0x70], 711
	jmp	$_074

$_026:	cmp	dword ptr [rbp-0x2C], 0
	jne	$_032
	mov	rdx, qword ptr [rbp-0x58]
	test	rdx, rdx
	jz	$_027
	cmp	byte ptr [rdx], 9
	jnz	$_027
	mov	r8, qword ptr [rdx+0x8]
	mov	edx, dword ptr [rbp-0x6C]
	lea	rcx, [DS0000+rip]
	call	AddLineQueueX@PLT
	dec	esi
	jmp	$_031

$_027:	mov	eax, dword ptr [rbp-0x68]
	mov	edx, dword ptr [rbp-0x64]
	test	edx, edx
	jnz	$_029
	cmp	eax, 0
	jle	$_029
	mov	ecx, dword ptr [rbp-0x6C]
	cmp	ecx, 115
	jnz	$_028
	mov	ecx, 17
$_028:	mov	r8d, eax
	mov	edx, ecx
	lea	rcx, [DS0001+rip]
	call	AddLineQueueX@PLT
	dec	esi
	jmp	$_031

$_029:	test	eax, eax
	jnz	$_031
	test	edx, edx
	jnz	$_031
	mov	eax, dword ptr [rbp-0x6C]
	cmp	eax, 115
	jnz	$_030
	mov	eax, 17
$_030:	mov	r8d, eax
	mov	edx, eax
	lea	rcx, [DS0002+rip]
	call	AddLineQueueX@PLT
	dec	esi
$_031:	jmp	$_074

$_032:	cmp	dword ptr [rbp-0x2C], 2
	jnz	$_040
	test	byte ptr [rbp-0x25], 0x01
	jnz	$_040
	mov	rbx, qword ptr [rbp-0x50]
	mov	eax, dword ptr [rbx+0x4]
	cmp	eax, 17
	jz	$_033
	cmp	eax, 115
	jnz	$_034
$_033:	dec	esi
	jmp	$_039

$_034:	mov	ecx, eax
	call	SizeFromRegister@PLT
	jmp	$_038

$_035:	mov	dword ptr [rbp-0x6C], 9
	jmp	$_039

$_036:	mov	dword ptr [rbp-0x6C], 17
	jmp	$_039

$_037:	mov	dword ptr [rbp-0x6C], 115
	jmp	$_039

$_038:	cmp	rax, 2
	jz	$_035
	cmp	rax, 4
	jz	$_036
	cmp	rax, 8
	jz	$_037
$_039:	jmp	$_074

$_040:	cmp	dword ptr [rbp-0x2C], 3
	jne	$_060
	cmp	qword ptr [rbp+0x38], 0
	jnz	$_049
	cmp	byte ptr [rbx], 11
	jnz	$_041
	cmp	byte ptr [rbx+0x1], 0
	jnz	$_042
$_041:	cmp	byte ptr [rbx], 40
	jnz	$_049
	cmp	byte ptr [rbx+0x18], 11
	jnz	$_049
	cmp	byte ptr [rbx+0x19], 0
	jz	$_049
	cmp	byte ptr [rbx+0x30], 41
	jnz	$_049
$_042:	cmp	byte ptr [rbx], 40
	jnz	$_043
	mov	rbx, qword ptr [rbx+0x20]
	jmp	$_044

$_043:	mov	rbx, qword ptr [rbx+0x8]
$_044:	mov	rcx, rbx
	call	tstrlen@PLT
	dec	rax
	shr	eax, 1
	jmp	$_047

$_045:	cmp	byte ptr [rbx], 48
	jnz	$_046
	dec	eax
$_046:	jmp	$_048

$_047:	cmp	eax, 3
	jz	$_045
	cmp	eax, 5
	jz	$_045
	cmp	eax, 9
	jz	$_045
	cmp	eax, 11
	jz	$_045
	cmp	eax, 17
	jz	$_045
$_048:	jmp	$_052

$_049:	mov	rdx, qword ptr [rbp+0x38]
	test	rdx, rdx
	jz	$_050
	mov	ecx, dword ptr [rdx+0x4]
	lea	r11, [SpecialTable+rip]
	imul	eax, ecx, 12
	mov	al, byte ptr [r11+rax+0xA]
	jmp	$_051

$_050:	mov	al, byte ptr [rbp-0x28]
$_051:	xor	r8d, r8d
	mov	edx, 254
	movzx	ecx, al
	call	SizeFromMemtype@PLT
$_052:	jmp	$_058

$_053:	mov	rdx, rdi
	lea	rcx, [DS0003+rip]
	call	AddLineQueueX@PLT
	jmp	$_075

$_054:	mov	dword ptr [rbp-0x70], 1050
	jmp	$_059

$_055:	mov	dword ptr [rbp-0x70], 612
	jmp	$_059

$_056:	lea	r8, [rbp-0x178]
	lea	rdx, [rbp-0x68]
	mov	ecx, 10
	call	CreateFloat@PLT
	lea	rdx, [rbp-0x178]
	lea	rcx, [DS0004+rip]
	call	AddLineQueueX@PLT
	jmp	$_075

$_057:	mov	dword ptr [rbp-0x70], 1030
	jmp	$_059

$_058:	cmp	eax, 2
	jz	$_053
	cmp	eax, 4
	jz	$_054
	cmp	eax, 8
	jz	$_055
	cmp	eax, 10
	jz	$_056
	cmp	eax, 16
	jz	$_057
$_059:	mov	dword ptr [rbp-0x6C], 40
	lea	rdi, [rbp-0x178]
	mov	ecx, eax
	mov	r8, rdi
	lea	rdx, [rbp-0x68]
	call	CreateFloat@PLT
	jmp	$_074

$_060:	cmp	dword ptr [rbp-0x2C], 1
	jne	$_073
	mov	al, byte ptr [rbp-0x28]
	jmp	$_071

$_061:	mov	dword ptr [rbp-0x70], 719
	cmp	dword ptr [rbp-0x6C], 115
	jnz	$_062
	mov	dword ptr [rbp-0x6C], 17
$_062:	jmp	$_072

$_063:	cmp	dword ptr [rbp-0x6C], 9
	jz	$_064
	mov	dword ptr [rbp-0x70], 718
	mov	dword ptr [rbp-0x6C], 17
$_064:	jmp	$_072

$_065:	mov	dword ptr [rbp-0x6C], 17
	jmp	$_072

$_066:	cmp	dword ptr [rbp-0x6C], 115
	jne	$_072
	mov	r8, rdi
	mov	rdx, rdi
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
	jmp	$_075

$_067:	mov	dword ptr [rbp-0x6C], 9
	jmp	$_072

$_068:	mov	dword ptr [rbp-0x6C], 40
	mov	dword ptr [rbp-0x70], 1050
	jmp	$_072

$_069:	mov	dword ptr [rbp-0x6C], 40
	mov	dword ptr [rbp-0x70], 612
	jmp	$_072

$_070:	mov	dword ptr [rbp-0x6C], 40
	mov	dword ptr [rbp-0x70], 1030
	jmp	$_072

$_071:	cmp	al, 0
	je	$_061
	cmp	al, 64
	je	$_061
	cmp	al, 1
	je	$_061
	cmp	al, 65
	je	$_063
	cmp	al, 3
	je	$_065
	cmp	al, 67
	je	$_065
	cmp	al, 15
	je	$_066
	cmp	al, 79
	je	$_066
	cmp	al, 33
	jz	$_067
	cmp	al, 35
	jz	$_068
	cmp	al, 39
	jz	$_069
	cmp	al, 47
	jz	$_070
$_072:	jmp	$_074

$_073:	cmp	dword ptr [rbp-0x2C], -2
	jnz	$_074
	cmp	byte ptr [rdi], 123
	jnz	$_074
	mov	rdx, rdi
	lea	rcx, [DS0006+rip]
	call	AddLineQueueX@PLT
	xor	esi, esi
$_074:	test	esi, esi
	jz	$_075
	mov	r9, rdi
	mov	r8d, dword ptr [rbp-0x6C]
	mov	edx, dword ptr [rbp-0x70]
	lea	rcx, [DS0007+rip]
	call	AddLineQueueX@PLT
$_075:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ReturnDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 200
	cmp	qword ptr [CurrProc+rip], 0
	jnz	$_076
	mov	ecx, 2012
	call	asmerr@PLT
	jmp	$_085

$_076:	mov	rsi, qword ptr [ModuleInfo+0x110+rip]
	test	rsi, rsi
	jnz	$_077
	mov	ecx, 56
	call	LclAlloc@PLT
	mov	rsi, rax
	mov	qword ptr [ModuleInfo+0x110+rip], rax
	xor	eax, eax
	mov	qword ptr [rsi], rax
	mov	dword ptr [rsi+0x18], eax
	mov	dword ptr [rsi+0x10], eax
	mov	qword ptr [rsi+0x20], rax
	mov	qword ptr [rsi+0x8], rax
	mov	dword ptr [rsi+0x28], 5
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x14], eax
$_077:	mov	rcx, qword ptr [rbp+0x30]
	call	ExpandCStrings@PLT
	inc	dword ptr [rbp+0x28]
	lea	rdi, [rbp-0x94]
	lea	rax, [rbp-0x8]
	mov	qword ptr [rsp+0x28], rax
	lea	rax, [rbp-0x14]
	mov	qword ptr [rsp+0x20], rax
	lea	r9, [rbp-0x4]
	lea	r8, [rbp-0x10]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	$_001
	mov	rdx, rdi
	mov	ecx, dword ptr [rsi+0x14]
	call	GetLabelStr@PLT
	cmp	dword ptr [rbp-0x14], 0
	je	$_080
	cmp	dword ptr [rbp-0x8], 0
	je	$_078
	mov	ebx, dword ptr [rbp+0x28]
	mov	eax, dword ptr [rbp-0x4]
	add	dword ptr [rbp+0x28], eax
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	dword ptr [rsi+0x18], eax
	mov	dword ptr [rsp+0x28], 0
	mov	qword ptr [rsp+0x20], rsi
	mov	r9d, 2
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp+0x28]
	mov	rcx, rsi
	call	HllContinueIf@PLT
	mov	dword ptr [rbp+0x28], ebx
	mov	r9d, dword ptr [rbp-0x4]
	mov	r8, qword ptr [rbp-0x10]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	$_013
	mov	rdx, rdi
	lea	rcx, [DS0008+rip]
	call	AddLineQueueX@PLT
	mov	rdx, rdi
	mov	ecx, dword ptr [rsi+0x18]
	call	GetLabelStr@PLT
	mov	rdx, rax
	lea	rcx, [DS0009+rip]
	call	AddLineQueueX@PLT
	jmp	$_079

$_078:	mov	eax, dword ptr [rbp-0x4]
	add	dword ptr [rbp+0x28], eax
	mov	dword ptr [rsp+0x28], 1
	mov	qword ptr [rsp+0x20], rsi
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp+0x28]
	mov	rcx, rsi
	call	HllContinueIf@PLT
$_079:	jmp	$_082

$_080:	cmp	dword ptr [rbp-0x8], 0
	jz	$_081
	mov	r9d, dword ptr [rbp-0x4]
	mov	r8, qword ptr [rbp-0x10]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	$_013
$_081:	mov	rdx, rdi
	lea	rcx, [DS0008+rip]
	call	AddLineQueueX@PLT
$_082:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_083
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_083:	cmp	qword ptr [ModuleInfo+0xC8+rip], 0
	jz	$_084
	call	RunLineQueue@PLT
$_084:	xor	eax, eax
$_085:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x20, 0x6C, 0x65, 0x61, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x40, 0x43, 0x53, 0x74, 0x72, 0x28, 0x25
	.byte  0x73, 0x29, 0x00

DS0001:
	.byte  0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C, 0x25
	.byte  0x64, 0x00

DS0002:
	.byte  0x78, 0x6F, 0x72, 0x20, 0x25, 0x72, 0x2C, 0x25
	.byte  0x72, 0x00

DS0003:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x61, 0x78, 0x2C
	.byte  0x20, 0x25, 0x73, 0x0A, 0x20, 0x6D, 0x6F, 0x76
	.byte  0x64, 0x20, 0x78, 0x6D, 0x6D, 0x30, 0x2C, 0x20
	.byte  0x65, 0x61, 0x78, 0x00

DS0004:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x61, 0x70, 0x73, 0x20
	.byte  0x78, 0x6D, 0x6D, 0x30, 0x2C, 0x20, 0x78, 0x6D
	.byte  0x6D, 0x77, 0x6F, 0x72, 0x64, 0x20, 0x70, 0x74
	.byte  0x72, 0x20, 0x25, 0x73, 0x00

DS0005:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x72, 0x61, 0x78
	.byte  0x2C, 0x20, 0x71, 0x77, 0x6F, 0x72, 0x64, 0x20
	.byte  0x70, 0x74, 0x72, 0x20, 0x25, 0x73, 0x0A, 0x20
	.byte  0x6D, 0x6F, 0x76, 0x20, 0x72, 0x64, 0x78, 0x2C
	.byte  0x20, 0x71, 0x77, 0x6F, 0x72, 0x64, 0x20, 0x70
	.byte  0x74, 0x72, 0x20, 0x25, 0x73, 0x5B, 0x38, 0x5D
	.byte  0x00

DS0006:
	.byte  0x6D, 0x6F, 0x76, 0x61, 0x70, 0x73, 0x20, 0x78
	.byte  0x6D, 0x6D, 0x30, 0x2C, 0x25, 0x73, 0x00

DS0007:
	.byte  0x25, 0x72, 0x20, 0x25, 0x72, 0x2C, 0x25, 0x73
	.byte  0x00

DS0008:
	.byte  0x6A, 0x6D, 0x70, 0x20, 0x25, 0x73, 0x00

DS0009:
	.byte  0x25, 0x73, 0x3A, 0x00


.att_syntax prefix
