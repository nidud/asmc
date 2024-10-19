
.intel_syntax noprefix

.global FindDotSymbol
.global AssignPointer
.global HandleIndirection

.extern SearchNameInStruct
.extern AddLineQueueX
.extern RetLineQueue
.extern asmerr
.extern ModuleInfo
.extern SymFind


.SECTION .text
	.ALIGN	16

$_001:	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rbx, rcx
	xor	edx, edx
	mov	ecx, 1
	add	rbx, 24
$_002:	test	ecx, ecx
	jz	$_007
	cmp	byte ptr [rbx], 0
	jz	$_007
	mov	al, byte ptr [rbx]
	cmp	al, 40
	jnz	$_003
	inc	edx
	jmp	$_006

$_003:	cmp	al, 41
	jnz	$_004
	dec	edx
	jmp	$_006

$_004:	test	edx, edx
	jnz	$_005
	cmp	al, 91
	jnz	$_005
	inc	ecx
	jmp	$_006

$_005:	test	edx, edx
	jnz	$_006
	cmp	al, 93
	jnz	$_006
	dec	ecx
	jnz	$_006
	add	rbx, 24
	mov	rax, rbx
	jmp	$_008

$_006:	add	rbx, 24
	jmp	$_002

$_007:	xor	eax, eax
$_008:	leave
	pop	rbx
	ret

$_009:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rdi, rdx
	mov	rsi, rcx
	call	$_001
	test	rax, rax
	jz	$_010
	mov	rcx, qword ptr [rax+0x10]
	mov	rsi, qword ptr [rsi+0x10]
	sub	rcx, rsi
	rep movsb
	mov	byte ptr [rdi], 0
$_010:	leave
	pop	rdi
	pop	rsi
	ret

FindDotSymbol:
	mov	qword ptr [rsp+0x8], rcx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	mov	rbx, rcx
	jmp	$_012

$_011:	sub	rbx, 24
$_012:	cmp	byte ptr [rbx-0x18], 44
	jz	$_013
	cmp	byte ptr [rbx-0x18], 3
	jnz	$_011
$_013:	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	test	rax, rax
	jz	$_020
	mov	rsi, rax
	add	rbx, 24
	jmp	$_019

$_014:	cmp	byte ptr [rbx], 44
	jnz	$_015
	xor	eax, eax
	jmp	$_020

$_015:	cmp	byte ptr [rbx], 91
	jnz	$_016
	mov	rcx, rbx
	call	$_001
	test	rax, rax
	jz	$_020
	mov	rbx, rax
$_016:	xor	eax, eax
	cmp	byte ptr [rbx], 46
	jnz	$_020
	add	rbx, 24
	cmp	byte ptr [rsi+0x19], -60
	jnz	$_017
	mov	rsi, qword ptr [rsi+0x20]
$_017:	cmp	byte ptr [rsi+0x19], -61
	jnz	$_018
	mov	rsi, qword ptr [rsi+0x40]
$_018:	test	rsi, rsi
	jz	$_020
	cmp	byte ptr [rsi+0x18], 7
	jnz	$_020
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rsi
	call	SearchNameInStruct@PLT
	mov	rsi, rax
	test	rsi, rsi
	jz	$_020
	cmp	rbx, qword ptr [rbp+0x28]
	jz	$_020
	add	rbx, 24
$_019:	cmp	byte ptr [rbx], 0
	jnz	$_014
$_020:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

AssignPointer:
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 184
	mov	rbx, r8
	mov	rsi, rcx
	test	rsi, rsi
	jnz	$_024
	cmp	byte ptr [rbx], 2
	jnz	$_022
	mov	eax, dword ptr [rbp+0x30]
	cmp	dword ptr [rbx+0x4], eax
	jz	$_021
	mov	r8d, dword ptr [rbx+0x4]
	mov	edx, dword ptr [rbp+0x30]
	lea	rcx, [DS0000+rip]
	call	AddLineQueueX@PLT
$_021:	jmp	$_023

$_022:	mov	r8, qword ptr [rbx+0x10]
	mov	edx, dword ptr [rbp+0x30]
	lea	rcx, [DS0001+rip]
	call	AddLineQueueX@PLT
$_023:	mov	rax, rsi
	jmp	$_042

$_024:	mov	byte ptr [rbp-0x85], 0
	mov	rdi, qword ptr [rbp+0x40]
	test	rdi, rdi
	je	$_033
	test	byte ptr [rdi+0x16], 0x04
	je	$_033
	xor	eax, eax
	jmp	$_028

$_025:	mov	eax, 122
	jmp	$_029

$_026:	mov	eax, 1
$_027:	add	eax, dword ptr [ModuleInfo+0x340+rip]
	jmp	$_029

$_028:	cmp	dword ptr [rbp+0x48], 2
	jz	$_025
	cmp	dword ptr [rbp+0x48], 7
	jz	$_026
	cmp	dword ptr [rbp+0x48], 9
	jz	$_027
	cmp	dword ptr [rbp+0x48], 10
	jz	$_027
$_029:	test	eax, eax
	je	$_033
	mov	ecx, dword ptr [rbp+0x30]
	mov	dword ptr [rbp+0x30], eax
	mov	edi, eax
	mov	dword ptr [rbp-0x84], ecx
	add	rbx, 24
	cmp	byte ptr [rbx], 91
	jnz	$_030
	lea	rdx, [rbp-0x80]
	mov	rcx, rbx
	call	$_009
	test	rax, rax
	je	$_042
	mov	rbx, rax
	lea	r9, [rbp-0x80]
	mov	r8d, edi
	mov	edx, edi
	lea	rcx, [DS0002+rip]
	call	AddLineQueueX@PLT
$_030:	mov	rax, rsi
	cmp	byte ptr [rbx], 46
	jne	$_042
	add	rbx, 24
	cmp	byte ptr [rsi+0x19], -60
	jnz	$_031
	mov	rsi, qword ptr [rsi+0x20]
$_031:	cmp	byte ptr [rsi+0x19], -61
	jnz	$_032
	mov	rsi, qword ptr [rsi+0x40]
$_032:	test	rsi, rsi
	je	$_042
	cmp	byte ptr [rsi+0x18], 7
	jne	$_042
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rsi+0x8]
	mov	r8d, edi
	mov	edx, edi
	lea	rcx, [DS0003+rip]
	call	AddLineQueueX@PLT
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rsi
	call	SearchNameInStruct@PLT
	xchg	rax, rsi
	test	rsi, rsi
	je	$_042
	mov	byte ptr [rbp-0x85], 1
$_033:	cmp	byte ptr [rbp-0x85], 0
	jnz	$_034
	mov	r8, qword ptr [rsi+0x8]
	mov	edx, dword ptr [rbp+0x30]
	lea	rcx, [DS0001+rip]
	call	AddLineQueueX@PLT
$_034:	add	rbx, 24
	jmp	$_039

$_035:	cmp	byte ptr [rbx], 44
	je	$_040
	cmp	byte ptr [rbx], 91
	jnz	$_036
	lea	rdx, [rbp-0x80]
	mov	rcx, rbx
	call	$_009
	test	rax, rax
	je	$_040
	mov	rbx, rax
	lea	r9, [rbp-0x80]
	mov	r8d, dword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp+0x30]
	lea	rcx, [DS0002+rip]
	call	AddLineQueueX@PLT
$_036:	cmp	byte ptr [rbx], 46
	jnz	$_040
	add	rbx, 24
	mov	rax, rsi
	cmp	byte ptr [rax+0x19], -60
	jnz	$_037
	mov	rax, qword ptr [rax+0x20]
$_037:	cmp	byte ptr [rax+0x19], -61
	jnz	$_038
	mov	rax, qword ptr [rax+0x40]
$_038:	test	rax, rax
	jz	$_040
	cmp	byte ptr [rax+0x18], 7
	jnz	$_040
	mov	rsi, rax
	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rsi+0x8]
	mov	r8d, dword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp+0x30]
	lea	rcx, [DS0003+rip]
	call	AddLineQueueX@PLT
	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rsi
	call	SearchNameInStruct@PLT
	test	rax, rax
	jz	$_040
	mov	rsi, rax
	add	rbx, 24
$_039:	cmp	byte ptr [rbx], 0
	jne	$_035
$_040:	cmp	byte ptr [rbp-0x85], 0
	jz	$_041
	cmp	qword ptr [rbp+0x50], 0
	jnz	$_041
	mov	r8d, dword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp-0x84]
	lea	rcx, [DS0004+rip]
	call	AddLineQueueX@PLT
$_041:	mov	rax, rsi
$_042:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

HandleIndirection:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 200
	mov	rbx, rdx
	cmp	dword ptr [rbp+0x38], 0
	jz	$_043
	mov	eax, dword ptr [rbx-0x14]
	mov	dword ptr [rbp-0x8], eax
	jmp	$_044

$_043:	mov	eax, dword ptr [rbx-0x44]
	mov	dword ptr [rbp-0x8], eax
	mov	eax, dword ptr [rbx-0x2C]
	mov	dword ptr [rbp-0xC], eax
$_044:	mov	eax, dword ptr [ModuleInfo+0x340+rip]
	mov	dword ptr [rbp-0x4], eax
	mov	r8, qword ptr [rbx+0x8]
	mov	edx, eax
	lea	rcx, [DS0001+rip]
	call	AddLineQueueX@PLT
	add	rbx, 24
	mov	rsi, qword ptr [rbp+0x28]
	jmp	$_052

$_045:	cmp	byte ptr [rbx], 91
	jnz	$_046
	lea	rdx, [rbp-0x8C]
	mov	rcx, rbx
	call	$_009
	test	rax, rax
	je	$_053
	mov	rbx, rax
	lea	r9, [rbp-0x8C]
	mov	r8d, dword ptr [rbp-0x4]
	mov	edx, dword ptr [rbp-0x4]
	lea	rcx, [DS0002+rip]
	call	AddLineQueueX@PLT
$_046:	cmp	byte ptr [rbx], 46
	jne	$_053
	cmp	dword ptr [rbp+0x38], 0
	jz	$_048
	cmp	byte ptr [rbx+0x30], 91
	jnz	$_047
	lea	rcx, [rbx+0x30]
	call	$_001
	test	rax, rax
	je	$_053
	cmp	byte ptr [rax], 46
	jne	$_053
	jmp	$_048

$_047:	cmp	byte ptr [rbx+0x30], 46
	jne	$_053
$_048:	add	rbx, 24
	cmp	byte ptr [rsi+0x19], -60
	jnz	$_049
	mov	rsi, qword ptr [rsi+0x20]
$_049:	cmp	byte ptr [rsi+0x19], -61
	jnz	$_050
	mov	rsi, qword ptr [rsi+0x40]
$_050:	xor	r9d, r9d
	xor	r8d, r8d
	mov	rdx, qword ptr [rbx+0x8]
	mov	rcx, rsi
	call	SearchNameInStruct@PLT
	test	rax, rax
	jnz	$_051
	mov	ecx, 2166
	call	asmerr@PLT
	jmp	$_058

$_051:	mov	rdi, rax
	add	rbx, 24
	cmp	byte ptr [rax+0x19], -60
	jnz	$_053
	mov	rax, qword ptr [rax+0x20]
	cmp	byte ptr [rax+0x19], -61
	jnz	$_053
	mov	rax, qword ptr [rbx-0x10]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rsi+0x8]
	mov	r8d, dword ptr [rbp-0x4]
	mov	edx, dword ptr [rbp-0x4]
	lea	rcx, [DS0003+rip]
	call	AddLineQueueX@PLT
	mov	rsi, rdi
$_052:	cmp	byte ptr [rbx], 0
	jz	$_053
	cmp	byte ptr [rbx], 44
	jne	$_045
$_053:	cmp	byte ptr [rsi+0x19], -60
	jnz	$_054
	mov	rsi, qword ptr [rsi+0x20]
$_054:	cmp	byte ptr [rsi+0x19], -61
	jnz	$_055
	mov	rsi, qword ptr [rsi+0x40]
$_055:	cmp	dword ptr [rbp+0x38], 0
	jz	$_056
	mov	rax, qword ptr [rbx+0x10]
	mov	qword ptr [rsp+0x20], rax
	mov	r9, qword ptr [rsi+0x8]
	mov	r8d, dword ptr [rbp-0x4]
	mov	edx, dword ptr [rbp-0x8]
	lea	rcx, [DS0005+rip]
	call	AddLineQueueX@PLT
	jmp	$_057

$_056:	mov	rax, qword ptr [rbx-0x8]
	mov	qword ptr [rsp+0x28], rax
	mov	rax, qword ptr [rsi+0x8]
	mov	qword ptr [rsp+0x20], rax
	mov	r9d, dword ptr [rbp-0x4]
	mov	r8d, dword ptr [rbp-0xC]
	mov	edx, dword ptr [rbp-0x8]
	lea	rcx, [DS0006+rip]
	call	AddLineQueueX@PLT
$_057:	call	RetLineQueue@PLT
$_058:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x72, 0x00

DS0001:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x25, 0x73, 0x00

DS0002:
	.byte  0x20, 0x6C, 0x65, 0x61, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x5B, 0x25, 0x72, 0x5D, 0x25, 0x73, 0x00

DS0003:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x5B, 0x25, 0x72, 0x5D, 0x2E, 0x25, 0x73
	.byte  0x2E, 0x25, 0x73, 0x00

DS0004:
	.byte  0x20, 0x6D, 0x6F, 0x76, 0x20, 0x25, 0x72, 0x2C
	.byte  0x20, 0x5B, 0x25, 0x72, 0x5D, 0x00

DS0005:
	.byte  0x20, 0x25, 0x72, 0x20, 0x5B, 0x25, 0x72, 0x5D
	.byte  0x2E, 0x25, 0x73, 0x25, 0x73, 0x00

DS0006:
	.byte  0x20, 0x25, 0x72, 0x20, 0x25, 0x72, 0x2C, 0x20
	.byte  0x5B, 0x25, 0x72, 0x5D, 0x2E, 0x25, 0x73, 0x2E
	.byte  0x25, 0x73, 0x00


.att_syntax prefix
