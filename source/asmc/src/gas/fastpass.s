
.intel_syntax noprefix

.global StoreLine
.global SkipSavedState
.global SaveVariableState
.global RestoreState
.global FastpassInit
.global NoLineStore
.global LineStoreCurr
.global StoreState
.global UseSavedState

.extern list_pos
.extern SetOfssize
.extern ContextSaveState
.extern AssumeSaveState
.extern SegmentSaveState
.extern get_curr_srcfile
.extern GetLineNumber
.extern SetInputState
.extern GetInputState
.extern LclAlloc
.extern tstrlen
.extern tmemcpy
.extern MacroLevel
.extern ModuleInfo
.extern SymSetCmpFunc


.SECTION .text
	.ALIGN	16

$_001:	push	rsi
	push	rdi
	sub	rsp, 40
	mov	qword ptr [modstate+0x8+rip], 0
	mov	qword ptr [modstate+0x10+rip], 0
	mov	dword ptr [StoreState+rip], 1
	mov	dword ptr [UseSavedState+rip], 1
	mov	dword ptr [modstate+rip], 1
	mov	ecx, 456
	lea	rsi, [ModuleInfo+0x190+rip]
	lea	rdi, [modstate+0x28+rip]
	rep movsb
	lea	rcx, [modstate+0x18+rip]
	call	GetInputState@PLT
	call	SegmentSaveState@PLT
	call	AssumeSaveState@PLT
	call	ContextSaveState@PLT
	add	rsp, 40
	pop	rdi
	pop	rsi
	ret

StoreLine:
	mov	qword ptr [rsp+0x8], rcx
	mov	qword ptr [rsp+0x10], rdx
	mov	qword ptr [rsp+0x18], r8
	push	rsi
	push	rdi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 40
	xor	eax, eax
	cmp	eax, dword ptr [NoLineStore+rip]
	jne	$_013
	cmp	dword ptr [ModuleInfo+0x210+rip], eax
	jne	$_013
	cmp	dword ptr [StoreState+rip], eax
	jnz	$_002
	call	$_001
$_002:	mov	rcx, qword ptr [rbp+0x28]
	call	tstrlen@PLT
	mov	ebx, eax
	xor	eax, eax
	cmp	dword ptr [rbp+0x30], 1
	jnz	$_003
	cmp	qword ptr [ModuleInfo+0x218+rip], rax
	jz	$_003
	mov	rcx, qword ptr [ModuleInfo+0x218+rip]
	call	tstrlen@PLT
$_003:	mov	edi, eax
	lea	ecx, [rax+rbx+0x28]
	call	LclAlloc@PLT
	mov	rcx, qword ptr [LineStoreCurr+rip]
	mov	qword ptr [LineStoreCurr+rip], rax
	mov	rsi, rax
	mov	qword ptr [rsi+0x8], rcx
	mov	qword ptr [rsi], 0
	call	GetLineNumber@PLT
	mov	dword ptr [rsi+0x10], eax
	call	get_curr_srcfile@PLT
	mov	dword ptr [rsi+0x14], eax
	mov	eax, dword ptr [MacroLevel+rip]
	mov	dword ptr [rsi+0x18], eax
	mov	eax, dword ptr [rbp+0x38]
	test	eax, eax
	jnz	$_004
	mov	eax, dword ptr [list_pos+rip]
$_004:	mov	dword ptr [rsi+0x1C], eax
	test	edi, edi
	jz	$_005
	mov	r8d, ebx
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [rsi+0x20]
	call	tmemcpy@PLT
	inc	edi
	add	rax, rbx
	mov	r8d, edi
	mov	rdx, qword ptr [ModuleInfo+0x218+rip]
	mov	rcx, rax
	call	tmemcpy@PLT
	jmp	$_006

$_005:	inc	ebx
	mov	r8d, ebx
	mov	rdx, qword ptr [rbp+0x28]
	lea	rcx, [rsi+0x20]
	call	tmemcpy@PLT
$_006:	lea	rcx, [rsi+0x20]
	jmp	$_008

$_007:	inc	rcx
$_008:	movzx	eax, byte ptr [rcx]
	test	byte ptr [r15+rax], 0x08
	jnz	$_007
	cmp	al, 37
	jnz	$_010
	mov	edx, dword ptr [rcx+0x1]
	and	edx, 0xFFFFFF
	or	edx, 0x202020
	movzx	eax, byte ptr [rcx+0x4]
	cmp	edx, 7632239
	jnz	$_009
	test	byte ptr [r15+rax], 0x44
	jz	$_010
$_009:	mov	byte ptr [rcx], 32
$_010:	cmp	qword ptr [LineStore+rip], 0
	jz	$_011
	mov	rax, qword ptr [LineStore+0x8+rip]
	mov	qword ptr [rax], rsi
	jmp	$_012

$_011:	mov	qword ptr [LineStore+rip], rsi
$_012:	mov	qword ptr [LineStore+0x8+rip], rsi
$_013:	leave
	pop	rbx
	pop	rdi
	pop	rsi
	ret

SkipSavedState:
	sub	rsp, 8
	mov	dword ptr [UseSavedState+rip], 0
	add	rsp, 8
	ret

SaveVariableState:
	push	rsi
	push	rdi
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	rsi, rcx
	or	byte ptr [rsi+0x15], 0x10
	mov	ecx, 32
	call	LclAlloc@PLT
	mov	rdi, rax
	mov	qword ptr [rdi], 0
	mov	qword ptr [rdi+0x8], rsi
	mov	byte ptr [rdi+0x19], 0
	test	byte ptr [rsi+0x14], 0x02
	jz	$_014
	inc	byte ptr [rdi+0x19]
$_014:	mov	eax, dword ptr [rsi+0x28]
	mov	dword ptr [rdi+0x10], eax
	mov	eax, dword ptr [rsi+0x50]
	mov	dword ptr [rdi+0x14], eax
	mov	al, byte ptr [rsi+0x19]
	mov	byte ptr [rdi+0x18], al
	cmp	qword ptr [modstate+0x10+rip], 0
	jz	$_015
	mov	rax, qword ptr [modstate+0x10+rip]
	mov	qword ptr [rax], rdi
	mov	qword ptr [modstate+0x10+rip], rdi
	jmp	$_016

$_015:	mov	qword ptr [modstate+0x8+rip], rdi
	mov	qword ptr [modstate+0x10+rip], rdi
$_016:	leave
	pop	rdi
	pop	rsi
	ret

RestoreState:
	sub	rsp, 40
	cmp	dword ptr [modstate+rip], 0
	jz	$_021
	mov	rdx, qword ptr [modstate+0x8+rip]
	jmp	$_019

$_017:	mov	rcx, qword ptr [rdx+0x8]
	mov	eax, dword ptr [rdx+0x10]
	mov	dword ptr [rcx+0x28], eax
	mov	eax, dword ptr [rdx+0x14]
	mov	dword ptr [rcx+0x50], eax
	and	dword ptr [rcx+0x14], 0xFFFFFFFD
	cmp	byte ptr [rdx+0x19], 0
	jz	$_018
	and	dword ptr [rcx+0x14], 0xFFFFFFFD
$_018:	mov	rdx, qword ptr [rdx]
$_019:	test	rdx, rdx
	jnz	$_017
	test	byte ptr [ModuleInfo+0x334+rip], 0x04
	mov	rax, rsi
	mov	rdx, rdi
	mov	ecx, 456
	lea	rsi, [modstate+0x28+rip]
	lea	rdi, [ModuleInfo+0x190+rip]
	rep movsb
	mov	rdi, rdx
	mov	rsi, rax
	jz	$_020
	or	byte ptr [ModuleInfo+0x334+rip], 0x04
$_020:	lea	rcx, [modstate+0x18+rip]
	call	SetInputState@PLT
	call	SetOfssize@PLT
	call	SymSetCmpFunc@PLT
$_021:	mov	rax, qword ptr [LineStore+rip]
	add	rsp, 40
	ret

FastpassInit:
	sub	rsp, 8
	mov	dword ptr [StoreState+rip], 0
	mov	dword ptr [modstate+rip], 0
	mov	qword ptr [LineStore+rip], 0
	mov	qword ptr [LineStore+0x8+rip], 0
	mov	dword ptr [UseSavedState+rip], 0
	add	rsp, 8
	ret


.SECTION .data
	.ALIGN	16

NoLineStore:
	.int   0x00000000


.SECTION .bss
	.ALIGN	16

LineStore:
	.zero	2 * 8

LineStoreCurr:
	.zero	8

StoreState:
	.zero	4

UseSavedState:
	.zero	4

modstate: .zero 62 * 8


.att_syntax prefix
