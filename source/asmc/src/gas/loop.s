
.intel_syntax noprefix

.global LoopDirective

.extern LstWriteSrcLine
.extern StoreMacro
.extern ReleaseMacroData
.extern RunMacro
.extern Tokenize
.extern EvalOperand
.extern get_curr_srcfile
.extern tstrlen
.extern asmerr
.extern ModuleInfo


.SECTION .text
	.ALIGN	16

LoopDirective:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 344
	inc	dword ptr [rbp+0x28]
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	byte ptr [ModuleInfo+0x1DB+rip], 1
	jnz	$_001
	call	LstWriteSrcLine@PLT
$_001:	mov	eax, dword ptr [rbx-0x14]
	mov	dword ptr [rbp-0x4], eax
	jmp	$_030

$_002:	mov	eax, dword ptr [rbp+0x28]
	mov	dword ptr [rbp-0x8], eax
$_003:	mov	byte ptr [rsp+0x20], 2
	lea	r9, [rbp-0x80]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, qword ptr [rbp+0x30]
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	cmp	eax, -1
	jnz	$_004
	mov	dword ptr [rbp-0x80], 0
	mov	eax, dword ptr [ModuleInfo+0x220+rip]
	mov	dword ptr [rbp+0x28], eax
	imul	ebx, dword ptr [rbp+0x28], 24
	add	rbx, qword ptr [rbp+0x30]
	jmp	$_006

$_004:	cmp	dword ptr [rbp-0x44], 0
	jz	$_005
	mov	ecx, 2026
	call	asmerr@PLT
	mov	dword ptr [rbp-0x80], 0
	jmp	$_006

$_005:	cmp	byte ptr [rbx], 0
	jz	$_006
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	mov	dword ptr [rbp-0x80], 0
$_006:	jmp	$_031

$_007:	cmp	byte ptr [rbx], 0
	jnz	$_008
	mov	rdx, qword ptr [rbx-0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_052

$_008:	mov	rcx, qword ptr [rbx+0x8]
	movzx	edx, byte ptr [ModuleInfo+0x1D4+rip]
	movzx	eax, byte ptr [rcx]
	cmp	al, 46
	jnz	$_009
	test	dl, dl
	jnz	$_010
$_009:	test	byte ptr [r15+rax], 0x40
	jnz	$_010
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_052

$_010:	mov	eax, dword ptr [rbp+0x28]
	mov	dword ptr [rbp-0x8], eax
	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	dword ptr [rbp-0x4], 467
	jz	$_011
	cmp	dword ptr [rbp-0x4], 469
	jne	$_021
$_011:	cmp	byte ptr [rbx], 44
	jz	$_012
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_052

$_012:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 9
	jnz	$_016
	cmp	byte ptr [rbx+0x1], 60
	jnz	$_016
	mov	rdi, qword ptr [rbx+0x28]
	mov	rsi, qword ptr [rbx+0x10]
	sub	rdi, rsi
	dec	rdi
	mov	eax, edi
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x30]
	mov	qword ptr [rbp-0x10], rax
	mov	rcx, rdi
	mov	rdi, rax
	inc	rsi
	rep movsb
	dec	rdi
	jmp	$_014

$_013:	dec	rdi
$_014:	cmp	byte ptr [rdi], 62
	jnz	$_013
	mov	byte ptr [rdi], 0
	cmp	byte ptr [rbx+0x18], 0
	jz	$_015
	mov	rdx, qword ptr [rbx+0x28]
	mov	ecx, 2008
	call	asmerr@PLT
$_015:	jmp	$_020

$_016:	mov	rdi, qword ptr [rbx+0x10]
	mov	rsi, rdi
	jmp	$_018

$_017:	inc	rdi
$_018:	movzx	eax, byte ptr [rdi]
	cmp	byte ptr [rdi], 0
	jz	$_019
	test	byte ptr [r15+rax], 0x08
	jz	$_017
$_019:	sub	rdi, rsi
	lea	ecx, [rdi+0x1]
	mov	eax, ecx
	add	eax, 15
	and	eax, 0xFFFFFFF0
	sub	rsp, rax
	lea	rax, [rsp+0x30]
	mov	qword ptr [rbp-0x10], rax
	mov	rcx, rdi
	mov	rdi, rax
	rep movsb
	mov	byte ptr [rdi], 0
$_020:	jmp	$_029

$_021:	jmp	$_023

$_022:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
$_023:	cmp	byte ptr [rbx], 0
	jz	$_024
	cmp	byte ptr [rbx], 44
	jnz	$_022
$_024:	cmp	byte ptr [rbx], 44
	jz	$_025
	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_052

$_025:	inc	dword ptr [rbp+0x28]
	add	rbx, 24
	cmp	byte ptr [rbx], 9
	jnz	$_026
	cmp	byte ptr [rbx+0x1], 60
	jz	$_027
$_026:	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_052

$_027:	cmp	byte ptr [rbx+0x18], 0
	jz	$_028
	mov	rdx, qword ptr [rbx+0x28]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_052

$_028:	mov	rax, qword ptr [rbx+0x8]
	mov	qword ptr [rbp-0x10], rax
$_029:	dec	dword ptr [rbp+0x28]
	sub	rbx, 24
	mov	byte ptr [rbx], 0
	mov	eax, dword ptr [rbp+0x28]
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rbp+0x28], eax
	jmp	$_031

$_030:	cmp	eax, 472
	je	$_002
	cmp	eax, 471
	je	$_003
	cmp	eax, 470
	je	$_003
	jmp	$_007

$_031:	lea	rdi, [rbp-0x120]
	xor	eax, eax
	mov	ecx, 128
	rep stosb
	lea	rdi, [rbp-0xA0]
	mov	ecx, 32
	rep stosb
	lea	rax, [DS0000+rip]
	mov	qword ptr [rbp-0x118], rax
	lea	rax, [rbp-0xA0]
	mov	qword ptr [rbp-0xB8], rax
	call	get_curr_srcfile@PLT
	mov	dword ptr [rbp-0x88], eax
	lea	rdi, [rbp-0x120]
	mov	r9d, 1
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, dword ptr [rbp+0x28]
	mov	rcx, rdi
	call	StoreMacro@PLT
	cmp	eax, -1
	jnz	$_032
	mov	rcx, rdi
	call	ReleaseMacroData@PLT
	mov	rax, -1
	jmp	$_052

$_032:	and	byte ptr [rdi+0x38], 0xFFFFFFFD
	mov	rbx, qword ptr [rbp+0x30]
	cmp	qword ptr [rbp-0x90], 0
	je	$_051
	jmp	$_050

$_033:	mov	eax, dword ptr [rbp-0x80]
	cmp	dword ptr [rdi+0x28], eax
	jge	$_034
	mov	byte ptr [rbx], 0
	mov	dword ptr [ModuleInfo+0x220+rip], 0
	lea	rax, [rbp-0x14]
	mov	qword ptr [rsp+0x28], rax
	mov	dword ptr [rsp+0x20], 2
	xor	r9d, r9d
	mov	r8, rbx
	xor	edx, edx
	mov	rcx, rdi
	call	RunMacro@PLT
	cmp	dword ptr [rbp-0x14], 0
	jne	$_051
	inc	dword ptr [rdi+0x28]
	jmp	$_033

$_034:	jmp	$_051

$_035:	jmp	$_037

$_036:	lea	rax, [rbp-0x14]
	mov	qword ptr [rsp+0x28], rax
	mov	dword ptr [rsp+0x20], 0
	xor	r9d, r9d
	mov	r8, rbx
	mov	edx, dword ptr [ModuleInfo+0x220+rip]
	mov	rcx, rdi
	call	RunMacro@PLT
	cmp	dword ptr [rbp-0x14], 0
	jne	$_051
	mov	eax, dword ptr [rbp-0x8]
	mov	dword ptr [rbp+0x28], eax
	mov	byte ptr [rsp+0x20], 0
	lea	r9, [rbp-0x80]
	mov	r8d, dword ptr [ModuleInfo+0x220+rip]
	mov	rdx, rbx
	lea	rcx, [rbp+0x28]
	call	EvalOperand@PLT
	cmp	eax, -1
	je	$_051
	inc	dword ptr [rdi+0x28]
$_037:	cmp	dword ptr [rbp-0x44], 0
	jnz	$_038
	cmp	dword ptr [rbp-0x80], 0
	jnz	$_036
$_038:	jmp	$_051

$_039:	mov	rsi, qword ptr [rbp-0x10]
$_040:	cmp	byte ptr [rsi], 0
	je	$_045
	mov	byte ptr [rbx], 9
	mov	byte ptr [rbx+0x1], 0
	lea	rax, [rbp-0x124]
	mov	qword ptr [rbx+0x8], rax
	mov	qword ptr [rbx+0x10], rax
	mov	byte ptr [rbx+0x18], 0
	mov	byte ptr [rbp-0x122], 0
	mov	dword ptr [ModuleInfo+0x220+rip], 1
	cmp	byte ptr [rsi], 33
	jnz	$_042
	lodsb
	mov	byte ptr [rbp-0x124], al
	mov	al, byte ptr [rsi]
	mov	byte ptr [rbp-0x123], al
	cmp	byte ptr [rsi], 0
	jnz	$_041
	dec	rsi
$_041:	mov	dword ptr [rbx+0x4], 2
	lea	rax, [rbp-0x122]
	mov	qword ptr [rbx+0x28], rax
	jmp	$_044

$_042:	movzx	eax, byte ptr [rsi]
	test	byte ptr [r15+rax], 0x08
	jz	$_043
	mov	byte ptr [rbp-0x124], 33
	mov	al, byte ptr [rsi]
	mov	byte ptr [rbp-0x123], al
	mov	dword ptr [rbx+0x4], 2
	lea	rax, [rbp-0x122]
	mov	qword ptr [rbx+0x28], rax
	jmp	$_044

$_043:	mov	al, byte ptr [rsi]
	mov	byte ptr [rbp-0x124], al
	mov	dword ptr [rbx+0x4], 1
	lea	rax, [rbp-0x123]
	mov	qword ptr [rbx+0x28], rax
	mov	byte ptr [rbp-0x123], 0
$_044:	lea	rax, [rbp-0x14]
	mov	qword ptr [rsp+0x28], rax
	mov	dword ptr [rsp+0x20], 2
	xor	r9d, r9d
	mov	r8, rbx
	xor	edx, edx
	mov	rcx, rdi
	call	RunMacro@PLT
	cmp	dword ptr [rbp-0x14], 0
	jne	$_051
	inc	rsi
	inc	dword ptr [rdi+0x28]
	jmp	$_040

$_045:	jmp	$_051

$_046:	mov	esi, dword ptr [ModuleInfo+0x220+rip]
	inc	esi
	mov	r9d, 3
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, esi
	mov	rcx, qword ptr [rbp-0x10]
	call	Tokenize@PLT
	mov	dword ptr [ModuleInfo+0x220+rip], eax
	imul	ebx, eax, 24
	add	rbx, qword ptr [rbp+0x30]
	mov	rdx, qword ptr [rbx-0x8]
	cmp	esi, dword ptr [ModuleInfo+0x220+rip]
	jz	$_047
	cmp	byte ptr [rbx-0x18], 44
	jnz	$_047
	cmp	byte ptr [rdx+0x1], 0
	jz	$_047
	mov	byte ptr [rbx], 9
	mov	byte ptr [rbx+0x1], 0
	mov	rcx, qword ptr [rbx+0x10]
	call	tstrlen@PLT
	mov	dword ptr [rbx+0x4], eax
	mov	ecx, dword ptr [rbx+0x4]
	add	rcx, qword ptr [rbx+0x10]
	add	rbx, 24
	mov	qword ptr [rbx+0x10], rcx
	inc	dword ptr [ModuleInfo+0x220+rip]
	mov	byte ptr [rbx], 0
$_047:	and	byte ptr [rdi+0x38], 0xFFFFFFFE
$_048:	cmp	esi, dword ptr [ModuleInfo+0x220+rip]
	jge	$_049
	lea	rax, [rbp-0x14]
	mov	qword ptr [rsp+0x28], rax
	mov	dword ptr [rsp+0x20], 4
	xor	r9d, r9d
	mov	r8, qword ptr [rbp+0x30]
	mov	edx, esi
	mov	rcx, rdi
	call	RunMacro@PLT
	mov	esi, eax
	cmp	esi, 0
	jl	$_049
	cmp	dword ptr [rbp-0x14], 0
	jnz	$_049
	inc	esi
	inc	dword ptr [rdi+0x28]
	jmp	$_048

$_049:	jmp	$_051

$_050:	cmp	dword ptr [rbp-0x4], 470
	je	$_033
	cmp	dword ptr [rbp-0x4], 471
	je	$_033
	cmp	dword ptr [rbp-0x4], 472
	je	$_035
	cmp	dword ptr [rbp-0x4], 467
	je	$_039
	cmp	dword ptr [rbp-0x4], 469
	je	$_039
	jmp	$_046

$_051:	mov	rcx, rdi
	call	ReleaseMacroData@PLT
	xor	eax, eax
$_052:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x00


.att_syntax prefix
