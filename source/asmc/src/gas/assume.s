
.intel_syntax noprefix

.global SetSegAssumeTable
.global GetSegAssumeTable
.global SetStdAssumeTable
.global GetStdAssumeTable
.global AssumeSaveState
.global AssumeInit
.global ModelAssumeInit
.global GetStdAssume
.global GetStdAssumeEx_
.global AssumeDirective
.global search_assume
.global GetOverrideAssume
.global GetOfssizeAssume
.global GetAssume
.global szDgroup
.global SegAssumeTable
.global StdAssumeTable

.extern StoreLine
.extern UseSavedState
.extern EvalOperand
.extern AddLineQueueX
.extern OperandSize
.extern SpecialTable
.extern GetGroup
.extern GetQualifiedType
.extern CreateTypeSymbol
.extern tstricmp
.extern asmerr
.extern ModuleInfo
.extern Parse_Pass


.SECTION .text
	.ALIGN	16

SetSegAssumeTable:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	mov	rsi, rcx
	lea	rdi, [SegAssumeTable+rip]
	mov	ecx, 96
	rep movsb
	leave
	pop	rdi
	pop	rsi
	ret

GetSegAssumeTable:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	mov	rdi, rcx
	lea	rsi, [SegAssumeTable+rip]
	mov	ecx, 96
	rep movsb
	leave
	pop	rdi
	pop	rsi
	ret

SetStdAssumeTable:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	lea	rdi, [StdAssumeTable+rip]
	mov	rsi, rcx
	mov	ecx, 256
	mov	rax, rdi
	rep movsb
	mov	rdi, rax
	mov	rsi, rdx
	xor	ecx, ecx
$_001:	cmp	ecx, 16
	jnc	$_003
	cmp	qword ptr [rdi], 0
	jz	$_002
	mov	rdx, qword ptr [rdi]
	mov	rax, qword ptr [rsi]
	mov	qword ptr [rdx+0x20], rax
	mov	rax, qword ptr [rsi+0x8]
	mov	qword ptr [rdx+0x40], rax
	mov	al, byte ptr [rsi+0x10]
	mov	byte ptr [rdx+0x19], al
	mov	al, byte ptr [rsi+0x11]
	mov	byte ptr [rdx+0x3A], al
	mov	al, byte ptr [rsi+0x12]
	mov	byte ptr [rdx+0x39], al
$_002:	inc	ecx
	add	rdi, 16
	add	rsi, 24
	jmp	$_001

$_003:
	leave
	pop	rdi
	pop	rsi
	ret

GetStdAssumeTable:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	mov	rdi, rcx
	lea	rsi, [StdAssumeTable+rip]
	mov	ecx, 256
	rep movsb
	lea	rsi, [StdAssumeTable+rip]
	mov	rdi, rdx
$_004:	cmp	ecx, 16
	jnc	$_006
	cmp	qword ptr [rsi], 0
	jz	$_005
	mov	rdx, qword ptr [rsi]
	mov	rax, qword ptr [rdx+0x20]
	mov	qword ptr [rdi], rax
	mov	rax, qword ptr [rdx+0x40]
	mov	qword ptr [rdi+0x8], rax
	mov	al, byte ptr [rdx+0x19]
	mov	byte ptr [rdi+0x10], al
	mov	al, byte ptr [rdx+0x3A]
	mov	byte ptr [rdi+0x11], al
	mov	al, byte ptr [rdx+0x39]
	mov	byte ptr [rdi+0x12], al
$_005:	inc	ecx
	add	rdi, 24
	add	rsi, 16
	jmp	$_004

$_006:
	leave
	pop	rdi
	pop	rsi
	ret

AssumeSaveState:
	sub	rsp, 40
	lea	rcx, [saved_SegAssumeTable+rip]
	call	GetSegAssumeTable
	lea	rdx, [saved_StdTypeInfo+rip]
	lea	rcx, [saved_StdAssumeTable+rip]
	call	GetStdAssumeTable
	add	rsp, 40
	ret

AssumeInit:
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	ebx, ecx
	xor	eax, eax
	lea	rdx, [SegAssumeTable+rip]
	xor	ecx, ecx
$_007:	cmp	ecx, 6
	jnc	$_008
	mov	qword ptr [rdx], rax
	mov	byte ptr [rdx+0x8], al
	mov	byte ptr [rdx+0x9], al
	inc	ecx
	add	rdx, 16
	jmp	$_007

$_008:
	cmp	ebx, 0
	ja	$_011
	lea	rdx, [StdAssumeTable+rip]
	xor	ecx, ecx
$_009:	cmp	ecx, 16
	jnc	$_010
	mov	qword ptr [rdx], rax
	mov	byte ptr [rdx+0x8], al
	inc	ecx
	add	rdx, 16
	jmp	$_009

$_010:	test	ebx, ebx
	jnz	$_011
	lea	rdx, [stdsym+rip]
	mov	ecx, 128
	xchg	rdx, rdi
	rep stosb
	mov	rdi, rdx
$_011:	cmp	ebx, 0
	jbe	$_012
	cmp	dword ptr [UseSavedState+rip], 0
	jz	$_012
	lea	rcx, [saved_SegAssumeTable+rip]
	call	SetSegAssumeTable
	lea	rdx, [saved_StdTypeInfo+rip]
	lea	rcx, [saved_StdAssumeTable+rip]
	call	SetStdAssumeTable
$_012:	leave
	pop	rbx
	ret

ModelAssumeInit:
	sub	rsp, 40
	cmp	byte ptr [ModuleInfo+0x1B5+rip],7
	jne	$C0013
	lea	rdx, [szError+rip]
	mov	rcx, rdx
	cmp	byte ptr [ModuleInfo+0x1B9+rip], 2
	jz	$_013
	cmp	byte ptr [ModuleInfo+0x1B9+rip], 5
	jnz	$_014
$_013:	lea	rcx, [szNothing+rip]
$_014:	mov	r8, rcx
	lea	rcx, [DS0000+rip]
	call	AddLineQueueX@PLT
$C0013: add	rsp, 40
	ret

GetStdAssume:
	imul	ecx, ecx, 16
	lea	rax, [StdAssumeTable+rip]
	mov	rax, qword ptr [rax+rcx]
	test	rax, rax
	jz	$_016
	cmp	byte ptr [rax+0x19], -60
	jnz	$_015
	mov	rax, qword ptr [rax+0x20]
	jmp	$_016
$_015:	mov	rax, qword ptr [rax+0x40]
$_016:	ret

GetStdAssumeEx_:
	cmp	eax, 16
	jnc	$_017
	push	rcx
	imul	ecx, eax, 16
	lea	rax, [StdAssumeTable+rip]
	add	rax, rcx
	pop	rcx
	mov	rax, qword ptr [rax]
	jmp	$_018

$_017:	xor	eax, eax
$_018:	ret

AssumeDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 216
	mov	dword ptr [rbp-0x4], 0
	mov	dword ptr [rbp-0x8], 0
	mov	dword ptr [rbp-0x10], 0
	mov	dword ptr [rbp-0x1C], 0
	inc	dword ptr [rbp+0x28]
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
$_019:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp+0x28], eax
	jge	$_059
	cmp	byte ptr [rbx], 8
	jnz	$_020
	lea	rdx, [szNothing+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_020
	mov	ecx, 4294967295
	call	AssumeInit
	inc	dword ptr [rbp+0x28]
	jmp	$_059

$_020:	xor	edi, edi
	cmp	byte ptr [rbx], 2
	jnz	$_022
	mov	eax, dword ptr [rbx+0x4]
	mov	dword ptr [rbp-0x4], eax
	lea	r11, [SpecialTable+rip]
	imul	eax, eax, 12
	mov	eax, dword ptr [r11+rax]
	mov	dword ptr [rbp-0x10], eax
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp-0x4], 12
	movzx	eax, byte ptr [r11+rax+0xA]
	mov	dword ptr [rbp-0x8], eax
	imul	eax, eax, 16
	test	byte ptr [rbp-0xD], 0x0C
	jz	$_021
	lea	rdi, [SegAssumeTable+rip]
	add	rdi, rax
	mov	dword ptr [rbp-0x1C], 1
	jmp	$_022

$_021:	test	byte ptr [rbp-0x10], 0x0F
	jz	$_022
	lea	rdi, [StdAssumeTable+rip]
	add	rdi, rax
	mov	dword ptr [rbp-0x1C], 0
$_022:	test	rdi, rdi
	jnz	$_023
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_061

$_023:	mov	ecx, dword ptr [ModuleInfo+0x1C0+rip]
	and	ecx, 0xF0
	lea	r11, [SpecialTable+rip]
	imul	eax, dword ptr [rbp-0x4], 12
	cmp	cx, word ptr [r11+rax+0x8]
	jnc	$_024
	mov	ecx, 2085
	call	asmerr@PLT
	jmp	$_061

$_024:	cmp	byte ptr [rbx+0x18], 58
	jz	$_025
	lea	rdx, [DS0000+0x32+rip]
	mov	ecx, 2065
	call	asmerr@PLT
	jmp	$_061

$_025:	cmp	byte ptr [rbx+0x30], 0
	jnz	$_026
	mov	ecx, 2009
	call	asmerr@PLT
	jmp	$_061

$_026:	add	dword ptr [rbp+0x28], 2
	add	rbx, 48
	lea	rdx, [szError+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_030
	cmp	dword ptr [rbp-0x1C], 0
	jz	$_027
	mov	byte ptr [rdi+0x9], 0
	mov	byte ptr [rdi+0x8], 1
	jmp	$_029

$_027:	mov	eax, dword ptr [rbp-0x10]
	and	eax, 0x0F
	cmp	dword ptr [rbp-0x4], 5
	jl	$_028
	cmp	dword ptr [rbp-0x4], 8
	jg	$_028
	mov	eax, 16
$_028:	or	byte ptr [rdi+0x8], al
$_029:	mov	qword ptr [rdi], 0
	inc	dword ptr [rbp+0x28]
	jmp	$_057

$_030:	lea	rdx, [szNothing+rip]
	mov	rcx, qword ptr [rbx+0x8]
	call	tstricmp@PLT
	test	eax, eax
	jnz	$_034
	cmp	dword ptr [rbp-0x1C], 0
	jz	$_031
	mov	byte ptr [rdi+0x9], 0
	mov	byte ptr [rdi+0x8], 0
	jmp	$_033

$_031:	mov	eax, dword ptr [rbp-0x10]
	and	eax, 0x0F
	cmp	dword ptr [rbp-0x4], 5
	jl	$_032
	cmp	dword ptr [rbp-0x4], 8
	jg	$_032
	mov	eax, 16
$_032:	not	eax
	mov	cl, byte ptr [rdi+0x8]
	and	al, cl
	mov	byte ptr [rdi+0x8], al
$_033:	mov	qword ptr [rdi], 0
	inc	dword ptr [rbp+0x28]
	jmp	$_057

$_034:	cmp	dword ptr [rbp-0x1C], 0
	jne	$_042
	mov	dword ptr [rbp-0x38], 0
	mov	byte ptr [rbp-0x27], 0
	mov	byte ptr [rbp-0x26], 0
	mov	byte ptr [rbp-0x28], -64
	mov	byte ptr [rbp-0x24], -64
	mov	qword ptr [rbp-0x30], 0
	mov	al, byte ptr [ModuleInfo+0x1CC+rip]
	mov	byte ptr [rbp-0x25], al
	lea	r8, [rbp-0x38]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	GetQualifiedType@PLT
	cmp	eax, -1
	je	$_061
	xor	edx, edx
	mov	ecx, dword ptr [rbp-0x10]
	call	OperandSize@PLT
	mov	dword ptr [rbp-0xC], eax
	cmp	byte ptr [rbp-0x27], 0
	jnz	$_035
	cmp	eax, dword ptr [rbp-0x38]
	jnz	$_036
$_035:	cmp	byte ptr [rbp-0x27], 0
	jbe	$_037
	cmp	al, byte ptr [ModuleInfo+0x1CE+rip]
	jnc	$_037
$_036:	mov	ecx, 2024
	call	asmerr@PLT
	jmp	$_061

$_037:	mov	eax, dword ptr [rbp-0x10]
	and	eax, 0x0F
	cmp	dword ptr [rbp-0x4], 5
	jl	$_038
	cmp	dword ptr [rbp-0x4], 8
	jg	$_038
	mov	eax, 16
$_038:	not	eax
	mov	cl, byte ptr [rdi+0x8]
	and	al, cl
	mov	byte ptr [rdi+0x8], al
	mov	esi, dword ptr [rbp-0x8]
	lea	rcx, [stdsym+rip]
	mov	rax, qword ptr [rcx+rsi*8]
	test	rax, rax
	jnz	$_039
	xor	r8d, r8d
	lea	rdx, [DS0000+0x32+rip]
	xor	ecx, ecx
	call	CreateTypeSymbol@PLT
	lea	rcx, [stdsym+rip]
	mov	qword ptr [rcx+rsi*8], rax
	mov	word ptr [rax+0x5A], 3
$_039:	mov	rsi, rax
	mov	eax, dword ptr [rbp-0x38]
	mov	dword ptr [rsi+0x50], eax
	mov	al, byte ptr [rbp-0x28]
	mov	byte ptr [rsi+0x19], al
	mov	al, byte ptr [rbp-0x27]
	mov	byte ptr [rsi+0x39], al
	mov	al, byte ptr [rbp-0x26]
	mov	byte ptr [rsi+0x1C], al
	mov	al, byte ptr [rbp-0x25]
	mov	byte ptr [rsi+0x38], al
	mov	al, byte ptr [rbp-0x24]
	mov	byte ptr [rsi+0x3A], al
	cmp	byte ptr [rbp-0x28], -60
	jnz	$_040
	mov	rax, qword ptr [rbp-0x30]
	mov	qword ptr [rsi+0x20], rax
	jmp	$_041

$_040:	mov	rax, qword ptr [rbp-0x30]
	mov	qword ptr [rsi+0x40], rax
$_041:	mov	qword ptr [rdi], rsi
	jmp	$_057

$_042:	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0xA0]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_061
	mov	rsi, qword ptr [rbp-0x50]
	jmp	$_055

$_043:	test	rsi, rsi
	jz	$_044
	test	byte ptr [rbp-0x5D], 0x01
	jnz	$_044
	cmp	dword ptr [rbp-0xA0], 0
	jz	$_045
$_044:	mov	ecx, 2096
	call	asmerr@PLT
	jmp	$_061

	jmp	$_051

$_045:	cmp	byte ptr [rsi+0x18], 0
	jnz	$_047
	cmp	dword ptr [Parse_Pass+rip], 0
	jnz	$_046
	xor	r8d, r8d
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	StoreLine@PLT
$_046:	mov	qword ptr [rdi], rsi
	jmp	$_051

$_047:	cmp	byte ptr [rsi+0x18], 3
	jz	$_048
	cmp	byte ptr [rsi+0x18], 4
	jnz	$_049
$_048:	cmp	dword ptr [rbp-0x68], -2
	jnz	$_049
	mov	qword ptr [rdi], rsi
	jmp	$_051

$_049:	cmp	dword ptr [rbp-0x68], 252
	jnz	$_050
	mov	rax, qword ptr [rsi+0x30]
	mov	qword ptr [rdi], rax
	jmp	$_051

$_050:	mov	ecx, 2096
	call	asmerr@PLT
	jmp	$_061

$_051:	xor	eax, eax
	mov	rcx, qword ptr [ModuleInfo+0x200+rip]
	cmp	qword ptr [rdi], rcx
	jnz	$_052
	inc	eax
$_052:	mov	byte ptr [rdi+0x9], al
	jmp	$_056

$_053:	mov	rdx, qword ptr [rbp-0x88]
	mov	esi, dword ptr [rdx+0x4]
	lea	r11, [SpecialTable+rip]
	imul	eax, esi, 12
	test	byte ptr [r11+rax+0x3], 0x0C
	jz	$_054
	lea	r11, [SpecialTable+rip]
	imul	eax, esi, 12
	movzx	ecx, byte ptr [r11+rax+0xA]
	imul	ecx, ecx, 16
	lea	rdx, [SegAssumeTable+rip]
	mov	rax, qword ptr [rdx+rcx]
	mov	qword ptr [rdi], rax
	mov	al, byte ptr [rdx+rcx+0x9]
	mov	byte ptr [rdi+0x9], al
	jmp	$_056

$_054:	mov	ecx, 2096
	call	asmerr@PLT
	jmp	$_061

	jmp	$_056

$_055:	cmp	dword ptr [rbp-0x64], 1
	je	$_043
	cmp	dword ptr [rbp-0x64], 2
	jz	$_053
	jmp	$_054

$_056:	mov	byte ptr [rdi+0x8], 0
$_057:	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp+0x28], eax
	jge	$_058
	cmp	byte ptr [rbx], 44
	jnz	$_059
$_058:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	jmp	$_019

$_059:	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	cmp	dword ptr [rbp+0x28], eax
	jge	$_060
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_061

$_060:	xor	eax, eax
$_061:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

search_assume:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rdi, rcx
	mov	ebx, edx
	test	rdi, rdi
	jnz	$_062
	movabs	rax, 0xFFFFFFFE
	jmp	$_070

$_062:	mov	rcx, rdi
	call	GetGroup@PLT
	mov	rsi, rax
	lea	rcx, [SegAssumeTable+rip]
	cmp	ebx, -2
	jz	$_064
	mov	eax, ebx
	imul	edx, ebx, 16
	add	rdx, rcx
	cmp	rdi, qword ptr [rdx]
	je	$_070
	cmp	dword ptr [rbp+0x38], 0
	jz	$_064
	test	rsi, rsi
	jz	$_064
	cmp	byte ptr [rdx+0x9], 0
	jz	$_063
	cmp	rsi, qword ptr [ModuleInfo+0x200+rip]
	jz	$_070
$_063:	cmp	rsi, qword ptr [rdx]
	jz	$_070
$_064:	lea	rdi, [SegAssumeTable+rip]
	lea	rbx, [searchtab+rip]
	xor	ecx, ecx
$_065:	cmp	ecx, 6
	jnc	$_066
	mov	eax, dword ptr [rbx+rcx*4]
	imul	edx, eax, 16
	mov	rdx, qword ptr [rdi+rdx]
	cmp	rdx, qword ptr [rbp+0x28]
	jz	$_070
	inc	ecx
	jmp	$_065

$_066:	cmp	dword ptr [rbp+0x38], 0
	jz	$_069
	test	rsi, rsi
	jz	$_069
	xor	ecx, ecx
$_067:	cmp	ecx, 6
	jnc	$_069
	mov	eax, dword ptr [rbx+rcx*4]
	imul	edx, eax, 16
	cmp	byte ptr [rdi+rdx+0x9], 0
	jz	$_068
	cmp	rsi, qword ptr [ModuleInfo+0x200+rip]
	jz	$_070
$_068:	cmp	rsi, qword ptr [rdi+rdx]
	jz	$_070
	inc	ecx
	jmp	$_067

$_069:
	movabs	rax, 0xFFFFFFFE
$_070:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

GetOverrideAssume:
	mov	qword ptr [rsp+0x8], rcx
	push	rbp
	mov	rbp, rsp
	imul	edx, dword ptr [rbp+0x10], 16
	lea	rcx, [SegAssumeTable+rip]
	mov	rax, qword ptr [rdx+rcx]
	cmp	byte ptr [rdx+rcx+0x9], 0
	jz	$_071
	mov	rax, qword ptr [ModuleInfo+0x200+rip]
$_071:	leave
	ret

GetOfssizeAssume:
	imul	edx, ecx, 16
	lea	rcx, [SegAssumeTable+rip]
	cmp	byte ptr [rdx+rcx+0x9], 0
	jnz	$_073
	mov	rax, qword ptr [rdx+rcx]
	test	rax, rax
	jz	$_073
	cmp	byte ptr [rax+0x18], 3
	jnz	$_072
	mov	rax, qword ptr [rax+0x68]
	movzx	eax, byte ptr [rax+0x68]
	jmp	$_074

$_072:	movzx	eax, byte ptr [rax+0x38]
	jmp	$_074

$_073:	movzx	eax, byte ptr [ModuleInfo+0x1CC+rip]
$_074:	ret

GetAssume:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	imul	eax, dword ptr [rbp+0x20], 16
	lea	rdx, [SegAssumeTable+rip]
	add	rdx, rax
	mov	eax, dword ptr [rbp+0x20]
	cmp	eax, -2
	jz	$_075
	cmp	byte ptr [rdx+0x9], 0
	jz	$_075
	mov	rdx, qword ptr [ModuleInfo+0x200+rip]
	mov	rcx, qword ptr [rbp+0x28]
	mov	qword ptr [rcx], rdx
	jmp	$_081

$_075:	mov	rcx, qword ptr [rbp+0x18]
	cmp	qword ptr [rbp+0x10], 0
	jz	$_076
	xor	r8d, r8d
	mov	edx, eax
	mov	rcx, qword ptr [rbp+0x10]
	call	search_assume
	jmp	$_078

$_076:	cmp	byte ptr [rcx+0x18], 5
	jnz	$_077
	mov	eax, 2
	jmp	$_078

$_077:	mov	r8d, 1
	mov	edx, eax
	mov	rcx, qword ptr [rcx+0x30]
	call	search_assume
$_078:	cmp	eax, -2
	jnz	$_079
	mov	rcx, qword ptr [rbp+0x18]
	test	rcx, rcx
	jz	$_079
	cmp	byte ptr [rcx+0x18], 2
	jnz	$_079
	cmp	qword ptr [rcx+0x30], 0
	jnz	$_079
	mov	eax, dword ptr [rbp+0x20]
$_079:	cmp	eax, -2
	jz	$_080
	imul	edx, eax, 16
	lea	rcx, [SegAssumeTable+rip]
	mov	rcx, qword ptr [rdx+rcx]
	mov	rdx, qword ptr [rbp+0x28]
	mov	qword ptr [rdx], rcx
	jmp	$_081

$_080:	mov	rcx, qword ptr [rbp+0x28]
	xor	eax, eax
	mov	qword ptr [rcx], rax
	movabs	rax, 0xFFFFFFFE
$_081:	leave
	ret


.SECTION .data
	.ALIGN	16

searchtab:
	.byte  0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte  0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00
	.byte  0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00

szError:
	.byte  0x45, 0x52, 0x52, 0x4F, 0x52, 0x00

szNothing:
	.byte  0x4E, 0x4F, 0x54, 0x48, 0x49, 0x4E, 0x47, 0x00

szDgroup:
	.byte  0x44, 0x47, 0x52, 0x4F, 0x55, 0x50, 0x00

DS0000:
	.byte  0x61, 0x73, 0x73, 0x75, 0x6D, 0x65, 0x20, 0x63
	.byte  0x73, 0x3A, 0x66, 0x6C, 0x61, 0x74, 0x2C, 0x64
	.byte  0x73, 0x3A, 0x66, 0x6C, 0x61, 0x74, 0x2C, 0x73
	.byte  0x73, 0x3A, 0x66, 0x6C, 0x61, 0x74, 0x2C, 0x65
	.byte  0x73, 0x3A, 0x66, 0x6C, 0x61, 0x74, 0x2C, 0x66
	.byte  0x73, 0x3A, 0x25, 0x73, 0x2C, 0x67, 0x73, 0x3A
	.byte  0x25, 0x73, 0x00


.SECTION .bss
	.ALIGN	16

SegAssumeTable:
	.zero	96 * 1

StdAssumeTable:
	.zero	256 * 1

stdsym:
	.zero	128 * 1

saved_SegAssumeTable:
	.zero	96 * 1

saved_StdAssumeTable:
	.zero	256 * 1

saved_StdTypeInfo:
	.zero	384 * 1


.att_syntax prefix
