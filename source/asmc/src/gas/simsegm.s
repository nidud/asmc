
.intel_syntax noprefix

.global SimGetSegName
.global GetCodeClass
.global SimplifiedSegDir
.global SetModelDefaultSegNames
.global ModelSimSegmInit
.global ModelSimSegmExit

.extern LstWrite
.extern EvalOperand
.extern RunLineQueue
.extern AddLineQueueX
.extern AddLineQueue
.extern SpecialTable
.extern LclDup
.extern LclAlloc
.extern tstrcat
.extern tstrcpy
.extern tstrlen
.extern tmemcpy
.extern tsprintf
.extern asmerr
.extern szDgroup
.extern Options
.extern ModuleInfo
.extern Parse_Pass
.extern SymFind


.SECTION .text
	.ALIGN	16

SimGetSegName:
	lea	rax, [SegmNames+rip]
	mov	rax, qword ptr [rax+rcx*8]
	ret

GetCodeClass:
	cmp	qword ptr [Options+0x50+rip], 0
	jz	$_001
	mov	rax, qword ptr [Options+0x50+rip]
	jmp	$_002

$_001:	lea	rax, [SegmClass+rip]
	mov	rax, qword ptr [rax]
$_002:	ret

$_003:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	cmp	byte ptr [ModuleInfo+0x1B5+rip], 7
	jz	$_004
	cmp	dword ptr [Options+0xA4+rip], 2
	jz	$_004
	cmp	dword ptr [Options+0xA4+rip], 3
	jnz	$_005
$_004:	jmp	$_007

$_005:	test	rdx, rdx
	jnz	$_006
	lea	rdx, [SegmNames+rip]
	mov	rdx, qword ptr [rdx+rcx*8]
$_006:	mov	r9, rdx
	mov	r8d, 518
	lea	rdx, [szDgroup+rip]
	lea	rcx, [DS000A+rip]
	call	AddLineQueueX@PLT
$_007:	leave
	ret

$_008:
	sub	rsp, 40
	mov	rcx, qword ptr [ModuleInfo+0x1F8+rip]
	test	rcx, rcx
	jz	$_009
	mov	r8d, 517
	mov	rdx, qword ptr [rcx+0x8]
	lea	rcx, [DS000B+rip]
	call	AddLineQueueX@PLT
$_009:	add	rsp, 40
	ret

$_010:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 136
	lea	rax, [DS0011+0x1+rip]
	mov	qword ptr [rbp-0x8], rax
	lea	rax, [DS000D+rip]
	mov	qword ptr [rbp-0x10], rax
	lea	rax, [DS0016+0x4+rip]
	mov	qword ptr [rbp-0x18], rax
	cmp	byte ptr [Options+0xCD+rip], 4
	jz	$_011
	mov	edx, 1
	mov	cl, byte ptr [Options+0xCD+rip]
	shl	edx, cl
	mov	r8d, edx
	lea	rdx, [DS000E+rip]
	lea	rcx, [rbp-0x28]
	call	tsprintf@PLT
	lea	rax, [rbp-0x28]
	mov	qword ptr [rbp-0x10], rax
$_011:	cmp	byte ptr [ModuleInfo+0x1CD+rip], 0
	jbe	$_017
	cmp	byte ptr [ModuleInfo+0x1B5+rip], 7
	jnz	$_012
	lea	rax, [DS000F+rip]
	mov	qword ptr [rbp-0x18], rax
	jmp	$_013

$_012:	lea	rax, [DS0010+rip]
	mov	qword ptr [rbp-0x18], rax
$_013:	mov	eax, dword ptr [ModuleInfo+0x1C0+rip]
	and	eax, 0xF0
	cmp	byte ptr [Options+0xCD+rip], 4
	jz	$_014
	lea	rax, [rbp-0x28]
	mov	qword ptr [rbp-0x8], rax
	jmp	$_016

$_014:	cmp	eax, 48
	ja	$_015
	lea	rax, [DS0011+rip]
	mov	qword ptr [rbp-0x8], rax
	jmp	$_016

$_015:	lea	rax, [DS000D+rip]
	mov	qword ptr [rbp-0x8], rax
$_016:	mov	rax, qword ptr [rbp-0x8]
	mov	qword ptr [rbp-0x10], rax
$_017:	mov	esi, dword ptr [rbp+0x28]
	test	esi, esi
	jnz	$_018
	call	GetCodeClass
	mov	qword ptr [rbp-0x40], rax
	jmp	$_019

$_018:	lea	rcx, [SegmClass+rip]
	mov	rax, qword ptr [rcx+rsi*8]
	mov	qword ptr [rbp-0x40], rax
$_019:	cmp	esi, 1
	jz	$_020
	cmp	esi, 4
	jz	$_020
	cmp	esi, 5
	jnz	$_021
$_020:	mov	rax, qword ptr [rbp-0x10]
	mov	qword ptr [rbp-0x8], rax
$_021:	lea	rax, [DS0012+rip]
	mov	qword ptr [rbp-0x38], rax
	mov	rdi, qword ptr [rbp+0x30]
	test	rdi, rdi
	jnz	$_025
	lea	rcx, [SegmNames+rip]
	mov	rdi, qword ptr [rcx+rsi*8]
	mov	ebx, 1
	mov	ecx, esi
	shl	ebx, cl
	test	byte ptr [ModuleInfo+0x1E3+rip], bl
	jz	$_022
	lea	rax, [DS000B+rip]
	mov	qword ptr [rbp-0x38], rax
	jmp	$_024

$_022:	or	byte ptr [ModuleInfo+0x1E3+rip], bl
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_023
	mov	rcx, rdi
	call	SymFind@PLT
	test	rax, rax
	jz	$_023
	cmp	byte ptr [rax+0x18], 3
	jnz	$_023
	test	byte ptr [rax+0x14], 0x02
	jz	$_023
	or	byte ptr [ModuleInfo+0x1EC+rip], bl
$_023:	test	byte ptr [ModuleInfo+0x1EC+rip], bl
	jz	$_024
	lea	rax, [DS000B+rip]
	mov	qword ptr [rbp-0x38], rax
$_024:	jmp	$_026

$_025:	mov	rcx, rdi
	call	SymFind@PLT
	test	rax, rax
	jz	$_026
	cmp	byte ptr [rax+0x18], 3
	jnz	$_026
	test	byte ptr [rax+0x14], 0x02
	jz	$_026
	lea	rax, [DS000B+rip]
	mov	qword ptr [rbp-0x38], rax
$_026:	lea	rax, [SegmCombine+rip]
	mov	rcx, qword ptr [rax+rsi*8]
	mov	rax, qword ptr [rbp-0x40]
	mov	qword ptr [rsp+0x30], rax
	mov	qword ptr [rsp+0x28], rcx
	mov	rax, qword ptr [rbp-0x18]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rbp-0x8]
	mov	r8d, 516
	mov	rdx, rdi
	mov	rcx, qword ptr [rbp-0x38]
	call	AddLineQueueX@PLT
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_027:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	lea	rax, [SegmNames+rip]
	mov	rdx, qword ptr [rax+rcx*8]
	mov	r8d, 517
	lea	rcx, [DS000B+rip]
	call	AddLineQueueX@PLT
	leave
	ret

$_028:
	mov	rax, rcx
	cmp	byte ptr [ModuleInfo+0x1B5+rip], 7
	jz	$_029
	cmp	dword ptr [Options+0xA4+rip], 2
	jz	$_029
	cmp	dword ptr [Options+0xA4+rip], 3
	jnz	$_031
$_029:	test	rax, rax
	jnz	$_030
	mov	rax, qword ptr [SegmNames+rip]
$_030:	jmp	$_032

$_031:	lea	rax, [szDgroup+rip]
$_032:	ret

SimplifiedSegDir:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 168
	cmp	byte ptr [ModuleInfo+0x1B5+rip], 0
	jnz	$_033
	mov	rax, -1
	jmp	$_060

$_033:	xor	r8d, r8d
	xor	edx, edx
	mov	ecx, 4
	call	LstWrite@PLT
	xor	edi, edi
	inc	dword ptr [rbp+0x28]
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbx-0x14], 12
	mov	esi, dword ptr [r11+rax+0x4]
	cmp	esi, 1
	jnz	$_037
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x70]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_034
	mov	rax, -1
	jmp	$_060

$_034:	cmp	dword ptr [rbp-0x34], -2
	jnz	$_035
	mov	dword ptr [rbp-0x70], 1024
	jmp	$_036

$_035:	cmp	dword ptr [rbp-0x34], 0
	jz	$_036
	mov	ecx, 2026
	call	asmerr@PLT
	mov	rax, -1
	jmp	$_060

$_036:	jmp	$_039

$_037:	cmp	byte ptr [rbx], 8
	jnz	$_039
	test	esi, esi
	jz	$_038
	cmp	esi, 4
	jz	$_038
	cmp	esi, 5
	jz	$_038
	cmp	byte ptr [Options+0xC6+rip], 0
	jnz	$_039
	cmp	esi, 2
	jz	$_038
	cmp	esi, 3
	jz	$_038
	cmp	esi, 6
	jnz	$_039
$_038:	mov	rdi, qword ptr [rbx+0x8]
	inc	dword ptr [rbp+0x28]
$_039:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 0
	jz	$_040
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_060

$_040:	cmp	esi, 1
	jz	$_041
	call	$_008
$_041:	test	rdi, rdi
	jnz	$_042
	mov	ecx, esi
	mov	edx, 1
	shl	edx, cl
	and	dl, byte ptr [ModuleInfo+0x1E3+rip]
	mov	byte ptr [rbp-0x1], dl
$_042:	jmp	$_058

$_043:	mov	rdx, rdi
	xor	ecx, ecx
	call	$_010
	cmp	byte ptr [ModuleInfo+0x1B5+rip], 1
	jnz	$_047
	test	rdi, rdi
	jz	$_045
	mov	rcx, rdi
	call	SymFind@PLT
	test	rax, rax
	jz	$_044
	cmp	byte ptr [rax+0x18], 3
	jnz	$_044
	mov	rax, qword ptr [rax+0x68]
	mov	al, byte ptr [rax+0x68]
	cmp	al, byte ptr [ModuleInfo+0x1CD+rip]
	jnz	$_044
	mov	rdx, rdi
	xor	ecx, ecx
	call	$_003
	mov	rcx, rdi
	call	$_028
	mov	rdi, rax
$_044:	jmp	$_046

$_045:	mov	rcx, rdi
	call	$_028
	mov	rdi, rax
$_046:	jmp	$_050

$_047:	cmp	byte ptr [ModuleInfo+0x1B5+rip], 7
	jnz	$_048
	lea	rdi, [DS000F+rip]
	jmp	$_050

$_048:	test	rdi, rdi
	jnz	$_049
	mov	rdi, qword ptr [SegmNames+rip]
$_049:	mov	rcx, rdi
	call	SymFind@PLT
	test	rax, rax
	jz	$_050
	cmp	byte ptr [rax+0x18], 3
	jnz	$_050
	mov	rax, qword ptr [rax+0x68]
	mov	rax, qword ptr [rax]
	test	rax, rax
	jz	$_050
	mov	rdi, qword ptr [rax+0x8]
$_050:	mov	rdx, rdi
	lea	rcx, [DS0013+rip]
	call	AddLineQueueX@PLT
	jmp	$_059

$_051:	xor	edx, edx
	mov	ecx, 1
	call	$_010
	mov	edx, dword ptr [rbp-0x70]
	lea	rcx, [DS0014+rip]
	call	AddLineQueueX@PLT
	mov	ecx, 1
	call	$_027
	cmp	byte ptr [rbp-0x1], 0
	jnz	$_052
	cmp	byte ptr [ModuleInfo+0x1B4+rip], 1
	jz	$_052
	xor	edx, edx
	mov	ecx, 1
	call	$_003
$_052:	jmp	$_059

$_053:	mov	rdx, rdi
	mov	ecx, esi
	call	$_010
	lea	rcx, [DS0015+rip]
	call	AddLineQueue@PLT
	test	rdi, rdi
	jnz	$_054
	cmp	byte ptr [rbp-0x1], 0
	jnz	$_055
$_054:	mov	rdx, rdi
	mov	ecx, esi
	call	$_003
$_055:	jmp	$_059

$_056:	mov	rdx, rdi
	mov	ecx, esi
	call	$_010
	lea	rcx, [DS0015+rip]
	call	AddLineQueue@PLT
	jmp	$_059

$_057:	jmp	$_059

$_058:	cmp	esi, 0
	je	$_043
	cmp	esi, 1
	je	$_051
	cmp	esi, 2
	jz	$_053
	cmp	esi, 3
	jz	$_053
	cmp	esi, 6
	jz	$_053
	cmp	esi, 4
	jz	$_056
	cmp	esi, 5
	jz	$_056
	jmp	$_057

$_059:	call	RunLineQueue@PLT
	xor	eax, eax
$_060:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

SetModelDefaultSegNames:
	push	rsi
	sub	rsp, 32
	mov	r8d, 56
	lea	rdx, [SegmNamesDef+rip]
	lea	rcx, [SegmNames+rip]
	call	tmemcpy@PLT
	cmp	qword ptr [Options+0x40+rip], 0
	jz	$_061
	mov	rcx, qword ptr [Options+0x40+rip]
	call	LclDup@PLT
	mov	qword ptr [SegmNames+rip], rax
	jmp	$_062

$_061:	mov	eax, 1
	mov	cl, byte ptr [ModuleInfo+0x1B5+rip]
	shl	eax, cl
	test	eax, 0x70
	jz	$_062
	mov	rcx, qword ptr [SegmNamesDef+rip]
	call	tstrlen@PLT
	mov	esi, eax
	lea	rcx, [ModuleInfo+0x230+rip]
	call	tstrlen@PLT
	add	esi, eax
	inc	esi
	mov	ecx, esi
	call	LclAlloc@PLT
	mov	qword ptr [SegmNames+rip], rax
	lea	rdx, [ModuleInfo+0x230+rip]
	mov	rcx, qword ptr [SegmNames+rip]
	call	tstrcpy@PLT
	mov	rdx, qword ptr [SegmNamesDef+rip]
	mov	rcx, qword ptr [SegmNames+rip]
	call	tstrcat@PLT
$_062:	cmp	qword ptr [Options+0x48+rip], 0
	jz	$_063
	mov	rcx, qword ptr [Options+0x48+rip]
	call	LclDup@PLT
	mov	qword ptr [SegmNames+0x10+rip], rax
$_063:	add	rsp, 32
	pop	rsi
	ret

ModelSimSegmInit:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 80
	mov	byte ptr [ModuleInfo+0x1E3+rip], 0
	xor	edx, edx
	xor	ecx, ecx
	call	$_010
	xor	ecx, ecx
	call	$_027
	xor	edx, edx
	mov	ecx, 2
	call	$_010
	mov	ecx, 2
	call	$_027
	cmp	dword ptr [rbp+0x10], 7
	je	$_066
	cmp	dword ptr [Options+0xA4+rip], 1
	jz	$_064
	cmp	dword ptr [Options+0xA4+rip], 0
	jnz	$_066
$_064:	lea	rdx, [DS000A+rip]
	lea	rcx, [rbp-0x14]
	call	tstrcpy@PLT
	cmp	dword ptr [rbp+0x10], 1
	jnz	$_065
	lea	rdx, [DS0016+rip]
	lea	rcx, [rbp-0x14]
	call	tstrcat@PLT
	mov	rax, qword ptr [SegmNames+0x10+rip]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [SegmNames+rip]
	mov	r8d, 518
	lea	rdx, [szDgroup+rip]
	lea	rcx, [rbp-0x14]
	call	AddLineQueueX@PLT
	jmp	$_066

$_065:	mov	r9, qword ptr [SegmNames+0x10+rip]
	mov	r8d, 518
	lea	rdx, [szDgroup+rip]
	lea	rcx, [rbp-0x14]
	call	AddLineQueueX@PLT
$_066:	xor	eax, eax
	leave
	ret

ModelSimSegmExit:
	sub	rsp, 40
	cmp	qword ptr [ModuleInfo+0x1F8+rip], 0
	jz	$_067
	call	$_008
	call	RunLineQueue@PLT
$_067:	add	rsp, 40
	ret


.SECTION .data
	.ALIGN	16

SegmNames:
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000
	.quad  0x0000000000000000

SegmNamesDef:
	.quad  DS0000
	.quad  DS0001
	.quad  DS0002
	.quad  DS0003
	.quad  DS0004
	.quad  DS0005
	.quad  DS0006

SegmClass:
	.quad  DS0007
	.quad  DS0001
	.quad  DS0004+0x4
	.quad  DS0005+0x4
	.quad  DS0004
	.quad  DS0005
	.quad  DS0006

SegmCombine:
	.quad  DS0008
	.quad  DS0001
	.quad  DS0008
	.quad  DS0008
	.quad  DS0009
	.quad  DS0009
	.quad  DS0008

DS000A:
	.byte  0x25, 0x73, 0x20, 0x25, 0x72, 0x20, 0x25, 0x73
	.byte  0x00

DS000B:
	.byte  0x25, 0x73, 0x20, 0x25, 0x72, 0x00, 0x57, 0x4F
	.byte  0x52, 0x44, 0x00

DS000D:
	.byte  0x50, 0x41, 0x52, 0x41, 0x00

DS000E:
	.byte  0x41, 0x4C, 0x49, 0x47, 0x4E, 0x28, 0x25, 0x64
	.byte  0x29, 0x00

DS000F:
	.byte  0x46, 0x4C, 0x41, 0x54, 0x00

DS0010:
	.byte  0x55, 0x53, 0x45, 0x33, 0x32, 0x00

DS0011:
	.byte  0x44, 0x57, 0x4F, 0x52, 0x44, 0x00

DS0012:
	.byte  0x25, 0x73, 0x20, 0x25, 0x72, 0x20, 0x25, 0x73
	.byte  0x20, 0x25, 0x73, 0x20, 0x25, 0x73, 0x20, 0x27
	.byte  0x25, 0x73, 0x27, 0x00

DS0013:
	.byte  0x61, 0x73, 0x73, 0x75, 0x6D, 0x65, 0x20, 0x63
	.byte  0x73, 0x3A, 0x25, 0x73, 0x00

DS0014:
	.byte  0x4F, 0x52, 0x47, 0x20, 0x30, 0x25, 0x78, 0x68
	.byte  0x00

DS0015:
	.byte  0x61, 0x73, 0x73, 0x75, 0x6D, 0x65, 0x20, 0x63
	.byte  0x73, 0x3A, 0x45, 0x52, 0x52, 0x4F, 0x52, 0x00

DS0016:
	.byte  0x2C, 0x20, 0x25, 0x73, 0x00


.SECTION .rodata
	.ALIGN	16

DS0000:
	.byte  0x5F, 0x54, 0x45, 0x58, 0x54, 0x00

DS0001:
	.byte  0x53, 0x54, 0x41, 0x43, 0x4B, 0x00

DS0002:
	.byte  0x5F, 0x44, 0x41, 0x54, 0x41, 0x00

DS0003:
	.byte  0x5F, 0x42, 0x53, 0x53, 0x00

DS0004:
	.byte  0x46, 0x41, 0x52, 0x5F, 0x44, 0x41, 0x54, 0x41
	.byte  0x00

DS0005:
	.byte  0x46, 0x41, 0x52, 0x5F, 0x42, 0x53, 0x53, 0x00

DS0006:
	.byte  0x43, 0x4F, 0x4E, 0x53, 0x54, 0x00

DS0007:
	.byte  0x43, 0x4F, 0x44, 0x45, 0x00

DS0008:
	.byte  0x50, 0x55, 0x42, 0x4C, 0x49, 0x43, 0x00

DS0009:
	.byte  0x50, 0x52, 0x49, 0x56, 0x41, 0x54, 0x45, 0x00


.att_syntax prefix
