
.intel_syntax noprefix

.global DeleteLineQueue
.global tvsprintf
.global tvfprintf
.global tfprintf
.global tsprintf
.global tprintf
.global AddLineQueue
.global AddLineQueueX
.global RunLineQueue
.global InsertLineQueue

.extern ResWordTable
.extern PreprocessLine
.extern ParseLine
.extern PopInputStatus
.extern PushInputStatus
.extern MemFree
.extern MemAlloc
.extern tstrcpy
.extern myltoa
.extern ModuleInfo
.extern fwrite
.extern write


.SECTION .text
	.ALIGN	16

DeleteLineQueue:
	push	rsi
	push	rdi
	sub	rsp, 40
	mov	rsi, qword ptr [ModuleInfo+0xC8+rip]
$_001:	test	rsi, rsi
	jz	$_002
	mov	rdi, qword ptr [rsi]
	mov	rcx, rsi
	call	MemFree@PLT
	mov	rsi, rdi
	jmp	$_001

$_002:
	mov	qword ptr [ModuleInfo+0xC8+rip], 0
	add	rsp, 40
	pop	rdi
	pop	rsi
	ret

tvsprintf:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 136
	mov	rsi, qword ptr [rbp+0x30]
	mov	rdi, qword ptr [rbp+0x28]
$_003:	cmp	byte ptr [rsi], 0
	je	$_036
	lodsb
	cmp	al, 37
	jne	$_034
	mov	byte ptr [rbp-0x4A], 32
	mov	dword ptr [rbp-0x44], 0
	mov	byte ptr [rbp-0x49], 0
	mov	rbx, qword ptr [rbp+0x38]
	lodsb
	cmp	al, 42
	jnz	$_005
	mov	eax, dword ptr [rbx]
	add	rbx, 8
	cmp	eax, 0
	jge	$_004
	mov	byte ptr [rbp-0x49], 45
	neg	eax
$_004:	mov	dword ptr [rbp-0x44], eax
	lodsb
$_005:	cmp	al, 45
	jnz	$_006
	mov	byte ptr [rbp-0x49], al
	lodsb
$_006:	cmp	al, 48
	jz	$_007
	cmp	al, 46
	jnz	$_008
$_007:	mov	byte ptr [rbp-0x4A], al
	lodsb
$_008:	jmp	$_010

$_009:	movsx	eax, al
	imul	edx, dword ptr [rbp-0x44], 10
	add	eax, edx
	add	eax, -48
	mov	dword ptr [rbp-0x44], eax
	lodsb
$_010:	cmp	al, 48
	jc	$_011
	cmp	al, 57
	jbe	$_009
$_011:	xor	edx, edx
	mov	ecx, dword ptr [rbx]
	cmp	al, 108
	jnz	$_013
	lodsb
	cmp	al, 108
	jnz	$_012
	lodsb
$_012:	mov	rcx, qword ptr [rbx]
	jmp	$_015

$_013:	cmp	al, 115
	jnz	$_014
	mov	rcx, qword ptr [rbx]
	jmp	$_015

$_014:	cmp	al, 100
	jnz	$_015
	movsxd	rcx, ecx
$_015:	add	rbx, 8
	mov	qword ptr [rbp+0x38], rbx
	mov	ebx, 16
	jmp	$_032

$_016:	lea	rdx, [ResWordTable+rip]
	imul	ecx, ecx, 16
	mov	rax, qword ptr [rdx+rcx+0x8]
	movzx	ecx, byte ptr [rdx+rcx+0x2]
	xchg	rax, rsi
	rep movsb
	mov	byte ptr [rdi], 0
	mov	rsi, rax
	jmp	$_033

$_017:	test	cl, cl
	jz	$_018
	mov	al, cl
	stosb
$_018:	jmp	$_033

$_019:	test	rcx, rcx
	jnz	$_020
	lea	rcx, [DS0000+rip]
$_020:	mov	rdx, rdi
$_021:	mov	al, byte ptr [rcx]
	stosb
	inc	rcx
	test	al, al
	jnz	$_021
	dec	rdi
	cmp	byte ptr [rbp-0x49], 0
	jnz	$_022
	cmp	rdi, rdx
	jnz	$_023
$_022:	mov	rax, rdi
	sub	rax, rdx
	cmp	eax, dword ptr [rbp-0x44]
	jnc	$_023
	mov	ecx, dword ptr [rbp-0x44]
	sub	ecx, eax
	mov	al, byte ptr [rbp-0x4A]
	rep stosb
$_023:	jmp	$_033

$_024:	test	rcx, rcx
	sets	bh
$_025:	mov	bl, 10
$_026:	movzx	eax, bl
	mov	dword ptr [rbp-0x48], eax
	shr	ebx, 8
	mov	dword ptr [rsp+0x20], 0
	mov	r9d, ebx
	mov	r8d, eax
	lea	rdx, [rbp-0x40]
	call	myltoa@PLT
	mov	ebx, eax
	cmp	byte ptr [rbp-0x49], 0
	jnz	$_027
	cmp	eax, dword ptr [rbp-0x44]
	jnc	$_027
	mov	ecx, dword ptr [rbp-0x44]
	sub	ecx, eax
	mov	al, byte ptr [rbp-0x4A]
	rep stosb
$_027:	mov	ecx, ebx
	mov	rdx, rsi
	lea	rsi, [rbp-0x40]
	rep movsb
	cmp	byte ptr [rbp-0x49], 0
	jz	$_028
	cmp	ebx, dword ptr [rbp-0x44]
	jnc	$_028
	mov	ecx, dword ptr [rbp-0x44]
	sub	ecx, ebx
	mov	al, byte ptr [rbp-0x4A]
	rep stosb
$_028:	mov	rsi, rdx
	mov	al, byte ptr [rsi-0x1]
	cmp	dword ptr [rbp-0x48], 10
	jz	$_033
	cmp	al, 100
	jz	$_029
	cmp	al, 117
	jnz	$_033
$_029:	mov	al, 116
	stosb
	jmp	$_033

$_030:	mov	rax, qword ptr [rbp+0x38]
	mov	rcx, qword ptr [rax-0x8]
	mov	dword ptr [rbp-0x44], 16
	mov	byte ptr [rbp-0x4A], 48
	jmp	$_026

$_031:	stosb
	jmp	$_033

$_032:	cmp	al, 114
	je	$_016
	cmp	al, 99
	je	$_017
	cmp	al, 115
	je	$_019
	cmp	al, 100
	je	$_024
	cmp	al, 117
	je	$_025
	cmp	al, 120
	je	$_026
	cmp	al, 88
	je	$_026
	cmp	al, 112
	jz	$_030
	jmp	$_031

$_033:	jmp	$_035

$_034:	stosb
$_035:	jmp	$_003

$_036:
	mov	byte ptr [rdi], 0
	mov	rax, rdi
	sub	rax, qword ptr [rbp+0x28]
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

tvfprintf:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 4128
	mov	r8, qword ptr [rbp+0x30]
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [rbp-0x1000]
	call	tvsprintf
	mov	rcx, qword ptr [rbp+0x20]
	mov	edx, eax
	mov	esi, 1
	lea	rdi, [rbp-0x1000]
	call	fwrite@PLT
	leave
	pop	rdi
	pop	rsi
	ret

tfprintf:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	lea	r8, [rbp+0x20]
	mov	rdx, qword ptr [rbp+0x18]
	mov	rcx, qword ptr [rbp+0x10]
	call	tvfprintf
	leave
	ret

tsprintf:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	lea	r8, [rbp+0x20]
	mov	rdx, qword ptr [rbp+0x18]
	mov	rcx, qword ptr [rbp+0x10]
	call	tvsprintf
	leave
	ret

tprintf:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 4128
	lea	r8, [rbp+0x28]
	mov	rdx, qword ptr [rbp+0x20]
	lea	rcx, [rbp-0x1000]
	call	tvsprintf
	mov	edx, eax
	lea	rsi, [rbp-0x1000]
	mov	edi, 1
	call	write@PLT
	leave
	pop	rdi
	pop	rsi
	ret

AddLineQueue:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	mov	rsi, rcx
	mov	rdi, rsi
	xor	eax, eax
	mov	ecx, 4294967295
	repne scasb
	not	ecx
	mov	ebx, ecx
	dec	ebx
	jz	$_040
$_037:	mov	rdi, rsi
	mov	ecx, ebx
	mov	eax, 10
	repne scasb
	sete	al
	sub	rdi, rax
	mov	rcx, rdi
	sub	rcx, rsi
	sub	ebx, ecx
	test	ecx, ecx
	jz	$_039
	add	ecx, 16
	call	MemAlloc@PLT
	xor	ecx, ecx
	mov	qword ptr [rax], rcx
	cmp	rcx, qword ptr [ModuleInfo+0xC8+rip]
	jz	$_041
	mov	rcx, qword ptr [ModuleInfo+0xD0+rip]
	mov	qword ptr [rcx], rax
$_038:	mov	qword ptr [ModuleInfo+0xD0+rip], rax
	mov	rcx, rdi
	sub	rcx, rsi
	lea	rdi, [rax+0x8]
	rep movsb
	mov	byte ptr [rdi], cl
$_039:	inc	rsi
	dec	ebx
	jg	$_037
$_040:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

$_041:
	mov	qword ptr [ModuleInfo+0xC8+rip], rax
	jmp	$_038

AddLineQueueX:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	mov	qword ptr [rsp+0x20], r9
	push	rbp
	mov	rbp, rsp
	sub	rsp, 48
	mov	byte ptr [rbp-0x9], 0
	mov	ecx, dword ptr [ModuleInfo+0x174+rip]
	cmp	ecx, 2048
	jbe	$_042
	mov	byte ptr [rbp-0x9], 1
	call	MemAlloc@PLT
	jmp	$_043

$_042:	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x20]
$_043:	mov	qword ptr [rbp-0x8], rax
	lea	r8, [rbp+0x18]
	mov	rdx, qword ptr [rbp+0x10]
	mov	rcx, qword ptr [rbp-0x8]
	call	tvsprintf
	mov	rcx, qword ptr [rbp-0x8]
	call	AddLineQueue
	cmp	byte ptr [rbp-0x9], 0
	jz	$_044
	mov	rcx, qword ptr [rbp-0x8]
	call	MemFree@PLT
$_044:	leave
	ret

RunLineQueue:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 80
	lea	rcx, [rbp-0x20]
	call	PushInputStatus@PLT
	mov	qword ptr [rbp-0x28], rax
	inc	dword ptr [ModuleInfo+0x210+rip]
	mov	rsi, qword ptr [ModuleInfo+0xC8+rip]
	mov	qword ptr [ModuleInfo+0xC8+rip], 0
$_045:	test	rsi, rsi
	jz	$_047
	lea	rdx, [rsi+0x8]
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	tstrcpy@PLT
	mov	rcx, qword ptr [rbp-0x28]
	call	PreprocessLine@PLT
	test	rax, rax
	jz	$_046
	mov	rcx, qword ptr [rbp-0x28]
	call	ParseLine@PLT
$_046:	mov	rcx, rsi
	mov	rsi, qword ptr [rsi]
	call	MemFree@PLT
	jmp	$_045

$_047:
	dec	dword ptr [ModuleInfo+0x210+rip]
	lea	rcx, [rbp-0x20]
	call	PopInputStatus@PLT
	leave
	pop	rdi
	pop	rsi
	ret

InsertLineQueue:
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 72
	mov	ebx, dword ptr [ModuleInfo+0x210+rip]
	lea	rcx, [rbp-0x20]
	call	PushInputStatus@PLT
	mov	qword ptr [rbp-0x28], rax
	mov	dword ptr [ModuleInfo+0x210+rip], 0
	mov	rsi, qword ptr [ModuleInfo+0xC8+rip]
	mov	qword ptr [ModuleInfo+0xC8+rip], 0
$_048:	test	rsi, rsi
	jz	$_050
	lea	rdx, [rsi+0x8]
	mov	rcx, qword ptr [ModuleInfo+0x178+rip]
	call	tstrcpy@PLT
	mov	rcx, qword ptr [rbp-0x28]
	call	PreprocessLine@PLT
	test	rax, rax
	jz	$_049
	mov	rcx, qword ptr [rbp-0x28]
	call	ParseLine@PLT
$_049:	mov	rcx, rsi
	mov	rsi, qword ptr [rsi]
	call	MemFree@PLT
	jmp	$_048

$_050:
	mov	dword ptr [ModuleInfo+0x210+rip], ebx
	lea	rcx, [rbp-0x20]
	call	PopInputStatus@PLT
	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x28, 0x6E, 0x75, 0x6C, 0x6C, 0x29, 0x00


.att_syntax prefix
