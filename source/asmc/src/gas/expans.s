
.intel_syntax noprefix

.global myltoa
.global RunMacro
.global ExpandText
.global ExpandLineItems
.global ExpandLiterals
.global ExpandLine
.global MacroLocals
.global MacroLevel

.extern _flttostr
.extern LstWriteSrcLine
.extern SetIfNestLevel
.extern GetIfNestLevel
.extern TextItemError
.extern fill_placeholders
.extern Tokenize
.extern PopInputStatus
.extern PushInputStatus
.extern SetLineNumber
.extern PushMacro
.extern GetTextLine
.extern EvalOperand
.extern WriteCodeLabel
.extern PreprocessLine
.extern WritePreprocessedLine
.extern ParseLine
.extern SpecialTable
.extern MemFree
.extern MemAlloc
.extern tstrcmp
.extern tstrcat
.extern tstrcpy
.extern tstrlen
.extern tmemicmp
.extern tsprintf
.extern DelayExpand
.extern asmerr
.extern Options
.extern ModuleInfo
.extern StringBuffer
.extern SymFind


.SECTION .text
	.ALIGN	16

myltoa:
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 104
	mov	rdi, rdx
	mov	rax, rcx
	test	r9d, r9d
	jz	$_001
	mov	byte ptr [rdi], 45
	inc	rdi
	neg	rax
	jmp	$_002

$_001:	test	rax, rax
	jnz	$_002
	mov	word ptr [rdi], 48
	mov	eax, 1
	jmp	$_007

$_002:	lea	rsi, [rbp-0x1]
$_003:	test	rax, rax
	jz	$_005
	xor	edx, edx
	div	r8
	add	dl, 48
	cmp	dl, 57
	jbe	$_004
	add	dl, 7
$_004:	mov	byte ptr [rsi], dl
	dec	rsi
	jmp	$_003

$_005:	inc	rsi
	cmp	dword ptr [rbp+0x48], 0
	jz	$_006
	cmp	byte ptr [rsi], 57
	jbe	$_006
	mov	byte ptr [rdi], 48
	inc	rdi
$_006:	lea	rcx, [rbp]
	sub	rcx, rsi
	rep movsb
	mov	byte ptr [rdi], 0
	mov	rax, rdi
	sub	rax, qword ptr [rbp+0x30]
$_007:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_008:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	byte ptr [rbp-0x1], 0
	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	cmp	ecx, 2048
	jbe	$_009
	mov	byte ptr [rbp-0x1], 1
	call	MemAlloc@PLT
	jmp	$_010

$_009:	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x20]
$_010:	mov	qword ptr [rbp-0x10], rax
	jmp	$_012

$_011:	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x10]
	xor	edx, edx
	mov	rcx, qword ptr [rbp-0x10]
	call	Tokenize@PLT
$_012:	mov	rcx, qword ptr [rbp-0x10]
	call	GetTextLine@PLT
	test	rax, rax
	jnz	$_011
	cmp	byte ptr [rbp-0x1], 0
	jz	$_013
	mov	rcx, qword ptr [rbp-0x10]
	call	MemFree@PLT
$_013:	leave
	ret

RunMacro:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 424
	mov	rax, qword ptr [ModuleInfo+0x188+rip]
	sub	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [rbp-0x10], rax
	mov	dword ptr [rbp-0x18], 0
	cmp	dword ptr [rbp+0x30], 1
	jle	$_014
	inc	dword ptr [rbp-0x18]
$_014:	mov	dword ptr [rbp-0x28], -1
	cmp	dword ptr [MacroLevel+rip], 100
	jnz	$_015
	mov	ecx, 2123
	call	asmerr@PLT
	jmp	$_151

$_015:	mov	dword ptr [rbp-0x13C], 0
	mov	qword ptr [rbp-0xD8], 0
	mov	rsi, qword ptr [rbp+0x28]
	mov	rdi, qword ptr [rsi+0x68]
	mov	qword ptr [rbp-0x48], rdi
	imul	ebx, dword ptr [rbp+0x30], 24
	add	rbx, qword ptr [rbp+0x38]
	mov	dword ptr [rbp-0x2C], 0
	test	byte ptr [rsi+0x38], 0x02
	jz	$_017
	cmp	byte ptr [rbx], 40
	jnz	$_016
	inc	dword ptr [rbp+0x30]
	add	rbx, 24
	mov	dword ptr [rbp-0x2C], 41
	mov	dword ptr [rbp-0x28], 1
$_016:	mov	rax, qword ptr [rbp+0x40]
	mov	byte ptr [rax], 0
$_017:	test	byte ptr [rsi+0x38], 0x10
	jz	$_024
	cmp	dword ptr [rbp-0x28], 0
	jle	$_022
$_018:	cmp	dword ptr [rbp-0x28], 0
	jz	$_021
	cmp	byte ptr [rbx], 0
	jz	$_021
	cmp	byte ptr [rbx], 40
	jnz	$_019
	inc	dword ptr [rbp-0x28]
	jmp	$_020

$_019:	cmp	byte ptr [rbx], 41
	jnz	$_020
	dec	dword ptr [rbp-0x28]
$_020:	inc	dword ptr [rbp+0x30]
	add	rbx, 24
	jmp	$_018

$_021:	jmp	$_023

$_022:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp+0x30], eax
$_023:	mov	eax, dword ptr [rbp+0x30]
	jmp	$_151

$_024:	cmp	word ptr [rdi], 0
	jz	$_027
	movzx	eax, word ptr [rdi]
	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	mov	edx, ecx
	add	ecx, ecx
	lea	ecx, [rcx+rax*8]
	cmp	edx, 2048
	jnz	$_025
	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x30]
	jmp	$_026

$_025:	mov	dword ptr [rbp-0x13C], 1
	call	MemAlloc@PLT
$_026:	mov	qword ptr [rbp-0xD8], rax
	movzx	ecx, word ptr [rdi]
	lea	rax, [rax+rcx*8]
	mov	qword ptr [rbp-0x40], rax
	mov	qword ptr [rbp-0x8], rax
$_027:	mov	rbx, qword ptr [rbp+0x38]
	mov	dword ptr [rbp-0x1C], 0
	test	byte ptr [rsi+0x38], 0x04
	jz	$_030
	test	byte ptr [rbp+0x48], 0x01
	jz	$_028
	mov	rcx, qword ptr [rbx+0x8]
	call	tstrlen@PLT
	mov	dword ptr [rbp-0x14], eax
	mov	ecx, dword ptr [rbp-0x1C]
	mov	rdx, qword ptr [rbp-0xD8]
	mov	rdi, qword ptr [rbp-0x8]
	mov	qword ptr [rdx+rcx*8], rdi
	mov	ecx, dword ptr [rbp-0x14]
	inc	ecx
	mov	rsi, qword ptr [rbx+0x8]
	rep movsb
	mov	edx, dword ptr [rbp-0x14]
	mov	rax, qword ptr [rbp-0x8]
	add	edx, 8
	and	edx, 0xFFFFFFF8
	add	rax, rdx
	mov	qword ptr [rbp-0x8], rax
	jmp	$_029

$_028:	mov	ecx, dword ptr [rbp-0x1C]
	mov	rdx, qword ptr [rbp-0xD8]
	lea	rax, [DS0000+rip]
	mov	qword ptr [rdx+rcx*8], rax
$_029:	inc	dword ptr [rbp-0x1C]
$_030:	mov	rax, qword ptr [rbp+0x50]
	mov	dword ptr [rax], 0
	imul	eax, dword ptr [ModuleInfo+0x220+rip], 24
	mov	dword ptr [rbx+rax+0x4], 0
	imul	eax, dword ptr [rbp+0x30], 24
	add	rbx, rax
	mov	dword ptr [rbp-0x24], 0
	mov	dword ptr [rbp-0x20], 0
$_031:	mov	rsi, qword ptr [rbp+0x28]
	mov	rdi, qword ptr [rbp-0x48]
	movzx	ecx, word ptr [rdi]
	cmp	dword ptr [rbp-0x1C], ecx
	jge	$_109
	imul	ebx, dword ptr [rbp+0x30], 24
	add	rbx, qword ptr [rbp+0x38]
	cmp	byte ptr [rbx], 44
	jnz	$_032
	cmp	dword ptr [rbp-0x20], 0
	jz	$_032
	inc	dword ptr [rbp+0x30]
	add	rbx, 24
$_032:	mov	dword ptr [rbp-0x20], 1
	dec	ecx
	cmp	byte ptr [rbx], 0
	jz	$_033
	mov	eax, dword ptr [rbp-0x2C]
	cmp	byte ptr [rbx], al
	jz	$_033
	cmp	byte ptr [rbx], 44
	jnz	$_036
	test	byte ptr [rsi+0x38], 0x01
	jz	$_033
	cmp	dword ptr [rbp-0x1C], ecx
	jz	$_036
$_033:	imul	eax, dword ptr [rbp-0x1C], 16
	mov	rcx, qword ptr [rdi+0x8]
	add	rcx, rax
	cmp	byte ptr [rcx+0x8], 0
	jz	$_034
	mov	ecx, 2125
	call	asmerr@PLT
	mov	dword ptr [rbp+0x30], eax
	jmp	$_149

$_034:	cmp	dword ptr [rbp-0x24], 0
	jnz	$_035
	imul	edx, dword ptr [rbp-0x1C], 8
	add	rdx, qword ptr [rbp-0xD8]
	mov	rax, qword ptr [rcx]
	mov	qword ptr [rdx], rax
$_035:	jmp	$_108

$_036:	mov	dword ptr [rbp-0x11C], 0
	mov	dword ptr [rbp-0x120], 0
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp-0x124], eax
	mov	rdx, qword ptr [rbp-0x8]
	mov	byte ptr [rdx], 0
	mov	qword ptr [rbp-0x38], rdx
$_037:	imul	ebx, dword ptr [rbp+0x30], 24
	add	rbx, qword ptr [rbp+0x38]
	cmp	byte ptr [rbx], 0
	jz	$_038
	cmp	byte ptr [rbx], 44
	jnz	$_039
$_038:	cmp	dword ptr [rbp-0x11C], 0
	je	$_099
$_039:	cmp	byte ptr [rbx], 0
	jnz	$_042
	mov	eax, dword ptr [rbx+0x4]
	mov	dword ptr [rbp+0x30], eax
	imul	ebx, eax, 24
	add	rbx, qword ptr [rbp+0x38]
	dec	dword ptr [rbp-0x11C]
	cmp	byte ptr [rbx+0x1], 60
	jnz	$_040
	mov	dword ptr [rbp-0x120], 0
	jmp	$_041

$_040:	mov	rax, qword ptr [rbp-0x38]
	inc	qword ptr [rbp-0x38]
	mov	byte ptr [rax], 125
$_041:	jmp	$_098

$_042:	cmp	byte ptr [rbx], 37
	jne	$_078
	inc	dword ptr [rbp+0x30]
	add	rbx, 24
	jmp	$_044

$_043:	inc	dword ptr [rbp+0x30]
	add	rbx, 24
$_044:	cmp	byte ptr [rbx], 37
	jz	$_043
	mov	eax, dword ptr [rbp+0x30]
	mov	dword ptr [rbp-0x14], eax
	mov	dword ptr [rbp-0x130], 1
	cmp	byte ptr [rbx], 8
	jnz	$_046
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x58], rax
	test	rax, rax
	jz	$_046
	test	byte ptr [rax+0x14], 0x02
	jz	$_046
	cmp	byte ptr [rax+0x18], 10
	jz	$_045
	cmp	byte ptr [rax+0x18], 9
	jnz	$_046
	test	byte ptr [rax+0x38], 0x02
	jz	$_046
	cmp	byte ptr [rbx+0x18], 40
	jnz	$_046
$_045:	mov	dword ptr [rbp-0x130], 0
$_046:	mov	dword ptr [rbp-0x12C], 0
$_047:	imul	ebx, dword ptr [rbp-0x14], 24
	add	rbx, qword ptr [rbp+0x38]
	cmp	byte ptr [rbx], 0
	je	$_060
	cmp	byte ptr [rbx], 44
	je	$_060
	mov	rcx, qword ptr [rbx+0x8]
	movzx	edx, byte ptr [ModuleInfo+0x1D4+rip]
	movzx	eax, byte ptr [rcx]
	cmp	al, 46
	jnz	$_048
	test	dl, dl
	jnz	$_049
$_048:	test	byte ptr [r15+rax], 0x40
	jz	$_055
$_049:	cmp	byte ptr [rbx+0x18], 40
	jnz	$_054
	add	dword ptr [rbp-0x14], 2
	add	rbx, 48
	mov	ecx, 1
$_050:	test	ecx, ecx
	jz	$_053
	cmp	byte ptr [rbx], 0
	jz	$_053
	cmp	byte ptr [rbx], 40
	jnz	$_051
	inc	ecx
	jmp	$_052

$_051:	cmp	byte ptr [rbx], 41
	jnz	$_052
	dec	ecx
$_052:	inc	dword ptr [rbp-0x14]
	add	rbx, 24
	jmp	$_050

$_053:	dec	dword ptr [rbp-0x14]
$_054:	jmp	$_059

$_055:	cmp	dword ptr [rbp-0x2C], 41
	jnz	$_057
	cmp	byte ptr [rbx], 40
	jnz	$_056
	inc	dword ptr [rbp-0x12C]
	jmp	$_057

$_056:	cmp	byte ptr [rbx], 41
	jnz	$_057
	cmp	dword ptr [rbp-0x12C], 0
	jz	$_060
	dec	dword ptr [rbp-0x12C]
$_057:	cmp	byte ptr [rbx], 9
	jnz	$_058
	cmp	byte ptr [rbx+0x1], 0
	jz	$_060
$_058:	cmp	byte ptr [rbx], 46
	jz	$_059
	cmp	byte ptr [rbx], 38
	jz	$_059
	cmp	byte ptr [rbx], 37
	jz	$_059
	inc	dword ptr [rbp-0x130]
$_059:	inc	dword ptr [rbp-0x14]
	jmp	$_047

$_060:	mov	eax, dword ptr [rbp+0x30]
	cmp	dword ptr [rbp-0x14], eax
	jnz	$_061
	dec	dword ptr [rbp+0x30]
	jmp	$_098

$_061:	mov	rcx, qword ptr [rbx+0x10]
	imul	ebx, dword ptr [rbp+0x30], 24
	add	rbx, qword ptr [rbp+0x38]
	mov	rsi, qword ptr [rbx+0x10]
	sub	rcx, rsi
	jmp	$_063

$_062:	dec	ecx
$_063:	movzx	eax, byte ptr [rsi+rcx-0x1]
	test	byte ptr [r15+rax], 0x08
	jnz	$_062
	mov	dword ptr [rbp-0x12C], ecx
	mov	rdi, qword ptr [rbp-0x38]
	rep movsb
	mov	byte ptr [rdi], 0
	xor	r8d, r8d
	mov	rdx, qword ptr [rbp+0x38]
	mov	rcx, qword ptr [rbp-0x38]
	call	ExpandText
	cmp	eax, -1
	jnz	$_064
	mov	dword ptr [rbp+0x30], eax
	mov	rax, qword ptr [rbp-0x10]
	add	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [ModuleInfo+0x188+rip], rax
	jmp	$_149

$_064:	mov	eax, dword ptr [rbp-0x14]
	mov	dword ptr [rbp+0x30], eax
	dec	dword ptr [rbp+0x30]
	cmp	dword ptr [rbp-0x130], 0
	je	$_077
	mov	edx, dword ptr [ModuleInfo+0x220+rip]
	inc	edx
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x38]
	mov	rcx, qword ptr [rbp-0x38]
	call	Tokenize@PLT
	mov	dword ptr [rbp-0x128], eax
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp-0x14], eax
	inc	dword ptr [rbp-0x14]
	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0xC0]
	mov	r8d, dword ptr [rbp-0x128]
	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [rbp-0x14]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_065
	mov	dword ptr [rbp-0xC0], 0
	mov	dword ptr [rbp-0xBC], 0
	jmp	$_067

$_065:	cmp	dword ptr [rbp-0x84], 0
	jz	$_067
	cmp	dword ptr [rbp-0x84], 3
	jnz	$_066
	cmp	byte ptr [rbp-0x80], 47
	jz	$_067
$_066:	mov	ecx, 2026
	call	asmerr@PLT
	mov	dword ptr [rbp-0xC0], 0
	mov	dword ptr [rbp-0xBC], 0
$_067:	cmp	dword ptr [rbp-0x84], 0
	jnz	$_068
	xor	eax, eax
	cmp	dword ptr [rbp-0xBC], 0
	setl	al
	mov	dword ptr [rsp+0x20], 0
	mov	r9d, eax
	movzx	r8d, byte ptr [ModuleInfo+0x1C4+rip]
	mov	rdx, qword ptr [ModuleInfo+0x188+rip]
	mov	rcx, qword ptr [rbp-0xC0]
	call	myltoa
	jmp	$_075

$_068:	cmp	dword ptr [rbp-0x84], 3
	jne	$_075
	cmp	byte ptr [rbp-0x80], 47
	jne	$_075
	cmp	dword ptr [rbp-0xC0], 16
	jnz	$_069
	cmp	dword ptr [rbp-0xB4], 0
	jnz	$_069
	lea	rdx, [DS0001+rip]
	mov	rcx, qword ptr [ModuleInfo+0x188+rip]
	call	tstrcpy@PLT
	jmp	$_075

$_069:	cmp	byte ptr [ModuleInfo+0x350+rip], 120
	jnz	$_070
	mov	r9, qword ptr [rbp-0xC0]
	mov	r8, qword ptr [rbp-0xB8]
	lea	rdx, [DS0002+rip]
	mov	rcx, qword ptr [ModuleInfo+0x188+rip]
	call	tsprintf@PLT
	jmp	$_075

$_070:	mov	dword ptr [rbp-0x164], 101
	mov	dword ptr [rbp-0x160], 3
	mov	eax, dword ptr [ModuleInfo+0x34C+rip]
	mov	dword ptr [rbp-0x170], eax
	mov	eax, dword ptr [ModuleInfo+0x174+rip]
	mov	dword ptr [rbp-0x144], eax
	cmp	byte ptr [ModuleInfo+0x350+rip], 101
	jnz	$_071
	mov	dword ptr [rbp-0x16C], 1
	mov	dword ptr [rbp-0x168], 4096
	jmp	$_073

$_071:	cmp	byte ptr [ModuleInfo+0x350+rip], 103
	jnz	$_072
	mov	dword ptr [rbp-0x16C], 1
	mov	dword ptr [rbp-0x168], 16384
	jmp	$_073

$_072:	mov	dword ptr [rbp-0x16C], 0
	mov	dword ptr [rbp-0x168], 8192
$_073:	mov	rsi, qword ptr [ModuleInfo+0x188+rip]
	inc	rsi
	mov	r9d, 2097152
	mov	r8, rsi
	lea	rdx, [rbp-0x170]
	lea	rcx, [rbp-0xC0]
	call	_flttostr@PLT
	cmp	dword ptr [rbp-0x15C], -1
	jnz	$_074
	mov	byte ptr [rsi-0x1], 45
	jmp	$_075

$_074:	mov	rdx, rsi
	mov	rcx, qword ptr [ModuleInfo+0x188+rip]
	call	tstrcpy@PLT
$_075:	mov	eax, dword ptr [rbp-0x128]
	cmp	dword ptr [rbp-0x14], eax
	jz	$_076
	imul	ebx, dword ptr [rbp-0x14], 24
	add	rbx, qword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbx+0x10]
	mov	rcx, qword ptr [ModuleInfo+0x188+rip]
	call	tstrcat@PLT
$_076:	mov	rdx, qword ptr [ModuleInfo+0x188+rip]
	mov	rcx, qword ptr [rbp-0x38]
	call	tstrcpy@PLT
$_077:	mov	rcx, qword ptr [rbp-0x38]
	call	tstrlen@PLT
	add	qword ptr [rbp-0x38], rax
	jmp	$_098

$_078:	imul	ebx, dword ptr [rbp+0x30], 24
	add	rbx, qword ptr [rbp+0x38]
	cmp	byte ptr [rbx], 9
	jnz	$_079
	cmp	byte ptr [rbx+0x1], 123
	jnz	$_079
	mov	rcx, qword ptr [rbx+0x8]
	mov	ebx, dword ptr [rbp+0x30]
	mov	rax, qword ptr [rbp-0x38]
	inc	qword ptr [rbp-0x38]
	mov	byte ptr [rax], 123
	inc	dword ptr [rbp-0x11C]
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp+0x30], eax
	mov	r9d, 3
	mov	r8, qword ptr [rbp+0x38]
	lea	edx, [rax+0x1]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	imul	eax, eax, 24
	add	rax, qword ptr [rbp+0x38]
	mov	dword ptr [rax+0x4], ebx
	jmp	$_098

$_079:	cmp	dword ptr [rbp-0x120], 0
	jne	$_089
	cmp	dword ptr [rbp-0x28], 0
	jle	$_081
	cmp	byte ptr [rbx], 40
	jnz	$_080
	inc	dword ptr [rbp-0x28]
	jmp	$_081

$_080:	cmp	byte ptr [rbx], 41
	jnz	$_081
	dec	dword ptr [rbp-0x28]
	je	$_099
$_081:	cmp	byte ptr [rbx], 9
	jne	$_084
	cmp	byte ptr [rbx+0x1], 60
	jne	$_084
	cmp	dword ptr [rbp-0x120], 0
	jne	$_084
	mov	rsi, qword ptr [rbx+0x10]
	inc	rsi
	mov	rcx, qword ptr [rbx+0x28]
	sub	rcx, rsi
	mov	edx, ecx
	mov	rdi, qword ptr [ModuleInfo+0x188+rip]
	rep movsb
	mov	rdi, qword ptr [ModuleInfo+0x188+rip]
	jmp	$_083

$_082:	dec	edx
$_083:	cmp	byte ptr [rdi+rdx-0x1], 62
	jnz	$_082
	mov	byte ptr [rdi+rdx-0x1], 0
	mov	rax, rdi
	add	edx, 8
	and	edx, 0xFFFFFFF8
	add	rax, rdx
	mov	qword ptr [ModuleInfo+0x188+rip], rax
	inc	dword ptr [rbp-0x11C]
	mov	dword ptr [rbp-0x120], 1
	mov	ebx, dword ptr [rbp+0x30]
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp+0x30], eax
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x38]
	lea	edx, [rax+0x1]
	mov	rcx, rdi
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	imul	eax, eax, 24
	add	rax, qword ptr [rbp+0x38]
	mov	dword ptr [rax+0x4], ebx
	imul	ebx, dword ptr [rbp+0x30], 24
	add	rbx, qword ptr [rbp+0x38]
	mov	rcx, qword ptr [rbx+0x28]
	sub	rcx, rdi
	mov	rsi, rdi
	mov	rdi, qword ptr [rbp-0x38]
	rep movsb
	mov	qword ptr [rbp-0x38], rdi
	jmp	$_098

$_084:	cmp	byte ptr [rbx], 8
	jne	$_089
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	test	rax, rax
	je	$_089
	mov	qword ptr [rbp-0x58], rax
	cmp	byte ptr [rax+0x18], 9
	jne	$_087
	test	byte ptr [rax+0x14], 0x02
	je	$_087
	test	byte ptr [rax+0x38], 0x02
	je	$_087
	cmp	byte ptr [rbx+0x18], 40
	jne	$_087
	inc	dword ptr [rbp+0x30]
	lea	rax, [rbp-0x134]
	mov	qword ptr [rsp+0x28], rax
	mov	dword ptr [rsp+0x20], 0
	mov	r9, qword ptr [rbp-0x38]
	mov	r8, qword ptr [rbp+0x38]
	mov	edx, dword ptr [rbp+0x30]
	mov	rcx, qword ptr [rbp-0x58]
	call	RunMacro
	mov	dword ptr [rbp+0x30], eax
	cmp	dword ptr [rbp+0x30], 0
	jge	$_085
	mov	rax, qword ptr [rbp-0x10]
	add	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [ModuleInfo+0x188+rip], rax
	jmp	$_149

$_085:	mov	rcx, qword ptr [rbp-0x38]
	call	tstrlen@PLT
	add	qword ptr [rbp-0x38], rax
	imul	ebx, dword ptr [rbp+0x30], 24
	add	rbx, qword ptr [rbp+0x38]
	cmp	byte ptr [rbx], 0
	jz	$_086
	cmp	byte ptr [rbx], 44
	jz	$_086
	mov	rsi, qword ptr [rbx-0x8]
	inc	rsi
	mov	rcx, qword ptr [rbx+0x10]
	sub	rcx, rsi
	mov	rdi, qword ptr [rbp-0x38]
	rep movsb
	mov	qword ptr [rbp-0x38], rdi
$_086:	dec	dword ptr [rbp+0x30]
	sub	rbx, 24
	jmp	$_098

	jmp	$_089

$_087:	cmp	byte ptr [rax+0x18], 10
	jnz	$_089
	test	byte ptr [rax+0x14], 0x02
	jz	$_089
	mov	ecx, dword ptr [rbp-0x1C]
	mov	edx, 1
	shl	edx, cl
	mov	rdi, qword ptr [rbp-0x48]
	mov	rsi, qword ptr [rbp+0x28]
	test	byte ptr [rsi+0x14], 0x20
	jz	$_089
	test	word ptr [rdi+0x2], dx
	jz	$_089
	mov	rdx, qword ptr [rax+0x28]
	mov	rcx, qword ptr [rbp-0x38]
	call	tstrcpy@PLT
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, qword ptr [rbp+0x38]
	mov	rcx, qword ptr [rbp-0x38]
	call	$_199
	mov	rcx, qword ptr [rbp-0x38]
	call	tstrlen@PLT
	add	qword ptr [rbp-0x38], rax
	cmp	byte ptr [rbx+0x18], 0
	jz	$_088
	cmp	byte ptr [rbx+0x18], 44
	jz	$_088
	mov	rdx, qword ptr [rbp-0x58]
	mov	esi, dword ptr [rdx+0x10]
	add	rsi, qword ptr [rbx+0x10]
	mov	rcx, qword ptr [rbx+0x28]
	sub	rcx, rsi
	mov	rdi, qword ptr [rbp-0x38]
	rep movsb
	mov	qword ptr [rbp-0x38], rdi
$_088:	jmp	$_098

$_089:	mov	rcx, qword ptr [rbx+0x28]
	sub	rcx, qword ptr [rbx+0x10]
	cmp	dword ptr [rbp-0x11C], 0
	jnz	$_093
	cmp	byte ptr [rbx+0x18], 44
	jz	$_090
	mov	eax, dword ptr [rbp-0x2C]
	cmp	byte ptr [rbx+0x18], al
	jnz	$_093
$_090:	mov	rdx, qword ptr [rbx+0x10]
	jmp	$_092

$_091:	dec	rcx
$_092:	movzx	eax, byte ptr [rdx+rcx-0x1]
	test	byte ptr [r15+rax], 0x08
	jnz	$_091
$_093:	mov	rdi, qword ptr [rbp-0x38]
	mov	rsi, qword ptr [rbx+0x10]
	cmp	byte ptr [rbx], 9
	jnz	$_097
	cmp	byte ptr [rbx+0x1], 0
	jnz	$_097
	add	rcx, rsi
$_094:	cmp	rsi, rcx
	jnc	$_096
	cmp	byte ptr [rsi], 33
	jnz	$_095
	inc	rsi
$_095:	movsb
	jmp	$_094

$_096:	mov	qword ptr [rbp-0x38], rdi
	jmp	$_098

$_097:	rep movsb
	mov	qword ptr [rbp-0x38], rdi
$_098:	inc	dword ptr [rbp+0x30]
	jmp	$_037

$_099:	mov	rax, qword ptr [rbp-0x38]
	mov	byte ptr [rax], 0
	mov	eax, dword ptr [rbp-0x124]
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	rax, qword ptr [rbp-0x10]
	add	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [ModuleInfo+0x188+rip], rax
	mov	rdi, qword ptr [rbp-0x48]
	mov	rsi, qword ptr [rbp+0x28]
	movzx	eax, word ptr [rdi]
	dec	eax
	mov	rdx, qword ptr [rbp-0x8]
	test	byte ptr [rsi+0x38], 0x01
	jz	$_106
	cmp	dword ptr [rbp-0x1C], eax
	jnz	$_106
	cmp	dword ptr [rbp-0x24], 0
	jnz	$_100
	mov	rax, qword ptr [rbp-0xD8]
	mov	ecx, dword ptr [rbp-0x1C]
	mov	qword ptr [rax+rcx*8], rdx
$_100:	mov	rax, qword ptr [rbp-0x38]
	test	byte ptr [rsi+0x14], 0x20
	jz	$_101
	sub	rax, qword ptr [rbp-0x8]
	mov	edx, eax
	mov	rax, qword ptr [rbp-0x8]
	add	edx, 8
	and	edx, 0xFFFFFFF8
	add	rax, rdx
$_101:	mov	qword ptr [rbp-0x8], rax
	cmp	byte ptr [rbx], 44
	jnz	$_105
	inc	dword ptr [rbp+0x30]
	add	rbx, 24
	mov	rdx, rax
	test	byte ptr [rsi+0x38], 0x02
	jz	$_102
	mov	eax, dword ptr [rbp-0x2C]
	cmp	byte ptr [rbx], al
	jz	$_104
$_102:	dec	dword ptr [rbp-0x1C]
	test	byte ptr [rsi+0x14], 0x20
	jnz	$_103
	mov	byte ptr [rdx], 44
	inc	rdx
	inc	qword ptr [rbp-0x8]
$_103:	mov	byte ptr [rdx], 0
$_104:	mov	dword ptr [rbp-0x20], 0
$_105:	inc	dword ptr [rbp-0x24]
	jmp	$_108

$_106:	cmp	byte ptr [rdx], 0
	jz	$_107
	mov	rax, rdx
	mov	rcx, qword ptr [rbp-0xD8]
	mov	edx, dword ptr [rbp-0x1C]
	mov	qword ptr [rcx+rdx*8], rax
	mov	rdx, qword ptr [rbp-0x38]
	sub	rdx, rax
	add	edx, 8
	and	edx, 0xFFFFFFF8
	add	rax, rdx
	mov	qword ptr [rbp-0x8], rax
	jmp	$_108

$_107:	mov	rdx, qword ptr [rbp-0xD8]
	mov	ecx, dword ptr [rbp-0x1C]
	lea	rax, [DS0002+0xA+rip]
	mov	qword ptr [rdx+rcx*8], rax
$_108:	inc	dword ptr [rbp-0x1C]
	jmp	$_031

$_109:	cmp	dword ptr [rbp-0x28], 0
	jl	$_114
	cmp	byte ptr [rbx], 41
	jz	$_113
	mov	eax, dword ptr [rbp+0x30]
	mov	dword ptr [rbp-0x14], eax
$_110:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp+0x30], eax
	jge	$_111
	cmp	byte ptr [rbx], 41
	jz	$_111
	inc	dword ptr [rbp+0x30]
	add	rbx, 24
	jmp	$_110

$_111:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp+0x30], eax
	jnz	$_112
	mov	ecx, 2157
	call	asmerr@PLT
	mov	dword ptr [rbp+0x30], eax
	jmp	$_149

	jmp	$_113

$_112:	imul	eax, dword ptr [rbp-0x14], 24
	add	rax, qword ptr [rbp+0x38]
	mov	r8, qword ptr [rax+0x10]
	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 4006
	call	asmerr@PLT
$_113:	inc	dword ptr [rbp+0x30]
	add	rbx, 24
	jmp	$_115

$_114:	cmp	byte ptr [rbx], 0
	jz	$_115
	test	byte ptr [rbp+0x48], 0x04
	jnz	$_115
	mov	r8, qword ptr [rbx+0x10]
	mov	rdx, qword ptr [rsi+0x8]
	mov	ecx, 4006
	call	asmerr@PLT
$_115:	test	byte ptr [rsi+0x14], 0x20
	jz	$_116
	cmp	qword ptr [rsi+0x28], 0
	jz	$_116
	mov	eax, dword ptr [rbp-0x24]
	mov	dword ptr [rbp-0xC8], eax
	mov	r8, qword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbp+0x40]
	lea	rcx, [rbp-0xF0]
	call	qword ptr [rsi+0x28]
	mov	rax, qword ptr [rbp+0x50]
	mov	dword ptr [rax], 1
	jmp	$_149

$_116:	mov	eax, dword ptr [MacroLocals+rip]
	mov	dword ptr [rbp-0xE0], eax
	movzx	eax, word ptr [rdi+0x2]
	add	dword ptr [MacroLocals+rip], eax
	mov	rax, qword ptr [rdi+0x10]
	mov	qword ptr [rbp-0xE8], rax
	mov	qword ptr [rbp-0xF0], 0
	movzx	eax, word ptr [rdi]
	mov	dword ptr [rbp-0xC8], eax
	cmp	qword ptr [rbp-0xE8], 0
	je	$_149
	mov	rax, qword ptr [rsi+0x8]
	test	byte ptr [rsi+0x38], 0x02
	jnz	$_117
	cmp	byte ptr [rax], 0
	jz	$_117
	call	LstWriteSrcLine@PLT
$_117:	test	byte ptr [rbp+0x48], 0x02
	jnz	$_118
	lea	rcx, [rbp-0x110]
	call	PushInputStatus@PLT
	mov	qword ptr [rbp+0x38], rax
$_118:	mov	qword ptr [rbp-0xD0], rsi
	lea	rcx, [rbp-0xF0]
	call	PushMacro@PLT
	inc	dword ptr [MacroLevel+rip]
	call	GetIfNestLevel@PLT
	mov	dword ptr [rbp-0x114], eax
	mov	dword ptr [rbp-0x118], 0
	jmp	$_147

$_119:	mov	rcx, qword ptr [rbp+0x38]
	call	PreprocessLine@PLT
	test	rax, rax
	je	$_147
	mov	rbx, qword ptr [rbp+0x38]
	cmp	byte ptr [rbx], 58
	jnz	$_122
	cmp	byte ptr [rbx+0x18], 8
	jz	$_120
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_121

$_120:	cmp	byte ptr [rbx+0x30], 0
	jz	$_121
	mov	rdx, qword ptr [rbx+0x40]
	mov	ecx, 2008
	call	asmerr@PLT
$_121:	jmp	$_147

$_122:	cmp	byte ptr [rbx], 3
	jne	$_146
	cmp	dword ptr [rbx+0x4], 474
	jz	$_123
	cmp	dword ptr [rbx+0x4], 409
	jne	$_135
$_123:	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_124
	cmp	dword ptr [ModuleInfo+0x1C8+rip], 2
	jnz	$_124
	call	LstWriteSrcLine@PLT
$_124:	cmp	byte ptr [rbx+0x18], 0
	je	$_133
	cmp	byte ptr [rbx+0x18], 9
	jnz	$_125
	cmp	byte ptr [rbx+0x19], 60
	jz	$_126
$_125:	lea	rcx, [rbx+0x18]
	call	TextItemError@PLT
	jmp	$_133

$_126:	cmp	dword ptr [ModuleInfo+0x220+rip], 2
	jle	$_127
	mov	rdx, qword ptr [rbx+0x40]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_133

$_127:	cmp	qword ptr [rbp+0x40], 0
	jz	$_133
	mov	rdi, qword ptr [rbp+0x40]
	mov	rdx, qword ptr [rbp-0xF0]
	mov	rax, qword ptr [rbx+0x28]
	sub	rax, qword ptr [ModuleInfo+0x178+rip]
	mov	al, byte ptr [rdx+rax+0x9]
	cmp	dword ptr [rbp-0x18], 0
	jnz	$_128
	cmp	dword ptr [rbx+0x4], 409
	jnz	$_128
	mov	rax, qword ptr [rbp+0x40]
	mov	byte ptr [rax], 0
	jmp	$_133

$_128:	cmp	byte ptr [rdx+0x8], 0
	jnz	$_129
	cmp	al, 60
	jz	$_130
$_129:	mov	ecx, dword ptr [rbx+0x1C]
	inc	ecx
	mov	rsi, qword ptr [rbx+0x20]
	rep movsb
	jmp	$_133

$_130:	mov	rsi, qword ptr [rbx+0x28]
	inc	rsi
	mov	rcx, qword ptr [rbx+0x40]
	sub	rcx, rsi
	rep movsb
	dec	rdi
	jmp	$_132

$_131:	dec	rdi
$_132:	cmp	byte ptr [rdi], 62
	jnz	$_131
	mov	byte ptr [rdi], 0
$_133:	cmp	dword ptr [rbp-0x118], 0
	jz	$_134
	mov	qword ptr [rbp-0xF0], 0
	xor	ecx, ecx
	call	SetLineNumber@PLT
	mov	ecx, dword ptr [rbp-0x114]
	call	SetIfNestLevel@PLT
$_134:	mov	rcx, qword ptr [rbp+0x38]
	call	$_008
	mov	rax, qword ptr [rbp+0x50]
	mov	dword ptr [rax], 1
	jmp	$_148

	jmp	$_146

$_135:	cmp	dword ptr [rbx+0x4], 476
	jne	$_146
	cmp	byte ptr [rbx+0x18], 0
	je	$_144
	mov	rcx, qword ptr [rbx+0x20]
	call	tstrlen@PLT
	mov	dword ptr [rbp-0x138], eax
	mov	dword ptr [rbp-0x14], 1
	mov	rdi, qword ptr [rbp-0xE8]
$_136:	test	rdi, rdi
	je	$_141
	lea	rsi, [rdi+0x9]
	cmp	byte ptr [rsi], 58
	jnz	$_140
	cmp	byte ptr [rdi+0x8], 0
	jz	$_137
	mov	rax, qword ptr [rbp-0xD8]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rbp-0xE0]
	mov	r8d, dword ptr [rbp-0xC8]
	mov	rdx, rsi
	mov	rcx, qword ptr [ModuleInfo+0x188+rip]
	call	fill_placeholders@PLT
	mov	rsi, qword ptr [ModuleInfo+0x188+rip]
$_137:	inc	rsi
	jmp	$_139

$_138:	inc	rsi
$_139:	movzx	eax, byte ptr [rsi]
	test	byte ptr [r15+rax], 0x08
	jnz	$_138
	mov	r8d, dword ptr [rbp-0x138]
	mov	rdx, qword ptr [rbx+0x20]
	mov	rcx, rsi
	call	tmemicmp@PLT
	test	eax, eax
	jnz	$_140
	mov	ecx, dword ptr [rbp-0x138]
	movzx	eax, byte ptr [rsi+rcx]
	test	byte ptr [r15+rax], 0x44
	jz	$_141
$_140:	mov	rdi, qword ptr [rdi]
	inc	dword ptr [rbp-0x14]
	jmp	$_136

$_141:	test	rdi, rdi
	jnz	$_142
	mov	rdx, qword ptr [rbx+0x20]
	mov	ecx, 2147
	call	asmerr@PLT
	jmp	$_143

$_142:	mov	qword ptr [rbp-0xF0], rdi
	mov	ecx, dword ptr [rbp-0x14]
	call	SetLineNumber@PLT
	mov	ecx, dword ptr [rbp-0x114]
	call	SetIfNestLevel@PLT
	inc	dword ptr [rbp-0x118]
	jmp	$_147

$_143:	jmp	$_145

$_144:	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
$_145:	mov	rcx, qword ptr [rbp+0x38]
	call	$_008
	jmp	$_148

$_146:	mov	rcx, qword ptr [rbp+0x38]
	call	ParseLine@PLT
	cmp	byte ptr [Options+0x96+rip], 1
	jnz	$_147
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	WritePreprocessedLine@PLT
$_147:	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	GetTextLine@PLT
	test	rax, rax
	jne	$_119
$_148:	dec	dword ptr [MacroLevel+rip]
	test	byte ptr [rbp+0x48], 0x02
	jnz	$_149
	lea	rcx, [rbp-0x110]
	call	PopInputStatus@PLT
$_149:	cmp	dword ptr [rbp-0x13C], 0
	jz	$_150
	mov	rcx, qword ptr [rbp-0xD8]
	call	MemFree@PLT
$_150:	mov	eax, dword ptr [rbp+0x30]
$_151:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_152:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rbx, rcx
	movsxd	rax, dword ptr [rbp+0x28]
	imul	rcx, rax, 24
	mov	edx, dword ptr [rbp+0x20]
	cmp	eax, 0
	jle	$_155
	imul	eax, dword ptr [rbp+0x30], 24
	add	rbx, rax
$_153:	cmp	dword ptr [rbp+0x30], edx
	jl	$_154
	mov	rax, qword ptr [rbx]
	mov	qword ptr [rbx+rcx], rax
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbx+rcx+0x8], rax
	mov	rax, qword ptr [rbx+0x10]
	mov	qword ptr [rbx+rcx+0x10], rax
	dec	dword ptr [rbp+0x30]
	sub	rbx, 24
	jmp	$_153

$_154:	jmp	$_157

$_155:	cmp	eax, 0
	jge	$_157
	sub	edx, eax
	imul	eax, edx, 24
	add	rbx, rax
$_156:	cmp	edx, dword ptr [rbp+0x30]
	jg	$_157
	mov	rax, qword ptr [rbx]
	mov	qword ptr [rbx+rcx], rax
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbx+rcx+0x8], rax
	mov	rax, qword ptr [rbx+0x10]
	mov	qword ptr [rbx+rcx+0x10], rax
	inc	edx
	add	rbx, 24
	jmp	$_156

$_157:
	leave
	pop	rbx
	ret

ExpandText:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 280
	mov	dword ptr [rbp-0xC], 0
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp-0xC0], eax
	mov	byte ptr [rbp-0xC1], 0
	mov	byte ptr [rbp-0xC2], 0
	mov	rax, qword ptr [ModuleInfo+0x188+rip]
	sub	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [rbp-0xE8], rax
	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	mov	qword ptr [rbp-0xE0], rcx
	add	ecx, ecx
	call	MemAlloc@PLT
	mov	qword ptr [rbp-0xD8], rax
	add	qword ptr [rbp-0xE0], rax
	mov	rdi, rax
	mov	rax, qword ptr [rbp+0x28]
	mov	qword ptr [rbp-0xB8], rax
	mov	dword ptr [rbp-0x4], 0
$_158:	cmp	dword ptr [rbp-0x4], 0
	jl	$_192
	mov	eax, dword ptr [rbp-0x4]
	mov	rsi, qword ptr [rbp+rax*8-0xB8]
	jmp	$_190

$_159:	movzx	edx, byte ptr [ModuleInfo+0x1D4+rip]
	movsx	eax, byte ptr [rsi]
	cmp	al, 46
	jnz	$_160
	test	dl, dl
	jnz	$_161
$_160:	test	byte ptr [r15+rax], 0x40
	je	$_186
$_161:	cmp	dword ptr [rbp+0x38], 0
	jnz	$_162
	cmp	byte ptr [rbp-0xC1], 0
	jne	$_186
$_162:	mov	qword ptr [rbp-0xD0], rdi
$_163:	stosb
	inc	rsi
	movsx	eax, byte ptr [rsi]
	test	byte ptr [r15+rax], 0x44
	jnz	$_163
	mov	byte ptr [rdi], 0
	mov	rcx, qword ptr [rbp-0xD0]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x18], rax
	test	rax, rax
	je	$_185
	test	byte ptr [rax+0x14], 0x02
	je	$_185
	cmp	byte ptr [rax+0x18], 10
	jne	$_169
	mov	rdx, qword ptr [rbp-0xD0]
	cmp	byte ptr [rbp-0xC1], 0
	jz	$_164
	cmp	byte ptr [rdx-0x1], 38
	jz	$_164
	cmp	byte ptr [rsi], 38
	jne	$_190
$_164:	cmp	dword ptr [rbp+0x38], 0
	jz	$_167
	cmp	byte ptr [rdx-0x1], 38
	jnz	$_165
	dec	rdx
$_165:	cmp	byte ptr [rsi], 38
	jnz	$_166
	inc	rsi
$_166:	jmp	$_168

$_167:	cmp	rdx, qword ptr [rbp-0xD8]
	jbe	$_168
	cmp	byte ptr [rdx-0x1], 37
	jnz	$_168
	dec	rdx
$_168:	mov	rdi, rdx
	mov	qword ptr [rbp-0xD0], rdx
	mov	dword ptr [rbp-0xC], 1
	mov	eax, dword ptr [rbp-0x4]
	inc	dword ptr [rbp-0x4]
	mov	qword ptr [rbp+rax*8-0xB8], rsi
	mov	rsi, qword ptr [rbp-0xE0]
	mov	rax, qword ptr [rbp-0x18]
	mov	rdx, qword ptr [rax+0x28]
	mov	rcx, rsi
	call	tstrcpy@PLT
	mov	rcx, rax
	call	tstrlen@PLT
	mov	edx, eax
	mov	rax, rsi
	add	edx, 8
	and	edx, 0xFFFFFFF8
	add	rax, rdx
	mov	qword ptr [rbp-0xE0], rax
	jmp	$_184

$_169:	cmp	byte ptr [rax+0x18], 9
	jne	$_183
	test	byte ptr [rax+0x38], 0x02
	je	$_183
	mov	rcx, rsi
	jmp	$_171

$_170:	inc	rcx
$_171:	movzx	eax, byte ptr [rcx]
	test	byte ptr [r15+rax], 0x08
	jnz	$_170
	cmp	al, 40
	jne	$_182
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp-0x10], eax
	inc	dword ptr [rbp-0x10]
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp-0x10]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	edx, dword ptr [rbp-0x10]
	imul	ecx, edx, 24
	add	rcx, qword ptr [ModuleInfo+0x180+rip]
	xor	eax, eax
$_172:	cmp	edx, dword ptr [ModuleInfo+0x220+rip]
	jge	$_175
	cmp	byte ptr [rcx], 40
	jnz	$_173
	inc	eax
	jmp	$_174

$_173:	cmp	byte ptr [rcx], 41
	jnz	$_174
	dec	eax
	jnz	$_174
	add	rcx, 24
	jmp	$_175

$_174:	inc	edx
	add	rcx, 24
	jmp	$_172

$_175:	mov	rdx, qword ptr [rbp-0xD0]
	cmp	byte ptr [rbp-0xC1], 0
	jz	$_176
	cmp	byte ptr [rdx-0x1], 38
	jz	$_176
	cmp	byte ptr [rcx], 38
	jz	$_176
	mov	eax, dword ptr [rbp-0xC0]
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	jmp	$_190

$_176:	cmp	dword ptr [rbp+0x38], 0
	jz	$_178
	cmp	byte ptr [rdx-0x1], 38
	jnz	$_177
	dec	qword ptr [rbp-0xD0]
$_177:	jmp	$_179

$_178:	cmp	rdx, qword ptr [rbp-0xD8]
	jbe	$_179
	cmp	byte ptr [rdx-0x1], 37
	jnz	$_179
	dec	qword ptr [rbp-0xD0]
$_179:	lea	rax, [rbp-0x8]
	mov	qword ptr [rsp+0x28], rax
	mov	dword ptr [rsp+0x20], 0
	mov	r9, rdi
	mov	r8, qword ptr [ModuleInfo+0x180+rip]
	mov	edx, dword ptr [rbp-0x10]
	mov	rcx, qword ptr [rbp-0x18]
	call	RunMacro
	mov	dword ptr [rbp-0xC], eax
	mov	ecx, dword ptr [rbp-0xC0]
	mov	dword ptr [ModuleInfo+0x220+rip], ecx
	mov	rcx, qword ptr [rbp-0xE8]
	add	rcx, qword ptr [StringBuffer+rip]
	mov	qword ptr [ModuleInfo+0x188+rip], rcx
	cmp	eax, -1
	jnz	$_180
	mov	rcx, qword ptr [rbp-0xD8]
	call	MemFree@PLT
	mov	eax, dword ptr [rbp-0xC]
	jmp	$_198

$_180:	imul	ebx, eax, 24
	add	rbx, qword ptr [ModuleInfo+0x180+rip]
	mov	rsi, qword ptr [rbx-0x8]
	mov	rcx, qword ptr [rbx-0x10]
	call	tstrlen@PLT
	add	rsi, rax
	cmp	dword ptr [rbp+0x38], 0
	jz	$_181
	cmp	byte ptr [rsi], 38
	jnz	$_181
	inc	rsi
$_181:	mov	eax, dword ptr [rbp-0x4]
	inc	dword ptr [rbp-0x4]
	mov	qword ptr [rbp+rax*8-0xB8], rsi
	mov	rcx, rdi
	call	tstrlen@PLT
	mov	rsi, rdi
	mov	rdi, qword ptr [rbp-0xE0]
	lea	rcx, [rax+0x1]
	rep movsb
	mov	rsi, qword ptr [rbp-0xE0]
	mov	edx, eax
	mov	rax, rsi
	add	edx, 8
	and	edx, 0xFFFFFFF8
	add	rax, rdx
	mov	qword ptr [rbp-0xE0], rax
	mov	rdi, qword ptr [rbp-0xD0]
	mov	dword ptr [rbp-0xC], 1
$_182:	jmp	$_184

$_183:	cmp	byte ptr [rax+0x18], 9
	jnz	$_184
	mov	byte ptr [rbp-0xC2], 1
$_184:	cmp	dword ptr [rbp-0x4], 20
	jnz	$_185
	mov	ecx, 2123
	call	asmerr@PLT
	jmp	$_191

$_185:	jmp	$_190

$_186:	mov	al, byte ptr [rsi]
	cmp	al, 34
	jz	$_187
	cmp	al, 39
	jnz	$_189
$_187:	cmp	byte ptr [rbp-0xC1], 0
	jnz	$_188
	mov	byte ptr [rbp-0xC1], al
	jmp	$_189

$_188:	cmp	al, byte ptr [rbp-0xC1]
	jnz	$_189
	mov	byte ptr [rbp-0xC1], 0
$_189:	movsb
$_190:	cmp	byte ptr [rsi], 0
	jne	$_159
$_191:	dec	dword ptr [rbp-0x4]
	jmp	$_158

$_192:	xor	eax, eax
	stosb
	mov	rax, qword ptr [rbp-0xE8]
	add	rax, qword ptr [StringBuffer+rip]
	mov	qword ptr [ModuleInfo+0x188+rip], rax
	cmp	dword ptr [rbp-0xC], 1
	jnz	$_193
	mov	rcx, rdi
	mov	rsi, qword ptr [rbp-0xD8]
	sub	rcx, rsi
	mov	rdi, qword ptr [rbp+0x28]
	rep movsb
$_193:	mov	rcx, qword ptr [rbp-0xD8]
	call	MemFree@PLT
	cmp	dword ptr [rbp+0x38], 0
	jz	$_197
	mov	rbx, qword ptr [ModuleInfo+0x180+rip]
	cmp	dword ptr [rbp-0xC], 1
	jnz	$_194
	mov	r9d, 1
	mov	r8, rbx
	xor	edx, edx
	mov	rcx, qword ptr [rbx+0x10]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
$_194:	cmp	dword ptr [rbp-0xC], 1
	jz	$_195
	cmp	byte ptr [rbp-0xC2], 0
	jz	$_197
$_195:	mov	rcx, rbx
	call	DelayExpand@PLT
	test	rax, rax
	jz	$_196
	mov	dword ptr [rbp-0xC], 0
	jmp	$_197

$_196:	mov	rdx, rbx
	mov	rcx, qword ptr [rbx+0x10]
	call	ExpandLine
	mov	dword ptr [rbp-0xC], eax
$_197:	mov	eax, dword ptr [rbp-0xC]
$_198:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_199:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 88
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp-0x4], eax
	mov	dword ptr [rbp-0x1C], 0
	mov	byte ptr [rbp-0x1D], 1
	cmp	dword ptr [rbp+0x40], 20
	jl	$_200
	mov	ecx, 2123
	call	asmerr@PLT
	jmp	$_212

$_200:	mov	byte ptr [rbp-0x1E], 0
	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	cmp	ecx, 2048
	jbe	$_201
	mov	byte ptr [rbp-0x1E], 1
	call	MemAlloc@PLT
	jmp	$_202

$_201:	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x30]
$_202:	mov	qword ptr [rbp-0x28], rax
	jmp	$_209

$_203:	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rbp-0x8], eax
	inc	dword ptr [rbp-0x8]
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp-0x8]
	mov	rcx, qword ptr [rbp+0x28]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	byte ptr [rbp-0x1D], 0
$_204:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp-0x8], eax
	jge	$_209
	imul	ebx, dword ptr [rbp-0x8], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 8
	jne	$_208
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	mov	qword ptr [rbp-0x18], rax
	test	rax, rax
	je	$_206
	cmp	byte ptr [rax+0x18], 9
	jne	$_206
	test	byte ptr [rax+0x14], 0x02
	je	$_206
	test	byte ptr [rax+0x38], 0x02
	je	$_206
	cmp	byte ptr [rbx+0x18], 40
	jne	$_206
	cmp	dword ptr [rbp+0x38], 0
	jnz	$_206
	mov	rcx, qword ptr [rbx+0x10]
	sub	rcx, qword ptr [rbp+0x28]
	mov	rdi, qword ptr [rbp-0x28]
	mov	rsi, qword ptr [rbp+0x28]
	rep movsb
	mov	edx, dword ptr [rbp-0x8]
	inc	edx
	lea	rax, [rbp-0x10]
	mov	qword ptr [rsp+0x28], rax
	mov	dword ptr [rsp+0x20], 0
	mov	r9, rdi
	mov	r8, qword ptr [rbp+0x30]
	mov	rcx, qword ptr [rbp-0x18]
	call	RunMacro
	mov	dword ptr [rbp-0x8], eax
	cmp	dword ptr [rbp-0x8], 0
	jge	$_205
	mov	dword ptr [rbp-0x1C], -1
	jmp	$_210

$_205:	imul	ebx, dword ptr [rbp-0x8], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	rdx, qword ptr [rbx+0x10]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rdx, qword ptr [rbp-0x28]
	mov	rcx, qword ptr [rbp+0x28]
	call	tstrcpy@PLT
	mov	byte ptr [rbp-0x1D], 1
	jmp	$_209

	jmp	$_208

$_206:	test	rax, rax
	jz	$_208
	cmp	byte ptr [rax+0x18], 10
	jnz	$_208
	test	byte ptr [rax+0x14], 0x02
	jz	$_208
	mov	rsi, qword ptr [rbp+0x28]
	mov	rdi, qword ptr [rbp-0x28]
	mov	rcx, qword ptr [rbx+0x10]
	sub	rcx, rsi
	rep movsb
	mov	rdx, qword ptr [rax+0x28]
	mov	rcx, rdi
	call	tstrcpy@PLT
	mov	ecx, dword ptr [rbp+0x40]
	inc	ecx
	mov	r9d, ecx
	mov	r8d, dword ptr [rbp+0x38]
	mov	rdx, qword ptr [rbp+0x30]
	mov	rcx, rdi
	call	$_199
	cmp	eax, -1
	jnz	$_207
	mov	dword ptr [rbp-0x1C], eax
	jmp	$_210

$_207:	mov	rax, qword ptr [rbp-0x18]
	mov	edx, dword ptr [rax+0x10]
	add	rdx, qword ptr [rbx+0x10]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rdx, qword ptr [rbp-0x28]
	mov	rcx, qword ptr [rbp+0x28]
	call	tstrcpy@PLT
	mov	byte ptr [rbp-0x1D], 1
	jmp	$_209

$_208:	inc	dword ptr [rbp-0x8]
	jmp	$_204

$_209:	cmp	byte ptr [rbp-0x1D], 1
	je	$_203
$_210:	cmp	byte ptr [rbp-0x1E], 0
	jz	$_211
	mov	rcx, qword ptr [rbp-0x28]
	call	MemFree@PLT
$_211:	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	eax, dword ptr [rbp-0x1C]
$_212:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_213:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	dword ptr [rbp-0x1C], 0
	mov	byte ptr [rbp-0x1D], 0
	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	cmp	ecx, 2048
	jbe	$_214
	mov	byte ptr [rbp-0x1D], 1
	call	MemAlloc@PLT
	jmp	$_215

$_214:	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x20]
$_215:	mov	qword ptr [rbp-0x28], rax
	imul	ebx, dword ptr [rbp+0x30], 24
	add	rbx, qword ptr [rbp+0x38]
	mov	esi, dword ptr [rbp+0x40]
	add	rsi, qword ptr [rbx+0x10]
	mov	rcx, rsi
	call	tstrlen@PLT
	inc	rax
	mov	dword ptr [rbp-0x18], eax
	mov	rdi, qword ptr [rbp-0x28]
	mov	ecx, eax
	rep movsb
	mov	rdi, qword ptr [rbx+0x10]
	mov	rcx, qword ptr [rbp+0x28]
	call	tstrlen@PLT
	mov	dword ptr [rbp-0x14], eax
	cmp	dword ptr [rbp+0x50], 0
	jz	$_219
	add	dword ptr [rbp-0x14], 2
	mov	rsi, qword ptr [rbp+0x28]
	mov	al, byte ptr [rsi]
$_216:	test	al, al
	jz	$_219
	cmp	al, 60
	jz	$_217
	cmp	al, 62
	jz	$_217
	cmp	al, 33
	jnz	$_218
$_217:	inc	dword ptr [rbp-0x14]
$_218:	inc	rsi
	mov	al, byte ptr [rsi]
	jmp	$_216

$_219:
	mov	eax, dword ptr [rbp+0x40]
	cmp	dword ptr [rbp-0x14], eax
	jbe	$_220
	mov	eax, dword ptr [rbp+0x48]
	add	eax, dword ptr [rbp-0x14]
	sub	eax, dword ptr [rbp+0x40]
	add	eax, dword ptr [rbp-0x18]
	cmp	eax, dword ptr [ModuleInfo+0x174+rip]
	jc	$_220
	mov	ecx, 2039
	call	asmerr@PLT
	mov	dword ptr [rbp-0x1C], eax
	jmp	$_228

$_220:	cmp	dword ptr [rbp+0x50], 0
	jz	$_225
	mov	byte ptr [rdi], 60
	inc	rdi
	mov	rsi, qword ptr [rbp+0x28]
$_221:	cmp	byte ptr [rsi], 0
	jz	$_224
	mov	al, byte ptr [rsi]
	cmp	al, 60
	jz	$_222
	cmp	al, 62
	jz	$_222
	cmp	al, 33
	jnz	$_223
$_222:	mov	byte ptr [rdi], 33
	inc	rdi
$_223:	mov	byte ptr [rdi], al
	inc	rdi
	inc	rsi
	jmp	$_221

$_224:	mov	byte ptr [rdi], 62
	inc	rdi
	jmp	$_226

$_225:	mov	ecx, dword ptr [rbp-0x14]
	mov	rsi, qword ptr [rbp+0x28]
	rep movsb
$_226:	mov	ecx, dword ptr [rbp-0x18]
	mov	rsi, qword ptr [rbp-0x28]
	rep movsb
	mov	ecx, dword ptr [rbp+0x30]
	inc	ecx
	add	rbx, 24
	mov	eax, dword ptr [rbp+0x40]
	mov	edx, dword ptr [rbp-0x14]
$_227:	cmp	ecx, dword ptr [ModuleInfo+0x220+rip]
	jg	$_228
	sub	qword ptr [rbx+0x10], rax
	add	qword ptr [rbx+0x10], rdx
	inc	ecx
	add	rbx, 24
	jmp	$_227

$_228:
	cmp	byte ptr [rbp-0x1D], 0
	jz	$_229
	mov	rcx, qword ptr [rbp-0x28]
	call	MemFree@PLT
$_229:	mov	eax, dword ptr [rbp-0x1C]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_230:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 200
	mov	eax, dword ptr [rdx]
	mov	dword ptr [rbp-0xC], eax
	mov	eax, dword ptr [rbp+0x48]
	mov	dword ptr [rbp-0x14], eax
	mov	byte ptr [rbp-0x15], 0
	mov	dword ptr [rbp-0x8C], 0
$_231:	mov	eax, dword ptr [rbp+0x40]
	cmp	dword ptr [rbp-0xC], eax
	jge	$_261
	imul	ebx, dword ptr [rbp-0xC], 24
	add	rbx, qword ptr [rbp+0x38]
	cmp	byte ptr [rbx], 44
	je	$_261
	cmp	byte ptr [rbx], 37
	jnz	$_232
	cmp	dword ptr [rbp-0x14], 0
	jz	$_232
	cmp	byte ptr [rbp-0x15], 0
	jnz	$_232
	mov	byte ptr [rbp-0x15], 1
	mov	dword ptr [rbp-0x14], 0
	mov	dword ptr [rbp+0x50], 0
	mov	eax, dword ptr [rbp-0xC]
	mov	dword ptr [rbp-0x4], eax
	jmp	$_260

$_232:	cmp	byte ptr [rbx], 8
	jne	$_260
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	mov	rsi, rax
	test	rsi, rsi
	je	$_260
	cmp	byte ptr [rsi+0x18], 9
	jne	$_250
	mov	ecx, dword ptr [rbp-0xC]
	mov	edi, ecx
	test	byte ptr [rsi+0x38], 0x02
	je	$_241
	cmp	byte ptr [rbx+0x18], 40
	jne	$_260
	inc	dword ptr [rbp-0xC]
	add	rbx, 24
	cmp	dword ptr [rbp+0x50], 1
	jnz	$_237
	inc	dword ptr [rbp-0xC]
	add	rbx, 24
	mov	ecx, 1
$_233:	mov	eax, dword ptr [rbp+0x40]
	cmp	dword ptr [rbp-0xC], eax
	jge	$_236
	cmp	byte ptr [rbx], 40
	jnz	$_234
	inc	ecx
	jmp	$_235

$_234:	cmp	byte ptr [rbx], 41
	jnz	$_235
	dec	ecx
	jz	$_236
$_235:	inc	dword ptr [rbp-0xC]
	add	rbx, 24
	jmp	$_233

$_236:	dec	dword ptr [rbp-0xC]
	sub	rbx, 24
	jmp	$_260

$_237:	xor	edx, edx
	cmp	edi, 1
	jnz	$_238
	mov	edx, 1
$_238:	lea	rax, [rbp-0x1C]
	mov	qword ptr [rsp+0x28], rax
	mov	dword ptr [rsp+0x20], edx
	mov	r9, qword ptr [rbp+0x58]
	mov	r8, qword ptr [rbp+0x38]
	mov	edx, dword ptr [rbp-0xC]
	mov	rcx, rsi
	call	RunMacro
	mov	dword ptr [rbp-0xC], eax
	cmp	eax, -1
	je	$_267
	imul	ebx, dword ptr [rbp-0xC], 24
	add	rbx, qword ptr [rbp+0x38]
	test	edi, edi
	jz	$_239
	cmp	dword ptr [rbp-0x14], 0
	jnz	$_239
	xor	r9d, r9d
	mov	r8d, dword ptr [rbp+0x50]
	mov	rdx, qword ptr [rbp+0x38]
	mov	rcx, qword ptr [rbp+0x58]
	call	$_199
	cmp	eax, -1
	je	$_267
$_239:	imul	ecx, edi, 24
	mov	rax, qword ptr [rbx-0x8]
	inc	rax
	add	rcx, qword ptr [rbp+0x38]
	sub	rax, qword ptr [rcx+0x10]
	mov	dword ptr [rbp-0x10], eax
	mov	edx, edi
	inc	edx
	mov	ecx, edx
	sub	ecx, dword ptr [rbp-0xC]
	mov	r9d, dword ptr [ModuleInfo+0x220+rip]
	mov	r8d, ecx
	mov	rcx, qword ptr [rbp+0x38]
	call	$_152
	mov	eax, edi
	inc	eax
	sub	eax, dword ptr [rbp-0xC]
	add	dword ptr [ModuleInfo+0x220+rip], eax
	mov	eax, dword ptr [rbp+0x40]
	cmp	dword ptr [ModuleInfo+0x220+rip], eax
	jge	$_240
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp+0x40], eax
$_240:	imul	ecx, edi, 24
	add	rcx, qword ptr [rbp+0x38]
	mov	rdx, qword ptr [rcx+0x10]
	sub	rdx, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rbp-0x14]
	mov	dword ptr [rsp+0x28], eax
	mov	dword ptr [rsp+0x20], edx
	mov	r9d, dword ptr [rbp-0x10]
	mov	r8, qword ptr [rbp+0x38]
	mov	edx, edi
	mov	rcx, qword ptr [rbp+0x58]
	call	$_213
	cmp	eax, -1
	je	$_267
	mov	dword ptr [rbp-0x8C], 1
	mov	dword ptr [rbp-0xC], edi
	jmp	$_249

$_241:	mov	edx, dword ptr [rbp-0xC]
	mov	rcx, qword ptr [rbp+0x38]
	test	edx, edx
	jz	$_243
	cmp	edx, 2
	jnz	$_242
	cmp	byte ptr [rcx+0x18], 58
	jz	$_243
	cmp	byte ptr [rcx+0x18], 13
	jz	$_243
$_242:	cmp	edx, 1
	jnz	$_244
	test	byte ptr [rsi+0x38], 0x04
	jz	$_244
$_243:	jmp	$_245

$_244:	jmp	$_260

$_245:	cmp	edx, 2
	jnz	$_246
	mov	rdx, qword ptr [rbp+0x38]
	mov	rcx, qword ptr [rbp+0x28]
	call	WriteCodeLabel@PLT
	cmp	eax, -1
	je	$_267
	mov	edx, dword ptr [rbp-0xC]
$_246:	mov	ecx, 2
	cmp	edx, 1
	jnz	$_247
	or	ecx, 0x01
$_247:	inc	edx
	lea	rax, [rbp-0x1C]
	mov	qword ptr [rsp+0x28], rax
	mov	dword ptr [rsp+0x20], ecx
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x38]
	mov	rcx, rsi
	call	RunMacro
	cmp	eax, -1
	jnz	$_248
	jmp	$_267

$_248:	mov	rax, -2
	jmp	$_267

$_249:	jmp	$_260

$_250:	cmp	byte ptr [rsi+0x18], 10
	jne	$_260
	cmp	byte ptr [rbx-0x18], 46
	jnz	$_257
	mov	ecx, dword ptr [rbp-0xC]
	sub	ecx, 2
	lea	rdx, [rbx-0x30]
	jmp	$_252

$_251:	sub	ecx, 2
	lea	rdx, [rdx-0x30]
$_252:	cmp	byte ptr [rdx-0x18], 46
	jz	$_251
	cmp	byte ptr [rdx], 93
	jnz	$_256
	xor	eax, eax
$_253:	cmp	rdx, qword ptr [rbp+0x38]
	jbe	$_256
	cmp	byte ptr [rdx], 91
	jnz	$_254
	dec	eax
	jz	$_256
	jmp	$_255

$_254:	cmp	byte ptr [rdx], 93
	jnz	$_255
	inc	eax
$_255:	sub	rdx, 24
	dec	ecx
	jmp	$_253

$_256:	mov	dword ptr [rbp-0x8], ecx
	mov	byte ptr [rsp+0x20], 1
	lea	r9, [rbp-0x88]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [rbp-0x8]
	call	EvalOperand@PLT
	cmp	eax, -1
	jz	$_257
	cmp	dword ptr [rbp-0x4C], 1
	jnz	$_257
	cmp	qword ptr [rbp-0x30], 0
	jz	$_257
	jmp	$_260

$_257:	mov	rdx, qword ptr [rsi+0x28]
	mov	rcx, qword ptr [rbp+0x58]
	call	tstrcpy@PLT
	xor	r9d, r9d
	mov	r8d, dword ptr [rbp+0x50]
	mov	rdx, qword ptr [rbp+0x38]
	mov	rcx, qword ptr [rbp+0x58]
	call	$_199
	cmp	eax, -1
	jnz	$_258
	jmp	$_267

$_258:	mov	rcx, qword ptr [rbx+0x8]
	call	tstrlen@PLT
	mov	edx, eax
	mov	rcx, qword ptr [rbx+0x10]
	sub	rcx, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rbp-0x14]
	mov	dword ptr [rsp+0x28], eax
	mov	dword ptr [rsp+0x20], ecx
	mov	r9d, edx
	mov	r8, qword ptr [rbp+0x38]
	mov	edx, dword ptr [rbp-0xC]
	mov	rcx, qword ptr [rbp+0x58]
	call	$_213
	cmp	eax, -1
	jnz	$_259
	jmp	$_267

$_259:	mov	dword ptr [rbp-0x8C], 1
$_260:	inc	dword ptr [rbp-0xC]
	jmp	$_231

$_261:	mov	ecx, dword ptr [rbp-0xC]
	mov	rax, qword ptr [rbp+0x30]
	mov	dword ptr [rax], ecx
	cmp	byte ptr [rbp-0x15], 0
	je	$_266
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp-0x90], eax
	mov	rbx, qword ptr [rbp+0x38]
	mov	edx, dword ptr [rbp-0x4]
	lea	rax, [rdx+0x1]
	cmp	eax, dword ptr [rbp-0xC]
	jnz	$_262
	mov	dword ptr [rbp-0x88], 0
	mov	dword ptr [rbp-0xC], edx
	jmp	$_265

$_262:	mov	dword ptr [rbp-0xC], edx
	inc	edx
	imul	ecx, ecx, 24
	imul	edx, edx, 24
	mov	rcx, qword ptr [rbx+rcx+0x10]
	mov	rsi, qword ptr [rbx+rdx+0x10]
	mov	rdi, qword ptr [rbp+0x58]
	sub	rcx, rsi
	rep movsb
	mov	byte ptr [rdi], 0
	mov	edi, dword ptr [rbp-0x90]
	inc	edi
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x38]
	mov	edx, edi
	mov	rcx, qword ptr [rbp+0x58]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	dword ptr [rbp-0x8], edi
	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x88]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x38]
	lea	rcx, [rbp-0x8]
	call	EvalOperand@PLT
	cmp	eax, -1
	jnz	$_263
	mov	dword ptr [rbp-0x88], 0
	jmp	$_264

$_263:	cmp	dword ptr [rbp-0x4C], 0
	jz	$_264
	mov	ecx, 2026
	call	asmerr@PLT
	mov	dword ptr [rbp-0x88], 0
$_264:	mov	eax, dword ptr [rbp-0x90]
	mov	dword ptr [ModuleInfo+0x220+rip], eax
$_265:	mov	dword ptr [rbp-0x84], 0
	mov	dword ptr [rsp+0x20], 0
	xor	r9d, r9d
	movzx	r8d, byte ptr [ModuleInfo+0x1C4+rip]
	mov	rdx, qword ptr [ModuleInfo+0x188+rip]
	mov	rcx, qword ptr [rbp-0x88]
	call	myltoa
	mov	rsi, qword ptr [rbp+0x30]
	mov	esi, dword ptr [rsi]
	imul	eax, esi, 24
	imul	edx, dword ptr [rbp-0xC], 24
	mov	rdi, qword ptr [rbx+rax+0x10]
	sub	rdi, qword ptr [rbx+rdx+0x10]
	add	rbx, rdx
	mov	rax, qword ptr [ModuleInfo+0x188+rip]
	mov	qword ptr [rbx+0x8], rax
	mov	eax, dword ptr [rbp-0xC]
	inc	eax
	mov	edx, eax
	sub	edx, esi
	mov	r9d, dword ptr [ModuleInfo+0x220+rip]
	mov	r8d, edx
	mov	edx, eax
	mov	rcx, qword ptr [rbp+0x38]
	call	$_152
	mov	eax, dword ptr [rbp-0xC]
	inc	eax
	sub	eax, esi
	add	dword ptr [ModuleInfo+0x220+rip], eax
	mov	rcx, qword ptr [rbx+0x10]
	sub	rcx, qword ptr [rbp+0x28]
	mov	eax, dword ptr [rbp+0x48]
	mov	dword ptr [rsp+0x28], eax
	mov	dword ptr [rsp+0x20], ecx
	mov	r9d, edi
	mov	r8, qword ptr [rbp+0x38]
	mov	edx, dword ptr [rbp-0xC]
	mov	rcx, qword ptr [ModuleInfo+0x188+rip]
	call	$_213
	cmp	eax, -1
	jz	$_267
	mov	dword ptr [rbp-0x8C], 1
$_266:	mov	eax, dword ptr [rbp-0x8C]
$_267:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

ExpandLineItems:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 80
	mov	byte ptr [rbp-0x5], 0
	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	cmp	ecx, 2048
	jbe	$_268
	mov	byte ptr [rbp-0x5], 1
	call	MemAlloc@PLT
	jmp	$_269

$_268:	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x40]
$_269:	mov	qword ptr [rbp-0x10], rax
	xor	esi, esi
$_270:	mov	edi, 0
	mov	eax, dword ptr [rbp+0x28]
	mov	dword ptr [rbp-0x4], eax
$_271:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp-0x4], eax
	jge	$_274
	mov	rax, qword ptr [rbp-0x10]
	mov	qword ptr [rsp+0x30], rax
	mov	eax, dword ptr [rbp+0x40]
	mov	dword ptr [rsp+0x28], eax
	mov	eax, dword ptr [rbp+0x38]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [ModuleInfo+0x220+rip]
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp-0x4]
	mov	rcx, qword ptr [rbp+0x20]
	call	$_230
	cmp	eax, -1
	jz	$_276
	cmp	eax, 1
	jnz	$_272
	mov	edi, eax
$_272:	imul	eax, dword ptr [rbp-0x4], 24
	add	rax, qword ptr [rbp+0x30]
	cmp	byte ptr [rax], 44
	jnz	$_273
	inc	dword ptr [rbp-0x4]
$_273:	jmp	$_271

$_274:	test	edi, edi
	jz	$_276
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp+0x28]
	mov	rcx, qword ptr [rbp+0x20]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	cmp	esi, 20
	jnz	$_275
	mov	ecx, 2123
	call	asmerr@PLT
	jmp	$_276

$_275:	inc	esi
	jmp	$_270

$_276:
	cmp	byte ptr [rbp-0x5], 0
	jz	$_277
	mov	rcx, qword ptr [rbp-0x10]
	call	MemFree@PLT
$_277:	mov	eax, esi
	leave
	pop	rdi
	pop	rsi
	ret

ExpandLiterals:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	xor	eax, eax
	mov	rbx, rdx
$_278:	cmp	ecx, dword ptr [ModuleInfo+0x220+rip]
	jge	$_281
	imul	edx, ecx, 24
	cmp	byte ptr [rbx+rdx], 9
	jnz	$_280
	cmp	dword ptr [rbx+rdx+0x4], 0
	jz	$_280
	cmp	byte ptr [rbx+rdx+0x1], 60
	jz	$_279
	cmp	byte ptr [rbx+rdx+0x1], 123
	jnz	$_280
$_279:	inc	eax
$_280:	inc	ecx
	jmp	$_278

$_281:
	test	eax, eax
	jz	$_282
	imul	ecx, dword ptr [rbp+0x18], 24
	add	rbx, rcx
	xor	r8d, r8d
	mov	rdx, qword ptr [rbp+0x20]
	mov	rcx, qword ptr [rbx+0x10]
	call	ExpandText
	cmp	rax, 1
	jnz	$_282
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x20]
	mov	edx, dword ptr [rbp+0x18]
	mov	rcx, qword ptr [rbx+0x10]
	call	Tokenize@PLT
$_282:	leave
	pop	rbx
	ret

ExpandLine:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 120
	mov	byte ptr [rbp-0x29], 0
	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	cmp	ecx, 2048
	jbe	$_283
	mov	byte ptr [rbp-0x29], 1
	call	MemAlloc@PLT
	jmp	$_284

$_283:	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x40]
$_284:	mov	qword ptr [rbp-0x38], rax
	mov	dword ptr [rbp-0x10], 0
$_285:	cmp	dword ptr [rbp-0x10], 20
	jge	$_358
	xor	esi, esi
	mov	dword ptr [rbp-0x8], esi
	mov	dword ptr [rbp-0x4], esi
	mov	dword ptr [rbp-0x14], esi
	mov	rbx, qword ptr [rbp+0x30]
	cmp	dword ptr [ModuleInfo+0x220+rip], 2
	jle	$_290
	cmp	byte ptr [rbx+0x18], 58
	jz	$_286
	cmp	byte ptr [rbx+0x18], 13
	jnz	$_290
$_286:	cmp	byte ptr [rbx], 8
	jnz	$_287
	cmp	byte ptr [rbx+0x18], 58
	jz	$_287
	cmp	byte ptr [rbx+0x30], 8
	jz	$_288
$_287:	jmp	$_358

$_288:	mov	rcx, qword ptr [rbx+0x38]
	call	SymFind@PLT
	test	rax, rax
	jz	$_289
	cmp	byte ptr [rax+0x18], 9
	jnz	$_289
	jmp	$_358

$_289:	cmp	byte ptr [rbx+0x30], 3
	jnz	$_290
	add	rbx, 48
$_290:	mov	rdx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 3
	jne	$_299
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbx+0x4], 12
	mov	eax, dword ptr [r11+rax]
	mov	dword ptr [rbp-0xC], eax
	test	eax, 0x2
	jz	$_297
	mov	dword ptr [rbp-0x8], -1
	cmp	byte ptr [rbx+0x1], 10
	jnz	$_296
	cmp	dword ptr [rbx+0x4], 437
	jz	$_291
	cmp	dword ptr [rbx+0x4], 438
	jnz	$_296
$_291:	test	esi, esi
	jz	$_292
	mov	rax, qword ptr [rbp-0x38]
	mov	qword ptr [rsp+0x30], rax
	mov	dword ptr [rsp+0x28], 0
	mov	dword ptr [rsp+0x20], 0
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp-0x4]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_230
	mov	dword ptr [rbp-0x14], eax
$_292:	jmp	$_294

$_293:	inc	esi
	add	rbx, 24
$_294:	cmp	byte ptr [rbx], 0
	jz	$_295
	cmp	byte ptr [rbx], 44
	jnz	$_293
$_295:	mov	dword ptr [rbp-0x4], esi
$_296:	jmp	$_298

$_297:	test	eax, 0x4
	jz	$_298
	mov	dword ptr [rbp-0x14], 0
	jmp	$_358

$_298:	jmp	$_321

$_299:	cmp	dword ptr [ModuleInfo+0x220+rip], 1
	jle	$_315
	cmp	byte ptr [rdx+0x18], 3
	jne	$_315
	mov	al, byte ptr [rdx+0x19]
	jmp	$_313

$_300:	mov	dword ptr [rbp-0x8], -1
	mov	dword ptr [rbp-0x4], 2
	jmp	$_314

$_301:	mov	dword ptr [rbp-0x8], 1
	mov	dword ptr [rbp-0x4], 2
	jmp	$_314

$_302:	mov	rax, qword ptr [rbp-0x38]
	mov	qword ptr [rsp+0x30], rax
	mov	dword ptr [rsp+0x28], 0
	mov	dword ptr [rsp+0x20], 0
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp-0x4]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_230
	mov	dword ptr [rbp-0x14], eax
	mov	dword ptr [rbp-0x8], 1
	mov	dword ptr [rbp-0x4], 2
	jmp	$_314

$_303:	mov	rax, qword ptr [rbp-0x38]
	mov	qword ptr [rsp+0x30], rax
	mov	dword ptr [rsp+0x28], 0
	mov	dword ptr [rsp+0x20], 0
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp-0x4]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_230
	mov	dword ptr [rbp-0x14], eax
	mov	esi, 2
	xor	eax, eax
	xor	ecx, ecx
$_304:	cmp	esi, dword ptr [ModuleInfo+0x220+rip]
	jge	$_308
	imul	ebx, esi, 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 40
	jnz	$_305
	inc	eax
	jmp	$_307

$_305:	cmp	byte ptr [rbx], 41
	jnz	$_306
	dec	eax
	jmp	$_307

$_306:	cmp	byte ptr [rbx], 44
	jnz	$_307
	test	eax, eax
	jnz	$_307
	inc	ecx
$_307:	inc	esi
	jmp	$_304

$_308:	mov	eax, 3
	cmp	ecx, 1
	jbe	$_309
	mov	eax, 6
$_309:	mov	dword ptr [rbp-0x8], eax
	mov	dword ptr [rbp-0x4], 2
	jmp	$_314

$_310:	mov	rcx, qword ptr [rdx+0x8]
	call	SymFind@PLT
	test	rax, rax
	jz	$_311
	cmp	byte ptr [rax+0x18], 9
	jz	$_311
	mov	rax, qword ptr [rbp-0x38]
	mov	qword ptr [rsp+0x30], rax
	mov	dword ptr [rsp+0x28], 0
	mov	dword ptr [rsp+0x20], 0
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp-0x4]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_230
	mov	dword ptr [rbp-0x14], eax
$_311:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp-0x4], eax
	jmp	$_314

$_312:	mov	dword ptr [rbp-0x14], 0
	jmp	$_358

$_313:	cmp	al, 5
	je	$_300
	cmp	al, 6
	je	$_301
	cmp	al, 21
	je	$_302
	cmp	al, 20
	je	$_303
	cmp	al, 4
	je	$_310
	cmp	al, 44
	jz	$_312
$_314:	jmp	$_321

$_315:	mov	rax, qword ptr [rbp-0x38]
	mov	qword ptr [rsp+0x30], rax
	mov	dword ptr [rsp+0x28], 0
	mov	dword ptr [rsp+0x20], 0
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp-0x4]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_230
	mov	dword ptr [rbp-0x14], eax
	cmp	eax, -1
	jz	$_316
	cmp	eax, -2
	jnz	$_317
$_316:	jmp	$_358

$_317:	cmp	dword ptr [rbp-0x14], 1
	jnz	$_318
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x30]
	xor	edx, edx
	mov	rcx, qword ptr [rbp+0x28]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	jmp	$_357

$_318:	mov	rax, qword ptr [rbp+0x30]
	cmp	dword ptr [rbp-0x4], 1
	jnz	$_321
	cmp	byte ptr [rax], 8
	jnz	$_321
	cmp	byte ptr [rax+0x18], 8
	jnz	$_321
	mov	rax, qword ptr [rbp-0x38]
	mov	qword ptr [rsp+0x30], rax
	mov	dword ptr [rsp+0x28], 0
	mov	dword ptr [rsp+0x20], 0
	mov	r9d, 2
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp-0x4]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_230
	mov	dword ptr [rbp-0x14], eax
	cmp	eax, -1
	jz	$_319
	cmp	eax, -2
	jnz	$_320
$_319:	jmp	$_358

$_320:	cmp	dword ptr [rbp-0x14], 1
	jnz	$_321
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x30]
	xor	edx, edx
	mov	rcx, qword ptr [rbp+0x28]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	jmp	$_357

$_321:	jmp	$_326

$_322:	mov	eax, dword ptr [rbp-0x8]
	and	eax, 0x01
	mov	dword ptr [rbp-0x18], eax
	cmp	dword ptr [rbp-0x8], -1
	jz	$_323
	shr	dword ptr [rbp-0x8], 1
$_323:	mov	rax, qword ptr [rbp-0x38]
	mov	qword ptr [rsp+0x30], rax
	mov	dword ptr [rsp+0x28], 0
	mov	eax, dword ptr [rbp-0x18]
	mov	dword ptr [rsp+0x20], eax
	mov	r9d, dword ptr [ModuleInfo+0x220+rip]
	mov	r8, qword ptr [rbp+0x30]
	lea	rdx, [rbp-0x4]
	mov	rcx, qword ptr [rbp+0x28]
	call	$_230
	cmp	eax, 0
	jge	$_324
	mov	dword ptr [rbp-0x14], eax
	jmp	$_358

$_324:	cmp	eax, 1
	jnz	$_325
	mov	dword ptr [rbp-0x14], 1
$_325:	imul	ebx, dword ptr [rbp-0x4], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [rbx], 44
	jnz	$_326
	inc	dword ptr [rbp-0x4]
$_326:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp-0x4], eax
	jl	$_322
	cmp	dword ptr [rbp-0x14], 1
	jnz	$_327
	mov	r9d, 5
	mov	r8, qword ptr [rbp+0x30]
	xor	edx, edx
	mov	rcx, qword ptr [rbp+0x28]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
$_327:	mov	rbx, qword ptr [rbp+0x30]
	cmp	dword ptr [ModuleInfo+0x220+rip], 2
	jle	$_356
	test	byte ptr [rbx+0x2], 0x40
	je	$_356
	test	byte ptr [rbx+0x2], 0x08
	jz	$_329
	lea	rsi, [DS0003+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	test	rax, rax
	jz	$_328
	cmp	byte ptr [rax+0x18], 7
	jnz	$_328
	lea	rsi, [DS0004+rip]
$_328:	mov	rdx, rsi
	mov	rcx, qword ptr [rbp-0x38]
	call	tstrcpy@PLT
	mov	rdx, qword ptr [rbx+0x10]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rdx, qword ptr [rbp-0x38]
	mov	rcx, qword ptr [rbp+0x28]
	call	tstrcpy@PLT
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x30]
	xor	edx, edx
	mov	rcx, rax
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
$_329:	cmp	byte ptr [rbx], 0
	je	$_356
	cmp	byte ptr [rbx+0x18], 13
	jne	$_355
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x28], rax
	mov	rcx, rax
	call	SymFind@PLT
	test	rax, rax
	jz	$_333
	cmp	byte ptr [rax+0x18], 7
	jnz	$_332
	jmp	$_331

$_330:	mov	rax, qword ptr [rax+0x20]
$_331:	cmp	qword ptr [rax+0x20], 0
	jnz	$_330
$_332:	mov	rcx, qword ptr [rax+0x8]
	mov	qword ptr [rbp-0x28], rcx
$_333:	xor	edi, edi
	mov	ecx, dword ptr [rbx+0x4C]
	cmp	byte ptr [rbx+0x48], 3
	jnz	$_336
	cmp	ecx, 508
	jz	$_334
	cmp	ecx, 507
	jnz	$_336
$_334:	inc	edi
	test	rax, rax
	jz	$_335
	test	byte ptr [rax+0x16], 0x01
	jz	$_335
	inc	edi
$_335:	jmp	$_339

$_336:	mov	al, byte ptr [rbx]
	mov	ah, byte ptr [rbx+0x30]
	cmp	al, 2
	jz	$_337
	cmp	byte ptr [rbx+0x48], 40
	jz	$_338
$_337:	cmp	al, 9
	jnc	$_339
	cmp	al, 2
	jbe	$_339
	cmp	ah, 9
	jnc	$_339
	cmp	ah, 2
	jbe	$_339
$_338:	inc	edi
$_339:	mov	dword ptr [rbp-0x1C], edi
	test	edi, edi
	jz	$_343
	mov	rdi, qword ptr [rbp-0x38]
	mov	rdx, qword ptr [rbp+0x30]
	mov	rsi, qword ptr [rdx+0x10]
	mov	rcx, qword ptr [rbx+0x10]
	sub	rcx, rsi
	rep movsb
	mov	rsi, qword ptr [rbp-0x28]
$_340:	lodsb
	stosb
	test	al, al
	jnz	$_340
	mov	byte ptr [rdi-0x1], 95
	mov	rdx, qword ptr [rbx+0x38]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstrcmp@PLT
	test	rax, rax
	jnz	$_342
	mov	rsi, qword ptr [rbp-0x28]
$_341:	lodsb
	stosb
	test	al, al
	jnz	$_341
	mov	byte ptr [rdi-0x1], 32
	mov	rsi, qword ptr [rbx+0x58]
	mov	edx, 96
	jmp	$_343

$_342:	mov	rsi, qword ptr [rbx+0x40]
	mov	edx, 72
$_343:	cmp	dword ptr [rbp-0x1C], 1
	jnz	$_344
	mov	rcx, rsi
	call	tstrlen@PLT
	mov	ecx, eax
	inc	ecx
	rep movsb
	jmp	$_353

$_344:	cmp	dword ptr [rbp-0x1C], 1
	jle	$_353
$_345:	cmp	byte ptr [rbx+rdx], 0
	jz	$_346
	cmp	byte ptr [rbx+rdx], 58
	jz	$_346
	cmp	byte ptr [rbx+rdx], 9
	jz	$_346
	add	rdx, 24
	jmp	$_345

$_346:	cmp	byte ptr [rbx+rdx], 58
	jnz	$_347
	cmp	byte ptr [rbx+rdx-0x18], 8
	jnz	$_347
	sub	rdx, 24
$_347:	mov	rcx, qword ptr [rbx+rdx+0x10]
	sub	rcx, rsi
	rep movsb
	cmp	byte ptr [rdi-0x1], 32
	jnz	$_348
	dec	rdi
$_348:	mov	eax, 1768453152
	stosd
	mov	eax, 1953512051
	stosd
	mov	ax, 8306
	stosw
	mov	rcx, qword ptr [rbp-0x28]
	mov	al, byte ptr [rcx]
	jmp	$_350

$_349:	stosb
	inc	rcx
	mov	al, byte ptr [rcx]
$_350:	test	al, al
	jnz	$_349
	cmp	byte ptr [rbx+rdx], 58
	jz	$_351
	cmp	byte ptr [rbx+rdx+0x18], 58
	jnz	$_352
$_351:	mov	eax, 8236
	stosw
$_352:	mov	rcx, rsi
	call	tstrlen@PLT
	mov	ecx, eax
	inc	ecx
	rep movsb
$_353:	test	edi, edi
	je	$_355
	mov	rdx, qword ptr [rbp-0x38]
	mov	rcx, qword ptr [rbp+0x28]
	call	tstrcpy@PLT
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x30]
	xor	edx, edx
	mov	rcx, qword ptr [rbp+0x28]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	cmp	eax, 2
	jbe	$_354
	cmp	rbx, qword ptr [rbp+0x30]
	jnz	$_354
	test	byte ptr [rbx+0x2], 0x08
	jz	$_354
	cmp	byte ptr [rbx+0x18], 40
	jnz	$_354
	lea	rdx, [DS0003+rip]
	mov	rcx, qword ptr [rbp-0x38]
	call	tstrcpy@PLT
	mov	rdx, qword ptr [rbx+0x10]
	mov	rcx, rax
	call	tstrcat@PLT
	mov	rdx, qword ptr [rbp-0x38]
	mov	rcx, qword ptr [rbp+0x28]
	call	tstrcpy@PLT
	xor	r9d, r9d
	mov	r8, rbx
	xor	edx, edx
	mov	rcx, rax
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
$_354:	sub	rbx, 24
$_355:	add	rbx, 24
	jmp	$_329

$_356:	cmp	dword ptr [rbp-0x14], 1
	jnz	$_358
$_357:	inc	dword ptr [rbp-0x10]
	jmp	$_285

$_358:
	cmp	byte ptr [rbp-0x29], 0
	jz	$_359
	mov	rcx, qword ptr [rbp-0x38]
	call	MemFree@PLT
$_359:	cmp	dword ptr [rbp-0x10], 20
	jnz	$_360
	mov	ecx, 2123
	call	asmerr@PLT
	jmp	$_361

$_360:	mov	eax, dword ptr [rbp-0x14]
$_361:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

MacroLocals:
	.int   0x00000000

MacroLevel:
	.int   0x00000000

DS0000:
	.byte  0x00

DS0001:
	.byte  0x31, 0x36, 0x00

DS0002:
	.byte  0x25, 0x31, 0x36, 0x6C, 0x78, 0x25, 0x31, 0x36
	.byte  0x6C, 0x78, 0x00

DS0003:
	.byte  0x69, 0x6E, 0x76, 0x6F, 0x6B, 0x65, 0x20, 0x00

DS0004:
	.byte  0x2E, 0x6E, 0x65, 0x77, 0x20, 0x00


.att_syntax prefix
