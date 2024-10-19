
.intel_syntax noprefix

.global NameSpace_
.global NameSpaceDirective

.extern LclDup
.extern LclAlloc
.extern tstrcat
.extern tstrcpy
.extern tstrlen
.extern asmerr
.extern ModuleInfo


.SECTION .text
	.ALIGN	16

NameSpace_:
	push	rbp
	mov	rbp, rsp
	push	rsi
	push	rdi
	push	rbx
	sub	rsp, 296
	mov	rsi, qword ptr [ModuleInfo+0x120+rip]
	test	rsi, rsi
	jnz	$_001
	cmp	rax, rdx
	jz	$_006
$_001:	mov	rdi, rdx
	mov	rbx, rax
	test	rdi, rdi
	jz	$_002
	cmp	rdi, rax
	jnz	$_003
$_002:	lea	rdi, [rbp-0x118]
$_003:	mov	byte ptr [rdi], 0
	test	rsi, rsi
	jnz	$_004
	mov	rdx, rax
	mov	rcx, rdi
	call	tstrcpy@PLT
	jmp	$_005

$_004:	mov	rdx, qword ptr [rsi+0x8]
	mov	rcx, rdi
	call	tstrcat@PLT
	lea	rdx, [DS0000+rip]
	mov	rcx, rdi
	call	tstrcat@PLT
	mov	rsi, qword ptr [rsi]
	test	rsi, rsi
	jnz	$_004
	mov	rdx, rbx
	mov	rcx, rdi
	call	tstrcat@PLT
$_005:	cmp	rdi, rdx
	jz	$_006
	mov	rcx, rdi
	call	LclDup@PLT
$_006:	add	rsp, 296
	pop	rbx
	pop	rdi
	pop	rsi
	leave
	ret

NameSpaceDirective:
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rbx, rdx
	mov	rsi, qword ptr [ModuleInfo+0x120+rip]
	cmp	dword ptr [rbx+0x4], 414
	jnz	$_012
	test	rsi, rsi
	jnz	$_007
	mov	ecx, 1011
	call	asmerr@PLT
	jmp	$_017

$_007:	mov	rcx, qword ptr [rsi]
	test	rcx, rcx
	jz	$_010
	jmp	$_009

$_008:	mov	rcx, qword ptr [rcx]
	mov	rsi, qword ptr [rsi]
$_009:	cmp	qword ptr [rcx], 0
	jnz	$_008
	mov	qword ptr [rsi], 0
	jmp	$_011

$_010:	mov	qword ptr [ModuleInfo+0x120+rip], 0
$_011:	xor	eax, eax
	jmp	$_017

$_012:	mov	rcx, qword ptr [rbx+0x20]
	call	tstrlen@PLT
	lea	ecx, [eax+0x11]
	call	LclAlloc@PLT
	mov	rsi, rax
	mov	qword ptr [rsi], 0
	lea	rax, [rax+0x10]
	mov	qword ptr [rsi+0x8], rax
	mov	rdx, qword ptr [rbx+0x20]
	mov	rcx, qword ptr [rsi+0x8]
	call	tstrcpy@PLT
	cmp	qword ptr [ModuleInfo+0x120+rip], 0
	jnz	$_013
	mov	qword ptr [ModuleInfo+0x120+rip], rsi
	jmp	$_016

$_013:	mov	rax, rsi
	mov	rsi, qword ptr [ModuleInfo+0x120+rip]
	jmp	$_015

$_014:	mov	rsi, qword ptr [rsi]
$_015:	cmp	qword ptr [rsi], 0
	jnz	$_014
	mov	qword ptr [rsi], rax
$_016:	xor	eax, eax
$_017:	leave
	pop	rbx
	pop	rsi
	ret


.SECTION .data
	.ALIGN	16

DS0000:
	.byte  0x5F, 0x00


.att_syntax prefix
