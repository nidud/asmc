
.intel_syntax noprefix

.global RetLineQueue
.global mem2mem
.global imm2xmm

.extern CreateFloat
.extern quad_resize
.extern GetLabelStr
.extern Tokenize
.extern EvalOperand
.extern GetCurrOffset
.extern RunLineQueue
.extern AddLineQueueX
.extern LstWrite
.extern SizeFromMemtype
.extern tstrcpy
.extern asmerr
.extern ModuleInfo


.SECTION .text
	.ALIGN	16

$_001:	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 120
	movzx	eax, byte ptr [ModuleInfo+0x1CC+rip]
	shl	eax, 2
	lea	rbx, [ofss+rip]
	add	rax, rbx
	movzx	esi, byte ptr [rax]
	movzx	edi, byte ptr [rax+0x1]
	movzx	ebx, byte ptr [rax+0x2]
	movzx	ecx, byte ptr [rax+0x3]
	mov	dword ptr [rsp+0x60], esi
	mov	dword ptr [rsp+0x58], edi
	mov	dword ptr [rsp+0x50], ebx
	mov	eax, dword ptr [rbp+0x38]
	mov	dword ptr [rsp+0x48], eax
	mov	dword ptr [rsp+0x40], ecx
	mov	rax, qword ptr [rbp+0x28]
	mov	qword ptr [rsp+0x38], rax
	mov	dword ptr [rsp+0x30], edi
	mov	rax, qword ptr [rbp+0x30]
	mov	qword ptr [rsp+0x28], rax
	mov	dword ptr [rsp+0x20], esi
	mov	r9d, ebx
	mov	r8d, edi
	mov	edx, esi
	lea	rcx, [DS0000+rip]
	call	AddLineQueueX@PLT
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_002:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 88
	movzx	edi, byte ptr [ModuleInfo+0x1CC+rip]
	lea	rbx, [ofss+rip]
	movzx	esi, byte ptr [rbx+rdi+0xC]
	movzx	eax, byte ptr [rbx+rdi+0x10]
	mov	dword ptr [rbp-0x4], eax
	shl	edi, 2
	xor	ebx, ebx
$_003:	cmp	dword ptr [rbp+0x38], edi
	jc	$_004
	mov	dword ptr [rsp+0x40], esi
	mov	dword ptr [rsp+0x38], ebx
	mov	rax, qword ptr [rbp+0x28]
	mov	qword ptr [rsp+0x30], rax
	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rsp+0x28], eax
	mov	dword ptr [rsp+0x20], ebx
	mov	r9, qword ptr [rbp+0x30]
	mov	r8d, dword ptr [rbp-0x4]
	mov	edx, esi
	lea	rcx, [DS0001+rip]
	call	AddLineQueueX@PLT
	sub	dword ptr [rbp+0x38], edi
	add	ebx, edi
	jmp	$_003

$_004:
	mov	esi, dword ptr [rbp+0x38]
	cmp	edi, 8
	jnz	$_005
	cmp	esi, 4
	jc	$_005
	mov	dword ptr [rsp+0x20], ebx
	mov	r9, qword ptr [rbp+0x28]
	mov	r8d, ebx
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [DS0002+rip]
	call	AddLineQueueX@PLT
	sub	esi, 4
	add	ebx, 4
$_005:	test	esi, esi
	jz	$_006
	mov	dword ptr [rsp+0x20], ebx
	mov	r9, qword ptr [rbp+0x28]
	mov	r8d, ebx
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [DS0003+rip]
	call	AddLineQueueX@PLT
	dec	esi
	inc	ebx
	jmp	$_005

$_006:
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

RetLineQueue:
	sub	rsp, 40
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 0
	jz	$_007
	call	GetCurrOffset@PLT
	xor	r8d, r8d
	mov	edx, eax
	mov	ecx, 4
	call	LstWrite@PLT
$_007:	call	RunLineQueue@PLT
	xor	eax, eax
	add	rsp, 40
	ret

$_008:
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdx, rcx
	mov	rcx, qword ptr [rdx+0x58]
	cmp	byte ptr [rdx+0x40], -64
	jz	$_009
	movzx	ecx, byte ptr [rdx+0x40]
	mov	r8, qword ptr [rdx+0x60]
	movzx	edx, byte ptr [rdx+0x42]
	movzx	ecx, cl
	call	SizeFromMemtype@PLT
	jmp	$_012

$_009:	test	rcx, rcx
	jz	$_010
	cmp	byte ptr [rcx+0x18], 6
	jnz	$_010
	jmp	$_011

	jmp	$_012

$_010:	xor	eax, eax
	mov	rcx, qword ptr [rdx+0x60]
	test	rcx, rcx
	jz	$_012
$_011:	mov	eax, dword ptr [rcx+0x50]
	test	byte ptr [rcx+0x15], 0x02
	jz	$_012
	mov	ecx, dword ptr [rcx+0x58]
	xor	edx, edx
	div	ecx
$_012:	leave
	ret

mem2mem:
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 136
	mov	byte ptr [rbp-0x41], 0
	mov	byte ptr [rbp-0x42], 0
	mov	ebx, ecx
	mov	edi, edx
	test	ebx, 0x607F00
	jz	$_013
	test	edi, 0x607F00
	jz	$_013
	cmp	byte ptr [ModuleInfo+0x337+rip], 1
	jnz	$_014
$_013:	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_070

$_014:	and	ebx, 0xF00
	and	edi, 0xF00
	mov	dword ptr [rbp-0x8], 17
	mov	dword ptr [rbp-0x10], 4
	cmp	byte ptr [ModuleInfo+0x1CC+rip], 2
	jnz	$_015
	mov	dword ptr [rbp-0x8], 115
	mov	dword ptr [rbp-0x10], 8
$_015:	mov	rcx, qword ptr [rbp+0x38]
	add	rcx, 24
	cmp	byte ptr [rcx+0x30], 5
	jnz	$_016
	cmp	dword ptr [rcx+0x34], 270
	jnz	$_016
	add	rcx, 48
$_016:	mov	rax, qword ptr [rcx+0x10]
	mov	qword ptr [rbp-0x20], rax
	mov	rdx, rcx
$_017:	cmp	byte ptr [rdx], 0
	jz	$_020
	cmp	byte ptr [rdx], 2
	jnz	$_019
	mov	eax, dword ptr [rdx+0x4]
	cmp	eax, 1
	jz	$_018
	cmp	eax, 9
	jz	$_018
	cmp	eax, 17
	jz	$_018
	cmp	eax, 115
	jnz	$_019
$_018:	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_070

$_019:	cmp	byte ptr [rdx], 44
	jz	$_020
	add	rdx, 24
	jmp	$_017

$_020:	cmp	byte ptr [rdx], 44
	jz	$_021
	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_070

$_021:	mov	rax, qword ptr [rdx+0x10]
	mov	qword ptr [rbp-0x28], rax
	add	rdx, 24
	cmp	byte ptr [rdx], 38
	jnz	$_022
	inc	byte ptr [rbp-0x42]
	add	rdx, 24
$_022:	mov	qword ptr [rbp-0x30], rdx
	cmp	byte ptr [rdx+0x18], 5
	jnz	$_023
	cmp	dword ptr [rdx+0x1C], 270
	jnz	$_023
	add	rdx, 48
$_023:	mov	rax, qword ptr [rdx+0x10]
	mov	qword ptr [rbp-0x18], rax
	mov	rsi, qword ptr [rbp+0x40]
	mov	rcx, rsi
	call	$_008
	mov	dword ptr [rbp-0xC], eax
	cmp	byte ptr [rbp-0x42], 0
	jnz	$_025
	lea	rcx, [rsi+0x68]
	call	$_008
	test	rax, rax
	jz	$_025
	cmp	eax, dword ptr [rbp-0xC]
	jge	$_024
	mov	dword ptr [rbp-0xC], eax
	jmp	$_025

$_024:	cmp	dword ptr [rbp-0xC], 0
	jnz	$_025
	cmp	byte ptr [rsi+0x40], -64
	jnz	$_025
	mov	dword ptr [rbp-0xC], eax
$_025:	mov	rdx, qword ptr [rbp+0x38]
	mov	eax, dword ptr [rdx+0x4]
	mov	dword ptr [rbp-0x4], eax
	cmp	eax, 682
	jz	$_028
	test	byte ptr [rsi+0x40], 0x20
	jnz	$_026
	test	byte ptr [rsi+0xA8], 0x20
	jz	$_028
$_026:	mov	byte ptr [rbp-0x41], 1
	cmp	dword ptr [rbp-0xC], 4
	jz	$_027
	cmp	dword ptr [rbp-0xC], 8
	jz	$_027
	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_070

$_027:	mov	dword ptr [rbp-0x8], 40
$_028:	mov	edx, edi
	mov	ecx, dword ptr [rbp-0x8]
	mov	esi, ecx
	mov	edi, ecx
	jmp	$_032

$_029:	mov	edi, 1
	jmp	$_033

$_030:	mov	edi, 9
	jmp	$_033

$_031:	mov	edi, 17
	jmp	$_033

$_032:	cmp	ebx, 3840
	jz	$_029
	cmp	ebx, 256
	jz	$_029
	cmp	ebx, 512
	jz	$_030
	cmp	ebx, 1024
	jz	$_031
$_033:	jmp	$_037

$_034:	mov	esi, 1
	jmp	$_038

$_035:	mov	esi, 9
	jmp	$_038

$_036:	mov	esi, 17
	jmp	$_038

$_037:	cmp	edx, 3840
	jz	$_034
	cmp	edx, 256
	jz	$_034
	cmp	edx, 512
	jz	$_035
	cmp	edx, 1024
	jz	$_036
$_038:	cmp	esi, edi
	jbe	$_039
	cmp	ebx, 3840
	jnz	$_039
	mov	edi, esi
$_039:	cmp	edi, esi
	jbe	$_040
	cmp	edx, 3840
	jnz	$_040
	mov	esi, edi
$_040:	mov	rax, qword ptr [rbp-0x28]
	mov	bl, byte ptr [rax]
	mov	byte ptr [rax], 0
	inc	rax
	mov	rdx, qword ptr [rbp-0x30]
	cmp	byte ptr [rbp-0x42], 0
	jz	$_042
	mov	edi, ecx
	mov	r8, qword ptr [rdx+0x10]
	mov	edx, ecx
	lea	rcx, [DS0004+rip]
	call	AddLineQueueX@PLT
	cmp	dword ptr [rbp-0xC], 4
	jnz	$_041
	cmp	edi, 115
	jnz	$_041
	mov	edi, 17
$_041:	jmp	$_066

$_042:	cmp	edi, esi
	jbe	$_043
	cmp	esi, 17
	jnc	$_043
	mov	rdx, rax
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
	jmp	$_066

$_043:	mov	ecx, 8
	jmp	$_047

$_044:	mov	ecx, 1
	jmp	$_048

$_045:	mov	ecx, 2
	jmp	$_048

$_046:	mov	ecx, 4
	jmp	$_048

$_047:	cmp	edi, 1
	jz	$_044
	cmp	edi, 9
	jz	$_045
	cmp	edi, 17
	jz	$_046
$_048:	cmp	dword ptr [rbp-0xC], ecx
	jg	$_052
	mov	ecx, 682
	cmp	byte ptr [rbp-0x41], 0
	jz	$_051
	mov	ecx, 1050
	mov	edx, 1000
	cmp	dword ptr [rbp-0xC], 8
	jnz	$_049
	mov	ecx, 612
	mov	edx, 999
$_049:	cmp	dword ptr [rbp-0x4], 588
	jnz	$_050
	mov	dword ptr [rbp-0x4], edx
$_050:	mov	rax, qword ptr [rbp-0x20]
	mov	esi, 40
	mov	edi, 40
$_051:	mov	r9, rax
	mov	r8d, esi
	mov	edx, ecx
	lea	rcx, [DS0006+rip]
	call	AddLineQueueX@PLT
	jmp	$_066

$_052:	cmp	dword ptr [rbp-0x4], 682
	jnz	$_058
	mov	rsi, qword ptr [rbp-0x18]
	mov	edi, dword ptr [rbp-0xC]
	cmp	dword ptr [rbp-0x10], 8
	jnz	$_055
	cmp	edi, 32
	jbe	$_053
	mov	r8d, edi
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp-0x20]
	call	$_001
	jmp	$_054

$_053:	mov	r8d, edi
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp-0x20]
	call	$_002
$_054:	jmp	$_057

$_055:	cmp	edi, 16
	jbe	$_056
	mov	r8d, edi
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp-0x20]
	call	$_001
	jmp	$_057

$_056:	mov	r8d, edi
	mov	rdx, rsi
	mov	rcx, qword ptr [rbp-0x20]
	call	$_002
$_057:	xor	ebx, ebx
	mov	rax, qword ptr [rbp-0x28]
	mov	byte ptr [rax], 44
	jmp	$_066

$_058:	cmp	dword ptr [rbp-0xC], 8
	jne	$_065
	cmp	ecx, 4
	jne	$_065
	mov	rbx, qword ptr [rbp-0x18]
	jmp	$_063

$_059:	lea	rdx, [rbp-0x40]
	inc	dword ptr [ModuleInfo+0x1B0+rip]
	mov	eax, dword ptr [ModuleInfo+0x1B0+rip]
	mov	ecx, eax
	call	GetLabelStr@PLT
	lea	rax, [rbp-0x40]
	mov	qword ptr [rsp+0x30], rax
	mov	rax, qword ptr [rbp-0x20]
	mov	qword ptr [rsp+0x28], rax
	mov	qword ptr [rsp+0x20], rbx
	lea	r9, [rbp-0x40]
	mov	r8, qword ptr [rbp-0x20]
	mov	rdx, rbx
	lea	rcx, [DS0007+rip]
	call	AddLineQueueX@PLT
	jmp	$_064

$_060:	mov	qword ptr [rsp+0x20], rbx
	mov	r9, qword ptr [rbp-0x20]
	mov	r8, rbx
	mov	rdx, qword ptr [rbp-0x20]
	lea	rcx, [DS0008+rip]
	call	AddLineQueueX@PLT
	jmp	$_064

$_061:	mov	qword ptr [rsp+0x20], rbx
	mov	r9, qword ptr [rbp-0x20]
	mov	r8, rbx
	mov	rdx, qword ptr [rbp-0x20]
	lea	rcx, [DS0009+rip]
	call	AddLineQueueX@PLT
	jmp	$_064

$_062:	mov	qword ptr [rsp+0x30], rbx
	mov	rax, qword ptr [rbp-0x20]
	mov	qword ptr [rsp+0x28], rax
	mov	eax, dword ptr [rbp-0x4]
	mov	dword ptr [rsp+0x20], eax
	mov	r9, rbx
	mov	r8, qword ptr [rbp-0x20]
	mov	edx, dword ptr [rbp-0x4]
	lea	rcx, [DS000A+rip]
	call	AddLineQueueX@PLT
	jmp	$_064

$_063:	cmp	dword ptr [rbp-0x4], 588
	je	$_059
	cmp	dword ptr [rbp-0x4], 581
	jz	$_060
	cmp	dword ptr [rbp-0x4], 586
	jz	$_061
	jmp	$_062

$_064:	mov	eax, 44
	mov	byte ptr [rbx-0x1], al
	xor	ebx, ebx
	jmp	$_066

$_065:	mov	ecx, 2070
	call	asmerr@PLT
	jmp	$_070

$_066:	test	rbx, rbx
	jz	$_069
	cmp	byte ptr [rbp-0x41], 0
	jz	$_067
	mov	rcx, qword ptr [rbp-0x28]
	inc	rcx
	mov	r9, rcx
	mov	r8d, edi
	mov	edx, dword ptr [rbp-0x4]
	lea	rcx, [DS0006+rip]
	call	AddLineQueueX@PLT
	jmp	$_068

$_067:	mov	r9d, edi
	mov	r8, qword ptr [rbp-0x20]
	mov	edx, dword ptr [rbp-0x4]
	lea	rcx, [DS000B+rip]
	call	AddLineQueueX@PLT
$_068:	mov	rax, qword ptr [rbp-0x28]
	mov	byte ptr [rax], bl
$_069:	call	RetLineQueue
$_070:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_071:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 1200
	mov	rdx, qword ptr [rdi+0x10]
	lea	rcx, [rbp-0x478]
	call	tstrcpy@PLT
	mov	rdx, qword ptr [rdi+0x50]
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	tstrcpy@PLT
	xor	ecx, ecx
$_072:	cmp	byte ptr [rax], 0
	jz	$_074
	cmp	byte ptr [rax], 44
	jnz	$_073
	add	ecx, 1
$_073:	inc	rax
	jmp	$_072

$_074:
	inc	ecx
	mov	dword ptr [rbp-0x8], ecx
	mov	eax, 16
	cdq
	idiv	ecx
	mov	dword ptr [rbp-0xC], eax
	mul	ecx
	cmp	eax, 16
	jz	$_075
	mov	rdx, qword ptr [ModuleInfo+0x178+rip]
	mov	ecx, 2036
	call	asmerr@PLT
	mov	dword ptr [rbp-0x8], 1
	mov	dword ptr [rbp-0xC], 4
$_075:	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x20]
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	dword ptr [rbp-0x4], 0
	mov	rdi, qword ptr [rbp+0x28]
$_076:	cmp	dword ptr [rbp-0x8], 0
	jz	$_078
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x78]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x20]
	lea	rcx, [rbp-0x4]
	call	EvalOperand@PLT
	cmp	eax, -1
	jz	$_078
	test	byte ptr [rbp-0x38], 0x20
	jz	$_077
	mov	edx, dword ptr [rbp-0xC]
	lea	rcx, [rbp-0x78]
	call	quad_resize@PLT
$_077:	lea	rsi, [rbp-0x78]
	mov	ecx, dword ptr [rbp-0xC]
	rep movsb
	dec	dword ptr [rbp-0x8]
	inc	dword ptr [rbp-0x4]
	jmp	$_076

$_078:
	lea	rdx, [rbp-0x478]
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	tstrcpy@PLT
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x20]
	xor	edx, edx
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	eax, 16
	leave
	pop	rdi
	pop	rsi
	ret

imm2xmm:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 184
	mov	rdi, rcx
	mov	rcx, rdx
	mov	esi, dword ptr [rdi+0x4]
	cmp	dword ptr [rbp+0x38], 16
	jnz	$_079
	cmp	byte ptr [rcx+0x40], -64
	jnz	$_079
	mov	rdx, rcx
	mov	rcx, rdi
	call	$_071
	jmp	$_081

$_079:	cmp	esi, 1050
	jz	$_080
	cmp	esi, 612
	jnz	$_081
$_080:	cmp	byte ptr [rdi+0x18], 2
	jnz	$_081
	mov	rax, qword ptr [rcx]
	or	rax, qword ptr [rcx+0x8]
	test	rax, rax
	jnz	$_081
	mov	esi, 1002
	mov	r9d, dword ptr [rdi+0x1C]
	mov	r8d, dword ptr [rdi+0x1C]
	mov	edx, esi
	lea	rcx, [DS000C+rip]
	call	AddLineQueueX@PLT
	call	RetLineQueue
	jmp	$_084

$_081:	lea	r8, [rbp-0x10]
	mov	rdx, qword ptr [rbp+0x30]
	mov	ecx, dword ptr [rbp+0x38]
	call	CreateFloat@PLT
	cmp	byte ptr [rdi+0x18], 2
	jnz	$_082
	lea	r9, [rbp-0x10]
	mov	r8d, dword ptr [rdi+0x1C]
	mov	edx, esi
	lea	rcx, [DS000D+rip]
	call	AddLineQueueX@PLT
	jmp	$_083

$_082:	mov	rbx, qword ptr [rdi+0x28]
	mov	dword ptr [rbp-0x14], 1
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x80]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [rbp-0x14]
	call	EvalOperand@PLT
	imul	edi, dword ptr [rbp-0x14], 24
	add	rdi, qword ptr [rbp+0x28]
	mov	rdi, qword ptr [rdi+0x10]
	mov	byte ptr [rdi], 0
	lea	r9, [rbp-0x10]
	mov	r8, rbx
	mov	edx, esi
	lea	rcx, [DS000E+rip]
	call	AddLineQueueX@PLT
	mov	byte ptr [rdi], 44
$_083:	call	RetLineQueue
$_084:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

ofss:
	.byte  0x0F, 0x10, 0x0A, 0x0A, 0x17, 0x18, 0x12, 0x12
	.byte  0x79, 0x7A, 0x74, 0x12, 0x09, 0x11, 0x73, 0x00
	.byte  0xCF, 0xD2, 0xD6, 0x00

DS0000:
	.byte  0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x25, 0x72
	.byte  0x0A, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20, 0x25
	.byte  0x72, 0x0A, 0x20, 0x70, 0x75, 0x73, 0x68, 0x20
	.byte  0x25, 0x72, 0x0A, 0x20, 0x6C, 0x65, 0x61, 0x20
	.byte  0x25, 0x72, 0x2C, 0x20, 0x25, 0x73, 0x0A, 0x20
	.byte  0x6C, 0x65, 0x61, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x25, 0x73, 0x0A, 0x20, 0x6D, 0x6F, 0x76, 0x20
	.byte  0x25, 0x72, 0x2C, 0x20, 0x25, 0x75, 0x0A, 0x20
	.byte  0x72, 0x65, 0x70, 0x20, 0x6D, 0x6F, 0x76, 0x73
	.byte  0x62, 0x0A, 0x20, 0x70, 0x6F, 0x70, 0x20, 0x25
	.byte  0x72, 0x0A, 0x20, 0x70, 0x6F, 0x70, 0x20, 0x25
	.byte  0x72, 0x0A, 0x20, 0x70, 0x6F, 0x70, 0x20, 0x25
	.byte  0x72, 0x00

DS0001:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x72, 0x20, 0x70, 0x74, 0x72, 0x20
	.byte  0x25, 0x73, 0x5B, 0x25, 0x64, 0x5D, 0x0A, 0x20
	.byte  0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x20, 0x70
	.byte  0x74, 0x72, 0x20, 0x25, 0x73, 0x5B, 0x25, 0x64
	.byte  0x5D, 0x2C, 0x20, 0x25, 0x72, 0x00

DS0002:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x65, 0x61, 0x78
	.byte  0x2C, 0x20, 0x64, 0x77, 0x6F, 0x72, 0x64, 0x20
	.byte  0x70, 0x74, 0x72, 0x20, 0x25, 0x73, 0x5B, 0x25
	.byte  0x64, 0x5D, 0x0A, 0x20, 0x6D, 0x6F, 0x76, 0x20
	.byte  0x64, 0x77, 0x6F, 0x72, 0x64, 0x20, 0x70, 0x74
	.byte  0x72, 0x20, 0x25, 0x73, 0x5B, 0x25, 0x64, 0x5D
	.byte  0x2C, 0x20, 0x65, 0x61, 0x78, 0x00

DS0003:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x61, 0x6C, 0x2C
	.byte  0x20, 0x62, 0x79, 0x74, 0x65, 0x20, 0x70, 0x74
	.byte  0x72, 0x20, 0x25, 0x73, 0x5B, 0x25, 0x64, 0x5D
	.byte  0x0A, 0x20, 0x6D, 0x6F, 0x76, 0x20, 0x62, 0x79
	.byte  0x74, 0x65, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x5B, 0x25, 0x64, 0x5D, 0x2C, 0x20, 0x61
	.byte  0x6C, 0x00

DS0004:
	.byte  0x20, 0x6C, 0x65, 0x61, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x73, 0x00

DS0005:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x7A, 0x78, 0x20, 0x65
	.byte  0x61, 0x78, 0x2C, 0x20, 0x25, 0x73, 0x00

DS0006:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x25, 0x73, 0x00

DS0007:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x65, 0x61, 0x78
	.byte  0x2C, 0x20, 0x64, 0x77, 0x6F, 0x72, 0x64, 0x20
	.byte  0x70, 0x74, 0x72, 0x20, 0x25, 0x73, 0x5B, 0x34
	.byte  0x5D, 0x0A, 0x20, 0x63, 0x6D, 0x70, 0x20, 0x64
	.byte  0x77, 0x6F, 0x72, 0x64, 0x20, 0x70, 0x74, 0x72
	.byte  0x20, 0x25, 0x73, 0x5B, 0x34, 0x5D, 0x2C, 0x20
	.byte  0x65, 0x61, 0x78, 0x0A, 0x20, 0x6A, 0x6E, 0x65
	.byte  0x20, 0x25, 0x73, 0x0A, 0x20, 0x6D, 0x6F, 0x76
	.byte  0x20, 0x65, 0x61, 0x78, 0x2C, 0x20, 0x64, 0x77
	.byte  0x6F, 0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20
	.byte  0x25, 0x73, 0x0A, 0x20, 0x63, 0x6D, 0x70, 0x20
	.byte  0x64, 0x77, 0x6F, 0x72, 0x64, 0x20, 0x70, 0x74
	.byte  0x72, 0x20, 0x25, 0x73, 0x2C, 0x20, 0x65, 0x61
	.byte  0x78, 0x0A, 0x25, 0x73, 0x3A, 0x00

DS0008:
	.byte  0x20, 0x61, 0x64, 0x64, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x2C, 0x20, 0x64, 0x77, 0x6F, 0x72, 0x64
	.byte  0x20, 0x70, 0x74, 0x72, 0x20, 0x25, 0x73, 0x0A
	.byte  0x20, 0x61, 0x64, 0x63, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x5B, 0x34, 0x5D, 0x2C, 0x20, 0x64, 0x77
	.byte  0x6F, 0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20
	.byte  0x25, 0x73, 0x5B, 0x34, 0x5D, 0x00

DS0009:
	.byte  0x20, 0x73, 0x75, 0x62, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x2C, 0x20, 0x64, 0x77, 0x6F, 0x72, 0x64
	.byte  0x20, 0x70, 0x74, 0x72, 0x20, 0x25, 0x73, 0x0A
	.byte  0x20, 0x73, 0x62, 0x62, 0x20, 0x64, 0x77, 0x6F
	.byte  0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25
	.byte  0x73, 0x5B, 0x34, 0x5D, 0x2C, 0x20, 0x64, 0x77
	.byte  0x6F, 0x72, 0x64, 0x20, 0x70, 0x74, 0x72, 0x20
	.byte  0x25, 0x73, 0x5B, 0x34, 0x5D, 0x00

DS000A:
	.byte  0x20, 0x25, 0x72, 0x20, 0x64, 0x77, 0x6F, 0x72
	.byte  0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25, 0x73
	.byte  0x2C, 0x20, 0x64, 0x77, 0x6F, 0x72, 0x64, 0x20
	.byte  0x70, 0x74, 0x72, 0x20, 0x25, 0x73, 0x0A, 0x20
	.byte  0x25, 0x72, 0x20, 0x64, 0x77, 0x6F, 0x72, 0x64
	.byte  0x20, 0x70, 0x74, 0x72, 0x20, 0x25, 0x73, 0x5B
	.byte  0x34, 0x5D, 0x2C, 0x20, 0x64, 0x77, 0x6F, 0x72
	.byte  0x64, 0x20, 0x70, 0x74, 0x72, 0x20, 0x25, 0x73
	.byte  0x5B, 0x34, 0x5D, 0x00

DS000B:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x73, 0x2C, 0x20
	.byte  0x25, 0x72, 0x00

DS000C:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x72, 0x2C, 0x25
	.byte  0x72, 0x00

DS000D:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x72, 0x2C, 0x25
	.byte  0x73, 0x00

DS000E:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x73, 0x2C, 0x25
	.byte  0x73, 0x00


.att_syntax prefix
