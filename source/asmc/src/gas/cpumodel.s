
.intel_syntax noprefix

.global SetCPU
.global sym_Interface
.global sym_Cpu

.extern pe_create_PE_header
.extern AddPredefinedText
.extern sym_ReservedStack
.extern LstWriteSrcLine
.extern CreateVariable
.extern ModelAssumeInit
.extern SetModelDefaultSegNames
.extern ModelSimSegmInit
.extern SimGetSegName
.extern DefineFlatGroup
.extern SetOfssize
.extern Options
.extern ModuleInfo
.extern Parse_Pass


.SECTION .text
	.ALIGN	16

$_001:	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	call	CreateVariable@PLT
	test	rax, rax
	jz	$_002
	or	byte ptr [rax+0x14], 0x20
$_002:	leave
	ret

SetCPU:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	edx, ecx
	mov	ecx, dword ptr [ModuleInfo+0x1C0+rip]
	test	edx, edx
	jz	$_003
	test	edx, 0xF0
	jz	$_004
$_003:	and	ecx, 0xFFFF0007
	mov	eax, edx
	and	eax, 0xF8
	or	ecx, eax
	test	edx, 0x7
	jnz	$_004
	and	ecx, 0xFFFFFFF8
	or	ecx, 0x04
$_004:	test	edx, 0x7
	jz	$_005
	and	ecx, 0xFFFFFFF8
	mov	eax, edx
	and	eax, 0x07
	or	ecx, eax
$_005:	or	ecx, 0xFF00
	test	edx, 0xFF00
	jz	$_006
	and	ecx, 0xFFFF00FF
	and	edx, 0xFF00
	or	ecx, edx
$_006:	mov	dword ptr [ModuleInfo+0x1C0+rip], ecx
	mov	edx, 95
	test	ecx, 0x8
	jz	$_007
	or	edx, 0x80
$_007:	or	edx, 0xD00
	mov	byte ptr [ModuleInfo+0x1B5+rip], 7
	mov	dword ptr [ModuleInfo+0x1BC+rip], edx
	lea	rcx, [DS0000+rip]
	call	CreateVariable@PLT
	mov	qword ptr [sym_Cpu+rip], rax
	cmp	dword ptr [Options+0xA4+rip], 3
	jnz	$_008
	lea	rax, [elf64_fmtopt+rip]
	jmp	$_009

$_008:	lea	rax, [coff64_fmtopt+rip]
$_009:	mov	qword ptr [ModuleInfo+0x1A8+rip], rax
	call	SetModelDefaultSegNames@PLT
	mov	byte ptr [ModuleInfo+0x1BB+rip], 1
	cmp	qword ptr [ModuleInfo+0x1F8+rip], 0
	jnz	$_010
	mov	byte ptr [ModuleInfo+0x1CD+rip], 2
$_010:	call	SetOfssize@PLT
	cmp	byte ptr [ModuleInfo+0x1B6+rip], 8
	jnz	$_011
	mov	al, 5
	jmp	$_013

$_011:	cmp	dword ptr [Options+0xA4+rip], 3
	jz	$_012
	mov	al, 2
	jmp	$_013

$_012:	mov	al, 3
$_013:	mov	byte ptr [ModuleInfo+0x1B9+rip], al
	call	DefineFlatGroup@PLT
	movzx	ecx, byte ptr [ModuleInfo+0x1B5+rip]
	call	ModelSimSegmInit@PLT
	call	ModelAssumeInit@PLT
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_014
	call	LstWriteSrcLine@PLT
$_014:	cmp	dword ptr [Parse_Pass+rip], 0
	jz	$_015
	xor	eax, eax
	jmp	$_020

$_015:	xor	edx, edx
	lea	rcx, [DS0001+rip]
	call	$_001
	xor	ecx, ecx
	call	SimGetSegName@PLT
	mov	rdx, rax
	lea	rcx, [DS0002+rip]
	call	AddPredefinedText@PLT
	xor	edx, edx
	lea	rcx, [DS0003+rip]
	call	$_001
	lea	rdx, [DS0005+rip]
	lea	rcx, [DS0004+rip]
	call	AddPredefinedText@PLT
	lea	rdx, [DS0005+rip]
	lea	rcx, [DS0006+rip]
	call	AddPredefinedText@PLT
	movzx	edx, byte ptr [ModuleInfo+0x1B5+rip]
	lea	rcx, [DS0007+rip]
	call	$_001
	movzx	edx, byte ptr [ModuleInfo+0x1B6+rip]
	lea	rcx, [DS0008+rip]
	call	$_001
	mov	qword ptr [sym_Interface+rip], rax
	mov	al, byte ptr [ModuleInfo+0x1B9+rip]
	cmp	al, 2
	jz	$_016
	cmp	al, 5
	jz	$_016
	cmp	al, 3
	jnz	$_017
$_016:	xor	edx, edx
	lea	rcx, [DS0009+rip]
	call	$_001
	mov	qword ptr [sym_ReservedStack+rip], rax
$_017:	cmp	byte ptr [ModuleInfo+0x1B8+rip], 2
	jz	$_018
	cmp	byte ptr [ModuleInfo+0x1B8+rip], 3
	jnz	$_019
	cmp	dword ptr [Options+0xA4+rip], 0
	jnz	$_019
$_018:	call	pe_create_PE_header@PLT
$_019:	xor	eax, eax
$_020:	leave
	ret


.SECTION .data
	.ALIGN	16

sym_Interface:
	.quad  0x0000000000000000

sym_Cpu: .quad	0x0000000000000000

coff64_fmtopt:
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x12, 0x0E, 0x50, 0x45, 0x33, 0x32, 0x2B, 0x00

elf64_fmtopt:
	.byte  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte  0x00, 0x0F, 0x45, 0x4C, 0x46, 0x36, 0x34, 0x00

DS0000:
	.byte  0x40, 0x43, 0x70, 0x75, 0x00

DS0001:
	.byte  0x40, 0x43, 0x6F, 0x64, 0x65, 0x53, 0x69, 0x7A
	.byte  0x65, 0x00

DS0002:
	.byte  0x40, 0x63, 0x6F, 0x64, 0x65, 0x00

DS0003:
	.byte  0x40, 0x44, 0x61, 0x74, 0x61, 0x53, 0x69, 0x7A
	.byte  0x65, 0x00

DS0004:
	.byte  0x40, 0x64, 0x61, 0x74, 0x61, 0x00

DS0005:
	.byte  0x46, 0x4C, 0x41, 0x54, 0x00

DS0006:
	.byte  0x40, 0x73, 0x74, 0x61, 0x63, 0x6B, 0x00

DS0007:
	.byte  0x40, 0x4D, 0x6F, 0x64, 0x65, 0x6C, 0x00

DS0008:
	.byte  0x40, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x66, 0x61
	.byte  0x63, 0x65, 0x00

DS0009:
	.byte  0x40, 0x52, 0x65, 0x73, 0x65, 0x72, 0x76, 0x65
	.byte  0x64, 0x53, 0x74, 0x61, 0x63, 0x6B, 0x00


.att_syntax prefix
