
.intel_syntax noprefix

.global UndefDirective

.extern asmerr
.extern ModuleInfo
.extern SymFind


.SECTION .text
	.ALIGN	16

UndefDirective:
	push	rsi
	push	rbx
	push	rbp
	mov	rbp, rsp
	sub	rsp, 32
	mov	esi, ecx
	mov	rbx, rdx
	inc	esi
	imul	eax, esi, 24
	add	rbx, rax
$_001:	cmp	byte ptr [rbx], 8
	jz	$_002
	mov	rdx, qword ptr [rbx+0x8]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_007

$_002:	mov	rcx, qword ptr [rbx+0x8]
	call	SymFind@PLT
	test	rax, rax
	jz	$_003
	mov	byte ptr [rax+0x18], 0
$_003:	inc	esi
	add	rbx, 24
	cmp	esi, dword ptr [ModuleInfo+0x220+rip]
	jge	$_006
	cmp	byte ptr [rbx], 44
	jnz	$_004
	cmp	byte ptr [rbx+0x18], 0
	jnz	$_005
$_004:	mov	rdx, qword ptr [rbx+0x10]
	mov	ecx, 2008
	call	asmerr@PLT
	jmp	$_007

$_005:	inc	esi
	add	rbx, 24
$_006:	cmp	esi, dword ptr [ModuleInfo+0x220+rip]
	jl	$_001
	xor	eax, eax
$_007:	leave
	pop	rbx
	pop	rsi
	ret

.att_syntax prefix
